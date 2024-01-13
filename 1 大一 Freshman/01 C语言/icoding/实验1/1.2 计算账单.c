/*
计算账单（Bills）

编写⼀个程序，要求用户输出⼀个美元数量，然后显示出如何用最少20美元、10美元、5美元和1美元来付款。

Enter a dollar amount: 93
$20 bills: 4
$10 bills: 1
$5 bills: 0
$1 bills: 3
*/
#include <stdio.h>
int main() {
  int a, b, c, d, e;
  scanf("%d", &e);
  a = e / 20;
  e = e % 20;
  b = e / 10;
  e %= 10;
  c = e / 5;
  e %= 5;
  d = e;
  printf("$20 bills: %d\n$10 bills: %d\n$5 bills: %d\n$1 bills: %d", a, b, c,
         d);
  return 0;
}