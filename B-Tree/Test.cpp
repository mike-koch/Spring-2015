// Test.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/19/2015
// Test file, used for testing and/or debugging various aspects of the program.

#include "AVLNode.h"
#include "DiskIO.h"
#include <fstream>

// Function prototypes
void populateNodes(unsigned int num);
const string AVL_FILE_LOCATION = "AVLNodes.nodes";
const string BTREE_FILE_LOCATION = "BTreeNodes.nodes";
int main2()
{
	DiskIO::openFileStream(AVL_FILE_LOCATION);
	populateNodes(8);

	AVLNode* node = DiskIO::loadAVLNode(8);
	DiskIO::closeFileStream();
	char throwaway = 0;

	return 0;
}

void populateNodes(unsigned int num)
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