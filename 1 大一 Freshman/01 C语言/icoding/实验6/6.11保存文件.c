/*
函数原型：int save_to_file(GoodsList *L)

将当前链表所有的商品信息保存到文件 goodsinfo.txt
中，其中L为指向链表头结点的指针，保存成功后，该函数返回商品的数量。
*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

int save_to_file(GoodsList *L) {
  int number = 0;
  if (L == NULL)
    return 0;
  GoodsList *p = L->next;
  FILE *fp;
  if ((fp = fopen("goodsinfo.txt", "w")) == NULL)
    return 0;
  while (p != NULL) {
    fprintf(fp, "%s\t", p->data.goods_id);
    fprintf(fp, "%s\t", p->data.goods_name);
    fprintf(fp, "%d\t", p->data.goods_price);
    fprintf(fp, "%s\t", p->data.goods_discount);
    fprintf(fp, "%d\t", p->data.goods_amount);
    fprintf(fp, "%d\n", p->data.goods_remain);
    p = p->next;
    number++;
  }

  fclose(fp);
  return number;
}