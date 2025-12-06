#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

using namespace std;

typedef int ItemType;

//error classes
class EmptyQueue
{};

class FullQueue
{};

class MissingItem
{};

class ItemExists
{};

struct NodeType
{
	Itemtype value;
	Itemtype priority;
	NodeType* previous;
	NodeType* next;

};

//the actual class
class PriorityQueue
{
private:
	NodeType* front;
	NodeType* rear;

public:
	PriorityQueue();
	void MakeEmpty();
	bool IsEmpty();
	bool IsFull();
	int Size();
	void Enqueue(ItemType newValue, ItemType priority);
	ItemType Dequeue();
	ItemType Peek();
	void UpdatePriority(ItemType value, ItemType newPriority);
	bool Search(ItemType value);
	void Print();
	~PriorityQueue();
};

#endif