#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "heap.h"

heap *heap_create(size_t capacity)
{
    heap *new_heap = (heap *)malloc(sizeof(heap));
    new_heap->elements = (int *)malloc(capacity * sizeof(int));
    new_heap->size = 0;
    new_heap->capacity = capacity;
    return new_heap;
}

void heapify(heap *h, size_t i)
{
    size_t l = (i + 1) * 2 - 1;
    size_t r = (i + 1) * 2;
    size_t smallest, temp;

    if (l < h->size && h->elements[l] < h->elements[i])
    {
        smallest = l;
    }
    else
    {
        smallest = i;
    }
    if (r < h->size && h->elements[r] < h->elements[smallest])
    {
        smallest = r;
    }
    if (smallest != i)
    {
        temp = h->elements[smallest];
        h->elements[smallest] = h->elements[i];
        h->elements[i] = temp;
        heapify(h, smallest);
    }
}

int heap_extract_min(heap *h)
{
    size_t min;
    if (h->size < 1)
    {
        return -1;
    }
    else
    {
        min = h->elements[0];
        h->elements[0] = h->elements[h->size - 1];
        h->size = h->size - 1;
        heapify(h, 0);
        return min;
    }
}

int heap_insert(heap *h, int key)
{
    size_t pc = h->size;
    if (h->size == h->capacity)
    {
        return -1;
    }

    h->size = h->size + 1;

    while (pc != 0 && h->elements[(pc + 1) / 2 - 1] > key)
    {
        h->elements[pc] = h->elements[(pc + 1) / 2 - 1];
        pc = (pc + 1) / 2 - 1;
    }
    h->elements[pc] = key;

    return 0;
}

void heap_free(heap *h)
{
    free(h->elements);
    free(h);
}
