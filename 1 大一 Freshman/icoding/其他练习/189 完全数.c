/*
找出闭区间内所有完全数
题目编号：189
一. 已知条件
真因子 有正整数f和m，且f <
m。如果m能被f整除，那么f是m的真因子。显然，1是任意大于1的正整数的真因子；m不是它本身的真因子。
完全数
如果一个正整数m，其所有真因子之和等于m，那么它就是一个完全数。例如完全数6和28：
6 = 1 + 2 + 3
28 = 1 + 2 + 4 + 7 + 14
二. 任务
请补全函数is_perfect。该函数的原型如下：
bool is_perfect(unsigned m);
此函数的功能是：
判断m是否是一个完全数。
如果是，则返回真true；否则返回假false。
注：你可以将bool类型看作是int类型，true视为1，false视为0。
提示：如果判断i是m的真因子？
三. 测试用例
测试程序 测试程序已经写好，并保证输入的有效性。你不必自行编写。
测试程序的功能是：
从键盘输入两个正整数a和b并保证3 < a < b <= 10000。
调用你补全的函数is_perfect，找出区间内的所有完全数，并按如下格式输出结果:
(完全数1)(完全数2)...(完全数n) 如果区间内没有完全数，则输出为： ()
测试用例举例
示例1 输入 1 30 输出 (6)(28)
示例2 输入 7 27 输出 ()
四. 要求
请在框架文件中完成任务。
请将你的代码写在//TODO和//END OF TODO这对标记之间。
请勿修改框架中的任何已有内容。
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
*
 * 判断m是否为完全数
 * 参数说明：
 *      - m：unsigned，待判断的正整数
 * 返回值说明：
 *      - bool，如果m是完全数，返回true；否则返回false。
 *
bool is_perfect(unsigned m) {
  // TODO
  // END OF TODO
}
static void print_perfect(unsigned a, unsigned b) {
  int c = 0;
  for (unsigned i = a; i <= b; ++i)
    if (is_perfect(i)) {
      ++c;
      printf("(%d)", i);
    }
  if (!c)
    printf("()");
  putchar('\n');
}
int main() {
  unsigned a, b;
  scanf("%u%u", &a, &b);
  print_perfect(a, b);
  return 0;
}
*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
bool is_perfect(unsigned m) {
  unsigned sum = 1;
  for (unsigned i = 2; i <= m / 2; ++i) {
    if (m % i == 0) {
      sum += i;
    }
  }
  return sum == m;
}
static void print_perfect(unsigned a, unsigned b) {
  int c = 0;
  for (unsigned i = a; i <= b; ++i)
    if (is_perfect(i)) {
      ++c;
      printf("(%d)", i);
    }
  if (!c)
    printf("()");
  putchar('\n');
}
int main() {
  unsigned a, b;
  scanf("%u%u", &a, &b);
  print_perfect(a, b);
  return 0;
}
