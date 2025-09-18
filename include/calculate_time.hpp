#ifndef CALCULATE_TIME
#define CALCULATE_TIME

#include <vector>
#include <unordered_map>

struct data_algorithm {
    int entry;
    int real_time;
    int n_time;
    int n2_time;
};

class Calculate_time {
    public:
        void calculate_all(std::vector<int> *input_ptr);
        void calculate_time_linear(std::vector<int> *input_ptr, 
        int (*func_ptr)(std::vector<int>&, int), std::vector<data_algorithm> &vec_alg);  
        int random_number(std::vector<int> *input_ptr);
        std::unordered_map<int, float> *initialize_map(std::vector<int> *input_ptr);
        void test_csv(std::unordered_map<int , float> map);
        void calculate_O_n();

    private:
        std::unordered_map<int, float> media_linear_search;
        //std::unordered_map<int, float> o_linear;
        std::vector<float> o_linear;
        std::vector<data_algorithm> linear_vec;
};

#endif
