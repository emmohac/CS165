#include "project2.h"
#include "WAVLTree.h"
#include <algorithm>

void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
    WAVLTree<int, double> tree;
    int bin_index = 1;
    for (int i = 0; i < items.size(); ++i){
        if (tree.is_empty()) {
            tree.insert(bin_index, items[i]);
        }
        else if (tree.get_root_brc() < items[i]){
            tree.insert(tree.getSize()+1, items[i]);
            bin_index = tree.getSize();
        }
        else {
            double item_value = items[i];
            bin_index = tree.add_item(item_value);
        }
        assignment[i] = bin_index;
        if (bin_index > free_space.size())
            free_space.push_back(1.0 - items[i]);
        else 
            free_space[bin_index - 1] -= items[i];
    }
}

void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
    std::vector<double> sorted_item(items);
    std::sort(sorted_item.begin(), sorted_item.end());
    std::reverse(sorted_item.begin(), sorted_item.end());
    WAVLTree<int, double> tree;
    int bin_index = 1;
    for (int i = 0; i < sorted_item.size(); ++i) {
        if (tree.is_empty())
            tree.insert(bin_index, sorted_item[i]);
        else if (tree.get_root_brc() < sorted_item[i]){
            tree.insert(tree.getSize() + 1, sorted_item[i]);
            bin_index = tree.getSize();
        } else {
            double item_value = sorted_item[i];
            bin_index = tree.add_item(item_value);
        }
        assignment[i] = bin_index;
        if (bin_index > free_space.size())
            free_space.push_back(1.0 - sorted_item[i]);
        else 
            free_space[bin_index - 1] -= sorted_item[i];
    }
}