#include <vector>
#include <map>
#include <iostream>
#include "parser.h"

SLR_Table::SLR_Table() {
    initializeParserTable();
}


void SLR_Table::initializeParserTable() {

    Action empilha = { AC_EMPILHA, 1};
    actionTable[0][TOKEN_IF] = empilha;

    Action aceita = { AC_ACEITA, 0};
    actionTable[1][END_OF_SENTENCE] = aceita;

}

Action SLR_Table::getAction(int state, TokenType token) {
    //std::cout << "Getting Action" << std::endl;
    if (SLR_Table::actionTable[state].find(token) != actionTable[state].end()) {
        return actionTable[state][token];
    }
    return { AC_ERRO, -1 };
}

int SLR_Table::getGoto(int state, nonTerminal nonTerminal) {
    //std::cout << "Going to" << std::endl;
    if (gotoTable[state].find(nonTerminal) != gotoTable[state].end()) {
        return gotoTable[state][nonTerminal];
    }
    return -1;
}


int SLR_Table::parse(std::vector<Token> tokens) {
    
    //std::cout << "Parsing" << std::endl;
    std::vector<int> stateStack = {0};

    for (const Token &t : tokens ){
        int currentState = stateStack.back();

        Action action = getAction(currentState, t.type);
        
        switch (action.type) {
            case AC_EMPILHA:
                std::cout << "Empilha: " << t.type << " e " << action.value << std::endl;
                stateStack.push_back(t.type);
                stateStack.push_back(action.value);
                break;
            case AC_REDUZ:
                // Desempilhar e aplicar a redução correspondente
                break;
            case AC_ACEITA:
                std::cout << "Input accepted" << std::endl;
                return 0;
            case AC_ERRO:
                std::cout << "Syntax error" << std::endl;
                return 0;
        }
    }

    return 1;
}
