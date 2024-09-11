// main.cpp
#include "lexer.h"
#include <iostream>


// FALTA ADICIONAR O FINAL DE SENTENÇA
// FALTA MODIFICIAR A MANEIRA COMO ELE INTERPRETA VALORES DESONHECIDOS

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <entrada>" << std::endl;
        return 1;
    }

    // Obter a string de entrada do primeiro argumento
    std::string input = argv[1];

    DFA lexer;

    // String de entrada para análise
    // std::string input = "( 012 == != > < >= <= )";

    // Analisar a string de entrada e obter tokens
    std::vector<Token> tokens = lexer.analyze(input);

    // Imprimir tokens reconhecidos
    for (const auto& token : tokens) {
        std::string tokenType;
        switch (token.type) {
            case TOKEN_EQ: tokenType = "TOKEN_EQ"; break;
            case TOKEN_NEQ: tokenType = "TOKEN_NEQ"; break;
            case TOKEN_LT: tokenType = "TOKEN_LT"; break;
            case TOKEN_GT: tokenType = "TOKEN_GT"; break;
            case TOKEN_LTE: tokenType = "TOKEN_LTE"; break;
            case TOKEN_GTE: tokenType = "TOKEN_GTE"; break;
            case TOKEN_NUMBER: tokenType = "NUMBER"; break;
            case TOKEN_LPAREN: tokenType = "TOKEN_LPAREN"; break;
            case TOKEN_RPAREN: tokenType = "TOKEN_RPAREN"; break;
            default: tokenType = "UNKNOWN"; break;
        }
        std::cout << "Token: " << token.value << " (Tipo: " << tokenType << ")" << std::endl;
    }

    return 0;
}
