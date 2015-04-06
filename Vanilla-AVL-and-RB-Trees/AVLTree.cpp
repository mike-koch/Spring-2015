// AVLTree.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/02/2015
// AVL Tree source file. Responsible for insert, search, and traversal.

#include "AVLTree.h"
#include <iostream>

//-- PUBLIC functions
void AVLTree::insertValue(string key)
{
	// 1. Search if the key already exists
	// 2. If yes, just increment the counter
	// 3. Otherwise, create a new node and hang it on the tree.
	Node *a, *b, *c, *cl, *cr; // Node pointers used for searching and rebalancing
	Node *f = NULL;
	int displacement; // Used for balance factors

	// If the tree is empty, make the root node
	if (root == NULL)
	{
		addNodeToTree(key, NULL);
		return; // There's no need to even check for an imbalance, since we just added our first node
	}

	Node* q = NULL;
	a = root;
	Node* p = root;

	while (p != NULL) // search tree for insertion point
	{
		keyComparisons++;
		if (key == p->key)
		{
			p->numberOfOccurrences++;  // This node is a duplicate, so increment its counter
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
			? p->leftChild
			: p->rightChild;
		keyComparisons++;
	}

	// We fell off the tree, so we need to make a new node
	Node* newNode = addNodeToTree(key, q);

	// Update our balance factors
	keyComparisons++;
	if (key > a->key)
	{
		p = a->rightChild;
		displacement = -1;
	}
	else
	{
		p = a->leftChild;
		displacement = 1;
	}
	b = p;
	
	while (p != newNode)
	{
		keyComparisons++;
		if (key > p->key)
		{
			p->balanceFactor = -1;
			p = p->rightChild;
		}
		else
		{
			p->balanceFactor = 1;
			p = p->leftChild;
		}
	}

	// Now we check the BF at A and see if we just 
	// BALANCED the tree, IMBALANCED the tree, or if 
	// it is still BALANCED ENOUGH.

	if (a->balanceFactor == 0)				// Tree WAS completely balanced.  The
	{										// insert pushed it to slight imbalance
		a->balanceFactor = displacement;    // set the BF to +/- 1.  This is close
		return;								// enough to live with, so exit now
	}

	if (a->balanceFactor == -displacement) // If the tree had a slight imbalance
	{									   // the OTHER way, did the insertion
		a->balanceFactor = 0;			   // throw the tree INTO balance?
		return;							   // If so, set the BF to zero & return
	}

	if (displacement == +1) // left imbalance.  LL or LR?
	{
		if (b->balanceFactor == +1) // LL rotation
		{
			a->leftChild = b->rightChild;
			b->rightChild = a;
			nodePointerChanges += 2; // We made two node pointer changes here
			a->balanceFactor = b->balanceFactor = 0; // Tree is balanced. Put balance factors back at 0
			balanceFactorChanges += 2; // We made two balance factor changes here
		}
		else  // LR Rotation: three cases
		{
			c = b->rightChild; // C is B's right child
			cl = c->leftChild; // CL and CR are C's left
			cr = c->rightChild; //    and right children
			a->leftChild = cr;
			b->rightChild = cl;
			c->leftChild = b;
			c->rightChild = a;
			nodePointerChanges += 4; // We made four node pointer changes here
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
			balanceFactorChanges += 3; // We made three balance factor changes regardless of C's balance factor
			b = c;
		} // end of else (LR Rotation)
	} // end of “if (d = +1)”
	else // d=-1.  This is a right imbalance
	{
		if (b->balanceFactor == -1) // RR rotation
		{
			a->rightChild = b->leftChild;
			b->leftChild = a;
			nodePointerChanges += 2; // We made two node pointer changes here
			a->balanceFactor = b->balanceFactor = 0; // Tree is balanced. Put balance factors back at 0
			balanceFactorChanges += 2; // We made two balance factor changes here
		}
		else  // LR Rotation: three cases
		{
			c = b->leftChild; // C is B's left child
			cl = c->leftChild; // CL and CR are C's left
			cr = c->rightChild; //    and right children
			a->rightChild = cl;
			b->leftChild = cr;
			c->leftChild = a;
			c->rightChild = b;
			nodePointerChanges += 4; // We made four node pointer changes here
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
			balanceFactorChanges += 3; // We made three balance factor changes regardless of C's original balance factor
			b = c;
		} // end of else (LR Rotation)
	}

	nodePointerChanges++; // Regardless of the path chosen below, there will be exactly one node pointer change
	// did we rebalance the root?
	if (f == NULL) 
	{ 
		root = b;
		return; 
	}

	// otherwise, we rebalanced whatever was the
	// child (left or right) of F.
	if (a == f->leftChild) 
	{ 
		f->leftChild = b; 
		return; 
	}
	if (a == f->rightChild) 
	{ 
		f->rightChild = b; 
		return; 
	}

}

void AVLTree::outputMetrics()
{
	cout << "Height of tree: " << to_string(traverseTree(root, TraversalType::HEIGHT) - 1) << endl;
	cout << "Number of key comparisons: " << to_string(keyComparisons) << endl;
	cout << "Number of node pointer changes: " << to_string(nodePointerChanges) << endl;
	cout << "Total number of unique words: " << to_string(traverseTree(root, TraversalType::UNIQUE_WORDS)) << endl;
	cout << "Total number of words (incl. duplicates): " << to_string(traverseTree(root, TraversalType::TOTAL_WORDS)) << endl;
	cout << "Number of balance factor changes: " << to_string(balanceFactorChanges) << endl;
}

//-- PRIVATE functions
Node* AVLTree::addNodeToTree(string key, Node* parent)
{
	Node* newNode = new Node();
	newNode->key = key;
	newNode->leftChild = newNode->rightChild = NULL;
	newNode->balanceFactor = 0;

	if (parent == NULL)
	{
		// We're at the root of the tree, so just assign the root to this new node
		root = newNode;
	}
	else if (key < parent->key)
	{
		keyComparisons++;
		parent->leftChild = newNode;
	}
	else
	{
		keyComparisons++;
		parent->rightChild = newNode;
	}
	nodePointerChanges++; // There was one pointer change to set the new node
	return newNode;
}

/*
Returns one of the following, depending on the TraversalType:
- Number of unique words in document
- Total number of words in document
- Height of tree + 1 (the height is offset by 1 to return a non-zero value. The caller is responsible for subtracting one off)
*/
int AVLTree::traverseTree(Node* startingNode, TraversalType traversalType)
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