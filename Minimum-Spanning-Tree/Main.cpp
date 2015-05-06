// Mike Koch - Minimum Spanning Tree
// EECS 2510 | 04/28/2015
// Main.cpp - Responsible for parsing input and executing required tree algorithms

#include <iostream>
#include <climits>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include "List.h"
#include "Kruskal.h"
#include "Prim.h"
#include "Common.h"
using namespace std;

// Function prototypes
List<Vertex>* parseVerticies(unsigned int numberOfVerticies);
List<Edge>* parseEdges(List<Vertex>* verticies, unsigned int numberOfVerticies);
bool shouldAddEdge(List<Edge>* edgeList, unsigned int row, unsigned int column);
void executeKruskal(Graph* graph);
void executePrim(Graph* graph);
void pause(string text);
void outputEdgeResults(List<Edge>* edgeList);
void outputVertexResults(Graph* graph);
double getWeightOfTree(List<Edge>* edgeList, Graph* graph);

int main()
{
	unsigned int numberOfVerticies;
	cin >> numberOfVerticies;

	List<Vertex>* vertexList = parseVerticies(numberOfVerticies);
	List<Edge>* edgeList = parseEdges(vertexList, numberOfVerticies); // Returns a list of the parsed edges	

	// Create our graph
	Graph* graph = new Graph(edgeList, vertexList);

	// Process Kruskal's algorithm with the graph
	executeKruskal(graph);

	// Process Prim's algorithm with the graph
	executePrim(graph);

	// Hold here so the user has a chance to read the data, in case the window disappears right away.
	pause("Execution complete. Press ENTER to exit.");
}

// Create a vertex object for each vertex with a unique ID value
List<Vertex>* parseVerticies(unsigned int numberOfVerticies)
{
	List<Vertex>* vertexList = new List<Vertex>();
	for (unsigned int i = 0; i < numberOfVerticies; i++)
	{
		// Create a new vertex of id = i and name = the string passed in through the console. Add it to the list of verticies
		string name;
		cin >> name;
		vertexList->add(new Vertex(i, name));
	}
	return vertexList;
}

// The next N*N characters indicate the edges that are connected to each vertex along with the weight. The first N pertain to the first
//   edge, the second N pertain to the second edge, and so forth. The outer loop keeps track of row # and the inner loop keeps track of column #
List<Edge>* parseEdges(List<Vertex>* verticies, unsigned int numberOfVerticies)
{
	List<Edge>* edgeList = new List<Edge>();
	for (unsigned int i = 0; i < numberOfVerticies; i++)
	{
		// the next N values indicate the edges that exist between two nodes.
		// check if the edge has already been created, and if not, create it.
		for (unsigned int j = 0; j < numberOfVerticies; j++)
		{
			// j indicates the current COLUMN we are looking at
			// i indicates the current ROW    we are looking at
			// ex. if i = 1 and j = 3, we are looking at the edge that connects B and D (if the verticies are named alphabetically starting w/A)

			double nextWeight;
			cin >> nextWeight;
			if (nextWeight != 0) // If the next weight is not 0, then we possibly have a newly discovered edge
			{
				// If we never found an edge with the current verticies, we should create a new edge and add it to the list.
				if (shouldAddEdge(edgeList, i, j))
				{
					Edge* newEdge = new Edge(nextWeight, i, j, Common::getVertexById(verticies, i)->name, Common::getVertexById(verticies, j)->name);
					edgeList->add(newEdge);

					// Update each vertex's weight if needed
					if (Common::getVertexById(verticies, i)->weight > newEdge->weight)
					{
						Common::getVertexById(verticies, i)->weight = newEdge->weight;
					}
				}
			}
		}
	}
	return edgeList;
}

