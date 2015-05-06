// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Graph.h - Graph header file, which contains properties needed for the graph as well as helper functions

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
	List<Edge>* edges;
	List<Vertex>* verticies;
	List<Vertex>* getAdjacentVerticies(Vertex* startingVertex);
	Edge* findEdgeConnectingVerticies(Vertex* vertexOne, Vertex* vertexTwo);
};
#endif

