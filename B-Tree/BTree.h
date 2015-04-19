// BTree.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// BTree header file. Responsible for insert, search, and traversal.
#ifndef BTREE
#define BTREE
#include <string>
#include "BTreeNode.h"
#include "TraversalType.h"
using namespace std;

class BTree
{
public:
	BTree(unsigned int t); // Constructor for defining value of T.
	void insertValue(string& key);
	void outputMetrics();

private:
	unsigned int t; // t value for the B-Tree. Determines how many keys can fit in one node
	BTreeNode* root;
	BTreeNode* addNodeToTree(string& key, BTreeNode* parent);
	int traverseTree(BTreeNode* startingNode, TraversalType traversalType);
	int search(BTreeNode* startingNode, string& key);

	int keyComparisons; // Contains the total number of times a given key was compared to another key in the tree
	int nodePointerChanges; // Contains the total number of node pointer changes made during insertions
	int numberOfReads; // Contains the total number of times a record was pulled from the hard drive
	int numberOfWrites; // Contains the total number of times a record was written to the hard drive
};
#endif