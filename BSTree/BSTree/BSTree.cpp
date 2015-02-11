#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node
{
	string key;
	int numberOfOccurrences;
	Node* leftChild;
	Node* rightChild;
	Node* parent;
};
struct Tree
{
	Node* root;
};

//-- Function prototypes
Node* search(Node* node, string key);
string insertValue(Tree* tree, string key);
void addNodeToTree(Tree* tree, Node* node);
string deleteValue(Tree* tree, string key);
void deleteNode(Tree* tree, Node* node);
void transplant(Tree* tree, Node* nodeOne, Node* nodeTwo);
Node* min(Node* node);
string max(Node* node);
string next(Node* node, string key);
string previous(Node* node, string key);
string list(Node* node);
string help();

int main() {
	//-- Create a new, empty tree to start with
	Tree* tree = new Tree();

	//-- Keep looping until the user enters "exit"
	while (true) {
		//-- Display a command prompt-like pointer
		cout << "BSTree> ";

		//-- Take user input from the console
		string input;
		cin >> input;

		//-- The transform method will convert the input string to all lowercase, making it easier to evaluate.
		transform(input.begin(), input.end(), input.begin(), tolower);

		//-- Go to the appropriate action the user requested
		if (input == "search") {
			string wordToSearch;
			cin >> wordToSearch;

			Node* node = search(tree->root, wordToSearch);
			cout << node->key + " " + to_string(node->numberOfOccurrences);
		} else if (input == "insert") {
			string wordToInsert;
			cin >> wordToInsert;

			cout << insertValue(tree, wordToInsert);
		} else if (input == "delete") {
			string wordToDelete;
			cin >> wordToDelete;

			cout << deleteValue(tree, wordToDelete);
		} else if (input == "min") {
			cout << min(tree->root);
		} else if (input == "max") {
			cout << max(tree->root);
		} else if (input == "next") {
			string stringToFind;
			cin >> stringToFind;

			cout << next(tree->root, stringToFind);
		} else if (input == "prev") {
			string stringToFind;
			cin >> stringToFind;

			cout << previous(tree->root, stringToFind);
		} else if (input == "list") {
			cout << list(tree->root);
		} else if (input == "help") {
			cout << help();
		} else if (input == "exit") {
			//-- Exit the application
			return 0;
		} else {
			//-- User entered invalid input. Notify the user that their input was invalid and have them prompt again.
			cout << "The input '" + input + "' is invalid. Enter 'help' for a list of commands." << endl;
		}
	}
}

// Searches for the value in the tree
Node* search(Node* node, string key) {
	// If the node we're looking at is NULL or if the node's key matches the key being searched, return the node.
	// Else if the key is less than the node's key, search relative to the node's left child.
	// Else search relative to the node's right child (the key is greater than the node's right child)

	if (node == NULL || key == node->key) {
		return node;
	}
	if (key < node->key) {
		return search(node->leftChild, key);
	}
	return search(node->rightChild, key);
}

// Inserts the string into the tree
string insertValue(Tree* tree, string key) {
	// 1. Search if the key already exists
	// 2. If yes, just increment the counter
	// 3. Otherwise, create a new node and hang it on the tree.
	Node* newNode = NULL;
	Node* existingNode = search(tree->root, key);
	if (existingNode == NULL) {
		//-- Create a new node
		newNode = new Node();
		newNode->key = key;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->numberOfOccurrences = 1;

		// Hang the node on the tree
		addNodeToTree(tree, newNode);

		return newNode->key + " " + to_string(newNode->numberOfOccurrences);
	} else {
		// Increment its counter
		existingNode->numberOfOccurrences++;

		return existingNode->key + " " + to_string(existingNode->numberOfOccurrences);
	}

}

void addNodeToTree(Tree* tree, Node* node) {
	Node* currentNode = tree->root;
	Node* previousNode = NULL;

	//-- Keep looping until the currentNode falls off of the tree. Then we found our place to hang our new node
	while (currentNode != NULL) {
		previousNode = currentNode; // Keep track of the last node we visited before moving along, in case we fall off.

		// Should the new node be left or right of the node we're currently looking at?
		if (node->key < currentNode->key) {
			currentNode = currentNode->leftChild;
		} else {
			currentNode = currentNode->rightChild;
		}
	}

	// Set the node's parent to the latest node we reached before falling off.
	node->parent = previousNode;
	if (previousNode == NULL) {
		// There was no previous node; this is now the root.
		tree->root = node;
	} else if (node->key < previousNode->key) {
		previousNode->leftChild = node;
	} else {
		previousNode->rightChild = node;
	}
}

// Deletes the string from the tree
string deleteValue(Tree* tree, string key) {
	// 1. Check to see if the node is even IN the tree.
	Node* nodeToDelete = search(tree->root, key);

	if (nodeToDelete != NULL) {
		if (nodeToDelete->numberOfOccurrences == 1) {
			// 2. If the counter is currently at one, actually delete the node.

		} else {
			// 3. Otherwise, just decrement the counter
			nodeToDelete->numberOfOccurrences--;
		}
	}
	// 4. The node does not exist
	return key + " " + "-1";
}

