#ifndef CALCULATE_TIME
#define CALCULATE_TIME

#include <vector>
#include <unordered_map>

class Calculate_time {
    public:
        void calculate_time_linear(std::vector<int> *input_ptr);  
        int random_number(std::vector<int> *input_ptr);
        std::unordered_map<int, float> *initialize_map(std::vector<int> *input_ptr);
        void test_csv(std::unordered_map<int , float> map);
        void calculate_O_n();

    private:
        std::unordered_map<int, float> media_linear_search;
        std::unordered_map<int, float> o_linear;
};

#endif
