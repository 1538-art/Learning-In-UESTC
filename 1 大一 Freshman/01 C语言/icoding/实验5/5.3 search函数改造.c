/*题目：

修改16.3节的invertory.c程序，使 inventory 和 num_parts 为 main 函数的局部变量。

本小题只需完成 search 函数的改造即可，相关结构及函数声明如下：

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

void search(const struct part inv[], int np) {
  int i, number; // 定义变量i和number用于存储要查找的部件编号

  printf("Enter part number: "); // 提示用户输入部件编号
  scanf("%d", &number);          // 读取用户输入的部件编号

  i = find_part(number, inv, np); // 在inventory数组中查找指定的部件编号

  if (i >= 0) {                             // 如果查找到了部件
    printf("Part name: %s\n", inv[i].name); // 输出部件名称
    printf("Quantity on hand: %d\n", inv[i].on_hand); // 输出部件在手数量
  } else {                       // 如果没有查找到部件
    printf("Part not found.\n"); // 输出提示信息
  }
}