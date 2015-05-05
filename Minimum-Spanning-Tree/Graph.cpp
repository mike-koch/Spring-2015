#include "Graph.h"
#include "Common.h"

List<Vertex>* Graph::getAdjacentVerticies(Vertex* startingVertex)
{
	List<Vertex>* adjacentVerticies = new List<Vertex>();
	for (int i = 0; i < edges->size(); i++)
	{
		Edge* currentEdge = edges->get(i);
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

Edge* Graph::findEdgeConnectingVerticies(Vertex* vertexOne, Vertex* vertexTwo)
{
	for (int i = 0; i < edges->size(); i++)
	{
		Edge* currentEdge = edges->get(i);
		if ((currentEdge->startingVertexId == vertexOne->id && currentEdge->endingVertexId == vertexTwo->id)
			|| (currentEdge->startingVertexId == vertexTwo->id && currentEdge->endingVertexId == vertexOne->id))
		{
			return currentEdge;
		}
	}
	return NULL;
}