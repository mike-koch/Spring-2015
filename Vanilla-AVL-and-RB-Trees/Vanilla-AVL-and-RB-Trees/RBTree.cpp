// RBTree.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/04/2015
// AVL Tree source file. Responsible for insert, search, and traversal.

#include "RBTree.h"
#include <iostream>

//-- PUBLIC Functions
RBTree::RBTree()
{
	nil = new Node();
	nil->key = "";
	nil->leftChild = nil->rightChild = nil->parent = nil;
	nil->color = Color::BLACK;
	root = nil;
}

void RBTree::insertValue(string key)
{
	// 1. Search if the key already exists
	// 2. If yes, just increment the counter
	// 3. Otherwise, create a new node and hang it on the tree. Then fix up the tree if necessary
	Node* newNode = NULL;
	Node* searchedNode = search(root, key);
	// If nil is found, the tree is empty. If the keys are different, the key isn't in the tree yet
	if (searchedNode == nil || searchedNode->key != key)
	{
		//-- We are creating the first node in the tree, or we are simply creating a new node
		newNode = new Node();
		newNode->key = key;
		newNode->parent = searchedNode; // If searches results in no results, search() will return the parent of the new node. If this is
										//     the first node, searchedNode will be nil, which is what we want.
		newNode->leftChild = nil;
		newNode->rightChild = nil;
		newNode->color = Color::RED;
		if (searchedNode == nil)
		{
			//-- We are creating the first node in the tree
			root = newNode;
		}
		else if (newNode->key < searchedNode->key)
		{
			searchedNode->leftChild = newNode;
		}
		else
		{
			searchedNode->rightChild = newNode;
		}
		fixupTree(newNode); // Fix up the tree if anything has gone awry
		return;
	}
	else
	{
		//-- The node already exists in the tree. Simply increment its counter
		searchedNode->numberOfOccurrences++;
		return;
	}
}

void RBTree::outputMetrics()
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
Node* RBTree::search(Node* startingNode, string key)
{
	// If the node's key matches the key being searched, return the node.
	// Else if the key is less than the node's key, search relative to the node's left child, or return the parent of the would-be node if the parent doesn't have a child in the correct direction.
	// Else search relative to the node's right child, or return the parent of the would-be node if the parent doesn't have a child in the correct direction.
	if (key == startingNode->key)
	{
		return startingNode;
	}
	if (key < startingNode->key)
	{
		if (startingNode->leftChild == nil)
		{
			return startingNode; // We found the node that should be the parent of the one we're looking for. Our key doesn't exist, but we now
								 //    now know who the parent should be.
		}
		return search(startingNode->leftChild, key);
	}
	
	// key must be greater than startingNode->key
	if (startingNode->rightChild == nil)
	{
		return startingNode; // We found the node that should be the parent of the one we're looking for. Our key doesn't exist, but we now
							 //    now know who the parent should be.
	}
	return search(startingNode->rightChild, key);
}

/* After an insert, fixupTree checks to make sure the rules of a Red-Black tree are adhered to. fixupTree checks for three cases of an illegal tree:
    - The node added is red, its parent is red, and its uncle is red
	- The node added's uncle is black, and the node added is a right child
	- The node added's uncle is black, and the node added is a left child
*/
void RBTree::fixupTree(Node* startingNode)
{
	Node* uncleNode;
	while (startingNode->parent->color == Color::RED)
	{
		if (startingNode->parent == startingNode->parent->parent->leftChild)
		{
			uncleNode = startingNode->parent->parent->rightChild;
			if (uncleNode->color == Color::RED) // Case 1 violation (re-coloring only)
			{
				startingNode->parent->color = Color::BLACK;
				uncleNode->color = Color::BLACK;
				startingNode->parent->parent->color = Color::RED;
				startingNode = startingNode->parent->parent;
			}
			else
			{
				if (startingNode == startingNode->parent->rightChild)
				{
					startingNode = startingNode->parent; // Case 2 violation
					leftRotate(startingNode);
				}
				startingNode->parent->color = Color::BLACK; // Case 3 violation
				startingNode->parent->parent->color = Color::RED;
				rightRotate(startingNode->parent->parent);
			}
		}
		else
		{
			uncleNode = startingNode->parent->parent->leftChild;
			if (uncleNode->color == Color::RED) // Case 1 violation (re-color only)
			{
				startingNode->parent->color = Color::BLACK;
				uncleNode->color = Color::BLACK;
				startingNode->parent->parent->color = Color::RED;
				startingNode = startingNode->parent->parent;
			}
			else
			{
				if (startingNode == startingNode->parent->leftChild)
				{
					startingNode = startingNode->parent; // Case 2 violation
					rightRotate(startingNode);
				}
				startingNode->parent->color = Color::BLACK; // Case 3 violation
				startingNode->parent->parent->color = Color::RED;
				leftRotate(startingNode->parent->parent);
			}
		}
	}
	root->color = Color::BLACK;
}

void RBTree::leftRotate(Node* startingNode)
{
	Node* originalRightChild = startingNode->rightChild;
	startingNode->rightChild = originalRightChild->leftChild;
	if (originalRightChild->leftChild != nil)
	{
		originalRightChild->leftChild->parent = startingNode;
	}
	originalRightChild->parent = startingNode->parent;
	if (startingNode->parent == nil)
	{
		root = originalRightChild;
	}
	else if (startingNode == startingNode->parent->leftChild)
	{
		startingNode->parent->leftChild = originalRightChild;
	}
	else
	{
		startingNode->parent->rightChild = originalRightChild;
	}

	originalRightChild->leftChild = startingNode;
	startingNode->parent = originalRightChild;
}

void RBTree::rightRotate(Node* startingNode)
{
	Node* originalLeftChild = startingNode->leftChild;
	startingNode->leftChild = originalLeftChild->rightChild;
	if (originalLeftChild->rightChild != nil)
	{
		originalLeftChild->rightChild->parent = startingNode;
	}
	originalLeftChild->parent = startingNode->parent;
	if (startingNode->parent == nil)
	{
		root = originalLeftChild;
	}
	else if (startingNode == startingNode->parent->rightChild)
	{
		startingNode->parent->rightChild = originalLeftChild;
	}
	else
	{
		startingNode->parent->leftChild = originalLeftChild;
	}

	originalLeftChild->rightChild = startingNode;
	startingNode->parent = originalLeftChild;
}

int RBTree::traverseTree(Node* startingNode, TraversalType traversalType)
{
	// Since this is an in-order traversal (maintains order), three steps are performed:
	//    1. Call this function on the left child if it's not nil. (recursive call)
	//    2. Append the weight (depending on TraversalType) to the running total
	//    3. Call this function on the right child if it's not nil. (recursive call)
	if (startingNode == nil) {
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