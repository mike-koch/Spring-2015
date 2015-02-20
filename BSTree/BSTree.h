// Binary Search Tree Implementation
// Mike Koch - EECS 2510
// BSTree.h - Interface for the BSTree class and Node struct. Contains all private and public methods that BSTree needs.

#include <string>
using namespace std;

struct Node {
	string key;
	int numberOfOccurrences;
	Node* leftChild;
	Node* rightChild;
	Node* parent;
};
class BSTree {
public:
	void searchForValue(string key);
	void insertValue(string key);
	void deleteValue(string key);
	void findMin();
	void findMax();
	void findNext(string key);
	void findPrevious(string key);
	void listTree();

private:
	Node* root;
	Node* search(Node* node, string key);
	void addNodeToTree(Node* node);
	void deleteNode(Node* node);
	void transplant(Node* nodeOne, Node* nodeTwo);
	Node* min(Node* node);
	Node* max(Node* node);
	Node* next(Node* node, string key);
	Node* previous(Node* node, string key);
	void list(Node* node);
	void outputNodeInformation(string key, string value = "");
};