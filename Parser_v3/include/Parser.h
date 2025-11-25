
#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"

class Parser {
private:
    std::vector<Token> tokens;
    int i;

    Token atual();
    void consumir();

    void erro(std::string msg);

    // Regras da gramática
    void Programa();
    void Statement();
    void Bloco();
    void Expr();
    void ExprLogica();
    void ExprRel();
    void ExprArit();
    void Termo();
    void Fator();

public:
    Parser(std::vector<Token> t);
    void analisar();
};

#endif
