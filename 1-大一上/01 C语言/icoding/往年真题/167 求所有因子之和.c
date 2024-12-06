/*
有如下定义：

【定义1】假设有正整数n和f（f小于n），如果n能够被f整除，那么f就是n的一个因子。

【定义2】正整数n的因子范围包括1但不包括n本身。

基于上述定义，假设有两个正整数a和b（a小于b），如果a的所有因子之和等于b，且b的所有因子等于a，那么二元组(a,b)就被称为是“亲密数对”。例如，(220,284)就是一对亲密数对。

根据上述描述，编写程序，要求如下。
编写一个函数，其功能是求正整数n的所有因子之和。

函数原型为：

 unsigned sum_of_factors(unsigned n);
 */
#include <stdio.h>
#include <stdlib.h>

unsigned sum_of_factors(unsigned n) {
  unsigned sum = 0;
  for (unsigned i = 1; i <= n / 2; i++) {
    if (n % i == 0) {
      sum += i;
    }
  }
  return sum;
}