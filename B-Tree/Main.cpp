// Main.cpp
// Mike Koch
// EECS 2510 | Spring 2015 | 04/17/2015
// Entry point of the program. Responsible for traversing through Shakespeare.txt 3 times: one as a "dry run", and the others to populate an
//    AVL tree and a BTree.

#include <iostream>
#include <fstream>
#include <time.h>
#include "AVLTree.h"
#include "BTree.h"
#include "DiskIO.h"
using namespace std;

static const string AVL_FILE_NAME = "AVLNodes.nodes";
static const string BTREE_FILE_NAME = "BTreeNodes.nodes";

AVLTree avlTree;
BTree bTree;

enum InputMode
{
	DRY_RUN,
	AVL,
	B_TREE
};

//Function prototypes
int processFile(string filePath, InputMode inputMode, int elapsedOverheadTime = 0);
void cleanup(InputMode inputMode);
void parseInput(string filePath, InputMode inputMode);
void insertWord(string& word, InputMode inputMode);
void outputMetrics(InputMode inputMode);
bool isDelimiter(char c);
void outputTitle(string header);

// Process the file three times: first as a dry run (to calculate overhead), and then once each through the AVL and BTree.
int main2()
{
	const string INPUT_FILE = "C:\\Shakespeare.txt";

	//outputTitle("Starting dry run");
	//int overheadTime = processFile(INPUT_FILE, InputMode::DRY_RUN);
	int overheadTime = 0;

	//outputTitle("Starting AVL Tree");
	//DiskIO::openFileStream(AVL_FILE_NAME);
	//processFile(INPUT_FILE, InputMode::AVL, overheadTime);
	//DiskIO::closeFileStream();

	outputTitle("Starting BTree");
	DiskIO::openFileStream(BTREE_FILE_NAME);
	bTree.initializeTree();
	processFile(INPUT_FILE, InputMode::B_TREE, overheadTime);
	DiskIO::closeFileStream();

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

// Process the file, and then returns the elapsed time. Only truly helpful for the dry run so we have a benchmark for the other runs.
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

// Taking the file path, open an input stream and parse each word from the file by looking for delimiters (such as !, ., etc)
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
			//-- We're not at a delimiter; just keep going
			chari[iPtr] = c;
			iPtr++;
		}
		wasDelimiter = isDelimiter(c);
		inputStream.get(c);
	}
	inputStream.close();
	outputMetrics(inputMode);
}

// Inserts a word into the respective tree, based on the current InputMode
void insertWord(string& word, InputMode inputMode)
{
	switch (inputMode)
	{
	case InputMode::AVL:
		avlTree.insertValue(word);
		break;
	case InputMode::B_TREE:
		bTree.insertValue(word);
		break;
	}
}

// Outputs relevant metrics, such as height, number of words, etc.
void outputMetrics(InputMode inputMode)
{
	switch (inputMode)
	{
	case InputMode::AVL:
		avlTree.outputMetrics();
		break;
	case InputMode::B_TREE:
		bTree.outputMetrics();
		break;
	}
}

// Checks to see if a specific character is classified as a delimiter
bool isDelimiter(char c)
{
	return  (c == 32 || c == 10 || c == 13 || c == 9 ||
		c == '.' || c == ',' || c == '!' || c == ';' ||
		c == ':' || c == '(' || c == ')');
}