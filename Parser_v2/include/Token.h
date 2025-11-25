#ifndef TOKEN_H
#define TOKEN_H

#include "TipoDeToken.h"
#include <string>

using namespace std;

class Token
{
    public:
        Token() : tipo(TipoDeToken::INVALIDO), lexema("") {}
        Token(TipoDeToken tipo, string lexema) : tipo(tipo), lexema(lexema) {}

        static string tipoParaString(TipoDeToken tipo){
            switch(tipo){
                case TipoDeToken::ESPACO: return "ESPACO";
                case TipoDeToken::NUMERO_INTEIRO : return "NUMERO_INTEIRO";
                case TipoDeToken::OPERADOR_ARITMETICO : return "OPERADOR_ARITMETICO";
                case TipoDeToken::IDENTIFICADOR : return "IDENTIFICADOR";
                case TipoDeToken::OPERADOR_ATRIBUICAO : return "OPERADOR_ATRIBUICAO";
                case TipoDeToken::PONTO_E_VIRGULA : return "PONTO_E_VIRGULA";
                case TipoDeToken::PALAVRA_RESERVADA : return "PALAVRA_RESERVADA";
                case TipoDeToken::OPERADOR_RELACIONAL : return "OPERADOR_RELACIONAL";
                case TipoDeToken::OPERADOR_LOGICO : return "OPERADOR_LOGICO";
                case TipoDeToken::ABRE_PAREN : return "ABRE_PAREN";
                case TipoDeToken::FECHA_PAREN : return "FECHA_PAREN";
                case TipoDeToken::ABRE_CHAVE : return "ABRE_CHAVE";
                case TipoDeToken::FECHA_CHAVE : return "FECHA_CHAVE";
                case TipoDeToken::ABRE_COLCHETE : return "ABRE_COLCHETE";
                case TipoDeToken::FECHA_COLCHETE : return "FECHA_COLCHETE";
                case TipoDeToken::INCREMENTO : return "INCREMENTO";
                case TipoDeToken::DECREMENTO : return "DECREMENTO";
                case TipoDeToken::PONTO : return "PONTO";
                case TipoDeToken::DOIS_PONTOS : return "DOIS_PONTOS";
                case TipoDeToken::INTERROGACAO : return "INTERROGACAO";
                case TipoDeToken::ABRE_ASPAS : return "ABRE_ASPAS";
                case TipoDeToken::FECHA_ASPAS : return "FECHA_ASPAS";
                case TipoDeToken::INVALIDO: return "INVALIDO";
                default: return "DESCONHECIDO";
            }
        }

        TipoDeToken getTipo() const {
            return tipo;
        }

        string getLexema() const {
            return lexema;
        }

        string print() const {
            return "<" + lexema + ", " + Token::tipoParaString(tipo) + ">";
        }

    private:
        TipoDeToken tipo;
        string lexema;
};

#endif // TOKEN_H
