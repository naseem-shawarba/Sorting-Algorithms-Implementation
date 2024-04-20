#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "avl.h"

// Finds a node with the given value in the AVL tree
AVLNode *find_node(AVLTree *avlt, int value)
{
	AVLNode *temp = avlt->root;
	while (temp != NULL)
	{
		if (value == temp->value)
		{
			return temp; // Return the node if value matches
		}
		else if (value < temp->value)
		{
			temp = temp->left; // Traverse left subtree
		}
		else
		{
			temp = temp->right; // Traverse right subtree
		}
	}
	return NULL; // Return NULL if value is not found in the tree
}

// Function to check the height of a node
int heightcheck(AVLNode *node)
{
	if (node == NULL)
	{
		return 0; // Return 0 if node is NULL
	}
	else
	{
		return node->height; // Return height of the node
	}
}

// Performs in-order traversal of a node in the AVL tree
void AVL_in_order_walk_node(AVLNode *node)
{
	if (node->left != NULL)
	{
		AVL_in_order_walk_node(node->left); // Traverse left subtree
	}
	printf("%d ", node->value); // Print value of current node
	if (node->right != NULL)
	{
		AVL_in_order_walk_node(node->right); // Traverse right subtree
	}
}

// Performs in-order traversal of the AVL tree
void AVL_in_order_walk(AVLTree *avlt)
{
	if (avlt != NULL && avlt->root != NULL)
	{
		AVL_in_order_walk_node(avlt->root); // Start traversal from root
	}
}

// Function to perform a left rotation on the AVL tree
void AVL_rotate_left(AVLTree *avlt, AVLNode *x)
{
	// Get the right child of node x
	AVLNode *y = x->right;

	// Update pointers to perform the rotation
	x->right = y->left;
	if (y->left != NULL)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		avlt->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;

	// Update heights of nodes after rotation
	if (x->left == NULL && x->right == NULL)
	{
		x->height = 1;
	}
	else
	{
		int L, R;
		L = heightcheck(x->left);
		R = heightcheck(x->right);
		if (L > R)
		{
			x->height = L + 1;
		}
		else
		{
			x->height = R + 1;
		}
	}
	if (y->left == NULL && y->right == NULL)
	{
		y->height = 1;
	}
	else
	{
		int L, R;
		L = heightcheck(y->left);
		R = heightcheck(y->right);
		if (L > R)
		{
			y->height = L + 1;
		}
		else
		{
			y->height = R + 1;
		}
	}
}

// Function to perform a right rotation on the AVL tree
void AVL_rotate_right(AVLTree *avlt, AVLNode *y)
{
	// Get the left child of node y
	AVLNode *x = y->left;

	// Update pointers to perform the rotation
	y->left = x->right;
	if (x->right != NULL)
	{
		x->right->parent = y;
	}
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		avlt->root = x;
	}
	else if (y == y->parent->right)
	{
		y->parent->right = x;
	}
	else
	{
		y->parent->left = x;
	}

	x->right = y;
	y->parent = x;

	// Update heights of nodes after rotation
	if (y->left == NULL && y->right == NULL)
	{
		y->height = 1;
	}
	else
	{
		int L, R;
		L = heightcheck(y->left);
		R = heightcheck(y->right);
		if (L > R)
		{
			y->height = L + 1;
		}
		else
		{
			y->height = R + 1;
		}
	}
	if (x->left == NULL && x->right == NULL)
	{
		x->height = 1;
	}
	else
	{
		int L, R;
		L = heightcheck(x->left);
		R = heightcheck(x->right);
		if (L > R)
		{
			x->height = L + 1;
		}
		else
		{
			x->height = R + 1;
		}
	}
}

// Function to balance the AVL tree after insertion or deletion
void AVL_balance(AVLTree *avlt, AVLNode *node)
{
	// Check if the node is NULL (base case for recursion)
	if (node == NULL)
	{
		return;
	}

	// Calculate the heights of the left and right subtrees
	int L, R;
	L = heightcheck(node->left);
	R = heightcheck(node->right);

	// Perform rotations if the balance factor is violated
	if (L > R + 1)
	{
		// Check if a double rotation is needed
		int LL, LR;
		LL = heightcheck(node->left->left);
		LR = heightcheck(node->left->right);
		if (LL < LR)
		{
			AVL_rotate_left(avlt, node->left);
		}
		AVL_rotate_right(avlt, node);
	}
	else if (R > L + 1)
	{
		// Check if a double rotation is needed
		int RR, RL;
		RR = heightcheck(node->right->right);
		RL = heightcheck(node->right->left);
		if (RR < RL)
		{
			AVL_rotate_right(avlt, node->right);
		}
		AVL_rotate_left(avlt, node);
	}
}

// Function to insert a value into the AVL tree
void AVL_insert_value(AVLTree *avlt, int value)
{
	// Check if the value already exists in the tree
	AVLNode *check = find_node(avlt, value);
	if (check != NULL)
	{
		printf("The value already exists!\n");
		return;
	}

	// Create a new node for the value
	AVLNode *newnode = (AVLNode *)malloc(sizeof(AVLNode));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
	newnode->value = value;
	newnode->height = 1;

	// Insert the new node into the tree
	if (avlt->root == NULL)
	{
		avlt->root = newnode;
		avlt->numberOfNodes = avlt->numberOfNodes + 1;
	}
	else
	{
		AVLNode *current = avlt->root;
		AVLNode *prev;
		while (current != NULL)
		{
			prev = current;
			if (current->value < value)
			{
				current = current->right;
			}
			else
			{
				current = current->left;
			}
		}
		if (prev->value < value)
		{
			prev->right = newnode;
			newnode->parent = prev;
			avlt->numberOfNodes = avlt->numberOfNodes + 1;
		}
		else
		{
			prev->left = newnode;
			newnode->parent = prev;
			avlt->numberOfNodes = avlt->numberOfNodes + 1;
		}
	}

	// Rebalance the tree after insertion
	AVLNode *temp = newnode;
	while (temp != NULL)
	{
		AVL_balance(avlt, temp);
		if (temp->parent != NULL)
		{
			// Update the height of the parent node
			if (temp->parent->left == NULL && temp->parent->right == NULL)
			{
				temp->parent->height = 1;
			}
			else
			{
				int L, R;
				L = heightcheck(temp->parent->left);
				R = heightcheck(temp->parent->right);
				if (L > R)
				{
					temp->parent->height = L + 1;
				}
				else
				{
					temp->parent->height = R + 1;
				}
			}
		}
		temp = temp->parent;
	}
}

// Function to recursively remove all nodes in the AVL tree
void AVL_remove_all_nodes(AVLNode *node)
{
	if (node->left != NULL)
	{
		AVL_remove_all_nodes(node->left);
	}
	if (node->right != NULL)
	{
		AVL_remove_all_nodes(node->right);
	}
	free(node);
}

// Function to remove all elements in the AVL tree
void AVL_remove_all_elements(AVLTree *avlt)
{
	if (avlt != NULL)
	{
		AVL_remove_all_nodes(avlt->root);
	}
	else
	{
		free(avlt);
	}
}