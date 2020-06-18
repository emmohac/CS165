#ifndef PROJECT3_H
#define PROJECT3_H

// DO NOT MODIFY THIS FILE 

#include <vector>
#include <map>
#include "graph.h"

/*
 * - implement the functions listed in graph.cpp, node.cpp and graph_algorithms.cpp. explanations for some of these can be found below
 *   you can define new members for the Node/Graph classes 
 *
 * - files that you need to submit:
 *   - node.h
 *   - graph.h
 *   - node.cpp
 *   - graph.cpp
 *   - graph_algorithms.cpp
 *
 * - you can create additional header/source files and submit them alongside the required files
 *
 * - make sure you do not modify any of the public members for Node/Graph classes, as during testing
 *   we will be assuming that these members  have the same types/names
 *
 * - we will be using our own main function while grading, so do NOT submit any files that have a main function defined
 *
 * - the submission should be a zip file consisting of all source code/header files. the zip file should not contain any directories
 *
 */

/******* EXPLANATIONS ********/

// construct a graph using num_nodes nodes and edges (ui, vi) for all i
// implement this function in graph.cpp. you can find an empty definition there
// u and v will be the same length
// (ui, vi) are pairs of integers which can be mapped uniquely to (ui', vi'), pairs of Nodes
// ui, vi values are numbered from 1 to num_nodes, inclusive
// you *must* implement this function for the autograder to work, as we will be calling this function to create Graph instances
Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v);
Graph G(int n, double p);
Graph BA(int n, int d);


// network algorithms
// implement these in graph_algorithms.cpp
int get_diameter(Graph graph); 
float get_clustering_coefficient(Graph graph);
std::map<int, int> get_degree_distribution(Graph graph); // key-value pairs represent {degree, number of nodes with that degree}

#endif
