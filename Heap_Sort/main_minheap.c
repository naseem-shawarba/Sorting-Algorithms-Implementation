#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "input_heap_sort.h"
#include "heap.h"

#define MAX_HEAP_SIZE 400
#define MAX_LINE_SIZE 100

int main(int argc, char **argv)
{
    heap *waiting_list = heap_create(MAX_HEAP_SIZE);

    // Check if the correct number of command-line arguments is provided
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Extract the command-line argument
    char *filename = argv[1];

    // Allocate memory for the array
    int *array = (int *)malloc(MAX_HEAP_SIZE * sizeof(int));
    // Check if memory allocation was successful
    assert(array != NULL);

    // Read integers from the file into the array
    int len = read_array_from_file(array, MAX_HEAP_SIZE, filename);

    // Print the unsorted array
    printf("Unsorted:");
    print_array(array, len);

    // Add elements to the heap
    for (int i = 0; i < len; i++)
    {
        // Insert each element into the heap
        if (heap_insert(waiting_list, array[i]) == -1)
        {
            printf("Error: Heap is full, input not saved\n");
        }
    }

    // Extract elements from the heap in sorted order and print them
    int number = heap_extract_min(waiting_list);
    printf("Sorted: ");
    while (number >= 0)
    {
        printf("%i ", number);
        number = heap_extract_min(waiting_list);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(array);
    heap_free(waiting_list);
}
