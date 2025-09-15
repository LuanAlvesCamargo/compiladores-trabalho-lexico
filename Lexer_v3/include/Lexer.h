#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

class Lexer {
public:
    Lexer(string codigo);
    vector<Token> Analisar();

private:
    string codigo, lexema;
    int i, estado_atual;
    vector<Token> tokens;

    void inicializar();

    void q0(); void q1(); void q2(); void q3(); void q4(); void q5();
    void q6(); void q7(); void q8(); void q9(); void q10(); void q11();
    void q12(); void q13(); void q14(); void q15(); void q16(); void q17();
    void q18(); void q19(); void q20(); void q21(); void q22();
};

#endif // LEXER_H
