// BTreeNode.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// Source file used for the BTreeNode

#include "BTreeNode.h"

void BTreeNode::initializeArrays()
{
	unsigned int i = 0;
	for (i = 0; i <= maxNumberOfKeys; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			keys[i][j] = '\0';
		}
		numberOfOccurrences[i] = 1; // Always start with one occurrence
		childIds[i] = 0;
	}
	childIds[i] = 0; // There's one extra child ID at the end
}