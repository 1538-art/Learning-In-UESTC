/*
 * 顺序表 删除指定范围

设计一个高效的算法，从顺序表L中删除所有值介于x和y之间(包括x和y)的所有元素（假设y>=x），要求时间复杂度为O(n)，空间复杂度为O(1)。

函数原型如下：
void del_x2y(SeqList *L, ElemType x, ElemType y);

相关定义如下：
struct _seqlist{
    ElemType elem[MAXSIZE];
    int last;
};
typedef struct _seqlist SeqList;
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

void del_x2y(SeqList *L, ElemType x, ElemType y) {
  int prev = -1;  // 前指针
  int curr = 0;  // 当前指针
  
  while (curr <= L->last) {
    if (L->elem[curr] >= x && L->elem[curr] <= y) {
      curr++;  // 删除介于x和y之间的元素
    } else {
      prev++;
      L->elem[prev] = L->elem[curr];
      curr++;
    }
  }
  
  L->last = prev;  // 更新顺序表长度
}
