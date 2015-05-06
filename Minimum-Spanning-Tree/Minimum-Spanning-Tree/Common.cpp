// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Common.cpp - The common source file contains code used by various source files in this solution, and therefore have no "specific" place

#include "Common.h"

// Takes a list of edges and sorts them by their weights in nondecreasing order, using insertion sort
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


// Same as sortEdgesByWeight, but sorts based on the edge's getFormattedString() instead of weight
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

// Initializes the vertex by settings its parent to itself and its rank to zero
void Common::makeSet(Vertex* vertex)
{
	vertex->parent = vertex;
	vertex->rank = 0;
}

// Finds the set that the vertex belongs to by using a recursive call to the vertex's parent if its vertex is not itself.
Vertex* Common::findSet(Vertex* vertex)
{
	if (vertex != vertex->parent)
	{
		vertex->parent = findSet(vertex->parent);
	}
	return vertex->parent;
}

// Returns a vertex with the requested ID in the list of verticies provided
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

// Links two verticies together based on the set each one is in
void Common::unionVerticies(Vertex* vertexOne, Vertex* vertexTwo)
{
	linkVerticies(findSet(vertexOne), findSet(vertexTwo));
}

// Performs a hard copy of the data from the source edge to the destination edge
void Common::moveEdge(Edge* source, Edge* destination)
{
	destination->endingVertexId = source->endingVertexId;
	destination->endingVertexName = source->endingVertexName;
	destination->startingVertexId = source->startingVertexId;
	destination->startingVertexName = source->startingVertexName;
	destination->weight = source->weight;
}

// Links two verticies together based on their rank. 
void Common::linkVerticies(Vertex* vertexOne, Vertex* vertexTwo)
{
	// If vertexOne's rank is larger than vertexTwo, vertexOne will become the parent of vertexTwo
	if (vertexOne->rank > vertexTwo->rank)
	{
		vertexTwo->parent = vertexOne;
	}
	else
	{
		// Otherwise, it goes the other way around. However, if the ranks are equal, vertexTwo becomes the parent
		vertexOne->parent = vertexTwo;
		if (vertexOne->rank == vertexTwo->rank)
		{
			vertexTwo->rank++;
		}
	}
}