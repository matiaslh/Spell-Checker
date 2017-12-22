
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/HashTableAPI.h"

/**Function to point the hash table to the appropriate functions. Allocates memory to the struct and table based on the size given.
*@return pointer to the hash table
*@param size size of the hash table
*@param hashFunction function pointer to a function to hash the data
*@param destroyData function pointer to a function to delete a single piece of data from the hash table
*@param printNode function pointer to a function that prints out a data element of the table
**/
HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char* key), void (*destroyData)(void *data), void (*printNode)(void *toBePrinted)) {
	HTable* hashTable = malloc(sizeof(HTable));
	hashTable->size = size;
	hashTable->destroyData = destroyData;
	hashTable->printNode = printNode;
	hashTable->hashFunction = hashFunction;
	hashTable->table = malloc(sizeof(Node*)*hashTable->size);

	for (int i = 0; i < hashTable->size; i++) {
		hashTable->table[i] = NULL;
	}

	return hashTable;
}

/*
	Print all dictionary words
	@param table hashtable
*/
void printTable(HTable * hashTable) {
	int empty = 1;
	for (int i = 0; i < hashTable->size; i++) {
		Node* currNode = hashTable->table[i];
		while (currNode) {
			printf("%d:%s:%s\n", i, currNode->key, (char*)currNode->data);
			currNode = currNode->next;
			empty = 0;
		}
	}
	if (empty) {
		printf("Table is empty.\n");
	}
	printf("\n");
}

/**Function for creating a node for the hash table.
*@pre Node must be cast to void pointer before being added.
*@post Node is valid and able to be added to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data is a generic pointer to any data type.
*@return returns a node for the hash table
**/
Node* createNode(char* key, void *data) {
	Node* node = malloc(sizeof(Node));
	node->key = key;
	node->data = data;
	node->next = NULL;
	return node;
}

/** Deletes the entire hash table and frees memory of every element.
*@pre Hash Table must exist.
*@param hashTable pointer to hash table containing elements of data
**/
void destroyTable(HTable *hashTable) {
	if (hashTable && hashTable->table) {
		for (int i = 0; i < hashTable->size; i++) {
			Node* currNode = hashTable->table[i];
			while (currNode) {
				Node* tempNode = currNode->next;
				hashTable->destroyData(currNode->data);
				free(currNode);
				currNode = tempNode;
			}
			hashTable->table[i] = NULL;
		}
		free(hashTable);
	}
}

/**Inserts a Node in the hash table.
*@pre hashTable type must exist and have data allocated to it
*@param hashTable pointer to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data pointer to generic data that is to be inserted into the list
**/
void insertData(HTable *hashTable, char* key, void *data) {
	Node* toInsert = createNode(key, data);
	int index = hashTable->hashFunction(hashTable->size, key);
	Node* currNode = hashTable->table[index];
	if (!currNode) {
		hashTable->table[index] = toInsert;

	} else {
		toInsert->next = hashTable->table[index];
		hashTable->table[index] = toInsert;
	}
}

/**Function to remove a node from the hash table
 *@pre Hash table must exist and have memory allocated to it
 *@post Node at key will be removed from the hash table if it exists.
 *@param hashTable pointer to the hash table struct
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 **/
void removeData(HTable *hashTable, char* key) {

	int index = hashTable->hashFunction(hashTable->size, key);

	Node* currNode = hashTable->table[index];
	Node* previousNode = currNode;

	if (!currNode) {
		return;
	}

	if (strcmp(currNode->key, key) == 0) {
		hashTable->table[index] = currNode->next;
		hashTable->destroyData(currNode->data);
		free(currNode);
		return;
	}

	while (currNode) {
		if (strcmp(currNode->key, key) == 0) {
			hashTable->destroyData(currNode->data);
			free(currNode);
			previousNode->next = currNode->next;
			return;
		}
		previousNode = currNode;
		currNode = currNode->next;
	}

}

/**Function to return the data from the key given.
 *@pre The hash table exists and has memory allocated to it
 *@param hashTable pointer to the hash table containing data nodes
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 *@return returns a pointer to the data in the hash table. Returns NULL if no match is found.
 **/
void *lookupData(HTable *hashTable, char* key) {
	int index = hashTable->hashFunction(hashTable->size, key);
	Node* currNode = hashTable->table[index];
	while (currNode) {
		if (strcmp(currNode->key, key) == 0) {
			return currNode->data;
		}
		currNode = currNode->next;
	}
	return NULL;
}