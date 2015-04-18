// BTree.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// BTree header file. Responsible for insert, search, and traversal.
#ifndef BTREE
#define BTREE
#include <string>
#include "NodeStruct.h"
#include "TraversalType.h"
using namespace std;

class BTree
{
public:
	void insertValue(string& key);
	void outputMetrics();

private:
	const unsigned int T = 2; // t value for the B-Tree. Determines how many keys can fit in one node
	Node* root; 
	Node* addNodeToTree(string& key, Node* parent);
	int traverseTree(Node* startingNode, TraversalType traversalType);

	int keyComparisons; // Contains the total number of times a given key was compared to another key in the tree
	int nodePointerChanges; // Contains the total number of node pointer changes made during insertions
};
#endif