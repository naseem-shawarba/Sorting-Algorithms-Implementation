#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function to check if the array is sorted
bool isSorted(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        if (arr[i - 1] > arr[i])
        {
            return false;
        }
    }
    return true;
}
void swapElements(int arr[], int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
// Function to shuffle array elements randomly
void shuffle(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int j = i + rand() % (n - i);
        swapElements(arr, i, j);
    }
}

void bogosort(int arr[], int n)
{
    srand(time(NULL)); // Seed for random number generation
    while (!isSorted(arr, n))
    {
        shuffle(arr, n);
    }
}

// Function to print an array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function
int main()
{
    int arr[] = {11, 2, 8, 95, 6, 1, 98, 14, 1000, 1, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    bogosort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
