#ifndef CALCULATE_TIME
#define CALCULATE_TIME

#include <string>
#include <vector>
#include <unordered_map>

struct Data_algorithm {
    int entry;
    int real_time;
    float n_time;
    float log_n_time;
    float n_log_n_time;
    float n2_time;
    float n3_time;
};

class Calculate_time {
    public:
        void calculate_all(std::vector<int> *input_ptr);
        void run_search_experiment(
        const std::string& alg_name,
        int (*func_ptr)(const std::vector<int>&, int), 
        std::vector<Data_algorithm>& vec_alg,
        std::unordered_map<int, float>& media_map
);
        void run_sort_experiment(
        const std::string& alg_name,
        void (*func_ptr)(std::vector<int>&), 
        std::vector<Data_algorithm>& vec_alg,
        std::unordered_map<int, float>& media_map
);
        int random_number(std::vector<int> *input_ptr);
        std::unordered_map<int, float> *initialize_map(std::vector<int> *input_ptr);
        void calculate_all_theoretical(std::vector<Data_algorithm> &vec_alg);
        void save_to_csv(const std::string& filename, const std::vector<Data_algorithm>& vec_alg);
    
    private:
        std::unordered_map<int, float> media_linear_search;
        std::vector<Data_algorithm> linear_vec;
        std::unordered_map<int, float> media_binary_search;
        std::vector<Data_algorithm> binary_vec;
        std::unordered_map<int, float> media_insertion_sort;
        std::vector<Data_algorithm> insertion_vec;
        std::unordered_map<int, float> media_quick_sort;
        std::vector<Data_algorithm> quick_vec;
};
#endif
