#include "project2.h"
#include "WAVLTree.h"
#include <algorithm>

void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    WAVLTree<double, int> tree;
    int bin_index = 1;
    for (int i = 0; i < items.size(); ++i){
        if (tree.is_empty())
            tree.insert(1.0 - items[i], bin_index);
        else {
            WAVLTree<double, int>::TreeNode *node = tree.find_lte(items[i]);
            if (!node) {
                //std::cout << "Cannot find places for item " << items[i] << std::endl;
                tree.insert(1.0 - items[i], tree.getSize() + 1);
                bin_index = tree.getSize();
            }
            else {
                double current_rc = node->key;
                bin_index = node->value;
                double new_rc = current_rc - items[i];
                tree.remove(current_rc);
                if (std::abs(current_rc - items[i] < 0.0001))
                    tree.insert(0.0, bin_index);
                else
                    tree.insert(new_rc, bin_index);
            }
        }
        //tree.print_inorder();
        assignment[i] = bin_index;
        if (bin_index > free_space.size())
            free_space.push_back(1.0 - items[i]);
        else 
            free_space[bin_index - 1] -= items[i];
    }
}

void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    return;
    // std::vector<double> v(items);
    // std::sort(v.begin(), v.end());
    // std::reverse(v.begin(), v.end());

    // WAVLTree<double, int> tree;
    // int bin_index = 1;
    // for (int i = 0; i < v.size(); ++i){
    //     if (tree.is_empty())
    //         tree.insert(1.0 - v[i], bin_index);
    //     else {
    //         WAVLTree<double, int>::TreeNode *node = tree.find_lte(v[i]);
    //         if (!node) {
    //             //std::cout << "Cannot find places for item " << v[i] << std::endl;
    //             tree.insert(1.0 - v[i], tree.getSize() + 1);
    //             bin_index = tree.getSize();
    //         }
    //         else {
    //             double current_rc = node->key;
    //             bin_index = node->value;
    //             double new_rc = current_rc - v[i];
    //             tree.remove(current_rc);
    //             if (std::abs(current_rc - v[i] < 0.0001))
    //                 tree.insert(0.0, bin_index);
    //             else
    //                 tree.insert(new_rc, bin_index);
    //         }
    //     }
    //     //tree.print_inorder();
    //     assignment[i] = bin_index;
    //     if (bin_index > free_space.size())
    //         free_space.push_back(1.0 - v[i]);
    //     else 
    //         free_space[bin_index - 1] -= v[i];
    // }
}