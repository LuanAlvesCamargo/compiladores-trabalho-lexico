#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TipoDeToken.h"

using namespace std;

class Token {
public:
    Token(TipoDeToken tipo, string valor) : tipo(tipo), valor(valor) {}

    TipoDeToken getTipo() { return tipo; }
    string getValor() { return valor; }

    string tipoToString() {
        switch(tipo) {
            case TipoDeToken::NUMERO_INTEIRO: return "NUMERO_INTEIRO";
            case TipoDeToken::NUMERO_REAL: return "NUMERO_REAL";
            case TipoDeToken::IDENTIFICADOR: return "IDENTIFICADOR";
            case TipoDeToken::PALAVRA_RESERVADA: return "PALAVRA_RESERVADA";
            case TipoDeToken::OPERADOR_ARITMETICO: return "OPERADOR_ARITMETICO";
            case TipoDeToken::OPERADOR_ATRIBUICAO: return "OPERADOR_ATRIBUICAO";
            case TipoDeToken::PONTO_E_VIRGULA: return "PONTO_E_VIRGULA";
            case TipoDeToken::OPERADOR_RELACIONAL: return "OPERADOR_RELACIONAL";
            case TipoDeToken::OPERADOR_LOGICO: return "OPERADOR_LOGICO";
            case TipoDeToken::ABRE_PARENTESES: return "ABRE_PARENTESES";
            case TipoDeToken::FECHA_PARENTESES: return "FECHA_PARENTESES";
            case TipoDeToken::ABRE_CHAVES: return "ABRE_CHAVES";
            case TipoDeToken::FECHA_CHAVES: return "FECHA_CHAVES";
            case TipoDeToken::ABRE_COLCHETES: return "ABRE_COLCHETES";
            case TipoDeToken::FECHA_COLCHETES: return "FECHA_COLCHETES";
            case TipoDeToken::VIRGULA: return "VIRGULA";
            case TipoDeToken::STRING: return "STRING";
            case TipoDeToken::PONTO: return "PONTO";
            case TipoDeToken::DOIS_PONTOS: return "DOIS_PONTOS";
            case TipoDeToken::INTERROGACAO: return "INTERROGACAO";
            case TipoDeToken::INCREMENTO: return "INCREMENTO";
            case TipoDeToken::DECREMENTO: return "DECREMENTO";
            case TipoDeToken::TOKEN_INVALIDO: return "TOKEN_INVALIDO";
            default: return "DESCONHECIDO";
        }
    }

private:
    TipoDeToken tipo;
    string valor;
};

#endif // TOKEN_H
