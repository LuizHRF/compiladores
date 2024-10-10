#include "lexer/lexer.h"
#include "parser/parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>


int main(int argc, char *argv[]) {

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada" << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    DFA lexer;

    std::vector<Token> tokens = lexer.analyze(input);

    // for(Token t : tokens) {
    //     std::cout << getName(t.type) << " ";
    // }

    //escreverFita(tokens, "..\\lexer\\fita.dat");

    // std::vector<Token> tokens = lerFita("../lexer/fita.dat");

    SLR_Table parser;
    //parser.displayTable();
    int result = parser.parse(tokens);

    return 0;
}