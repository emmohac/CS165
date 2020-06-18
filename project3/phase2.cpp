// Instructions:
//
// Move all source code/header files you will be submitting to a new directory, along with the two files Makefile and project3_tests.cpp
// Edit the main function to create and try different test cases on your algorithms
// Enter the command "make" to compile and run the program
// If you make any changes to any of the files, enter the command "make clean" to remove the generated executable before entering "make" again.
//
// note that passing the test cases here does not necessarily mean your algorithms will pass other test cases
// so it's a good idea to create and try different test cases

#include "project3.h"
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

void message(string s)
{
    cout << s << "\n";
}

void newline()
{
    cout << "\n";
}

bool floating_compare(float a, float b)
{
    return std::fabs(a-b) < 1e-3;
}

bool vectors_have_same_nodes(vector<Node> nodes1, vector<Node> nodes2)
{
    sort(nodes1.begin(), nodes1.end(), [](const Node& u, const Node& v){return u.id < v.id;});
    sort(nodes2.begin(), nodes2.end(), [](const Node& u, const Node& v){return u.id < v.id;});
    return nodes1 == nodes2;
}

int main()
{
    /*
    message(string("*******************************************")
            + string("\ngraph interface\n")
            + string("*******************************************"));

    message("0 nodes, 0 edges");
    message("Testing graph = Graph()");
    Graph graph;
    map<int, Node> id_to_node;
    message("Testing graph returns get_num_nodes() == 0");
    assert (graph.get_num_nodes() == 0);
    message("Testing graph returns get_num_edges() == 0");
    assert (graph.get_num_edges() == 0);

    newline();
    message("For each of the following graphs, we will use the shorthand (n, {(u1, v1), ... , (um, vm)}) to denote make_graph(n, vector<int>{u1, ... , um}, vector<int>{v1, ... , vm})");
    message("(n, {}) denotes make_graph(n, vector<int>{}, vector<int>{}), meaning the vectors are empty");
    message("Any vector<Node> will be shown sorted by node id");

    newline();
    message("0 nodes, 0 edges");
    message("Testing graph = (0, {})");
    graph = make_graph(0, vector<int>{}, vector<int>{});
    message("Testing graph returns get_num_nodes() == 0");
    assert (graph.get_num_nodes() == 0);
    message("Testing graph returns get_num_edges() == 0");
    assert (graph.get_num_edges() == 0);

    newline();
    message("1 node, 0 edges");
    message("Testing graph = (1, {})");
    graph = make_graph(1, vector<int>{}, vector<int>{});
    message("Testing graph returns get_num_nodes() == 1");
    assert (graph.get_num_nodes() == 1);
    message("Testing graph returns get_num_edges() == 0");
    assert (graph.get_num_edges() == 0);

    newline();
    message("2 nodes, 0 edges");
    message("Testing graph = (2, {})");
    graph = make_graph(2, vector<int>{}, vector<int>{});
    message("Testing graph returns get_num_nodes() == 2");
    assert (graph.get_num_nodes() == 2);
    message("Testing graph returns get_num_edges() == 0");
    assert (graph.get_num_edges() == 0);
    id_to_node = graph.get_id_to_node_map();
    message("Testing graph returns get_neighbors(id_to_node[1]) == vector<Node>{}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[1]), vector<Node>{}));
    message("Testing graph returns get_neighbors(id_to_node[2]) == vector<Node>{}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[2]), vector<Node>{}));

    newline();
    message("2 nodes, 1 edge");
    message("Testing graph = (2, {(1, 2)})");
    graph = make_graph(2, vector<int>{1}, vector<int>{2});
    message("Testing graph returns get_num_nodes() == 2");
    assert (graph.get_num_nodes() == 2);
    message("Testing graph returns get_num_edges() == 1");
    assert (graph.get_num_edges() == 1);
    id_to_node = graph.get_id_to_node_map();
    message("Testing graph returns get_neighbors(id_to_node[1]) == vector<Node>{id_to_node[2]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[1]), vector<Node>{id_to_node[2]}));
    message("Testing graph returns get_neighbors(id_to_node[2]) == vector<Node>{id_to_node[1]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[2]), vector<Node>{id_to_node[1]}));

    newline();
    message("3 nodes, 0 edges");
    message("Testing graph = (3, {})");
    graph = make_graph(3, vector<int>{}, vector<int>{});
    message("Testing graph returns get_num_nodes() == 3");
    assert (graph.get_num_nodes() == 3);
    message("Testing graph returns get_num_edges() == 0");
    assert (graph.get_num_edges() == 0);
    id_to_node = graph.get_id_to_node_map();
    message("Testing graph returns get_neighbors(id_to_node[1]) == vector<Node>{}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[1]), vector<Node>{}));
    message("Testing graph returns get_neighbors(id_to_node[2]) == vector<Node>{}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[2]), vector<Node>{}));
    message("Testing graph returns get_neighbors(id_to_node[3]) == vector<Node>{}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[3]), vector<Node>{}));

    newline();
    message("3 nodes, 1 edge");
    message("Testing graph = (3, {(2, 3)})");
    graph = make_graph(3, vector<int>{2}, vector<int>{3});
    message("Testing graph returns get_num_nodes() == 3");
    assert (graph.get_num_nodes() == 3);
    message("Testing graph returns get_num_edges() == 1");
    assert (graph.get_num_edges() == 1);
    id_to_node = graph.get_id_to_node_map();
    message("Testing graph returns get_neighbors(id_to_node[1]) == vector<Node>{}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[1]), vector<Node>{}));
    message("Testing graph returns get_neighbors(id_to_node[2]) == vector<Node>{id_to_node[3]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[2]), vector<Node>{id_to_node[3]}));
    message("Testing graph returns get_neighbors(id_to_node[3]) == vector<Node>{id_to_node[2]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[3]), vector<Node>{id_to_node[2]}));

    newline();
    message("3 nodes, 2 edges");
    message("Testing graph = (3, {(1, 2), (2, 3)})");
    graph = make_graph(3, vector<int>{1, 2}, vector<int>{2, 3});
    message("Testing graph returns get_num_nodes() == 3");
    assert (graph.get_num_nodes() == 3);
    message("Testing graph returns get_num_edges() == 2");
    assert (graph.get_num_edges() == 2);
    id_to_node = graph.get_id_to_node_map();
    message("Testing graph returns get_neighbors(id_to_node[1]) == vector<Node>{id_to_node[2]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[1]), vector<Node>{id_to_node[2]}));
    message("Testing graph returns get_neighbors(id_to_node[2]) == vector<Node>{id_to_node[1], id_to_node[3]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[2]), vector<Node>{id_to_node[1], id_to_node[3]}));
    message("Testing graph returns get_neighbors(id_to_node[3]) == vector<Node>{id_to_node[2]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[3]), vector<Node>{id_to_node[2]}));

    newline();
    message("3 nodes, 3 edges");
    message("Testing graph = (3, {(1, 2), (2, 3), (1, 3)})");
    graph = make_graph(3, vector<int>{1, 2, 1}, vector<int>{2, 3, 3});
    message("Testing graph returns get_num_nodes() == 3");
    assert (graph.get_num_nodes() == 3);
    message("Testing graph returns get_num_edges() == 3");
    assert (graph.get_num_edges() == 3);
    id_to_node = graph.get_id_to_node_map();
    message("Testing graph returns get_neighbors(id_to_node[1]) == vector<Node>{id_to_node[2], id_to_node[3]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[1]), vector<Node>{id_to_node[2], id_to_node[3]}));
    message("Testing graph returns get_neighbors(id_to_node[2]) == vector<Node>{id_to_node[1], id_to_node[3]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[2]), vector<Node>{id_to_node[1], id_to_node[3]}));
    message("Testing graph returns get_neighbors(id_to_node[3]) == vector<Node>{id_to_node[1], id_to_node[2]}");
    assert (vectors_have_same_nodes(graph.get_neighbors(id_to_node[3]), vector<Node>{id_to_node[1], id_to_node[2]}));
    message("Testing graph returns get_degree_distribution == {{2,3}}");

    newline();
    message(string("*******************************************")
            + string("\nnetwork algorithms\n")
            + string("*******************************************"));
    message("Testing graph = (3, {(1, 2), (1, 3), (2, 3)})");
    newline();
    graph = make_graph(3, vector<int>{1, 2}, vector<int>{2, 3});
    message("Testing graph returns get_diameter(graph) == 2");
    assert (get_diameter(graph) == 2);
    message("Testing graph returns get_clustering_coefficient(graph) == 0");
    assert(floating_compare(get_clustering_coefficient(graph), 0));
    message("Testing graph returns get_degree_distribution == {{1, 2}, {2, 1}}");
    assert (get_degree_distribution(graph) == (std::map<int, int>{{1, 2}, {2, 1}}));
    message("Testing graph = (10, {(1, 4), (1, 8), (2, 5), (2, 6), (2,7), (3, 4), (3, 8), (4, 5), (4, 9), (4,10), (5, 6), (5, 10), (6, 7), (9, 10)}");
    newline();
    graph = make_graph(10, vector<int>{1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 9},
                                     vector<int>{4, 8, 5, 6, 7, 4, 8, 5, 9, 10, 6, 10, 7, 10});
    message("Testing graph returns get_diameter(graph) == 5");
    assert (get_diameter(graph) == 5);
    message("Testing graph returns get_clustering_coefficient(graph) == 0.4");
    assert(floating_compare(get_clustering_coefficient(graph), 0.4));
    message("Testing graph returns get_degree_distribution == {{2, 5}, {3, 3}, {4, 1}, {5, 1}}");
    assert (get_degree_distribution(graph) == (std::map<int, int>{{2, 5}, {3, 3}, {4, 1}, {5, 1}}));
    newline();

    message(string("+++++++++++++++++++++++++++++++++++++++++++")
            + string("\nall tests passed!\n")
            + string("+++++++++++++++++++++++++++++++++++++++++++"));
    newline();
    message(string("+++++++++++++++++++++++++++++++++++++++++++")
            + string("\nTesting Erdos-Renyi\n")
            + string("+++++++++++++++++++++++++++++++++++++++++++"));
    int n = 100;
    double p = 2*std::log(n) / n;

    Graph g = G(n, p);
    message("Number of node: ");
    std::cout << g.get_num_nodes() << std::endl;
    message("Number of edge: ");
    std::cout << g.get_num_edges() << std::endl;
    message("Diameter: ");
    std::cout << get_diameter(g) << std::endl;
    message("Clustering coefficient: ");
    std::cout << get_clustering_coefficient(g) << std::endl;

    message(string("+++++++++++++++++++++++++++++++++++++++++++")
            + string("\nErdos-Renyi passed\n")
            + string("+++++++++++++++++++++++++++++++++++++++++++"));
            */
    const int COUNTER = 5;
    std::ofstream er_file;
    er_file.open("er_100k.csv", std::ofstream::app | std::ofstream::out);
    //std::string header = "size,diameter,clus_coef\n";
    std::string header = "degree,vertices\n";
    er_file << header;

    // for (int i = 3; i < 18; ++i){
    //     std::cout << "i: " << i << std::endl;
         //int N = std::pow(2,i);
         std::map<int,int> degree_dist;
         int N = 100000;
         double P = 2 * std::log(N)/N;
    //     int d = 0;
    //     float cc = 0.0;
        for (int counter = 0; counter < COUNTER;++counter) {
            std::cout << "Iter: " << counter << std::endl;
            Graph g = G(N,P);
            std::map<int,int> temp = get_degree_distribution(g);
            for (const auto &kv : temp)
                degree_dist[kv.first] += kv.second;
            //d += get_diameter(g);
            //cc += get_clustering_coefficient(g);
        }
    //     std::string to_write = std::to_string(N) + "," + std::to_string(d/COUNTER) + "," + std::to_string(cc/COUNTER) + "\n";
    //     er_file << to_write;
    // }
    for (auto &kv : degree_dist)
        kv.second /= COUNTER;
    for (const auto &kv : degree_dist) {
        std::string to_write = std::to_string(kv.first) + "," + std::to_string(kv.second) +"\n";
        er_file << to_write;
    }
    er_file.close();
    return 0;
}
