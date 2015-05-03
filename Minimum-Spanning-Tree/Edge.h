#ifndef EDGE_H
#define EDGE_H
#include "Vertex.h"

class Edge
{
public:
	Edge(int edgeWeight, int startVertexId, int endVertexId)
	{
		weight = edgeWeight;
		startingVertexId = startVertexId;
		endingVertexId = endVertexId;
	};
	~Edge();
	int weight;
	int startingVertexId;
	int endingVertexId;
};
#endif

