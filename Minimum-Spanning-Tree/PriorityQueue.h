// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// PriorityQueue.h - Priority Queue header file responsible for laying out functions used by the PriorityQueue class. 

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "List.h"
#include "Vertex.h"
class PriorityQueue
{
public:
	void insert(Vertex* element);
	Vertex* getMinimum();
	Vertex* extractMinimum();
	bool contains(Vertex* element);
	unsigned int size();

private:
	List<Vertex>* list = new List<Vertex>();
};
#endif

