/*
编写main函数，要求用户输入英文“名
姓”，用read_line函数读入这行信息，然后调用reverse_name函数进行姓名互换，并在main函数里面打印显示变化后的“姓
名”，输入输出示例如下：
(注意题目示例输出为 Clinton,
W.,是做了处理的；reverse_name和read_line可以直接使用）
----------------------------------------------------
示例如下
输入：
Enter a first and last name: William Clinton
输出：
Clinton, W.
*/
#include <stdio.h>
#include <stdlib.h>

void reverse_name(char *name);
int read_line(char str[], int n);

int main() {
  char name[100];
  read_line(name, sizeof(name));
  reverse_name(name);
  printf("%s\n", name);
  return 0;
}
