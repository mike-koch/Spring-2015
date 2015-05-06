// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// LinkedListNode.h - LinkedListNode template used by the List class. The node is responsible for holding the element, as well as the next
//    element in the list via the "nextNode" property.

#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H
#include <iostream>
template <class T> class LinkedListNode
{
public:
	LinkedListNode(T* listElement, LinkedListNode* listNextNode)
	{
		element = listElement;
		nextNode = listNextNode;
	}
	T* element = NULL;
	LinkedListNode* nextNode = NULL;
};
#endif

