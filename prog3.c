#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"List.h"
#include"ListTraverse.h"

int main(int argc, char **argv)
{
	if((argc != 4) && (argc != 3))
	{
		fprintf(stderr, "Not enough arguments: %s <count> <seed> [unbounded==1]\n", argv[0]);
		return 1;
	}
	int count = atoi(argv[1]);
	int seed = atoi(argv[2]);
	int unbounded = 0;
	if(argc == 4)
	{
		unbounded = atoi(argv[3]);
	}

	srand(seed);
	struct List_t *myList = (struct List_t*)malloc(1 * sizeof(struct List_t));
	myList = makeList(myList);

	char* commands = (char*)malloc(7 * sizeof(char));
	strcpy(commands, "csSifr");
	for(int i=0; i<count; i++)
	{
		int rOption;
		if(unbounded == 1)
		{
			rOption = rand();
			if(rand() & 1)
			{
				rOption = -1 * rOption;
			}
		}
		else
		{
			rOption = rand() % 1000;
		}

		char rBuffer[100];
		char rCommand = commands[rand() % strlen(commands)];
		switch(rCommand)
		{
		case 'c':
		case 's':
		case 'S':
			sprintf(rBuffer, "-%c", rCommand);
			break;
		case 'i':
		case 'f':
		case 'r':
			sprintf(rBuffer, "-%c:%d", rCommand, rOption);
			break;
		}

		int option = 0;
		char command = '\0';
		fprintf(stderr, "Processing command '%s'.\n", rBuffer);
		if(sscanf(rBuffer, "-%c:%d", &command, &option) < 1)
		{
			fprintf(stderr, "Unable to process command.\n");
			return 2;
		}
		switch(command)
		{
		case 'c':
			freeList(myList);
			free(myList);
			myList = (struct List_t*)malloc(1 * sizeof(struct List_t));
			myList = makeList(myList);
			break;
		case 's':
			fprintf(stdout, "Size: %ld.\n", size(myList));
			break;
		case 'S':
			fprintf(stdout, "Free List Size: %ld.\n", freeSize(myList));
			break;
		case 'i':
			{
				struct Node_t* myNode = insert(myList, option);
				if(myNode == NULL)
				{
					fprintf(stderr, "Insert failed.\n");
					return 3;
				}
			}
			break;
		case 'f':
			fprintf(stdout, "Found %ld elements.\n", find(myList, option));
			break;
		case 'r':
			fprintf(stdout, "Removed %ld elements.\n", removeItem(myList, option));
			break;
		}

		char* buffer = traverse(myList);
		size_t listSize = size(myList);
		size_t freeListSize = freeSize(myList);
		fprintf(stdout, "List (%ld, %ld): %s.\n", listSize, freeListSize, buffer);
		free(buffer);
	}

	free(commands);
	commands = NULL;

	char* buffer = traverse(myList);
	fprintf(stdout, "List: %s.\n", buffer);
	free(buffer);

	freeList(myList);
	free(myList);
	myList = NULL;
	//valgrind should report no memory leaks at this point

	return 0;
}