void deleteNode(Tree* tree, Node* node) {
	if (node->leftChild == NULL) {
		// The node has no left child, so replace this node with it's current right-child.
		transplant(tree, node, node->rightChild);
	} else if (node->rightChild == NULL) {
		// The node has no right child, but has a left child, so replace this node with it's current left child.
		transplant(tree, node, node->leftChild);
	} else {
		// Otherwise, find the node's successor and make that the replacement
		Node* successor = min(node);
		if (successor->parent != node) {
			// If the successor isn't the node's parent, replace the successor with the successor's right child
			transplant(tree, successor, successor->rightChild);
			// Now make the nodeToDelete's right child into the successor's right child
			successor->rightChild = node->rightChild;
			successor->rightChild->parent = successor;
		}
		// Replace the node to delete with the successor
		transplant(tree, node, successor);
		successor->leftChild = node->leftChild;
		successor->leftChild->parent = successor;
	}
}

// "Transplants" two nodes; taking the subtree at nodeOne, replaces it with the subtree at nodeTwo
void transplant(Tree* tree, Node* nodeOne, Node* nodeTwo) {
	//-- If nodeOne is the current root, make nodeTwo the new root
	if (nodeOne->parent == NULL) {
		tree->root = nodeTwo;
	} else if (nodeOne == nodeOne->parent->leftChild) {
		//-- nodeOne is a left child of its parent. nodeTwo now becomes the left child of nodeOne's parent
		nodeOne->parent->leftChild = nodeTwo;
	} else {
		//-- Otherwise nodeTwo becomes nodeOne's parent's right child.
		nodeOne->parent->rightChild = nodeTwo;
	}

	if (nodeTwo != NULL) {
		//-- If nodeTwo isn't null, then set nodeTwo's parent to be nodeOne's since it has been swapped
		nodeTwo->parent = nodeOne->parent;
	}
}

// Returns the node with the smallest value (ex. a < z)
Node* min(Node* node) {
	while (node->leftChild != NULL) {
		node = node->leftChild;
	}
	return node;
}

// Outputs the text with the largest value (ex z > a)
string max(Node* node) {
	while (node->rightChild != NULL) {
		node = node->rightChild;
	}
	return node->key + " " + to_string(node->numberOfOccurrences);
}

// Outputs the item that is directly next to the string entered
string next(Node* node, string key) {
	// If the node has a right child, then just find the minimum relative to the right child.
	// If the node has no right child, move to its parent, and keep going to its parent until a left "branch" is taken.
	if (node->rightChild != NULL) {
		return next(node->rightChild, key);
	}
	Node* successor = node->parent;
	while (successor != NULL && node->parent == successor->rightChild) {
		node = successor;
		successor = successor->parent;
	}
	return node->key + " " + to_string(node->numberOfOccurrences);
}

// Outputs the item that is directly previous to the string entered
string previous(Node* node, string key) {
	// If the node has a left child, then just find the maximum relative to the left child.
	// If the node has no left child, move to its parent, and keep going to its parent until a right "branch" is taken.
	if (node->leftChild != NULL) {
		return next(node->leftChild, key);
	}
	Node* predecessor = node->parent;
	while (predecessor != NULL && node->parent == predecessor->leftChild) {
		node = predecessor;
		predecessor = predecessor->parent;
	}
	return node->key + " " + to_string(node->numberOfOccurrences);
}

// Returns an in-order traversal of the tree in its current form
string list(Node* node) {
	// Since this is an in-order traversal (maintains order), three steps are performed:
	//    1. Call this function on the left child if it's not null. (recursive call)
	//    2. Output the current node.
	//    3. Call this function on the right child if it's not null. (recursive call)
	string output;
	if (node->leftChild != NULL) {
		output += list(node->leftChild);
	}
	output += node->key + " ";
	if (node->rightChild != NULL) {
		output += list(node->rightChild);
	}
	return output;
}

// Outputs help text to the user, showing a list of available commands
string help() {
	string helpText = "Available Commands (Case INsensitive)\n=====================================\n";

	//-- insert
	helpText += "insert <string>: Inserts the string into the tree. If <string> already exists,      ";
	helpText += "its counter is incremented by 1. <string> and its count is then displayed.";
	helpText += "\n\n";
	
	//-- delete
	helpText += "delete <string>: Decrements <string>s counter by 1. If <string>'s counter is 0";
	helpText += "      after decrementing, <string> is removed from the tree. If <string> is not in";
	helpText += "    the tree,  <string> <-1> is displayed";
	helpText += "\n\n";

	//-- search
	helpText += "search <string>: Searches for <string> in the tree. If <string> is in the set,";
	helpText += "      <string> <nnn> is displayed, where <nnn> is the number of occurrences in the";
	helpText += "    set. Otherwise <string> <0> is displayed.";
	helpText += "\n\n";
	
	//-- min
	helpText += "min: Displays <string>, where <string> is the smallest value in the set. If the";
	helpText += "     set is empty, a blank line is displayed.";
	helpText += "\n\n";

	//-- max
	helpText += "max: Displays <string>, where <string> is the largest value in the set. If the";
	helpText += "      set is empty, a blank line is displayed.";
	helpText += "\n\n";

	//-- next
	helpText += "next <string>: If <string> is in the set, the next value in the set is shown. If";
	helpText += "    <string> is the max, or is not in the set, a blank line is shown.";
	helpText += "\n\n";

	//-- prev
	helpText += "prev <string>: If <string> is in the set, the previous value in the set is";
	helpText += "          shown. If <string> is the min, or is not in the set, a blank line is shown.";
	helpText += "\n\n";

	//-- list
	helpText += "list: Outputs all items in the set in order from min to max.";
	helpText += "\n\n";

	//-- help
	helpText += "help: Displays this screen";
	helpText += "\n\n";

	//-- exit
	helpText += "exit: Exits the program \n";
	return helpText;
}