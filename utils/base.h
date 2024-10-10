#ifndef BASE_H
#define BASE_H

#include <vector>
#include <string>

// Enumeração para representar os tipos de Token
enum TokenType {
    TOKEN_VAR, // variável  "_[a-z][A-Z][0-9]"
    TOKEN_NUMBER, // número  "[0-9]+"
    TOKEN_ATRIB,  // :=
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
    TOKEN_IF,     // if
    TOKEN_DO,     // do
    TOKEN_ELSE,   // else
    TOKEN_UNKNOWN, // Desconhecido
    END_OF_SENTENCE // Final de sentença

};

// Estrutura para representar um Token
struct Token {
    TokenType type;
    std::string value;
    int line;
    int position;
    std::string tokenName;
};


// Função para ler a fita de tokens
std::vector<Token> lerFita(const char* filename);

// Função para escrever a fita de tokens
int escreverFita(std::vector<Token> tokens, const char* filename);

// Função para obter o nome do token
std::string getName(TokenType type);

#endif