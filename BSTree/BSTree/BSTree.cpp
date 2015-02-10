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
};
struct Tree
{
	Node* root;
};
int main() {

	// Keep looping until the user enters "exit"
	while (true) {
		// Take user input from the console
		string input;
		cin >> input;

		// The transform method will convert the input string to all lowercase, making it easier to evaluate.
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
			cout << "Entered help" << endl;
			//-- go to help
		} else if (input == "exit") {
			//-- Exit the application
			return 0;
		} else {
			//-- User entered invalid input. Notify the user that their input was invalid and have them prompt again.
			cout << "The input '" + input + "' is invalid. Enter 'help' for a list of commands." << endl;
		}
	}
}