#ifndef PRIM_H
#define PRIM_H
#include "List.h"
#include "Edge.h"
#include "Graph.h"
class Prim
{
public:
	static void execute(Graph* graph, Vertex* root);
	Prim();
	~Prim();
};
#endif