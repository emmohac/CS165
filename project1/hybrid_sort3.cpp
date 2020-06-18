#include "project1.h"
#include <math.h>

std::vector<int> hybrid_merge3(std::vector<int> &v1, std::vector<int> &v2){
    std::vector<int> to_return;

    int v1_index = 0,
        v2_index = 0;

    while (v1_index < v1.size() && v2_index < v2.size())
        if (v1[v1_index] < v2[v2_index])
            to_return.push_back(v1[v1_index++]);
        else
            to_return.push_back(v2[v2_index++]);

    while (v1_index < v1.size())
        to_return.push_back(v1[v1_index++]);

    while (v2_index < v2.size())
        to_return.push_back(v2[v2_index++]);

    return to_return;
}

void hybrid_merge_sort3(std::vector<int> &v, const double H){
    int n = v.size();
    
    if (n > H){
        auto iter = v.begin();
        for (int i = 0; i < n / 2; ++i)
            ++iter;
        std::vector<int> v1(v.begin(), iter);
        std::vector<int> v2(iter, v.end());

        hybrid_merge_sort3(v1, H);
        hybrid_merge_sort3(v2, H);
        v = hybrid_merge3(v1, v2);
    } else
        insertion_sort(v);
}

void hybrid_sort3(std::vector<int> &v){
    const int H = pow(v.size(), 1 / 3);
    hybrid_merge_sort3(v, H);
}
