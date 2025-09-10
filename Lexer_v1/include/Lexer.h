#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

class Lexer
{
    public:
        Lexer(string codigo);
        vector<Token> Analisar();

    private:
        string codigo, lexema;
        void q0(), q1(), inicializar();
        bool isEspaco(char c);
        bool isDigito(char c);
        int i, estado_atual;
        vector<Token> tokens;
};

#endif // LEXER_H
