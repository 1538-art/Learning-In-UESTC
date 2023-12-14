/*
函数原型：bool delete_item(GoodsList *L, char* goods_id)

其中L为指向链表头结点的指针，goods_id为要删除商品的ID；

如果成功删除，函数返回true，否则返回false。

delete_item
根据商品的ID来删除对应的商品信息，商品查找通过字符串比较的方式，
查找到后释放对应指针指向的内存区域，完成删除。*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

bool delete_item(GoodsList *L, char *goods_id) // 4删除
{
  for (GoodsList *i = L; i->next != NULL; i = i->next) {
    GoodsList *n = i->next;
    if (!strcmp(n->data.goods_id, goods_id)) {
      i->next = n->next;
      free(n);
      n = NULL;
      CurrentCnt--;
      return 1;
    }
  }

  return 0;
}