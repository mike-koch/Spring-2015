// BTree.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// AVL Tree header file. Responsible for insert, search, and traversal.

#include "BTree.h"
#include "DiskIO.h"
#include <iostream>
//#define DEBUG

static unsigned int nextNodeId = 1;
unsigned int iterationCount = 0;
//-- PUBLIC functions
void BTree::insertValue(string& key)
{
#ifdef DEBUG
	cout << endl << "Inserting Key: " << key << endl;
	cout << "-----------------" << endl;
#endif
	BTreeNode rootNode;
	getNode(&rootNode, root);
	// Search if a node with this key already exists.
	BTreeSearchResult searchResult;
	search(&searchResult, &rootNode, key);
	if (searchResult.node.id != 0)
	{
		//-- We found a hit for our word. Increment the occurrences counter and return
		searchResult.node.numberOfOccurrences[searchResult.keyPosition]++;
		saveNode(&searchResult.node);
#ifdef DEBUG
		// Print the current status of the tree if DEBUG is defined
		printTree(root);
#endif
		return;
	}

	int tempRoot = root;
	if (rootNode.numberOfKeys == rootNode.maxNumberOfKeys)
	{
		BTreeNode s;
		s.id = nextNodeId++;
		rootNode = s;
		root = s.id;
		s.isLeaf = false;
		s.numberOfKeys = 0;
		s.childIds[1] = tempRoot;
		s.numberOfChildren++;
		splitChild(&s, 1);
		insertNotFull(&s, key);
	}
	else
	{
		insertNotFull(&rootNode, key);
	}
#ifdef DEBUG
	// Print the current status of the tree if DEBUG is defined
	printTree(root);
#endif
}

void BTree::outputMetrics()
{
	//TODO
	cout << "Total number of nodes: " << to_string(traverse(root, TraversalType::NUMBER_OF_NODES)) << endl;
	cout << "Number of distinct words: " << to_string(traverse(root, TraversalType::UNIQUE_WORDS)) << endl;
	cout << "Total number of words (incl. duplicates): " << to_string(traverse(root, TraversalType::TOTAL_WORDS)) << endl;
	cout << "Total number of disk reads: " << to_string(numberOfReads) << endl;
	cout << "Total number of disk writes: " << to_string(numberOfWrites) << endl;
}

void BTree::initializeTree()
{
	BTreeNode x;
	x.id = nextNodeId++;
	x.isLeaf = true;
	x.numberOfKeys = 0;
	root = x.id;
	saveNode(&x);
}

void BTree::search(BTreeSearchResult* searchResult, BTreeNode* startingNode, string& key)
{
	unsigned int i = 1;
	while (i <= startingNode->numberOfKeys && key > startingNode->keys[i])
	{
		i++;
	}
	if (i <= startingNode->numberOfKeys && key == startingNode->keys[i])
	{
		searchResult->keyPosition = i;
		searchResult->node = *startingNode;
		if (searchResult->node.id > 1000)
		{
			char throwaway = 0;
		}
		return;
	}
	if (startingNode->isLeaf)
	{
		searchResult->keyPosition = 0;
		searchResult->node.id = 0;
		return;
	}
	BTreeNode nextNode;
	getNode(&nextNode, startingNode->childIds[i]);
	return search(searchResult, &nextNode, key);
}

void BTree::getNode(BTreeNode* node, int nodeId)
{
	if (nodeId == 0)
	{
#ifdef DEBUG
		cout << "BTree requested the null node." << endl;
#endif
		return;
	}
	numberOfReads++;
	DiskIO::loadBTreeNode(node, nodeId);
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
	//cout << "Saving a node with ID: " << node->id << endl;
#endif
	numberOfWrites++;
	DiskIO::saveBTreeNode(node);
	return;
}

