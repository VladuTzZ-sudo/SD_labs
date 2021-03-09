#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *lt;
	struct node *rt;
} TreeNode;

typedef struct tree {
	int (*compare)(int data1, int data2);
	void (*print)(int data);
	TreeNode *root;
} Tree;

Tree *createTree(int (*compare)(int data1, int data2), void (*print)(int data));

TreeNode *createTreeNode(int data);

void destroyTreeNode(TreeNode *root);

void destroyTree(Tree *tree, TreeNode *root);

TreeNode *insert(Tree *tree, TreeNode *root, int data);

TreeNode *delete(Tree *tree, TreeNode *root, int data);

TreeNode *search(Tree *tree, TreeNode *root, int data);

int minimum(Tree *tree, TreeNode *root);

int maximum(Tree *tree, TreeNode *root);

int size(Tree *tree, TreeNode *root);

int height(Tree *tree, TreeNode *root);

void printPreorder(Tree *tree, TreeNode *root);

void printInorder(Tree *tree, TreeNode *root);

void printPostorder(Tree *tree, TreeNode *root);

#endif // TREE_H_INCLUDED
