#ifndef LEXERTEST_H
#define LEXERTEST_H

#include "Lexer.h"
#include <iostream>

class LexerTest {
public:
    static void executarTestes() {
        std::string codigo = R"(


                ==========
            }
        )";

        Lexer lexer(codigo);
        std::vector<Token> listaDeTokens = lexer.Analisar();

        for (auto token : listaDeTokens) {
            std::cout << "Token: " << token.getLexema()
                      << " (" << Token::tipoParaString(token.getTipo())
                      << ")" << std::endl;
        }
    }
};

#endif // LEXERTEST_H
