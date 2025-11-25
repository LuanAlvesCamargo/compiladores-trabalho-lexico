
#include "Parser.h"
#include <iostream>

Parser::Parser(std::vector<Token> t) : tokens(t), i(0) {}

Token Parser::atual() {
    return tokens[i];
}

void Parser::consumir() {
    if (i < tokens.size()) i++;
}

void Parser::erro(std::string msg) {
    std::cerr << "[ERRO DE SINTAXE] " << msg 
              << " (token: " << atual().lexema << ")\n";
    exit(1);
}

void Parser::analisar() {
    std::cout << "ÁRVORE SINTÁTICA:\n";
    Programa();
}

void Parser::Programa() {
    std::cout << "Programa\n";

    while (atual().tipo != TipoDeToken::FIM) {
        Statement();
    }
}

void Parser::Statement() {

    Token t = atual();

    // Declaração: int x = expr ;
    if (t.tipo == TipoDeToken::PALAVRA_CHAVE &&
       (t.lexema == "int" || t.lexema == "float" || t.lexema == "string"))
    {
        std::cout << "  Declaracao: " << t.lexema << "\n";
        consumir();

        if (atual().tipo != TipoDeToken::IDENTIFICADOR)
            erro("Esperado identificador na declaração");

        std::cout << "    Nome: " << atual().lexema << "\n";
        consumir();

        if (atual().tipo == TipoDeToken::ATRIBUICAO) {
            std::cout << "    Atribuição inicial\n";
            consumir();
            Expr();
        }

        if (atual().tipo != TipoDeToken::PONTO_VIRGULA)
            erro("Esperado ';' ao final da declaração");

        consumir();
        return;
    }

    // IF
    if (t.tipo == TipoDeToken::PALAVRA_CHAVE && t.lexema == "if") {
        std::cout << "  If\n";
        consumir();

        if (atual().tipo != TipoDeToken::PARENTESE_ESQ)
            erro("Esperado '(' após if");

        consumir();
        Expr();
        if (atual().tipo != TipoDeToken::PARENTESE_DIR)
            erro("Esperado ')' no if");
        consumir();

        Statement();
        return;
    }

    // WHILE
    if (t.tipo == TipoDeToken::PALAVRA_CHAVE && t.lexema == "while") {
        std::cout << "  While\n";
        consumir();

        if (atual().tipo != TipoDeToken::PARENTESE_ESQ)
            erro("Esperado '(' após while");

        consumir();
        Expr();
        if (atual().tipo != TipoDeToken::PARENTESE_DIR)
            erro("Esperado ')' no while");
        consumir();

        Statement();
        return;
    }

    // FOR
    if (t.tipo == TipoDeToken::PALAVRA_CHAVE && t.lexema == "for") {
        std::cout << "  For\n";
        consumir();

        if (atual().tipo != TipoDeToken::PARENTESE_ESQ)
            erro("Esperado '(' após for");
        consumir();

        // inicialização
        if (atual().tipo != TipoDeToken::PONTO_VIRGULA) {
            Expr();
        }
        if (atual().tipo != TipoDeToken::PONTO_VIRGULA)
            erro("Esperado ';' no for (parte 1)");
        consumir();

        // condição
        if (atual().tipo != TipoDeToken::PONTO_VIRGULA) {
            Expr();
        }
        if (atual().tipo != TipoDeToken::PONTO_VIRGULA)
            erro("Esperado ';' no for (parte 2)");
        consumir();

        // incremento
        if (atual().tipo != TipoDeToken::PARENTESE_DIR) {
            Expr();
        }

        if (atual().tipo != TipoDeToken::PARENTESE_DIR)
            erro("Esperado ')'");
        consumir();

        Statement();
        return;
    }

    // BLOCO
    if (t.tipo == TipoDeToken::CHAVE_ESQ) {
        Bloco();
        return;
    }

    // Expressão / Atribuição
    if (t.tipo == TipoDeToken::IDENTIFICADOR) {

        std::cout << "  Statement expressão / atribuição\n";

        // Pode ser chamada de função
        if (tokens[i+1].tipo == TipoDeToken::PARENTESE_ESQ) {
            Expr();
        }
        else if (tokens[i+1].tipo == TipoDeToken::ATRIBUICAO) {
            std::cout << "    Atribuicao: " << t.lexema << "\n";
            consumir(); // id
            consumir(); // =
            Expr();
        }
        else {
            Expr();
        }

        if (atual().tipo != TipoDeToken::PONTO_VIRGULA)
            erro("Esperado ';' ao final da expressão");
        consumir();
        return;
    }

    // Nada válido encontrado
    erro("Comando inválido");
}

