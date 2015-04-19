// DiskIO.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/18/2015
// Disk IO source file. Responsible for saving and loading nodes to and from the disk drive.

#include "DiskIO.h"
#include <iostream>
#include <fstream>

const string AVL_FILE_LOCATION = "C:\\AVLNodes.nodes";
const string BTREE_FILE_LOCATION = "C:\\BTreeNodes.nodes";

const int SIZE_OF_AVL_NODE = sizeof(AVLNode);
const int SIZE_OF_BTREE_NODE = sizeof(BTreeNode);

//-- PUBLIC functions
void DiskIO::saveAVLNode(AVLNode& avlNode)
{
	ofstream outputStream;
	outputStream.open(AVL_FILE_LOCATION, ios::binary);

	//-- Make sure we can actually save the node
	if (outputStream.fail())
	{
		outputFailure(AVL_FILE_LOCATION);
	}

	//-- Move the seek pointer to the proper place in the file, based on the node's unique ID. 1 is added to the end to make everything "1-based".
	//   The caller is responsible for keeping track of the next node number for new nodes, so we don't have to worry about it here.
	outputStream.seekp(SIZE_OF_AVL_NODE * avlNode.id + 1);

	//-- Append the new bytes to the file
	outputStream.write((char*)&avlNode, SIZE_OF_AVL_NODE);

	//-- Close the output stream
	outputStream.close();
}

AVLNode DiskIO::loadAVLNode(int nodeNumber)
{
	//TODO
	AVLNode nodeToReturn;
	return nodeToReturn;
}

void DiskIO::saveBTreeNode(BTreeNode& bTreeNode)
{
	ofstream outputStream;
	outputStream.open(BTREE_FILE_LOCATION, ios::binary);

	//-- Make sure we can actually save the node
	if (outputStream.fail())
	{
		outputFailure(BTREE_FILE_LOCATION);
	}

	//-- Move the seek pointer to the proper place in the file, based on the node's unique ID. 1 is added to the end to make everything "1-based".
	//   The caller is responsible for keeping track of the next node number for new nodes, so we don't have to worry about it here.
	outputStream.seekp(SIZE_OF_BTREE_NODE * bTreeNode.id + 1);

	//-- Append the new bytes to the file
	outputStream.write((char*)&bTreeNode, SIZE_OF_BTREE_NODE);

	//-- Close the output stream
	outputStream.close();
}

BTreeNode DiskIO::loadBTreeNode(int nodeNumber)
{
	//TODO
	BTreeNode nodeToReturn;
	return nodeToReturn;
}

//-- PRIVATE functions
void DiskIO::outputFailure(string fileName)
{
	char throwaway;

	cout << "The file " << fileName << "could not be opened. Press ENTER to exit.\n";
	cin.get(throwaway);
	exit(2);
}