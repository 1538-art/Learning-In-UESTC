/*
编写在给定数组里面找最大值和最小值的函数，函数原型如下：
void max_min(int a[], int n, int *max, int *min);
*/
#include <stdio.h>
#include <stdlib.h>
void max_min(int a[], int n, int *max, int *min) {
  int mmax = a[0], mmin = a[0];
  for (int i = 1; i < n; i++) {
    if (mmax < a[i])
      mmax = a[i];
    if (mmin > a[i])
      mmin = a[i];
  }
  *max = mmax;
  *min = mmin;
}