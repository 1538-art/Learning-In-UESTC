/*函数原型：GoodsList* search_item(GoodsList *L, char* goods_id)

其中L为指向链表头结点的指针，goods_id为要查找商品的ID；

如果找到该商品，函数返回该商品对应的结点指针，否则返回 NULL.

根据输入的商品 ID 来查找对应的商品信息，商品 ID
的判断用字符串比较的方式来实现，然后调用格式化显示查找到的商品信息.*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

GoodsList *search_item(GoodsList *L, char *n) {

  while (L != NULL && strcmp(L->data.goods_id, n))
    L = L->next;
  return L;
}