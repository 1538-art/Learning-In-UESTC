/*
// 二叉树
typedef int DataType;

typedef struct Node {
  DataType data;
  struct Node *left;
  struct Node *right;
} BiTNode, *BiTree;

// 栈
#define Stack_Size 50
typedef BiTNode *ElemType;
typedef struct {
  ElemType elem[Stack_Size];
  int top;
} Stack;

void init_stack(Stack *S); // 初始化栈
bool push(Stack *S, ElemType x); //x 入栈
bool pop(Stack *S, ElemType *px);
 //出栈，元素保存到px所指的单元，函数返回true,栈为空时返回 false
bool top(Stack *S, ElemType *px);
 //获取栈顶元素，将其保存到px所指的单元，函数返回true，栈满时返回 false
bool is_empty(Stack *S);  // 栈为空时返回 true，否则返回 false

// 先序遍历
void pre_order(BiTree root);

void visit_node(BiTNode *node);
*/

#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过

void pre_order(BiTree root) {
  Stack S; // 声明栈变量
  init_stack(&S); // 初始化栈，传入栈的地址
  
  BiTree T = root; // 从根节点开始
  while (T != NULL || !is_empty(&S)) {
    if (T != NULL) {
      visit_node(T); // 访问当前节点
      push(&S, T); // 将当前节点压入栈中
      T = T->left; // 移动到左子树
    } else if (!is_empty(&S)) { // 如果栈不为空
      pop(&S, &T); // 弹出栈顶元素
      T = T->right; // 移动到右子树
    }
  }
}