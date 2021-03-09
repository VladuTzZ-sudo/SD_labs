CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -g -std=c89 -pedantic

EXE = laborator5

.PHONY: build
build: $(EXE)

$(EXE): main.o deque.o queue.o stack.o
	$(CC) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<

deque.o: deque.c deque.h
	$(CC) $(CFLAGS) -o $@ -c $<

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -o $@ -c $<

stack.o: stack.c stack.h
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