void BTree::splitChild(BTreeNode* node, unsigned int index)
{
	BTreeNode z, y;
	z.id = nextNodeId++;
	getNode(&y, node->childIds[index]);
	z.isLeaf = y.isLeaf;
	z.numberOfKeys = T - 1;
	for (unsigned int j = 1; j <= T - 1; j++)
	{
		strcpy(z.keys[j], y.keys[j + T]);
		z.numberOfOccurrences[j] = y.numberOfOccurrences[j + T];
	}
	if (!y.isLeaf)
	{
		for (unsigned int j = 1; j <= T; j++)
		{
			z.childIds[j] = y.childIds[j + T];
			z.numberOfChildren++;
			y.numberOfChildren--;
		}
	}
	y.numberOfKeys = T - 1;
	for (unsigned int j = node->numberOfKeys + 1; j >= index + 1; j--)
	{
		node->childIds[j + 1] = node->childIds[j];
	}
	node->childIds[index + 1] = z.id;
	node->numberOfChildren++;
	for (unsigned int j = node->numberOfKeys; j >= index; j--)
	{
		strcpy(node->keys[j + 1], node->keys[j]);
		node->numberOfOccurrences[j + 1] = node->numberOfOccurrences[j];
	}
	strcpy(node->keys[index], y.keys[T]);
	node->numberOfOccurrences[index] = y.numberOfOccurrences[T];
	node->numberOfKeys = node->numberOfKeys + 1;
	saveNode(&y);
	saveNode(&z);
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
		BTreeNode childNode;
		getNode(&childNode, node->childIds[i]);
		if (childNode.numberOfKeys == childNode.maxNumberOfKeys)
		{
			splitChild(node, i);
			if (key > node->keys[i])
			{
				i++;
			}
			getNode(&childNode, node->childIds[i]);
		}
		
		insertNotFull(&childNode, key);
	}
}

// Prints out the current contents of the tree. Simply a wrapper function to traverse, but with a cin at the end to require user input.
// If DEBUG is disabled, this is a no-op
void BTree::printTree(int startingNodeNumber)
{
#ifdef DEBUG
	traverse(startingNodeNumber, TraversalType::NONE);
	char throwaway;
	cin.get(throwaway);
#endif
}

int BTree::traverse(int startingNodeNumber, TraversalType traversalType, int printSpaces)
{
	if (startingNodeNumber == 0) {
		// Return early if the tree is empty or if we are at a leaf node to prevent NPEs.
		return 0;
	}
	BTreeNode node;
	getNode(&node, startingNodeNumber);
	int childCount = 0;
#ifdef DEBUG
	//Print out info for this node
	string keys;
	string spaces = "";
	for (int i = 0; i < printSpaces; i++)
	{
		spaces += " ";
	}
	bool first = true;
	for (unsigned int i = 1; i <= node.numberOfKeys; i++)
	{
		if (!first)
		{
			keys += ", ";
		}
		first = false;
		keys += node.keys[i];
		keys += " (" + to_string(node.numberOfOccurrences[i]) + ")";
	}
	cout << spaces << "Node #" << node.id << ", keys: " << keys << endl;
#endif
	for (unsigned int i = 1; i <= node.numberOfChildren; i++)
	{
		//-- There will be at most numberOfKeys + 1 children, and at least 0. The 0 check will prevent accesses to invalid children
		childCount += traverse(node.childIds[i], traversalType, printSpaces+2);
	// Set nodeCount to 1, unless the TraversalType is not NUMBER_OF_NODES
	int nodeCount = 1;
	if (traversalType != TraversalType::NUMBER_OF_NODES)
	{
		nodeCount = 0;
		for (unsigned int i = 1; i <= node.numberOfKeys; i++)
		{
			nodeCount += traversalType == TraversalType::UNIQUE_WORDS
				? 1
				: node.numberOfOccurrences[i];
		}
	}
	return childCount + nodeCount;
	

	/*int leftCount = traverseTree(node.leftChildId, traversalType);
	int nodeCount = traversalType == TraversalType::UNIQUE_WORDS
		? 1
		: startingNode->numberOfOccurrences;
	int rightCount = traverseTree(startingNode->rightChildId, traversalType);

	if (traversalType == TraversalType::HEIGHT)
	{
		// Return 1 (which must be 1 since we're starting at the root), along with the higher height of the left or right side
		if (leftCount > rightCount)
		{
			return 1 + leftCount;
		}
		return 1 + rightCount;
	}
	return leftCount + nodeCount + rightCount;*/
	return 0;
}