/*
分数加法（Fraction Addition）

修改如下程序，使用户可以同时输入两个分数，中间用加号隔开：

Enter two fractions separated by a plus sign: 5/6+3/4
The sum is 38/24
 */
#include <stdio.h>
int main(void) {
  int a, b, c, d;
  scanf("%d/%d+%d/%d", &a, &b, &c, &d);
  int a1 = a * d, c1 = c * b, e = b * d;
  int f = a1 + c1;
  printf("The sum is %d/%d", f, e);
  return 0;
}