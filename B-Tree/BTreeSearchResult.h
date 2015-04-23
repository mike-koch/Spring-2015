// BTreeSearchResult.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/20/2015
// Returns relevant information about the node returned from BTree::search. Includes the node itself and which key "slot" the key is in.

#ifndef BTREESEARCHRESULT_H
#define BTREESEARCHRESULT_H
#include "BTreeNode.h"

struct BTreeSearchResult
{
	BTreeNode node;
	unsigned int keyPosition;
};
#endif