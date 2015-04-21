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
	BTree(unsigned int t)
	{
		initializeTree(t);
		T = t;
	}// Constructor for defining value of T.
	void insertValue(string& key);
	void outputMetrics();
	static BTreeNode getNullNode();
	void initializeTree(const unsigned int T);

private:
	unsigned int T; // Value used for T 
	unsigned int root;
	BTreeSearchResult search(BTreeNode& startingNode, string& key);
	BTreeNode getNode(int nodeId);
	void saveNode(BTreeNode& node);
	BTreeNode allocateNode();
	void splitChild(BTreeNode& node, unsigned int index);
	void insert(string& key);
	void insertNotFull(BTreeNode& node, string& key);

	int keyComparisons; // Contains the total number of times a given key was compared to another key in the tree
	int nodePointerChanges; // Contains the total number of node pointer changes made during insertions
	int numberOfReads; // Contains the total number of times a record was pulled from the hard drive
	int numberOfWrites; // Contains the total number of times a record was written to the hard drive
};
#endif