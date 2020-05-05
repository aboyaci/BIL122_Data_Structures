#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

/* in order traversal */
int LDR(struct node* n)
{
	if(n == NULL)
		return 0;

	LDR(n->left);
	printf("%d\n", n->data);
	LDR(n->right);

	return 1;
}

/* pre order traversal */
int DLR(struct node* n)
{
	if(n == NULL)
		return 0;

	printf("%d\n", n->data);
	DLR(n->left);
	DLR(n->right);

	return 1;
}

/* post order traversal */
int LRD(struct node* n)
{
	if(n == NULL)
		return 0;

	LRD(n->left);
	LRD(n->right);
	printf("%d\n", n->data);

	return 1;
}

/*
	Allocate and initialize node
*/
struct node* allocate_node()
{
	struct node* n = calloc(1, sizeof(struct node));
	return n;
}

/*
	Insert new data to tree recursively
*/
struct node* insert(struct node* root, int data)
{
	if (!root)
	{
		struct node* n = allocate_node();
		n->data = data;
		return n;
	}

	if (root->data > data)
	{
		root->left = insert(root->left, data);	
	}
	else{
		root->right = insert(root->right, data);
	}

	return balance(root);
}

/*
	Balance the tree
*/
struct node* balance(struct node* n)
{
	int d = diff(n);

	if (d > 1)
	{
		if (diff(n->left) > 0)
		{
			n = ll_rotation(n);
		}
		else
		{
			n = lr_rotation(n);
		}
	}
	else if(d < -1)
	{
		if (diff(n->right) > 0)
		{
			n = rl_rotation(n);
		}
		else
		{
			n = rr_rotation(n);
		}
	}

	return n;
}

/*
	Right right rotation
 */
struct node* rr_rotation(struct node* parent)
{
	struct node* n;
	n = parent->right;
	parent->right = n->left;
	n->left = parent;
	return n;
}
/*
	Left left rotation
 */
struct node* ll_rotation(struct node* parent)
{
	struct node* n;
	n = parent->left;
	parent->left = n->right;
	n->right = parent;
	return n;
}

/*
	Left right rotation
*/
struct node* lr_rotation(struct node* parent)
{
	struct node* n;
	n = parent->left;
	parent->left = rr_rotation (n);
	return ll_rotation (parent);
}

/*
	Rigth left rotaiton
*/
struct node* rl_rotation(struct node* parent)
{
	struct node* n;
	n = parent->right;
	parent->right = ll_rotation (n);
	return rr_rotation (parent);
}

/*
	Find the hight difference between simblings
*/
int diff(struct node* n)
{
	int l = height(n->left);
	int r = height(n->right);

	return l-r;
}

/*
	Calculate the height of the tree
*/
int height(struct node* n)
{
	if (!n) return 0; // NULL Case

	int l = height(n->left);
	int r = height(n->right);

	return l>r ? l+1 : r+1; // pick max
}

int main(int argc, char const *argv[])
{
	struct node* root;

	printf("Inserting 1\n");
	root = insert(root, 1);
	printf("height is %d after insert\n\n", height(root));

	printf("Inserting 2\n");
	root = insert(root, 2);
	printf("height is %d after insert\n\n", height(root));

	printf("Inserting 3\n");
	root = insert(root, 3);
	printf("height is %d after insert\n\n", height(root));

	printf("Inserting 4\n");
	root = insert(root, 4);
	printf("height is %d after insert\n\n", height(root));

	printf("Inserting 5\n");
	root = insert(root, 5);
	printf("height is %d after insert\n\n", height(root));

	printf("Inserting 6\n");
	root = insert(root, 6);
	printf("height is %d after insert\n\n", height(root));

	printf("Inserting 7\n");
	root = insert(root, 7);
	printf("height is %d after insert\n\n", height(root));

	printf("data so far in order: \n");
	LDR(root);

	return 0;
}