#ifndef EDGE_H
#define EDGE_H
#include "Vertex.h"

class Edge
{
public:
	Edge(double edgeWeight, int startVertexId, int endVertexId)
	{
		weight = edgeWeight;
		startingVertexId = startVertexId;
		endingVertexId = endVertexId;
	};
	~Edge();
	double weight;
	unsigned int startingVertexId;
	unsigned int endingVertexId;
};
#endif

