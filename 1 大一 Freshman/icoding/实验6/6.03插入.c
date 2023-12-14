/*函数原型：bool insert_item(GoodsList *L, GoodsInfo goodsInfo, int choice)，

L为指向链表头结点的指针，函数根据choise的值，将goodsInfo插入到链表的指定位置，
如果成功插入，函数返回true，如果未插入，函数返回false。

分别实现头插法、尾插法，中间位置插入三种:
用户输入0，将商品信息插入到链表尾部；
用户输入1，将商品信息插入到链表头部；
用户输入其它正整数i，将商品信息插入到链表中间第i号位置,
例如：输入3，应该在第二个节点后插入新节点
 */
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

bool insert_item(GoodsList *L, GoodsInfo item, int choice) // 3插入
{
  if (choice == 0) {
    GoodsList *i = L;
    for (; i->next != NULL; i = i->next)
      ;
    GoodsList *n;
    n = (GoodsList *)malloc(sizeof(GoodsList));
    n->data = item;
    n->next = NULL;
    i->next = n;
    CurrentCnt++;

    //		output_all_items(L);
    return 1;
  }

  if (choice == 1) {
    GoodsList *i = L;
    GoodsList *n;
    n = (GoodsList *)malloc(sizeof(GoodsList));
    n->data = item;
    n->next = NULL;
    GoodsList *tem = i->next;
    i->next = n;
    n->next = tem;
    CurrentCnt++;

    //		output_all_items(L);
    return 1;
  }

  if (choice < 0 || choice > CurrentCnt + 1)
    return 0;

  GoodsList *i = L;
  for (int j = 1; j <= choice - 1; i = i->next, j++)
    ;
  GoodsList *n;
  n = (GoodsList *)malloc(sizeof(GoodsList));
  n->data = item;
  n->next = NULL;
  GoodsList *tem = i->next;
  i->next = n;
  n->next = tem;
  CurrentCnt++;

  //	output_all_items(L);
  return 1;
}