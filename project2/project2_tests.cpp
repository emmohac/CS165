#include "WAVLTree.h"
#include "project2.h"
#include <iostream>
#include <utility>
#include <string>
#include <cmath> 

// Instructions
// some test cases for the WAVLTree and bin packing algorithms can be found in the main function below
//
// 1. Move all source code/header files you will be submitting to a new directory, along with the two files Makefile and project2_tests.cpp
// 2. Edit the main function to create and try different test cases on your algorithms
// 3. Enter the command "make" to compile and run the program
// 4. If you make any changes to any of the files, enter the command "make clean" to remove the generated executable before entering "make" again.
//
// note that passing the test cases here does not necessarily mean your WAVL tree or algorithms will pass other cases
// so it's a good idea to create and try different test cases for both 

typedef struct ProblemInstance {
	std::vector<double> items;
	std::vector<int> assignments;
	std::vector<double> free_space;
} ProblemInstance;

typedef void (*algorithm) (const std::vector<double>&, std::vector<int>&, std::vector<double>&);

template <typename KeyType, typename ValType>
void initializeTreeWithData (WAVLTree<KeyType, ValType>& tree, std::vector<std::pair<KeyType, ValType> > data)
{
	for (auto const& item : data) {
		tree.insert(item.first, item.second);
	}
}

bool compare(std::vector<double> v1, std::vector<double> v2)
{
	// floating point comparison
	for (int i = 0; i<v1.size(); i++) {
		if (std::fabs(v1[i]-v2[i]) > 1e-3) {
			return false;
		}
	}
	return true;
}

void testAlgorithm(ProblemInstance test, ProblemInstance expected_result, algorithm algo, std::string name)
{
	algo(test.items, test.assignments, test.free_space);
	if (test.assignments == expected_result.assignments and compare(test.free_space, expected_result.free_space)) {
		std::cout << "Test case passed: " <<  name << std::endl;
	} 
	else {
		std::cout << "Test case failed: " <<  name << std::endl;
	}
}

int main()
{

	// ------------------
	// WAVLTree tests
	// ------------------
	std::cout << std::endl;
	std::cout << "testing WAVLTree" << std::endl; 

	// define key/value pairs
	WAVLTree<int, char> tree;
	std::vector<std::pair <int, char> > data = {{4, 'a'}, {5, 'b'}, {2, 'c'}, {1, 'd'}}; 
	initializeTreeWithData(tree, data);
	std::cout << "find(4): " << tree.find(4) << ", Expected: a" << std::endl; 
	std::cout << "getSize(): " << tree.getSize() << ", Expected: 4" << std::endl; 
	std::cout << "getHeight(): " << tree.getHeight() << ", Expected: 3" << std::endl; 
	std::cout << "getRank(2): " << tree.getRank(2) << ", Expected: 2" << std::endl; 
	std::cout << "getRank(1): " << tree.getRank(1) << ", Expected: 1" << std::endl; 
	tree.insert(0, 'e'); // single rotation
	std::cout << "getSize(): " << tree.getSize() << ", Expected: 5" << std::endl; 
	std::cout << "getHeight(): " << tree.getHeight() << ", Expected: 3" << std::endl; 
	std::cout << "getRank(2): " << tree.getRank(2) << ", Expected: 1" << std::endl; 
	std::cout << "getRank(1): " << tree.getRank(1) << ", Expected: 2" << std::endl; 
	// add new tests


	// ------------------
	// bin packing tests
	// ------------------
	std::cout << std::endl;
	std::cout << "testing bin packing" << std::endl; 

	
	//define list of items 
	std::vector<double> items {0.1, 0.8, 0.3, 0.5, 0.7, 0.2, 0.6, 0.4};
	std::vector<int> assignments(items.size(), 0);
	std::vector<double> free_space;
	ProblemInstance test1 = {items, assignments, free_space}, expected_result;
	
	// next_fit
	expected_result = {items, {1, 1, 2, 2, 3, 3, 4, 4}, {0.1, 0.2, 0.1, 0.0}};
	testAlgorithm(test1, expected_result, next_fit, "next_fit"); 

	// first_fit
	expected_result = {items, {1, 1, 2, 2, 3, 2, 4, 4}, {0.1, 0.0, 0.3, 0.0}};
	testAlgorithm(test1, expected_result, first_fit, "first_fit"); 

	// first_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 3, 2, 1, 4}, {0.0, 0.0, 0.0, 0.4}};
	testAlgorithm(test1, expected_result, first_fit_decreasing, "first_fit_decreasing"); 

	// best_fit
	expected_result = {items, {1, 1, 2, 2, 3, 2, 4, 4}, {0.1, 0.0, 0.3, 0.0}};
	testAlgorithm(test1, expected_result, best_fit, "best_fit"); 

	// // best_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 3, 2, 1, 4}, {0.0, 0.0, 0.0, 0.4}};
	testAlgorithm(test1, expected_result, best_fit_decreasing, "best_fit_decreasing");

	// add new tests


	return 0;
}

