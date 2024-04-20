#include <stdio.h>
#include "avl.h"

// Function prototypes
FILE* open_input_file(int argc, char** args);
void close_input_file(FILE* file, int argc);
void initialize_avl_tree(AVLTree* avlt);
void process_operations(AVLTree* avlt, FILE* input);

int main(int argc, char** args)
{
    FILE* input = open_input_file(argc, args);
    if (input == NULL)
    {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    AVLTree avlt;
    initialize_avl_tree(&avlt);

    process_operations(&avlt, input);

    AVL_remove_all_elements(&avlt);

    close_input_file(input, argc);

    return 0;
}

// Function to open the input file or use stdin if no filename provided
FILE* open_input_file(int argc, char** args)
{
    if (argc == 1)
    {
        return stdin;
    }
    else if (argc == 2)
    {
        FILE* file = fopen(args[1], "r");
        return file;
    }
    else
    {
        return NULL;
    }
}

// Function to close the input file if opened
void close_input_file(FILE* file, int argc)
{
    if (argc == 2)
    {
        fclose(file);
    }
}

// Function to initialize an empty AVL tree
void initialize_avl_tree(AVLTree* avlt)
{
    avlt->root = NULL;
    avlt->numberOfNodes = 0;
}

// Function to process operations on the AVL tree based on input
void process_operations(AVLTree* avlt, FILE* input)
{
    execute_operations(avlt, input);
}
