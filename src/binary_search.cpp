#include <iostream>
#include <vector>
#include <algorithm> 

int binary_search(const std::vector<int>& input, int target) {
    int left = 0;
    int right = input.size() - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (input[middle] == target) {
            return middle; 
        }
        if (input[middle] < target) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }
    return -1;
}
