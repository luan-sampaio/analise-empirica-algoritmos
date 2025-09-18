#include "../include/calculate_time.hpp"
#include "../include/linear_search.hpp"
#include "../include/binary_search.hpp"
#include "../include/insertion_sort.hpp"
#include "../include/quick_sort.hpp"
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
#define MAX 20000

void quickSortWrapper(std::vector<int>& vec) {
    if (!vec.empty()) {
        quick_sort(vec, 0, vec.size() - 1);
    }
}

void Calculate_time::calculate_all(std::vector<int> *input_ptr) {
   run_search_experiment("linear_search", linear_search, linear_vec, media_linear_search);
   run_search_experiment("binary_search", binary_search, binary_vec, media_binary_search);
   run_sort_experiment("insertion_sort", insertion_sort, insertion_vec, media_insertion_sort);
   run_sort_experiment("quick_sort", quickSortWrapper, quick_vec, media_quick_sort);
}
void Calculate_time::run_search_experiment(const std::string& alg_name,
    int (*func_ptr)(const std::vector<int>&, int),
    std::vector<Data_algorithm> &vec_alg,
    std::unordered_map<int, float> &media_map) {         

    media_map.clear();
    vec_alg.clear();

    // Prepara o mapa de médias
    std::vector<int>* temp_ptr = create_input();
    int temp_size = temp_ptr->size();
    while (temp_size < MAX) {
        media_map.insert({temp_size, 0});
        temp_size += 1000; // Salto de entrada
    }
    delete temp_ptr; // Libera memória

    for (int idx{ 0 }; idx < MEDIA; ++idx) {
        std::vector<int>* input_ptr = create_input();

        while (input_ptr->size() <= MAX) {
            int random = random_number(input_ptr);
    
            const auto start{std::chrono::steady_clock::now()};
            func_ptr(*input_ptr, random);  
            const auto finish{std::chrono::steady_clock::now()};
    
            auto elapsed_duration = finish - start;
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_duration).count();
    
            media_map[input_ptr->size()] += nanoseconds;

            resize_input(*input_ptr); // A função resize já retorna o ponteiro
        }
        delete input_ptr; // Libera a memória de cada vetor de teste
    }
    
    // Transfere as médias para o vetor de resultados
    for (auto const& [size, total_time] : media_map) {
        Data_algorithm temp;
        temp.entry = size;
        temp.real_time = total_time / MEDIA;
        vec_alg.push_back(temp);        
    }
    // Ordena o vetor de resultados pelo tamanho da entrada
    std::sort(vec_alg.begin(), vec_alg.end(), [](const Data_algorithm& a, const Data_algorithm& b){
        return a.entry < b.entry;
    });

    // Chama as funções genéricas de cálculo e salvamento
    calculate_all_theoretical(vec_alg);
    save_to_csv(alg_name + ".csv", vec_alg);
}
// Adicione esta implementação em calculate_time.cpp

void Calculate_time::run_sort_experiment(const std::string& alg_name,
                                        void (*func_ptr)(std::vector<int>&), 
                                        std::vector<Data_algorithm> &vec_alg,
                                        std::unordered_map<int, float> &media_map) {
    media_map.clear();
    vec_alg.clear();

    std::vector<int>* temp_ptr = create_input();
    int temp_size = temp_ptr->size();
    while (temp_size < MAX) {
        media_map.insert({temp_size, 0});
        temp_size += 200;
    }
    delete temp_ptr;

    for (int idx{ 0 }; idx < MEDIA; ++idx) {
        std::vector<int>* input_ptr = create_input();
        while (input_ptr->size() < MAX) {
            
            // IMPORTANTE: Embaralha o vetor para testar o caso médio
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(input_ptr->begin(), input_ptr->end(), g);
    
            const auto start{std::chrono::steady_clock::now()};
            func_ptr(*input_ptr); // <-- A chamada aqui é mais simples
            const auto finish{std::chrono::steady_clock::now()};
    
            auto elapsed_duration = finish - start;
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_duration).count();
    
            media_map[input_ptr->size()] += nanoseconds;
            resize_input(*input_ptr);
        }
        delete input_ptr;
    }
    
    // O resto da função é idêntico (calcular média, ordenar, salvar)
    for (auto const& [size, total_time] : media_map) {
        Data_algorithm temp;
        temp.entry = size;
        temp.real_time = total_time / MEDIA; // Use float para a média
        vec_alg.push_back(temp);        
    }
    std::sort(vec_alg.begin(), vec_alg.end(), [](const Data_algorithm& a, const Data_algorithm& b){
        return a.entry < b.entry;
    });

    calculate_all_theoretical(vec_alg);
    save_to_csv(alg_name + ".csv", vec_alg);
}

int Calculate_time::random_number(std::vector<int> *input_ptr) {
    return input_ptr->size();
}

// Função generalizada para calcular TODAS as curvas teóricas
void Calculate_time::calculate_all_theoretical(std::vector<Data_algorithm> &vec_alg) {
    if (vec_alg.empty()) return;

    // A constante C é calculada com base no maior valor de entrada,
    // usando o tempo real medido para a complexidade O(n).
    // Esta constante será usada para escalar todas as outras curvas para comparação.
    float constant = vec_alg.back().real_time / vec_alg.back().entry;

    for (size_t idx = 0; idx < vec_alg.size(); ++idx) {
        int n = vec_alg[idx].entry;
        
        // Evita divisão por zero ou log(0)
        if (n == 0) continue; 
        
        vec_alg[idx].n_time = n * constant;
        vec_alg[idx].log_n_time = std::log2(n) * constant;
        vec_alg[idx].n_log_n_time = n * std::log2(n) * constant;
        
        // Usamos (float)n para evitar overflow em n*n
        vec_alg[idx].n2_time = (float)n * n * constant; 
        vec_alg[idx].n3_time = (float)n * n * n * constant;
    }
}

// Função generalizada para salvar os resultados em um arquivo CSV
void Calculate_time::save_to_csv(const std::string& filename, const std::vector<Data_algorithm>& vec_alg) {
    std::ofstream myfile(filename);
    if (myfile.is_open()) {
        // Escreve o cabeçalho do CSV
        myfile << "Tamanho,Tempo_Real,O(n),O(log_n),O(n_log_n),O(n^2),O(n^3)\n";
        
        // Escreve os dados
        for (const auto& element : vec_alg) {
            myfile << element.entry << ","
                   << element.real_time << ","
                   << element.n_time << ","
                   << element.log_n_time << ","
                   << element.n_log_n_time << ","
                   << element.n2_time << ","
                   << element.n3_time << "\n";
        }
        std::cout << "Resultados salvos com sucesso em " << filename << "\n";
    } else {
        std::cerr << "Erro ao abrir o arquivo " << filename << "\n";
    }
}
