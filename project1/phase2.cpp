#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include "project1.h"
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>

typedef void (*sort_func)(std::vector<int> &nums);

std::vector<int> get_random_vector(int size);
void randomize(std::vector<int> &v);
void almost_sorted(std::vector<int> &v);

void print(const std::vector<int> &nums);

int main(int argc, char **argv){
    const std::string func_name = argv[1];
    const int vector_size = std::stoi(argv[2]);
    const std::string input_type = argv[3];
    const int COUNTER = 5;

    std::unordered_map<std::string, sort_func> name_to_func = {
        {"insertion", insertion_sort},
        {"merge", merge_sort},
        {"shell_sort1", shell_sort1},
        {"shell_sort2", shell_sort2},
        {"shell_sort3", shell_sort3},
        {"shell_sort4", shell_sort4},
        {"hybrid_sort1", hybrid_sort1},
        {"hybrid_sort2", hybrid_sort2},
        {"hybrid_sort3", hybrid_sort3},
    };

    std::vector<int> nums = get_random_vector(vector_size);

    if (input_type == "udp"){
        randomize(nums);
    } else if (input_type == "asp"){
        almost_sorted(nums);
    } else if (input_type == "rsp"){
        std::reverse(nums.begin(), nums.end());        
        almost_sorted(nums);
    } else
        std::cout << "Wrong input" << std::endl;

    std::chrono::seconds s(0);
    std::chrono::milliseconds foo = std::chrono::duration_cast<std::chrono::milliseconds> (s);
    for (int i = 0; i < COUNTER; ++i){
        std::vector<int> v(nums.cbegin(), nums.cend());
        auto start = std::chrono::steady_clock::now();
        name_to_func[func_name](v);
        auto end = std::chrono::steady_clock::now();
        foo += std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    }
    //std::cout << vector_size << ", " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    std::cout << vector_size << ", " << foo.count() / COUNTER  << std::endl;
    return 0;
}

std::vector<int> get_random_vector(int size){
    std::vector<int> to_return;
    for (int i = 0; i < size; ++i)
        to_return.push_back(i);
    
    return to_return;
}

void randomize(std::vector<int> &v){
    std::random_device device;    
    std::default_random_engine engine{device()};

    for (int i = v.size() - 1; i >= 0; --i){
        std::uniform_int_distribution<int> distribution{0, i};
        int k = distribution(engine);
        std::swap(v[i], v[k]);
    }
}

void almost_sorted(std::vector<int> &v){
    std::random_device device;
    std::default_random_engine engine{device()};
    int pairs = 2 * log(v.size());
    for (int i = 0; i < pairs; ++i){
        std::uniform_int_distribution<int> distribution{0, v.size()-1};
        int j = distribution(engine);
        int k = distribution(engine);
        std::swap(v[j], v[k]);
    }
}

void print(const std::vector<int> &nums){
    for (const int i : nums)
        std::cout << i << " ";
    std::cout << std::endl;
}