#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LENGTH = 1000;

void bubble_sort(int array[], int len)
{
    for (int j = 0; j < len - 1; ++j)
    {
        for (int i = 0; i < len - j - 1; ++i)
        {
            if (array[i] > array[i + 1])
            {

                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
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

    bubble_sort(array, len);

    printf("Sorted Array:");
    print_array(array, len);

    return 0;
}
