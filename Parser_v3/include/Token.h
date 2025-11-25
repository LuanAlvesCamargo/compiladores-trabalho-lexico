
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TipoDeToken.h"

class Token {
public:
    TipoDeToken tipo;
    std::string lexema;

    Token(TipoDeToken t, std::string l) : tipo(t), lexema(l) {}

    static std::string tipoParaString(TipoDeToken t) {
        switch (t) {
            case TipoDeToken::IDENTIFICADOR: return "IDENTIFICADOR";
            case TipoDeToken::NUMERO_INTEIRO: return "NUMERO_INTEIRO";
            case TipoDeToken::OPERADOR_ARITMETICO: return "OPERADOR_ARITMETICO";
            case TipoDeToken::OPERADOR_RELACIONAL: return "OPERADOR_RELACIONAL";
            case TipoDeToken::OPERADOR_LOGICO: return "OPERADOR_LOGICO";
            case TipoDeToken::ATRIBUICAO: return "ATRIBUICAO";
            case TipoDeToken::PARENTESE_ESQ: return "PARENTESE_ESQ";
            case TipoDeToken::PARENTESE_DIR: return "PARENTESE_DIR";
            case TipoDeToken::CHAVE_ESQ: return "CHAVE_ESQ";
            case TipoDeToken::CHAVE_DIR: return "CHAVE_DIR";
            case TipoDeToken::PONTO_VIRGULA: return "PONTO_VIRGULA";
            case TipoDeToken::VIRGULA: return "VIRGULA";
            case TipoDeToken::PALAVRA_CHAVE: return "PALAVRA_CHAVE";
            case TipoDeToken::FIM: return "FIM";
            default: return "INVALIDO";
        }
    }
};

#endif
