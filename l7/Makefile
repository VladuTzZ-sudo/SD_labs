CC = gcc
CFLAGS = -Wall -c -g

.PHONY: build
build: lab7-trie

lab7-trie: main.o trie.o 
	gcc main.o trie.o -o lab7-trie

trie.o: trie.c trie.h

main.o: main.c trie.h 

.PHONY: run
run:
	./lab7-trie

.PHONY: memcheck
memcheck:
	valgrind ./lab7-trie

.PHONY: clean
make clean:
	rm -f *.o lab7-trie

