#include "base.h"
#include <iostream>
#include <fstream>


std::vector<Token> lerFita(const char* filename) {
    std::vector<Token> tokens;
    std::ifstream arquivo(filename, std::ios::binary);
    
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo para leitura na análise sintática.\n";
        return tokens;
    }

    int length;
    arquivo.read((char*)(&length), sizeof(length));

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

int escreverFita(std::vector<Token> tokens, const char* filename) {
    
    std::ofstream outputFile(filename, std::ios::binary);
    if (!outputFile ) {
        std::cerr << "Erro ao escrever a fita." << std::endl;
        return 1;
    }

    int legnth = tokens.size();
    outputFile.write((char*) &legnth, sizeof(int));

    for (Token t : tokens) {

        outputFile.write(reinterpret_cast<const char*>(&t.type), sizeof(TokenType));

        outputFile.write(reinterpret_cast<const char*>(&t.position), sizeof(int));
        outputFile.write(reinterpret_cast<const char*>(&t.line), sizeof(int));

        int valueLength = static_cast<int>(t.value.size());
        outputFile.write(reinterpret_cast<const char*>(&valueLength), sizeof(int));
        outputFile.write(t.value.data(), valueLength); 

        int tokenNameLength = static_cast<int>(t.tokenName.size());
        outputFile.write(reinterpret_cast<const char*>(&tokenNameLength), sizeof(int));
        outputFile.write(t.tokenName.data(), tokenNameLength);    
    }

    outputFile.close();

    return 0;
}