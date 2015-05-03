// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 04/28/2015
// Main.cpp - Responsible for parsing input and executing required tree algorithms

#include <iostream>
#include <climits>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include "List.h"
using namespace std;

// Function prototypes
List* parseVerticies(unsigned int numberOfHeaders);
List* parseEdges(unsigned int numberOfHeaders);

int main()
{
	unsigned int numberOfHeaders;
	cin >> numberOfHeaders;

	List* vertexList = parseVerticies(numberOfHeaders);
	List* edgeList = parseEdges(numberOfHeaders); // Returns a list of the parsed edges	

	// Create our graph
	Graph* graph = new Graph();
}

// There will be N verticies for N numberOfHeaders. Create a vertex for each header with a unique ID value
List* parseVerticies(unsigned int numberOfHeaders)
{
	List* vertexList = new List();
	for (unsigned int i = 0; i < numberOfHeaders; i++)
	{
		// Create a new vertex of id = i and name = the string passed in through the console. Add it to the list of verticies
		string name;
		cin >> name;
		vertexList->add(new Vertex(i, name));
	}
	return vertexList;
}

// The next N*N characters indicate the edges that are connected to each vertex along with the weight. The first N pertain to the first
//   edge, the second N pertain to the second edge, and so forth.
List* parseEdges(unsigned int numberOfHeaders)
{
	List* edgeList = new List();
	for (unsigned int i = 0; i < numberOfHeaders; i++)
	{
		// the next N values indicate the edges that exist between two nodes.
		// check if the edge has already been created, and if not, create it.
		for (unsigned int j = 0; j < numberOfHeaders; j++)
		{
			// j indicates the current COLUMN we are looking at
			// i indicates the current ROW    we are looking at
			// ex. if i = 1 and j = 3, we are looking at the edge that connects B and D (if the verticies are named alphabetically starting w/A)

			int nextWeight;
			cin >> nextWeight;
			if (nextWeight != 0) // If the next weight is not 0, then we possibly have a newly discovered edge
			{
				bool shouldAddEdge = true;
				// check if we already have this edge. if not, create it. if we do, just ignore it.
				unsigned int currentIndex = 0;
				Edge* currentEdge = (Edge*)edgeList->get(currentIndex);
				while (currentEdge != NULL)
				{
					// If the edge's startingVertex and endingVertex are i and j (in either direction), set shouldAddEdge to FALSE and break out of the loop
					if ((currentEdge->startingVertexId == i && currentEdge->endingVertexId == j) ||
						(currentEdge->startingVertexId == j && currentEdge->endingVertexId == i))
					{
						//-- we already have the edge recorded
						shouldAddEdge = false;
						break;
					}
					// Otherwise, grab the next edge in the list and repeat the process.
					currentEdge = (Edge*)edgeList->get(++currentIndex);
				}

				// If we never found an edge with the current verticies, we should create a new edge and add it to the list.
				if (shouldAddEdge)
				{
					edgeList->add(new Edge(nextWeight, i, j));
				}
			}
		}
	}
	return edgeList;
}