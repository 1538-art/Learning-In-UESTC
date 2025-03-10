#include <stdio.h>
#include <stdlib.h>
#include "minbinheap.h"

void init_min_heap(PMinHeap pq, int capacity)
{
    pq->heap_size = 0;
    pq->capacity = capacity;
    pq->heap_array = (PMinHeapNode)malloc(capacity * sizeof(MinHeapNode));
}