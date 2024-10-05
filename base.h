#ifndef BASE_H
#define BASE_H

enum TokenType {
    TOKEN_VAR, // variável  "_[a-z][A-Z][0-9]"
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

#endif // ENUM_H