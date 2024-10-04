// main.cpp
#include "lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../enum.h"

//CORRIGIR STRING SENDO IDENTIFICADA PELA METADE

int main(int argc, char *argv[]) {

    // if (argc < 2) {
    //     std::cerr << "Uso: " << argv[0] << " <entrada>" << std::endl;
    //     return 1;
    // }

    // std::string input = argv[1];

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    DFA lexer;

    // std::string input = "( 012 == != > < >= <= )";

    // Analisar a string de entrada e obter tokens
    std::vector<Token> tokens = lexer.analyze(input);

    for (const Token t : tokens) {
        std::string tokenType;
        switch (t.type) {
            case TOKEN_ATRIB: tokenType = "TOKEN_ATRIB"; break;
            case TOKEN_EQ: tokenType = "TOKEN_EQ"; break;
            case TOKEN_NEQ: tokenType = "TOKEN_NEQ"; break;
            case TOKEN_LT: tokenType = "TOKEN_LT"; break;
            case TOKEN_GT: tokenType = "TOKEN_GT"; break;
            case TOKEN_LTE: tokenType = "TOKEN_LTE"; break;
            case TOKEN_GTE: tokenType = "TOKEN_GTE"; break;
            case TOKEN_VAR: tokenType = "TOKEN_VAR"; break;
            case TOKEN_LPAREN: tokenType = "TOKEN_LPAREN"; break;
            case TOKEN_RPAREN: tokenType = "TOKEN_RPAREN"; break;
            case TOKEN_TRUE: tokenType = "TOKEN_TRUE"; break;
            case TOKEN_FALSE: tokenType = "TOKEN_FALSE"; break;
            case TOKEN_IF: tokenType = "TOKEN_IF"; break;
            case TOKEN_ELSE : tokenType = "TOKEN_ELSE"; break;
            case TOKEN_DO: tokenType = "TOKEN_DO"; break;
            case TOKEN_UNKNOWN: tokenType = "TOKEN_UNKNOWN"; break;
            case END_OF_SENTENCE: tokenType = "END_OF_SENTENCE"; break;
            default: tokenType = "desconhecido"; break;
        }
        std::cout << tokenType << "\t\t" << "( '" <<t.value << "' \t\t | line: " << t.line << ")" << std::endl;
    }

    return 0;
}