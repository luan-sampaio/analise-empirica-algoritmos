#include "../include/linear_search.hpp"
#include <cstddef>


int linear_search(std::vector<int> &input, int value) {
    size_t size_input = input.size();
    
    for (size_t idx{0}; idx < size_input; ++idx) {
        if (input[idx] == value) {
            return idx;
        }
    }

    return -1;
}

