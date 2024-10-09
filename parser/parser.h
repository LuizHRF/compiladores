
#ifndef PARSER_H
#define PARSER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <map>
#include "../base.h"

enum ActionType {
    AC_EMPILHA,
    AC_REDUZ,
    AC_ACEITA,
    AC_ERRO,
};

enum nonTerminal {
    E,
    T,
    F,
};

struct Action {
    ActionType type;
    int value; 
};

class SLR_Table {
public:
    SLR_Table(); // Construtor

    int parse(std::vector<Token> tokens);

private:

    std::vector<int> production_lenght = {};

    void initializeParserTable();

    // [Estado, Terminal] -> Ação
    std::unordered_map<int, std::unordered_map<TokenType, Action>> actionTable;

    // [Estado, Não terminal] -> Estado
    std::unordered_map<int, std::unordered_map<nonTerminal, int>> gotoTable;

    // Função que processa a string de entrada e retorna os tokens
    Action getAction(int state, TokenType token);

    int getGoto(int state, nonTerminal nonTerminal);

};

#endif 
