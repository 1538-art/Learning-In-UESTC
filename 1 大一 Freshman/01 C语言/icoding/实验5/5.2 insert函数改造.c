/*题目：

修改16.3节的invertory.c程序，使 inventory 和 num_parts 为 main 函数的局部变量。

本小题只需完成 insert 函数的改造即可，相关结构及函数声明如下：

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

void insert(struct part inventory[], int *num_parts) {
  int part_number; // 定义变量part_number用于存储要插入的部件编号

  // 如果部件数量已经达到最大值，则无法再插入新的部件
  if (*num_parts == MAX_PARTS) {
    printf("Database is full; can't add more parts.\n");
    return;
  }

  printf("Enter part number: "); // 提示用户输入部件编号
  scanf("%d", &part_number);

  // 如果部件编号已经存在，则不插入新的部件
  if (find_part(part_number, inventory, *num_parts) >= 0) {
    printf("Part already exists.\n");
    return;
  }

  inventory[*num_parts].number =
      part_number; // 将新的部件编号存储到inventory数组中
  printf("Enter part name: "); // 提示用户输入部件名称
  read_line(inventory[*num_parts].name, NAME_LEN);
  printf("Enter quantity on hand: "); // 提示用户输入部件在手数量
  scanf("%d", &inventory[*num_parts].on_hand);

  (*num_parts)++; // 更新部件数量
}