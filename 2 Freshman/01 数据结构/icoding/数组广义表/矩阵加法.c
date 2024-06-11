/*
 * 矩阵加法

实现三元组表示的两个稀疏矩阵的加法。相关定义如下：

#define MAXSIZE 100          //假设非零元个数的最大值为100
typedef struct {
    int i,j;									//非零元的行下标和列下标，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
    ElemType e;						//非零元的值
}Triple;

typedef struct {
    Triple data[MAXSIZE];			// 非零元三元组表
    int    m, n, len;							// 矩阵的行数、列数和非零元个数
}TSMatrix;
在三元组中，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
矩阵加法函数的原型为：

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ);
pM, pN, pQ 分别指向三个矩阵，当 pM 和 pN 两个矩阵不可加时，函数返回 false，否则函数返回 true，且 pQ 指向两个矩阵的和。
 */

#include <stdio.h>
#include <stdlib.h>
#include "tsmatrix.h"

// 将稀疏矩阵 pM 和 pN 相加，结果存入 pQ
bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ){
  
  // 如果 pM 和 pN 的行列数不相等，则无法相加，返回 false
  if (pM->n != pN->n || pM->m != pN->m) {
    return false;
  }
  
  // pQ 的行列数和 pM 相同
  pQ->m = pM->m;
  pQ->n = pM->n;
  
  // Qdata_pos 表示结果矩阵 pQ 当前的非零元素个数
  int Qdata_pos = 0;
  int m = 0;
  int n = 0;
  int flag = -1;
  
  // 用归并排序的思想将 pM 和 pN 相加
  while (1) {
    if (m == pM->len && n == pN->len) {  // pM 和 pN 均已扫描完
      break;
    }
    
    // 如果 pM 扫描完了，则直接将 pN 剩余的元素复制到 pQ 中
    if (m == pM->len) {
      flag = 1;
    }
      // 如果 pN 扫描完了，则直接将 pM 剩余的元素复制到 pQ 中
    else if (n == pN->len) {
      flag = 2;
    }
    else {
      // 如果 pN 的当前元素在 pM 的当前元素之前，则先将 pN 的当前元素复制到 pQ 中
      if (pN->data[n].i < pM->data[m].i) {
        flag = 1;
      }
      else if (pN->data[n].i == pM->data[m].i) {
        // 如果 pN 和 pM 的当前元素的行下标相等，则比较列下标
        if (pN->data[n].j < pM->data[m].j) {
          flag = 1;
        }
        else if (pN->data[n].j == pM->data[m].j) {
          // 如果 pN 和 pM 的当前元素的行下标和列下标均相等，则将它们的值相加
          flag = 0;
        }
        else {
          flag = 2;
        }
      }
      else {
        flag = 2;
      }
    }
    // 根据 flag 的值进行相应的操作
    switch (flag) {
      case 1:
        pQ->data[Qdata_pos].i = pN->data[n].i;
        pQ->data[Qdata_pos].j = pN->data[n].j;
        pQ->data[Qdata_pos].e = pN->data[n].e;
        Qdata_pos++;
        n++;
        break;
      case 2:
        pQ->data[Qdata_pos].i = pM->data[m].i;
        pQ->data[Qdata_pos].j = pM->data[m].j;
        pQ->data[Qdata_pos].e = pM->data[m].e;
        Qdata_pos++;
        m++;
        break;
      case 0:
        pQ->data[Qdata_pos].i = pN->data[n].i;
        pQ->data[Qdata_pos].j = pN->data[n].j;
        pQ->data[Qdata_pos].e = pN->data[n].e + pM->data[m].e;
        Qdata_pos++;
        m++;
        n++;
        break;
      default:
        return false;
        break;
    }
  }
  pQ->len = Qdata_pos;
  //删除所有值为0的元素
  for (int q = 0; q < pQ->len; q++) {
    if (pQ->data[q].e == 0) {
      for (int i = q; i < pQ->len; i++) {
        pQ->data[i] = pQ->data[i + 1];
      }
      q--;
      pQ->len--;
    }
  }
  return true;
}