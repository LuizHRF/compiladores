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

std::string getName(TokenType t) {

    switch (t) {
            case TOKEN_ATRIB: return  "TOKEN_ATRIB"; break;
            case TOKEN_EQ: return  "TOKEN_EQ"; break;
            case TOKEN_NEQ: return  "TOKEN_NEQ"; break;
            case TOKEN_LT: return  "TOKEN_LT"; break;
            case TOKEN_GT: return  "TOKEN_GT"; break;
            case TOKEN_LTE: return  "TOKEN_LTE"; break;
            case TOKEN_GTE: return  "TOKEN_GTE"; break;
            case TOKEN_VAR: return  "TOKEN_VAR"; break;
            case TOKEN_LPAREN: return  "TOKEN_LPAREN"; break;
            case TOKEN_RPAREN: return  "TOKEN_RPAREN"; break;
            case TOKEN_TRUE: return  "TOKEN_TRUE"; break;
            case TOKEN_FALSE: return  "TOKEN_FALSE"; break;
            case TOKEN_IF: return  "TOKEN_IF"; break;
            case TOKEN_ELSE : return  "TOKEN_ELSE"; break;
            case TOKEN_DO: return  "TOKEN_DO"; break;
            case TOKEN_UNKNOWN: return  "TOKEN_UNKNOWN"; break;
            case END_OF_SENTENCE: return  "EOF"; break;
            case TOKEN_NUMBER: return  "TOKEN_NUMBER"; break;
            default: return  "desconhecido"; break;
        }
}