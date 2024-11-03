#include <vector>
#include <map>
#include <iostream>
#include <any>
#include "parser.h"
#include "semActions.h"

SemanticActions::SemanticActions(std::vector<Symbol> symbols, std::vector<Production> productions) {
    this->productions = productions;
    this->symbols = symbols;
}

std::string SemanticActions::getSymbolName(int index){
    for(Symbol s : symbols){
        if(s.index == index){
            return s.name;
        }
    }
    return "erro";
}

nonTerminal SemanticActions::executeAction(int production, std::vector<std::any> reduced){

    nonTerminal nt;
    nt.index = productions[production].nonTerminalIndex;
    nt.name = "<" + getSymbolName(productions[production].nonTerminalIndex) + ">";

    Token t;
    std::vector<nonTerminal> reducedNT;
    Variable* auxVar;

    switch(production){

        case 3: //<Stmt> ::= TOKEN_VAR TOKEN_ATRIB <Exp>

            t = std::any_cast<Token>(reduced[2]);
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[0]));
            auxVar = verifyVar(t.value);


            if(auxVar == NULL){

                addVariable(t, reducedNT.back().type);
               
            } else {

                if(auxVar->firstUseType != reducedNT.back().type){
                    std::cout << "Erro: Atribuição de tipos diferentes" << std::endl;
                    nt.type = EX_ERROR;
                    return nt;
                }

            }

            nt.type = EX_ATRIBUICAO;
            return nt; 

        case 6: // <Exp> ::= <Exp> TOKEN_EQ <Exp>
            
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[0]));
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[2]));

            if (reducedNT[0].type != reducedNT[1].type){
                std::cout << "Erro: Operação de comparação com tipos errados" << std::endl;
                nt.type = EX_ERROR;
                return nt;
            }

            nt.type = EX_BOOL;
            return nt;

        case 7: // <Exp> ::= <Exp> TOKEN_NEQ <Exp>

            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[0]));
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[2]));

            if (reducedNT[0].type != reducedNT[1].type){
                std::cout << "Erro: Operação de comparação com tipos errados" << std::endl;
                nt.type = EX_ERROR;
                return nt;
            }

            nt.type = EX_BOOL;
            return nt;

        case 8: // <Exp> ::= <Exp> TOKEN_GT <Exp>
            
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[0]));
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[2]));

            if (reducedNT[0].type != reducedNT[1].type){
                std::cout << "Erro: Operação de comparação com tipos errados" << std::endl;
                nt.type = EX_ERROR;
                return nt;
            }

            nt.type = EX_BOOL;
            return nt;

        case 9: // <Exp> ::= <Exp> TOKEN_LT <Exp>
            
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[0]));
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[2]));

            if (reducedNT[0].type != reducedNT[1].type){
                std::cout << "Erro: Operação de comparação com tipos errados" << std::endl;
                nt.type = EX_ERROR;
                return nt;
            }

            nt.type = EX_BOOL;
            return nt; 

        case 10: // <Exp> ::= <Exp> TOKEN_GTE <Exp>
            

            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[0]));
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[2]));

            if (reducedNT[0].type != reducedNT[1].type){
                std::cout << "Erro: Operação de comparação com tipos errados" << std::endl;
                nt.type = EX_ERROR;
                return nt;
            }

            nt.type = EX_BOOL;
            return nt; 

        case 11: // <Exp> ::= <Exp> TOKEN_LTE <Exp> 
            
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[0]));
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[2]));

            if (reducedNT[0].type != reducedNT[1].type){
                std::cout << "Erro: Operação de comparação com tipos errados" << std::endl;
                nt.type = EX_ERROR;
                return nt;
            }

            nt.type = EX_BOOL;
            return nt;
            
        case 12: // <Exp> ::= TOKEN_LPAREN <Exp> TOKEN_RPAREN 
            
            reducedNT.push_back(std::any_cast<nonTerminal>(reduced[1]));

            nt.type = reducedNT.back().type;
            return nt; 

        case 13: // <Exp> ::= TOKEN_TRUE
            
            nt.type = EX_BOOL;
            return nt; 
                  
        
        case 14: // <Exp> ::= TOKEN_FALSE
            
            nt.type = EX_BOOL;
            return nt;

        case 15: // <Exp> ::= TOKEN_NUMBER
            
            nt.type = EX_NUM;

            return nt;

        case 16: // <Exp> ::= TOKEN_VAR

            t = std::any_cast<Token>(reduced[0]);
            auxVar = verifyVar(t.value);

            if(auxVar == NULL){
                std::cout << "Erro: Variável não declarada" << std::endl;
                nt.type = EX_ERROR;
                return nt;
            }

            nt.type = auxVar->firstUseType;
            return nt;

        default:
            nt.type = EX_NADA;
            return nt;
        
    } 

}


Variable* SemanticActions::verifyVar(std::string varName){
    for(int i=0; i<variables.size(); i++){
        if(variables[i].token.value == varName){
            return &variables[i];
        }
    }
    return NULL;
}

void SemanticActions::addVariable(Token token, nonTerminalType type){
    Variable v;
    v.token = token;
    v.firstUseType = type;
    variables.push_back(v);
}
