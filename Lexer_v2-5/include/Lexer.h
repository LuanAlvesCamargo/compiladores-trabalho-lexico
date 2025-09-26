#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "LexerException.h"
#include <string>
#include <vector>

class Lexer {
public:
    Lexer(std::string codigo);
    std::vector<Token> Analisar();

private:
    std::string codigo;
    std::string lexema;
    size_t i;
    int estado_atual;
    std::vector<Token> tokens;

    void inicializar();
    void q0();
    void q1();
    void q2();
    void q3();
    void q4();
    void q5();
    void q6();
    void q7();
    void q8();
    void q9();
    void q10();
    void q11();
    void q12();
    void q13();
    void q14();
    void q15();
    void q16();
    void q17();
    void q18();
    void q19();
    void q20();
    void q21();
    void q22();
    void q23();
    void q24();

    void q_exclamacao();          // ✅ adicionado
    void q_aritmetico_simples();  // ✅ adicionado

    bool isEspaco(char c);
    bool isDigito(char c);
    bool isLetra(char c);
    bool isOperadorAritmetico(char c);
};

#endif // LEXER_H
