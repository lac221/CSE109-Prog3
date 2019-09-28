/*
CSE 109: Fall 2018
Lydia Cornwell
LAC221
creates, mutates, accesses, and destroyes nodes
Program #3
*/

#include"Node.h"
#include<stdlib.h>

struct Node_t* makeNode1(struct Node_t* this)
{
	this->nextNode = NULL;
	this->nodeVal = 0;
	return this;
}

struct Node_t* makeNode2(struct Node_t* this, int data)
{
	this->nextNode = NULL;
	this->nodeVal = data;
	return this;
}

struct Node_t* makeNode4(struct Node_t* this, int data, struct Node_t* next)
{
	this->nextNode = next;
	this->nodeVal = data;
	return this;
}

void freeNode(struct Node_t* this)
{
	this->nextNode = NULL;
	this->nodeVal = 0;
}

int setData(struct Node_t* this, int data)
{
	return this->nodeVal = data;
}

struct Node_t* setNext(struct Node_t* this, struct Node_t* next)
{
	return this->nextNode = next;
}

int getData(struct Node_t* this)
{
	return  this->nodeVal;
}

struct Node_t* getNext(struct Node_t* this)
{
	return this->nextNode;
}
