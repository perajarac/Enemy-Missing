#include <iostream>
#include <cstdio>
#include "../inc/assembler.hpp"
#include "../inc/parser.hpp"


int main() {
    std::cout << "Starting parser..." << std::endl;
    if (yyparse() == 0) {
        std::cout << "Parsing completed successfully!" << std::endl;
    } else {
        std::cerr << "Parsing failed." << std::endl;
    }

    return 0;
}
