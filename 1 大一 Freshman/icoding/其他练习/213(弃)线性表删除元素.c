/*
线性表删除元素
题目描述
【定义】线性表是一种存储数据的结构，其C语言描述如下：
// 线性表的最大容量
#define CAPACITY  128
typedef struct {
    int len; // 线性表实际存储的元素个数
    int data[CAPACITY];
//数组形式的存储空间。数据存储在该数组前len个单元中，后面的单元空置
} list;
输入一个有 N 个元素的线性表，输入一个位置 pos，将线性表内部数组中下标为 pos
的元素删除，原有元素依次前移。

注：插入元素后，线性表的长度要减小。
输入格式
输入分三行：
第一行是一个正整数 N，表示元素的个数。
第二行是 N 个用空格隔开的元素值。
第三行是一个正整数 pos，表示删除位置。
测试用例保证删除位置是合理的。

//输出格式
输出在一行。其中，第一值是刚删除的元素的值，此后是用空格隔开的线性表的元素。
//数据范围
0 < N ≤ CAPACITY
0 ≤ pos ≤ 线性表的有效长度
线性表元素是任意整数值
//输入样例1
9
99 22 77 44 55 66 33 88 11
0
输出样例1
99 22 77 44 55 66 33 88 11
输入样例2
9
99 22 77 44 55 66 33 88 11
8
输出样例2
11 99 22 77 44 55 66 33 88
输入样例3
9
99 22 77 44 55 66 33 88 11
4
输出样例3
55 99 22 77 44 66 33 88 11

#include <stdio.h>

// 你的代码写在 TODO和END OF TODO之间。
// 请勿修改这对标签外的任何代码！！！

// 线性表的最大容量
#define CAPACITY  128
typedef struct {
    int len; // 线性表实际存储的元素个数
    int data[CAPACITY]; // 数组形式的存储空间
} list;

 * @brief 在线性表的指定位置删除元素
 *
 * @param L 线性表指针
 * @param pos 删除位置
 * @return int 被删除元素的值
int del(list *L, int pos) {
  // TODO

  // END OF TODO
}

int main() {
  // 定义线性表及其指针
  list l, *L = &l;
  // 输入线性表长度
  scanf("%d", &L->len);
  // 输入线性表元素
  for (int i = 0; i < L->len; ++i)
    scanf("%d", &L->data[i]);
  int pos;
  // 输入插入位置和插入值
  scanf("%d", &pos);
  // 删除操作
  printf("%d ", del(L, pos));
  // 输出删除后的线性表
  for (int i = 0; i < L->len; ++i)
    printf("%d ", L->data[i]);
  printf("\n");
  return 0;
}*/

/*
 * @brief 在线性表的指定位置删除元素
 * @param L 线性表指针
 * @param pos 删除位置
 * @return int 被删除元素的值
 */
int del(list *L, int pos) {
  // TODO
  // 保存要删除的元素的值
  int value = L->data[pos];
  // 将删除位置之后的所有元素向前移动一位
  for (int i = pos; i < L->len - 1; i++)
    L->data[i] = L->data[i + 1];
  // 线性表的长度减1
  L->len--;
  // 返回被删除元素的值
  return value;
  // END OF TODO
}