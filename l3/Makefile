CC = gcc
CFLAGS = -Wall -c

.PHONY: build
build: lab3

lab3: main.o list.o
	gcc main.o list.o -o lab3

main.o: main.c list.h

list.o: list.c list.h

.PHONY: run
run:
	./lab3

.PHONY: memcheck
memcheck:
	valgrind ./lab3

.PHONY: clean
make clean:
	rm -f *.o lab3

