#include "../include/handle_input.hpp"
#include <vector>
#include <cstddef>
#include <iostream>

#define SIZE 100

void show_usage() {
    
    // Display program information and usage instructions
    std::cout << "Bem vindo ao alg_analyzer cpp, version 1.0, (c) IMD/UFRN.\n\n";
    std::cout << "NOME\n";
    std::cout << "  alg_analyzer - Analizador de algoritmos\n\n";
    std::cout << "DESCRIÇÃO\n";
    std::cout << "  Sloc counts the individual number **lines of code** (LOC), comments, and blank\n";
    std::cout << "  lines found in a list of files or directories passed as the last argument\n";
    std::cout << "  (after options).\n";
    std::cout << "  After the counting process is concluded the program prints out to the standard\n";
    std::cout << "  output a table summarizing the information gathered, by each source file and/or\n";
    std::cout << "  directory provided.\n";
    std::cout << "  It is possible to inform which fields sloc should use to sort the data by, as\n";
    std::cout << "  well as if the data should be presented in ascending/descending numeric order.\n\n";
    std::cout << "Clique enter para inicias os cálculos:\n";
    std::string command = "";
    getline(std::cin, command);
}

std::vector<int> *create_input(void) {
    std::vector<int>* input_ptr = new std::vector<int>();

    for (size_t idx{0}; idx < SIZE; ++idx) {
        input_ptr->push_back(idx);
    }
    
    return input_ptr;
}

std::vector<int> *resize_input(std::vector<int> &input) {
    int size = input.size();
    int max_size = size + 200;

    for (; size < max_size; ++size) {
        input.push_back(size);
    } 

    return &input;
}


