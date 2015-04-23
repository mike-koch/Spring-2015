// AVLTree.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// AVL Tree source file. Responsible for insert, search, and traversal.

#include "AVLTree.h"
#include "DiskIO.h"
#include <iostream>
#include <fstream>
//#define DEBUG  // Uncomment this line to enable DEBUG statements

const unsigned int NULL_NODE_ID = 0;
static unsigned int nextNewNodeNumber = 1;
int iteration = 0;
//-- PUBLIC functions

// Inserts a value by doing the following:
// 1. Search if the key already exists
// 2. If yes, just increment the counter
// 3. Otherwise, create a new node and hang it on the tree
void AVLTree::insertValue(string& key)
{
#ifdef DEBUG
	cout << "CURRENTLY AT ITERATION: " << ++iteration << endl;
	cout << "Root is currently has id #" << root << " and getNode(root) returned a node with id: " << getId(getNode(root)) << endl;
#endif
	AVLNode *a, *b, *c; // Node pointers used for searching and rebalancing
	int cl, cr;
	AVLNode *f = NULL;
	int displacement; // Used for balance factors

	// If the tree is empty, make the root node
	if (root == NULL_NODE_ID)
	{
		addNodeToTree(key, NULL);
		return; // There's no need to even check for an imbalance, since we just added our first node
	}

	AVLNode* q = NULL;
	a = getNode(root);
	AVLNode* p = getNode(root);

	while (p != NULL) // search tree for insertion point
	{
		if (key == p->key)
		{
			p->numberOfOccurrences++;  // This node is a duplicate, so increment its counter
			saveNode(p); // Save the node
			return; // No need to check or adjust balance factors, so return.
		}
		if (p->balanceFactor != 0)   // remember the last place we saw
		{
			// Keep track of the deepest node that has a balance factor != 0 and its parent
			a = p;
			f = q;
		}
		q = p;
		p = (key < p->key)
			? getNode(p->leftChildId)
			: getNode(p->rightChildId);
	}

	// We fell off the tree, so we need to make a new node
	AVLNode* newNode = addNodeToTree(key, q);

	// a and/or f may have been updated. grab the latest versions of them.
	a = getNode(getId(a));
	f = getNode(getId(f));

	// Update our balance factors
	if (key > a->key)
	{
		p = getNode(a->rightChildId);
		displacement = -1;
	}
	else
	{
		p = getNode(a->leftChildId);
		displacement = 1;
	}
	b = p;

	while (getId(p) != getId(newNode))
	{
		if (key > p->key)
		{
			p->balanceFactor = -1;
			saveNode(p);
			p = getNode(p->rightChildId);
		}
		else
		{
			p->balanceFactor = 1;
			saveNode(p);
			p = getNode(p->leftChildId);
		}
	}

	// Now we check the BF at A and see if we just 
	// BALANCED the tree, IMBALANCED the tree, or if 
	// it is still BALANCED ENOUGH.

	if (a->balanceFactor == 0)				// Tree WAS completely balanced.  The
	{										// insert pushed it to slight imbalance
		a->balanceFactor = displacement;    // set the BF to +/- 1.  This is close
		saveNode(a);
		return;								// enough to live with, so exit now
	}

	if (a->balanceFactor == -displacement) // If the tree had a slight imbalance
	{									   // the OTHER way, did the insertion
		a->balanceFactor = 0;			   // throw the tree INTO balance?
		saveNode(a);
		return;							   // If so, set the BF to zero & return
	}

	if (displacement == +1) // left imbalance.  LL or LR?
	{
		if (b->balanceFactor == +1) // LL rotation
		{
			a->leftChildId = b->rightChildId;
			b->rightChildId = getId(a);
			a->balanceFactor = b->balanceFactor = 0; // Tree is balanced. Put balance factors back at 0
			saveNode(a);
			saveNode(b);
		}
		else  // LR Rotation: three cases
		{
			c = getNode(b->rightChildId); // C is B's right child
			cl = c->leftChildId; // CL and CR are C's left
			cr = c->rightChildId; //    and right children
			a->leftChildId = cr;
			b->rightChildId = cl;
			c->leftChildId = getId(b);
			c->rightChildId = getId(a);
			switch (c->balanceFactor)
			{
				// Set the new BF’s at A and B, based on the
				// BF at C. Note: There are 3 sub-cases
			case 0:
				b->balanceFactor = a->balanceFactor = 0;
				break;
			case 1:
				b->balanceFactor = 0;
				a->balanceFactor = -1;
				break;
			case -1:
				b->balanceFactor = 1;
				a->balanceFactor = 0;
				break;
			}
			c->balanceFactor = 0;
			saveNode(a);
			saveNode(b);
			saveNode(c);
			b->id = getId(c);
		} // end of else (LR Rotation)
	} // end of "if (d = +1)"
	else // d=-1.  This is a right imbalance
	{
		if (b->balanceFactor == -1) // RR rotation
		{
			a->rightChildId = b->leftChildId;
			b->leftChildId = getId(a);
			a->balanceFactor = b->balanceFactor = 0; // Tree is balanced. Put balance factors back at 0
			saveNode(a);
			saveNode(b);
		}
		else  // RL Rotation: three cases
		{
			c = getNode(b->leftChildId); // C is B's left child
			cl = c->leftChildId; // CL and CR are C's left
			cr = c->rightChildId; //    and right children
			a->rightChildId = cl;
			b->leftChildId = cr;
			c->leftChildId = getId(a);
			c->rightChildId = getId(b);
			switch (c->balanceFactor)
			{
				// Set the new BF’s at A and B, based on the
				// BF at C. Note: There are 3 sub-cases
			case 0:
				b->balanceFactor = a->balanceFactor = 0;
				break;
			case 1:
				a->balanceFactor = 0;
				b->balanceFactor = -1;
				break;
			case -1:
				a->balanceFactor = 1;
				b->balanceFactor = 0;
				break;
			}

			c->balanceFactor = 0;
			saveNode(a);
			saveNode(b);
			saveNode(c);
			b->id = getId(c);
		} // end of else (LR Rotation)
	}

	// did we rebalance the root?
	if (f == NULL || f->id == NULL_NODE_ID)
	{
		root = getId(b);
#ifdef DEBUG
		cout << "216: Root is now pointing at id: " << root << "with getNode() returning as the ID: " << getId(getNode(root)) << endl;
#endif
		return;
	}

	// otherwise, we rebalanced whatever was the
	// child (left or right) of F.
	if (a->id == f->leftChildId)
	{
		f->leftChildId = getId(b);
		saveNode(f);
		return;
	}
	if (a->id == f->rightChildId)
	{
		f->rightChildId = getId(b);
		saveNode(f);
		return;
	}
}

