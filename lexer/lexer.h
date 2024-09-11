// lexer.h
#ifndef LEXER_H
#define LEXER_H

#include <unordered_map>
#include <vector>
#include <string>

// Definindo os tipos de tokens
enum TokenType {
    TOKEN_NUMBER, // número
    TOKEN_EQ,     // ==
    TOKEN_NEQ,    // !=
    TOKEN_GT,     // >
    TOKEN_LT,     // <
    TOKEN_GTE,    // >=
    TOKEN_LTE,    // <=
    TOKEN_LPAREN, // (
    TOKEN_RPAREN, // )
    TOKEN_TRUE,   // true
    TOKEN_FALSE,  // false
    TOKEN_UNKNOWN, // Desconhecido
};

// Estrutura para representar um Token
struct Token {
    TokenType type;
    std::string value;
};

// Classe para representar o AFD (Autômato Finito Determinístico)
class DFA {
public:
    DFA(); // Construtor

    // Função que processa a string de entrada e retorna os tokens
    std::vector<Token> analyze(const std::string& input);

private:
    std::unordered_map<int, std::unordered_map<char, int>> transitions;
    std::unordered_map<int, TokenType> finalStates;

    void buildDFA(); // Função para construir o AFD

    // Função para obter o próximo token a partir da posição atual
    Token getToken(const std::string& input, size_t start);
};

#endif // LEXER_H
