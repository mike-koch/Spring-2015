// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Graph.cpp - Graph source file, which contains properties needed for the graph as well as helper functions

#include "Graph.h"
#include "Common.h"

// Finds verticies that are directly adjacent to the vertex passed in by checking every edge in the graph
List<Vertex>* Graph::getAdjacentVerticies(Vertex* startingVertex)
{
	List<Vertex>* adjacentVerticies = new List<Vertex>();
	for (int i = 0; i < edges->size(); i++)
	{
		Edge* currentEdge = edges->get(i);

		// If the current edge's startingVertexId or endingVertexId is the reference vertex's ID, grab the other vertex in the edge and add it
		//    to the list.
		if (currentEdge->startingVertexId == startingVertex->id)
		{
			adjacentVerticies->add(Common::getVertexById(verticies, currentEdge->endingVertexId));
		}
		else if (currentEdge->endingVertexId == startingVertex->id)
		{
			adjacentVerticies->add(Common::getVertexById(verticies, currentEdge->startingVertexId));
		}
	}
	return adjacentVerticies;
}

// Returns the edge that connects the two given verticies, or NULL if no such edge exists
Edge* Graph::findEdgeConnectingVerticies(Vertex* vertexOne, Vertex* vertexTwo)
{
	for (int i = 0; i < edges->size(); i++)
	{
		Edge* currentEdge = edges->get(i);

		// Checks to see if the startingVertexId and the endingVertexId are the two verticies passed in
		if ((currentEdge->startingVertexId == vertexOne->id && currentEdge->endingVertexId == vertexTwo->id)
			|| (currentEdge->startingVertexId == vertexTwo->id && currentEdge->endingVertexId == vertexOne->id))
		{
			return currentEdge;
		}
	}
	return NULL;
}