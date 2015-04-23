// AVLNode.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// Header file that contains all properties that an AVL tree will need.
#ifndef AVLNODE_H
#define AVLNODE_H
#include <string>
using namespace std;

struct AVLNode
{
	unsigned int id = 0; // Unique identifier that dictates the position in the file
	unsigned int leftChildId = 0;
	unsigned int rightChildId = 0;
	string key;
	int numberOfOccurrences = 1;
	int balanceFactor = 0; // Can have the value -2, -1, 0, 1, or 2 (values of +/- 2 will be changed to +/- 1 after rebalancing)
};
#endif