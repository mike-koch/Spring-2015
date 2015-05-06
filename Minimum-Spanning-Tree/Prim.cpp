#include "Prim.h"
#include "PriorityQueue.h"
#include "Common.h"

void Prim::execute(Graph* graph, Vertex* root)
{
	List<Edge>* F = new List<Edge>();
	List<Vertex>* Y = new List<Vertex>();
	for (int i = 0; i < graph->verticies->size(); i++)
	{
		Vertex* currentVertex = graph->verticies->get(i);
		currentVertex->weight = INT_MAX;
		currentVertex->parent = NULL;
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
		Vertex* u = queue->extractMinimum();
		List<Vertex>* adjacentVerticies = graph->getAdjacentVerticies(u);
		for (int i = 0; i < adjacentVerticies->size(); i++)
		{
			Vertex* v = adjacentVerticies->get(i);
			if (queue->contains(v) && graph->findEdgeConnectingVerticies(u, v)->weight < v->weight)
			{
				v->parent = u;
				v->weight = graph->findEdgeConnectingVerticies(u, v)->weight;
				F->add(graph->findEdgeConnectingVerticies(u, v));
			}
		}
		Y->add(u);
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
