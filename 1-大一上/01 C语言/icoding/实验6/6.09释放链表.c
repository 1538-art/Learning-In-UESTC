/*
函数原型：void destory_list(GoodsList **L)，

该函数释放包括头结点在内的所有结点，完成后指向链表头结点的指针为NULL。
*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

void destory_list(GoodsList **L) {
  GoodsList *prev = *L;
  GoodsList *cur = prev->next;
  while (prev != NULL) {
    cur = prev->next;
    free(prev);
    prev = cur;
  }
  *L = NULL;
  CurrentCnt = 0;
  L = NULL;
}