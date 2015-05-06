// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// PriorityQueue.cpp - Priority Queue source file. Essentially wraps a List<Vertex>* adding a couple helper methods needed for a priority queue
#include "PriorityQueue.h"

void PriorityQueue::insert(Vertex* element)
{
	list->add(element);
}

// Iterates over the list of elements and finds the vertex with the smallest weight. No elements are removed from the list
Vertex* PriorityQueue::getMinimum()
{
	Vertex* currentMinimum = NULL;
	for (int i = 0; i < list->size(); i++)
	{
		Vertex* currentVertex = list->get(i);
		if (currentMinimum == NULL || currentVertex->weight < currentMinimum->weight)
		{
			currentMinimum = currentVertex;
		}
	}
	return currentMinimum;
}

// Calls getMinimum() to find the smallest element, removes it from the list, and returns it to the caller.
Vertex* PriorityQueue::extractMinimum()
{
	Vertex* minimum = getMinimum();
	list->remove(minimum);
	return minimum;
}

// Simply calls list->contains(element) and returns the result
bool PriorityQueue::contains(Vertex* element)
{
	return list->contains(element);
}

// Returns the number of elements in the priority queue by calling the list's size() function
unsigned int PriorityQueue::size()
{
	return list->size();
}