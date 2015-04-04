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
	Node *f;
	int displacement; // Used for balance factors

	// If the tree is empty, make the root node
	if (root == NULL)
	{
		addNodeToTree(key, NULL);
	}

	Node* q = NULL;
	a = root;
	Node* p = root;

	while (p != NULL) // search tree for insertion point
	{
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
	}

	// We fell off the tree, so we need to make a new node
	Node* newNode = addNodeToTree(key, q);

	// Update our balance factors
	b = p;
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
	
	while (p != newNode)
	{
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
			a->balanceFactor = b->balanceFactor = 0; // Tree is balanced. Put balance factors back at 0
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
			b = c;
		} // end of else (LR Rotation)
	} // end of “if (d = +1)”
	else // d=-1.  This is a right imbalance
	{
		if (b->balanceFactor == -1) // RR rotation
		{
			a->rightChild = b->leftChild;
			b->leftChild = a;
			a->balanceFactor = b->balanceFactor = 0; // Tree is balanced. Put balance factors back at 0
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
			b = c;
		} // end of else (LR Rotation)
	}

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
		parent->leftChild = newNode;
	}
	else
	{
		parent->rightChild = newNode;
	}
	return newNode;
}