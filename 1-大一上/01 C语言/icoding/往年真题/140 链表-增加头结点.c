/*
链表结点定义如下：
struct node{
        int value;
        struct node *next;
};
编写函数，通过list传入链表首节点指针，在链表头插入value域为n的新结点，并返回新结点的指针，函数原型如下：
struct node *add_list(struct node *list, int n);
*/
#include <stdlib.h>
// 第一种写法：
struct node {
  int value;
  struct node *next;
};
struct node *add_list(struct node *list, int n) {
  struct node *new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("Error: malloc failed in add_list\n");
    exit(EXIT_FAILURE);
    // EXIT_FAILURE 是在stdlib.h头文件中定义的宏，用于表示程序异常结束(=1)
  }
  new_node->value = n;
  new_node->next = list;
  return new_node;
}

/* 第二种写法：
typedef struct node {
  int value;
  struct node *next;
}Node;
Node *add_list(Node *list, int n) {
  Node *new_node = malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Error: malloc failed in add_list\n");
    exit(EXIT_FAILURE);
  }
  new_node->value = n;
  new_node->next = list;
  return new_node;
}
*/