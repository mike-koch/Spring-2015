#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;
#include "Huffman.h"

Node* nodeArray[256];
Node* root;
//-- PUBLIC methods

// Builds a Huffman tree based on each byte processed. Each byte will be one of the ASCII characters with an int value of 0-255.
void Huffman::initializeFromFile(string fileName) {
	// Obtain the file from the filepath
	ifstream inputFile;
	inputFile.open(fileName, ios::binary);

	if (inputFile.fail()) {
		char waitChar;
		cout << "ERROR: The file could not be opened. Check that the path exists and try again. Press ENTER to exit.";
		cin.get(waitChar);
		exit(1);
	}

	//-- Initialize an array to contain all 255 ASCII characters nodes.
	initializeNodeArray();

	//-- Process the input file with the array
	processFile(inputFile);

	//-- Build the huffman tree
	buildTree();
}

/*
   Summary: Takes the contents of the "inFile" and stores the encoded result in the "outFile".  Function also outputs input/output byte counts,
            size of the encoded file as a percentage of the original file's size. Elapsed time is also displayed.
   Requires: initializeFromFile must have been ran before encoding; otherwise there is no tree to use as the key!
*/
void Huffman::encodeFile(string inFile, string outFile) {
	//-- First, build an array of ASCII character to encoding string that we can use to encode our file.
	string encodingArray[256];
	buildEncodingArray(encodingArray, root, "");
	string throwaway = "debugging...";
}

/*
   Summary: takes the contents of the "inFile" and stores the decoded result in the "outFiel". Function also outputs in / out byte counts, as well as elapsed time.
   Requires: initializeFromFile must have been ran before encoding; otherwise there is no tree to use as the key!
*/
void Huffman::decodeFile(string inFile, string outFile) {
}

//-- PRIVATE functions
void Huffman::initializeNodeArray() {
	for (int i = 0; i < 256; i++) {
		Node* node = new Node();
		node->key = (unsigned char)i;
		node->weight = 0;
		nodeArray[i] = node;
	}
}

void Huffman::processFile(ifstream& inputFile) {
	//-- Process each symbol, by incrementing the node's count.
	while (!inputFile.eof()) {
		char symbol;
		inputFile.get(symbol);
		nodeArray[(unsigned char)symbol]->weight++;
	}
}

//-- Builds the tree by taking the smallest nodes and giving them a parent. Then, the process keeps looping until a full tree has been formed.
void Huffman::buildTree() {
	while (!treeIsBuilt()) {
		//-- Get the smallest two nodes in the array
		int firstMinIndex = min();
		int secondMinIndex = min(firstMinIndex);
		Node* firstMin = nodeArray[firstMinIndex];
		Node* secondMin = nodeArray[secondMinIndex];


		//-- Create a new parent node for the two min nodes
		Node* parentNode = new Node();
		parentNode->key = NULL;
		parentNode->leftChild = firstMin;
		parentNode->rightChild = secondMin;
		parentNode->weight = firstMin->weight + secondMin->weight;

		//-- Set firstMinIndex to the new parent node, and set secondMinIndex to NULL.
		nodeArray[firstMinIndex] = parentNode;
		nodeArray[secondMinIndex] = NULL;

		root = parentNode;
	}

	//-- The tree has been built. The root was set to firstMin at the very end of the loop, so we also have our root node.
	return;
}

//-- Searches for the node with the smallest weight, excluding the node specified as the exclusion. 
//   A NULL exclusion means to not exclude a node.
//   Returns: the array index of the min.
int Huffman::min(int exclusionIndex) {
	//-- Set the minWeight to the max, so the first MUST be smaller than INT_MAX.
	int minWeight = INT_MAX;
	int minIndex = -1;
	for (int i = 0; i < 256; i++) {
		//-- If the current array's position is not NULL, not the node to exclude, and its weight is smaller than the current minWeight, make it the new min.
		if (nodeArray[i] != NULL && i != exclusionIndex && nodeArray[i]->weight < minWeight) {
			minWeight = nodeArray[i]->weight;
			minIndex = i;
		}
	}
	return minIndex;
}

//-- Returns true if the Huffman tree has been built (all indices are NULL except for one)
bool Huffman::treeIsBuilt() {
	bool encounteredNotNullIndex = false;
	for (int i = 0; i < 256; i++) {
		if (nodeArray[i] != NULL) {
			if (!encounteredNotNullIndex) {
				encounteredNotNullIndex = true;
			} else {
				//-- More than one non-null index was found. Return false since the tree hasn't been built yet.
				return false;
			}
		}
	}
	//-- If we got here, only one index was not null. Return true;
	return true;
}

int stackCount = 0;
void Huffman::buildEncodingArray(string encodingArray[256], Node* startingNode, string encodedValue) {
	stackCount++;
	//-- Perform an in-order traversal of the tree, keeping track of each branch taken (0 = left, 1 = right). Once we find a leaf node,
	//   mark the encoding string for it's ASCII character.

	// check if we're at a leaf node (no left/right children). If so, set the array's encoded value
	/*if (startingNode->leftChild == NULL && startingNode->rightChild == NULL) {
		encodingArray[(unsigned char)startingNode->key] = encodedValue;
	}
	
	// start by going left, only if not null.
	if (startingNode->leftChild != NULL) {
		//-- Now go left, adding a 0 to the encodedValue
		buildEncodingArray(encodingArray, startingNode->leftChild, encodedValue += "0");
	}
	// we know that this isn't a leaf node, since that was checked earlier. So there's nothing to do with this node. Just go to the right now.
	if (startingNode->rightChild != NULL) {
		//-- Now go right, adding a 1 to the encodedValue
		buildEncodingArray(encodingArray, startingNode->rightChild, encodedValue += "1");
	}*/
	string throwawayArray[256];

	if (startingNode == NULL) {
		stackCount--;
		return;
	}

	buildEncodingArray(throwawayArray, startingNode->leftChild, "");
	cout << to_string(startingNode->key) + to_string(startingNode->weight) << endl;
	buildEncodingArray(throwawayArray, startingNode->rightChild, "");
}

