#ifndef NODE_H
#define NODE_H

#include <vector>
class Node {
	public:
		// DO NOT MODIFY MEMBERS BELOW THIS LINE 
		bool operator==(const Node& other) const {return id == other.id;} 	// used for comparing two nodes, already implemented	
		int id; 															// uniquely identifies a node (no two nodes have the same id).
				   															// id must be set in the constructor and thereafter not modified
		// DO NOT MODIFY MEMBERS ABOVE THIS LINE 

	    // you should declare a constructor/any other members you need
	    // implement any newly declared member functions in node.cpp
        Node();
        ~Node();
        Node(int id, int degree=0) : id(id), degree(degree) {}
        void connect(const Node &node);
        std::vector<int> neighbors;
        int degree{};
};

#endif
