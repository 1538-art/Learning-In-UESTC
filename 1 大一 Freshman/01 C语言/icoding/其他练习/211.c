/*
判断是否是亲密数对判断是否是亲密数对 【定义】亲密数对指的是一对正整数 m 和 n，m
的真因子之和等于 n，n 的真因子之和等于 m。其中，正整数 x 真因子 y 指得是 y < x
且 x 能被 y 整除。 输入正整数 m 和 n，判断它们是否是亲密数对。 【算法】 1. 先求
m 的真因子之和 x 2. 再求 n 的真因子之和 y 3. 如果 x == y，则 m 和 n
是亲密数对；否则不是 输入格式 两个正整数 m 和 n，用空格隔开。 输出格式 m 和 n
是亲密对，输出 n m，用空格隔开 否则输出字符串 "not"。 数据范围 0 < n ≤ 10000 0 <
m ≤ 10000 输入样例1 220 284 输出样例1 284 220 输入样例2 2620 2924 输出样例2 2924
2620 输入样例3 580 290 输出样例3 not
*/
#include <stdio.h>

// 你的代码写在 TODO和END OF TODO之间。
// 请勿修改这对标签外的任何代码！！

/**
 * @brief 求x的所有真因子之和
 *
 * @param x 正整数
 * @return int 真因子之和
 */
int sum_of_factor(int x) {
  // TODO

  // END OF TODO
}

/**
 * @brief 判断是否是亲密数对
 *
 * @param m 数1
 * @param n 数2
 */
void is_intimate(int m, int n) {
  // TODO
  // 这个程序要用到输出

  // END OF TODO
}

int main() {
  int m, n;
  scanf("%d%d", &m, &n);

  is_intimate(m, n);

  return 0;
}