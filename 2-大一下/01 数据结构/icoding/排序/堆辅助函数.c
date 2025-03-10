#include <stdio.h>
#include <stdlib.h>
#include "minbinheap.h"

int parent(int i)
{
    return (i - 1) / 2;
} // 返回堆元素数组下标为 i 的结点的父结点下标
int left(int i)
{
    return 2 * i + 1;
} // 返回堆元素数组下标为 i 的结点的左子结点下标
int right(int i)
{
    return 2 * i + 2;
} // 返回堆元素数组下标为 i 的结点的右子结点下标
void swap_node(MinHeapNode *x, MinHeapNode *y)
{
    int temp = x->value;
    x->value = y->value;
    y->value = temp;
    OtherInfo tempInfo = x->otherInfo;
    x->otherInfo = y->otherInfo;
    y->otherInfo = tempInfo;
} // 交换两个堆元素的值