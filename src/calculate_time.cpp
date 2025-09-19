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
#include <iomanip> 
#include <limits> 
#include <map>  
#include <functional>  


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
// Em calculate_time.cpp, substitua a função inteira por esta versão

void Calculate_time::run_search_experiment(const std::string& alg_name,
    int (*func_ptr)(const std::vector<int>&, int),
    std::vector<Data_algorithm> &vec_alg,
    std::unordered_map<int, float> &media_map) {         

    media_map.clear();
    vec_alg.clear();

    std::vector<int>* temp_ptr = create_input();
    int temp_size = temp_ptr->size();
    while (temp_size < MAX) {
        media_map.insert({temp_size, 0});
        temp_size += 1000;
    }
    delete temp_ptr; 

    for (int idx{ 0 }; idx < MEDIA; ++idx) {
        std::vector<int>* input_ptr = create_input();

        while (input_ptr->size() < MAX) { // Use '<' para consistência
            int random = random_number(input_ptr);
            long long nanoseconds = 0; // Variável para guardar o tempo

            // --- LÓGICA CONDICIONAL ADICIONADA AQUI ---
            if (alg_name == "binary_search") {
                // Para a busca binária (muito rápida), amplificamos o sinal
                const int REPETICOES_INTERNAS = 10000;
                const auto start{std::chrono::steady_clock::now()};
                for (int i = 0; i < REPETICOES_INTERNAS; ++i) {
                    func_ptr(*input_ptr, random);
                }
                const auto finish{std::chrono::steady_clock::now()};
                auto total_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
                nanoseconds = total_nanoseconds / REPETICOES_INTERNAS;
            } else {
                // Para outros algoritmos de busca (como a linear), uma única medição é suficiente
                const auto start{std::chrono::steady_clock::now()};
                func_ptr(*input_ptr, random);  
                const auto finish{std::chrono::steady_clock::now()};
                nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
            }
            // --- FIM DA LÓGICA CONDICIONAL ---
    
            media_map[input_ptr->size()] += nanoseconds;
            resize_input(*input_ptr); 
        }
        delete input_ptr; 
    }
    
    // O resto da função continua igual...
    for (auto const& [size, total_time] : media_map) {
        Data_algorithm temp;
        temp.entry = size;
        temp.real_time = total_time / MEDIA;
        vec_alg.push_back(temp);        
    }
    std::sort(vec_alg.begin(), vec_alg.end(), [](const Data_algorithm& a, const Data_algorithm& b){
        return a.entry < b.entry;
    });

    std::string best_fit = find_best_fit_mse(vec_alg);
    std::cout << "-> Para o algoritmo '" << alg_name << "', a curva de melhor ajuste é: " << best_fit << std::endl;

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
        temp_size += 1000;
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
            func_ptr(*input_ptr); 
            const auto finish{std::chrono::steady_clock::now()};
    
            auto elapsed_duration = finish - start;
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_duration).count();
    
            media_map[input_ptr->size()] += nanoseconds;
            resize_input(*input_ptr);
        }
        delete input_ptr;
    }
    
    for (auto const& [size, total_time] : media_map) {
        Data_algorithm temp;
        temp.entry = size;
        temp.real_time = total_time / MEDIA;
        vec_alg.push_back(temp);        
    }
    std::sort(vec_alg.begin(), vec_alg.end(), [](const Data_algorithm& a, const Data_algorithm& b){
        return a.entry < b.entry;
    });

    std::string best_fit = find_best_fit_mse(vec_alg);
    std::cout << "-> Para o algoritmo '" << alg_name << "', a curva de melhor ajuste é: " << best_fit << std::endl;

    save_to_csv(alg_name + ".csv", vec_alg);
}

int Calculate_time::random_number(std::vector<int> *input_ptr) {
    return input_ptr->size();
}

// Função generalizada para calcular TODAS as curvas teóricas
std::string Calculate_time::find_best_fit_mse(std::vector<Data_algorithm>& vec_alg) {
    if (vec_alg.empty()) return "N/A";

    float max_y = 0.0f;
    for (const auto& element : vec_alg) {
        if (element.real_time > max_y) {
            max_y = element.real_time;
        }
    }
    if (max_y > 0) {
        for (auto& element : vec_alg) {
            element.real_time_norm = element.real_time / max_y;
        }
    }

    std::map<std::string, double> mse_results;

    std::map<std::string, std::function<double(double)>> theoretical_funcs = {
        {"O(n)", [](double n){ return n; }},
        {"O(n log n)", [](double n){ return n <= 1 ? 0 : n * std::log2(n); }},
        {"O(n^2)", [](double n){ return n * n; }},
        {"O(n^3)", [](double n){ return n * n * n; }}
    };

    for (auto const& [name, func] : theoretical_funcs) {
        std::vector<double> theoretical_w;
        double max_w = 0.0;
        
        for (const auto& element : vec_alg) {
            double w = func(element.entry);
            theoretical_w.push_back(w);
            if (w > max_w) {
                max_w = w;
            }
        }
        double sum_squared_error = 0.0;
        if (max_w > 0) {
            for (size_t i = 0; i < vec_alg.size(); ++i) {
            
                double wi_norm = theoretical_w[i] / max_w;

                // Salva o valor normalizado na struct para o CSV
                if (name == "O(n)") vec_alg[i].theoretical_n_norm = wi_norm;
                if (name == "O(n log n)") vec_alg[i].theoretical_n_log_n_norm = wi_norm;
                if (name == "O(n^2)") vec_alg[i].theoretical_n2_norm = wi_norm;
                if (name == "O(n^3)") vec_alg[i].theoretical_n3_norm = wi_norm;
                
                // Calcula o erro quadrático com os valores normalizados
                double error = vec_alg[i].real_time_norm - wi_norm;
                sum_squared_error += error * error;
            }
        }
        
        mse_results[name] = sum_squared_error / vec_alg.size();
    }
    std::string best_fit = "N/A";
    double min_mse = std::numeric_limits<double>::max();
    for (auto const& [name, mse] : mse_results) {
        if (mse < min_mse) {
            min_mse = mse;
            best_fit = name;
        }
    }
    
    return best_fit;
}

void Calculate_time::save_to_csv(const std::string& filename, const std::vector<Data_algorithm>& vec_alg) {
    std::ofstream myfile(filename);
    if (myfile.is_open()) {
        myfile << "Tamanho,Tempo_Real_Norm,O(n)_Norm,O(nlogn)_Norm,O(n^2)_Norm,O(n^3)_Norm\n";
        
        myfile << std::fixed << std::setprecision(6);

        for (const auto& element : vec_alg) {
            myfile << element.entry << ","
                   << element.real_time_norm << "," 
                   << element.theoretical_n_norm << ","
                   << element.theoretical_n_log_n_norm << ","
                   << element.theoretical_n2_norm << ","
                   << element.theoretical_n3_norm << "\n";
        }
        std::cout << "Resultados salvos com sucesso em " << filename << "\n";
    } else {
        std::cerr << "Erro ao abrir o arquivo " << filename << "\n";
    }
}