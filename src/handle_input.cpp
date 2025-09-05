#include "../include/handle_input.hpp"
#include <vector>
#include <cstddef>
#include <iostream>

#define SIZE 100

std::vector<int> *create_input(void) {
    std::vector<int>* input_ptr = new std::vector<int>();

    for (size_t idx{0}; idx < SIZE; ++idx) {
        input_ptr->push_back(idx);
    }
    
    return input_ptr;
}

std::vector<int> *resize_input(std::vector<int> *input) {
    int size = input->size();
    int max_size = size * 2;


    for (; size < max_size; ++size) {
        input->push_back(size);
    } 

    return input;
}


