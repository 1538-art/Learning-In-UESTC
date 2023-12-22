/*
还原压缩的三角方阵
题目编号：191
一. 已知条件
三角方阵压缩
有这样的一种方阵（行列数相同的矩阵），左上三角地带所有值都是0，右下三角地带全是无规律的非0值。
例如，以下是这样的一个4阶方阵：
0 0 0 7
0 0 2 4
0 9 6 3
8 5 1 10
因为存在大量的0元素，所以常把它压缩存储到一个一维序列中：
7 2 4 9 6 3 8 5 1 10
假设方阵是n阶的，其非0元素个数为m，则有：m=n(n+1)/2；那么反推过来，n就接近于2m的平方根。提示：是向上取整还是向下取整？
数据结构
在C语言实现上，方阵可以用一个二维数组表示，压缩成的一维序列可以用一个一维数组表示。
二. 任务
请补全函数restore_matrix的编码。该函数的原型如下：
int restore_matrix(int a[], int b[][MAXN]); //#define MAXN  512
此函数的功能是：
将一维数组a中的压缩数据还原到方阵b中，返回方阵的阶数。
三. 测试用例
测试程序 测试程序已经写好，并保证输入的有效性。你不必自行编写。
测试程序的功能是：
从键盘依次输入压缩一维数组的值，最后一个数据是0值，表示输入结束。输入数值间用空格隔开。
调用你补全的函数restore_matrix，得到结果，并按行依次输出还原的二维方阵的所有元素，元素间用空格隔开。
测试用例举例
用例 输入 7 2 4 9 6 3 8 5 1 10 0 输出 0 0 0 7 0 0 2 4 0 9 6 3 8 5 1 10
四. 要求
请在框架文件中完成任务。
请将你的代码写在//TODO和//END OF TODO这对标记之间。
请勿修改框架中的任何已有内容。
*
1.
本题需要的数据较多。因此，为了避免你在本地调试时反复输入，已将测试用例写在了一个数据文件q4.in中，其内容如下：
7 2 4 9 6 3 8 5 1 10 0
上述数据产生的输出是：
0 0 0 7 0 0 2 4 0 9 6 3 8 5 1 10
2. 如果这个文件不存在，那么你就要从键盘手动输入。
3. 如果你的程序编译后是a.out，那在命令行里，你可以这样运行程序 a.out < q4.in
，避免重复从键盘输入
*
#include <math.h>
#include <stdio.h>
#define MAXN 512
int a[MAXN];
int b[MAXN][MAXN];
*
 * 将压缩到一维数组的二维方阵还原
 * 首先要根据一维数组的非0元素个数m，计算二维方阵的阶数n。
 * 提示：n接近于sqrt(2m)
 *
 * 参数说明：
 *      -
 * a：int[]，存储压缩数据的一维数组。其中的第一个0值只表示结尾，不是压缩数据。
 *      - b：int[][MAXN]，待还原的方阵。
 * 返回值说明：
 *      - int。方阵的阶数。
 *
int restore_matrix(int a[], int b[][MAXN]) {
  // TODO
  // END OF TODO
}
int main() {
  int i, j;
  i = 0;
  while (1) {
    scanf("%d", &a[i]);
    if (a[i] == 0)
      break;
    ++i;
  }
  int n = restore_matrix(a, b);
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      printf("%d ", b[i][j]);
  putchar('\n');
  return 0;
}
*/
#include <math.h>
#include <stdio.h>
#define MAXN 512
int a[MAXN];
int b[MAXN][MAXN];
int restore_matrix(int a[], int b[][MAXN]) {
  // TODO
  int i = 0; // 记录数组a中有多少个数据
  while (a[i] != 0) {
    i++;
  }
  int num = floor(sqrt(i * 2)); // 根据a中数据个数求方阵一行有几个数

  i = 0;                                   // 用于记录a中第几个数据
  for (int j = 0, n = num; j < num; j++) { // j表示第几行，num表示一行中0的个数
    for (int m = 0; m < n; m++) {
      b[j][m] = 0; // 将一行中前num个数设为0
    }
    n--;                                // 每行0的个数减一
    for (int m = 0; m < num - n; m++) { // 每一行不为0的数
      b[j][n + m] = a[i];
      i++; // 记录a数组中数据的变量加一
    }
  }
  return num; //
  // END OF TODO
}
int main() {
  int i, j;
  i = 0;
  while (1) {
    scanf("%d", &a[i]);
    if (a[i] == 0)
      break;
    ++i;
  }
  int n = restore_matrix(a, b);
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      printf("%d ", b[i][j]);
  putchar('\n');
  return 0;
}