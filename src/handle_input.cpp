#include "../include/handle_input.hpp"
#include <vector>
#include <cstddef>
#include <iostream>

#define SIZE 1000

void show_usage() {
    std::cout << "Bem vindo ao alg_analyzer cpp, version 1.0, (c) IMD/UFRN.\n\n";
    std::cout << "NOME\n";
    std::cout << "  alg_analyzer - Analisador de algoritmos\n\n";
    std::cout << "DESCRIÇÃO\n";
    std::cout << "  O analizador de algoritmos é um programa que avaliará empiricamente o tempo de execução\n";
    std::cout << "  de execução dos seguintes algoritmos:\n\n";
    std::cout << "  - Busca linear, algoritmo_1, algoritmo_2 e algoritmo_3.\n\n";
    std::cout << "  Assim, o programa coletará o tempo de cada algoritmo e fará a comparação nas seguintes funções teóricas:\n\n";
    std::cout << "  - O(n), O(log(n)), O(n.log(n)), O(n²) e O(n³).\n\n";
    std::cout << "  Dessa forma, o programa entrega a função assintótica que mais se aproxima do desempenho\n";
    std::cout << "  do algoritmo calculado, além de exportar um arquivo CSV com os dados reais calculado e \n";
    std::cout << "  das funções teóricas, assim poderemos plotar nos gráficos para visualizar os cálculos\n\n";
    std::cout << "[ Clique enter para iniciar os cálculos ]\n";
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
    int max_size = size + 1000;

    for (; size < max_size; ++size) {
        input.push_back(size);
    } 

    return &input;
}


