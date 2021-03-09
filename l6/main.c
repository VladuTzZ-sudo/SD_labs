#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int compareInt(int data1, int data2)
{
	return (data1 - data2);
}

void printInt(int data)
{
	printf("%d", data);
}

int main()
{
	Tree *tree = createTree(compareInt, printInt);
	insert(tree, tree->root, 3);
	insert(tree, tree->root, 1);
	insert(tree, tree->root, 0);
	insert(tree, tree->root, 2);
	insert(tree, tree->root, 5);
	insert(tree, tree->root, 4);
	insert(tree, tree->root, 6);


	
	printInorder(tree, tree->root);
	printf("== 0 1 2 3 4 5 6\n");
	printf("%d == 0\n", search(tree, tree->root, 1)->lt->data);
	printf("%d == 1\n", search(tree, tree->root, 1)->data);
	printf("%d == 2\n", search(tree, tree->root, 1)->rt->data);
	printf("%d == 0\n", search(tree, search(tree, tree->root, 1), 1)->lt->data);
	printf("%d == 1\n", search(tree, search(tree, tree->root, 1), 1)->data);
	printf("%d == 2\n", search(tree, search(tree, tree->root, 1), 1)->rt->data);

	printf("%d == 0\n", minimum(tree, tree->root));
	printf("%d == 2\n", maximum(tree, tree->root->lt));

	printf("%d == 7\n", size(tree,tree->root));
	printf("%d == 2\n", height(tree, tree->root));
	delete(tree, tree->root, 5);
	printInorder(tree, tree->root);
	printf("== 0 1 2 3 4 6\n");
	printf("%d == 6\n", size(tree, tree->root));
	printf("%d == 1\n", height(tree, tree->root->rt));
	destroyTree(tree, tree->root);
	return 0;
}
