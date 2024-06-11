/*
 * 十字链表

十字链表相关定义如下：

typedef int ElemType;

// 非零元素结点结构
typedef struct OLNode
{
    int row,col;
    ElemType value;
    struct OLNode *right,*down;
}OLNode,*OLink;

// 十字链表结构
typedef struct
{
    OLink *rowhead,*colhead;
    int rows,cols,nums;
}CrossList, *PCrossList;
1）实现十字链表的初始化操作：

 int init_cross_list(PCrossList L, const ElemType *A, int m, int n);
其中 L 指向 CrossList 结构，且各成员已被初始化为0；
A 为 ElemType 类型数组中第一个元素的地址，元素的个数为 m×n 个，按行优先存储（即A[0] 为十字链表第1行第1列的元素；
A[1] 为第1行第2列的元素，A[n] 为第2行第1列的元素，A[n+1] 为第2行第2个元素）；
m 表示十字链表的行数，n 表示十字链表的列数。
init_cross_list 函数将 ElemType 数组中非0元素保存到十字链表中，函数返回非 0 元素的个数。

2）实现十字链表的删除操作：

 int del_cross_list(PCrossList L, ElemType k);
其中 L 指向 要处理的 CrossList 结构，k 为要删除的元素；
del_cross_list 函数删除十字链表中所有值为 k 的结点，并返回删除结点的个数。
 */
#include <stdio.h>
#include <stdlib.h>
#include "crosslist.h"

int init_cross_list(PCrossList L, const ElemType* A, int m, int n) {
  // 初始化行数，列数和非零元素个数为0
  L->rows = m;
  L->cols = n;
  L->nums = 0;
  // 分配行指针数组和列指针数组的内存空间
  L->rowhead = (OLNode**)malloc(sizeof(OLNode*) * (m + 1));
  if (L->rowhead == NULL) {
    exit(0);
  }
  // 初始化行指针数组的所有元素为NULL
  for (int i = 0; i <= m; i++) {
    L->rowhead[i] = NULL;
  }
  L->colhead = (OLNode**)malloc(sizeof(OLNode*) * (n + 1));
  if (L->colhead == NULL) {
    exit(0);
  }
  // 初始化列指针数组的所有元素为NULL
  for (int i = 0; i <= n; i++) {
    L->colhead[i] = NULL;
  }
  
  OLNode* p_row = NULL;
  OLNode* p_col = NULL;
  
  // 遍历矩阵元素
  for (int i = 0; i < m * n; i++) {
    // 如果当前元素为0，则跳过
    if (A[i] == 0) {
      continue;
    }
    // 创建新结点
    OLNode* New = (OLNode*)malloc(sizeof(OLNode));
    if (New == NULL) {
      break;
    }
    // 初始化新结点
    New->down = NULL;
    New->right = NULL;
    New->row = i / n + 1; // 这里是从1开始算起的（即与数学中矩阵元素的编号一致）
    New->col = i % n + 1;
    New->value = A[i];
    // 非零元素个数加1
    L->nums++;
    
    // 尾插法插入新结点
    // 处理行指针
    if (i % n == 0) {
      p_row = L->rowhead[i / n + 1]; // 这里也是，rowhead和colhead都是从1开始储存
    }
    
    if (L->rowhead[i / n + 1] == NULL) {
      L->rowhead[i / n + 1] = New;
      New->right = NULL;
      p_row = New;
    }
    else {
      p_row->right = New;
      New->right = NULL;
      p_row = New;
    }
    // 处理列指针
    p_col = L->colhead[i % n + 1];
    if (L->colhead[i % n + 1] == NULL) {
      L->colhead[i % n + 1] = New;
      New->down = NULL;
      p_col = New;
    }
    else {
      while (p_col->down != NULL) {
        p_col = p_col->down;
      }
      p_col->down = New;
      New->down = NULL;
      p_col = New;
    }
  }
  
  return L->nums;
}

int del_cross_list(PCrossList L, ElemType k) {
  
  int count = 0;  // 计数器，记录删除的元素个数
  
  // 遍历每一行
  for (int i = 1; i <= L->rows; i++) {
    OLNode* p_row = L->rowhead[i];  // 指向当前行的头结点
    while (p_row != NULL) {  // 遍历当前行的每一个结点
      if (p_row->value == k) {  // 如果找到了值为k的结点
        OLNode* pre = L->rowhead[i];  // 指向当前结点前面的结点
        while (pre != p_row && pre->right != p_row) {  // 找到当前结点前面的结点
          pre = pre->right;
        }
        if (p_row == pre) {  // 如果当前结点是第一个结点
          L->rowhead[i] = L->rowhead[i]->right;  // 修改当前行的头结点
          p_row = L->rowhead[i];  // 重新指向当前结点
          continue;  // 继续遍历当前行的结点
        }
        else {  // 如果当前结点不是第一个结点
          pre->right = p_row->right;  // 修改前面结点的指针
          p_row = p_row->right;  // 重新指向当前结点
          continue;  // 继续遍历当前行的结点
        }
      }
      p_row = p_row->right;  // 继续遍历当前行的下一个结点
    }
  }
  
  // 遍历每一列
  for (int i = 1; i <= L->cols; i++) {
    OLNode* p_col = L->colhead[i];  // 指向当前列的头结点
    while (p_col != NULL) {  // 遍历当前列的每一个结点
      if (p_col->value == k) {  // 如果找到了值为k的结点
        OLNode* pre = L->colhead[i];  // 指向当前结点前面的结点
        while (pre != p_col && pre->down != p_col) {  // 找到当前结点前面的结点
          pre = pre->down;
        }
        if (p_col == pre) {  // 如果当前结点是第一个结点
          count++;  // 计数器加1
          L->colhead[i] = p_col->down;  // 修改当前列的头结点
          p_col = L->colhead[i];  // 重新指向当前结点
          free(pre);  // 释放前面结点的内存
          continue;  // 继续遍历当前列的结点
        }
        else {  // 如果当前结点不是第一个结点
          count++;  // 计数器加1
          OLNode* temp = pre->down;  // 指向当前结点的下一个结点
          pre->down = p_col->down;  // 修改前面结点的指针
          p_col = p_col->down;
          free(temp);  // 释放当前结点的内存
          continue;  // 继续遍历当前列的结点
        }
      }
      p_col = p_col->down;  // 继续遍历当前列的下一个结点
    }
  }
  
  return count;  // 返回删除的元素个数
}
