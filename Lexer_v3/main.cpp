#include <iostream>
#include "Lexer.h"

using namespace std;

int main() {
    string codigo = R"(
        int x = 10;
        float y = 3.14;
        x++;
        y--;
        if(x > y && y < 5) {
            x = x + 1;
        }
    )";

    Lexer lexer(codigo);
    vector<Token> tokens = lexer.Analisar();

    for (auto &token : tokens) {
        cout << "Token: " << token.getValor() 
             << " (" << token.tipoToString() << ")" << endl;
    }

    return 0;
}
