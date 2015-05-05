#ifndef EDGE_H
#define EDGE_H
#include "Vertex.h"
#include <string>
using namespace std;

class Edge
{
public:
	Edge(double edgeWeight, int startVertexId, int endVertexId, string startVertexName, string endVertexName)
	{
		weight = edgeWeight;
		startingVertexId = startVertexId;
		endingVertexId = endVertexId;
		startingVertexName = startVertexName;
		endingVertexName = endVertexName;
	}
	~Edge();
	double weight;
	unsigned int startingVertexId;
	string startingVertexName;
	unsigned int endingVertexId;
	string endingVertexName;
	string getFormattedName()
	{
		return startingVertexName + "-" + endingVertexName;
	}
};
#endif

