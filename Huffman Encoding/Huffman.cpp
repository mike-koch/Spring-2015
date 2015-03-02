#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;
#include "Huffman.h"

Node* nodeArray[256];
Node* root;
string encodingArray[256];
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

	//-- The input file can now be closed.
	inputFile.close();

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
	buildEncodingArray(encodingArray, root, "");
	
	//-- Using the encoding strings, encode the file.

	// build a string containing all of the bits that will be processed
	string outputBits = getOutputBits(inFile, encodingArray);
	// save the file
	saveFile(outputBits, outFile);
}

/*
   Summary: takes the contents of the "inFile" and stores the decoded result in the "outFile". Function also outputs in / out byte counts, as well as elapsed time.
   Requires: initializeFromFile must have been ran before encoding; otherwise there is no tree to use as the key!
*/
void Huffman::decodeFile(string inFile, string outFile) {
	ifstream inputStream;
	inputStream.open(inFile, ios::binary);
	if (inputStream.fail()) {
		cout << "ERROR: Could not open the file for decoding. Ensure the file path is correct and try again. Press ENTER to exit.";
		char waitChar;
		cin.get(waitChar);
		exit(1);
	}
	// take each byte and build the entire bit string.
	string bitString;
	while (!inputStream.eof()) {
		char symbol;
		inputStream.get(symbol);
		//convert to binary
		string* binaryValue = getBinaryValueForChar((unsigned char)symbol);
		//append to bit string
		bitString += *binaryValue;
	}

	// Now that we have the bit string, go through and find each letter that cooresponds to the bit values. Output to the output stream
	ofstream outputStream;
	outputStream.open(outFile, ios::binary);
	decodeBitString(outputStream, bitString);
	outputStream.close();
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

void Huffman::buildEncodingArray(string encodingArray[256], Node* startingNode, string encodedValue) {
	//-- Perform an in-order traversal of the tree, keeping track of each branch taken (0 = left, 1 = right). Once we find a leaf node,
	//   mark the encoding string for it's ASCII character.

	// check if we're at a leaf node (no left/right children). If so, set the array's encoded value
	if (startingNode->leftChild == NULL && startingNode->rightChild == NULL) {
		encodingArray[(unsigned char)startingNode->key] = encodedValue;
		
	}
	
	// start by going left, only if not null.
	if (startingNode->leftChild != NULL) {
		//-- Now go left, adding a 0 to the encodedValue
		buildEncodingArray(encodingArray, startingNode->leftChild, encodedValue += "0");
	}

	// Remove the last character added to the encodedValue string since we're no longer at the left child's subtree any more.
	encodedValue = encodedValue.substr(0, encodedValue.length() - 1);

	// Move to the right node
	if (startingNode->rightChild != NULL) {
		//-- Now go right, adding a 1 to the encodedValue
		buildEncodingArray(encodingArray, startingNode->rightChild, encodedValue += "1");
	}
}

string Huffman::getOutputBits(string inFile, string encodingArray[256]) {
	string outputBits;
	//loop through each character, getting its encoded value and appending it to the outputBits string
	ifstream inputStream;
	inputStream.open(inFile, ios::binary);
	if (inputStream.fail()) {
		cout << "ERROR: The file could not be opened. Check that the path exists and try again. Press ENTER to exit." << endl;
		char waitChar;
		cin.get(waitChar);
		exit(1);
	}

	while (!inputStream.eof()) {
		// get the encoded value and append it to outputBits
		char symbol;
		inputStream.get(symbol);
		outputBits += encodingArray[(unsigned char)symbol];
	}


	return outputBits;
}

void Huffman::saveFile(string outputBits, string outFile) {
	// Loop through the ouputBits, grabbing the next 8 at a time and appending it to the output stream.
	int currentIndex = 0;
	ofstream outputStream;
	outputStream.open(outFile, ios::binary);
	if (outputStream.fail()) {
		cout << "ERROR: Could not open the output file for writing. Ensure that you have permission" <<
			" to save the file in this location and try again. Press ENTER to exit.";
		char waitChar;
		cin.get(waitChar);
		exit(1);
	}
	for (unsigned int i = 0; i < outputBits.length(); i += 8) {
		outputStream.put(getNextByte(outputBits, i));
	}
	outputStream.close();
	cout << "FINISHED ENCODING";
}

unsigned char Huffman::getNextByte(string& outputBits, int startingIndex) {
	int nextBits[8];
	int arrayIndex = 0;
	bool needToPad = false;
	unsigned int numberOfBitsToPad = 0;

	//-- Get (what will become) the next 8 bits in an int array
	//  1. Are there less than 8 bits left in the string? If yes, only loop to the max
	unsigned int loopEnd = startingIndex + 8;
	if (loopEnd > outputBits.length()) {
		needToPad = true;
		numberOfBitsToPad = loopEnd - outputBits.length();
		loopEnd = outputBits.length();
	}

	for (unsigned int i = startingIndex; i < loopEnd; i++) {
		nextBits[arrayIndex] = outputBits[i] == '0' 
			? 0 
			: 1;
		arrayIndex++;
	}

	//-- If all 8 indexes aren't filled, we will need to pad them. Loop through the encoding array and find an encoding string that is
	//   at least 1 bit longer than the number of bits we need to pad.
	if (needToPad) {
		string bitsToAdd;
		int startingPadIndex = 8 - numberOfBitsToPad;
		//-- find an encoding value that is larger than X, and then get the first X number of bits in its sequence, where X is numberOfBitsToPad
		for (int i = 0; i < 256; i++) {
			if (encodingArray[i].length() > numberOfBitsToPad) {
				bitsToAdd = encodingArray[i].substr(0, numberOfBitsToPad);
				break;
			}
		}
		int bitsToAddIndex = 0;
		for (int i = startingPadIndex; i < 8; i++) {
			nextBits[i] = bitsToAdd[bitsToAddIndex] == '0'
				? 0
				: 1;
			bitsToAddIndex++;
		}
	}
	

	//-- Set the bits in the char to return
	char byte = 0;
	for (int i = 0; i < 8; i++) {
		if (nextBits[i]) {
			byte |= (1 << (7 - i));
		}
	}

	return (unsigned char)byte;
}

string* Huffman::getBinaryValueForChar(unsigned char theChar) {
	string* bitString = new string();
	unsigned char dividedChar = theChar;
	int values[8];
	for (int i = 0; i < 8; i++) {
		values[i] = 0;
	}
	int index = 0;
	while (true) {
		int quotient = (dividedChar / 2);
		values[index] = (dividedChar % 2);
		if (quotient == 0) {
			// we're done dividing. loop through the array in reverse to get the string representation of the binary bits.
			for (int i = 7; i > -1; i--) {
				bitString->append(to_string(values[i]));
			}
			return bitString;
		}
		index++;
		dividedChar = quotient;
	}
}

void Huffman::decodeBitString(ofstream& outputStream, string& bitString) {
	Node* currentNode = root;
	for (unsigned int i = 0; i < bitString.length(); i++) {
		//-- Go to this node's left or right child, depending if the number at the current string position is a 0 or 1.
		if (bitString[i] == '0') {
			currentNode = currentNode->leftChild;
		} else {
			currentNode = currentNode->rightChild;
		}
		if (currentNode->leftChild == NULL && currentNode->rightChild == NULL) {
			//-- We hit a leaf node, and subsequently, a character. Output this character to the output stream and go back to the root
			outputStream.put(currentNode->key);
			currentNode = root;
		}
	}
}