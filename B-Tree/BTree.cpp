// BTree.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// BTree source file. Responsible for insert, search, and traversal.

#include "BTree.h"
#include "DiskIO.h"
#include <iostream>
//#define DEBUG

static unsigned int nextNodeId = 1;
unsigned int iterationCount = 0;
//-- PUBLIC functions

// 1. Searches for the key to see if it already exists in the tree
// 2. If it does, simply increment its counter
// 3. Otherwise, create a new BTreeNode and insert it into the tree
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
		// Create a new node, call splitChild on it, and insert it into the tree
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

/* Outputs key information about the tree, including:
   - Height
   - # of nodes
   - # of available keys
   - # of used keys
   - Ratio of used to available keys
   - Distinct words
   - Total words
   - Disk reads/writes
   - File size
*/
void BTree::outputMetrics()
{
	cout << "Height of tree: " << to_string(getHeight(root, 0)) << endl;
	cout << "Total number of nodes: " << to_string(traverse(root, TraversalType::NUMBER_OF_NODES)) << endl;
	int numberOfKeys = traverse(root, TraversalType::NUMBER_OF_KEYS);
	cout << "Total number of \"available\" keys: " << to_string(numberOfKeys) << endl;

	// Both # of used keys and distinct words will be the same, as each distinct word is a key.
	int distinctNumberOfWords = traverse(root, TraversalType::UNIQUE_WORDS);
	cout << "Total number of used keys: " << to_string(distinctNumberOfWords) << endl;
	cout << "Load factor (used keys / available keys): " << to_string(distinctNumberOfWords/(double)numberOfKeys * 100) << "%" << endl;
	cout << "Number of distinct words: " << to_string(distinctNumberOfWords) << endl;
	cout << "Total number of words (incl. duplicates): " << to_string(traverse(root, TraversalType::TOTAL_WORDS)) << endl;
	cout << "Total number of disk reads: " << to_string(numberOfReads) << endl;
	cout << "Total number of disk writes: " << to_string(numberOfWrites) << endl;
	cout << "File size: " << to_string(DiskIO::getFileSize()) << " bytes" << endl;
}

// Creates an empty tree and adds one node with no keys
void BTree::initializeTree()
{
	BTreeNode x;
	x.id = nextNodeId++;
	x.isLeaf = true;
	x.numberOfKeys = 0;
	root = x.id;
	saveNode(&x);
}

// Searches for a given node by finding the key position that the key WOULD be in, and then by checking that position and all children that
//   are descendants of that key. If the key exists, the node and key value are returned. Otherwise a null node result (ID = 0) is returned.
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

// Returns a given node from the hard disk based on its id, and increments the total number of reads. See DiskIO::loadBTreeNode() for more info.
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

// Saves a given node to the hard disk, and increments the total number of writes. See DiskIO::saveBTreeNode() for more info.
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

// Splits a given node (if necessary) into three nodes, node, z, and y. Z takes half of Y's children, and node takes the median of the values,
//  and node will be the parent of both z and y.
void BTree::splitChild(BTreeNode* node, unsigned int index)
{
	BTreeNode z, y;
	z.id = nextNodeId++;
	getNode(&y, node->childIds[index]);
	z.isLeaf = y.isLeaf;
	z.numberOfKeys = T - 1;
	for (unsigned int j = 1; j <= T - 1; j++)
	{
		// Move half of y's keys to z, and reset the # of occurrences in y since the key was moved.
		strcpy(z.keys[j], y.keys[j + T]);
		z.numberOfOccurrences[j] = y.numberOfOccurrences[j + T];
		y.numberOfOccurrences[j + T] = 1;
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
		node->numberOfOccurrences[j] = 1;
	}
	strcpy(node->keys[index], y.keys[T]);
	node->numberOfOccurrences[index] = y.numberOfOccurrences[T];
	y.numberOfOccurrences[T] = 1;
	node->numberOfKeys = node->numberOfKeys + 1;
	saveNode(&y);
	saveNode(&z);
	saveNode(node);
}

// Inserts the given key into the tree, starting at the node provided. 
void BTree::insertNotFull(BTreeNode* node, string& key)
{
	unsigned int i = node->numberOfKeys;
	// If the node provided is a leaf, and there is a spot for the key, simply add the key in and save the node.
	if (node->isLeaf)
	{
		while (i >= 1 && key < node->keys[i])
		{
			strcpy(node->keys[i + 1], node->keys[i]);
			node->numberOfOccurrences[i + 1] = node->numberOfOccurrences[i];
			node->numberOfOccurrences[i] = 1;
			i--;
		}
		strcpy(node->keys[i + 1], key.c_str());
		node->numberOfOccurrences[i + 1] = 1;
		node->numberOfKeys++;
		saveNode(node);
	}
	else
	{
		// Otherwise, find where the key should go, relative to the given node's children, split the child if necessary, and then save the node.
		// This call may be recursive as the key finds its position down the tree.
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
	traverse(startingNodeNumber, TraversalType::DEBUG_MODE);
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
	if (traversalType == TraversalType::DEBUG_MODE)
	{
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
	}
	for (unsigned int i = 1; i <= node.numberOfChildren; i++)
	{
		//-- Call traverse on each child. "printSpaces+2" is only used when printing out the tree, pushing the output 2 characters to the right.
		childCount += traverse(node.childIds[i], traversalType, printSpaces+2);
	}

	// Set nodeCount to 1, unless the TraversalType is not NUMBER_OF_NODES
	int nodeCount = 1;
	if (traversalType != TraversalType::NUMBER_OF_NODES)
	{
		nodeCount = 0;
		if (traversalType == TraversalType::NUMBER_OF_KEYS)
		{
			nodeCount = node.maxNumberOfKeys;
		}
		else
		{
			for (unsigned int i = 1; i <= node.numberOfKeys; i++)
			{
				nodeCount += traversalType == TraversalType::UNIQUE_WORDS
					? 1
					: node.numberOfOccurrences[i];
			}
		}
	}
	return childCount + nodeCount;
}

int BTree::getHeight(int startingNodeNumber, int currentHeight)
{
	BTreeNode node;
	getNode(&node, startingNodeNumber);
	if (node.isLeaf)
	{
		//-- We've hit the end of the line. Return the current height that was passed in.
		return currentHeight;
	}
	for (unsigned int i = 1; i <= node.numberOfChildren; i++)
	{
		int childHeight = getHeight(node.childIds[i], currentHeight+1);
		if (childHeight > height)
		{
			height = childHeight;
		}
	}

	//-- Check to see if this height is larger than the height found.
	return height;
}