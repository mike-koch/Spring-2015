#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;
#include "Huffman.h"

//-- PUBLIC methods

// Builds a Huffman tree based on each byte processed. Each byte will be one of the ASCII characters with an int value of 0-255.
void Huffman::initializeFromFile(string fileName) {
	// Obtain the file from the filepath
	ifstream inputFile;
	inputFile.open(fileName, ios::binary);

	if (inputFile.fail()) {
		char waitChar;
		cout << "ERROR: The file could not be opened. Check that the path exists and try again. Press ENTER to exit.";
		cin.get(waitChar);
		exit(1);
	}

	int characterArray[256];

	while (!inputFile.eof()) {
		char symbol;
		inputFile.get(symbol);
		characterArray[(unsigned char)symbol]++;
		cout << characterArray[symbol];
	}
}

/*
   Summary: Takes the contents of the "inFile" and stores the encoded result in the "outFile".  Function also outputs input/output byte counts,
            size of the encoded file as a percentage of the original file's size. Elapsed time is also displayed.
   Requires: initializeFromFile must have been ran before encoding; otherwise there is no tree to use as the key!
*/
void Huffman::encodeFile(string inFile, string outFile) {
	//placeholder
}

/*
   Summary: takes the contents of the "inFile" and stores the decoded result in the "outFiel". Function also outputs in / out byte counts, as well as elapsed time.
   Requires: initializeFromFile must have been ran before encoding; otherwise there is no tree to use as the key!
*/
void Huffman::decodeFile(string inFile, string outFile) {
	//placeholder
}