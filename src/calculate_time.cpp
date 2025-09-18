#include "../include/calculate_time.hpp"
#include "../include/linear_search.hpp"
#include "../include/handle_input.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <cmath>

#define MEDIA 30
#define MAX 2000

void Calculate_time::calculate_all(std::vector<int> *input_ptr) {
    calculate_time_linear(input_ptr, linear_search, linear_vec);
}

void Calculate_time::calculate_time_linear(std::vector<int> *input_ptr, 
                                        int (*func_ptr)(std::vector<int>&, int), 
                                        std::vector<Data_algorithm> &vec_alg) {                             
    int temp = input_ptr->size();
    while (temp < MAX) {
        media_linear_search.insert({temp, 0});
        temp += 200; // Salto de entrada
    }

    for (int idx{ 0 }; idx < MEDIA; ++idx) {
        input_ptr = create_input();

        while (input_ptr->size() < MAX) {
            int random = random_number(input_ptr);
    
            const auto start{std::chrono::steady_clock::now()};
            func_ptr(*input_ptr, random);  
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
        Data_algorithm temp;
        temp.entry = e.first;
        temp.real_time = e.second;

        vec_alg.insert(vec_alg.begin(), temp);        
    }

    calculate_O_n();
    calculate_O_n2();
    test_csv(media_linear_search);
}

int Calculate_time::random_number(std::vector<int> *input_ptr) {
    return input_ptr->size();
}

void Calculate_time::test_csv(std::unordered_map<int , float> map) {
    std::ofstream myfile ("linear.CSV");
    if (myfile.is_open()) {
        for (auto element : linear_vec) {
            myfile << element.entry << "," << element.real_time << "," << element.n_time << 
            "," << element.n2_time << '\n';
        }
    }
}

// deixar generico
void Calculate_time::calculate_O_n() {
    float numerator = 0;
    float denominator = 0;

    for (auto element : linear_vec) {
        float fn = element.entry;
        numerator += fn * element.real_time;
        denominator += fn * fn;
    }

    float constant = numerator / denominator;
    //float constant = linear_vec.back().real_time / linear_vec.back().entry;

    for (size_t idx{ 0 }; idx < linear_vec.size(); ++idx) {
        linear_vec[idx].n_time = linear_vec[idx].entry * constant;
    }
} 

void Calculate_time::calculate_O_n2() {
    float numerator = 0;
    float denominator = 0;

    for (auto element : linear_vec) {
        float fn = element.entry * element.entry;
        numerator += fn * element.real_time;
        denominator += fn * fn;
    }

    float constant = numerator / denominator;
    //float constant = linear_vec.back().real_time / pow(linear_vec.back().entry, 2);

    for (size_t idx{ 0 }; idx < linear_vec.size(); ++idx) {
        linear_vec[idx].n2_time = pow(linear_vec[idx].entry, 2) * constant;
        //linear_vec[idx].n_time = linear_vec[idx].entry * constant;
    }
}

/*     float numerator = 0.0f, denominator = 0.0f;

    for (auto &elem : linear_vec) {
        float fn = f(elem.entry);
        numerator += fn * elem.real_time;z
        denominator += fn * fn;
    }

    float constant = numerator / denominator; */
