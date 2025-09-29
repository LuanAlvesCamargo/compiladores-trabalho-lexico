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
        else if (c == '+') { q18(); continue; } // incremento ou '+'
        else if (c == '-') { q19(); continue; } // decremento ou '-'
        else if (isOperadorAritmetico(c)) { q2(); continue; } // *, /, %
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
        else if (c == '\'') {
            std::string lex(1, c);
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lex));
            i++;
            continue;
        }
        else {
            std::string lex(1, c);
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lex));
            i++;
        }
    }
    return tokens;
}

// q0: espaços
void Lexer::q0() {
    char c = codigo[i];
    if (isspace(static_cast<unsigned char>(c))) { i++; return; }
    else if (isalpha(c) || c == '_') { q1(); return; }
    else if (isdigit(c)) { q3(); return; }
    else if (c == '=') { q4(); return; }
    else if (c == '<' || c == '>' || c == '!') { q7(); return; }
    else if (c == '&' || c == '|') { q8(); return; }
    else if (c == '+') { q18(); return; }
    else if (c == '-') { q19(); return; }
    else if (isOperadorAritmetico(c)) { q2(); return; }
    else {
        lexema = std::string(1, c);
        tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lexema));
        i++;
    }
}

// q1: número inteiro ou real
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

// q2: operadores aritméticos simples (* / %)
void Lexer::q2() {
    lexema = std::string(1, codigo[i++]);
    tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, lexema));
}

// q3: identificador / palavra reservada
void Lexer::q3() {
    lexema = "";
    while (i < codigo.size() && (isLetra(codigo[i]) || isDigito(codigo[i]) || codigo[i] == '_')) lexema += codigo[i++];
    if (lexema == "int" || lexema == "float" || lexema == "double" ||
        lexema == "char" || lexema == "bool" || lexema == "string" ||
        lexema == "main" || lexema == "if" || lexema == "else" ||
        lexema == "while" || lexema == "for" || lexema == "do") {
        tokens.push_back(Token(TipoDeToken::PALAVRA_RESERVADA, lexema));
    } else tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lexema));
}

// q4: '=' ou '=='
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

// q5: ponto e vírgula
void Lexer::q5() { tokens.push_back(Token(TipoDeToken::PONTO_E_VIRGULA, std::string(1, codigo[i++]))); }

// // q7: operadores relacionais > >= < <= != ou '!' lógico
// void Lexer::q7() {
//     lexema = std::string(1, codigo[i++]);
//     if ((lexema == ">" || lexema == "<") && i < codigo.size() && codigo[i] == '=') {
//         lexema += codigo[i++];
//         tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
//         if (i < codigo.size() && codigo[i] == '=') {
//             std::string inval = "";
//             while (i < codigo.size() && codigo[i] == '=') inval += codigo[i++];
//             tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, inval));
//         }
//         return;
//     }
//     if (lexema == "!") {
//         if (i < codigo.size() && codigo[i] == '=') {
//             lexema += codigo[i++];
//             tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
//             if (i < codigo.size() && codigo[i] == '=') {
//                 std::string inval = "";
//                 while (i < codigo.size() && codigo[i] == '=') inval += codigo[i++];
//                 tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, inval));
//             }
//         } else tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema));
//         return;
//     }
//     tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
// }

// // q8: operadores lógicos && ||
// void Lexer::q8() {
//     lexema = std::string(1, codigo[i++]);
//     if (i < codigo.size() && codigo[i] == lexema[0]) {
//         lexema += codigo[i++];
//         tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema));
//     } else tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lexema));
// }


// q7: operadores relacionais > >= < <= ! != ou inválidos
void Lexer::q7() {
    lexema = std::string(1, codigo[i++]);

    if (lexema == ">" || lexema == "<") {
        if (i < codigo.size() && codigo[i] == '=') { // >= ou <=
            lexema += codigo[i++];
            tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
        } else { // só > ou <
            tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
        }
        // checa excesso de > ou <
        std::string inval = "";
        while (i < codigo.size() && codigo[i] == lexema[0]) {
            inval += codigo[i++];
        }
        if (!inval.empty()) tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, inval));
        return;
    }

    if (lexema == "!") {
        if (i < codigo.size() && codigo[i] == '=') { // !=
            lexema += codigo[i++];
            tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
        } else {
            tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema));
        }
        // checa excesso de !
        std::string inval = "";
        while (i < codigo.size() && codigo[i] == '!') {
            inval += codigo[i++];
        }
        if (!inval.empty()) tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, inval));
        return;
    }
}

