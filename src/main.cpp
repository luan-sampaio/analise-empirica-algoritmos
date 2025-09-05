#include "../include/handle_input.hpp"
#include "../include/linear_search.hpp"

#include <vector>
#include <random>
#include <chrono>
#include <iostream>

struct Time {
    double size;
    double time;
};

int main(void) {
    std::vector<int> *input_ptr = create_input();
    //input_ptr = resize_input(*input_ptr);
    //input_ptr = resize_input(*input_ptr);
    //input_ptr = resize_input(*input_ptr);
    std::vector<Time> amount_time;

    while (input_ptr->size() < 2000) {
        
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed); // Gerador de números pseudoaleatórios
        std::uniform_int_distribution<int> distrib(0, input_ptr->size());
        int random_number = distrib(gen);
    
        const auto start{std::chrono::steady_clock::now()};
        int i = linear_search(*input_ptr, random_number);
        const auto finish{std::chrono::steady_clock::now()};
        auto elapsed_duration = finish - start;
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_duration).count();
    
        Time temp_time;
        temp_time.size = input_ptr->size();
        temp_time.time = nanoseconds;

        amount_time.push_back(temp_time);

        input_ptr = resize_input(*input_ptr);
    }

    for (auto e : amount_time) {
        std::cout << "Time: " << e.time / amount_time.back().time ;
        std::cout << "  N: " << e.size << '\n';
    }

    delete input_ptr;

    return 0;
}
