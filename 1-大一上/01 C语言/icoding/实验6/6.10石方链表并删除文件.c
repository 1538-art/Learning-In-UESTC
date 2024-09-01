/*
函数原型：void destory_list_and_file(GoodsList **L)，

该函数调用destory_list释放包括头结点在内的所有结点，将指向链表头结点的指针为NULL，最后删除存储商品信息的文件goodinfo.txt。
*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

void destory_list_and_file(GoodsList **L) {
  destory_list(L);
  *L = NULL;
  L = NULL;
  remove("GoodsInfo.txt");
}