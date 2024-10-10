#include <vector>
#include <map>
#include <iostream>
#include "parser.h"

SLR_Table::SLR_Table() {
    initializeParserTable("utils/parserv1.xml");

}

using namespace tinyxml2;

int SLR_Table::initializeParserTable(const char* filename) {

    //std::cout << "Initializing parser table" << std::endl;
    
    XMLDocument doc;
    XMLError result = doc.LoadFile(filename);
    if (result != XML_SUCCESS) {
        std::cerr << "Erro ao carregar o arquivo XML: " << result << std::endl;
        return 1;
    }

    XMLElement* root = doc.RootElement(); //root = <Tables>
    if (root == nullptr) {
        std::cerr << "Erro: elemento raiz não encontrado." << std::endl;
        return 1;
    }

    int symbolcount = std::stoi(root->FirstChildElement("m_Symbol")->Attribute("Count"));
    XMLElement* symbol = root->FirstChildElement("m_Symbol")->FirstChildElement("Symbol");
    for(int i=0; i<symbolcount; i++) {
        Symbol s;
        s.index = std::stoi(symbol->Attribute("Index"));
        s.name = symbol->Attribute("Name");
        s.type = std::stoi(symbol->Attribute("Type"));
        symbols.push_back(s);
        symbol = symbol->NextSiblingElement();
    }

    int count = std::stoi(root->FirstChildElement("m_Production")->Attribute("Count"));
    XMLElement* prod = root->FirstChildElement("m_Production")->FirstChildElement("Production");
    for(int i=0; i<count; i++) {
        Production p;
        p.index = std::stoi(prod->Attribute("Index"));
        p.nonTerminalIndex = std::stoi(prod->Attribute("NonTerminalIndex"));
        p.symbolCount = std::stoi(prod->Attribute("SymbolCount"));
        productions.push_back(p);
        prod = prod->NextSiblingElement();
    }

    count = std::stoi(root->FirstChildElement("LALRTable")->Attribute("Count"));


    XMLElement* state = root->FirstChildElement("LALRTable")->FirstChildElement("LALRState");
        
    for(int j=0; j<count; j++) {
        State s;
        s.index = std::stoi(state->Attribute("Index"));
        s.actionCount = std::stoi(state->Attribute("ActionCount"));

        Operation invalid = {-1, -1, -1};
        s.operations.resize(symbolcount, invalid);
        //std::cout<< "State: " << s.index << std::endl;

        XMLElement* oper = state->FirstChildElement("LALRAction");
        for(int i=0; i<s.actionCount; i++) {

            Operation op;
            op.symbolIndex = std::stoi(oper->Attribute("SymbolIndex"));
            op.action = std::stoi(oper->Attribute("Action"));
            op.value = std::stoi(oper->Attribute("Value"));
            s.operations[op.symbolIndex] = op;

            oper = oper->NextSiblingElement();
            //std::cout << "Operation: " << op.symbolIndex << " / " << op.action << std::endl;

        }

        LALRTable.push_back(s);
        state = state->NextSiblingElement();
    }

    return 0;

}

void SLR_Table::displayTable() {
    std::cout << "Displaying table:" << std::endl;

    std::cout << "Symbols:" << std::endl;
    for (Symbol &s : symbols) {
        std::cout <<  s.index << " / " << s.name << " / " << s.type << std::endl;
    }

    std::cout << "Productions:" << std::endl;
    for (Production &p : productions) {
        std::cout << p.index << " / " << p.nonTerminalIndex << " / " << p.symbolCount << std::endl;
    }

    std::cout << "States:" << std::endl;
    for (State &s : LALRTable) {
        std::cout << "State " << s.index << " has operations: "<< std::endl;
        for(int i=0; i< s.actionCount; i++) {
            Operation op = s.operations[i];
            std::cout << "Operation: " << op.symbolIndex << " / " << op.action << " / " << op.value << std::endl;
        }
    }

    std::cout << "States number: " << LALRTable.size() << std::endl;
}

int SLR_Table::getSymbolIndex(std::string symbolName) {
    for (Symbol &s : symbols) {
        if (s.name == symbolName) {
            return s.index;
        }
    }
    return -1;
}
// Action SLR_Table::getAction(int state, TokenType token) {
//     //std::cout << "Getting Action" << std::endl;
//     if (SLR_Table::actionTable[state].find(token) != actionTable[state].end()) {
//         return actionTable[state][token];
//     }
//     return { AC_ERRO, -1 };
// }

// int SLR_Table::getGoto(int state, nonTerminal nonTerminal) {
//     //std::cout << "Going to" << std::endl;
//     if (gotoTable[state].find(nonTerminal) != gotoTable[state].end()) {
//         return gotoTable[state][nonTerminal];
//     }
//     return -1;
// }


int SLR_Table::parse(std::vector<Token> tokens) {
    
    //std::cout << "Parsing" << std::endl;
    std::vector<int> stateStack = {0};
    int meanState;

    for (const Token &t : tokens ){

        int currentState = stateStack.back();
        
        int currentToken = getSymbolIndex(getName(t.type));
        std::cout << "Current token: " << getName(t.type) << std::endl;

        Operation op = LALRTable[currentState].operations[currentToken];


        std::cout << "[" << currentState << ", " << currentToken << "] -> " << op.action << " / " << op.value << std::endl;
        
        switch(op.action){

            case OP_SHIFT:
                stateStack.push_back(currentToken);
                stateStack.push_back(op.value);
                break;
            
            case OP_REDUCE:
                for(int i=0; i<productions[op.value].symbolCount; i++) {
                    stateStack.pop_back();
                    stateStack.pop_back();
                }
                meanState = stateStack.back();
                stateStack.push_back(productions[op.value].nonTerminalIndex); 
                stateStack.push_back(LALRTable[meanState].operations[productions[op.value].nonTerminalIndex].value); // Salto
                std::cout << "Remove " << productions[op.value].index << " e [" << meanState << ", " << productions[op.value].nonTerminalIndex << "] -> " << stateStack.back() << std::endl;
                break;

            default:
                std::cerr << "Erro: Ação não reconhecida" << std::endl;
                return 1;
        }
    }

    return 1;
}
