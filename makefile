CC=gcc
CFLAGS=-std=c99

all: bin/main bin/testMain

bin/main: bin/main.o bin/HashTableAPI.o
	$(CC) -o bin/main bin/main.o bin/HashTableAPI.o

bin/main.o: src/main.c include/HashTableAPI.h
	$(CC) -c $(CFLAGS) src/main.c -o bin/main.o

bin/testMain: bin/testMain.o bin/HashTableAPI.o
	$(CC) -o bin/testMain bin/testMain.o bin/HashTableAPI.o

bin/testMain.o: src/testMain.c include/HashTableAPI.h
	$(CC) -c $(CFLAGS) src/testMain.c -o bin/testMain.o

bin/HashTableAPI.o: src/HashTableAPI.c
	$(CC) -c $(CFLAGS) src/HashTableAPI.c -o bin/HashTableAPI.o

run:
	./bin/main $(file)

runTest:
	./bin/testMain

clean:
	rm bin/*