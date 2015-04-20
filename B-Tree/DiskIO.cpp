// DiskIO.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/18/2015
// Disk IO source file. Responsible for saving and loading nodes to and from the disk drive.

#include "DiskIO.h"
#include <iostream>
#include <fstream>

static ifstream inputStream;
static ofstream outputStream;

const int SIZE_OF_AVL_NODE = sizeof(AVLNode);
const int SIZE_OF_BTREE_NODE = sizeof(BTreeNode);

//-- PUBLIC functions
void DiskIO::openOutputStream(string fileName)
{
	if (!outputStream.is_open())
	{
		outputStream.open(fileName, ios::binary);
	}
}

void DiskIO::closeOutputStream()
{
	if (outputStream.is_open())
	{
		outputStream.close();
	}
	else
	{
		cout << "WARNING: Output stream was not open, yet closeOutputStream() was called!\n";
	}
}

void DiskIO::openInputStream(string fileName)
{
	if (!inputStream.is_open())
	{
		inputStream.open(fileName, ios::binary);
	}
}

void DiskIO::closeInputStream()
{
	if (inputStream.is_open())
	{
		inputStream.close();
	}
	else
	{
		cout << "WARNING: Input stream was not open, yet closeInputStream() was called!\n";
	}
}

void DiskIO::saveAVLNode(AVLNode* avlNode)
{
	//-- Open the output stream if it isn't already
	//-- Move the seek pointer to the proper place in the file, based on the node's unique ID.
	//   The caller is responsible for keeping track of the next node number for new nodes, so we don't have to worry about it here.
	outputStream.seekp(SIZE_OF_AVL_NODE * avlNode->id);

	//-- Append the new bytes to the file
	outputStream.write((char*)avlNode, SIZE_OF_AVL_NODE);

	//-- Flush the output stream
	outputStream.flush();
}

AVLNode* DiskIO::loadAVLNode(int nodeNumber)
{
	//-- Move the seek pointer to the proper place in the file, based on the node number passed in.
	inputStream.seekg(SIZE_OF_AVL_NODE * nodeNumber);

	//-- Grab the next number of bytes and stuff it into an AVLNode
	AVLNode* nodeToRetrieve = new AVLNode();
	inputStream.read((char*)nodeToRetrieve, SIZE_OF_AVL_NODE);

	return nodeToRetrieve;
}

void DiskIO::saveBTreeNode(BTreeNode bTreeNode)
{
	//-- Move the seek pointer to the proper place in the file, based on the node's unique ID. 1 is added to the end to make everything "1-based".
	//   The caller is responsible for keeping track of the next node number for new nodes, so we don't have to worry about it here.
	outputStream.seekp(SIZE_OF_BTREE_NODE * bTreeNode.id);

	//-- Append the new bytes to the file
	outputStream.write((char*)&bTreeNode, SIZE_OF_BTREE_NODE);

	//-- Close the output stream
	outputStream.flush();
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

	cout << "The file " << fileName << " could not be opened. Press ENTER to exit.\n";
	cin.get(throwaway);
	exit(2);
}