#ifndef LEXEREXCEPTION_H
#define LEXEREXCEPTION_H

#include <exception>
#include <string>

class LexerException : public std::exception {
public:
    explicit LexerException(const std::string& mensagem)
        : mensagem(mensagem) {}

    const char* what() const noexcept override {
        return mensagem.c_str();
    }

private:
    std::string mensagem;
};

#endif // LEXEREXCEPTION_H
