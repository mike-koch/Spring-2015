#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "List.h"
class Graph
{
public:
	Graph(List* edgeList, List* vertexList)
	{
		edges = edgeList;
		verticies = vertexList;
	};
	~Graph();
	List* edges;
	List* verticies;
};
#endif

