/*
 * 链表 倒数查找

已知一个带有表头结点的单链表, 假设链表只给出了头指针L。在不改变链表的前提下，请设计一个尽可能高效的算法，查找链表中倒数第k个位置上的结点（k为正整数）。
函数原型为：int lnk_search(LinkList L, int k, ElemType* p_ele)
若查找成功，函数通过指针参数 p_ele 返回该结点 data 域的值，此时函数返回 1；否则，函数返回 0。相关定义如下：

struct _lnklist{
    ElemType data;
    struct _lnklist *next;
};

typedef struct _lnklist Node;
typedef struct _lnklist *LinkList;
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

int lnk_search(LinkList L, int k, ElemType* p_ele) {
  Node *fast = L;  // 快指针
  Node *slow = L;  // 慢指针
  
  // 将快指针向前移动k个位置
  int i;
  for (i = 0; i < k && fast != NULL; i++) {
    fast = fast->next;
  }
  
  // 链表长度小于k，查找失败
  if (i < k) {
    return 0;
  }
  
  // 同时移动快指针和慢指针，直到快指针到达链表末尾
  while (fast != NULL) {
    fast = fast->next;
    slow = slow->next;
  }
  
  // 将倒数第k个结点的data域的值通过指针参数返回
  *p_ele = slow->data;
  
  return 1;  // 查找成功
}
