#ifndef LIST_H
#define LIST_H
#include "LinkedListNode.h"
#include <iostream>
class List
{
public:
	List();
	~List();
	void add(void* item);
	void* get(unsigned int index);

private:
	// Keeps track of the first element in the list (for traversing), and the last element (for adding)
	LinkedListNode* firstElement = NULL;
	LinkedListNode* lastElement = NULL;
};
#endif

