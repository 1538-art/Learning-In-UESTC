/*题目：

函数原型：void init_list(GoodsList **L)

其中 *L
为指向链表头结点的指针，L为指向链表头结点指针的地址，init_list首先创建链表的头结点，
之后读取goodsinfo.txt(示例文件下载)中的商品信息，并初始化链表，函数执行后，需确保
*L 为指向链表头结点的指针。

init_list
实现商品信息链表的初始化，函数从已有的商品信息文件goodsinfo.txt(示例文件下载)
中读入商品信息，并且分配内存保存至链表中。
为了方便在表头插入和删除结点的操作，经常在表头结点（存储第一个元素的结点）的前面增加一个结点，
称之为头结点或表头附加结点。这样原来的表头指针由指向第一个元素的结点改为指向头结点，
头结点的数据域为空，头结点的指针域指向第一个元素的结点。*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

void init_list(GoodsList **L) {
  FILE *fp;
  GoodsInfo goodsInfo;
  GoodsList *p, *r;

  (*L) = (GoodsList *)malloc(sizeof(GoodsList));
  r = (*L);
  if ((fp = fopen(GOODS_FILE_NAME, "r")) == NULL) {
    if ((fp = fopen(GOODS_FILE_NAME, "w")) == NULL)
      printf("提示：不能创建商品文件\n");
  } else {
    while (!feof(fp)) {
      fscanf(fp, "%s", goodsInfo.goods_id);
      fscanf(fp, "\t%s", goodsInfo.goods_name);
      fscanf(fp, "\t%d", &goodsInfo.goods_price);
      fscanf(fp, "\t%s", goodsInfo.goods_discount);
      fscanf(fp, "\t%d", &goodsInfo.goods_amount);
      fscanf(fp, "\t%d\n", &goodsInfo.goods_remain);
      p = (GoodsList *)malloc(sizeof(GoodsList));
      p->data = goodsInfo;
      r->next = p;
      r = p;
      CurrentCnt++;
    }
  }
  fclose(fp);
  r->next = NULL;
  printf("商品的链表文件已建立，有%d个商品记录\n", CurrentCnt);
}