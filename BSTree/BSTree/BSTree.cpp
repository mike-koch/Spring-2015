#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node
{
	string key;
	string value;
	Node* leftChild;
	Node* rightChild;
	Node* parent;
};
struct Tree
{
	Node* root;
};

//-- Function prototypes
string search(Tree* tree, string key);
string insertValue(Tree* tree, string key);
string deleteValue(Tree* tree, string key);
string min(Tree* tree);
string max(Tree* tree);
string next(Tree* tree, string key);
string previous(Tree* tree, string key);
string list(Tree* tree);
string help();

int main() {
	//-- Create a new, empty tree to start with
	Tree* tree = new Tree();

	//-- Keep looping until the user enters "exit"
	while (true) {
		//-- Take user input from the console
		string input;
		cin >> input;

		//-- The transform method will convert the input string to all lowercase, making it easier to evaluate.
		transform(input.begin(), input.end(), input.begin(), tolower);

		//-- Go to the appropriate action the user requested
		if (input == "search") {
			cout << "Entered search" << endl;
			//-- go to search
		} else if (input == "insert") {
			cout << "Entered insert" << endl;
			//-- go to insert
		} else if (input == "delete") {
			cout << "Entered delete" << endl;
			//-- go to delete
		} else if (input == "min") {
			cout << "Entered min" << endl;
			//-- go to min
		} else if (input == "max") {
			cout << "Entered max" << endl;
			//-- go to max
		} else if (input == "next") {
			string stringToFind;
			cin >> stringToFind;
			cout << "Entered next with stringToFind = " << stringToFind << endl;
			//-- go to next
		} else if (input == "prev") {
			string stringToFind;
			cin >> stringToFind;
			cout << "Entered prev with stringToFind = " << stringToFind << endl;
			//-- go to previous
		} else if (input == "list") {
			cout << "Entered list" << endl;
			//-- go to list
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
string search(Tree* tree, string key) {
	return "";
}

// Inserts the string into the tree
string insertValue(Tree* tree, string key) {
	return "";
}

// Deletes the string from the tree
string deleteValue(Tree* tree, string key) {
	return "";
}

// Outputs the text with the smallest value (ex. a < z)
string min(Tree* tree) {
	return "";
}

// Outputs the text with the largest value (ex z > a)
string max(Tree* tree) {
	return "";
}

// Outputs the item that is directly next to the string entered
string next(Tree* tree, string key) {
	return "";
}

// Outputs the item that is directly previous to the string entered
string previous(Tree* tree, string key) {
	return "";
}

// Outputs an in-order traversal of the tree in its current form
string list(Tree* tree) {
	return "";
}

// Outputs help text to the user, showing a list of available commands
string help() {
	return "TODO: Help text.";
}