// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Prim.cpp - Prim's Algorithm source file. Executes Prim's algorithm for a given graph and an arbitrary starting vertex.

#include "Prim.h"
#include "PriorityQueue.h"
#include "Common.h"

void Prim::execute(Graph* graph, Vertex* root)
{
	// To begin, set each vertex's weight to infinity (or in this case, INT_MAX), and its parent to NULL.
	for (int i = 0; i < graph->verticies->size(); i++)
	{
		Vertex* currentVertex = graph->verticies->get(i);
		currentVertex->weight = INT_MAX;
		currentVertex->parent = NULL;
	}

	// We can reach our starting vertex immediately, so its weight is zero.
	root->weight = 0;

	// Create a new priority queue and add each vertex to the queue
	PriorityQueue* queue = new PriorityQueue();
	for (int i = 0; i < graph->verticies->size(); i++)
	{
		queue->insert(graph->verticies->get(i));
	}

	// Check for the lightest edge for each vertex in the queue
	while (queue->size() != 0)
	{
		// Extract the vertex that currently has the lowest weight in the priority queue, and get all verticies that are adjacent to the current vertex.
		Vertex* currentVertex = queue->extractMinimum();
		List<Vertex>* adjacentVerticies = graph->getAdjacentVerticies(currentVertex);

		// Iterate over each adjacent vertex to check if the path to this edge is lighter than any other previously discovered edge. The vertex's
		//    weight currently stores the lighest edge (via the parent and weight properties), so we can easily check if this edge is lighter than
		//    the current most lightest edge.
		for (int i = 0; i < adjacentVerticies->size(); i++)
		{
			Vertex* currentAdjacentVertex = adjacentVerticies->get(i);
			if (queue->contains(currentAdjacentVertex) && 
				graph->findEdgeConnectingVerticies(currentVertex, currentAdjacentVertex)->weight < currentAdjacentVertex->weight)
			{
				// If we got here, then we found a new lightest-weight edge. Update the parent of the adjacent vertex to the vertex we're currently
				//    exploring, and update its weight to be the edge's weight
				currentAdjacentVertex->parent = currentVertex;
				currentAdjacentVertex->weight = graph->findEdgeConnectingVerticies(currentVertex, currentAdjacentVertex)->weight;
			}
		}
	}

	// We only manipulated the graph's current list verticies, so the caller will have the updated graph. Therefore, we don't need to return anything
	return;
}
