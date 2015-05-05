#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "List.h"
#include "Edge.h"
#include "Vertex.h"
class Graph
{
public:
	Graph(List<Edge>* edgeList, List<Vertex>* vertexList)
	{
		edges = edgeList;
		verticies = vertexList;
	};
	~Graph();
	List<Edge>* edges;
	List<Vertex>* verticies;
	List<Vertex>* getAdjacentVerticies(Vertex* startingVertex);
	Edge* findEdgeConnectingVerticies(Vertex* vertexOne, Vertex* vertexTwo);
};
#endif

