// Define _POSIX_C_SOURCE macro to enable certain POSIX features
#define _POSIX_C_SOURCE 200809L

// Include necessary header files
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "avl.h" // Include the header file for AVL tree implementation

#define BUFFER_SIZE 255

// Function to calculate the index of the left child of a node in an array representation of a binary tree
int left(int i)
{
	return 2 * i + 1;
}

// Function to calculate the index of the right child of a node in an array representation of a binary tree
int right(int i)
{
	return 2 * i + 2;
}

// Recursively copy nodes into an array
void fill_array(AVLNode *node, AVLNode **node_array, int current_position)
{
	node_array[current_position] = node; // Store the current node in the array
	if (node->left != NULL)				 // If the left child exists
	{
		fill_array(node->left, node_array, left(current_position)); // Recursively copy the left subtree
	}
	if (node->right != NULL) // If the right child exists
	{
		fill_array(node->right, node_array, right(current_position)); // Recursively copy the right subtree
	}
}

// Find the maximum value in a subtree
int find_max_value(AVLNode *node)
{
	while (node->right != NULL) // Traverse to the rightmost node
	{
		node = node->right;
	}
	return node->value; // Return the value of the rightmost node
}

// Parse input from the given file and perform corresponding operations on the AVL tree
void execute_operations(AVLTree *avlt, FILE *input)
{
	char buffer[BUFFER_SIZE]; // Buffer to store input lines
	if (!input)
	{
		printf("Error: Could not open file.\n");
		return;
	}
	printf("Unsorted: ");							  // Print message indicating unsorted values
	while (fgets(buffer, BUFFER_SIZE, input) != NULL) // Read lines from the input file until end-of-file or abort flag is set
	{
		int value; // Variable to store parsed integer value

		int result = sscanf(buffer, "%d", &value); // Parse integer from the input line
		if (result != 1)						   // If sscanf failed to parse an integer
		{
			printf("Error: Invalid input.\n"); // Print error message
		}
		else
		{
			printf("%d ", value);		   // Print the parsed integer
			AVL_insert_value(avlt, value); // Insert the value into the AVL tree
		}
	}
	printf("\n");			 // Print newline after unsorted values
	printf("Sorted: ");		 // Print message indicating sorted values
	AVL_in_order_walk(avlt); // Perform in-order traversal of the AVL tree (prints sorted values)
	printf("\n");			 // Print newline after sorted values
}
