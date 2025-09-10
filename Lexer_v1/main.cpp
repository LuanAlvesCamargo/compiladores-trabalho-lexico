#include <iostream>
#include "Lexer.h"

using namespace std;

int main()
{
    string codigo = "  1 	\n   23    \t    456  \n   98";
    Lexer lexer(codigo);
    try
    {
        vector<Token> listaDeTokens = lexer.Analisar();
        for(auto token : listaDeTokens){
            cout << "Token: " << token.getLexema() <<
            " (" << Token::tipoParaString(token.getTipo())
                 << ")" << endl;
        }
    }
    catch(exception &e)
    {
        cout << "Erro: " << e.what() << endl;
    }

    return 0;

}
