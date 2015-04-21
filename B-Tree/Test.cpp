// Test.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/19/2015
// Test file, used for testing and/or debugging various aspects of the program.

#include "AVLNode.h"
#include "DiskIO.h"
#include "BTreeNode.h"
#include "BTree.h"
#include <fstream>

// Function prototypes
void populateAVLNodes(unsigned int num);
const string AVL_FILE_LOCATION = "AVLNodes.nodes";
const string BTREE_FILE_LOCATION = "BTreeNodes.nodes";
int main2()
{
	DiskIO::openFileStream(BTREE_FILE_LOCATION);
	BTree tree;
	tree.initializeTree();
	string value = "F";
	tree.insertValue(value);
	value = "S";
	tree.insertValue(value);
	value = "Q";
	tree.insertValue(value);
	value = "K";
	tree.insertValue(value);
	value = "C";
	tree.insertValue(value);
	value = "L";
	tree.insertValue(value);
	value = "H";
	tree.insertValue(value);
	value = "T";
	tree.insertValue(value);
	value = "V";
	tree.insertValue(value);
	value = "W";
	tree.insertValue(value);
	value = "M";
	tree.insertValue(value);
	value = "R";
	tree.insertValue(value);
	value = "N";
	tree.insertValue(value);
	value = "P";
	tree.insertValue(value);
	value = "A";
	tree.insertValue(value);
	value = "B";
	tree.insertValue(value);
	value = "X";
	tree.insertValue(value);
	value = "Y";
	tree.insertValue(value);
	value = "D";
	tree.insertValue(value);
	value = "Z";
	tree.insertValue(value);
	value = "E";
	tree.insertValue(value);
	char throwaway = 0;
	DiskIO::closeFileStream();
	return 0;
}

void populateAVLNodes(unsigned int num)
{
	for (unsigned int i = 1; i <= num; i++)
	{
		AVLNode* node = new AVLNode();
		node->id = i;
		node->key = to_string(i) + "KEY" + to_string(i);
		node->leftChildId = 0;
		node->rightChildId = 0;
		node->numberOfOccurrences = 0;
		node->balanceFactor = 0;
		DiskIO::saveAVLNode(node);
	}
}