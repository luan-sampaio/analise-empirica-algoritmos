#include "../include/quick_sort.hpp"
#include <cstddef>
#include <utility>
#include <vector>

int particion(std::vector<int>& input, int begin, int end) {
    int pivo = input[end];
    
    int idx = (begin - 1);

    for (int j = begin; j <= end - 1; j++) {
        if (input[j] <= pivo) {
            idx++;
            std::swap(input[idx], input[j]);
        }
    }
    std::swap(input[idx + 1], input[end]);
    return (idx + 1);
}

void quick_sort(std::vector<int>& input, int begin, int end) {
    if (begin < end) {
        int pi = particion(input, begin, end);

        quick_sort(input, begin, pi - 1);
        
        quick_sort(input, pi + 1, end);
    }
}