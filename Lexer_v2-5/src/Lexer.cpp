#include "Lexer.h"
#include <cctype>
#include <map>

// Implementação do construtor.
Lexer::Lexer(std::string codigo) {
    this->codigo = codigo;
    i = 0;
    estado_atual = 0;
}

// Inicializa o estado do analisador para começar a análise.
void Lexer::inicializar() {
    i = 0;
    estado_atual = 0;
    tokens.clear();
    lexema = "";
}

// Analisa o código-fonte e retorna uma lista de tokens.
std::vector<Token> Lexer::Analisar() {
    inicializar();
    while (i < codigo.size()) {
        char c = codigo[i];

        if (isEspaco(c)) {
            q0();
            continue;
        } else if (isDigito(c)) {
            q1();
            continue;
        } else if (isLetra(c)) {
            q3();
            continue;
        } else if (c == '=') {
            q4();
            continue;
        } else if (c == ';') {
            q5();
            continue;
        } else if (c == '>' || c == '<') {
            q7();
            continue;
        } else if (c == '&' || c == '|') {
            q8();
            continue;
        } else if (c == '(') {
            tokens.push_back(Token(TipoDeToken::ABRE_PARENTESES, std::string(1, codigo[i++])));
            continue;
        } else if (c == ')') {
            tokens.push_back(Token(TipoDeToken::FECHA_PARENTESES, std::string(1, codigo[i++])));
            continue;
        } else if (c == '{') {
            tokens.push_back(Token(TipoDeToken::ABRE_CHAVES, std::string(1, codigo[i++])));
            continue;
        } else if (c == '}') {
            tokens.push_back(Token(TipoDeToken::FECHA_CHAVES, std::string(1, codigo[i++])));
            continue;
        } else if (c == '[') {
            tokens.push_back(Token(TipoDeToken::ABRE_COLCHETES, std::string(1, codigo[i++])));
            continue;
        } else if (c == ']') {
            tokens.push_back(Token(TipoDeToken::FECHA_COLCHETES, std::string(1, codigo[i++])));
            continue;
        } else if (c == ',') {
            tokens.push_back(Token(TipoDeToken::VIRGULA, std::string(1, codigo[i++])));
            continue;
        } else if (c == '"') {
            q17();
            continue;
        } else if (c == '.') {
            q20();
            continue;
        } else if (c == ':') {
            tokens.push_back(Token(TipoDeToken::DOIS_PONTOS, std::string(1, codigo[i++])));
            continue;
        } else if (c == '?') {
            tokens.push_back(Token(TipoDeToken::INTERROGACAO, std::string(1, codigo[i++])));
            continue;
        } else if (c == '+' || c == '-') {
            q2();
            continue;
        } else if (c == '*' || c == '/' || c == '%') {
            q_aritmetico_simples();
            continue;
        } else if (c == '!') {
            q_exclamacao();
            continue;
        } else {
            // Se nenhum dos estados anteriores corresponder, é um token inválido.
            std::string invalid_lexema(1, c);
            tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, invalid_lexema));
            i++;
        }
    }
    return tokens;
}

// q0: Espaços, tabulações e quebras de linha
void Lexer::q0() {
    while (i < codigo.size() && isEspaco(codigo[i])) {
        i++;
    }
}

// q1: Número inteiro
void Lexer::q1() {
    lexema = "";
    while (i < codigo.size() && isDigito(codigo[i])) {
        lexema += codigo[i];
        i++;
    }
    if (i < codigo.size() && codigo[i] == '.') {
        q16();
    } else {
        tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, lexema));
    }
}

// q2: Operadores aritméticos (+, -, ++, --)
void Lexer::q2() {
    char c = codigo[i];
    lexema = "";
    lexema += c;
    i++;
    if (i < codigo.size() && codigo[i] == c) {
        if (c == '+') {
            lexema += c;
            i++;
            tokens.push_back(Token(TipoDeToken::INCREMENTO, lexema));
        } else if (c == '-') {
            lexema += c;
            i++;
            tokens.push_back(Token(TipoDeToken::DECREMENTO, lexema));
        }
    } else {
        tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, lexema));
    }
}

