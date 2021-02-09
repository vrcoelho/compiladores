// 00243463 - Vanessa Coelho

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 997

typedef struct hashnode
{
	int type;
	char *lit;
	struct hashnode *next;
} HASHNODE;

HASHNODE *HashTable[HASHSIZE];

void initMe(void);
int hashAddress(char *lit);
HASHNODE* hashInsert(int type, char *lit);
void hashPrint(void);
HASHNODE* hashFind(char *lit, int address);