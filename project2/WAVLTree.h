#ifndef WAVLTREE_H
#define WAVLTREE_H

// explanations for public member functions are provided in project2.h
// each file that uses a WAVL tree should #include this file 

#include <algorithm>
#include <iostream>
#include <float.h>

template <typename KeyType, typename ValType>
class WAVLTree {
	public:
		// DO NOT MODIFY PUBLIC MEMBERS BELOW THIS LINE
		WAVLTree();
		~WAVLTree();
		void insert(KeyType key, ValType val);
		ValType find(const KeyType& key);
		int getSize();
		int getHeight();
		int getRank(const KeyType& key);
		// DO NOT MODIFY PUBLIC MEMBERS ABOVE THIS LINE

		// define new public members
		ValType get_root_brc()								const;
		KeyType add_item(ValType v);
		class TreeNode {
			public: 
				TreeNode() {}
				TreeNode(TreeNode *parent_node) : key(KeyType()), value(ValType()), 
												parent(parent_node), left(nullptr), right(nullptr),
												rank(0) {}
				TreeNode *left, *right, *parent;
				KeyType key;
				ValType value;
				double rc = 1.0;
				double brc = 0.0;
				int rank = 0;
		};

		void print_inorder();
		bool is_empty();
		void remove(const KeyType &key);

	private:
		// define new private member function
		TreeNode *find_key(TreeNode *node, const KeyType &key)							const;
		void make_dummies(TreeNode *parent_node);
		void update_brc(TreeNode *of_node);
		void promote(TreeNode *node_to_promote);
		void demote(TreeNode *node_to_demote);
		bool is_type(TreeNode *node, int left_rank, int right_rank)						const;
		int height(TreeNode *node) 														const;
		void rebalance(TreeNode *node_to_balance);
		void inorder(TreeNode *node);
		void print_info(TreeNode *of_node);
		void delete_tree(TreeNode *&node);
		void single_left_rotate(TreeNode *node);
		void single_right_rotate(TreeNode *node);
		void trinode_left_right(TreeNode *node_x, TreeNode *node_y, TreeNode *node_z);
		void trinode_right_left(TreeNode *node_x, TreeNode *node_y, TreeNode *node_z);
		bool lte_v(const ValType &v1, const ValType &v2)								const;
		void remove_node(TreeNode *node, const KeyType &key);
		TreeNode *find_left_most(TreeNode *node)										const;
		TreeNode *find_lte_v(TreeNode *node, ValType &item_to_add)						const;

		// member variable
		TreeNode *root;
		int tree_size = 0;
};

// fill in the definitions for each public member function and for any additional public/private members you define

template <typename KeyType, typename ValType>
WAVLTree<KeyType, ValType>::WAVLTree()
{
	this->root = new TreeNode(nullptr);
}


