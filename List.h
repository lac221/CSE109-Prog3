/*
CSE 109: Fall 2018
Lydia Cornwell
LAC221
prototypes List functions
Program #3
*/

#ifndef LIST_H
#define LIST_H
#include"Node.h"
#include<stdio.h>

struct List_t
{
	size_t sizeList;
	size_t sizeFreeList;
	struct Node_t* listStart;
	struct Node_t* freeListStart;
	//Associated metadata so you can deallocate the free List
	struct Node_t** freeList;
	size_t freeCapacity;
	size_t freeSize;
};

struct List_t* makeList(struct List_t*);
void freeList(struct List_t*);
size_t size(struct List_t*);
size_t freeSize(struct List_t*);
struct Node_t* insert(struct List_t*, int);
size_t find(struct List_t*, int);
size_t removeItem(struct List_t*, int);
struct Node_t* getHead(struct List_t*);


#endif
