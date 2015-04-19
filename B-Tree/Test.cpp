// Test.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/19/2015
// Test file, used for testing and/or debugging various aspects of the program.

#include "AVLNode.h"
#include "DiskIO.h"

// Function prototypes
AVLNode testCreatingAVLNode(int latestId);

int maintest()
{
	AVLNode node = testCreatingAVLNode(0);
	int nodeId = node.id;
	DiskIO::saveAVLNode(node);
	AVLNode returnedNode = DiskIO::loadAVLNode(node.id);
	char throwaway = 0;
}

AVLNode testCreatingAVLNode(int latestId)
{
	AVLNode avlNode;
	avlNode.id = latestId + 1;
	avlNode.parentId = 22;
	avlNode.leftChildId = 0;
	avlNode.rightChildId = 0;
	avlNode.key = "MY KEY";
	avlNode.numberOfOccurrences = 572;
	avlNode.isLeaf = true;
	avlNode.balanceFactor = 1;

	return avlNode;
}