// AstractTree.h
// Mike Koch
// EECS 2510 | Spring 2015 | 03/30/2015
// Basic wireframe of all of the tree types (BST, AVL, RBT).  There is no direct implementation of AbstractTree; instead, BST, AVL, and RBT
//    will extend AbstractTree, asserting that the proper functions are in each tree and to improve code clarity.

class AbstractTree
{
public:
	virtual void insert() = 0; // Creating a pure virtual function to require derivative classes to implement insert() (Savitch 5th ed, pg 671)
};