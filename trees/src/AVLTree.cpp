#include "AVLTree.hpp"

unsigned int AVLTree::get_h(node* p) const {
    return p?p->height:0;
}

int AVLTree::bfactor(node* p) const {
    return get_h(p->right)-get_h(p->left);
}

void AVLTree::fixheight(node* p) {
    unsigned int hl = get_h(p->left);
	unsigned int hr = get_h(p->right);
	p->height = (hl>hr?hl:hr)+1;
}


AVLTree::node* AVLTree::rotate_r(node* p){
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

AVLTree::node* AVLTree::rotate_l(node* q){
    node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

AVLTree::node* AVLTree::balance(node* p){
    fixheight(p);
    if(bfactor(p) == 2){
        if(bfactor(p->right) < 0) p->right = rotate_r(p->right);
        return rotate_l(p);
    }
    if(bfactor(p) == -2){
        if(bfactor(p->left) > 0) p->left = rotate_l(p->left);
        return rotate_r(p);
    }
    return p; //если балансировка не нужна
}

AVLTree::node* AVLTree::insert(node* p, int k){
    if(!p) return new node(k);
	if(k < p->key)
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}

AVLTree::node* AVLTree::findmin(node* p){
    return p->left?findmin(p->left):p;
}

AVLTree::node* AVLTree::removemin(node* p){
    if (p->left==0) return p->right;
    p -> left = removemin(p->left);
    return balance(p);
}

AVLTree::node* AVLTree::remove(node* p, int k){
    if(!p) return 0;
	if( k < p->key )
		p->left = remove(p->left,k);
	else if( k > p->key )
		p->right = remove(p->right,k);	
	else
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void AVLTree::clear(node* p) {
    if (!p) return;
    clear(p->left);
    clear(p->right);
    delete p;

}

void AVLTree::in_order(node* p, std::vector<int>& values) const{
    if(!p) return;
    in_order(p->left, values);
    values.push_back(p->key);
    in_order(p->right, values); 
}



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

