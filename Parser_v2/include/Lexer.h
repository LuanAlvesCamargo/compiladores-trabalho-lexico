#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string>
#include <vector>

using namespace std;

class Lexer
{
    public:
        Lexer(string codigo);
        vector<Token> Analisar();

    private:
        vector<Token> tokens;
        int i;
        string lexema, codigo;

        void inicializar();

        bool isEspaco(char c);
        bool isDigito(char c);
        bool isCaractereOuUnderline(char c);

        bool isRelacionalInicio(char c);
        bool isOperadorAritmeticoChar(char c);

        bool isReservada(const string &s);

        void consumirNumero();
        void consumirIdentificadorOuReservada();
        void consumirOperadorOuSimbolo();
        void consumirStringLiteral();
};

#endif // LEXER_H
