// BTree.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// BTree header file. Responsible for insert, search, and traversal.
#ifndef BTREE
#define BTREE
#include <string>
#include "BTreeNode.h"
#include "BTreeSearchResult.h"
#include "TraversalType.h"
using namespace std;

class BTree
{
public:
	void insertValue(string& key);
	void outputMetrics();
	void initializeTree();

private:
	unsigned int root;
	void search(BTreeSearchResult* searchResult, BTreeNode* startingNode, string& key);
	void getNode(BTreeNode* node, int nodeId);
	void saveNode(BTreeNode* node);
	void splitChild(BTreeNode* node, unsigned int index);
	void insert(string& key);
	void insertNotFull(BTreeNode* node, string& key);
	int traverse(int startingNodeNumber, TraversalType traversalType, int printSpaces = 0);
	void printTree(int startingNodeNumber);

	int keyComparisons; // Contains the total number of times a given key was compared to another key in the tree
	int nodePointerChanges; // Contains the total number of node pointer changes made during insertions
	int numberOfReads; // Contains the total number of times a record was pulled from the hard drive
	int numberOfWrites; // Contains the total number of times a record was written to the hard drive
};
#endif