// Test.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/19/2015
// Test file, used for testing and/or debugging various aspects of the program.

#include "AVLNode.h"
#include "DiskIO.h"
#include <fstream>

// Function prototypes
AVLNode* testCreatingAVLNode(int latestId);
const string AVL_FILE_LOCATION = "AVLNodes.nodes";
const string BTREE_FILE_LOCATION = "BTreeNodes.nodes";
int main2()
{

	AVLNode* node = new AVLNode();
	node->id = 1;
	node->key = "FIRST 1KEY1";
	DiskIO::openOutputStream(AVL_FILE_LOCATION);
	DiskIO::saveAVLNode(node);
	AVLNode* anothernode = new AVLNode();
	anothernode->id = 2;
	anothernode->key = "SECOND 2KEY2";
	DiskIO::saveAVLNode(anothernode);
	AVLNode* thirdnode = new AVLNode();
	thirdnode->id = 3;
	thirdnode->key = "THIRD 3KEY3";
	DiskIO::saveAVLNode(thirdnode);
	DiskIO::openInputStream(AVL_FILE_LOCATION);
	AVLNode* returnedNode = DiskIO::loadAVLNode(1);
	AVLNode* anotherReturnedNode = DiskIO::loadAVLNode(2);
	AVLNode* thirdReturnedNode = DiskIO::loadAVLNode(3);
	DiskIO::closeInputStream();
	DiskIO::closeOutputStream();
	char throwaway = 0;

	return 0;
}