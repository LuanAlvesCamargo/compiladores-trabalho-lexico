#include "Lexer.h"
#include <cctype>

Lexer::Lexer(string codigo) {
    this->codigo = codigo;
}

void Lexer::inicializar() {
    i = 0;
    estado_atual = 0;
    lexema = "";
    tokens.clear();
}

vector<Token> Lexer::Analisar() {
    inicializar();
    while (i < codigo.size()) {
        char c = codigo[i];

        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') { q0(); continue; }
        else if (isdigit(c)) { q1(); continue; }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') { q2(); continue; }
        else if (isalpha((unsigned char)c) || c == '_') { q3(); continue; }
        else if (c == '=') { q4(); continue; }
        else if (c == ';') { q5(); continue; }
        else if (c == '>' || c == '<' || c == '!') { q7(); continue; }
        else if (c == '&' || c == '|') { q8(); continue; }
        else if (c == '(') { q9(); continue; }
        else if (c == ')') { q10(); continue; }
        else if (c == '{') { q11(); continue; }
        else if (c == '}') { q12(); continue; }
        else if (c == '[') { q13(); continue; }
        else if (c == ']') { q14(); continue; }
        else if (c == ',') { q15(); continue; }
        else if (c == '.') { q20(); continue; }
        else if (c == ':') { q21(); continue; }
        else if (c == '?') { q22(); continue; }
        else if (c == '"') { q17(); continue; }
        else {
            lexema = string(1, c);
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lexema));
            i++;
        }
    }
    return tokens;
}

// Estados simplificados:
void Lexer::q0() { i++; } // espaço/tab/linha
void Lexer::q1() { lexema=""; while(i<codigo.size() && isdigit(codigo[i])) lexema+=codigo[i++]; tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, lexema)); }
void Lexer::q2() { lexema = codigo[i++]; tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, lexema)); }
void Lexer::q3() { lexema=""; while(i<codigo.size() && (isalnum(codigo[i]) || codigo[i]=='_')) lexema+=codigo[i++];
    if(lexema=="int"||lexema=="float"||lexema=="double"||lexema=="char"||lexema=="bool"||
       lexema=="string"||lexema=="main"||lexema=="if"||lexema=="else"||lexema=="while"||lexema=="for"||lexema=="do") tokens.push_back(Token(TipoDeToken::PALAVRA_RESERVADA, lexema));
    else tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lexema));
}
void Lexer::q4() { lexema = codigo[i++]; if(i<codigo.size() && codigo[i]=='='){ lexema+=codigo[i++]; tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema)); } else tokens.push_back(Token(TipoDeToken::OPERADOR_ATRIBUICAO, lexema)); }
void Lexer::q5() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::PONTO_E_VIRGULA, lexema)); }
void Lexer::q6() {} // não usada diretamente
void Lexer::q7() { lexema=string(1,codigo[i++]); if(i<codigo.size() && codigo[i]=='='){ lexema+=codigo[i++]; } tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema)); }
void Lexer::q8() { lexema=string(1,codigo[i++]); if(i<codigo.size() && codigo[i]==lexema[0]) lexema+=codigo[i++]; tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema)); }
void Lexer::q9() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::ABRE_PARENTESES, lexema)); }
void Lexer::q10() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::FECHA_PARENTESES, lexema)); }
void Lexer::q11() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::ABRE_CHAVES, lexema)); }
void Lexer::q12() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::FECHA_CHAVES, lexema)); }
void Lexer::q13() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::ABRE_COLCHETES, lexema)); }
void Lexer::q14() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::FECHA_COLCHETES, lexema)); }
void Lexer::q15() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::VIRGULA, lexema)); }
void Lexer::q16() { lexema=""; while(i<codigo.size() && (isdigit(codigo[i])||codigo[i]=='.')) lexema+=codigo[i++]; tokens.push_back(Token(TipoDeToken::NUMERO_REAL, lexema)); }
void Lexer::q17() { i++; lexema=""; while(i<codigo.size() && codigo[i]!='"') lexema+=codigo[i++]; i++; tokens.push_back(Token(TipoDeToken::STRING, lexema)); }
void Lexer::q18() { lexema=string(1,codigo[i++]); if(i<codigo.size() && codigo[i]==lexema[0]) { i++; lexema+=lexema[0]; tokens.push_back(Token(TipoDeToken::INCREMENTO, lexema)); } }
void Lexer::q19() { lexema=string(1,codigo[i++]); if(i<codigo.size() && codigo[i]==lexema[0]) { i++; lexema+=lexema[0]; tokens.push_back(Token(TipoDeToken::DECREMENTO, lexema)); } }
void Lexer::q20() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::PONTO, lexema)); }
void Lexer::q21() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::DOIS_PONTOS, lexema)); }
void Lexer::q22() { lexema=string(1,codigo[i++]); tokens.push_back(Token(TipoDeToken::INTERROGACAO, lexema)); }

