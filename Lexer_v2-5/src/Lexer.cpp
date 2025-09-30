#include "Lexer.h"
#include <cctype>
#include <string>

Lexer::Lexer(std::string codigo) {
    this->codigo = codigo;
}

void Lexer::inicializar() {
    i = 0;
    estado_atual = 0;
    tokens.clear();
    lexema = "";
}

std::vector<Token> Lexer::Analisar() {
    inicializar();
    while (i < codigo.size()) {
        char c = codigo[i];

        if (isEspaco(c)) { q0(); continue; }
        else if (isDigito(c)) { q1(); continue; }
        else if (c == '+') { q18(); continue; }
        else if (c == '-') { q19(); continue; }
        else if (isOperadorAritmetico(c)) { q2(); continue; }
        else if (isLetra(c)) { q3(); continue; }
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
        else if (c == '.') {
            if (i + 1 < codigo.size() && isDigito(codigo[i+1])) q16();
            else q20();
            continue;
        }
        else if (c == '"') { q17(); continue; }
        else if (c == ':') { q21(); continue; }
        else if (c == '?') { q22(); continue; }
        else {
            std::string lex(1, c);
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lex));
            i++;
        }
    }
    return tokens;
}

void Lexer::q0() { i++; }

void Lexer::q1() {
    lexema = "";
    while (i < codigo.size() && isDigito(codigo[i])) lexema += codigo[i++];

    if (i < codigo.size() && codigo[i] == '.') {
        if (i + 1 < codigo.size() && isDigito(codigo[i+1])) {
            lexema += codigo[i++];
            while (i < codigo.size() && isDigito(codigo[i])) lexema += codigo[i++];
            tokens.push_back(Token(TipoDeToken::NUMERO_REAL, lexema));
            return;
        }
    }
    tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, lexema));
}

void Lexer::q2() {
    lexema = std::string(1, codigo[i++]);
    tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, lexema));
}

void Lexer::q3() {
    lexema = "";
    while (i < codigo.size() && (isLetra(codigo[i]) || isDigito(codigo[i]) || codigo[i]=='_')) {
        lexema += codigo[i++];
    }
    if (lexema == "int" || lexema == "float" || lexema == "double" ||
        lexema == "char" || lexema == "bool" || lexema == "string" ||
        lexema == "main" || lexema == "if" || lexema == "else" ||
        lexema == "while" || lexema == "for" || lexema == "do") {
        tokens.push_back(Token(TipoDeToken::PALAVRA_RESERVADA, lexema));
    } else {
        tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lexema));
    }
}

void Lexer::q4() {
    lexema = std::string(1, codigo[i++]);
    if (i < codigo.size() && codigo[i] == '=') {
        lexema += codigo[i++];
        tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
        if (i < codigo.size() && codigo[i] == '=') {
            std::string inval = "";
            while (i < codigo.size() && codigo[i] == '=') inval += codigo[i++];
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, inval));
        }
    } else {
        tokens.push_back(Token(TipoDeToken::OPERADOR_ATRIBUICAO, lexema));
    }
}

void Lexer::q5() {
    lexema = std::string(1, codigo[i++]);
    tokens.push_back(Token(TipoDeToken::PONTO_E_VIRGULA, lexema));
    if (i < codigo.size() && codigo[i] == ';') {
        std::string invalido = "";
        while (i < codigo.size() && codigo[i] == ';') invalido += codigo[i++];
        tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, invalido));
    }
}

void Lexer::q7() {
    lexema = std::string(1, codigo[i++]);
    if ((lexema == ">" || lexema == "<") && i < codigo.size() && codigo[i] == '=') {
        lexema += codigo[i++];
        tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
        return;
    }
    if (lexema == "!") {
        if (i < codigo.size() && codigo[i] == '=') {
            lexema += codigo[i++];
            tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
        } else tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema));
        return;
    }
    tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
}

void Lexer::q8() {
    lexema = std::string(1, codigo[i++]);
    if (i < codigo.size() && codigo[i] == lexema[0]) {
        lexema += codigo[i++];
        tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema));
    } else tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lexema));
}

void Lexer::q9() { tokens.push_back(Token(TipoDeToken::ABRE_PARENTESES, std::string(1, codigo[i++]))); }

void Lexer::q10() { tokens.push_back(Token(TipoDeToken::FECHA_PARENTESES, std::string(1, codigo[i++]))); }

