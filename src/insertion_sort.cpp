#include "../include/insertion_sort.hpp"
#include <cstddef>
#include <vector>

void insertion_sort(std::vector<int>& input) {
    size_t size_input = input.size();
    for (size_t idx = 1; idx < size_input; idx++) { 
        int key = input[idx];
        int j = idx - 1;

        while (j >= 0 && input[j] > key) {
            input[j + 1] = input[j]; 
            j = j - 1;
        }
        input[j + 1] = key;
    }
}