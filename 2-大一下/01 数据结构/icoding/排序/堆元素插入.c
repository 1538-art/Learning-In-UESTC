#include <stdio.h>
#include <stdlib.h>
#include "minbinheap.h"

bool heap_insert_value(PMinHeap pq, int value)
{
    if (pq->heap_size >= pq->capacity)
        return false;
    pq->heap_array[pq->heap_size].value = value;
    int curNodeIndex = pq->heap_size;
    while (pq->heap_array[curNodeIndex].value < pq->heap_array[parent(curNodeIndex)].value)
    {
        swap_node(&pq->heap_array[curNodeIndex], &pq->heap_array[parent(curNodeIndex)]);
        curNodeIndex = parent(curNodeIndex);
    }
    pq->heap_size++;
    return true;
}