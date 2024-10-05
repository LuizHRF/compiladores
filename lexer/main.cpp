// main.cpp
#include "lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string getName(TokenType t) {

    switch (t) {
            case TOKEN_ATRIB: return  "TOKEN_ATRIB"; break;
            case TOKEN_EQ: return  "TOKEN_EQ"; break;
            case TOKEN_NEQ: return  "TOKEN_NEQ"; break;
            case TOKEN_LT: return  "TOKEN_LT"; break;
            case TOKEN_GT: return  "TOKEN_GT"; break;
            case TOKEN_LTE: return  "TOKEN_LTE"; break;
            case TOKEN_GTE: return  "TOKEN_GTE"; break;
            case TOKEN_VAR: return  "TOKEN_VAR"; break;
            case TOKEN_LPAREN: return  "TOKEN_LPAREN"; break;
            case TOKEN_RPAREN: return  "TOKEN_RPAREN"; break;
            case TOKEN_TRUE: return  "TOKEN_TRUE"; break;
            case TOKEN_FALSE: return  "TOKEN_FALSE"; break;
            case TOKEN_IF: return  "TOKEN_IF"; break;
            case TOKEN_ELSE : return  "TOKEN_ELSE"; break;
            case TOKEN_DO: return  "TOKEN_DO"; break;
            case TOKEN_UNKNOWN: return  "TOKEN_UNKNOWN"; break;
            case END_OF_SENTENCE: return  "END_OF_SENTENCE"; break;
            default: return  "desconhecido"; break;
        }
}

int main(int argc, char *argv[]) {

    // if (argc < 2) {
    //     std::cerr << "Uso: " << argv[0] << " <entrada>" << std::endl;
    //     return 1;
    // }

    // std::string input = argv[1];

    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("fita.dat", std::ios::binary);
    if (!inputFile or !outputFile) {
        std::cerr << "Erro ao abrir o arquivo de entrada ou saída." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    DFA lexer;

    std::vector<Token> tokens = lexer.analyze(input);

    for (Token t : tokens) {
        t.tokenName = getName(t.type);
        
        outputFile.write(reinterpret_cast<const char*>(&t), sizeof(Token));
    }

    outputFile.close();

    return 0;
}