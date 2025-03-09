#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _minHeapNode
{
    int value;
    int index;
    int arrayIndex;
} MinHeapNode, *PMinHeapNode;

typedef struct _minPQ
{
    PMinHeapNode heap_array; // 指向堆元素数组
    int heap_size;           // 当前堆中的元素个数
    int capacity;            // 堆数组的大小
} MinHeap, *PMinHeap;

int parent(int i)
{
    return (i - 1) / 2;
}
int left(int i)
{
    return 2 * i + 1;
}
int right(int i)
{
    return 2 * i + 2;
}
void swap_node(MinHeapNode *x, MinHeapNode *y)
{
    x->value ^= y->value;
    y->value ^= x->value;
    x->value ^= y->value;
    x->index ^= y->index;
    y->index ^= x->index;
    x->index ^= y->index;
    x->arrayIndex ^= y->arrayIndex;
    y->arrayIndex ^= x->arrayIndex;
    x->arrayIndex ^= y->arrayIndex;
}

bool heap_insert_value(PMinHeap pq, const int *arr, int index, int arrayIndex, int k)
{
    if (pq->heap_size >= pq->capacity)
        return false;
    pq->heap_array[pq->heap_size].value = arr[arrayIndex * k + index];
    pq->heap_array[pq->heap_size].index = index;
    pq->heap_array[pq->heap_size].arrayIndex = arrayIndex;
    int curNodeIndex = pq->heap_size;
    while (pq->heap_array[curNodeIndex].value < pq->heap_array[parent(curNodeIndex)].value)
    {
        swap_node(&pq->heap_array[curNodeIndex], &pq->heap_array[parent(curNodeIndex)]);
        curNodeIndex = parent(curNodeIndex);
    }
    pq->heap_size++;
    return true;
}

void heap_build(PMinHeap pq, const int *arr, int n, int k)
{
    pq->heap_size = 0;
    pq->capacity = n;
    pq->heap_array = (PMinHeapNode)malloc(n * sizeof(MinHeapNode));
    for (int i = 0; i < n; i++)
    {
        heap_insert_value(pq, arr, 0, i, k);
    }
}

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

void merge_arrays(const int *arr, int n, int k, int *output)
{
    PMinHeap heap = (PMinHeap)malloc(sizeof(MinHeap));
    heap_build(heap, arr, n, k);
    int i = 0;
    while (heap->heap_size > 0)
    {
        output[i++] = heap->heap_array[0].value;
        int nextIndex = heap->heap_array[0].index + 1;
        int arrayIndex = heap->heap_array[0].arrayIndex;
        heap->heap_array[0].value = 0x3f3f3f3f;
        swap_node(&heap->heap_array[0], &heap->heap_array[heap->heap_size - 1]);
        heap->heap_size--;
        min_heapify(heap, 0);
        if (nextIndex < k)
        {
            heap_insert_value(heap, arr, nextIndex, arrayIndex, k);
        }
    }
}