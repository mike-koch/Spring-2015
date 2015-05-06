// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// List.h - List template used to hold a collection of objects. The template allows for an arbitrary object/primitive type to be added.

#ifndef LIST_H
#define LIST_H
#include "LinkedListNode.h"
#include <iostream>

template <class T> class List
{
public:
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

	// Returns the element at the specified index by traversing through the list, incrementing an index counter.
	T* get(unsigned int index)
	{
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

	// Removes the element provided, if it exists. LinkedListNode pointers are updated to simply "leap" over the removed node. Otherwise nothing occurs.
	void remove(T* element)
	{
		LinkedListNode<T>* previousElement = NULL;
		LinkedListNode<T>* currentElement = firstElement;
		while (currentElement != NULL)
		{
			if (currentElement->element == element)
			{
				if (previousElement == NULL) // We're removing the first element in the list
				{
					firstElement = currentElement->nextNode;
				}
				else
				{
					// Set the previous element's nextNode to this nodes next element
					previousElement->nextNode = currentElement->nextNode;
				}
				return;
			}
			// Otherwise increment previousElement and currentElement and try again
			previousElement = currentElement;
			currentElement = currentElement->nextNode;
		}
	}

	// Iterates through the list to see if the requested element exists
	bool contains(T* element)
	{
		LinkedListNode<T>* currentNode = firstElement;
		while (currentNode != NULL)
		{
			if (currentNode->element == element)
			{
				return true;
			}
			currentNode = currentNode->nextNode;
		}
		return false;
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

