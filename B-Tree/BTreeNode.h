// NodeStruct.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// Header file that contains all properties that any tree may use. Not all trees will use every property; however all properties will be 
//    used at some point.
#ifndef BTREENODE_H
#define BTREENODE_H
#include <string>
using namespace std;

struct BTreeNode
{
	const int numberOfKeys;
	BTreeNode* parent;
	BTreeNode* leftChild;
	BTreeNode* rightChild;
	int numberOfOccurrences = 1;
	bool isLeaf;
};
#endif