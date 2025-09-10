#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TipoDeToken.h"

using namespace std;

class Token
{
    public:
        Token(TipoDeToken tipo,
              string lexema) :
                  tipo(tipo),
                  lexema(lexema) {}

        TipoDeToken getTipo(){
            return tipo;
        }

        string getLexema(){
            return lexema;
        }

        static string tipoParaString(TipoDeToken tipo){
           switch(tipo)
           {
               case TipoDeToken::NUMERO_INTEIRO :
                   return "NUMERO_INTEIRO"; break;
               default: return "DESCONHECIDO";
           }
        }


    private:
        string lexema;
        TipoDeToken tipo;
};

#endif // TOKEN_H
