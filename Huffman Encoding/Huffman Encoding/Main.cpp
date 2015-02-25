#include <iostream>
#include "Huffman.h"
using namespace std;

int main() {
	Huffman tree;
	char waitChar;
	tree.initializeFromFile("c:\\Shakespeare.txt");
	tree.encodeFile("c:\\Shakespeare.txt", "c:\\Shakespeare.enc");
	tree.decodeFile("c:\\Shakespeare.enc", "c:\\Shakespeare.dec");
	cout << "Process complete. Press ENTER to exit.\n";
	cin.get(waitChar);
	return 0;
}