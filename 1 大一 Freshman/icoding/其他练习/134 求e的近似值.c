/*
编写程序，用下面的公式计算e的近似值： e=1+1/1! +1/2! +1/3! +…+1/n!
示例如下
输入：
Enter value for n: 9
----------------------------------------------------
输出：
Approximation of e: 2.71828
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  scanf("%d", &n);
  double e = 1, mul = 1;
  for (int i = 1; i <= n; i++) {
    mul *= i;
    e += 1 / mul;
  }
  printf("Approximation of e: %.5lf", e);
  return 0;
}