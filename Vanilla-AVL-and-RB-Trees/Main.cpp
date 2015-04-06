// Main.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 03/30/2015
// Entry point of the program. Responsible for traversing through Shakespeare.txt 4 times: one as a "dry run", and the others to populate a
//    "vanilla" BST, an AVL binary tree, and a Red-Black binary tree.

#include <iostream>
#include <fstream>
#include <time.h>
#include "BSTree.h"
#include "AVLTree.h"
#include "RBTree.h"
using namespace std;

BSTree bstree;
AVLTree avlTree;
RBTree rbTree;

enum InputMode
{
	DRY_RUN,
	BST,
	AVL,
	RBT
};

//Function prototypes
int processFile(string filePath, InputMode inputMode, int elapsedOverheadTime = 0);
void parseInput(string filePath, InputMode inputMode);
void insertWord(string& word, InputMode inputMode);
void outputMetrics(InputMode inputMode);
bool isDelimiter(char c);
void outputTitle(string header);

int main() 
{
	const string INPUT_FILE = "C:\\Shakespeare.txt";

	outputTitle("Starting dry run");
	int overheadTime = processFile(INPUT_FILE, InputMode::DRY_RUN);

	outputTitle("Starting Vanilla BST");
	processFile(INPUT_FILE, InputMode::BST, overheadTime);

	outputTitle("Starting AVL Tree");
	processFile(INPUT_FILE, InputMode::AVL, overheadTime);

	outputTitle("Starting Red-Black Tree");
	processFile(INPUT_FILE, InputMode::RBT, overheadTime);

	cout << "\n\nFinished. Press ENTER to exit.";
	char throwaway;
	cin.get(throwaway);
	exit(0);
}

void outputTitle(string header)
{
	cout << endl << header << endl;
	cout << "-----------------------\n";
}

// Returns the elapsed time. Only truly helpful for the dry run so we have a benchmark for the other runs.
int processFile(string filePath, InputMode inputMode, int elapsedOverheadTime)
{
	clock_t startTime = clock();
	parseInput(filePath, inputMode);
	clock_t endTime = clock();
	int elapsedTime = endTime - startTime;
	cout << "Elapsed time: " << elapsedTime << " clock cycles.\n";

	// There is only time without overhead if this isn't the dry run
	if (inputMode != InputMode::DRY_RUN)
	{
		cout << "Excluding overhead, elapsed time: " << elapsedTime - elapsedOverheadTime << " clock cycles.\n";
	}
	return elapsedTime;
}

void parseInput(string filePath, InputMode inputMode)
{
	char c;
	ifstream inputStream;
	char chari[50]; // assuming no word is > 49 characters
	int iPtr;
	bool wasDelimiter = false;
	inputStream.open(filePath, ios::binary);

	if (inputStream.fail())
	{
		// Exiting as we are unable to open the file.
		cout << "Failed to open input file " << filePath << endl << "Press ENTER to exit.\n";
		cin.get(c);
		exit(1);
	}

	iPtr = 0;
	inputStream.get(c);
	while (!inputStream.eof())
	{
		// Check if we are currently at a delimiter, and we weren't at one before
		if (isDelimiter(c) && !wasDelimiter)
		{
			string currentWord = "";
			for (int i = 0; i < iPtr; i++)
			{
				currentWord += chari[i];
			}
			wasDelimiter = true;
			insertWord(currentWord, inputMode);
			for (int i = 0; i < 50; i++) chari[i] = '\0'; // We added the word, so clear it back out.
			iPtr = 0;
		}
		else if (!isDelimiter(c))
		{
			//-- We're not at a delimeter; just keep going
			chari[iPtr] = c;
			iPtr++;
		}
		wasDelimiter = isDelimiter(c);
		inputStream.get(c);
	}
	inputStream.close();
	outputMetrics(inputMode);
}

void insertWord(string& word, InputMode inputMode)
{
	switch (inputMode)
	{
		case InputMode::BST:
			bstree.insertValue(word);
			break;
		case InputMode::AVL:
			avlTree.insertValue(word);
			break;
		case InputMode::RBT:
			rbTree.insertValue(word);
			break;
	}
}

void outputMetrics(InputMode inputMode)
{
	switch (inputMode)
	{
		case InputMode::BST:
			bstree.outputMetrics();
			break;
		case InputMode::AVL:
			avlTree.outputMetrics();
			break;
		case InputMode::RBT:
			rbTree.outputMetrics();
			break;
	}
}

bool isDelimiter(char c)
{
	return  (c == 32 || c == 10 || c == 13 || c == 9 ||
			c == '.' || c == ',' || c == '!' || c == ';' ||
			c == ':' || c == '(' || c == ')');
}