// q3: Identificadores e Palavras Reservadas
void Lexer::q3() {
    lexema = "";
    while (i < codigo.size() && (isLetra(codigo[i]) || isDigito(codigo[i]) || codigo[i] == '_')) {
        lexema += codigo[i];
        i++;
    }
    static const std::map<std::string, TipoDeToken> palavrasReservadas = {
        {"int", TipoDeToken::PALAVRA_RESERVADA}, {"float", TipoDeToken::PALAVRA_RESERVADA},
        {"double", TipoDeToken::PALAVRA_RESERVADA}, {"char", TipoDeToken::PALAVRA_RESERVADA},
        {"bool", TipoDeToken::PALAVRA_RESERVADA}, {"string", TipoDeToken::PALAVRA_RESERVADA},
        {"main", TipoDeToken::PALAVRA_RESERVADA}, {"if", TipoDeToken::PALAVRA_RESERVADA},
        {"else", TipoDeToken::PALAVRA_RESERVADA}, {"while", TipoDeToken::PALAVRA_RESERVADA},
        {"for", TipoDeToken::PALAVRA_RESERVADA}, {"do", TipoDeToken::PALAVRA_RESERVADA},
        {"true", TipoDeToken::PALAVRA_RESERVADA}, {"false", TipoDeToken::PALAVRA_RESERVADA},
        {"cout", TipoDeToken::PALAVRA_RESERVADA}
    };

    auto it = palavrasReservadas.find(lexema);
    if (it != palavrasReservadas.end()) {
        tokens.push_back(Token(it->second, lexema));
    } else {
        tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lexema));
    }
}

// q4: Operador de atribuição (=) e relacional (==)
void Lexer::q4() {
    lexema = "";
    lexema += codigo[i];
    i++;
    if (i < codigo.size() && codigo[i] == '=') {
        lexema += codigo[i];
        i++;
        tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
    } else {
        tokens.push_back(Token(TipoDeToken::OPERADOR_ATRIBUICAO, lexema));
    }
}

// q5: Ponto e vírgula (;)
void Lexer::q5() {
    tokens.push_back(Token(TipoDeToken::PONTO_E_VIRGULA, std::string(1, codigo[i++])));
}

// q7: Operadores relacionais (>, >=, <, <=)
void Lexer::q7() {
    lexema = "";
    lexema += codigo[i];
    i++;
    if (i < codigo.size() && codigo[i] == '=') {
        lexema += codigo[i];
        i++;
    }
    tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
}

// q8: Operadores lógicos (&&, ||)
void Lexer::q8() {
    lexema = "";
    char c = codigo[i];
    lexema += c;
    i++;
    if (i < codigo.size() && codigo[i] == c) {
        lexema += codigo[i];
        i++;
        tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema));
    } else {
        // Operador lógico incompleto, como um único '&' ou '|'
        tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, lexema));
    }
}

// q_exclamacao: Operador de negação (!) ou relacional (!=)
void Lexer::q_exclamacao() {
    lexema = "";
    lexema += codigo[i];
    i++;
    if (i < codigo.size() && codigo[i] == '=') {
        lexema += codigo[i];
        i++;
        tokens.push_back(Token(TipoDeToken::OPERADOR_RELACIONAL, lexema));
    } else {
        tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema));
    }
}

// q_aritmetico_simples: Operadores aritméticos de um caractere (*, /, %)
void Lexer::q_aritmetico_simples() {
    tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, std::string(1, codigo[i++])));
}

// q16: Número real
void Lexer::q16() {
    lexema += codigo[i]; // Adiciona o '.'
    i++;
    if (i >= codigo.size() || !isDigito(codigo[i])) {
        // Caso de um número terminando em ponto, como "123."
        tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, lexema.substr(0, lexema.size() - 1)));
        tokens.push_back(Token(TipoDeToken::PONTO, "."));
        return;
    }
    while (i < codigo.size() && isDigito(codigo[i])) {
        lexema += codigo[i];
        i++;
    }
    tokens.push_back(Token(TipoDeToken::NUMERO_REAL, lexema));
}

// q17: Strings
void Lexer::q17() {
    tokens.push_back(Token(TipoDeToken::ABRE_ASPAS, std::string(1, codigo[i++])));
    lexema = "";
    while (i < codigo.size() && codigo[i] != '"') {
        lexema += codigo[i];
        i++;
    }
    tokens.push_back(Token(TipoDeToken::STRING, lexema));
    if (i < codigo.size() && codigo[i] == '"') {
        tokens.push_back(Token(TipoDeToken::FECHA_ASPAS, std::string(1, codigo[i++])));
    } else {
        // String não fechada, lança exceção ou marca como inválida
        tokens.push_back(Token(TipoDeToken::TOKEN_INVALIDO, "String nao fechada"));
    }
}

// q20: Ponto (.)
void Lexer::q20() {
    if (i + 1 < codigo.size() && isDigito(codigo[i+1])) {
        // Número real que começa com ponto, como .5
        lexema = "";
        lexema += codigo[i];
        i++;
        q16(); // Transição para o estado de número real
    } else {
        tokens.push_back(Token(TipoDeToken::PONTO, std::string(1, codigo[i++])));
    }
}

// Métodos auxiliares para verificação de caracteres
bool Lexer::isEspaco(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }
bool Lexer::isDigito(char c) { return c >= '0' && c <= '9'; }
bool Lexer::isLetra(char c) { return std::isalpha(static_cast<unsigned char>(c)); }
