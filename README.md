# Spell-Checker by Matias Levy-Hara
With a list of dictionary words, the program corrects a given file for incorrect words.


Program Information
###################
This program aims to create a dictionary of words using a text file.
With this dictionary, the user can add and remove words as they think of them.
Once the user completed their dictionary, they can use it to spell check another text file for incorrectly spelled words.
This programs spell checks the file by checking if each word already exists in the dictionary the user created.

To run the program:
	$ make
	$ make run file='path/to/dictionary.txt'	// you can use included dictionary in assets folder

To run the HashTable tests:
	$ make
	$ make runTest
