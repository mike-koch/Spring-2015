#include "Prim.h"
#include "PriorityQueue.h"

void Prim::execute(Graph* graph, Vertex* root)
{
	for (int i = 0; i < graph->verticies->size(); i++)
	{
		Vertex* currentVertex = graph->verticies->get(i);
		currentVertex->weight = INT_MAX;
		currentVertex->predecessor = NULL;
	}
	root->weight = 0;

	// Create a new queue and add each vertex to the queue
	PriorityQueue* queue = new PriorityQueue();
	for (int i = 0; i < graph->verticies->size(); i++)
	{
		queue->insert(graph->verticies->get(i));
	}
	while (queue->size() != 0)
	{
		Vertex* currentVertex = queue->extractMinimum();
		List<Vertex>* adjacentVerticies = graph->getAdjacentVerticies(currentVertex);
		for (int i = 0; i < adjacentVerticies->size(); i++)
		{
			Vertex* currentAdjacentVertex = adjacentVerticies->get(i);
			if (queue->contains(currentAdjacentVertex) && graph->findEdgeConnectingVerticies(currentVertex, currentAdjacentVertex)->weight < currentAdjacentVertex->weight)
			{
				currentAdjacentVertex->predecessor = currentVertex;
				currentAdjacentVertex->weight = graph->findEdgeConnectingVerticies(currentVertex, currentAdjacentVertex)->weight;
			}
		}
	}

	// We only manipulated the graph's current list verticies, so the caller will have the updated graph
	return;
}

Prim::Prim()
{
}


Prim::~Prim()
{
}
