/*
编写main函数，要求用户输入10个整数存入数组，调用函数max_min找出数组中的最大值和最小值
示例如下
输入：
Enter 10 numbers: 15 1 56 2 7 9 85 99 3 5
----------------------------------------------------
输出：
Largest: 99
Smallest: 1
*/
#include <stdio.h>
#include <stdlib.h>
void max_min(int a[], int n, int *max, int *min);

int main() {
  int a[10], min, max;
  for (int i = 0; i < 10; i++) {
    scanf("%d", &a[i]);
  }
  max_min(a, 10, &max, &min);
  printf("Largest: %d\nSmallest: %d", max, min);
  return 0;
}
