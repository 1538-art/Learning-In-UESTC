/*
函数原型：void output_all_items(GoodsList *L)，

L为指针链表头结点的指针，output_all_items 调用 output_one_item
函数，将链表中所有的商品信息以格式化的方式打印输出到屏幕上。
*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

void output_all_items(GoodsList *L) {
  while (L->next != NULL) {
    output_one_item(L->next);
    L = L->next;
  }
}