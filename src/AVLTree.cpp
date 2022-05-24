#include "AVLTree.h"
#include <iostream>

using namespace std;

/**
 * @brief           constructor
 * @param pair      pair for the new node
 */
AVLTree::AVLTree(Pair* pair) {
    this->pair = pair;
    left = NULL;
    right = NULL;
    height = 1;
}

/**
 * @brief 			find the leftmost leaf-node
 * @param node 		tree node pointer
 * @return AVLTree* 	leftmost node
 */
AVLTree* AVLTree::inorder_successor(AVLTree* node) {
    while (node->left)
        node = node->left;
    return node;
}

/**
 * @brief           get node height
 * @param node      tree node pointer
 * @return int      node height
 */
int AVLTree::get_height(AVLTree* node) {
    if (node)
        return node->height;
    return 0;
}

/**
 * @brief           update node height
 * @param node      tree node pointer
 */
void AVLTree::update_height(AVLTree* node) {
    if (node)
        node->height = max(get_height(node->left), get_height(node->right)) + 1;
}

/**
 * @brief           get node balance factor
 * @param node      tree node pointer
 * @return int      node balance factor
 */
int AVLTree::balance_factor(AVLTree* node) {
    if (node)
        return get_height(node->left) - get_height(node->right);
    return 0;
}

/**
 * @brief           maximum of a and b
 * @return int      max(a, b)
 */
int max(int a, int b) {
    return (a > b) ? a : b; 
}

/**
 * @brief               insert pair in tree - subtree
 * @param node          tree node pointer
 * @param pair          pair to insert
 * @return AVLTree*     if pair is successfully inserted in tree return node pointer, else null
 */
AVLTree* AVLTree::insert(AVLTree* node, Pair* pair) {
    if(!node) {
        node = new AVLTree(pair);
		return node;
	}
    else { // if pair is not present in tree
		if (*node->pair == *pair)
            node->pair->increment_occurrences();
		else if (*node->pair < *pair)
            node->right = insert(node->right, pair);
		else
            node->left = insert(node->left, pair);

        update_height(node);
        int bf = balance_factor(node); 

        // if node is unbalanced, make the required rotations
        if (bf > 1 && *pair < *node->left->pair) // left-left case
            return rotate_right(node);
        else if (bf < -1 && *pair > *node->right->pair) // right-right case
            return rotate_left(node);
        else if (bf > 1 && *pair > *node->left->pair) // left-right case
            return rotate_left_right(node);
        else if (bf < -1 && *pair < *node->right->pair) // right-left case
            return rotate_right_left(node);
	}
	return node;
}

/**
 * @brief               search pair in tree - subtree
 * @param node          tree node pointer
 * @param pair          pair to search
 * @return AVLTree*     if pair is found in tree return node pointer, else null
 */
AVLTree* AVLTree::search(AVLTree* node, Pair* pair) {
	if (!node || *node->pair == *pair) // if pair is found or node is null
        return node;
    else {
		if (*node->pair < *pair)
			return search(node->right, pair);
		else
			return search(node->left, pair);
	}
}

// remove pair from node
/**
 * @brief               remove pair from tree - subtree
 * @param node 		    tree node pointer
 * @param pair 		    pair to remove
 * @return AVLTree*     result tree node
 */
AVLTree* AVLTree::remove(AVLTree* node, Pair* pair) {
    if (!node)
		return node;
	if (*pair < *node->pair)
        node->left = remove(node->left, pair);
    else if (*pair > *node->pair)
        node->right = remove(node->right, pair);
	else { // if pair is found
		if (!node->left && !node->right) // no childs
            node = NULL;
        else if (!node->left) { // one right child
            AVLTree* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) { // one left child
            AVLTree* temp = node->left;
            delete node;
            return temp;
        }
		else { // two left and right childs
			AVLTree* temp = inorder_successor(node->right); // find inorder succesor and replace node
			node->pair = temp->pair;
			node->right = remove(node->right, temp->pair);
		}
	}

    if (!node)
        return node;

    update_height(node);
    int bf = balance_factor(node);

    // if node became unbalanced, make the required rotations
    if (bf > 1 && *pair < *node->left->pair) // left-left case
            return rotate_right(node);
    else if (bf < -1 && *pair > *node->right->pair) // right-right case
        return rotate_left(node);
    else if (bf > 1 && *pair > *node->left->pair) // left-right case
        return rotate_left_right(node);
    else if (bf < -1 && *pair < *node->right->pair) // right-left case
        return rotate_right_left(node);
    return node;
}

/**
 *        z                                y
 *      /  \                            /   \ 
 *     T1   y       left rotation      z      x
 *         /  \   - - - - - - - ->    / \    / \
 *        T2   x                     T1  T2 T3  T4
 *            / \
 *          T3  T4
 */
AVLTree* AVLTree::rotate_left(AVLTree* node) {
    AVLTree *new_root = node->right;
    AVLTree *tmp = new_root->left;
    new_root->left = node;
    node->right = tmp;
    update_height(node);
    update_height(new_root);
    return new_root;
}

/**
 *          z                                      y 
 *         / \                                   /   \
 *        y   T4         right rotation         x      z
 *       / \          - - - - - - - - ->      /  \    /  \ 
 *      x   T3                               T1  T2  T3  T4
 *     / \
 *   T1   T2
 */
AVLTree* AVLTree::rotate_right(AVLTree *node) {
    AVLTree *new_root = node->left;
    AVLTree *tmp = new_root->right;
    new_root->right = node;
    node->left = tmp;
    update_height(node);
    update_height(new_root);
    return new_root;
}

/**
 *           z                                 z                             x
 *          / \                              /   \                          /  \ 
 *         y   T4    left rotation          x    T4   right rotation      y      z
 *        / \        - - - - - - - - ->    /  \       - - - - - - - ->   / \    / \
 *      T1   x                            y    T3                      T1  T2 T3  T4
 *          / \                          / \ 
 *        T2   T3                      T1   T2 
 */
AVLTree* AVLTree::rotate_left_right(AVLTree* node) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
}

/**
 *        z                            z                              x
 *       / \                          / \                            /  \ 
 *     T1   y   right rotation      T1   x      left rotation      z      y
 *         / \  - - - - - - - - ->     /  \   - - - - - - - ->    / \    / \
 *        x   T4                      T2   y                    T1  T2  T3  T4
 *       / \                              /  \
 *     T2   T3                           T3   T4
 */
AVLTree* AVLTree::rotate_right_left(AVLTree* node) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

/**
 * @brief 			in order print of tree pairs 
 * @param node 		tree node pointer
 */
void AVLTree::print(AVLTree * node) { 
    if(node) { 
        print(node->left);
	    cout << *node->pair << endl;
	    print(node->right);
    }
}