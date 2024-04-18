#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LENGTH = 1000;

void insertion_sort(int array[], int len)
{
    int j, key;
    for (int i = 1; i < len; i++)
    {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        printf("Example: %s numbers.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int array[MAX_LENGTH];
    int len = read_array_from_file(array, MAX_LENGTH, filename);

    printf("Unsorted Array:");
    print_array(array, len);

    insertion_sort(array, len);

    printf("Sorted Array:");
    print_array(array, len);

    return 0;
}
