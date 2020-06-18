#include "graph.h"
#include <random>
#include <iostream>

int get_random_id(Graph graph){
    std::vector<int> id;
    for (const auto &kv : graph.id_to_node)
        if (kv.first != 0)
            id.push_back(kv.first);
    std::random_device device;
    std::default_random_engine engine{device()};
    std::uniform_int_distribution<int> distribution(0, graph.get_num_nodes()-1);
    int random_index = distribution(engine);
    return id[random_index];
}

int get_diameter(Graph graph)
{
    int random_id = get_random_id(graph);
    int d_max = 0;
    Node r = graph.id_to_node[random_id];
    bool changed = true;

    while (changed){
        std::pair<int,int> node_depth = graph.bfs(r);
        int depth = node_depth.second;
        if (depth == d_max)
            changed = false;
        else if (depth > d_max) {
            d_max = depth;
            r = graph.id_to_node[node_depth.first];
        }
    }
    return d_max;
}

float get_clustering_coefficient(Graph graph) 
{
    float to_return = 0.0;
    int triangels = graph.get_triangels();
    int two_edge_path = graph.get_two_edges_path();
    to_return = 3.0*triangels / two_edge_path;
    return to_return;
}

std::map<int, int> get_degree_distribution(Graph graph) 
{
	std::map<int,int> to_return;
    int size = graph.get_num_nodes();
	for (int i = 0; i < size; ++i)
	    to_return[graph.id_to_node[i+1].degree] += 1;
	return to_return;
}
