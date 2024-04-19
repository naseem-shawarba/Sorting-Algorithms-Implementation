#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "input_merge_sort.h"

// Function to read integers from a file into an array
int read_array_from_file(int array[], size_t size, char *filename)
{
    // Open the file for reading
    FILE *file_pointer = fopen(filename, "r");

    // Check if the file opened successfully
    if (file_pointer == NULL)
    {
        // Print an error message including the filename
        perror(filename);
        // Exit the program with an error code
        exit(1);
    }

    // Initialize a counter for the number of integers read
    int i = 0;

    // Read integers from the file until the array is filled or EOF is reached
    while (i < size)
    {
        // Attempt to read an integer from the file into the array
        int return_fscanf = fscanf(file_pointer, "%d", &array[i]);

        // If EOF is reached, break out of the loop
        if (return_fscanf == EOF)
        {
            break;
        }

        // If fscanf fails to read an integer, print an error message and break out of the loop
        if (return_fscanf != 1)
        {
            printf("File has invalid format. No number found!\n");
            break;
        }
        i++;
    }

    // Close the file
    fclose(file_pointer);

    // Return the number of integers read
    return i;
}

// Function to print the elements of an array
void print_array(int array[], int len)
{
    // Loop through the array and print each element
    for (int i = 0; i < len; i++)
    {
        printf(" %d", array[i]);
    }

    // Print a newline character to move to the next line
    printf("\n");
}
