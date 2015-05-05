#include "Kruskal.h"
#include "Common.h"

Kruskal::Kruskal()
{
}

List<Edge>* Kruskal::execute(Graph* graph)
{
	List<Edge>* A = new List<Edge>();
	for (int i = 0; i < graph->verticies->size(); i++)
	{
		Common::makeSet(graph->verticies->get<Vertex>(i));
	}
	Common::sortEdges(graph->edges);
	for (int i = 0; i < graph->edges->size(); i++)
	{
		Edge* currentEdge = graph->edges->get<Edge>(i);
		Vertex* vertexU = getVertexById(graph->verticies, currentEdge->startingVertexId);
		Vertex* vertexV = getVertexById(graph->verticies, currentEdge->endingVertexId);
		if (Common::findSet(vertexU) != Common::findSet(vertexV))
		{
			A->add(currentEdge);
			Common::unionVerticies(vertexU, vertexV);
		}
	}
	return A;
}

Vertex* Kruskal::getVertexById(List<Vertex>* verticies, unsigned int id)
{
	for (int i = 0; i < verticies->size(); i++)
	{
		Vertex* currentVertex = verticies->get<Vertex>(i);
		if (currentVertex->id == id)
		{
			return currentVertex;
		}
	}
	return NULL;
}


Kruskal::~Kruskal()
{
}