// Checks if the list of edges already contains the edge discovered by checking the current edges.
bool shouldAddEdge(List<Edge>* edgeList, unsigned int row, unsigned int column)
{
	unsigned int currentIndex = 0;
	Edge* currentEdge = edgeList->get(currentIndex);
	while (currentEdge != NULL)
	{
		// If the edge's startingVertex and endingVertex are i and j (in either direction), set shouldAddEdge to FALSE and break out of the loop
		if ((currentEdge->startingVertexId == row && currentEdge->endingVertexId == column) ||
			(currentEdge->startingVertexId == column && currentEdge->endingVertexId == row))
		{
			//-- we already have the edge recorded, so return false.
			return false;
		}
		// Otherwise, grab the next edge in the list and repeat the process.
		currentEdge = edgeList->get(++currentIndex);
	}

	// If we get to here, the edge doesn't exist yet. So return true.
	return true;
}

// Executes Kruskal's algorithm against the given graph
void executeKruskal(Graph* graph)
{
	cout << "Calculating MST using Kruskal's Algorithm\n----------------------------------------\n";
	List<Edge>* edges = Kruskal::execute(graph);
	outputEdgeResults(edges);
	// TODO
}

// Executes Prim's algorithm against the given graph
void executePrim(Graph* graph)
{
	cout << "Calculating MST using Prim's Algorithm\n----------------------------------------\n";

	// We will use the first vertex to start Prim's algorithm.
	Prim::execute(graph, graph->verticies->get(0));
	outputVertexResults(graph);
	// TODO
}

// Waits for the user to press ENTER. Nothing fancy.
void pause(string text)
{
	cout << endl << text << endl;
	char throwaway = 0;
	cin.get(throwaway);

	// It *appears* that the final "ENTER" from entering in the edges triggers the first cin.get(), so adding a second one here
	cin.get(throwaway);
}

/* Outputs the following:
	- Total weight of all edges involved in MST
	- The edges that make up the tree in alphabetical order
*/
void outputEdgeResults(List<Edge>* edgeList)
{
	// Sort our edges by their formatted string output
	Common::sortEdgesByString(edgeList);

	// Output the total weight of the MST, and then each edge and its weight
	cout << getWeightOfTree(edgeList, NULL) << endl;
	for (int i = 0; i < edgeList->size(); i++)
	{
		Edge* currentEdge = edgeList->get(i);
		cout << currentEdge->startingVertexName + "-" + currentEdge->endingVertexName + ": " << currentEdge->weight << endl;
	}

}

void outputVertexResults(Graph* graph)
{
	// Output the total weight of the MST, and then each vertex and its weight
	cout << getWeightOfTree(NULL, graph) << endl;
	List<Edge>* tempEdges = new List<Edge>();
	for (int i = 0; i < graph->verticies->size(); i++)
	{
		if (graph->verticies->get(i)->weight != 0)
		{
			// Create a temporary edge containing the information needed for sorting
			Vertex* currentVertex = graph->verticies->get(i);
			Edge* tempEdge = new Edge(currentVertex->weight,
				currentVertex->parent->id,
				currentVertex->id,
				currentVertex->parent->name,
				currentVertex->name);
			tempEdges->add(tempEdge);
		}
	}
	Common::sortEdgesByString(tempEdges);
	for (int i = 0; i < tempEdges->size(); i++)
	{
		Edge* currentEdge = tempEdges->get(i);
		cout << currentEdge->startingVertexName + "-" + currentEdge->endingVertexName + ": " << currentEdge->weight << endl;
	}
}

// Calculates the total weights of all of the edges in the list and returns the value
double getWeightOfTree(List<Edge>* edges, Graph* graph)
{
	double weight = 0;
	if (edges != NULL)
	{
		for (int i = 0; i < edges->size(); i++)
		{
			weight += edges->get(i)->weight;
		}
	}
	else
	{
		for (int i = 0; i < graph->verticies->size(); i++)
		{
			if (graph->verticies->get(i)->weight != INT_MAX)
			{
				weight += graph->verticies->get(i)->weight;
			}
		}
	}
	return weight;
}