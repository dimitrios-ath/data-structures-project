#pragma once
#include "Pair.h"

class AVLTree {
    private:
        AVLTree* left;
		AVLTree* right;
		Pair* pair;
        long height;
    public:
        AVLTree(Pair* pair);
        Pair* get_pair(AVLTree* node) { return node->pair; }
        AVLTree* search(AVLTree* node, Pair* pair);
		AVLTree* insert(AVLTree* node, Pair* pair);
		AVLTree* remove(AVLTree* node, Pair* pair);
        AVLTree* rotate_left(AVLTree* node);
        AVLTree* rotate_right(AVLTree* node);
        AVLTree* rotate_left_right(AVLTree* node);
        AVLTree* rotate_right_left(AVLTree* node);
		AVLTree* inorder_successor(AVLTree* node);
        void increment_height() { height++; }
        int balance_factor(AVLTree* node);
        int get_height(AVLTree* node);
        void update_height(AVLTree* node);
        void print(AVLTree * node);
};