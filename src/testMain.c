#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/HashTableAPI.h"

/*
	Does an exponential calculation of x^y
	@param x base
	@param y power
*/
int power(int x, int y);

int main(void) {

	printf("TEST MAIN STARTING\n\n");

	HTable* hashTable = NULL;
	char* buffer = NULL;

	// Creating and destroying tables with edge cases

	printf("\tCreating a table with size 137.\n\tExpected output:\nTable created.\n\tActual output:\nSuccessful.\n");
	hashTable = createTable(137, &hashNode, &destroyNodeData, &printNodeData);

	printf("\tDestroying table with size 137.\n\tExpected output:\nTable destroyed.\n\tActual output:\nSuccessful.\n");
	destroyTable(hashTable);

	printf("\tCreating a table with size 0.\n\tExpected output:\nTable created.\n\tActual output:\nSuccessful.\n");
	hashTable = createTable(0, &hashNode, &destroyNodeData, &printNodeData);

	printf("\tDestroying table with size 0.\n\tExpected output:\nTable destroyed.\n\tActual output:\nSuccessful.\n");
	destroyTable(hashTable);

	printf("\tCreating a table with size 199.\n\tExpected output:\nTable created.\n\tActual output:\nSuccessful.\n");
	hashTable = createTable(199, &hashNode, &destroyNodeData, &printNodeData);

	// Inserting and removing data from the table with edge cases

	printf("\tInserting long sentence of data into the hashtable.\n\tExpected output:\n<index>:<long sentence>:<long sentence>\n\tActual output:\n");
	buffer = malloc(sizeof(char) * 200);
	strcpy(buffer, "Testing a long sentence for the key and then checking if it works correctly.");
	insertData(hashTable, buffer, buffer);
	printTable(hashTable);
	printf("Successful.\n");

	printf("\nRemoving long sentence of data from the hashtable.\n\tExpected output:\nEmpty Table.\n\tActual output:\n");
	removeData(hashTable, buffer);
	printTable(hashTable);
	printf("Successful.\n");

	printf("\tInserting empty string of data into the hashtable.\n\tExpected output:\n0::\n\tActual output:\n");
	buffer = malloc(sizeof(char) * 1);
	strcpy(buffer, "\0");
	insertData(hashTable, buffer, buffer);
	printTable(hashTable);
	printf("Successful.\n");

	printf("\nRemoving empty string of data from the hashtable.\n\tExpected output:\nEmpty Table.\n\tActual output:\n");
	removeData(hashTable, buffer);
	printTable(hashTable);
	printf("Successful.\n");

	// Inserting and lookup of data in the hashtable

	printf("\tInserting 'hello' into the hashtable.\n\tExpected output:\n<index>:hello:hello\n\tActual output:\n");
	buffer = malloc(sizeof(char) * 100);
	strcpy(buffer, "hello");
	insertData(hashTable, buffer, buffer);
	printTable(hashTable);
	printf("Successful.\n");

	printf("\tInserting 'goodbye' into the hashtable.\n\tExpected output:\n<index>:goodbye:goodbye\n<index>:hello:hello\n\tActual output:\n");
	buffer = malloc(sizeof(char) * 100);
	strcpy(buffer, "goodbye");
	insertData(hashTable, buffer, buffer);
	printTable(hashTable);
	printf("Successful.\n");

	printf("\tInserting 'assignment' into the hashtable.\n\tExpected output:\n<index>:goodbye:goodbye\n<index>:assignment:assignment\n<index>:hello:hello\n\tActual output:\n");
	buffer = malloc(sizeof(char) * 100);
	strcpy(buffer, "assignment");
	insertData(hashTable, buffer, buffer);
	printTable(hashTable);
	printf("Successful.\n");

	printf("Looking up data for 'goodbye' in the hashtable.\n\tExpected output:\ngoodbye\n\tActual output:\n");
	buffer = malloc(sizeof(char) * 100);
	strcpy(buffer, "goodbye");
	printf("%s\n", (char*)(lookupData(hashTable, buffer)));
	printf("Successful.\n");

	printf("Looking up data for 'hello' in the hashtable.\n\tExpected output:\nhello\n\tActual output:\n");
	buffer = malloc(sizeof(char) * 100);
	strcpy(buffer, "hello");
	printf("%s\n", (char*)(lookupData(hashTable, buffer)));
	printf("Successful.\n");

	printf("Looking up data for 'assignment' in the hashtable.\n\tExpected output:\nassignment\n\tActual output:\n");
	buffer = malloc(sizeof(char) * 100);
	strcpy(buffer, "assignment");
	printf("%s\n", (char*)(lookupData(hashTable, buffer)));
	printf("Successful.\n");

	printf("Looking up data for 'nope' in the hashtable.\n\tExpected output:\nNULL\n\tActual output:\n");
	buffer = malloc(sizeof(char) * 100);
	strcpy(buffer, "nope");
	printf("%p\n", lookupData(hashTable, buffer));
	printf("Successful.\n");

	// Final destroy of hashtable to free data allocated

	printf("\tDestroying table with size 199 along with its data stored inside (hello, goodbye, assignment).\n\tExpected output:\nTable destroyed.\n\tActual output:\n");
	destroyTable(hashTable);
	printTable(hashTable);
	printf("Successful.\n");

	return 0;
}

int hashNode(size_t tableSize, char* key) {
	int sum = 0;
	for (int i = 0; i < strlen(key); i++) {
		char c = key[i];
		int value = c - '0';
		sum += value * power(2, i);
	}
	return sum % tableSize;
}

/*
	Does an exponential calculation of x^y
	@param x base
	@param y power
*/
int power(int x, int y) {
	if (y == 0) {
		return 1;
	}
	return x * power(x, y - 1);
}

/*
	Makes the string all lowercase
	@param string
*/
void toLowerCase(char* string) {
	for (int i = 0; i < strlen(string); i++) {
		string[i] = tolower(string[i]);
	}
}

void destroyNodeData(void *data) {
	free(data);
}

void printNodeData(void *toBePrinted) {
	printf("%s\n", (char*)toBePrinted);
}
