#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H
class LinkedListNode
{
public:
	LinkedListNode(void* listElement, LinkedListNode* listNextNode)
	{
		element = listElement;
		nextNode = listNextNode;
	};
	~LinkedListNode();
	void* element;
	LinkedListNode* nextNode;
};
#endif

