#include "project1.h"

void insertion_sort(std::vector<int> &v){
    for (int i = 1; i < v.size(); ++i){
        int j = i;
        while (j > 0 && v[j] < v[j-1]){
            std::swap(v[j], v[j-1]);
            --j;
        }
    }
}
