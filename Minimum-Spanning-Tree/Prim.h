// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Prim.h - Prim's Algorithm header file. Contains list of functions required to execute Prim's algorithm for a given graph and an arbitrary
//    starting vertex

#ifndef PRIM_H
#define PRIM_H
#include "List.h"
#include "Edge.h"
#include "Graph.h"
class Prim
{
public:
	static void execute(Graph* graph, Vertex* root);
};
#endif