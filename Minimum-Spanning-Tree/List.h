#ifndef LIST_H
#define LIST_H
#include "LinkedListNode.h"
#include <iostream>

template <class T> class List
{
public:
	template <class T>
	void add(T* item)
	{
		// Create a linked list node and append it after the last item added. Returns the index of the new node
		LinkedListNode<T>* newNode = new LinkedListNode<T>(item, NULL);
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

	template <class T>
	T* get(unsigned int index)
	{
		// Returns the element at the specified index by traversing through the list, incrementing an index counter.
		unsigned int currentIndex = 0;
		LinkedListNode<T>* currentNode = firstElement;
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

	// Iterates through all of the nodes, increasing a counter and returning said counter.
	int size()
	{
		int currentSize = 0;
		LinkedListNode<T>* currentNode = firstElement;
		while (currentNode != NULL)
		{
			currentSize++;
			currentNode = currentNode->nextNode;
		}
		return currentSize;
	}

private:
	// Keeps track of the first element in the list (for traversing), and the last element (for adding)
	LinkedListNode<T>* firstElement = NULL;
	LinkedListNode<T>* lastElement = NULL;
};
#endif

