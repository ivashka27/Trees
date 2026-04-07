#include "AVLTree.hpp"
#include <algorithm>

AVLTree::Node::Node(int value) {  
	key = value;
	right = nullptr;
	left = nullptr;
	height = 0;
}
bool AVLTree::contains(int value) const { 
	Node* current = root;
	while (current != nullptr) { 
		if (value == current->key) {
			return true;
		}
		else if (value < current->key) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return false;
}
bool AVLTree::insert(int value) {
	if (this->contains(value)) { 
		return false;
	}
	root = balance_insert(root, value);
	tree_size += 1;
	return true;
}
bool AVLTree::remove(int value) {
	if (!this->contains(value)) { 
		return false;
	}
	root = removeNode(root, value); 
	tree_size -= 1;
	return true;
}
std::size_t AVLTree::size() const {
	return tree_size;
}
bool AVLTree::empty() const {
	return root == nullptr;
}
std::vector<int> AVLTree::values() const {
	std::vector<int> keys;
	in_order_values(root, keys);
	return keys;
}
AVLTree::~AVLTree() {
	destroy(root);
	root = nullptr;
}
int AVLTree::get_height(Node* node) const {
	if (node == nullptr) {
		return -1;
	}
	else {
		return node->height;
	}
} 
int AVLTree::update_node_height(Node*node) const{
	return std::max(get_height(node->right), get_height(node->left)) + 1;
}
int AVLTree::bf(Node* node) const {
	return get_height(node->left) - get_height(node->right);
}
AVLTree::Node* AVLTree::rightRotate(Node* node) {
	Node* new_root = node->left;
	node->left = new_root->right;
	new_root->right = node;
	node->height = update_node_height(node);
	new_root->height= update_node_height(new_root);
	return new_root;
}
AVLTree::Node* AVLTree::leftRotate(Node* node) {
	Node* new_root = node->right;
	node->right = new_root->left;
	new_root->left = node;
	node->height = update_node_height(node);
	new_root->height = update_node_height(new_root);
	return new_root;
}
AVLTree::Node* AVLTree::doBalance(Node* node) {
	if (bf(node) == 2) {
		if (bf(node->left) >= 0) { // LL
			node = rightRotate(node);
		}
		else { //LR
			node->left = leftRotate(node->left);
			node = rightRotate(node);
		}
	}
	else if (bf(node) == -2) {
		if (bf(node->right) <= 0) { // RR
			node = leftRotate(node);
		}
		else { //RL
			node->right = rightRotate(node->right);
			node = leftRotate(node);
		}
	}
	return node;
}
AVLTree::Node* AVLTree::find_min(Node* node) const {
	while (node->left != nullptr) {
		node = node->left;
	}
	return node;
}
//рекурсивная реализация методов
AVLTree::Node* AVLTree::balance_insert(Node* node, int value) {
	if (node == nullptr) { 
		node = new Node(value);
		return node;
	}
	if (value < node->key) {
		node->left = balance_insert(node->left, value); 
	}
	else {
		node->right = balance_insert(node->right, value); 
	}
	node->height = update_node_height(node); 
	node = doBalance(node); 
	return node; 
}
AVLTree::Node* AVLTree::removeNode(Node* node, int value) {
	if (node == nullptr) { 
		return nullptr;
	}
	if (value < node->key) { 
		node->left = removeNode(node->left, value);
	}
	else if (value > node->key) {
		node->right = removeNode(node->right, value);
	}
	else {
		if (node->right == node->left) { 
			delete node;
			return nullptr;
		}
		else if (node->right != nullptr && node->left == nullptr) {  
			Node* temp = node->right;
			delete node;
			return temp;
		}
		else if (node->right == nullptr && node->left != nullptr) { 
			Node* temp = node->left; 
			delete node;
			return temp;
		}
		else {
			int new_key = find_min(node->right)->key; 
			node->key = new_key;
			node->right = removeNode(node->right, new_key);
		}
	}
	node->height= update_node_height(node); 
	node = doBalance(node); 
	return node;
}
void AVLTree::in_order_values(Node* node, std::vector<int>& values) const{ 
	if (node == nullptr) {
		return;
	}
	in_order_values(node->left, values);
	values.push_back(node->key);
	in_order_values(node->right	, values);
}

void AVLTree::destroy(Node* node) {
	if (node == nullptr) {
		return;
	}
	destroy(node->left);
	destroy(node->right);
	delete node;
}

