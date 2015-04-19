// NodeStruct.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// Header file that contains all properties that any tree may use. Not all trees will use every property; however all properties will be 
//    used at some point.
#ifndef AVLNODE_H
#define AVLNODE_H
#include <string>
using namespace std;

struct AVLNode
{
	AVLNode* parent;
	AVLNode* leftChild;
	AVLNode* rightChild;
	string key;
	int numberOfOccurrences = 1;
	int balanceFactor = 0; // Used by AVL trees only. Can have the value -2, -1, 0, 1, or 2 (values of +/- 2 will be changed to +/- 1 after rebalancing)
	bool isLeaf;
};
#endif