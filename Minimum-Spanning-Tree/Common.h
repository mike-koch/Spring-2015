#ifndef COMMON_H
#define COMMON_H
#include "List.h"
#include "Edge.h"
class Common
{
public:
	static void sortEdges(List<Edge>* edges);
	static void makeSet(Vertex* vertex);
	static Vertex* findSet(Vertex* vertex);
	static void unionVerticies(Vertex* vertexOne, Vertex* vertexTwo);
private:
	static void moveEdge(Edge* source, Edge* destination);
	static void linkVerticies(Vertex* vertexOne, Vertex* vertexTwo);
};
#endif
