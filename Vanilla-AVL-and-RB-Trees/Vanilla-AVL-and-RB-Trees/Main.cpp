// Main.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 03/30/2015
// Entry point of the program. Responsible for traversing through Shakespeare.txt 4 times: one as a "dry run", and the others to populate a
//    "vanilla" BST, an AVL binary tree, and a Red-Black binary tree.

#include <iostream>
#include <fstream>
#include "BSTree.h"
#include "AVLTree.h"
using namespace std;

BSTree bstree;
AVLTree avlTree;

enum InputMode
{
	DRY_RUN,
	BST,
	AVL,
	RBT
};

//Function prototypes
void parseFile(string filePath, InputMode inputMode);
void insertWord(string word, InputMode inputMode);
void outputMetrics(InputMode inputMode);
bool isDelimiter(char c);

int main() 
{
	const string INPUT_FILE = "C:\\Shakespeare.txt";

	cout << "Starting dry run\n";
	parseFile(INPUT_FILE, InputMode::DRY_RUN);
	cout << "Starting BST\n";
	parseFile(INPUT_FILE, InputMode::BST);
	parseFile(INPUT_FILE, InputMode::AVL);
	//parseFile(INPUT_FILE, InputMode::RBT);
	cout << "Finished. Press ENTER to exit.";
	char throwaway;
	cin.get(throwaway);
	exit(0);
	// avl

	// rbt
}

void parseFile(string filePath, InputMode inputMode)
{
	char c;
	ifstream inputStream;
	char chari[50]; // assuming no word is > 49 characters
	int iPtr;
	bool wasDelimiter = false;
	inputStream.open(filePath);

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
			for (int i = 0; i <= iPtr; i++)
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

void insertWord(string word, InputMode inputMode)
{
	switch (inputMode)
	{
		case InputMode::BST:
			bstree.insertValue(word);
			break;
		case InputMode::AVL:
			avlTree.insertValue(word);
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
	}
}

bool isDelimiter(char c)
{
	return  (c == 32 || c == 10 || c == 13 || c == 9 ||
			c == '.' || c == ',' || c == '!' || c == ';' ||
			c == ':' || c == '(' || c == ')');
}