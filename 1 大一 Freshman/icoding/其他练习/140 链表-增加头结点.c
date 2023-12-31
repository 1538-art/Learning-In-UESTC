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
struct node {
  int value;
  struct node *next;
};
struct node *add_list(struct node *list, int n) {
  struct node *new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("Error: malloc failed in add_list\n");
    exit(EXIT_FAILURE);
  }
  new_node->value = n;
  new_node->next = list;
  return new_node;
}
