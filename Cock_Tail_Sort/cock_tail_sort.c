#include <stdio.h>

void swapElements(int arr[], int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void cocktailSort(int arr[], int n)
{
    int swapped = 1;
    int start = 0;
    int end = n - 1;

    while (swapped)
    {
        // Reset the swapped flag
        swapped = 0;

        // Move from left to right, similar to bubble sort
        for (int i = start; i < end; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                // Swap if the current element is greater than the next one
                swapElements(arr, i, i + 1);
                swapped = 1;
            }
        }

        // If no swaps occurred, the array is sorted
        if (!swapped)
            break;

        // Move the end point one position to the left
        --end;

        // Move from right to left, similar to bubble sort in reverse
        for (int i = end - 1; i >= start; --i)
        {
            if (arr[i] > arr[i + 1])
            {
                // Swap if the current element is greater than the next one
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }

        // Move the start point one position to the right
        ++start;
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {11, 2, 8, 95, 6, 1, 98, 14, 1000, 1, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    cocktailSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
