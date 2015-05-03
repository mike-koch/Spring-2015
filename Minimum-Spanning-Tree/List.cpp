#include "List.h"
#include <iostream>
List::List()
{
}

void List::add(void* item)
{
	// Create a linked list node and append it after the last item added. Returns the index of the new node
	LinkedListNode* newNode = new LinkedListNode(item, NULL);
	if (firstElement == NULL)
	{
		firstElement = newNode;
		lastElement = newNode;
	}
	else if (lastElement != NULL)
	{
		lastElement->nextNode = newNode; // Update next pointer for the last element in the list, as we're adding a new item.
	}

	lastElement = newNode;
}

void* List::get(unsigned int index)
{
	// Returns the element at the specified index by traversing through the list, incrementing an index counter.
	unsigned int currentIndex = 0;
	LinkedListNode* currentNode = firstElement;
	while (currentNode != NULL)
	{
		if (currentIndex == index)
		{
			return currentNode->element;
		}
		currentNode = currentNode->nextNode;
		currentIndex++;
	}
	return NULL;
}


List::~List()
{
}