void Parser::Bloco() {
    std::cout << "  Bloco {\n";
    consumir(); // {

    while (atual().tipo != TipoDeToken::CHAVE_DIR &&
           atual().tipo != TipoDeToken::FIM)
    {
        Statement();
    }

    if (atual().tipo != TipoDeToken::CHAVE_DIR)
        erro("Esperado '}'");

    consumir();
    std::cout << "  }\n";
}


void Parser::Expr() {
    std::cout << "    Expr\n";
    ExprLogica();
}

void Parser::ExprLogica() {
    ExprRel();
    while (atual().lexema == "&&" || atual().lexema == "||") {
        std::cout << "      Op lógico: " << atual().lexema << "\n";
        consumir();
        ExprRel();
    }
}

void Parser::ExprRel() {
    ExprArit();
    while (atual().tipo == TipoDeToken::OPERADOR_RELACIONAL &&
          (atual().lexema == "<" || atual().lexema == ">" ||
           atual().lexema == "<=" || atual().lexema == ">=" ||
           atual().lexema == "==" || atual().lexema == "!="))
    {
        std::cout << "      Op relacional: " << atual().lexema << "\n";
        consumir();
        ExprArit();
    }
}

void Parser::ExprArit() {
    Termo();
    while (atual().tipo == TipoDeToken::OPERADOR_ARITMETICO &&
          (atual().lexema == "+" || atual().lexema == "-"))
    {
        std::cout << "      Op arit: " << atual().lexema << "\n";
        consumir();
        Termo();
    }
}

void Parser::Termo() {
    Fator();
    
    while (atual().tipo == TipoDeToken::OPERADOR_ARITMETICO &&
          (atual().lexema == "*" || atual().lexema == "/"))
    {
        std::cout << "      Op arit: " << atual().lexema << "\n";
        consumir();
        Fator();
    }
}

void Parser::Fator() {

    Token t = atual();

    if (t.tipo == TipoDeToken::NUMERO_INTEIRO) {
        std::cout << "      Número: " << t.lexema << "\n";
        consumir();
        return;
    }

    if (t.tipo == TipoDeToken::IDENTIFICADOR) {

        // chamada de função
        if (tokens[i+1].tipo == TipoDeToken::PARENTESE_ESQ) {
            std::cout << "      Chamada funcao: " << t.lexema << "\n";
            consumir(); // nome
            consumir(); // (

            if (atual().tipo != TipoDeToken::PARENTESE_DIR) {
                Expr();
                while (atual().tipo == TipoDeToken::VIRGULA) {
                    consumir();
                    Expr();
                }
            }

            if (atual().tipo != TipoDeToken::PARENTESE_DIR)
                erro("Esperado ')'");
            consumir();
            return;
        }

        std::cout << "      Id: " << t.lexema << "\n";
        consumir();
        return;
    }

    if (t.tipo == TipoDeToken::PARENTESE_ESQ) {
        std::cout << "      ( Expr )\n";
        consumir();
        Expr();
        if (atual().tipo != TipoDeToken::PARENTESE_DIR)
            erro("Esperado ')'");
        consumir();
        return;
    }

    erro("Fator inválido");
}
