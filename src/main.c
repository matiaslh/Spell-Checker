
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/HashTableAPI.h"

#define MAX_STRING_SIZE 100

/*
	Add word to the dictionary
	@param hashTable hashtable
*/
void addWord(HTable* hashTable);

/*
	Remove word from dictionary
	@param hashTable hashtable
*/
void removeWord(HTable* hashTable);

/*
	Spell check a file
	@param hashTable hashtable
*/
void spellCheck(HTable* hashTable);

/*
	Get input from file and store inside hashtable
	@param filename file to get input data
	@param hashtable to insert data
	@return -1 if errors occurred, amount of words found otherwise
*/
int parseInputFile(char* filename, HTable* hashTable);

/*
	Does an exponential calculation of x^y
	@param x base
	@param y power
*/
int power(int x, int y);

/*
	Makes the string all lowercase
	@param string
*/
void toLowerCase(char* string);

int main(int argc, char* argv[]) {

	size_t size = 137;
	HTable* hashTable = createTable(size, &hashNode, &destroyNodeData, &printNodeData);
	if (argc < 2 || parseInputFile(argv[1], hashTable) == -1) {
		printf("No file found.\n");
		return 0;
	}

	int input = 0;
	do {

		printf("1)\tAdd a word to Dictionary\n2)\tRemove a word from Dictionary\n3)\tSpell Check a file\n4)\tShow Dictionary Words\n5)\tQuit\n");
		printf("Enter an index for the menu above.\n");

		scanf(" %d", &input);
		getchar();
		switch (input) {
		case 1:
			addWord(hashTable);
			break;
		case 2:
			removeWord(hashTable);
			break;
		case 3:
			spellCheck(hashTable);
			break;
		case 4:
			printf("\nDictionary:\n");
			printTable(hashTable);
			break;
		case 5:
			destroyTable(hashTable);
			break;
		default:
			printf("Invalid input.\n");
		}

	} while (input != 5);

	return 0;
}

/*
	Add word to the dictionary
	@param table hashtable
*/
void addWord(HTable* hashTable) {
	char* buffer = malloc(sizeof(char) * MAX_STRING_SIZE);
	printf("Enter a word to add.\n");
	scanf("%s", buffer);
	toLowerCase(buffer);

	// Checks if the word already exists in the dictionary
	if (lookupData(hashTable, buffer) != NULL) {
		printf("Word already exists in dictionary.\n");
	} else {

		insertData(hashTable, buffer, buffer);
		if (lookupData(hashTable, buffer) != NULL) {
			printf("Word added.\n");
		} else {
			printf("Error adding word.\n");
		}
	}
	printf("\n");
}

/*
	Remove word from dictionary
	@param table hashtable
*/
void removeWord(HTable* hashTable) {
	char* buffer = malloc(sizeof(char) * MAX_STRING_SIZE);
	printf("Enter a word to remove.\n");
	scanf("%s", buffer);
	toLowerCase(buffer);

	// Checks if that word already is removed from the dictionary
	if (lookupData(hashTable, buffer) == NULL) {
		printf("Word is not in dictionary.\n");
	} else {

		removeData(hashTable, buffer);
		if (lookupData(hashTable, buffer) == NULL) {
			printf("Word removed.\n");
		} else {
			printf("Error removing word.\n");
		}
	}
	printf("\n");
}

/*
	Spell check a file
	@param table hashtable
*/
void spellCheck(HTable* hashTable) {
	char* filename = malloc(sizeof(char) * MAX_STRING_SIZE);
	printf("Enter a file to check.\n");
	scanf("%s", filename);

	FILE* file = fopen(filename, "r");
	if (!file) {
		printf("File not found.\n");
		return;
	}

	printf("\nFile processed by Spell Check %s:\n\n", filename);

	int correctWords = 0, incorrectWords = 0;
	for (int i = 0; !feof(file); i++) {
		char* buffer = malloc(sizeof(char) * MAX_STRING_SIZE);
		fscanf(file, "%s", buffer);

		// Checks if the word exists in the dictionary and increments respectively
		if (!lookupData(hashTable, buffer)) {
			incorrectWords++;
			printf("%s was not found in the dictionary.\n", buffer);
		} else {
			correctWords++;
		}
		free(buffer);
	}
	printf("\nCorrectly spelt words: %d\nIncorrectly spelt words: %d\n\n", correctWords, incorrectWords);

	char* input = malloc(sizeof(char) * MAX_STRING_SIZE);
	while (strcmp(input, "0") != 0) {
		printf("Enter '0' to return to main menu.\n");
		scanf("%s", input);
	}
	printf("\n");
	fclose(file);
}

/*
	Get input from file and store inside hashtable
	@param filename file to get input words
	@param hashTable of all data
	@return -1 if errors occurred, amount of words found otherwise
*/
int parseInputFile(char* filename, HTable * hashTable) {
	FILE* input = fopen(filename, "r");
	if (!input) {
		return -1;
	}

	int i = 0;

	for (i = 0; !feof(input); i++) {
		char* buffer = malloc(sizeof(char) * MAX_STRING_SIZE);
		fscanf(input, "%s", buffer);
		toLowerCase(buffer);
		insertData(hashTable, buffer, buffer);
	}
	fclose(input);
	return i;
}

int hashNode(size_t tableSize, char* key) {
	int sum = 0;

	// Converts the string to a unique number
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
















