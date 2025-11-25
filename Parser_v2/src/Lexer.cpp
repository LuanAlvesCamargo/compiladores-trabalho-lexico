#include "Lexer.h"
#include <stdexcept>
#include <cctype>
#include <set>

Lexer::Lexer(string codigo)
{
    this->codigo = codigo;
}

void Lexer::inicializar(){
    tokens.clear();
    i = 0;
    lexema = "";
}

bool Lexer::isEspaco(char c){
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool Lexer::isDigito(char c){
    return c >= '0' && c <= '9';
}

bool Lexer::isCaractereOuUnderline(char c){
    return (c == '_') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Lexer::isRelacionalInicio(char c){
    return c == '=' || c == '<' || c == '>' || c == '!';
}

bool Lexer::isOperadorAritmeticoChar(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool Lexer::isReservada(const string &s){
    static const set<string> reservadas = {
        "if","else","while","for","return","int","float","double","char","bool","true","false","string","void","break","continue"
    };
    return reservadas.find(s) != reservadas.end();
}

void Lexer::consumirNumero(){
    lexema = "";
    while (i < (int)codigo.size() && isDigito(codigo[i])) {
        lexema += codigo[i++];
    }
    tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, lexema));
    lexema = "";
}

void Lexer::consumirIdentificadorOuReservada(){
    lexema = "";
    while (i < (int)codigo.size() && (isCaractereOuUnderline(codigo[i]) || isDigito(codigo[i]))) {
        lexema += codigo[i++];
    }
    if (isReservada(lexema)){
        tokens.push_back(Token(TipoDeToken::PALAVRA_RESERVADA, lexema));
    } else {
        tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lexema));
    }
    lexema = "";
}

void Lexer::consumirStringLiteral(){
    // já consumiu a " inicial? aqui i aponta para o próximo caractere após as aspas iniciais
    tokens.push_back(Token(TipoDeToken::ABRE_ASPAS, "\""));
    lexema = "";
    while (i < (int)codigo.size() && codigo[i] != '"') {
        // aceita qualquer caractere (não trata escapes por simplicidade)
        lexema += codigo[i++];
    }
    if (i >= (int)codigo.size()){
        throw runtime_error("Lexer: string não fechada (aspas ausentes)");
    }
    // se encontrou a aspas final
    if (!lexema.empty()){
        // conteúdo entre aspas - vou guardar como IDENTIFICADOR (pode adaptar)
        tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lexema));
    } else {
        // string vazia - ainda guarda conteúdo vazio como IDENTIFICADOR
        tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lexema));
    }
    // consumir a aspas de fechamento
    tokens.push_back(Token(TipoDeToken::FECHA_ASPAS, "\""));
    i++; // pula a aspas de fechamento
    lexema = "";
}

void Lexer::consumirOperadorOuSimbolo(){
    char c = codigo[i];

    // dois caracteres possíveis (==, !=, <=, >=, &&, ||, ++, --)
    if (i + 1 < (int)codigo.size()){
        string dois;
        dois += codigo[i];
        dois += codigo[i+1];

        if (dois == "==" || dois == "!=" || dois == "<=" || dois == ">="){
            tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, dois));
            i += 2;
            return;
        }
        if (dois == "&&" || dois == "||"){
            tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, dois));
            i += 2;
            return;
        }
        if (dois == "++"){
            tokens.push_back(Token(TipoDeToken::INCREMENTO, "++"));
            i += 2;
            return;
        }
        if (dois == "--"){
            tokens.push_back(Token(TipoDeToken::DECREMENTO, "--"));
            i += 2;
            return;
        }
    }

    // um caractere
    switch(c){
        case '+':
        case '-':
        case '*':
        case '/':
            tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, string(1,c)));
            i++;
            return;
        case '=':
            tokens.push_back(Token(TipoDeToken::OPERADOR_ATRIBUICAO, "="));
            i++;
            return;
        case ';':
            tokens.push_back(Token(TipoDeToken::PONTO_E_VIRGULA, ";"));
            i++;
            return;
        case '(':
            tokens.push_back(Token(TipoDeToken::ABRE_PAREN, "("));
            i++;
            return;
        case ')':
            tokens.push_back(Token(TipoDeToken::FECHA_PAREN, ")"));
            i++;
            return;
        case '{':
            tokens.push_back(Token(TipoDeToken::ABRE_CHAVE, "{"));
            i++;
            return;
        case '}':
            tokens.push_back(Token(TipoDeToken::FECHA_CHAVE, "}"));
            i++;
            return;
        case '[':
            tokens.push_back(Token(TipoDeToken::ABRE_COLCHETE, "["));
            i++;
            return;
        case ']':
            tokens.push_back(Token(TipoDeToken::FECHA_COLCHETE, "]"));
            i++;
            return;
        case '<':
            tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, "<"));
            i++;
            return;
        case '>':
            tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, ">"));
            i++;
            return;
        case '!':
            tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, "!"));
            i++;
            return;
        case '.':
            tokens.push_back(Token(TipoDeToken::PONTO, "."));
            i++;
            return;
        case ':':
            tokens.push_back(Token(TipoDeToken::DOIS_PONTOS, ":"));
            i++;
            return;
        case '?':
            tokens.push_back(Token(TipoDeToken::INTERROGACAO, "?"));
            i++;
            return;
        case '"':
            // consumir aspas e o literal até a próxima "
            i++; // pula a aspas inicial
            consumirStringLiteral();
            return;
        default:
            {
                string msg = "Caractere invalido ou nao esperado: ";
                msg += c;
                throw runtime_error(msg);
            }
    }
}

vector<Token> Lexer::Analisar(){
    inicializar();
    while (i < (int)codigo.size()){
        char c = codigo[i];

        if (isEspaco(c)){
            // opcional: poderíamos emitir token ESPACO, mas normalmente ignoramos espaços
            i++;
            continue;
        }

        if (isDigito(c)){
            consumirNumero();
            continue;
        }

        if (isCaractereOuUnderline(c)){
            consumirIdentificadorOuReservada();
            continue;
        }

        // operadores ou símbolos
        consumirOperadorOuSimbolo();
    }

    return tokens;
}
