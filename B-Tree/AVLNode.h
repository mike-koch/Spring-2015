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
	int id = 0; // Unique identifier that dictates the position in the file
	int parentId = 0;
	int leftChildId = 0;
	int rightChildId = 0;
	string key;
	int numberOfOccurrences = 1;
	int balanceFactor = 0; // Can have the value -2, -1, 0, 1, or 2 (values of +/- 2 will be changed to +/- 1 after rebalancing)
};
#endif