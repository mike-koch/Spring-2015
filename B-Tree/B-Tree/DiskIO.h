// DiskIO.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/18/2015
// Disk IO header file. Responsible for saving and loading nodes to and from the disk drive, obtaining the file size, and managing the file stream.
#ifndef DISKIO_H
#define DISKIO_H
#include "AVLNode.h"
#include "BTreeNode.h"
using namespace std;

struct DiskIO
{
public:
	static void openFileStream(string fileName); // Opens the filestream for the given file name if it isn't open already

	static void saveAVLNode(AVLNode* avlNode); // Saves the requested node
	static void loadAVLNode(AVLNode* node, int nodeNumber); // Returns the node for the node number requested

	static void saveBTreeNode(BTreeNode* bTreeNode); // Saves the requested node
	static void loadBTreeNode(BTreeNode* node, int nodeNumber); // Same as loadAVLNode, but for a BTreeNode
	static unsigned long long getFileSize();
	static void closeFileStream(); // Closes the filestream
private:
	static void outputFailure(string fileName);
};

#endif