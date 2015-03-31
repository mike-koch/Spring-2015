// NodeStruct.h
// Mike Koch
// EECS 2510 | Spring 2015 | 03/31/2015
// Header file that contains all properties that any tree may use. Not all trees will use every property; however all properties will be 
//    used at some point.

struct Node 
{
	Node* parent;
	Node* leftChild;
	Node* rightChild;
	int numberOfOccurrences;
	int balanceFactor; // Used by AVL trees only. Can have the value -2, -1, 0, 1, or 2 (values of +/- 2 will be changed to +/- 1 after rebalancing
	//TODO add property for Color after the enum has been created
};