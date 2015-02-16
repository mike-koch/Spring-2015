#include <algorithm>
#include <iostream>
#include <string>
#include "BSTree.h"
using namespace std;

//-- Function prototypes
string help();

int main() {
	BSTree* tree = new BSTree();
	//-- Keep looping until the user enters "exit"
	while (true) {
		//-- Take user input from the console
		string input;
		cin >> input;

		//-- The transform method will convert the input string to all lowercase, making it easier to evaluate.
		transform(input.begin(), input.end(), input.begin(), tolower);

		//-- Go to the appropriate action the user requested
		if (input == "search") {
			string wordToSearch;
			cin >> wordToSearch;

			tree->searchForValue(wordToSearch);
		} else if (input == "insert") {
			string wordToInsert;
			cin >> wordToInsert;

			tree->insertValue(wordToInsert);
		} else if (input == "delete") {
			string wordToDelete;
			cin >> wordToDelete;

			tree->deleteValue(wordToDelete);
		} else if (input == "min") {
			tree->findMin();
		} else if (input == "max") {
			tree->findMax();
		} else if (input == "next") {
			string stringToFind;
			cin >> stringToFind;
			tree->findNext(stringToFind);
		} else if (input == "prev") {
			string stringToFind;
			cin >> stringToFind;

			tree->findPrevious(stringToFind);
		} else if (input == "list") {
			tree->listTree();
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

// Outputs help text to the user, showing a list of available commands
string help() {
	string helpText = "Available Commands (Case INsensitive)\n=====================================\n";

	//-- insert
	helpText += "insert <string>: Inserts the string into the tree. If <string> already exists, its counter is incremented by 1. <string> and ";
	helpText += "its count is then displayed.";
	helpText += "\n\n";

	//-- delete
	helpText += "delete <string>: Decrements <string>'s counter by 1. If <string>'s counter is 0 after decrementing, <string> is removed from ";
	helpText += "the tree.If <string> is not in the tree, <string> <-1> is displayed";
	helpText += "\n\n";

	//-- search
	helpText += "search <string>: Searches for <string> in the tree. If <string> is in the set, <string> <nnn> is displayed, where <nnn> is ";
	helpText += "the number of occurrences in the set.Otherwise <string> <0> is displayed.";
	helpText += "\n\n";

	//-- min
	helpText += "min: Displays <string>, where <string> is the smallest value in the set. If the set is empty, a blank line is displayed.";
	helpText += "\n\n";

	//-- max
	helpText += "max: Displays <string>, where <string> is the largest value in the set. If the set is empty, a blank line is displayed.";
	helpText += "\n\n";

	//-- next
	helpText += "next <string>: If <string> is in the set, the next value in the set is shown. If <string> is the max, or is not in the set, ";
	helpText += "a blank line is displayed.";
	helpText += "\n\n";

	//-- prev
	helpText += "prev <string>: If <string> is in the set, the previous value in the set is shown. If <string> is the min, or is not in the ";
	helpText += "set, a blank line is displayed.";
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