#include "project1.h"
#include <iterator>

std::vector<int> merge(std::vector<int> &a, std::vector<int> &b);

void merge_sort(std::vector<int> &v){
    int len = v.size();
    if (len == 1)
        return;

    auto iter = v.begin();
    for (int i = 0; i < len / 2; ++i)
        ++iter;

    std::vector<int> v1(v.begin(), iter);
    std::vector<int> v2(iter, v.end());

    merge_sort(v1);
    merge_sort(v2);
    v = merge(v1, v2);
}

std::vector<int> merge(std::vector<int> &v1, std::vector<int> &v2){
    std::vector<int> to_return;

    int v1_index = 0,
        v2_index = 0;

    while (v1_index < v1.size() && v2_index < v2.size()){
        if (v1[v1_index] < v2[v2_index])
            to_return.push_back(v1[v1_index++]);
        else
            to_return.push_back(v2[v2_index++]);
    }

    while (v1_index < v1.size())
        to_return.push_back(v1[v1_index++]);

    while (v2_index < v2.size())
        to_return.push_back(v2[v2_index++]);
    
    return to_return;
}
