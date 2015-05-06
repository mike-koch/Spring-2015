// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 05/03/2015
// Vertex.h - Vertex header file, which contains properties about the vertex

#ifndef VERTEX_H
#define VERTEX_H
#include <string>
using namespace std;

class Vertex
{
public:
	Vertex(int vertexId, string& vertexName)
	{
		id = vertexId;
		name = vertexName;
	};
	unsigned int id;
	string name;
	double weight = 0;
	Vertex* parent;
	unsigned int rank;
};
#endif

