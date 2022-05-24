#include "BSTree.h"
#include <iostream>

using namespace std;

/**
 * @brief 			constructor
 * @param pair 		pair for the new node
 */
BSTree::BSTree(Pair* pair) {
	this->pair = pair;
	left = NULL;
	right = NULL;
}

/**
 * @brief 			insert pair in tree - subtree
 * @param node 		tree node pointer
 * @param pair 		pair to insert
 * @return BSTree* 	if pair is successfully inserted in tree return node pointer, else null
 */
BSTree* BSTree::insert(BSTree* node, Pair* pair) {    
	if(!node) {
        node = new BSTree(pair);
		return node;
	}
    else { // if pair is not present in tree
		if (*node->pair == *pair) // if pair is already in array
			node->pair->increment_occurrences();
		else if (*node->pair < *pair)
			node->right = insert(node->right, pair); // move to right child
		else
			node->left = insert(node->left, pair); // move to left child
	}
	return node;
}

/**
 * @brief 			search pair in tree - subtree
 * @param node 		tree node pointer
 * @param pair 		pair to search
 * @return BSTree* 	if pair is found in tree return node pointer, else null
 */
BSTree*  BSTree::search(BSTree* node, Pair* pair) {
	if (!node || *node->pair == *pair) // if pair is found or node is null
        return node;
    else {
		if (*node->pair < *pair)
			return search(node->right, pair); // move to right child
		else
			return search(node->left, pair); // move to left child
	}
}

/**
 * @brief 			find the leftmost leaf-node
 * @param node 		tree node pointer
 * @return BSTree* 	leftmost node
 */
BSTree* BSTree::inorder_successor(BSTree* node) {
    while (node->left)
        node = node->left;
    return node;
}

/**
 * @brief 			remove pair from tree - subtree
 * @param node 		tree node pointer
 * @param pair 		pair to remove
 * @return BSTree* 	result tree node
 */
BSTree*  BSTree::remove(BSTree* node, Pair* pair) {
    if (!node)
		return node;
	if (*pair < *node->pair)
        node->left = remove(node->left, pair); // move to left child
    else if (*pair > *node->pair)
        node->right = remove(node->right, pair); // move to right child
	else {
		if (!node->left && !node->right) // no childs
            node = NULL;
        else if (!node->left) { // one right child
            BSTree* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) { // one left child
            BSTree* temp = node->left;
            delete node;
            return temp;
        }
		else { // two left and right childs
			BSTree* temp = inorder_successor(node->right); // find inorder succesor and replace node
			node->pair = temp->pair;
			node->right = remove(node->right, temp->pair);
		}
	}
	return node;
}

/**
 * @brief 			in order print of tree pairs 
 * @param node 		tree node pointer
 */
void BSTree::print(BSTree * node) {
    if (node) { 
        print(node->left);
	    cout << *node->pair << endl;
	    print(node->right);
    }
}