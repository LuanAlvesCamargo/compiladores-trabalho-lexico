#include "Lexer.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(std::string c) : codigo(c), i(0) {}

bool Lexer::isLetra(char c) { return std::isalpha(c) || c=='_'; }
bool Lexer::isDigito(char c) { return std::isdigit(c); }
bool Lexer::isOperadorArit(char c) { return c=='+'||c=='-'||c=='*'||c=='/'; }
bool Lexer::isOperadorRel(char c) { return c=='<'||c=='>'||c=='!'; }
bool Lexer::isParenteses(char c) { return c=='(' || c==')'; }
bool Lexer::isChave(char c) { return c=='{' || c=='}'; }
bool Lexer::isAtrib(char c) { return c=='='; }
bool Lexer::isLogico(char c){ return c=='&' || c=='|'; }

bool Lexer::isPalavraChave(std::string s){
    return s == "if" || s=="while" || s=="for" ||
           s == "int" || s=="float" || s=="string";
}

void Lexer::analisar() {
    while (i < codigo.size()) {
        char c = codigo[i];

        if (isspace(c)) { i++; continue; }

        // Identificadores e palavras-chave
        if (isLetra(c)) {
            std::string lex = "";
            while (i < codigo.size() && (isLetra(codigo[i]) || isDigito(codigo[i]))) {
                lex += codigo[i];
                i++;
            }
            if (isPalavraChave(lex)) tokens.push_back(Token(TipoDeToken::PALAVRA_CHAVE, lex));
            else tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lex));
            continue;
        }

        // Números
        if (isDigito(c)) {
            std::string num = "";
            while (i < codigo.size() && isDigito(codigo[i])) {
                num += codigo[i];
                i++;
            }
            tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, num));
            continue;
        }

        // Operadores aritméticos
        if (isOperadorArit(c)) {
            tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, std::string(1,c)));
            i++;
            continue;
        }

        // Operadores relacionais e lógicos
        if (isOperadorRel(c) || isLogico(c)) {
            std::string op = "";
            op += c;
            i++;
            if (i < codigo.size() && codigo[i]=='=') {
                op += "=";
                i++;
            }
            tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, op));
            continue;
        }

        // Atribuição =
        if (isAtrib(c)) {
            tokens.push_back(Token(TipoDeToken::ATRIBUICAO, "="));
            i++;
            continue;
        }

        // Parênteses
        if (c=='(') tokens.push_back(Token(TipoDeToken::PARENTESE_ESQ,"("));
        else if (c==')') tokens.push_back(Token(TipoDeToken::PARENTESE_DIR,")"));
        else if (c=='{') tokens.push_back(Token(TipoDeToken::CHAVE_ESQ,"{"));
        else if (c=='}') tokens.push_back(Token(TipoDeToken::CHAVE_DIR,"}"));
        else if (c==';') tokens.push_back(Token(TipoDeToken::PONTO_VIRGULA,";"));
        else if (c==',') tokens.push_back(Token(TipoDeToken::VIRGULA,","));
        else {
            tokens.push_back(Token(TipoDeToken::INVALIDO, std::string(1,c)));
        }

        i++;
    }

    tokens.push_back(Token(TipoDeToken::FIM, "EOF"));
}
