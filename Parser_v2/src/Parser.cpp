#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(const vector<Token> &tokens)
{
    this->tokens = tokens;
    this->i = 0;
}

// -------------------- helpers --------------------

Token Parser::tokenAtual()
{
    if (i < (int)tokens.size())
        return tokens[i];
    return Token(TipoDeToken::INVALIDO, "");
}

Token Parser::consumir()
{
    Token t = tokenAtual();
    if (i < (int)tokens.size()) i++;
    return t;
}

bool Parser::verificar(TipoDeToken tipo)
{
    return tokenAtual().getTipo() == tipo;
}

bool Parser::verificarLexema(const string &lex)
{
    return tokenAtual().getLexema() == lex;
}

bool Parser::consumirSe(TipoDeToken tipo)
{
    if (verificar(tipo))
    {
        consumir();
        return true;
    }
    return false;
}

// void Parser::erro(string msg)
// {
//     cerr << "Erro de sintaxe: " << msg
//          << " — perto de '" << tokenAtual().getLexema() << "'\n";
//     throw runtime_error(msg);
// }

void Parser::erro(const string& msg)
{
    cerr << "Erro de sintaxe: " << msg
         << " — perto de '" << tokenAtual().getLexema() << "'\n";
    throw runtime_error(msg);
}


// -------------------- API pública --------------------

void Parser::analisar()
{
    // Wrapper público chamado no main
    try {
        parse();
    } catch (...) {
        throw; // propaga exceção para main
    }
}

// -------------------- parser interno --------------------

void Parser::parse()
{
    cout << "\n--- INICIANDO PARSE ---\n";

    while (tokenAtual().getTipo() != TipoDeToken::INVALIDO)
    {
        declaracao();
    }

    cout << "--- PARSE COMPLETO ---\n";
}

// ==============================
// Declarações e comandos
// ==============================

void Parser::declaracao()
{
    if (verificar(TipoDeToken::PALAVRA_RESERVADA))
    {
        string palavra = tokenAtual().getLexema();

        if (palavra == "int" || palavra == "double" ||
            palavra == "bool" || palavra == "string")
        {
            declaracaoVariavel();
            return;
        }

        if (palavra == "if")
        {
            comandoIf();
            return;
        }
        if (palavra == "while")
        {
            comandoWhile();
            return;
        }
        if (palavra == "return")
        {
            comandoReturn();
            return;
        }
    }

    comando();
}

void Parser::declaracaoVariavel()
{
    cout << "Reconhecido: declaração de variável\n";

    // consumir o tipo
    consumir();

    if (!verificar(TipoDeToken::IDENTIFICADOR))
        erro("Esperado identificador na declaração");

    // lista de ids separados por vírgula (ex: a, b, c)
    consumir(); // consome o primeiro identificador

    // aceita possivelmente inicialização com '='? seu lexer marca '=' como OPERADOR_ATRIBUICAO
    // (se quiser suportar "int x = 3, y = 4;" é preciso checar e chamar expressao() quando vir '=')
    while (verificarLexema(","))
    {
        consumir(); // ','
        if (!verificar(TipoDeToken::IDENTIFICADOR))
            erro("Esperado identificador apos ','");
        consumir(); // nome
    }

    if (!consumirSe(TipoDeToken::PONTO_E_VIRGULA))
        erro("Esperado ';' no fim da declaração");
}

void Parser::comando()
{
    // se inicia com identificador -> atribuicao (ou expressão)
    if (verificar(TipoDeToken::IDENTIFICADOR))
    {
        atribuicao();
        return;
    }

    // bloco
    if (verificar(TipoDeToken::ABRE_CHAVE))
    {
        bloco();
        return;
    }

    // se chega aqui, comando não reconhecido
    erro("Comando inválido");
}

void Parser::bloco()
{
    if (!consumirSe(TipoDeToken::ABRE_CHAVE))
        erro("Esperado '{' no inicio do bloco");

    while (!verificar(TipoDeToken::FECHA_CHAVE) &&
           tokenAtual().getTipo() != TipoDeToken::INVALIDO)
    {
        declaracao();
    }

    if (!consumirSe(TipoDeToken::FECHA_CHAVE))
        erro("Esperado '}' no fim do bloco");
}

// ==============================
// If / While / Return
// ==============================

void Parser::comandoIf()
{
    // consumir 'if'
    consumir();

    if (!consumirSe(TipoDeToken::ABRE_PAREN))
        erro("Esperado '(' apos if");

    expressao();

    if (!consumirSe(TipoDeToken::FECHA_PAREN))
        erro("Esperado ')' apos condicao do if");

    // comando: bloco ou comando simples
    comando();

    // else opcional
    if (verificarLexema("else"))
    {
        consumir();
        comando();
    }
}

