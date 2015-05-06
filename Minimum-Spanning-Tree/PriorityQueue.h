#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "List.h"
#include "Vertex.h"
class PriorityQueue
{
public:
	void insert(Vertex* element)
	{
		list->add(element);
	};
	Vertex* getMinimum()
	{
		Vertex* currentMinimum = NULL;
		// Go through the array, and find the element with the smallest weight. Don't remove it from the list, however.
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
	Vertex* extractMinimum()
	{
		// Finds the current minimum and removes it from the queue.
		Vertex* minimum = getMinimum();
		list->remove(minimum);
		return minimum;

	}
	bool contains(Vertex* element)
	{
		return list->contains(element);
	}
	unsigned int size()
	{
		return list->size();
	}

private:
	List<Vertex>* list = new List<Vertex>();
};
#endif

