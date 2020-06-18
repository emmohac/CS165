#include "project1.h"

void shell_sort1(std::vector<int> &v){
    for (int gap = v.size() / 2; gap > 0; gap /= 2){
        for (int i = gap; i < v.size(); ++i){
            int to_swap = v[i];
            int j = i;
            while (j >= gap && to_swap < v[j - gap]){
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = to_swap;
        }
    }
}
