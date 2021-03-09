#include "huffman.h"

void computeFreqs(char *text, int size, int freqs[N]) {
	char i;
	for (i = 0 ; i < size ; i++){
		freqs[text[i]-'a']++;
	}	
}

HuffmanNode *makeTree(int freqs[N], int *size) {
    int i;
	PriorityQueue *h;
	h = makeQueue(256);
	HuffmanNode *arbore;
	arbore = malloc(2*N*sizeof(HuffmanNode));
	for (i = 0 ; i < N ; i++)
	 {
		if (freqs[i] != 0 )
		 {
			ItemType x; 
			x.content = i;
			x.prior = freqs[i];
			insert(h,x);
			arbore[*size].value =i;
			arbore[*size].left= -5;
			arbore[*size].right= -10;
			(*size)++;
		}
	}	

	while (h->size >= 1)
	{
		ItemType x,y;
		x = removeMin(h);
		y = removeMin(h);
		 
		ItemType suma;
		suma.content = 3;
		suma.prior = x.prior + y.prior;
		insert(h,suma);
		arbore[*size].value=suma.content;
		for ( i = 0 ; i < (*size) ; i++ )
		{
			if ( arbore[i].value == x.content )
				arbore[*size].left = i;
			if ( arbore[i].value == y.content )
				arbore[*size].right = i;
		}
		*size++;
	}
	free(h->elem);
	free(h);
	return arbore;
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {
		
}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
	char **codes;
	makeCodes(0, nodes, codes, text);
	return "";
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
	return "";
}
