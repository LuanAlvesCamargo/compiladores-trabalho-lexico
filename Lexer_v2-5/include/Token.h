#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TipoDeToken.h"

class Token
{
public:
    Token(TipoDeToken tipo, const std::string& lexema) 
        : lexema(lexema), tipo(tipo) {} 

    TipoDeToken getTipo() const { return tipo; }
    std::string getLexema() const { return lexema; }

    static std::string tipoParaString(TipoDeToken tipo) {
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
        case TipoDeToken::ABRE_CHAVE: return "ABRE_CHAVE";
        case TipoDeToken::FECHA_CHAVE: return "FECHA_CHAVE";
        case TipoDeToken::ABRE_COLCHETE: return "ABRE_COLCHETE";
        case TipoDeToken::FECHA_COLCHETE: return "FECHA_COLCHETE";
        case TipoDeToken::VIRGULA: return "VIRGULA";
        case TipoDeToken::STRING: return "STRING";
        case TipoDeToken::PONTO: return "PONTO";
        case TipoDeToken::DOIS_PONTOS: return "DOIS_PONTOS";
        case TipoDeToken::INTERROGACAO: return "INTERROGACAO";
        case TipoDeToken::INCREMENTO: return "INCREMENTO";
        case TipoDeToken::DECREMENTO: return "DECREMENTO";
        case TipoDeToken::ABRE_ASPAS: return "ABRE_ASPAS";
        case TipoDeToken::FECHA_ASPAS: return "FECHA_ASPAS";
        case TipoDeToken::TOKEN_INVALIDO: return "TOKEN_INVALIDO";
        default: return "DESCONHECIDO";
    }
}

private:
    std::string lexema;
    TipoDeToken tipo;
};

#endif // TOKEN_H

