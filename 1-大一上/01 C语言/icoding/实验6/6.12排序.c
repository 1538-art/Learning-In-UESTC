/*
函数原型：void bubble_sort(GoodsList *L)

L为指向链表头结点的指针，该函数利用冒泡排序算法，按价格从低到高对商品进行排序。
*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

void bubble_sort(GoodsList *L) // 12排序
{
  if (CurrentCnt == 1 || !CurrentCnt)
    return;

  for (int j = 1; j < CurrentCnt; j++)
    for (GoodsList *i = L; i->next->next != NULL; i = i->next) {
      GoodsList *a = i->next, *b = i->next->next;
      if (a->data.goods_price > b->data.goods_price) {
        GoodsList *tem = b->next;
        i->next = b;
        b->next = a;
        a->next = tem;
      }
    }
}