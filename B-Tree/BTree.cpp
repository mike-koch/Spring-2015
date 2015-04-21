// BTree.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// AVL Tree header file. Responsible for insert, search, and traversal.

#include "BTree.h"
#include "DiskIO.h"
#include <iostream>
#define DEBUG

static const BTreeNode NULL_NODE = BTree::getNullNode();
static unsigned int nextNodeId = 1;
//-- PUBLIC functions
void BTree::insertValue(string& key)
{
	BTreeNode rootNode = getNode(root);
	// Search if a node with this key already exists.
	BTreeSearchResult searchResult = search(rootNode, key);
	if (searchResult.node.id != NULL_NODE.id)
	{
		//-- We found a hit for our word. Increment the occurrences counter and return
		searchResult.node.numberOfOccurrences[searchResult.keyPosition]++;
		return;
	}

	if (rootNode.numberOfKeys == 2 * T - 1)
	{
		BTreeNode s = allocateNode();
		rootNode = s;
		root = s.id;
		s.isLeaf = false;
		s.numberOfKeys = 0;
		s.childIds[0] = root;
		splitChild(s, 0);
		insertNotFull(s, key);
	}
	else
	{
		insertNotFull(rootNode, key);
	}
}

void BTree::outputMetrics()
{
	cout << "This works." << endl;
	//TODO
}

BTreeNode BTree::getNullNode()
{
	BTreeNode node = *(BTreeNode*)malloc(sizeof(BTreeNode));
	node.id = 0;
	return node;
}

void BTree::initializeTree(unsigned int T)
{
	BTreeNode x = allocateNode();
	x.id = nextNodeId++;
	x.isLeaf = true;
	x.numberOfKeys = 0;
	root = x.id;
}

//-- PRIVATE functions
BTreeSearchResult BTree::search(BTreeNode& startingNode, string& key)
{
	unsigned int i = 0;
	while (i < startingNode.numberOfKeys && key > startingNode.keys[i])
	{
		i++;
	}
	if (i <= startingNode.numberOfKeys && key == startingNode.keys[i])
	{
		BTreeSearchResult result;
		result.keyPosition = i;
		result.node = startingNode;
		return result;
	}
	if (startingNode.isLeaf)
	{
		BTreeSearchResult nullResult;
		nullResult.keyPosition = 0;
		nullResult.node = NULL_NODE;
		return nullResult;
	}
	
	BTreeNode nextNode = getNode(startingNode.childIds[i]);
	return search(nextNode, key);
}

BTreeNode BTree::allocateNode()
{
	return *(BTreeNode*)malloc(sizeof(BTreeNode));
}

BTreeNode BTree::getNode(int nodeId)
{
	if (nodeId == 0)
	{
#ifdef DEBUG
		cout << "BTree requested the null node." << endl;
#endif
		return NULL_NODE;
	}

	BTreeNode node = allocateNode();
	node = DiskIO::loadBTreeNode(nodeId);
	return node;
}

void BTree::saveNode(BTreeNode& node)
{
	if (node.id == 0)
	{
#ifdef DEBUG
		cout << "Attempted to save a node with ID 0. Its first key is " << node.keys[0] << endl;
#endif
		return;
	}
	DiskIO::saveBTreeNode(node);
	return;
}

void BTree::splitChild(BTreeNode& node, unsigned int index)
{
	BTreeNode z = allocateNode();
	BTreeNode y = getNode(node.childIds[index]);
	z.isLeaf = y.isLeaf;
	z.numberOfKeys = T - 1;
	for (unsigned int j = 0; j < T - 1; j++)
	{
		*z.keys[j] = *y.keys[j+T];
		z.numberOfOccurrences[j] = y.numberOfOccurrences[j + T];
	}
	if (!y.isLeaf)
	{
		for (unsigned int j = 0; j < T; j++)
		{
			z.childIds[j] = y.childIds[j + T];
		}
	}
	y.numberOfKeys = T - 1;
	for (unsigned int j = node.numberOfKeys; j > index + 1; j--)
	{
		node.childIds[j + 1] = node.childIds[j];
	}
	node.childIds[index + 1];
	for (unsigned int j = node.numberOfKeys; j > index; j--)
	{
		*node.keys[j + 1] = *node.keys[j];
		node.numberOfOccurrences[j + 1] = node.numberOfOccurrences[j];
	}
	*node.keys[index] = *y.keys[index];
	node.numberOfOccurrences[index] = y.numberOfOccurrences[index];
	node.numberOfKeys = node.numberOfKeys + 1;
	saveNode(y);
	saveNode(z);
	saveNode(node);
}

void BTree::insertNotFull(BTreeNode& node, string& key)
{
	unsigned int i = node.numberOfKeys;
	if (node.isLeaf)
	{
		while (i >= 0 && key < node.keys[i])
		{
			*node.keys[i + 1] = *node.keys[i];
			node.numberOfOccurrences[i + 1] = node.numberOfOccurrences[i];
			i--;
		}
		*node.keys[i + 1] = *key.c_str();
		node.numberOfOccurrences[i + 1] = 1;
		node.numberOfKeys++;
		saveNode(node);
	}
	else
	{
		while (i >= 0 && key < node.keys[i])
		{
			i--;
		}
		i++;
		getNode(node.childIds[i]);
		if (getNode(node.childIds[i]).numberOfKeys == 2 * T - 1)
		{
			splitChild(node, i);
			if (key > node.keys[i])
			{
				i++;
			}
			insertNotFull(getNode(node.childIds[i]), key);
		}
	}
}