/* Outputs key information about the tree, including:
- Height of tree
- Number of unique words
- Number of words including duplicates
- Number of disk reads/writes
- Total file size
*/
void AVLTree::outputMetrics()
{
	cout << "Height of tree: " << to_string(traverseTree(root, TraversalType::HEIGHT) - 1) << endl;

	// AVL Trees have one key per node, so the # of nodes and # of unique words are the same
	int numberOfUniqueWords = traverseTree(root, TraversalType::UNIQUE_WORDS);
	cout << "Total number of nodes: " << to_string(numberOfUniqueWords) << endl;
	cout << "Total number of unique words: " << to_string(numberOfUniqueWords) << endl;

	cout << "Total number of words (incl. duplicates): " << to_string(traverseTree(root, TraversalType::TOTAL_WORDS)) << endl;
	cout << "Total number of disk reads: " << to_string(numberOfReads) << endl;
	cout << "Total number of disk writes: " << to_string(numberOfWrites) << endl;
	cout << "File size: " << to_string(DiskIO::getFileSize()) << " bytes" << endl;
}

//-- PRIVATE functions
AVLNode* AVLTree::addNodeToTree(string& key, AVLNode* parent)
{
	AVLNode* newNode = new AVLNode();
	newNode->id = nextNewNodeNumber++;
	newNode->key = key;
	newNode->leftChildId = newNode->rightChildId = NULL_NODE_ID;
	newNode->balanceFactor = 0;

	if (parent == NULL || parent->id == NULL_NODE_ID)
	{
		// We're at the root of the tree, so just assign the root to this new node
		root = getId(newNode);
		
	}
	else if (key < parent->key)
	{
		parent->leftChildId = newNode->id;
	}
	else
	{
		parent->rightChildId = newNode->id;
	}
	saveNode(parent);
	saveNode(newNode);
	return newNode;
}

/*
Returns one of the following, depending on the TraversalType:
- Number of unique words in document
- Total number of words in document
- Height of tree + 1 (the height is offset by 1 to return a non-zero value. The caller is responsible for subtracting one off)
*/
int AVLTree::traverseTree(int startingNodeNumber, TraversalType traversalType)
{
	// Since this is an in-order traversal (maintains order), three steps are performed:
	//    1. Call this function on the left child if it's not null. (recursive call)
	//    2. Append the weight (depending on TraversalType) to the running total
	//    3. Call this function on the right child if it's not null. (recursive call)
	if (startingNodeNumber == NULL_NODE_ID) {
		// Return early if the tree is empty or if we are at a leaf node to prevent NPEs.
		return 0;
	}
	AVLNode* startingNode = getNode(startingNodeNumber);
	int leftCount = traverseTree(startingNode->leftChildId, traversalType);
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
	return leftCount + nodeCount + rightCount;
}

// Return the node's id, or NULL_NODE_ID if the node passed in is actually NULL
unsigned int AVLTree::getId(AVLNode* node)
{
	return node != NULL 
		? node->id 
		: NULL_NODE_ID;
}

AVLNode* AVLTree::getNode(int nodeNumber)
{
	if (nodeNumber == 0)
	{
		return NULL;
	}
	numberOfReads++;
	return DiskIO::loadAVLNode(nodeNumber);
}

void AVLTree::saveNode(AVLNode* node)
{
	if (node == NULL || node->id == 0)
	{
#ifdef DEBUG
		if (node == NULL)
		{
			cout << "Skipped saving NULL node";
		}
		else
		{
			cout << "Skipped saving node with id = 0. It's key was " << node->key << endl;
		}
#endif
		return;
	}
#ifdef DEBUG
	cout << "Saving a node with ID: " << getId(node) << endl;
	cout << "   |-- ID: " << getId(node) << endl;
	cout << "   |-- RC: " << node->rightChildId << endl;
	cout << "   |-- LC: " << node->leftChildId << endl;
	cout << "   |-- BF: " << node->balanceFactor << endl;
	cout << "   |--KEY: " << node->key << endl;
	cout << "   |-SIZE: " << sizeof(*node) << endl;
	cout << "   ----\n";
#endif
	numberOfWrites++;
	DiskIO::saveAVLNode(node);
}