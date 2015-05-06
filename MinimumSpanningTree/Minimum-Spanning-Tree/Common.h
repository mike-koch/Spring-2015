// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Common.h - The common header file contains code used by various source files in this solution, and therefore have no "specific" place

#ifndef COMMON_H
#define COMMON_H
#include "List.h"
#include "Edge.h"
class Common
{
public:
	static void sortEdgesByWeight(List<Edge>* edges);
	static void sortEdgesByString(List<Edge>* edges);
	static void makeSet(Vertex* vertex);
	static Vertex* findSet(Vertex* vertex);
	static Vertex* getVertexById(List<Vertex>* verticies, unsigned int id);
	static void unionVerticies(Vertex* vertexOne, Vertex* vertexTwo);
private:
	static void moveEdge(Edge* source, Edge* destination);
	static void linkVerticies(Vertex* vertexOne, Vertex* vertexTwo);
};
#endif
