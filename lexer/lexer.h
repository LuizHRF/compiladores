// lexer.h
#ifndef LEXER_H
#define LEXER_H

#include <unordered_map>
#include <vector>
#include <string>
#include "../base.h"

class DFA {
public:
    DFA(); // Construtor

    // Função que processa a string de entrada e retorna os tokens
    std::vector<Token> analyze(const std::string& input);

private:

    std::unordered_map<int, std::unordered_map<char, int>> transitions;
    std::unordered_map<int, TokenType> finalStates;

    void buildDFA();

    Token getToken(const std::string& input, size_t start);
};


#endif // LEXER_H
