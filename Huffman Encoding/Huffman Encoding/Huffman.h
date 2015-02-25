#include <string>
using namespace std;

struct Node {
	string key;
	int weight;
	Node* leftChild;
	Node* rightChild;
};
class Huffman {
public:
	void initializeFromFile(string fileName);
	void encodeFile(string inFile, string outFile);
	void decodeFile(string inFile, string outFile);
};