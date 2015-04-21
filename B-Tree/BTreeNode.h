// NodeStruct.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// Header file that contains all properties that any tree may use. Not all trees will use every property; however all properties will be 
//    used at some point.
#ifndef BTREENODE_H
#define BTREENODE_H
#include <string>
using namespace std;

struct BTreeNode
{
public:
	BTreeNode(unsigned const int T = 2) // Using a default value so search results don't need to create a random T value just to compile
	{
		// Initialize keys and childIds array sizes. There will always be one more child id than the number of keys
		maxNumberOfKeys = 2 * T - 1;
		numberOfKeys = 0;
		keys = new char[maxNumberOfKeys][50];
		childIds = new unsigned int[2*T];
		numberOfOccurrences = new unsigned int[maxNumberOfKeys];
		initializeArrays();
	}
	int id; // Unique identifier that dictates the position in the file
	char (*keys)[50]; // All of the keys in this node
	unsigned int numberOfKeys; // Number of keys in this node. Between t-1 and 2t-1
	unsigned int maxNumberOfKeys; // The max number of keys that this node can contain.
	unsigned int *childIds; // array of child IDs
	unsigned int *numberOfOccurrences;
	bool isLeaf;
private:
	void initializeArrays();
};
#endif