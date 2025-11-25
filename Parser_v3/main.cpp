
#include <iostream>
#include <vector>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main() {

    string codigo;
    cout << "Digite o código a ser analisado:\n";
    getline(cin, codigo);

    Lexer lexer(codigo);
    lexer.analisar();  

    vector<Token> tokens = lexer.tokens; 

    cout << "\n=== LISTA DE TOKENS ===\n";
    for (const Token& token : tokens) {
        cout << "Token: " << token.lexema               
             << " (" << Token::tipoParaString(token.tipo) << ")" 
             << endl;
    }

    cout << "\n=== PARSER ===\n";
    Parser parser(tokens);
    parser.analisar();

    return 0;
}
