/*
CSE 109: Fall 2018
Lydia Cornwell
LAC221
creates a 2 linked lists, freeList and list, and mutates
Program #3
*/

#include"List.h"
#include"ListTraverse.h"
#include"Node.h"
#include<stdio.h>
#include<stdlib.h>

void expandFreeList(struct List_t*);


struct List_t* makeList(struct List_t* this)
{
	this->sizeList = 0;
	this->sizeFreeList = 0;
	this->listStart = NULL;
	this->freeListStart = NULL;
	this->freeList = NULL;
	this->freeCapacity = 0;
	this->freeSize = 0;

	return this;
}

void freeList(struct List_t* this)
{
	for(int i = 0; i < this->freeSize; i++)
	{
		free(this->freeList[i]);
	}
	free(this->freeList);
}

size_t size(struct List_t* this)
{
	return this->sizeList;
}

size_t freeSize(struct List_t* this)
{
	return this->sizeFreeList;
}

struct Node_t* insert(struct List_t* this, int data)
{
	//malloc the free list if you need more nodes
	expandFreeList(this);

	struct Node_t* temp = (this->listStart);
	struct Node_t* newNode = this->freeListStart;
	this->freeListStart = getNext(this->freeListStart);
	makeNode2(newNode, data);
	if(this->listStart == NULL)
	{
		this->listStart = newNode;
		setNext(newNode, NULL);
		this->sizeFreeList -= 1;
		this->sizeList += 1;
		return newNode;
	}

//	fprintf(stderr, "Traversing\n");
	while(getNext(temp) != NULL)
	{
		//gets you to the end of the list
//		fprintf(stderr, "Temp at %d\n", temp->nodeVal);
		temp = getNext(temp);
	}

	setNext(temp, newNode);
	setNext(newNode, NULL);
	this->sizeFreeList -= 1;
	this->sizeList += 1;
	return newNode;
}

size_t find(struct List_t* this, int data)
{
	size_t counter = 0;
	struct Node_t* temp = (this->listStart);
	while(temp != NULL)
	{
		if(getData(temp) == data)
		{
			counter++;
		}
		temp = getNext(temp);
	}

	return counter;
}

size_t removeItem(struct List_t* this, int data)
{
	size_t removeCount = 0;
	struct Node_t* temp = (this->listStart);
	struct Node_t* prev = NULL;
	if(this->listStart == NULL)
	{
		return removeCount;
	}
	while(temp != NULL)
	{
		if(getData(temp) == data)
		{
			removeCount++;
			this->sizeList--;
			this->sizeFreeList++;

			if(prev == NULL)
			{
				this->listStart = getNext(temp);
				setNext(temp, this->freeListStart);
				this->freeListStart = temp;
				temp = this->listStart;
				continue;
			}

			setNext(prev, getNext(temp));
			setNext(temp, this->freeListStart);
			setNext(this->freeListStart, temp);
			freeNode(temp);

			temp = getNext(prev);
			continue;
		}

		prev = temp;
		temp = getNext(temp);
	}
	return removeCount;
}

struct Node_t* getHead(struct List_t* this)
{
	return this->listStart;
}


void expandFreeList(struct List_t* this)
{
	//if the list is empty, first malloc
	if(this->freeListStart == NULL)
	{
		struct Node_t* temp = (struct Node_t*)malloc(256 * sizeof(struct Node_t));

		for(int i = 0; i < 255; i++)
		{
			makeNode4(temp + i, 0, temp + i + 1);
		}
		setNext(temp + 255, NULL);
		this->sizeFreeList += 256;

		if(this->freeSize == this->freeCapacity)
		{
			size_t newFreeCap = (2 * (this->freeCapacity) + 1);
			struct Node_t** tempMeta = (struct Node_t**)malloc(newFreeCap * sizeof(struct Node_t*));
			for(int i = 0; i < this->freeSize; i++)
			{
				tempMeta[i] = this->freeList[i];
			}
			free(this->freeList);
			this->freeList = tempMeta;
			this->freeCapacity = newFreeCap;
		}

		this->freeList[this->freeSize] = temp;
		this->freeSize += 1;
		this->freeListStart = temp;
	}
}
