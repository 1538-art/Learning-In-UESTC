/*
大小写转换大小写转换 题目描述
一个字符串中可能嵌入了一个整数（如果有，则只有这一个）。编写程序读取这个整数并输出。
输入格式 一行字符串S 输出格式
字符串中嵌入的整数。如果没有嵌入的整数，那么输出0。 数据范围 0 ＜ len(S) ≤ 1000
输入样例1 abc1234def 输出样例1 1234 输入样例2 1234. 输出样例2 1234 输入样例3
abcde 输出样例3 0
*/
#include <stdio.h>

// 你的代码写在 TODO和END OF TODO之间。
// 请勿修改这对标签外的任何代码！！！

/**
 * @brief 读取字符串中的整数
 *
 * @param s 字符串
 * @return int 字符串中嵌入的整数。如果没有，则返回0。
 */
int get_int(char *s) {
  // 在此函数中，需要用到字符输出
  // TODO

  // END OF TODO
}

char S[1000];
int main() {
  scanf("%s", S);
  printf("%d\n", get_int(S));

  return 0;
}