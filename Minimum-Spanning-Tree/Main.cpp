// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 04/28/2015
// Main.cpp - Responsible for parsing input and executing required tree algorithms

#include <iostream>
#include <climits>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include "LinkedListNode.h"
using namespace std;

int main()
{
	int numberOfHeaders;
	cin >> numberOfHeaders;

	// There will be N nodes for N numberOfHeaders
	LinkedListNode* firstVertex = NULL;
	LinkedListNode* mostRecentVertex = NULL;
	for (int i = 0; i < numberOfHeaders; i++)
	{
		// Create a new vertex of id = i and name = the string passed in through the console
		string name;
		cin >> name;
		Vertex* vertex = new Vertex(i, name);

		// add the vertex to the list. if this is the first node, simply set firstNode equal to this vertex
		LinkedListNode* node = new LinkedListNode(vertex, NULL);
		if (firstVertex == NULL)
		{
			firstVertex = node;
		} 
		else
		{
			// Otherwise, set the mostRecentNode's nextNode to this node
			mostRecentVertex->nextNode = node;
		}

		// This new vertex was the node most recently created, so keep track of it.
		mostRecentVertex = node;
	}

	// The next N*N characters indicate the edges that are connected to each vertex along with the weight. The first N pertain to the first
	//   edge, the second N pertain to the second edge, and so forth.
	LinkedListNode* firstEdge = NULL;
	LinkedListNode* mostRecentEdge = NULL;
	for (int i = 0; i < numberOfHeaders * numberOfHeaders; i++)
	{
		// the next N values indicate the edges that exist between two nodes.
		// check if the edge has already been created, and if not, create it.
		for (int j = 0; j < numberOfHeaders; j++)
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
				LinkedListNode* currentEdge = firstEdge;
				while (currentEdge != NULL)
				{
					Edge* edge = (Edge*)currentEdge->element;
					// If the edge's startingVertex and endingVertex are i and j (in either direction), set shouldAddEdge to FALSE and break out of the loop
					if ((edge->startingVertexId == i && edge->endingVertexId == j) ||
						(edge->startingVertexId == j && edge->endingVertexId == i))
					{
						//-- we already have the edge recorded
						shouldAddEdge = false;
						break;
					}
				}
				if (shouldAddEdge)
				{
					//-- Create a new edge that connects vertex i to vertex j
					Edge* newEdge = new Edge(nextWeight, i, j);

					// add the edge to the list. if this is the first node, simply set firstNode equal to this edge
					LinkedListNode* node = new LinkedListNode(newEdge, NULL);
					if (firstEdge == NULL)
					{
						firstEdge = node;
					}
					else
					{
						// Otherwise, set the mostRecentEdge's nextNode to this node
						mostRecentEdge->nextNode = node;
					}

					// This new edge was the node most recently created, so keep track of it.
					mostRecentEdge = node;
				}
			}
		}
	}

	// Create our graph
	Graph* graph = new Graph();
}