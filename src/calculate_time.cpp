#include "../include/calculate_time.hpp"
#include "../include/linear_search.hpp"
#include "../include/handle_input.hpp"

#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>

#define MEDIA 30
#define MAX 2000


void Calculate_time::calculate_time_linear(std::vector<int> *input_ptr) {                             
    int temp = input_ptr->size();
    while (temp < MAX) {
        media_linear_search.insert({temp, 0});
        o_linear.insert(temp, 0);
        temp += 200; // Salto de entrada
    }

    for (int idx{ 0 }; idx < MEDIA; ++idx) {
        input_ptr = create_input();

        while (input_ptr->size() < MAX) {
            int random = random_number(input_ptr);
    
            const auto start{std::chrono::steady_clock::now()};
            linear_search(*input_ptr, random);
            const auto finish{std::chrono::steady_clock::now()};
    
            auto elapsed_duration = finish - start;
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_duration).count();
    
            media_linear_search[input_ptr->size()] += nanoseconds;
            input_ptr = resize_input(*input_ptr);
        }
    }
    
    for (auto e : media_linear_search) {
        media_linear_search[e.first] = e.second / MEDIA;
    }

    for (auto e : media_linear_search) {
        std::cout << e.first << " " << e.second << '\n';
    }
    test_csv(media_linear_search);
    calculate_O_n();
}

int Calculate_time::random_number(std::vector<int> *input_ptr) {
    return input_ptr->size();
}

void Calculate_time::test_csv(std::unordered_map<int , float> map) {
    std::ofstream myfile ("linear.CSV");
    if (myfile.is_open()) {
        for (auto e : map) {
            myfile << e.first << "," << e.second << '\n';
        }
    }
}

void Calculate_time::calculate_O_n() {
    float c = media_linear_search.begin()->second / media_linear_search.begin()->first;

    for (auto e : media_linear_search) {
        o_linear[e.first] = e.first * c;
    }
}
