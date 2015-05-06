// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Kruskal.cpp - Kruskal's Algorithm source file. Executes Kruskal's algorithm for a given graph.

#include "Kruskal.h"
#include "Common.h"

List<Edge>* Kruskal::execute(Graph* graph)
{
	// We will hold a list of edges that are part of the minimum spanning tree
	List<Edge>* edgesInMST = new List<Edge>();

	// Initialize each vertex for Kruskal's algorithm, and then sort all edges in order of weight in nondecreasing order
	for (int i = 0; i < graph->verticies->size(); i++)
	{
		Common::makeSet(graph->verticies->get(i));
	}
	Common::sortEdgesByWeight(graph->edges);

	// Iterate over each edge. Obtain the verticies that are connected by the current edge, and if they are in different sets, combine them
	//    into the same set and add the edge to the list of edges in the minimum spanning tree
	for (int i = 0; i < graph->edges->size(); i++)
	{
		Edge* currentEdge = graph->edges->get(i);
		Vertex* vertexU = Common::getVertexById(graph->verticies, currentEdge->startingVertexId);
		Vertex* vertexV = Common::getVertexById(graph->verticies, currentEdge->endingVertexId);
		if (Common::findSet(vertexU) != Common::findSet(vertexV))
		{
			// The verticies are in different trees, but should be combined. Add the edge to the list of edges in the minimum spanning tree and
			//    combine the verticies into the same tree
			edgesInMST->add(currentEdge);
			Common::unionVerticies(vertexU, vertexV);
		}
	}
	return edgesInMST;
}
