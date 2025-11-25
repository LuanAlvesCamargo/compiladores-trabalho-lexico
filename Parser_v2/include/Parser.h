#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "Token.h"

using namespace std;

class Parser
{
public:
    Parser(const vector<Token>& tokens);

    // Função pública chamada no main
    void analisar();

private:
    // versão interna do parse (implementação)
    void parse();

    vector<Token> tokens;
    int i;

    // Helpers para manipular tokens
    Token tokenAtual();
    Token consumir();

    bool verificar(TipoDeToken tipo);
    bool verificarLexema(const string& lex);
    bool consumirSe(TipoDeToken tipo);

    void erro(const string& msg);

    // Regras da gramática (métodos)
    void declaracao();
    void declaracaoVariavel();
    void comando();
    void bloco();
    void comandoIf();
    void comandoWhile();
    void comandoReturn();
    void atribuicao();

    // Expressões
    void expressao();
    void expressaoLogica();
    void expressaoRelacional();
    void expressaoAritmetica();
    void termo();
    void fator();
};

#endif // PARSER_H