void Parser::comandoWhile()
{
    consumir(); // while

    if (!consumirSe(TipoDeToken::ABRE_PAREN))
        erro("Esperado '(' apos while");

    expressao();

    if (!consumirSe(TipoDeToken::FECHA_PAREN))
        erro("Esperado ')' apos condicao do while");

    comando();
}

void Parser::comandoReturn()
{
    consumir(); // return
    expressao();
    if (!consumirSe(TipoDeToken::PONTO_E_VIRGULA))
        erro("Esperado ';' apos return");
}

// ==============================
// Atribuição
// ==============================

void Parser::atribuicao()
{
    // Consome o identificador inicial
    cout << "Reconhecido: possivel atribuicao/expressao iniciada por IDENTIFICADOR\n";
    consumir(); // identificador

    // possibilidade de indexação: a[ expr ]
    while (consumirSe(TipoDeToken::ABRE_COLCHETE))
    {
        expressao();
        if (!consumirSe(TipoDeToken::FECHA_COLCHETE))
            erro("Esperado ']' apos indice");
    }

    // postfix ++ / --
    if (consumirSe(TipoDeToken::INCREMENTO) || consumirSe(TipoDeToken::DECREMENTO))
    {
        if (!consumirSe(TipoDeToken::PONTO_E_VIRGULA))
            erro("Esperado ';' apos ++/--");
        return;
    }

    // atribuição: '='
    if (consumirSe(TipoDeToken::OPERADOR_ATRIBUICAO))
    {
        expressao();
        if (!consumirSe(TipoDeToken::PONTO_E_VIRGULA))
            erro("Esperado ';' apos atribuicao");
        return;
    }

    // Se não for atribuição, tratamos como expressão seguida de ';'
    // já consumimos o identificador no início, agora parseamos resto da expressão
    // (por simplicidade assumimos que já estava tudo consumido)
    if (!consumirSe(TipoDeToken::PONTO_E_VIRGULA))
        erro("Esperado ';' apos expressao iniciada por identificador");
}

// ==============================
// Expressões (precedência)
// ==============================

void Parser::expressao()
{
    expressaoLogica();
}

void Parser::expressaoLogica()
{
    expressaoRelacional();

    while (verificar(TipoDeToken::OPERADOR_LOGICO))
    {
        consumir(); // && ou ||
        expressaoRelacional();
    }
}

void Parser::expressaoRelacional()
{
    expressaoAritmetica();

    while (verificar(TipoDeToken::OPERADOR_RELACIONAL))
    {
        consumir(); // == != < > <= >=
        expressaoAritmetica();
    }
}

void Parser::expressaoAritmetica()
{
    termo();

    while (verificarLexema("+") || verificarLexema("-"))
    {
        consumir();
        termo();
    }
}

void Parser::termo()
{
    fator();

    while (verificarLexema("*") || verificarLexema("/") || verificarLexema("%"))
    {
        consumir();
        fator();
    }
}

void Parser::fator()
{
    // literal número
    if (verificar(TipoDeToken::NUMERO_INTEIRO))
    {
        consumir();
        return;
    }

    // string literal tratada como ABRE_ASPAS IDENTIFICADOR FECHA_ASPAS no seu lexer
    if (verificar(TipoDeToken::ABRE_ASPAS))
    {
        consumir(); // "
        // conteúdo (IDENTIFICADOR) pode ou não existir
        if (verificar(TipoDeToken::IDENTIFICADOR))
            consumir();
        if (!consumirSe(TipoDeToken::FECHA_ASPAS))
            erro("Esperado '\"' de fechamento da string");
        return;
    }

    // identificador (possivel indexacao e postfix)
    if (verificar(TipoDeToken::IDENTIFICADOR))
    {
        consumir(); // id

        // indices repetidos
        while (consumirSe(TipoDeToken::ABRE_COLCHETE))
        {
            expressao();
            if (!consumirSe(TipoDeToken::FECHA_COLCHETE))
                erro("Esperado ']' apos indice");
        }

        // postfix ++/--
        if (consumirSe(TipoDeToken::INCREMENTO) || consumirSe(TipoDeToken::DECREMENTO))
        {
            return;
        }
        return;
    }

    // parenteses
    if (consumirSe(TipoDeToken::ABRE_PAREN))
    {
        expressao();
        if (!consumirSe(TipoDeToken::FECHA_PAREN))
            erro("Esperado ')' apos expressao entre parenteses");
        return;
    }

    erro("Expressao invalida");
}
