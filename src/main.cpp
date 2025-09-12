#include "../include/handle_input.hpp"
#include "../include/calculate_time.hpp"

#include <vector>
int main(int argc, char *argv[]) {
    show_usage();
    std::vector<int> *input_ptr = create_input();
    std::unordered_map<int, float> media_algorithm;

    Calculate_time time;
    time.calculate_time_linear(input_ptr);
    
    delete input_ptr;

    return 0;
}
