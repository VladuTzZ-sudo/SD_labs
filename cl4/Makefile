CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -g -std=c89 -pedantic

.PHONY: build
build: laborator4

laborator4: main.o list.o
	$(CC) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<

list.o: list.c list.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: run
run: build
	./laborator4

.PHONY: clean
clean: build
	rm laborator4 *.o

.PHONY: memcheck
memcheck: build
	valgrind \
	--tool=memcheck \
	--leak-check=full --leak-check-heuristics=all \
	--show-leak-kinds=all \
	--track-origins=yes \
	--error-exitcode=1 ./laborator4

.PHONY: style
style:
	./checkpatch.pl --ignore SPDX_LICENSE_TAG,NEW_TYPEDEFS,CONST_STRUCT,TYPO_SPELLING,MACRO_WITH_FLOW_CONTROL,ARRAY_SIZE,STATIC_CONST_CHAR_ARRAY --no-tree --terse -f *.c *.h

