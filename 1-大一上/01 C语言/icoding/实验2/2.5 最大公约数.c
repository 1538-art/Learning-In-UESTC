/*
最大公约数（GCD, Greatest Common Divisor）

编写程序，要求用户输入两个整数，然后计算这两个整数的最大公约数（GCD, Greatest
Common Divisor）。

输出范例：


Enter two integers: 12 28
Greatest common divisor: 4


Enter two integers：1 9
Greatest common divisor：1


提示：求最大公约数的经典算法 Euclid 算法如下：
分别让变量 m 和 n 存储两个整数。如果 n 为 0，那么停止操作，m 中的值是 GCD
；否则计算 m 除以 n 的余数，把 n 保存到 m 中，并把余数保存到 n
中；重复上述操作，每次都先判断n是否为 0 。
*/
#include <stdio.h>
int main() {
  int a, b, c = 0;
  scanf("%d%d", &a, &b);
  while (1) {
    if (b == 0) {
      printf("%d", a);
      break;
    } else {
      c = a % b;
      a = b;
      b = c;
    }
  }
  return 0;
}