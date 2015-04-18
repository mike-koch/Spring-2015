// NodeStruct.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// Header file that contains all properties that any tree may use. Not all trees will use every property; however all properties will be 
//    used at some point.
#ifndef NODESTRUCT_H
#define NODESTRUCT_H
#include <string>
using namespace std;

struct Node
{
	Node* parent;
	Node* leftChild;
	Node* rightChild;
	string keys[2*T - 1]; // Establish an array of keys. For AVL, there will only ever be one key in this array. For BTrees, there will be 
						  //     between T - 1 and 2T - 1 keys.
	int numberOfOccurrences = 1;
	int balanceFactor = 0; // Used by AVL trees only. Can have the value -2, -1, 0, 1, or 2 (values of +/- 2 will be changed to +/- 1 after rebalancing)
	bool isLeaf;
};
#endif