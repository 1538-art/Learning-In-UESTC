/*
 * 链表 合并

设线性表A=(a1, a2,…,am)，B=(b1, b2,…,bn)，试写一个按下列规则合并A、B为线性表C的算法，使得：
C= (a1, b1,…,am, bm, bm+1, …,bn) 当m≤n时；
或者
C= (a1, b1,…,an, bn, an+1, …,am) 当m>n时。
线性表A、B、C均以单链表作为存储结构，且C表利用A表和B表中的结点空间构成。注意：单链表的长度值m和n均未显式存储。
函数的原型如下：
void lnk_merge(LinkList A, LinkList B, LinkList C)
即将A和B合并为C，其中 C 已经被初始化为空单链表
相关定义如下：

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

void lnk_merge(LinkList A, LinkList B, LinkList C) {
  Node *pa = A->next;  // A链表的头结点
  Node *pb = B->next;  // B链表的头结点
  Node *pc = C;  // C链表的头结点
  
  while (pa != NULL && pb != NULL) {
    // 将A链表的结点插入C链表
    pc->next = pa;
    pa = pa->next;
    pc = pc->next;
    
    // 将B链表的结点插入C链表
    pc->next = pb;
    pb = pb->next;
    pc = pc->next;
  }
  
  // 如果A链表还有剩余结点，将剩余结点插入C链表
  while (pa != NULL) {
    pc->next = pa;
    pa = pa->next;
    pc = pc->next;
  }
  
  // 如果B链表还有剩余结点，将剩余结点插入C链表
  while (pb != NULL) {
    pc->next = pb;
    pb = pb->next;
    pc = pc->next;
  }
}
