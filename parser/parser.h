
#ifndef PARSER_H
#define PARSER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <map>
#include "../utils/base.h"
#include "../utils/tinyxml2.h"

const int OP_SHIFT = 1;
const int OP_REDUCE = 2;
const int OP_JUMP = 3;
const int OP_ACCEPT = 4;

struct Symbol{
    int index;
    std::string name;
    int type;
};

struct Production{
    int index;
    int nonTerminalIndex;
    int symbolCount;
};

struct Operation {
    int symbolIndex;
    int action;
    int value;
};

struct State {
    int index;
    int actionCount;
    std::vector<Operation> operations;
};

class SLR_Table {
public:
    SLR_Table(); // Construtor

    int parse(std::vector<Token> tokens);

    //"Mostra" a tabela SLR
    void displayTable();

private:


    // Símbolos terminais e não terminais
    std::vector<Symbol> symbols;

    // Produções da gramática
    std::vector<Production> productions;

    // Tabela de parsing SLR
    std::vector<State> LALRTable;

    //Lê a gramática de um arquivo .xml gerado pelo Gold Parser (GOLD Parser Builder 5.2.0.)
    int initializeParserTable(const char* filename);

    //Retorna o index de um token na tabela de símbolos (symbols)
    int getSymbolIndex(std::string token);
    
};

#endif 
