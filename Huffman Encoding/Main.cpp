// Huffman Encoding
// Mike Koch - EECS 2510
// Main.cpp - Handles creating the "Huffman" instance, along with properly calling initializeFromFile, encode, and decode. Nothing fancy.

#include <iostream>
#include "Huffman.h"
using namespace std;

int main() {
	const string INPUT_FILE = "c:\\Shakespeare.txt";
	const string ENCODED_FILE_LOCATION = "c:\\Users\\Mike\\Desktop\\Shakespeare.enc";
	const string DECODED_FILE_LOCATION = "c:\\Users\\Mike\\Desktop\\Shakespeare.dec";
	Huffman tree;
	char waitChar;
	tree.initializeFromFile(INPUT_FILE);
	tree.encodeFile(INPUT_FILE, ENCODED_FILE_LOCATION);
	tree.decodeFile(ENCODED_FILE_LOCATION, DECODED_FILE_LOCATION);
	cout << "\nProcess complete. Press ENTER to exit.\n";
	cin.get(waitChar);
	return 0;
}