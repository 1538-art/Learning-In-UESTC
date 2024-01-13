/*01 main函数改造。

修改inventory.c (点击下载)程序，使 inventory 和 num_parts 为 main
函数的局部变量。

本小题只需完成 main 函数的改造即可，相关结构及函数声明如下：

#define NAME_LEN 25

#define MAX_PARTS 100

struct part {
int number;
char name[NAME_LEN+1];
int on_hand;
};


int read_line(char str[], int n);
int find_part(int number, const struct part inv[], int np);
void insert(struct part inv[], int *np);
void search(const struct part inv[], int np);
void update(struct part inv[], int np);
void print(const struct part inv[], int np);

该部分声明已包含在 “lab51.h”中。*/
#include "lab51.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

int main() {
  char code;
  struct part inventory[MAX_PARTS];
  int num_parts = 0;
  for (;;) {
    printf("Enter operation code: ");
    scanf("%c", &code);
    while (getchar() != '\n')
      ;
    switch (code) {
    case 'i': // 插入操作
      insert(inventory, num_parts);
      break;
    case 's': // 搜索操作
      search(inventory, num_parts);
      break;
    case 'u': // 更新操作
      update(inventory, num_parts);
      break;
    case 'p': // 打印操作
      print(inventory, num_parts);
      break;
    case 'q': // 退出程序
      return 0;
      break;
    default: // 非法操作
      printf("Illegal code\n");
    }
    printf("\n");
  }
}