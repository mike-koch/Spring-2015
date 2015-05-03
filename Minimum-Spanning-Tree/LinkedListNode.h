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
	};
	~LinkedListNode();
	T* element = NULL;
	LinkedListNode* nextNode = NULL;
};
#endif

