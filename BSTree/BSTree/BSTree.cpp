#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#include "BSTree.h"

//-- PUBLIC methods
void BSTree::searchForValue(string key) {
	// Searches for the specified key starting at the root of the tree
	Node* searchedNode = search(root, key);

	if (searchedNode == NULL) {
		outputNodeInformation(key, "0");
	}
	else {
		outputNodeInformation(key, to_string(searchedNode->numberOfOccurrences));
	}
}

void BSTree::insertValue(string key) {
	// 1. Search if the key already exists
	// 2. If yes, just increment the counter
	// 3. Otherwise, create a new node and hang it on the tree.
	Node* newNode = NULL;
	Node* existingNode = search(root, key);
	if (existingNode == NULL) {
		//-- Create a new node
		newNode = new Node();
		newNode->key = key;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->numberOfOccurrences = 1;

		// Hang the node on the tree
		addNodeToTree(newNode);

		outputNodeInformation(key, "1");
	}
	else {
		// Increment its counter
		existingNode->numberOfOccurrences++;

		outputNodeInformation(existingNode->key, to_string(existingNode->numberOfOccurrences));
	}

}

void BSTree::deleteValue(string key) {
	// 1. Check to see if the node is even IN the tree.
	Node* nodeToDelete = search(root, key);

	if (nodeToDelete != NULL) {
		if (nodeToDelete->numberOfOccurrences == 1) {
			// Keep the key for output after the node has been deleted
			string key = nodeToDelete->key;

			// 2. If the counter is currently at one, actually delete the node.
			deleteNode(nodeToDelete);

			// Delete the node from memory
			delete nodeToDelete;

			outputNodeInformation(key, "0");
		}
		else {
			// 3. Otherwise, just decrement the counter
			nodeToDelete->numberOfOccurrences--;

			outputNodeInformation(nodeToDelete->key, to_string(nodeToDelete->numberOfOccurrences));
		}
	} else {
		// 4. The node does not exist
		outputNodeInformation(key, "-1");
	}
}

void BSTree::findMin() {
	Node* minNode = min(root);

	if (minNode != NULL) {
		outputNodeInformation(minNode->key, to_string(minNode->numberOfOccurrences));
	}
}

void BSTree::findMax() {
	Node* maxNode = max(root);

	if (maxNode != NULL) {
		outputNodeInformation(maxNode->key, to_string(maxNode->numberOfOccurrences));
	}
}

void BSTree::findNext(string key) {
	Node* nextNode = next(root, key);

	if (nextNode != NULL) {
		outputNodeInformation(nextNode->key);
	}
}

void BSTree::findPrevious(string key) {
	Node* previousNode = previous(root, key);

	if (previousNode != NULL) {
		outputNodeInformation(previousNode->key);
	}
}

void BSTree::listTree() {
	list(root);
}

//-- PRIVATE methods
Node* BSTree::search(Node* node, string key) {
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

void BSTree::addNodeToTree(Node* node) {
	Node* currentNode = root;
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
		root = node;
	} else if (node->key < previousNode->key) {
		previousNode->leftChild = node;
	} else {
		previousNode->rightChild = node;
	}
}

void BSTree::deleteNode(Node* node) {
	if (node->leftChild == NULL) {
		// The node has no left child, so replace this node with it's current right-child.
		transplant(node, node->rightChild);
	} else if (node->rightChild == NULL) {
		// The node has no right child, but has a left child, so replace this node with it's current left child.
		transplant(node, node->leftChild);
	} else {
		// Otherwise, find the node's successor and make that the replacement
		Node* successor = min(node);
		if (successor->parent != node) {
			// If the successor isn't the node's parent, replace the successor with the successor's right child
			transplant(successor, successor->rightChild);
			// Now make the nodeToDelete's right child into the successor's right child
			successor->rightChild = node->rightChild;
			successor->rightChild->parent = successor;
		}
		// Replace the node to delete with the successor
		transplant(node, successor);
		successor->leftChild = node->leftChild;
		successor->leftChild->parent = successor;
	}
}

// "Transplants" two nodes; taking the subtree at nodeOne, replaces it with the subtree at nodeTwo
void BSTree::transplant(Node* nodeOne, Node* nodeTwo) {
	//-- If nodeOne is the current root, make nodeTwo the new root
	if (nodeOne->parent == NULL) {
		root = nodeTwo;
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
Node* BSTree::min(Node* node) {
	while (node != NULL && node->leftChild != NULL) {
		node = node->leftChild;
	}
	return node;
}


// Outputs the text with the largest value (ex z > a)
Node* BSTree::max(Node* node) {
	while (node != NULL && node->rightChild != NULL) {
		node = node->rightChild;
	}

	return node;
}


// Outputs the item that is directly next to the string entered
Node* BSTree::next(Node* node, string key) {
	// 1. If the node passed into this function is NULL, return NULL.
	// 2. If the node has a right child, then just find the minimum relative to the right child.
	// 3. If the node has no right child, move to its parent, and keep going to its parent until a left "branch" is taken.
	if (node == NULL) {
		return NULL;
	}
	if (node->rightChild != NULL) {
		return next(node->rightChild, key);
	}
	Node* successor = node->parent;
	while (successor != NULL && node->parent == successor->rightChild) {
		node = successor;
		successor = successor->parent;
	}
	return node;
}


// Outputs the item that is directly previous to the string entered
Node* BSTree::previous(Node* node, string key) {
	// 1. If the node passed into this function is NULL, return NULL.
	// 2. If the node has a left child, then just find the maximum relative to the left child.
	// 3. If the node has no left child, move to its parent, and keep going to its parent until a right "branch" is taken.
	if (node == NULL) {
		return NULL;
	}
	if (node->leftChild != NULL) {
		return next(node->leftChild, key);
	}
	Node* predecessor = node->parent;
	while (predecessor != NULL && node->parent == predecessor->leftChild) {
		node = predecessor;
		predecessor = predecessor->parent;
	}
	return node;
}


// Returns an in-order traversal of the tree in its current form
void BSTree::list(Node* node) {
	// Since this is an in-order traversal (maintains order), three steps are performed:
	//    1. Call this function on the left child if it's not null. (recursive call)
	//    2. Output the current node.
	//    3. Call this function on the right child if it's not null. (recursive call)
	if (node == NULL) {
		return;
	}
	list(node->leftChild);
	outputNodeInformation(node->key, to_string(node->numberOfOccurrences));
	list(node->rightChild);
}

void BSTree::outputNodeInformation(string key, string value) {
	cout << key + " " + value << endl;
}