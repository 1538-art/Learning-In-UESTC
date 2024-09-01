/*题目：

修改16.3节的invertory.c程序，使 inventory 和 num_parts 为 main 函数的局部变量。

本小题只需完成 print 函数的改造即可，相关结构及函数声明如下：

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

void print(const struct part inv[], int np) {
  int i; // 定义变量i用于循环遍历inventory数组

  // 打印表头
  printf("Part Number   Part Name            "
         "Quantity on Hand\n");

  // 循环遍历inventory数组，打印每个部件的编号、名称和在手数量
  for (i = 0; i < np; i++) {
    printf("%7d     %-25s%11d\n", inv[i].number, inv[i].name, inv[i].on_hand);
  }
}