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

    transitions[0]['t'] = 12;
    transitions[12]['r'] = 13;
    transitions[13]['u'] = 14;
    transitions[14]['e'] = 15;
    transitions[0]['T'] = 12;
    transitions[12]['R'] = 13;
    transitions[13]['U'] = 14;
    transitions[14]['E'] = 15;

    transitions[0]['f'] = 16;
    transitions[16]['a'] = 17;
    transitions[17]['l'] = 18;
    transitions[18]['s'] = 19;
    transitions[19]['e'] = 20;
    transitions[0]['F'] = 16;
    transitions[16]['A'] = 17;
    transitions[17]['L'] = 18;
    transitions[18]['S'] = 19;
    transitions[19]['E'] = 20;

    // Finalizações para tokens de comparação
    finalStates[21] = TOKEN_UNKNOWN;  // Nada identificado
    finalStates[4] = TOKEN_GT;  // >
    finalStates[5] = TOKEN_LT;  // <
    finalStates[6] = TOKEN_EQ;  // ==
    finalStates[7] = TOKEN_NEQ; // !=
    finalStates[8] = TOKEN_GTE; // >=
    finalStates[9] = TOKEN_LTE; // <=
    finalStates[10] = TOKEN_LPAREN; // (
    finalStates[11] = TOKEN_RPAREN; // )
    finalStates[15] = TOKEN_TRUE; // true
    finalStates[20] = TOKEN_FALSE; // false

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

        // Ignorar espaços em branco (se existirem) antes de buscar o próximo token
        while (position < input.size() && isspace(input[position])) {
            ++position;
        }
    
        Token token = getToken(input, position);
        
        if (!token.value.empty()) {

            tokens.push_back(token);
            
        } else {
            // Reportar token inválido
            std::cerr << "Erro lexico: token invalido '" << token.value << "' na posicao " << position << std::endl;
        }

        // Avançar a posição pela quantidade de caracteres do token processado
        position += token.value.size();

    }

    return tokens;
}

// Função para obter o próximo token a partir da posição atual
Token DFA::getToken(const std::string& input, size_t start) {
    int currentState = 0;       // Estado inicial
    std::string value;          // Valor do token
    size_t position = start;    // Posição inicial
    size_t lastValidPos = start; // Posição do último estado válido
    int lastValidState = -1;     // Último estado válido

    // Processar cada caractere da string de entrada
    while (position < input.size()) {
        char currentChar = input[position];

        // Verificar se o caractere atual é um espaço em branco
        if (isspace(currentChar)) {
            // Se já acumulamos algum valor no token, encerramos e retornamos o token
            if (!value.empty()) {
                break;
            }
            // Caso contrário, apenas ignore o espaço e continue
            ++position;
            continue;
        }

        // Verificar se há uma transição válida para o caractere atual
        if (transitions[currentState].find(currentChar) != transitions[currentState].end()) {
            currentState = transitions[currentState][currentChar];
            value += currentChar;
            position++;

            // Verificar se o estado atual é um estado final
            if (finalStates.find(currentState) != finalStates.end()) {
                lastValidState = currentState;
                lastValidPos = position;
            }
        } else {
            currentState = 21;
            value += currentChar;
            position++;
        }
    }

    // Verificar se encontramos um estado final válido
    if (lastValidState != -1) {
        // Retornar o token válido
        return {finalStates[lastValidState], input.substr(start, lastValidPos - start)};
    } else {
        // Se nenhum estado final foi encontrado, retornar o token inválido completo
        return {TOKEN_UNKNOWN, input.substr(start, position - start)};
    }
}