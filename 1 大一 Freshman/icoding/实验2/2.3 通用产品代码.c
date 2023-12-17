/*
通用产品代码（UPC, Universal Production Code）

修改如下程序，使其可以检测 UPC 的有效性。在用户输入UPC后，程序将输出 VALID 或
NOT VALID 。

输出范例：


Enter the first (single) digit: 0
Enter first group of five digits: 13800
Enter second group of five digits: 15173
Enter the last (single) digit: 5
VALID


Enter the first (single) digit: 0
Enter first group of five digits: 51500
Enter second group of five digits: 24128
Enter the last (single) digit: 7
NOT VALID
*/
#include <stdio.h>
int main(void) {
  int c, d, i1, i2, i3, i4, i5, j1, j2, j3, j4, j5, first_sum, second_sum,
      total;

  // 提示用户输入第一个（单个）数字
  printf("Enter the first (single) digit:");
  scanf("%1d", &d);

  // 提示用户输入第一个分组的前五个数字
  printf("Enter the first group of five digits:");
  scanf("%1d%1d%1d%1d%1d", &i1, &i2, &i3, &i4, &i5);

  // 提示用户输入第二个分组的前五个数字
  printf("Enter the second group of five digits:");
  scanf("%1d%1d%1d%1d%1d", &j1, &j2, &j3, &j4, &j5);

  // 提示用户输入第一个（单个）数字
  printf("Enter the last (single) digit:");
  scanf("%1d", &c);

  // 计算第一个数字各位总和
  first_sum = d + i2 + i4 + j1 + j3 + j5;

  // 计算第二个数字各位总和
  second_sum = i1 + i3 + i5 + j2 + j4;

  // 计算总和（第一个数乘3加上第二个数）
  total = 3 * first_sum + second_sum;

  // 计算校验码（找到加上总和之后为10的倍数的个位数）
  int check_digit = 10 - (total % 10);
  if (check_digit == 10) {
    check_digit = 0;
  }
  // 将输入的最后一位数与校验码比对，输出结果
  if (c == check_digit) {
    printf("VALID\n");
  } else {
    printf("NOT VALID\n");
  }
  return 0;
}