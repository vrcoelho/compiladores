// 00243463 - Vanessa Coelho

#include "tokens.h"

void initMe(void)
{
	int i = 0;
	for (i = 0; i < HASHSIZE; i++)
		HashTable[i] = 0;
}

int hashAddress(char *lit)
{
	int address = 1;
	int i;

	for (i = 0; i < strlen(lit); i++)
		address = (address * lit[i]) % HASHSIZE +1;

	return (address - 1);
}

HASHNODE* hashFind(char *lit, int address)
{
	HASHNODE *node;
	for (node = HashTable[address]; node; node = node->next)
		if (strcmp(node->lit, lit) == 0)
			return node;

	return 0;
}

HASHNODE* hashInsert(int type, char *lit)
{
	HASHNODE *node;
	int address = hashAddress(lit);

	if ((node = hashFind(lit, address)) != 0)
		return node;

	node = (HASHNODE *) calloc(1, sizeof(HASHNODE));
	node->type = type;
	node->lit = calloc(strlen(lit)+1, sizeof(char));

	strcpy(node->lit, lit);

	node->next = HashTable[address];
	HashTable[address] = node;

	return node;
}

void hashPrint()
{
	int i = 0;
	HASHNODE *node;

	for (i = 0; i < HASHSIZE; i++)
		for (node = HashTable[i]; node != 0; node = node->next)
			printf("Hash[%d]: %s\n", i, node->lit);
}