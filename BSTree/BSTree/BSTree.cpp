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

			cout << search(tree, wordToSearch);
		} else if (input == "insert") {
			string wordToInsert;
			cin >> wordToInsert;

			cout << insertValue(tree, wordToInsert);
		} else if (input == "delete") {
			string wordToDelete;
			cin >> wordToDelete;

			cout << deleteValue(tree, wordToDelete);
		} else if (input == "min") {
			cout << min(tree);
		} else if (input == "max") {
			cout << max(tree);
		} else if (input == "next") {
			string stringToFind;
			cin >> stringToFind;

			cout << next(tree, stringToFind);
		} else if (input == "prev") {
			string stringToFind;
			cin >> stringToFind;

			cout << previous(tree, stringToFind);
		} else if (input == "list") {
			cout << list(tree);
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