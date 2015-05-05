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
	~Vertex();
	unsigned int id;
	string name;
	double weight = 0;
	Vertex* predecessor;
	Vertex* parent;
	unsigned int rank;
};
#endif

