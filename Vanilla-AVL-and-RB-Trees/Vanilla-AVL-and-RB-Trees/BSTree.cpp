// BST.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 03/30/2015
// Binary Search Tree class. Responsible for insert, search, and traversal.  This class is a "splice" of the other BST.cpp file from Lab 1.

#include "BSTree.h"
#include <iostream>

//-- PUBLIC Functions
void BSTree::insertValue(string key) 
{
	// 1. Search if the key already exists
	// 2. If yes, just increment the counter
	// 3. Otherwise, create a new node and hang it on the tree.
	Node* newNode = NULL;
	Node* existingNode = search(root, key);
	if (existingNode == NULL || existingNode->key != key) 
	{
		//-- Create a new node
		newNode = new Node();
		newNode->key = key;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->numberOfOccurrences = 1;

		// Hang the node on the tree
		addNodeToTree(newNode, existingNode);
	}
	else 
	{
		// Increment its counter
		existingNode->numberOfOccurrences++;
	}
}

/* Outputs key information about the tree, including:
     - Height of tree
	 - Number of key comparisons
	 - Number of node pointer changes
	 - Number of unique words
	 - Number of words including duplicates
*/
void BSTree::outputMetrics()
{
	cout << "Height of tree: " << to_string(traverseTree(root, TraversalType::HEIGHT)) << endl;
	cout << "Number of key comparisons: " << to_string(keyComparisons) << endl;
	cout << "Number of node pointer changes: " << to_string(nodePointerChanges) << endl;
	cout << "Total number of unique words: " << to_string(traverseTree(root, TraversalType::UNIQUE_WORDS)) << endl;
	cout << "Total number of words (incl. duplicates): " << to_string(traverseTree(root, TraversalType::TOTAL_WORDS)) << endl;
}

//-- PRIVATE Functions

// Will return the node with the requested key if found, OR, if no results found, will return the node that will become the parent of 
//    the new node.
Node* BSTree::search(Node* node, string key) 
{
	// If the node's key matches the key being searched, return the node.
	// Else if the key is less than the node's key, search relative to the node's left child, or return the parent of the would-be node if the parent doesn't have a child in the correct direction.
	// Else search relative to the node's right child, or return the parent of the would-be node if the parent doesn't have a child in the correct direction.
	if (node == NULL || key == node->key)
	{
		return node;
	}
	if (key < node->key)
	{
		if (node->leftChild == NULL)
		{
			return node; // We found the node that should be the parent of the one we're looking for. Our key doesn't exist, but we now
						 //    now know who the parent should be.
		}
		return search(node->leftChild, key);
	}

	// key must be greater than startingNode->key
	if (node->rightChild == NULL)
	{
		return node; // We found the node that should be the parent of the one we're looking for. Our key doesn't exist, but we now
					 //    now know who the parent should be.
	}
	return search(node->rightChild, key);
}

void BSTree::addNodeToTree(Node* node, Node* parentNode) 
{
	// There will be one node pointer change regardless of the scenario (root, left child, or right child)
	nodePointerChanges++;
	if (parentNode == NULL)
	{
		// There was no previous node; this is now the root.
		root = node;
	}
	else if (node->key < parentNode->key)
	{
		parentNode->leftChild = node;
	}
	else 
	{
		parentNode->rightChild = node;
	}
}

/*
	Returns one of the following, depending on the TraversalType:
	    - Number of unique words in document
		- Total number of words in document
		- Height of tree
*/
int BSTree::traverseTree(Node* startingNode, TraversalType traversalType)
{
	// Since this is an in-order traversal (maintains order), three steps are performed:
	//    1. Call this function on the left child if it's not null. (recursive call)
	//    2. Append the weight (depending on TraversalType) to the running total
	//    3. Call this function on the right child if it's not null. (recursive call)
	if (startingNode == NULL) {
		// Return early if the tree is empty or if we are at a leaf node to prevent NPEs.
		return 0;
	}
	int leftCount = traverseTree(startingNode->leftChild, traversalType);
	int nodeCount = traversalType == TraversalType::UNIQUE_WORDS
					? 1
					: startingNode->numberOfOccurrences;
	int rightCount = traverseTree(startingNode->rightChild, traversalType);

	if (traversalType == TraversalType::HEIGHT)
	{
		// Return 1 (which must be 1 since we're starting at the root), along with the higher height of the left or right side
		if (leftCount > rightCount)
		{
			return 1 + leftCount;
		}
		return 1 + rightCount;
	}
	return leftCount + nodeCount + rightCount;
}