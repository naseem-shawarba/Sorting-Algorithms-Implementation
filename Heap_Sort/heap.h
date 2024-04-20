typedef struct heap heap;
struct heap {
    int* elements;
    size_t size;
    size_t capacity;
};

heap* heap_create(size_t capacity);
void heapify(heap* h, size_t i);
int heap_extract_min(heap* h);
int heap_insert(heap* h, int key);
void heap_free(heap* h);
