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
	Common::sortEdgesByWeight(graph->edges);
	for (int i = 0; i < graph->edges->size(); i++)
	{
		Edge* currentEdge = graph->edges->get<Edge>(i);
		Vertex* vertexU = Common::getVertexById(graph->verticies, currentEdge->startingVertexId);
		Vertex* vertexV = Common::getVertexById(graph->verticies, currentEdge->endingVertexId);
		if (Common::findSet(vertexU) != Common::findSet(vertexV))
		{
			A->add(currentEdge);
			Common::unionVerticies(vertexU, vertexV);
		}
	}
	return A;
}


Kruskal::~Kruskal()
{
}
