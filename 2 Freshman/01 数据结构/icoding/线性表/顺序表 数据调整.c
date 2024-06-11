/*
 * 顺序表 数据调整

已知顺序表L中的数据元素类型为int。设计算法将其调整为左右两部分，左边的元素（即排在前面的）均为奇数，右边所有元素（即排在后面的）均为偶数，并要求算法的时间复杂度为O(n),空间复杂度为O（1）。

函数原型如下：
void odd_even(SeqList *L);

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

void odd_even(SeqList *L) {
  int i = 0;
  int j = L->last;
  while (1) {
    if (L->elem[i] % 2 != 0) {
      i++;
      if (i == j) {
        break;
      }
    }
    if (L->elem[j] % 2 == 0) {
      j--;
      if (i == j) {
        break;
      }
    }
    if (L->elem[i] % 2 == 0 && L->elem[j] % 2 != 0) {
      int temp = L->elem[i];
      L->elem[i] = L->elem[j];
      L->elem[j] = temp;
    }
  }
}
