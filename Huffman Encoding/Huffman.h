#include <string>
using namespace std;

struct Node {
	char key;
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
	void initializeArray(Node* nodeArray[256]);
	void processFile(ifstream& inputFile, Node* nodeArray[256]);
	void buildTree(Node* nodeArray[256]);
	int min(Node* nodeArray[256], int exclusionIndex = INT_MAX);
	bool treeIsBuilt(Node* nodeArray[256]);
};