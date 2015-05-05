#ifndef KRUSKAL_H
#define KURSKAH_H
#include "List.h"
#include "Graph.h"
class Kruskal
{
public:
	static List<Edge>* execute(Graph* graph);
	Kruskal();
	~Kruskal();
private:
	static Vertex* getVertexById(List<Vertex>* verticies, unsigned int id);
};
#endif

