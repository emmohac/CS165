#include "project1.h"

void shell_sort4(std::vector<int> &v){
    std::vector<int> gaps {1073790977, 268460033, 67121153, 16783361, 4197377, 1050113, 262913, 65921, 16577, 4193, 1073, 281, 77, 23, 8, 1};
    for (const int gap : gaps)
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
