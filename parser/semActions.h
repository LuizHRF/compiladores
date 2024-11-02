
#ifndef SEMANTIC_ACTIONS
#define SEMANTIC_ACTIONS

#include <unordered_map>
#include <vector>
#include <string>
#include <map>
#include <any>

#include "parser.h"
#include "../utils/base.h"
#include "../utils/tinyxml2.h"

enum nonTerminalType{
    EX_NUM,
    EX_BOOL,
    EX_ATRIBUICAO,
    EX_NADA,
    EX_ERROR,
};

struct nonTerminal{
    int index;
    std::string name;
    nonTerminalType type;
};

struct Variable{
    Token token;
    nonTerminalType firstUseType;
};

class SemanticActions {
public:
    SemanticActions(std::vector<Symbol> symbols, std::vector<Production> productions); // Construtor

    nonTerminal executeAction(int production, std::vector<std::any> reduced);

private:

    std::vector<Symbol> symbols;

    std::vector<Production> productions;
    
    std::vector<Variable> variables;

    std::string getSymbolName(int index);

    Variable* verifyVar(std::string varName);

    void addVariable(Token token, nonTerminalType type);

};

#endif