void Lexer::q11() { tokens.push_back(Token(TipoDeToken::ABRE_CHAVE, std::string(1, codigo[i++]))); }

void Lexer::q12() { tokens.push_back(Token(TipoDeToken::FECHA_CHAVE, std::string(1, codigo[i++]))); }

void Lexer::q13() { tokens.push_back(Token(TipoDeToken::ABRE_COLCHETE, std::string(1, codigo[i++]))); }

void Lexer::q14() { tokens.push_back(Token(TipoDeToken::FECHA_COLCHETE, std::string(1, codigo[i++]))); }

void Lexer::q15() {
    lexema = std::string(1, codigo[i++]);
    tokens.push_back(Token(TipoDeToken::VIRGULA, lexema));
    if (i < codigo.size() && codigo[i] == ',') {
        std::string invalido = "";
        while (i < codigo.size() && codigo[i] == ',') invalido += codigo[i++];
        tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, invalido));
    }
}

void Lexer::q16() {
    lexema = std::string(1, codigo[i++]);
    while (i < codigo.size() && isDigito(codigo[i])) lexema += codigo[i++];
    tokens.push_back(Token(TipoDeToken::NUMERO_REAL, lexema));
}

void Lexer::q17() {
    i++;
    lexema = "";
    while (i < codigo.size() && codigo[i] != '"') lexema += codigo[i++];
    if (i < codigo.size() && codigo[i] == '"') {
        i++;
        tokens.push_back(Token(TipoDeToken::STRING, lexema));
    } else tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lexema));
}

void Lexer::q18() {
    lexema = std::string(1, codigo[i++]);
    if (i < codigo.size() && codigo[i] == '+') {
        lexema += codigo[i++];
        if (i < codigo.size() && codigo[i] == '+') {
            std::string inval = lexema;
            while (i < codigo.size() && codigo[i] == '+') inval += codigo[i++];
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, inval));
        } else tokens.push_back(Token(TipoDeToken::INCREMENTO, lexema));
    } else tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, lexema));
}

void Lexer::q19() {
    lexema = std::string(1, codigo[i++]);
    if (i < codigo.size() && codigo[i] == '-') {
        lexema += codigo[i++];
        if (i < codigo.size() && codigo[i] == '-') {
            std::string inval = lexema;
            while (i < codigo.size() && codigo[i] == '-') inval += codigo[i++];
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, inval));
        } else tokens.push_back(Token(TipoDeToken::DECREMENTO, lexema));
    } else tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, lexema));
}

void Lexer::q20() {
    lexema = std::string(1, codigo[i++]);
    tokens.push_back(Token(TipoDeToken::PONTO, lexema));

    if (i < codigo.size() && codigo[i] == '.') {
        std::string invalido = "";
        while (i < codigo.size() && codigo[i] == '.') invalido += codigo[i++];
        tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, invalido));
    }
}

void Lexer::q21() {
    lexema = std::string(1, codigo[i++]);
    tokens.push_back(Token(TipoDeToken::DOIS_PONTOS, lexema));

    if (i < codigo.size() && codigo[i] == ':') {
        std::string invalido = "";
        while (i < codigo.size() && codigo[i] == ':') invalido += codigo[i++];
        tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, invalido));
    }
}

void Lexer::q22() {
    lexema = std::string(1, codigo[i++]);
    tokens.push_back(Token(TipoDeToken::INTERROGACAO, lexema));

    if (i < codigo.size() && codigo[i] == '?') {
        std::string invalido = "";
        while (i < codigo.size() && codigo[i] == '?') invalido += codigo[i++];
        tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, invalido));
    }
}

void Lexer::q23() {
    tokens.push_back(Token(TipoDeToken::ABRE_ASPAS, std::string(1, codigo[i++])));
}

void Lexer::q24() {
    tokens.push_back(Token(TipoDeToken::FECHA_ASPAS, std::string(1, codigo[i++])));
}

bool Lexer::isEspaco(char c) { return c==' '||c=='\t'||c=='\r'||c=='\n'; }
bool Lexer::isDigito(char c) { return c>='0' && c<='9'; }
bool Lexer::isLetra(char c) { return std::isalpha(static_cast<unsigned char>(c)); }
bool Lexer::isOperadorAritmetico(char c) { return c=='*'||c=='/'||c=='%'; }

