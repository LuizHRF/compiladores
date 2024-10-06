#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.h"


std::vector<Token> lerFita(const char* filename) {
    std::vector<Token> tokens;
    std::ifstream arquivo(filename, std::ios::binary);
    
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo para leitura na análise sintática.\n";
        return tokens;
    }

    int length;
    arquivo.read((char*)(&length), sizeof(length));

    std::cout << "Length: " << length << std::endl;

    Token t;
    for (int i = 0; i < length; i++) {
        Token t;

        arquivo.read(reinterpret_cast<char*>(&t.type), sizeof(TokenType));
        arquivo.read(reinterpret_cast<char*>(&t.position), sizeof(int));
        arquivo.read(reinterpret_cast<char*>(&t.line), sizeof(int));

        int valueLength;
        arquivo.read(reinterpret_cast<char*>(&valueLength), sizeof(int));

        t.value.resize(valueLength);
        arquivo.read(&t.value[0], valueLength); 

        int tokenNameLength;
        arquivo.read(reinterpret_cast<char*>(&tokenNameLength), sizeof(int));

        t.tokenName.resize(tokenNameLength); 
        arquivo.read(&t.tokenName[0], tokenNameLength); 

        tokens.push_back(t);
    }

    arquivo.close();
    return tokens;
}


int main(){

    std::vector<Token> tokens = lerFita("../lexer/fita.dat");

    for (Token t : tokens) {
        std::cout << "Token: " << t.tokenName << " Valor: " << t.value << std::endl;
    }

    return 0;
}