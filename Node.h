/*
CSE 109: Fall 2018
Lydia Cornwell
LAC221
prototypes node functions
Program #3
*/

#ifndef NODE_H
#define NODE_H

struct Node_t
{
	struct Node_t* nextNode;
	int nodeVal;
};

//creation/destruction
struct Node_t* makeNode1(struct Node_t*);
struct Node_t* makeNode2(struct Node_t*, int);
struct Node_t* makeNode4(struct Node_t*, int, struct Node_t* next);
void freeNode(struct Node_t*);

//Mutators
int setData(struct Node_t*, int);
struct Node_t* setNext(struct Node_t*, struct Node_t* next);

//Accessors
int getData(struct Node_t*);
struct Node_t* getNext(struct Node_t*);

#endif