// q8: operadores lógicos && ||
void Lexer::q8() {
    lexema = std::string(1, codigo[i++]);
    if (i < codigo.size() && codigo[i] == lexema[0]) { // par correto
        lexema += codigo[i++];
        tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema));
        // checa excesso de & ou |
        std::string inval = "";
        while (i < codigo.size() && codigo[i] == lexema[0]) {
            inval += codigo[i++];
        }
        if (!inval.empty()) tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, inval));
    } else {
        // & ou | sozinho → inválido
        tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lexema));
    }
}


// q9..q15
void Lexer::q9()  { tokens.push_back(Token(TipoDeToken::ABRE_PARENTESES, std::string(1, codigo[i++]))); }
void Lexer::q10() { tokens.push_back(Token(TipoDeToken::FECHA_PARENTESES, std::string(1, codigo[i++]))); }
void Lexer::q11() { tokens.push_back(Token(TipoDeToken::ABRE_CHAVES, std::string(1, codigo[i++]))); }
void Lexer::q12() { tokens.push_back(Token(TipoDeToken::FECHA_CHAVES, std::string(1, codigo[i++]))); }
void Lexer::q13() { tokens.push_back(Token(TipoDeToken::ABRE_COLCHETES, std::string(1, codigo[i++]))); }
void Lexer::q14() { tokens.push_back(Token(TipoDeToken::FECHA_COLCHETES, std::string(1, codigo[i++]))); }
void Lexer::q15() { tokens.push_back(Token(TipoDeToken::VIRGULA, std::string(1, codigo[i++]))); }

// q16: número real começando com ponto
void Lexer::q16() {
    lexema = "";
    if (i < codigo.size() && codigo[i] == '.') {
        lexema += codigo[i++];
        while (i < codigo.size() && isDigito(codigo[i])) lexema += codigo[i++];
        tokens.push_back(Token(TipoDeToken::NUMERO_REAL, lexema));
    } else i++;
}

// q17: string
void Lexer::q17() {
    i++;
    lexema = "";
    while (i < codigo.size() && codigo[i] != '\"') lexema += codigo[i++];
    if (i < codigo.size() && codigo[i] == '\"') {
        i++;
        tokens.push_back(Token(TipoDeToken::STRING, lexema));
    } else tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lexema));
}

// q18: incremento ou '+'
void Lexer::q18() {
    lexema = std::string(1, codigo[i++]);
    if (i < codigo.size() && codigo[i] == '+') {
        lexema += codigo[i++];
        if (i < codigo.size() && codigo[i] == '+') {
            std::string invalido = lexema;
            while (i < codigo.size() && codigo[i] == '+') invalido += codigo[i++];
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, invalido));
        } else tokens.push_back(Token(TipoDeToken::INCREMENTO, lexema));
    } else tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, lexema));
}

// q19: decremento ou '-'
void Lexer::q19() {
    lexema = std::string(1, codigo[i++]);
    if (i < codigo.size() && codigo[i] == '-') {
        lexema += codigo[i++];
        if (i < codigo.size() && codigo[i] == '-') {
            std::string invalido = lexema;
            while (i < codigo.size() && codigo[i] == '-') invalido += codigo[i++];
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, invalido));
        } else tokens.push_back(Token(TipoDeToken::DECREMENTO, lexema));
    } else tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, lexema));
}

// q20..q24
void Lexer::q20() { tokens.push_back(Token(TipoDeToken::PONTO, std::string(1, codigo[i++]))); }
void Lexer::q21() { tokens.push_back(Token(TipoDeToken::DOIS_PONTOS, std::string(1, codigo[i++]))); }
void Lexer::q22() { tokens.push_back(Token(TipoDeToken::INTERROGACAO, std::string(1, codigo[i++]))); }
void Lexer::q23() { tokens.push_back(Token(TipoDeToken::ABRE_ASPAS, std::string(1, codigo[i++]))); }
void Lexer::q24() { tokens.push_back(Token(TipoDeToken::FECHA_ASPAS, std::string(1, codigo[i++]))); }

// helpers
bool Lexer::isEspaco(char c) { return c==' '||c=='\t'||c=='\r'||c=='\n'; }
bool Lexer::isDigito(char c) { return c>='0' && c<='9'; }
bool Lexer::isLetra(char c) { return std::isalpha(static_cast<unsigned char>(c)); }
bool Lexer::isOperadorAritmetico(char c) { return c=='*'||c=='/'||c=='%'; }

