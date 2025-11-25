
#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include "Token.h"

class Lexer {
private:
    std::string codigo;
    int i;

    bool isLetra(char c);
    bool isDigito(char c);
    bool isOperadorArit(char c);
    bool isOperadorRel(char c);
    bool isParenteses(char c);
    bool isChave(char c);
    bool isAtrib(char c);
    bool isLogico(char c);
    bool isPalavraChave(std::string s);

public:
    Lexer(std::string c);
    std::vector<Token> tokens;

    void analisar();
};

#endif
