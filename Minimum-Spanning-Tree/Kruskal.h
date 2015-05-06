// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Kruskal.h - Kruskal's Algorithm header file. Contains list of functions required to execute Kruskal's algorithm for a given graph

#ifndef KRUSKAL_H
#define KURSKAH_H
#include "List.h"
#include "Graph.h"
class Kruskal
{
public:
	static List<Edge>* execute(Graph* graph);
};
#endif

