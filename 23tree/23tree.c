/*
 * A 23Tree implementation
 * 2020 Ali Boyaci
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "23tree.h"

//https://en.wikipedia.org/wiki/2%E2%80%933_tree

/* in order traversal */
int LDR(struct node* n)
{
	if(n == NULL)
		return 0;

	LDR(n->left);
	printf("%d ", n->small_key);
	if (n->type == NODE3)
	{
		LDR(n->middle);
		printf("%d ", n->big_key);
	}
	LDR(n->right);

	return 1;
}

/* pre order traversal */
int DLR(struct node* n)
{
	if(n == NULL)
		return 0;

	printf("%d\n", n->small_key);
	DLR(n->left);
	if (n->type == NODE3)
	{
		printf("%d\n", n->big_key);
		DLR(n->middle);	
	}
	DLR(n->right);

	return 1;
}

/* post order traversal */
int LRD(struct node* n)
{
	if(n == NULL)
		return 0;

	LRD(n->left);
	if (n->type == NODE3)
	{
		LRD(n->middle);	
	}
	LRD(n->right);	
	printf("%d\n", n->small_key);
	if (n->type == NODE3)
	{
		printf("%d\n", n->big_key);	
	}	

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
	Compare data with a node
	return -1 if data is on the left of node
	0 in the middle and node is a 3node
	1 on the right
*/
int compare_key(struct node* n, int key)
{
	if(key < n->small_key)
		return LEFT;
	else if(n->type == NODE3 && key < n->big_key)
		return MIDDLE;
	else
		return RIGHT;
}


/*
	find a leaf for the new data
*/
struct node* find_proper_leaf(struct node* root, int data)
{
	struct node* n = root;

	assert(root != NULL);

	while(n->left != NULL)
	{
		switch(compare_key(n, data))
		{
			case LEFT  : n = n->left; break;
			case MIDDLE: n = n->middle; break;
			case RIGHT : n = n->right; break;
			default: assert(0);
		}
	}

	return n;
}

/*
	Insert new data to tree

	Algorithm:
	if root is null create one and put the value
	Otherwise find the proper leaf (we always add to leaf!!!)
	if leaf if 2node, append the new value
	otherwise split leaf, propagete middle value
	if parent is 2node or null done
	otherwise recursively propagate
*/
struct node* insert(struct node* root, int data)
{
	printf("\n----------------------------\n");
	printf("inserting value %d to tree\n", data);

	struct node* n = root;

	// no node case
	if (!root)
	{
		printf("Root does not exist, create root\n");
		struct node* n = allocate_node();
		n->small_key = data;
		return n;
	}

	// we always insert to leaf nodes!
	printf("find proper node\n");
	n = find_proper_leaf(root, data);


	printf("found a leaf node [%p], type = %d, d1[%d], d2[%d]\n", n, n->type, n->small_key, n->big_key);

	// node with only one element
	if (n->type == NODE2)
	{
		printf("it is NODE2, just put the value and done\n");
		// make sure we have the data in order!
		
		n->big_key = data;
		n->type = NODE3;

		if (n->small_key > n->big_key)//maintain order
		{
			// swap keys
			int tmp = n->small_key;
			n->small_key = n->big_key;
			n->big_key = tmp;
		}
	}
	else // NODE3
	{
		printf("it is NODE3, we need to split!\n");
		root = split(n, root, data);
	}

	return root;
}

/*
	Propagate new node to parent
	new node is always 2node
*/
struct node* propogate(struct node* n, struct node* root, struct node* new_node)
{
	struct node* parent = find_parent(root, n->small_key); // we may need to propagate more!
	struct node* small_simbling = NULL;
	struct node* big_simbling = NULL;
	struct node* new_parent = NULL;

	assert(new_node->type == NODE2);

	if (n->type == NODE2)
	{
		printf("node is 2node, just add\n");
		
		n->type = NODE3; //now it is 3node!
		if (compare_key(n, new_node->small_key) == RIGHT)
		{
			n->big_key  = new_node->small_key;
			n->middle = new_node->left;
			n->right  = new_node->right;
		}
		else
		{
			n->big_key  = n->small_key;
			n->small_key  = new_node->small_key;
			n->left   = new_node->left;
			n->middle = new_node->right;
		}

		free(new_node); // this is not needed

		return root;
	}

	printf("node is 3node do the magic\n");

	new_parent = allocate_node();
	new_parent->left = n;
	new_parent->right = new_node;

	// where are we connecting the new node?
	switch(compare_key(n, new_node->small_key))
	{
		case LEFT  : 
			new_parent->small_key = n->small_key;
			n->left = n->middle;
			break;
		case MIDDLE: 
			new_parent->small_key = new_node->small_key;
			struct node* tmp = n->right;
			n->right = new_node->left;
			new_node->left = new_node->right;
			new_node->right = tmp;
			break;
		case RIGHT : 
			new_parent->small_key = n->big_key;
			n->right = n->middle;
			break;
		default: assert(0);
	}
	
	n->middle = NULL;
	n->type = NODE2;

	if(parent == NULL)
	{
		printf("we need to replace the root key %d\n", new_parent->small_key);
		root = new_parent;
	}
	else
	{
		printf("one more propogation key %d\n", new_parent->small_key);
		root = propogate(parent, root, new_parent);
	}

	return root;
}

/*
	split a NODE3
	Note: current_node is always NODE3 and leaf!
*/
struct node* split(struct node* current_node, struct node* root, int data)
{
	int small_key, big_key, middle_key;
	struct node* left_simbling  = NULL;
	struct node* right_simbling = NULL;
	struct node* new_node = NULL;
	struct node* parent = find_parent(root, current_node->small_key);

	switch(compare_key(current_node, data))
	{
		case LEFT:
			small_key  = data;
			middle_key = current_node->small_key;
			big_key    = current_node->big_key;
			break;
		case MIDDLE:
			small_key  = current_node->small_key;
			middle_key = data;
			big_key    = current_node->big_key;
			break;
		case RIGHT:
			small_key  = current_node->small_key;
			middle_key = current_node->big_key;
			big_key    = data;
	}

	printf("Splitting d1 = %d, d2 = %d, data=%d, middle = %d\n", current_node->small_key, current_node->big_key, data, middle_key);

	// use current node as left simbling
	left_simbling = current_node;
	left_simbling->small_key = small_key;
	left_simbling->type = NODE2;

	// new right simbling
	right_simbling = allocate_node();
	right_simbling->small_key = big_key;

	new_node = allocate_node();
	new_node->small_key = middle_key;
	new_node->left =  left_simbling;
	new_node->right = right_simbling;

	if (parent == NULL) // n is root
	{
		printf("splitting root\n");
		root = new_node;
	}
	else
	{
		printf("propogate to parent %d\n", middle_key);
		root = propogate(parent, root, new_node);	
	}

	return root;
}

/*
	find parent with given data
*/
struct node* find_parent(struct node* root, int data)
{
	struct node* n = root;
	struct node* parent = NULL;

	while(n)
	{
		if(n->small_key == data 
			|| (n->type == NODE3 && n->big_key == data)
		)
			return parent;

		parent = n;

		switch(compare_key(n, data))
		{
			case LEFT  : n = n->left; break;
			case MIDDLE: n = n->middle; break;
			case RIGHT : n = n->right; break;
			default: assert(0);
		}
	}

	return NULL;
}


int main(int argc, char const *argv[])
{

	struct node* root;

	for(int i=0; i<10; i++)
	{
		root = insert(root, i);LDR(root);	
	}

	return EXIT_SUCCESS;
}