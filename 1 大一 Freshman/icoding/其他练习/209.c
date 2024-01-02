/*
求交集求交集 题目描述
【定义】两个集合A和B的交集(intersection)C定义为：包含既在A中又在B中的元素。
给定两个无重复元素的无序的正整数集合A和B，求这两个集合的交集并输出。交集仍是无序的。
【算法】 k = 0 对 A 中每一个元素 a: { 对 B 中每一个元素 b: { 如果 a 等于 b:
C[k++] = a } } C[k] = -1 输入格式
第一行是用空格隔开的集合A的元素。最后一个值-1表示输入结束。注：-1不是集合的元素。
第二行是用空格隔开的集合B的元素。最后一个值-1表示输入结束。注：-1不是集合的元素。
>测试用例保证交集至少有一个元素 输出格式
输出在一行的、用空格隔开的A和B交集的元素。 数据范围 0 ＜ 输入值的个数 ≤ 20
输入样例1 1 3 5 -1 2 3 5 6 -1 输出样例1 3 5 输入样例2 6 7 8 9 2 -1 2 -1
输出样例2 2 输入样例3 1 2 3 -1 3 2 1 -1 输出样例3 1 2 3
*/
#include <stdio.h>

// 你的代码写在 TODO和END OF TODO之间。
// 请勿修改这对标签外的任何代码！！！

/**
 * @brief 求集合的交集
 *
 * @param A 输入集合
 * @param B 输入集合
 * @param C A和B的交集
 */
void intersect(int *A, int *B, int *C) {
  // TODO

  // END OF TODO
}

/**
 * @brief 输入以-1结尾的正整数集合（数组）
 *
 * @param S 集合
 */
void input_set(int *S) {
  int i = 0, v;
  do {
    scanf("%d", &v);
    S[i++] = v;
  } while (v != -1);
}

// 集合最大元素个数
#define MAXN 20

int main() {
  int A[MAXN], B[MAXN], C[MAXN];

  input_set(A);
  input_set(B);

  intersect(A, B, C);
  for (int i = 0; C[i] != -1; ++i)
    printf("%d ", C[i]);
  printf("\n");

  return 0;
}