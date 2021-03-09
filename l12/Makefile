CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -g -std=c99 -pedantic

EXE = laborator12

.PHONY: build
build: $(EXE)

$(EXE): main.o hashtable.o
	$(CC) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<

hashtable.o: hashtable.c hashtable.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: run
run: build
	./$(EXE)

.PHONY: clean
clean: build
	rm $(EXE) *.o

.PHONY: memcheck
memcheck: build
	valgrind \
	--tool=memcheck \
	--leak-check=full --leak-check-heuristics=all \
	--show-leak-kinds=all \
	--track-origins=yes \
	--error-exitcode=1 ./$(EXE)

.PHONY: style
style:
	./checkpatch.pl --ignore SPDX_LICENSE_TAG,NEW_TYPEDEFS,CONST_STRUCT,TYPO_SPELLING,MACRO_WITH_FLOW_CONTROL,ARRAY_SIZE,STATIC_CONST_CHAR_ARRAY --no-tree --terse -f *.c *.h

