/*
有链表类型定义如下：

typedef struct node { //链表结点类型定义
    int data;
    struct node *next;
} node;

typedef struct { //采用头结点模式的链表类型定义
    node head;  //头结点
    int length; //链表长度（即结点数量）
} mlist;
请采用排序算法（如冒泡排序）对链表进行升序排序，即完成 void list_sort(mlist *L)
函数的编码， 其中 L 为指向链表变量的指针。

提示： 1. 当链表没有或者只有1个节点，无须排序

2. 对于数据 23 65 98 15 49 22 31 70 68 84， 排序后其结果为：15 22 23 31 49 65 68
70 84 98

//已经提供代码
#include <stdio.h>
#include <stdlib.h>

typedef struct node { //链表结点类型定义
    int data;
    struct node *next;
} node;

typedef struct { //采用头结点模式的链表类型定义
    node head;  //头结点
    int length; //链表长度（即结点数量）
} mlist;

void list_sort(mlist *L){


}

*/