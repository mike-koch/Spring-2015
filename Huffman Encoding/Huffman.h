// Huffman Encoding
// Mike Koch - EECS 2510
// Huffman.h - Interface for the Huffman tree; responsible for everything related to Huffman encoding, including intiailization, encoding,
//             and decoding.

#include <string>
using namespace std;

struct Node {
	unsigned char key;
	int weight;
	Node* leftChild;
	Node* rightChild;
};
class Huffman {
public:
	void initializeFromFile(string fileName);
	void encodeFile(string inFile, string outFile);
	void decodeFile(string inFile, string outFile);

private:
	void initializeNodeArray();
	void processFile(ifstream& inputFile);
	void buildTree();
	int getMin(int exclusionIndex = INT_MAX);
	bool treeIsBuilt();
	void buildEncodingArray(string encodingArray[256], Node* startingNode, string encodedValue);
	string getOutputBits(string inFile, string encodingArray[256]);
	int saveFile(string outputBits, string outFile);
	unsigned char getNextByte(string& outputBits, int startingIndex);
	string* getBinaryValueForChar(unsigned char theChar);
	int decodeBitString(ofstream& outputStream, string& bitString);
};