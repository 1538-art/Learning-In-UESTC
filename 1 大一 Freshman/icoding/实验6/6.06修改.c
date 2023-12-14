/*函数原型：bool change_item(GoodsList *L, char* goods_id, GoodsInfo new_info)

其中 L 为指向链表头结点的指针，goods_id 为要修改的商品 ID，new_info
为该商品的最新数据。函数成功修改后返回true，否则返回 false。*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

bool change_item(GoodsList *L, char *goods_id, GoodsInfo new_info) {
  GoodsList *p = search_item(L, goods_id);
  if (p != NULL) {
    p->data = new_info;
    return true;
  }
  return false;
}