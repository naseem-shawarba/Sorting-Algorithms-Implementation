#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"

// Function to initialize a linked list
void init_list(list *mylist)
{
	mylist->first = NULL;
	mylist->last = NULL;
}

// Function to insert an element into a linked list
void insert_list(list_element *element, list *mylist)
{
	if (mylist->first == NULL)
	{
		mylist->first = element;
		mylist->last = element;
		mylist->last->next = NULL;
	}
	else
	{
		mylist->last->next = element;
		mylist->last = element;
		mylist->last->next = NULL;
	}
}

// Function to free the memory allocated for a linked list
void free_list(list *mylist)
{
	list_element *prev = NULL;
	list_element *current = mylist->first;

	while (current)
	{
		prev = current;
		current = current->next;
		free(prev->password);
		free(prev);
	}
}

// Function to count words in a string
int words(const char *string)
{
	int counter = 0;
	int len = strlen(string);
	char lastC;

	if (len > 0)
	{
		lastC = string[0];
	}

	for (int i = 0; i <= len; i++)
	{
		if ((string[i] == ' ' || string[i] == '\0') && lastC != ' ')
		{
			counter++;
		}
		lastC = string[i];
	}
	return counter;
}

// Function to read data from a file into a linked list
void read_data(char *filename, list *mylist)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("Error");
		return;
	}

	char buffer[100];
	char pw[100];
	char *strbuffer;
	char pwcountbuffer[100];
	int pwcount;
	int pwwords;
	memset(pw, 0, sizeof(pw));

	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		pwwords = words(buffer) - 1;
		strbuffer = strtok(buffer, " ");
		for (int i = 0; i < pwwords; i++)
		{
			strcat(pw, strbuffer);
			if (pwwords > 1 && i != pwwords - 1)
			{
				strcat(pw, " ");
			}
			strbuffer = strtok(NULL, " ");
		}
		strcpy(pwcountbuffer, strbuffer);
		pwcount = atoi(pwcountbuffer);

		list_element *newle = (list_element *)malloc(sizeof(list_element));
		if (newle == NULL)
		{
			perror("Overflow!");
			return;
		}

		newle->password = strdup(pw);
		newle->count = pwcount;
		insert_list(newle, mylist);
		memset(pw, 0, sizeof(pw));
	}
	fclose(fp);
}

// Function to partition a linked list around a pivot element
list_element *partition(list *input, list *left, list *right)
{
	list_element *pivot;

	if (input->first == NULL)
	{
		pivot = NULL;
		input->last = NULL;
	}
	else
	{
		pivot = input->first;
		input->first = pivot->next;
		pivot->next = NULL;
	}

	if (pivot != NULL)
	{
		list_element *temp = input->first;
		while (temp != NULL)
		{
			input->first = temp->next;
			if (input->first == NULL)
			{
				input->last = NULL;
			}
			if (temp->count >= pivot->count)
			{
				insert_list(temp, right);
			}
			else
			{
				insert_list(temp, left);
			}
			temp = input->first;
		}
	}
	return pivot;
}

// Function to perform quicksort on a linked list
void qsort_list(list *mylist)
{
	if (mylist->first == mylist->last)
	{
		return;
	}
	else
	{
		list lstack;
		list rstack;
		list *left = &lstack;
		list *right = &rstack;
		init_list(left);
		init_list(right);

		list_element *pivot = partition(mylist, left, right);
		qsort_list(left);
		qsort_list(right);

		if (left->first == NULL)
		{
			mylist->first = pivot;
		}
		else
		{
			mylist->first = left->first;
			left->last->next = pivot;
		}

		if (right->first == NULL)
		{
			pivot->next = NULL;
			mylist->last = pivot;
		}
		else
		{
			pivot->next = right->first;
			mylist->last = right->last;
		}
	}
}

// Function to print a linked list
void print_list(list *mylist)
{
	if (mylist->first == NULL)
	{
		printf("List is empty!\n\n");
		return;
	}

	list_element *temp = mylist->first;

	while (temp)
	{
		printf("%s %d\n", temp->password, temp->count);
		temp = temp->next;
	}
}
