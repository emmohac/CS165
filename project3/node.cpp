#include "node.h"

// implement member functions for the Node class here
Node::Node() {
    this->degree = 0;
    this->id = 0;
}

Node::~Node() = default;

void Node::connect(const Node &node) {
    this->neighbors.push_back(node.id);
    this->degree = this->neighbors.size();
}