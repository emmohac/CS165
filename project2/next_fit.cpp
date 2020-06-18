#include "project2.h"

void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    std::vector<double> bins {0.0, 0.0};
    int bin_index = 1;
    for (int i = 0; i < items.size(); ++i){
        if ((bins[bin_index] + items[i]) > 1){
            bins.push_back(0.0);
            ++bin_index;
        }
        bins[bin_index] += items[i];
        if (bin_index > free_space.size())
            free_space.push_back(1.0 - bins[bin_index]);
        else
            free_space[bin_index - 1] = 1.0 - bins[bin_index];
        assignment[i] = bin_index; 
    }
}