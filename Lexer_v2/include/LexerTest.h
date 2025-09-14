#ifndef LEXERTEST_H
#define LEXERTEST_H

#include "Lexer.h"
#include <iostream>

class LexerTest {
public:
    static void executarTestes() {
        std::string codigo = R"(
            x == y

            int main() {
                int x = 10;
                float y = 3.14;
                double z = 0.5;
                char c = 'A';
                bool b = true;
                x++;
                y--;
                if (x > y && z < 1.0) {
                    x = x + 1;
                } else {
                    y = y - 1.0;
                }
                for (int i = 0; i < 10; i++) {
                    z = z / 2.0;
                }
                string s = "texto";
                bool flag = false;
                z = z * 2;
                a = b ? x : y;
                cout << s;
                @  # caractere inválido
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
