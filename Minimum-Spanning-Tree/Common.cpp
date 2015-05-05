#include "Common.h"

void Common::sortEdges(List<Edge>* edges)
{
	List<Edge>* sortedEdges = new List<Edge>();
	LinkedListNode<Edge>* firstNode = NULL;
	for (int i = 1; i < edges->size(); i++)
	{
		// Perform an insertion sort on the edges.
		Edge* tempEdge = edges->get<Edge>(i);

		int j;
		for (j = i - 1; j > -1 && tempEdge->weight < edges->get<Edge>(j)->weight; j--)
		{
			moveEdge(edges->get<Edge>(j), edges->get<Edge>(j + 1));
		}

		moveEdge(tempEdge, edges->get<Edge>(j + 1));
	}
}

void Common::makeSet(Vertex* vertex)
{
	vertex->parent = vertex;
	vertex->rank = 0;
}

Vertex* Common::findSet(Vertex* vertex)
{
	if (vertex != vertex->parent)
	{
		vertex->parent = findSet(vertex->parent);
	}
	return vertex->parent;
}

void Common::unionVerticies(Vertex* vertexOne, Vertex* vertexTwo)
{
	linkVerticies(findSet(vertexOne), findSet(vertexTwo));
}

void Common::moveEdge(Edge* source, Edge* destination)
{
	// Perform a hard copy of the data from the source edge to the destination edge
	destination->endingVertexId = source->endingVertexId;
	destination->startingVertexId = source->startingVertexId;
	destination->weight = source->weight;
}

void Common::linkVerticies(Vertex* vertexOne, Vertex* vertexTwo)
{
	if (vertexOne->rank > vertexTwo->rank)
	{
		vertexTwo->parent = vertexOne;
	}
	else
	{
		vertexOne->parent = vertexTwo;
		if (vertexOne->rank == vertexTwo->rank)
		{
			vertexTwo->rank++;
		}
	}
}