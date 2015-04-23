// NodeStruct.h
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// Header file that contains all properties that any tree may use. Not all trees will use every property; however all properties will be 
//    used at some point.
#ifndef BTREENODE_H
#define BTREENODE_H
#include <string>
using namespace std;

const int T = 2;
struct BTreeNode
{
public:
	BTreeNode() // Using a default value so search results don't need to create a random T value just to compile
	{
		initializeArrays();
	}
	unsigned int maxNumberOfKeys = 2 * T - 1; // The max number of keys that this node can contain.
	unsigned int id; // Unique identifier that dictates the position in the file
	char keys[2 * T][50];
	unsigned int numberOfKeys = 0; // Number of keys in this node. Between t-1 and 2t-1
	unsigned int numberOfChildren = 0; // Num of children in this node. Between 0 and 2t
	unsigned int childIds[2 * T + 1];
	unsigned int numberOfOccurrences[2 * T];
	bool isLeaf = false;
private:
	void initializeArrays();
};
#endif