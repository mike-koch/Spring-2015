#include "BTreeNode.h"

void BTreeNode::initializeArrays()
{
	int i = 0;
	for (i = 0; i < maxNumberOfKeys; i++)
	{
		*keys[i] = '\0';
		numberOfOccurrences[i] = 0;
		childIds[i] = 0;
	}
	childIds[i] = 0; // There's one extra child ID at the end
}