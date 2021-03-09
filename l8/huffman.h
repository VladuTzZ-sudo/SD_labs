#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

#include "heap.h"

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

static const int N = 256;

void computeFreqs(char *text, int size, int freqs[N]);

HuffmanNode *makeTree(int freqs[N], int *size);

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code);

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes);

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes);

#endif
