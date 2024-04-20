#include <stdio.h>
#include "quicksort.h"

int main(int argc, char **args)
{
	if (argc != 2)
	{
		printf("Usage: %s <Filename>\n", args[0]);
		return 1;
	}

	list mylist;
	init_list(&mylist);
	read_data(args[1], &mylist);
	qsort_list(&mylist);

	printf("Sorted List:\n");
	print_list(&mylist);

	free_list(&mylist);
	return 0;
}
