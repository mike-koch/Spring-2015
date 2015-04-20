// AVLTree.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// AVL Tree header file. Responsible for insert, search, and traversal.
#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include "AVLNode.h"
#include "TraversalType.h"
using namespace std;

class AVLTree
{
public:
	void insertValue(string& key);
	void outputMetrics();
	void closeStreams();

private:
	AVLNode* addNodeToTree(string& key, AVLNode* parent);
	int root = 0;
	int traverseTree(int startingNodeNumber, TraversalType traversalType);
	AVLNode* getNode(int nodeNumber);
	void saveNode(AVLNode* node);

	unsigned int getId(AVLNode* node);

	int keyComparisons; // Contains the total number of times a given key was compared to another key in the tree
	int nodePointerChanges; // Contains the total number of node pointer changes made during insertions
	int balanceFactorChanges; // Contains the total number of balance factor changes made
	int numberOfReads; // Contains the total number of times a record was pulled from the hard drive
	int numberOfWrites; // Contains the total number of times a record was written to the hard drive
};
#endif