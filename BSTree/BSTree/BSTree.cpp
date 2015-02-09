#include <iostream>;
#include <string>;
using namespace std;

int main() {

	// keep looping until "exit" is retrieved.
	while (true) {
		// Take user input from the console
		string input;
		cin >> input;

		// Depending on input, go to proper action.
		// if (action == 'SEARCH'), etc...
		//-- each method is responsible for their actions and will return appropriately.
	}

	return 0;
}

Action getAction(string input) {
	// Sample Action to return.
	return Action::INSERT;
}

enum Action {
	INSERT,
	DELETE,
	SEARCH,
	MIN,
	MAX,
	NEXT,
	PREV,
	LIST,
	HELP,
	EXIT
};