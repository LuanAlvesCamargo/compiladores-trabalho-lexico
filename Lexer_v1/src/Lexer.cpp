#include "Lexer.h"
#include <stdexcept>

Lexer::Lexer(string codigo)
{
    this->codigo = codigo;
}

void Lexer::q0(){
    char c = codigo[i];
    if (isEspaco(c)) {
        i++;
    }
    else{
        if (isDigito(c)){
            lexema = c;
            estado_atual = 1;
            i++;
            //caso especial - final do código:
            if (i == codigo.size()) {
                tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, lexema));
            }
        }
        else{
            string msg = "Caractere invalido: ";
            msg += c;
            throw runtime_error(msg);
        }
    }
}

void Lexer::q1(){
    char c = codigo[i];
    if (isDigito(c)) {
        lexema += c;
        i++;
        if (i == codigo.size()) {
            tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, lexema));
        }
    }
    else {
        tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, lexema));
        lexema = "";
        estado_atual = 0;
    }

}

void Lexer::inicializar(){
    i = 0;
    estado_atual = 0;
    tokens.clear();
    lexema = "";
}

vector<Token> Lexer::Analisar(){
    inicializar();
    while (i < codigo.size()){
        switch(estado_atual){
            case 0: q0(); break;
            case 1: q1(); break;
            default: throw runtime_error("Estado invalido");
        }
    }
    return tokens;
}

bool Lexer::isEspaco(char c){
    return c == ' ' || c == '\t' ||
           c == '\r' || c == '\n';
}

bool Lexer::isDigito(char c){
    return c >= '0' && c <= '9';
}
