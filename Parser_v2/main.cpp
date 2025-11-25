#include <iostream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main()
{
    // Exemplo: substitua por qualquer código/fração em C++ que queira testar
    string codigo = R"(int main() {
    int x = 10;
    x++;
    int y = x + 4 * (5 - 2);
    string s = "ola mundo";
    if (x >= y) { y = y - 1; }
})";

    Lexer lexer(codigo);
    try{
        cout << "Iniciando Analise Lexica..." << endl << endl;
        vector<Token> tokens = lexer.Analisar();
        for(auto token : tokens){
            cout << "Token: " << token.getLexema() << " (" << Token::tipoParaString(token.getTipo()) << ")" << endl;
        }
        cout << endl <<
        "Analise Lexica concluida com sucesso!"
        << endl << endl;

        cout << "Iniciando Analise Sintatica (expressao aritmetica exemplo)..."
             << endl << endl;
        // Para o parser atual (que reconhece expressões) vamos testar uma expressão simples:
        // construir vetor de tokens correspondentes à expressão: 10 + 4 * 5
        // Para demonstração, montamos tokens manualmente:
        vector<Token> exprTokens;
        exprTokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO,"10"));
        exprTokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO,"+"));
        exprTokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO,"4"));
        exprTokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO,"*"));
        exprTokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO,"5"));

        Parser parser(exprTokens);
        parser.analisar();
        cout << endl <<
        "Analise Sintatica concluida com sucesso!"
        << endl;

    }
    catch(exception &e){
        cout << "Erro: " << e.what() << endl;
    }
    return 0;
}

/*
// Entrada 1
        "int z + 23",

        // Entrada 2
        "int menino neymar + 23",

        // Entrada 3
        R"(int main() {
            int x = 42, y = 0;
            bool ativo = true, desligado = false;
            double pi = 3.14159;
            return y;
        })",

        // Entrada 4
        R"(int main() {
            if (x > 0 && ativo || !desligado) {
                y = (x * 10) % 7;
            }
            return y;
        })",

        // Entrada 5
        R"(int main(){
            double _neymar_10 = 9.75 , messi = 0;
            string texto = "santos";
            if (xxx >= r9)
                while (teste == 10 || teste2 != 20 && !sair)
                    a[75] = ( 123.456 - 5 ) / 2;
            i++;
            return 0;
        })",

        // Entrada 6
        R"(int main() {
            int x = 10;
            x++;
            int y = x + 4 * (5 - 2);
            string s = "ola mundo";
            if (x >= y) { y = y - 1; }
        })"
*/