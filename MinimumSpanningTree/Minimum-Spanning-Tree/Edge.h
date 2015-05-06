// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Edge.h - Edge header file, which contains properties about the edge

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
	double weight;
	unsigned int startingVertexId;
	string startingVertexName;
	unsigned int endingVertexId;
	string endingVertexName;
	string getFormattedName()
	{
		// Returns a string in the format <startingVertexName>-<endingVertexName>, helpful when outputting information about the minimum spanning tree
		return startingVertexName + "-" + endingVertexName;
	}
};
#endif

