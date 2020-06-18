#include "graph.h"
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <random>
#include <iostream>

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v){
    Graph to_return;
    for (int i = 0; i < num_nodes; ++i)
        to_return.id_to_node[i+1] = Node(i+1);

    for (int i = 0; i < u.size(); ++i){
        to_return.id_to_node[u[i]].connect(to_return.id_to_node[v[i]]);
        to_return.id_to_node[v[i]].connect(to_return.id_to_node[u[i]]);
        to_return.add_edge(u[i], v[i]);
    }

    return to_return;
}

int Graph::get_num_nodes() {
	return id_to_node.size();
}

int Graph::get_num_edges() {
    return edges.size();
}

std::vector<Node> Graph::get_neighbors(Node u) {
    std::vector<Node> to_return;
    for (const int i : u.neighbors)
        to_return.push_back(this->id_to_node[i]);
    return to_return;
}

std::map<int, Node>Graph::get_id_to_node_map(){
    return id_to_node;
}

Graph::Graph() {
}

void Graph::add_edge(int u, int v) {
    this->edges.insert(std::make_pair(u,v));
}

std::pair<int,int> Graph::bfs(const Node &node) {
    std::queue<std::pair<int, int>> container;
    container.push(std::make_pair(node.id, 0));
    std::unordered_set<int> seen;
    std::pair<int, int> last_pair = container.front();
    seen.insert(node.id);
    while (!container.empty()){
        int current_id = container.front().first;
        int current_depth = container.front().second;
        std::vector<int> current_neighbors = id_to_node[current_id].neighbors;
        for (const int n : current_neighbors)
            if (seen.find(n) == seen.end()) {
                container.push(std::make_pair(n, current_depth+1));
                seen.insert(n);
            }
        last_pair = container.front();
        container.pop();
    }
    return last_pair;
}

int Graph::get_two_edges_path() const {
    int count = 0;
    for (const auto &kv : this->id_to_node) {
        int degree = kv.second.degree;
        count += degree * (degree - 1) / 2;
    }
    return count;
}

int Graph::get_triangels() {
    // initialize output list L
    std::list<int> L;

    // initialize dv for each vertex - number of neighbors not in L
    // pair (node_id, degree)
    std::unordered_map<int,int> d;
    for (const auto &kv : this->id_to_node)
        d[kv.first] = kv.second.degree;

    std::unordered_map<int, std::list<int>> D;
    for (const auto &kv : d)
        D[kv.second].push_back(kv.first);

    // initialize a list of the neighbors of v that come before v in L
    std::vector<std::vector<int>> N(this->id_to_node.size()+1);

    std::unordered_set<int> in_L;

    for (int j = 0; j < this->id_to_node.size(); ++j) {
        int i;
        // find the first D[i] that is not empty
        for (i = 0; i < D.size(); ++i)
            if (!D[i].empty())
                break;
        // select v from D[i]
        int v = D[i].front();
        // Add v to beginning of L
        L.push_front(v);
        // Remove v from D[i]
        D[i].remove(v);
        // Mark v as being in L
        in_L.insert(v);

        std::vector<int> neighbors = id_to_node[v].neighbors;
        for (int w : neighbors) {
            if (in_L.find(w) == in_L.end()) {
                int degree_w = d[w];
                // subtract one from dw
                d[w] -= 1;
                // remove w from D
                D[degree_w].remove(w);
                // "move" w to the cell of D corresponding to the new value of dw
                D[d[w]].push_back(w);
                // Add w to Nv
                N[v].push_back(w);
            }
        }
    }

    int triangles = 0;
    for (int v : L) {
        if (N[v].size() > 1) {
            for (int k = 0; k < N[v].size()-1; ++k){
                int u = N[v][k];
                int w = N[v][k+1];
                if (this->edges.find(std::make_pair(u,w)) != this->edges.end() ||
                this->edges.find(std::make_pair(w,u)) != this->edges.end())
                    ++triangles;
            }
        }
    }
    return triangles;
}

double draw_r(const double a, const double b) {
    std::random_device device;
    std::default_random_engine engine{device()};

    std::uniform_real_distribution<double> distribution{a,b};
    for (int i = 0; i < 10; ++i) {
        double r = distribution(engine);
        if ((1.0 - r) > 0.0001)
            return r;
    }
    return 0.0;
}

Graph G(int n, double p) {
    Graph g;

    int v = 1,
        w = -1;

    for (int i = 0; i < n; ++i)
        g.id_to_node[i] = Node(i);

    while (v < n) {
        //std::cout << v << std::endl;
        double r = draw_r(0,1);
        double ans = std::log(1-r)/std::log(1-p);
        w += 1 + std::floor(ans);

        while (w >= v && v < n){
            w -= v;
            ++v;
        }

        if (v < n) {
            g.id_to_node[v].connect(g.id_to_node[w]);
            g.id_to_node[w].connect(g.id_to_node[v]);
            g.add_edge(v,w);
        }
    }
    std::cout << "Returning g" << std::endl;
    return g;
}

Graph BA(int n, int d) {
    Graph g;
    for (int i = 0; i < n; ++i)
        g.id_to_node[i] = Node(i);

    std::vector<int> M(2*d*n,0);

    for (int v = 0; v < n; ++v)
        for (int i = 0; i < d; ++i){
            int index = 2*(v*d+i);
            M[index] = v;
            int r = static_cast<int>(draw_r(0.0, index));
            M[index + 1] = M[r];
        }

    for (int i = 0; i < n*d; ++i){
        g.id_to_node[M[2*i]].connect(g.id_to_node[M[2*i+1]]);
        g.id_to_node[M[2*i+1]].connect(g.id_to_node[M[2*i]]);
        g.add_edge(M[2*i], M[2*i+1]);
    }

    return g;
}
Graph::~Graph() = default;

