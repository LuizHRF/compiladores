// main.cpp
#include "lexer.h"
#include <iostream>

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
            case TOKEN_EQ: tokenType = "=="; break;
            case TOKEN_NEQ: tokenType = "!="; break;
            case TOKEN_LT: tokenType = "<"; break;
            case TOKEN_GT: tokenType = ">"; break;
            case TOKEN_LTE: tokenType = "<="; break;
            case TOKEN_GTE: tokenType = ">="; break;
            case TOKEN_NUMBER: tokenType = "NUMBER"; break;
            case TOKEN_LPAREN: tokenType = "("; break;
            case TOKEN_RPAREN: tokenType = ")"; break;
            default: tokenType = "UNKNOWN"; break;
        }
        std::cout << "Token: " << token.value << " (Tipo: " << tokenType << ")" << std::endl;
    }

    return 0;
}
