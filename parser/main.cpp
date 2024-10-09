#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "parser.h"

int main(){

    std::vector<Token> tokens = lerFita("../lexer/fita.dat");

    for( const auto &token : tokens ){
        std::cout << token.tokenName << " ";
    }

    SLR_Table parser;
    int result = parser.parse(tokens);

    return 0;
}