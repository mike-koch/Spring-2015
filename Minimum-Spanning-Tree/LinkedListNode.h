#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H
#include <iostream>
class LinkedListNode
{
public:
	LinkedListNode(void* listElement, LinkedListNode* listNextNode)
	{
		element = listElement;
		nextNode = listNextNode;
	};
	~LinkedListNode();
	void* element = NULL;
	LinkedListNode* nextNode = NULL;
};
#endif

