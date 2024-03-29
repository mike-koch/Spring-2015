// DiskIO.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/18/2015
// Disk IO source file. Responsible for saving and loading nodes to and from the disk drive, obtaining the file size, and managing the file stream.

#include "DiskIO.h"
#include <iostream>
#include <fstream>

static fstream fileStream;

const int SIZE_OF_AVL_NODE = sizeof(AVLNode);
const int SIZE_OF_BTREE_NODE = sizeof(BTreeNode);

//-- PUBLIC functions
void DiskIO::openFileStream(string fileName)
{
	if (!fileStream.is_open())
	{
		// Allow input, output, write in binary (not text), and truncate the file if there's anything in it
		fileStream.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
	}
}

void DiskIO::closeFileStream()
{
	if (fileStream.is_open())
	{
		fileStream.close();
	}
	else
	{
		cout << "WARNING: Output stream was not open, yet closeOutputStream() was called!\n";
	}
}

void DiskIO::saveAVLNode(AVLNode* avlNode)
{
	//-- Open the output stream if it isn't already
	//-- Move the seek pointer to the proper place in the file, based on the node's unique ID.
	//   The caller is responsible for keeping track of the next node number for new nodes, so we don't have to worry about it here.
	fileStream.seekp(SIZE_OF_AVL_NODE * avlNode->id);

	//-- Append the new bytes to the file
	fileStream.write((char*)avlNode, SIZE_OF_AVL_NODE);

	//-- Flush the output stream
	fileStream.flush();
}

void DiskIO::loadAVLNode(AVLNode* node, int nodeNumber)
{
	//-- Move the seek pointer to the proper place in the file, based on the node number passed in.
	fileStream.seekg(SIZE_OF_AVL_NODE * nodeNumber);

	//-- Grab the next number of bytes and stuff it into an AVLNode
	fileStream.read((char*)node, SIZE_OF_AVL_NODE);

	return;
}

void DiskIO::saveBTreeNode(BTreeNode* bTreeNode)
{
	//-- Move the seek pointer to the proper place in the file, based on the node's unique ID. 1 is added to the end to make everything "1-based".
	//   The caller is responsible for keeping track of the next node number for new nodes, so we don't have to worry about it here.
	fileStream.seekp(SIZE_OF_BTREE_NODE * bTreeNode->id);

	//-- Append the new bytes to the file
	fileStream.write((char*)bTreeNode, SIZE_OF_BTREE_NODE);

	//-- Close the output stream
	fileStream.flush();
}

void DiskIO::loadBTreeNode(BTreeNode* node, int nodeNumber)
{
	//-- Move the seek pointer to the proper place in the file, based on the node number passed in.
	fileStream.seekg(SIZE_OF_BTREE_NODE * nodeNumber);

	//-- Grab the next number of bytes and stuff it into a BTreeNode
	fileStream.read((char*)node, SIZE_OF_BTREE_NODE);
}

unsigned long long DiskIO::getFileSize()
{
	//-- If the file stream isn't open, open it, and seek to the beginning of the file
	if (!fileStream.is_open())
	{
		cout << "WARNING: The file stream is not open. Open the file stream first and try again.";
		return 0;
	}

	//-- Seek to the beginning of the file. Then, after reading each byte, return the total number of iterations
	fileStream.seekg(0, ios::beg);
	char throwaway = 0;
	fileStream.get(throwaway);
	unsigned long long fileSize = 0;
	while (!fileStream.eof())
	{
		fileSize++;
		fileStream.get(throwaway);
	}

	return fileSize;
}

//-- PRIVATE functions
void DiskIO::outputFailure(string fileName)
{
	char throwaway;

	cout << "The file " << fileName << " could not be opened. Press ENTER to exit.\n";
	cin.get(throwaway);
	exit(2);
}