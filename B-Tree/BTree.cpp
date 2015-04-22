// BTree.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// AVL Tree header file. Responsible for insert, search, and traversal.

#include "BTree.h"
#include "DiskIO.h"
#include <iostream>
//#define DEBUG

unsigned int nextNodeId = 1;
unsigned int iterationCount = 0;
//-- PUBLIC functions
void BTree::insertValue(string& key)
{
	if (++iterationCount % 1000 == 0)
	{
		cout << iterationCount << endl;
	}
#ifdef DEBUG
	//cout << "KEY: " << key << endl;
#endif
	BTreeNode* rootNode = getNode(root);
	// Search if a node with this key already exists.
	BTreeSearchResult* searchResult = search(rootNode, key);
	if (searchResult->node != NULL)
	{
		//-- We found a hit for our word. Increment the occurrences counter and return
		searchResult->node->numberOfOccurrences[searchResult->keyPosition]++;
		return;
	}

	int tempRoot = root;
	if (rootNode->numberOfKeys == rootNode->maxNumberOfKeys)
	{
		BTreeNode* s = new BTreeNode();
		s->id = nextNodeId++;
		rootNode = s;
		root = s->id;
		s->isLeaf = false;
		s->numberOfKeys = 0;
		s->childIds[1] = tempRoot;
		splitChild(s, 1);
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

void BTree::initializeTree()
{
	BTreeNode* x = new BTreeNode();
	x->id = nextNodeId++;
	x->isLeaf = true;
	x->numberOfKeys = 0;
	root = x->id;
	saveNode(x);
}

BTreeSearchResult* BTree::search(BTreeNode* startingNode, string& key)
{
	unsigned int i = 1;
	while (i < startingNode->numberOfKeys && key > startingNode->keys[i])
	{
		i++;
	}
	if (i <= startingNode->numberOfKeys && key == startingNode->keys[i])
	{
		BTreeSearchResult* result = new BTreeSearchResult();
		result->keyPosition = i;
		result->node = startingNode;
		return result;
	}
	if (startingNode->isLeaf)
	{
		BTreeSearchResult* nullResult = new BTreeSearchResult();
		nullResult->keyPosition = 0;
		nullResult->node = NULL;
		return nullResult;
	}
	
	BTreeNode* nextNode = getNode(startingNode->childIds[i]);
	return search(nextNode, key);
}

BTreeNode* BTree::getNode(int nodeId)
{
	if (nodeId == 0)
	{
#ifdef DEBUG
		cout << "BTree requested the null node." << endl;
#endif
		return NULL;
	}

	BTreeNode* node = DiskIO::loadBTreeNode(nodeId);
	return node;
}

void BTree::saveNode(BTreeNode* node)
{
	if (node->id == 0)
	{
#ifdef DEBUG
		cout << "Attempted to save a node with ID 0. Its first key is " << node->keys[0] << endl;
#endif
		return;
	}
#ifdef DEBUG
	if (node->id % 1000 == 0)
	{
		cout << node->id << endl;
	}
	//cout << "Saving a node with ID: " << node->id << endl;
#endif
	DiskIO::saveBTreeNode(node);
	return;
}

void BTree::splitChild(BTreeNode* node, unsigned int index)
{
	BTreeNode* z = new BTreeNode();
	z->id = nextNodeId++;
	BTreeNode* y = getNode(node->childIds[index]);
	z->isLeaf = y->isLeaf;
	z->numberOfKeys = T - 1;
	for (unsigned int j = 1; j <= T - 1; j++)
	{
		strcpy(z->keys[j], y->keys[j + T]);
		z->numberOfOccurrences[j] = y->numberOfOccurrences[j + T];
	}
	if (!y->isLeaf)
	{
		for (unsigned int j = 1; j <= T; j++)
		{
			z->childIds[j] = y->childIds[j + T];
		}
	}
	y->numberOfKeys = T - 1;
	for (unsigned int j = node->numberOfKeys + 1; j >= index + 1; j--)
	{
		node->childIds[j + 1] = node->childIds[j];
	}
	node->childIds[index + 1] = z->id;
	for (unsigned int j = node->numberOfKeys; j >= index; j--)
	{
		strcpy(node->keys[j + 1], node->keys[j]);
		node->numberOfOccurrences[j + 1] = node->numberOfOccurrences[j];
	}
	strcpy(node->keys[index], y->keys[T]);
	node->numberOfOccurrences[index] = y->numberOfOccurrences[T];
	node->numberOfKeys = node->numberOfKeys + 1;
	saveNode(y);
	saveNode(z);
	saveNode(node);
}

void BTree::insertNotFull(BTreeNode* node, string& key)
{
	unsigned int i = node->numberOfKeys;
	if (node->isLeaf)
	{
		while (i >= 1 && key < node->keys[i])
		{
			strcpy(node->keys[i + 1], node->keys[i]);
			node->numberOfOccurrences[i + 1] = node->numberOfOccurrences[i];
			i--;
		}
		strcpy(node->keys[i + 1], key.c_str());
		node->numberOfOccurrences[i] = 1;
		node->numberOfKeys++;
		saveNode(node);
	}
	else
	{
		while (i >= 1 && key < node->keys[i])
		{
			i--;
		}
		i++;
		BTreeNode* childNode = getNode(node->childIds[i]);
		if (childNode->numberOfKeys == childNode->maxNumberOfKeys)
		{
			splitChild(node, i);
			if (key > node->keys[i])
			{
				i++;
			}
		}
		insertNotFull(getNode(node->childIds[i]), key);
	}
}