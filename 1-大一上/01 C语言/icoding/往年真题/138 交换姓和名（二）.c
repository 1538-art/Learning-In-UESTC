/*
读入用户输入的一行信息，按字符串格式存储在数组str中，
数组最多能存n个有效字符，函数返回str中有效字符的个数（不包括字符串尾部标记）。

函数原型如下：

 int read_line(char str[], int n);
*/
#include <stdio.h>

int read_line(char str[], int n) {
  int i = 0;
  char ch;

  while ((ch = getchar()) != '\n') {
    if (i < n) {
      str[i++] = ch;
    }
  }
  str[i] = '\0';
  return i;
}