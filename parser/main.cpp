#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.h"


std::vector<Token> lerFita(const char* filename) {
    std::vector<Token> token;
    std::ifstream arquivo(filename, std::ios::binary);
    
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo para leitura na análise sintática.\n";
        return token;
    }

    Token t;
    while (arquivo.read(reinterpret_cast<char*>(&t), sizeof(t))) {
        token.push_back(t);
    }

    arquivo.close();
    return token;
}


int main(){

    std::vector<Token> tokens = lerFita("../lexer/fita.dat");
    std::cout << "teste";
    for (Token t : tokens) {
        std::cout << "Token: " << t.tokenName << " Valor: " << t.value << std::endl;
    }

    return 0;
}