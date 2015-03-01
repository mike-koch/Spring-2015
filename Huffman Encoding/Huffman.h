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
	int min(int exclusionIndex = INT_MAX);
	bool treeIsBuilt();
	void buildEncodingArray(string encodingArray[256], Node* startingNode, string encodedValue);
	void saveFile(string outputBits, string outFile);
};