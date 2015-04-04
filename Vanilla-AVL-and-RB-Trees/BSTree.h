// BST.h
// Mike Koch
// EECS 2510 | Spring 2015 | 03/30/2015
// Binary Search Tree header file. Responsible for insert, search, and traversal.  This class is a "splice" of the other BST.cpp file from Lab 1
//    with the exception of "keyComparisons" and "nodePointerChanges", which are unique to this file.
#ifndef BSTREE_H
#define BSTREE_H
#include <string>
#include "NodeStruct.h"
#include "TraversalType.h"
using namespace std;

class BSTree
{
public:
	void insertValue(string key);
	void outputMetrics();

private:	
	Node* root;
	Node* search(Node* node, string key);
	void addNodeToTree(Node* node, Node* parent);
	int traverseTree(Node* startingNode, TraversalType traversalType);

	int keyComparisons; // Contains the total number of times a given key was compared to another key in the tree
	int nodePointerChanges; // Contains the total number of node pointer changes made during insertions
};
#endif