// lexer.cpp
#include "lexer.h"
#include <iostream>

// Construtor da classe DFA
DFA::DFA() {
    buildDFA();
}

// Função que constrói o AFD
void DFA::buildDFA() {
    // Estados do AFD
    transitions[0]['='] = 2;
    transitions[0]['!'] = 3;
    transitions[0]['>'] = 4;
    transitions[0]['<'] = 5;
    transitions[0]['('] = 10;
    transitions[0][')'] = 11;

    transitions[2]['='] = 6;
    transitions[3]['='] = 7;
    transitions[4]['='] = 8;
    transitions[5]['='] = 9;

    // Finalizações para tokens de comparação
    finalStates[4] = TOKEN_GT;  // >
    finalStates[5] = TOKEN_LT;  // <
    finalStates[6] = TOKEN_EQ;  // ==
    finalStates[7] = TOKEN_NEQ; // !=
    finalStates[8] = TOKEN_GTE; // >=
    finalStates[9] = TOKEN_LTE; // <=
    finalStates[10] = TOKEN_LPAREN; // (
    finalStates[11] = TOKEN_RPAREN; // )

    // Transições para números
    for (char c = '0'; c <= '9'; ++c) {
        transitions[0][c] = 1;
        transitions[1][c] = 1;
    }

    // Finalizações para números
    finalStates[1] = TOKEN_NUMBER;
}

// Função que processa a string de entrada e retorna os tokens
std::vector<Token> DFA::analyze(const std::string& input) {
    std::vector<Token> tokens;
    size_t position = 0;

    while (position < input.size()) {

        Token token = getToken(input, position);

        if (token.type != TOKEN_UNKNOWN) {
            tokens.push_back(token);
            position += token.value.size();

        } else {
            if (input[position] != ' '){
                std::cerr << "Erro lexico na posicaoo " << position << ":" << input[position] << " nao reconhecido." << std::endl;
            }
            position++;
        }
    }

    return tokens;
}

// Função para obter o próximo token a partir da posição atual
Token DFA::getToken(const std::string& input, size_t start) {
    int currentState = 0;
    std::string value;
    size_t position = start;

    while (position < input.size()) {
        char currentChar = input[position];
        if (transitions[currentState].find(currentChar) != transitions[currentState].end()) { //Se existir uma transição com aquele estado/simbolo
            currentState = transitions[currentState][currentChar];
            value += currentChar;
            position++;
        } else {
            //std::cerr << "Char atual: " << currentChar << std::endl;
            break;
        }
    }

    if (finalStates.find(currentState) != finalStates.end()) {  //Se o estado atual for um estado final
        return {finalStates[currentState], value};
    } else {
        //std::cerr << "Estado atual: " << currentState << std::endl;
        return {TOKEN_UNKNOWN, value};
    }
}
