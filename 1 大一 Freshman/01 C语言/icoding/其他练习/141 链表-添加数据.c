/*
编写main函数，输入3个整数，调用add_list函数将这3个整数按顺序添加到链表中，每次添加后在屏幕上显示新添加结点的值。程序输入输出示例如下：
示例如下
输入：
Enter 3 integers: 10 20 30
----------------------------------------------------
输出：
(*first).value = 10
(*first).value = 20
(*first).value = 30
*/
#include <stdio.h>
int main() {
  struct node *list = NULL;
  int i, n;

  printf("Enter 3 integers: ");
  for (i = 0; i < 3; i++) {
    scanf("%d", &n);
    list = add_list(list, n);
    printf("(*first).value = %d\n", list->value);
  }
  // 释放内存
  struct node *tmp;
  while (list != NULL) {
    tmp = list;
    list = list->next;
    free(tmp);
  }

  return 0;
}
