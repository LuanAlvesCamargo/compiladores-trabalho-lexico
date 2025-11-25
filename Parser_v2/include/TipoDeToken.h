#ifndef TIPODETOKEN_H
#define TIPODETOKEN_H

enum class TipoDeToken
{
    ESPACO,                 // q0 (usado internamente)
    NUMERO_INTEIRO,         // q1
    OPERADOR_ARITMETICO,    // q2 (+ - * /)
    IDENTIFICADOR,          // q3
    OPERADOR_ATRIBUICAO,    // q4 (=)
    PONTO_E_VIRGULA,        // q5 (;)
    PALAVRA_RESERVADA,      // q6 (if, else, while, int, return, etc.)
    OPERADOR_RELACIONAL,    // q7 (==, !=, <, >, <=, >=)
    OPERADOR_LOGICO,        // q8 (&&, ||, !)
    ABRE_PAREN,             // q9  '('
    FECHA_PAREN,            // q10 ')'
    ABRE_CHAVE,             // q12 '{'
    FECHA_CHAVE,            // q11 '}'
    ABRE_COLCHETE,          // q13 '['
    FECHA_COLCHETE,         // q14 ']'
    INCREMENTO,             // q15 '++'
    DECREMENTO,             // q16 '--'
    PONTO,                  // q17 '.'
    DOIS_PONTOS,            // q18 ':'
    INTERROGACAO,           // q19 '?'
    ABRE_ASPAS,             // q20 '"'
    FECHA_ASPAS,            // q21 '"'
    INVALIDO
};

#endif // TIPODETOKEN_H
