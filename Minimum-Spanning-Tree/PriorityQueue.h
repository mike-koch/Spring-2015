#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
class PriorityQueue
{
public:
	PriorityQueue();
	~PriorityQueue();
	void insert(void* element);
	void* getMinimum();
	void* extractMinimum();
	void increaseKey(void* element, void* newKey);
};
#endif

