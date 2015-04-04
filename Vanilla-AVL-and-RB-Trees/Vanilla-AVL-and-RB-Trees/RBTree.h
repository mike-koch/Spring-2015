// RBTree.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/04/2015
// Red-Black Tree header file. Responsible for insert, search, and traversal.
#ifndef RBTREE_H
#define RBTREE_H
#include <string>
#include "NodeStruct.h"
#include "TraversalType.h"
#include "Color.h"
using namespace std;

class RBTree
{
public:
	RBTree();
	void insertValue(string key);
	void outputMetrics();

private:
	Node* root;
	Node* nil;
	Node* search(Node* startingNode, string key);
	void fixupTree(Node* startingNode);
	void leftRotate(Node* startingNode);
	void rightRotate(Node* startingNode);
	int traverseTree(Node* startingNode, TraversalType traversalType);

	int keyComparisons; // Contains the total number of times a given key was compared to another key in the tree
	int nodePointerChanges; // Contains the total number of node pointer changes made during insertions
};
#endif