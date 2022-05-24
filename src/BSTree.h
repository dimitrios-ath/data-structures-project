#pragma once
#include "Pair.h"

class BSTree {
	private:
		BSTree* left;
		BSTree* right;
		Pair* pair;
	public:
		BSTree(Pair* pair);
		BSTree* search(BSTree* node, Pair* pair);
		Pair* get_pair(BSTree* node) { return node->pair; }
		BSTree* insert(BSTree* node, Pair* pair);
		BSTree* remove(BSTree* node, Pair* pair);
		BSTree* inorder_successor(BSTree* node);
		void print(BSTree * node);
};