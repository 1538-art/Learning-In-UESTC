/*
计算税金(Tax)

编写一个程序，要求用户输入一个美元数量，然后显示出增加 5% 税率后的相应金额。

Enter an amount: 100.00
with tax added: $105.00

输入的金额为大于 0 的两位数浮点数。
*/
#include <stdio.h>

int main() {
  float a;
  scanf("%f", &a);
  a += a * 0.05;
  printf("%.2f", a);

  return 0;
}