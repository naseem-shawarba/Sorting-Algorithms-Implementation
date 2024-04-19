#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "input_merge_sort.h"

// Function to merge two sorted subarrays into one sorted array
void merge(int *array, int first, int middle, int last)
{
	// Allocate memory for the merged array
	int *mergedArray = (int *)malloc((last - first + 2) * sizeof(int));
	// Check if memory allocation was successful
	assert(mergedArray != NULL);

	// Initialize variables for indices
	int k = first;
	int m = middle + 1;
	int i = 0;

	// Merge the two subarrays into the merged array
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

	// Copy any remaining elements from the first subarray
	while (k <= middle)
	{
		mergedArray[i++] = array[k++];
	}

	// Copy any remaining elements from the second subarray
	while (m <= last)
	{
		mergedArray[i++] = array[m++];
	}

	// Copy the merged array back to the original array
	for (int j = 0; j < i; j++)
	{
		array[first + j] = mergedArray[j];
	}

	// Free the memory allocated for the merged array
	free(mergedArray);
}

// Function to perform merge sort on an array
void merge_sort(int *array, int first, int last)
{
	// Initialize the step size
	int step = 1;
	int left, middle, right;

	// Iterate until the step size exceeds the size of the array
	while (step <= last)
	{
		left = 0;
		// Merge subarrays of size 'step'
		while (left <= last - step)
		{
			middle = left + step - 1;
			middle = (middle < last) ? middle : last;
			right = left + 2 * step - 1;
			right = (right < last) ? right : last;
			merge(array, left, middle, right);
			left = left + 2 * step;
		}
		// Double the step size for the next iteration
		step = step * 2;
	}
}

// Main function
int main(int argc, char *argv[])
{
	// Check if correct number of command-line arguments is provided
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <maximum number> <file path>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Extract command-line arguments
	char *filename = argv[2];
	int size = atoi(argv[1]);

	// Allocate memory for the array
	int *array = (int *)malloc(size * sizeof(int));
	// Check if memory allocation was successful
	assert(array != NULL);

	// Read integers from the file into the array
	int len = read_array_from_file(array, size, filename);

	// Print the input array
	printf("Input:\n");
	print_array(array, len);

	// Perform merge sort on the array
	merge_sort(array, 0, len - 1);

	// Print the sorted array
	printf("Sorted:\n");
	print_array(array, len);

	// Free the memory allocated for the array
	free(array);
	return EXIT_SUCCESS;
}
