#include <stdio.h>
#include <stdlib.h>
#include "minbinheap.h"

void min_heapify(PMinHeap pq, int i)
{
    if (i * 2 + 1 >= pq->heap_size)
        return;
    int minChild = left(i);
    if (pq->heap_array[right(i)].value < pq->heap_array[minChild].value)
        minChild = right(i);
    if (pq->heap_array[minChild].value < pq->heap_array[i].value)
    {
        swap_node(&pq->heap_array[i], &pq->heap_array[minChild]);
    }
    min_heapify(pq, minChild);
}