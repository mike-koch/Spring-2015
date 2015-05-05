#include "Common.h"

void Common::sortEdgesByWeight(List<Edge>* edges)
{
	LinkedListNode<Edge>* firstNode = NULL;
	for (int i = 1; i < edges->size(); i++)
	{
		// Perform an insertion sort on the edges.
		Edge* currentEdge = edges->get(i);
		Edge* tempEdge = new Edge(currentEdge->weight, 
			currentEdge->startingVertexId, 
			currentEdge->endingVertexId, 
			currentEdge->startingVertexName, 
			currentEdge->endingVertexName);

		int j;
		for (j = i - 1; j > -1 && tempEdge->weight < edges->get(j)->weight; j--)
		{
			moveEdge(edges->get(j), edges->get(j + 1));
		}

		moveEdge(tempEdge, edges->get(j + 1));
	}
}

void Common::sortEdgesByString(List<Edge>* edges)
{
	for (int i = 1; i < edges->size(); i++)
	{
		// Perform an insertion sort on the edges.
		Edge* currentEdge = edges->get(i);
		Edge* tempEdge = new Edge(currentEdge->weight,
			currentEdge->startingVertexId,
			currentEdge->endingVertexId,
			currentEdge->startingVertexName,
			currentEdge->endingVertexName);

		int j;
		for (j = i - 1; j > -1 && tempEdge->getFormattedName() < edges->get(j)->getFormattedName(); j--)
		{
			moveEdge(edges->get(j), edges->get(j + 1));
		}

		moveEdge(tempEdge, edges->get(j + 1));
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

Vertex* Common::getVertexById(List<Vertex>* verticies, unsigned int id)
{
	for (int i = 0; i < verticies->size(); i++)
	{
		Vertex* currentVertex = verticies->get(i);
		if (currentVertex->id == id)
		{
			return currentVertex;
		}
	}
	return NULL;
}

void Common::unionVerticies(Vertex* vertexOne, Vertex* vertexTwo)
{
	linkVerticies(findSet(vertexOne), findSet(vertexTwo));
}

void Common::moveEdge(Edge* source, Edge* destination)
{
	// Perform a hard copy of the data from the source edge to the destination edge
	destination->endingVertexId = source->endingVertexId;
	destination->endingVertexName = source->endingVertexName;
	destination->startingVertexId = source->startingVertexId;
	destination->startingVertexName = source->startingVertexName;
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