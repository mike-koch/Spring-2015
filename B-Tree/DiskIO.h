// DiskIO.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/18/2015
// Disk IO header file. Responsible for saving and loading nodes to and from the disk drive.
#ifndef DISKIO_H
#define DISKIO_H
#include "AVLNode.h"
#include "BTreeNode.h"
using namespace std;

struct DiskIO
{
public:
	static void saveAVLNode(AVLNode& avlNode); // Saves the requested node
	static AVLNode loadAVLNode(int nodeNumber); // Returns the node for the node number requested

	static void saveBTreeNode(BTreeNode& bTreeNode); // Saves the requested node
	static BTreeNode loadBTreeNode(int nodeNumber); // Same as loadAVLNode, but for a BTreeNode
private:
	static void outputFailure(string fileName);
};

#endif