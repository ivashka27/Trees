#include "AVLTree.hpp"

bool AVLTree::contains(int value) const {
	node* curr = root;
    while(curr != 0){
        if (value == curr->key) return true;
        else if (value > curr->key) curr = curr->right;
        else curr = curr->left;
    }
    return false;
}

bool AVLTree::insert(int value) {
    if (contains(value)) return false;
    root = insert(root, value);
    tree_size++;
    return true;
}

bool AVLTree::remove(int value){
    if (!contains(value)) return false;
    root = remove(root, value);
    tree_size--;
    return true;
}



std::size_t AVLTree::size() const{
    return tree_size;
}

bool AVLTree::empty() const{
    if (root) return false;
    return true;
}

std::vector<int> AVLTree::values() const{
    std::vector<int> vals;
    in_order(root, vals);
    return vals;

}




AVLTree::~AVLTree(){
    clear(root);
    root = 0;
    tree_size = 0;
}


unsigned int AVLTree::get_h(node* node) const {
    return node?node->height:0;
}
int AVLTree::bfactor(node* node) const {
    return get_h(node->right)-get_h(node->left);
}

void AVLTree::update_h(node* node) {
    unsigned int hl = get_h(node->left);
	unsigned int hr = get_h(node->right);
	node->height = (hl>hr?hl:hr)+1;
}



AVLTree::node* AVLTree::rotate_r(node* node){
    node* node2 = node->left;
    node->left = node2->right;
    node2->right = node;
    update_h(node);
    update_h(node2);
    return node2;
}
AVLTree::node* AVLTree::rotate_l(node* node){
    node* node2 = node->right;
	node->right = node2->left;
	node2->left = node;
	update_h(node);
	update_h(node2);
	return node2;
}




AVLTree::node* AVLTree::balance(node* node){
    update_h(node);
    if(bfactor(node) == 2){
        if(bfactor(node->right) < 0) p->right = rotate_r(node->right);
        return rotate_l(node);
    }
    if(bfactor(node) == -2){
        if(bfactor(node->left) > 0) node->left = rotate_l(node->left);
        return rotate_r(node);
    }
    return node;
}
AVLTree::node* AVLTree::insert(node* node, int k){
    if(!node) return new node(k);
	if(k < node->key)
		node->left = insert(node->left,k);
	else
		node->right = insert(node->right,k);
	return balance(node);
}


AVLTree::node* AVLTree::findmin(node* node){
    return node->left?findmin(node->left):node;
}
AVLTree::node* AVLTree::removemin(node* node){
    if (node->left==0) return node->right;
    node -> left = removemin(node->left);
    return balance(node);
}




AVLTree::node* AVLTree::remove(node* node, int k){
    if(!node) return 0;
	if( k < node->key )
		node->left = remove(node->left,k);
	else if( k > node->key )
		node->right = remove(node->right,k);	
	else
	{
		node* q = node->left;
		node* r = node->right;
		delete node;
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(node);
}

void AVLTree::clear(node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;

}


void AVLTree::in_order(node* node, std::vector<int>& values) const{
    if(!node) return;
    in_order(node->left, values);
    values.push_back(node->key);
    in_order(node->right, values); 
}