template <typename KeyType, typename ValType>
WAVLTree<KeyType, ValType>::~WAVLTree()
{
	delete_tree(this->root);
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::insert(KeyType key, ValType val)
{
	if (this->root->rank == 0) {
		this->root->key = key;
		this->root->value = val;
		this->root->rc = 1.0 - val;
		this->root->brc = 1.0 - val;
		promote(this->root);
		make_dummies(this->root);
		update_brc(this->root);
	} else {
		TreeNode *node_to_insert = find_key(this->root, key);
		node_to_insert->key = key;
		node_to_insert->value = val;
		node_to_insert->rc = 1.0 - val;
		node_to_insert->brc = 1.0 - val;
		promote(node_to_insert);
		make_dummies(node_to_insert);
		rebalance(node_to_insert->parent);
		update_brc(node_to_insert);
	}
	++this->tree_size;
}

template <typename KeyType, typename ValType>
ValType WAVLTree<KeyType, ValType>::find(const KeyType& key)
{
	TreeNode *node = find_key(this->root, key);
	return node ? node->value : -1;
}
template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::getSize()
{
	return this->tree_size;
}

template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::getHeight()
{
	return height(this->root);
}

template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::getRank(const KeyType& key)
{
	TreeNode *node = find_key(this->root, key);
	return node ? node->rank : -1;
}

// add definitions for any public/private members if needed
template<typename KeyType, typename ValType>
typename WAVLTree<KeyType, ValType>::TreeNode *WAVLTree<KeyType, ValType>::find_key(TreeNode *node, const KeyType &key) const {
	if (node->key == key || node->rank == 0)
		return node;
	if (node->key > key)
		return find_key(node->left, key);
	else 
		return find_key(node->right, key);
}

/*
	Make dummy nodes for a node. An external node is a node with no dummy children
	An internal node is visualized as below, where 0 is an external node
		A
	  /	  \
	 0	   0
*/
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::make_dummies(TreeNode *parent_node) {
	parent_node->left = new TreeNode(parent_node);
	parent_node->right = new TreeNode(parent_node);
}

// update the best remaining capacity of a node
// performed on newly inserted nodes and at rebalancing tree.
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::update_brc(TreeNode *of_node) {
	if (of_node == nullptr)
		return;
	else {
		double child_brc = std::max(of_node->left->brc, of_node->right->brc);
		of_node->brc = child_brc > of_node->rc ? child_brc : of_node->rc;
		update_brc(of_node->parent);
	}
}

// increment the rank of a node
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::promote(TreeNode *node_to_promote) {
	++node_to_promote->rank;
}

// decrement the rank of a node
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::demote(TreeNode *node_to_demote) {
	--node_to_demote->rank;
}

template<typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::height(TreeNode *node) const {
	if (node->rank == 0)
		return 0;
	return 1 + std::max(height(node->left), height(node->right));
}

// debugging function
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::inorder(TreeNode *node) {
	if (node == nullptr)
		return;
	else {
		inorder(node->left);
		print_info(node);
		inorder(node->right);
	}
}

// debugging function
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::print_inorder() {
	std::cout << "This root is " << this->root->key << std::endl;
	inorder(this->root);
}

// debugging function
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::print_info(TreeNode *node) {
	std::cout << "Key: " << node->key << " ";
	std::cout << "Val: " << node->value << std::endl;
	std::cout << "RC : " << node->rc << " ";
	std::cout << "BRC: " << node->brc << std::endl;
	std::cout << "Rnk: " << node->rank << std::endl;
	if (node->parent)
		std::cout << "Par: " << node->parent->key << std::endl;
	if (node->left)
		std::cout << "Lef: " << node->left->key << std::endl;
	if (node->right)
		std::cout << "Rig: " << node->right->key << std::endl;
	std::cout << std::endl;
}

template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::delete_tree(TreeNode *&node) {
	if (node == nullptr)
		return;
	else if (node->left == nullptr && node->right == nullptr) {
		delete node;
		node = nullptr;
	} else {
		delete_tree(node->left);
		delete_tree(node->right);
		delete_tree(node);
	}
}

// determine the type of the node, i.e. 1,1-node, 1,2-node, 2,2-node
template<typename KeyType, typename ValType>
bool WAVLTree<KeyType, ValType>::is_type(TreeNode *node, int left_rank, int right_rank) const{
	int l = node->rank - node->left->rank;
	int r = node->rank - node->right->rank;
	return (left_rank == l & right_rank == r) ? true : false;
}

// rebalance based on rank
// performed after insertion
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::rebalance(TreeNode *node) {
	if (node == nullptr)
		return;

	if (is_type(node, 1, 0) || is_type(node, 0, 1)) {
		promote(node);
		rebalance(node->parent);
	}

	if (is_type(node, 2, 0)) {
		if (is_type(node->right, 2, 1)) {
			demote(node);
			single_left_rotate(node);
		} else if (is_type(node->right, 1, 2)) {
			demote(node);
			demote(node->right);
			promote(node->right->left);
			trinode_right_left(node, node->right, node->right->left);
		}
	}

	if (is_type(node, 0, 2)) {
		if (is_type(node->left, 1, 2)) {
			demote(node);
			single_right_rotate(node);
		} else if (is_type(node->left, 2, 1)) {
			demote(node);
			demote(node->left);
			promote(node->left->right);
			trinode_left_right(node, node->left, node->left->right);
		}
	}
}

template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::single_left_rotate(TreeNode *node) {
	TreeNode *node_right = node->right;
	TreeNode *node_right_child = node_right->left;
	TreeNode *parent_node = node->parent;

	if (this->root == node) {
		node->right = node_right_child;
		node_right_child->parent = node;
		node->parent = node_right;
		this->root = node_right;
		this->root->left = node;
		this->root->parent = nullptr;
		update_brc(node);
	} else {
		node->right = node_right_child;
		node_right_child->parent = node;
		node->parent = node_right;
		node_right->left = node;
		parent_node->right = node_right;
		node_right->parent = parent_node;
		update_brc(node);
	}
}

/*
					A	<- node								B
	              /	  \									  /	  \
	node_left->	B	   \								 C	   A
			  /	  \		\					--->	   /  \   / \
			C	   \	 \							  X	   X X	 X
		  /	  \	    \	  X
		 X	   X	 X	<- node_left_child
*/

template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::single_right_rotate(TreeNode *node) {
	TreeNode *node_left = node->left;
	TreeNode *node_left_child = node_left->right;
	TreeNode *parent_node = node->parent;

	if (this->root == node) {
		node->left = node_left_child;
		node_left_child->parent = node;
		node_left->right = node;
		node->parent = node_left;
		this->root = node_left;
		this->root->parent = nullptr;
		update_brc(node);
	} else {
		node->left = node_left_child;
		node_left_child->parent = node;
		node->parent = node_left;
		node_left->right = node;
		node_left->parent = parent_node;
		parent_node->left = node_left;
		update_brc(node);
	}
}

/*
				X							Z
			  /   \						  /	  \
			 Y	   \					 Y	   X
		   /   \	O		-->		   /   \ /   \
		  /	    Z					  O	   O O	  O
		 O	  /   \
	   zl->	 O	   O  <-zr
*/
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::trinode_left_right(TreeNode *x, TreeNode *y, TreeNode *z) {
	TreeNode *parent_node = x->parent;
	TreeNode *zl = z->left;
	TreeNode *zr = z->right;

	x->left = zr;
	zr->parent = x;
	y->right = zl;
	zl->parent = y;
	z->left = y;
	z->right = x;
	x->parent = z;
	y->parent = z;
	if (this->root == x) {
		this->root = z;
		this->root->parent = nullptr;
	} else {
		parent_node->left = z;
		z->parent = parent_node;
	}
	update_brc(x);
	update_brc(y);
	update_brc(z);
}

template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::trinode_right_left(TreeNode *x, TreeNode *y, TreeNode *z) {
	TreeNode *parent_node = x->parent;
	TreeNode *zl = z->left;
	TreeNode *zr = z->right;

	x->right = zl;
	zl->parent = x;
	y->left = zr;
	zr->parent = y;
	z->right = y;
	z->left = x;
	x->parent = z;
	y->parent = z;
	if (this->root = x) {
		this->root = z;
		this->root->parent = nullptr;
	} else {
		parent_node->right = z;
		z->parent = parent_node;
	}
	update_brc(x);
	update_brc(y);
	update_brc(z);
}

// return the best remainin capacity of the root
template<typename KeyType, typename ValType>
ValType WAVLTree<KeyType, ValType>::get_root_brc() const{
	return this->root->brc;
}

// add an item to the first bin that fits the item
template<typename KeyType, typename ValType>
KeyType WAVLTree<KeyType, ValType>::add_item(ValType v) {
	TreeNode *node = find_lte_v(this->root, v);
	if (node) {
		node->value += v;
		node->rc = 1.0 - node->value;
		update_brc(node);
		return node->key;
	}
	return -1;
}

// float less than or equal comparison
template<typename KeyType, typename ValType>
bool WAVLTree<KeyType, ValType>::lte_v(const ValType &v1, const ValType &v2) const{
	return (std::abs(v1 - v2) < DBL_EPSILON || v1 < v2);
}


// finding the node that has the value that is less than or equal to item_to_add
template<typename KeyType, typename ValType>
typename WAVLTree<KeyType, ValType>::TreeNode *WAVLTree<KeyType, ValType>::find_lte_v(TreeNode *node, ValType &item_to_add) const{
	if (node->rank == 0)
		return nullptr;  
	if (lte_v(item_to_add, node->left->brc)) 
		return find_lte_v(node->left, item_to_add);
	if (lte_v(item_to_add, node->brc) && lte_v(item_to_add, node->rc)) 
		return node;
	else
		return find_lte_v(node->right, item_to_add);
}

template<typename KeyType, typename ValType>
bool WAVLTree<KeyType, ValType>::is_empty(){
	return this->tree_size == 0;
}

template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::remove(const KeyType &key){
	remove_node(this->root, key);
}

// Unfinished
template<typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::remove_node(TreeNode *node, const KeyType &key){
	if (node->rank == 0)
		return;
	else if (node->key > key)
		remove_node(node->left, key);
	else if (node->key < key)
		remove_node(node->right, key);
	else {
		if (node->left->rank == 0 && node->right->rank == 0){
			delete node->left;
			delete node->right;
			node = new TreeNode(node->parent);
			// rebalance
		} else if (node->left->rank != 0) { // has left_child
			TreeNode *p = node->parent;
			TreeNode *left_child = node->left;
			left_child->parent = p;
			if (node == p->left)	
				p->left = left_child;
			else if (node == p->right)
				p->right = left_child;
			left_child->rank = node->rank;
			
			node->left = nullptr;
			delete node->right;
			delete node;
			node = nullptr;
			//rebalance(p)
		} else if (node->right->rank != 0) { // has right_child
			TreeNode *p = node->parent;
			TreeNode *right_child = node->right;
			right_child->parent = p;
			if (node == p->left)
				p->left = right_child;
			else if (node == p->right)
				p->right = right_child;

			right_child->rank = node->rank;
			node->right = nullptr;
			delete node->left;
			delete node;
			node = nullptr;
			// rebalance(p)
		} else {
			// TreeNode *to_replace = find_left_most(node->right);
			// TreeNode *p = to_replace->parent;
			// TreeNode *right_child = to_replace->right;

			// right_child->parent = p
			// node->key = to_replace->key
			// node->value = to_replace->value

			// if (to_replace == p->left)
			//	p->left = right_child
			// else if (to_replace == p->right)
			//	p->right = right_child

			// to_replace->right = nullptr
			// delete to_replace->left
			// delete to_replace
			// to_replace = nullptr
			// rebalance(p)
		}
	}
}

// finding the left most node.
// performed in deletion of a node that has two children
template<typename KeyType, typename ValType>
typename WAVLTree<KeyType, ValType>::TreeNode *WAVLTree<KeyType, ValType>::find_left_most(TreeNode *node) const{
	TreeNode *current = node;
	while (current->left->rank != 0)
		current = current->left;
	return current;
}
#endif /* WAVLTREE_H */