#ifndef KRUSKAL_H
#define KURSKAH_H
#include "List.h"
#include "Graph.h"
class Kruskal
{
public:
	List<Edge>* execute(Graph* graph);
	Kruskal();
	~Kruskal();
};
#endif

