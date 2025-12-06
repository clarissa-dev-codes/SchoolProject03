/* Majority of code came from the queue code that we did in class
with the priority stuff being from my own research*/

#include <iostream>

#include "PriorityQueue.h"

using namespace std;

//default constructor
PriorityQueue::PriorityQueue()
{
	front = NULL;
	rear = NULL;
}

//Deletes all queue nodes
void PriorityQueue::MakeEmpty()
{
	NodeType* current;
	while (front != NULL)
	{
		current = front;
		front = front->next;
		delete current;
	}

	rear = NULL;
}

//checks if queue has no nodes
bool PriorityQueue::IsEmpty() const
{
	return (front == NULL);
}

//checks to see if the queue is full
bool PriorityQueue::IsFull()
{
	bool full = false;
	if (Size() < 0)
	{
		full = true;
	}
	return (full);
}

//gets the size of the queue
int PriorityQueue::Size()
{
	int size = 0;

	NodeType* current = front;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}

	return size;
}

//adds new element to the queue
void PriorityQueue::Enqueue(ItemType newValue, ItemType priority)
{

	NodeType* newNode = new NodeType;
	newNode->value = newValue;
	newNode->priority = priority;
	newNode->next = NULL;

	//checks if the queue is full
	if (IsFull())
	{
		throw FullQueue();
	}

	//test if the queue is empty
	if (IsEmpty())
	{
		front = rear = newNode;
	}

	else
	{
		NodeType* current = front;



		while (current->next != NULL)
		{
			//test to see if it even exists
			if (Search(newValue))
			{
				delete newNode;
				throw ItemExists();
			}

			current = current->next;
		}

		newNode->next = current->next;
		current->next = newNode;



		//if the node needs to go at the end
		if (newNode->next == NULL)
		{
			rear = newNode;
		}
	}
}

//removes element from the queue by priority
ItemType PriorityQueue::Dequeue()
{
	ItemType val;

	NodeType* current = front;
	NodeType* previous = NULL;

	//for the highest priority
	NodeType* high = front;
	NodeType* highPrev = NULL;

	if (IsEmpty())
	{
		throw EmptyQueue();
	}

	while (current != NULL)
	{
		//find it
		if (current->priority < high->priority)
		{
			high = current;
			highPrev = previous;
		}

		previous = current;
		current = current->next;

	}

	//remove it
	if (highPrev == NULL)
	{
		front = high->next;
	}

	else
	{
		highPrev->next = high->next;
	}


	//catch the rear
	if (high == rear)
	{
		rear = highPrev;
	}


	val = high->value;
	delete high;

	return val;

}


//returns the next element to be removed by priority
ItemType PriorityQueue::Peek()
{

	if (IsEmpty())
	{
		throw EmptyQueue();
	}

	NodeType* current = front;
	NodeType* high = front;

	while (current != NULL)
	{
		if (current->priority < high->priority)
		{
			high = current;
		}

		current = current->next;
	}

	return (high->value);
}

//updates the priority of the elements
void PriorityQueue::UpdatePriority(ItemType value, ItemType newPriority)
{
	//test if empty
	if (IsEmpty())
	{
		return;
	}

	NodeType* prev = NULL;
	NodeType* current = front;

	//find it
	while (current != NULL && current->value != value)
	{
		prev = current;
		current = current->next;
	}

	if (current == NULL)
	{
		throw MissingItem(); //here
	}


	//kill it
	if (prev == NULL)
	{
		front = current->next;
	}
	else
	{
		prev->next = current->next;
	}

	if (current == rear)
	{
		rear = prev;
	}

	//fix it
	ItemType val = current->value;
	delete current;
	Enqueue(val, newPriority);
}

//searches the queue
bool PriorityQueue::Search(ItemType value)
{
	NodeType* current = front;

	while (current != NULL)
	{
		if (current->value == value)
		{
			return true;
		}

		current = current->next;
	}

	return false;
}

//prints the queue
void PriorityQueue::Print()
{
	NodeType* current = front;

	cout << endl << "Current Queue " << endl << endl;
	while (current != NULL)
	{
		cout << "Element: " << current->value << " Priority: " << current->priority << endl;
		current = current->next;
	}
	cout << endl;

}

//deconstructor
PriorityQueue::~PriorityQueue()
{
	MakeEmpty();
}