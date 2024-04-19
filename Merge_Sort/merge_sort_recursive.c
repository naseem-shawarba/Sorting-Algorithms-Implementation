#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "input_merge_sort.h"

// Function to merge two sorted subarrays into one sorted array
void merge(int *array, int first, int middle, int last)
{
	// Allocate memory for the merged array
	int *mergedArray = (int *)malloc((last - first + 2) * sizeof(int));
	// Ensure memory allocation was successful
	assert(mergedArray != NULL);

	// Initialize indices for the subarrays and the merged array
	int k = first;
	int m = middle + 1;
	int i = 0;

	// Merge the two sorted subarrays into the merged array
	while (k <= middle && m <= last)
	{
		if (array[k] <= array[m])
		{
			mergedArray[i++] = array[k++];
		}
		else
		{
			mergedArray[i++] = array[m++];
		}
	}

	// Copy remaining elements from the first subarray to the merged array
	while (k <= middle)
	{
		mergedArray[i++] = array[k++];
	}

	// Copy remaining elements from the second subarray to the merged array
	while (m <= last)
	{
		mergedArray[i++] = array[m++];
	}

	// Copy the merged array back to the original array
	for (int j = 0; j < i; j++)
	{
		array[first + j] = mergedArray[j];
	}

	// Free the dynamically allocated memory
	free(mergedArray);
}

// Function to perform merge sort on an array
void merge_sort(int *array, int first, int last)
{
	// Check if there are more than one element in the array
	if (first < last)
	{
		// Calculate the middle index
		int middle = (first + last) / 2;

		// Recursively sort the left and right subarrays
		merge_sort(array, first, middle);
		merge_sort(array, middle + 1, last);

		// Merge the sorted subarrays
		merge(array, first, middle, last);
	}
}

// Main function
int main(int argc, char *argv[])
{
	// Check if the correct number of command-line arguments is provided
	if (argc != 3)
	{
		// Print usage instructions if arguments are incorrect
		fprintf(stderr, "Usage: %s <maximum number> <file path>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Extract command-line arguments
	char *filename = argv[2];
	int size = atoi(argv[1]);

	// Allocate memory for the array
	int *array = (int *)malloc(size * sizeof(int));
	// Ensure memory allocation was successful
	assert(array != NULL);

	// Read integers from the file into the array
	int len = read_array_from_file(array, size, filename);

	// Print the input array
	printf("Input:\n");
	print_array(array, len);

	// Sort the array using merge sort
	merge_sort(array, 0, len - 1);

	// Print the sorted array
	printf("Sorted:\n");
	print_array(array, len);

	// Free the dynamically allocated memory
	free(array);

	return EXIT_SUCCESS;
}
