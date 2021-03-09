 return 1 + height(tree,root->lt);
        }

Tree *createTree(int (*compare)(int data1, int data2), void (*print)(int data))
{
	Tree *tree = malloc(sizeof(Tree));

	if (tree == NULL)
		goto err;
	tree->compare = compare;
	tree->print = print;
	tree->root = NULL;
	return tree;
err:
	return NULL;
}

TreeNode *createTreeNode(int data)
{
	TreeNode *root = malloc(sizeof(TreeNode));
	if (root == NULL)
		goto err;
	root->data = data;
	root->lt = NULL;
	root->rt = NULL;
	return root;
err:
	return NULL;
}

void destroyTreeNode(TreeNode *root)
{
	free(root);
}

void destroyTree(Tree *tree, TreeNode *root)
{
	if (root == NULL)
		return;
	destroyTree(tree, root->lt);
	destroyTree(tree, root->rt);
	destroyTreeNode(root);
	if (tree->root == root)
		free(tree);
}

TreeNode *insert(Tree *tree, TreeNode *root, int data)
{
	if (root == NULL) {
		root = createTreeNode(data);
		if (tree->root == NULL)
			tree->root = root;
		return root;
	}
	if (tree->compare(root->data, data) == 0)
		return root;
	if (tree->compare(root->data, data) > 0)
		root->lt = insert(tree, root->lt, data);
	else
		root->rt = insert(tree, root->rt, data);
	return root;
}

TreeNode *delete(Tree *tree, TreeNode *root, int data)
{
	TreeNode *node;

	node = (TreeNode *)malloc(sizeof(TreeNode));
	node = search(tree, root, data);
	
	TreeNode *node2;
	
	node2 = (TreeNode *)malloc(sizeof(TreeNode));
	node2 = root;

	if ( node != NULL ){
		while ( node2->lt != node && node2->rt != node ){
			if (tree->compare(node2->data, data) > 0){
                		node2=node2->lt;
			}
			else{
				node2=node2->rt;
			}
		}
	}
	else {
		return NULL;
	}

	if (node->lt == NULL && node->rt == NULL){
		if (node2->lt == node){
			node2->lt=NULL;
		}
		if (node2->rt == node){
			node2->rt=NULL;
		}
		destroyTreeNode(node);
		return NULL; 
	}

	if (node->lt == NULL || node->rt == NULL){
		if (node->lt == NULL){
			if (node2->lt == node){
				node2->lt=node->rt;
			}
			else{
				node2->rt=node->rt;
			}
		}
		else{
			if (node2->lt == node){
				node2->lt=node->lt;
			}
			else{
				node2->rt=node->lt;
			}
		}
		destroyTreeNode(node);
		return NULL;
	}

	TreeNode *min,*tata;

	min = (TreeNode *)malloc(sizeof(TreeNode));
	tata = (TreeNode *)malloc(sizeof(TreeNode));

	int minim;
	minim = minimum(tree,node->rt);
	min = search(tree, node->rt, minim);

	tata = root;
	while (tata->lt != min && tata->rt != min){
                if (tree->compare(tata->data, minim) > 0){
                        tata=tata->lt;
                }
                else{
                        tata=tata->rt;
                }
        }

	if (node2->lt == node)
		node2->lt = min;
	else
		node2->rt = min;

	if (min->rt != NULL)
		tata->lt=min->rt;

	min->lt = node->lt;
	if ( node->rt != min )
		min->rt = node->rt;
	else
		min->rt = NULL;
	return root;
}

TreeNode *search(Tree *tree, TreeNode *root, int data)
{
	if (root == NULL)
		return NULL;
	if (tree->compare(root->data, data) == 0)
                return root;
        if (tree->compare(root->data, data) > 0)
		return search(tree, root->lt, data);
	return search(tree, root->rt, data);
}

#define inf 10000

int minimum(Tree *tree, TreeNode *root)
{
	if (root == NULL)
		return -inf;
	if (root->lt == NULL)
		return root->data;
	return minimum(tree, root->lt);
}

int maximum(Tree *tree, TreeNode *root)
{
	if (root == NULL)
		return inf;
	if (root->rt == NULL)
		return root->data;
	return maximum(tree, root->rt);
}

int size(Tree *tree, TreeNode *root)
{
	if (root == NULL)
		return 0;
	return 1 + size(tree, root->lt) + size(tree, root->rt);
}

int height(Tree *tree, TreeNode *root)
{
	if (root == NULL){
		return -1;
	}
	if (height(tree,root->lt) >= height(tree,root->rt)){
		return 1 + height(tree,root->lt);
	}
	else{
		return 1 + height(tree,root->rt);
	}
}

void printPreorder(Tree *tree, TreeNode *root)
{
	if (root == NULL)
		return;
	tree->print(root->data);
	printf(" ");
	printPreorder(tree, root->lt);
	printPreorder(tree, root->rt);
}

void printInorder(Tree *tree, TreeNode *root)
{
	if (root == NULL)
		return;
	printInorder(tree, root->lt);
	tree->print(root->data);
	printf(" ");
	printInorder(tree, root->rt);
}

void printPostorder(Tree *tree, TreeNode *root)
{
	if (root == NULL)
		return;
	printPostorder(tree, root->lt);
	printPostorder(tree, root->rt);
	tree->print(root->data);
	printf(" ");
}
