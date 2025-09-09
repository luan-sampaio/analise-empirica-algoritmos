#include "../include/handle_input.hpp"
#include "../include/linear_search.hpp"

#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>

struct Time {
    double size;
    double time;
};

int main(int argc, char *argv[]) {
    show_usage();
    std::vector<int> *input_ptr = create_input();
    std::vector<Time> amount_time;

    while (input_ptr->size() < 5000) {
        
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed); // Gerador de números pseudoaleatórios
        std::uniform_int_distribution<int> distrib(0, input_ptr->size());
        int random_number = distrib(gen);
        
        // Se precisar embaralhar o vetor.
        std::shuffle(input_ptr->begin(), input_ptr->end(), std::default_random_engine(seed));
        
        // Contagem do tempo
        const auto start{std::chrono::steady_clock::now()};
        linear_search(*input_ptr, random_number);
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
        std::cout << "  N: " << e.size;
        std::cout << " T: " << (e.size * (e.time / e.size)) / amount_time.back().time << '\n';
    }

    delete input_ptr;

    return 0;
}
