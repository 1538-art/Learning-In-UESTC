/*
bool path(BiTNode* root, BiTNode* node, Stack* s);

#define Stack_Size 50
typedef BiTNode* ElemType;
typedef struct{
  ElemType elem[Stack_Size];
  int top;
}Stack;

void init_stack(Stack *S); // 初始化栈
bool push(Stack* S, ElemType x); //x 入栈
bool pop(Stack* S, ElemType *px); //出栈，元素保存到px所指的单元，函数返回true,栈为空时返回 false
bool top(Stack* S, ElemType *px); //获取栈顶元素，将其保存到px所指的单元，函数返回true，栈满时返回 false
bool is_empty(Stack* S);  // 栈为空时返回 true，否则返回 false

//完成
BiTNode * nearest_ancestor(BiTree root, BiTNode *p, BiTNode *q);
*/

#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过

BiTNode* nearest_ancestor(BiTree root, BiTNode* p, BiTNode* q)
{
  Stack s1, s2;
  BiTNode* ancNode;
  init_stack(&s1);
  init_stack(&s2);
  
  path(root, p, &s1);
  path(root, q, &s2);
  
  if (s1.elem[0] != s2.elem[0])
    return NULL;
  
  ancNode = s1.elem[0];
  
  for (int i = 1; i < s1.top && i < s2.top; i++)
  {
    if (s1.elem[i] != s2.elem[i])
      return ancNode;
    ancNode = s1.elem[i];
  }
  return ancNode;
}