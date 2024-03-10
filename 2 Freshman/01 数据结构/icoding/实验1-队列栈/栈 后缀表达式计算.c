/*
请使用已定义好的栈完成后缀表达式计算：
(1)如果是操作数，直接入栈
(2)如果是操作符op，连续出栈两次，得到操作数x 和 y,计算 x op y，并将结果入栈。

后缀表达式示例如下：
9  3  1  -  3  *  +  10  2  /  +
13  445  +  51  /  6  -
操作数、操作符之间由空格隔开，操作符有 +，-，*, /, %共 5
种符号，所有操作数都为整型。

栈的定义如下：

#define Stack_Size 50
typedef struct{
    ElemType elem[Stack_Size];
    int top;
}Stack;

bool push(Stack* S, ElemType x);
bool pop(Stack* S, ElemType *x);
void init_stack(Stack *S);
其中，栈初始化的实现为：

void init_stack(Stack *S){
    S->top = -1;
}
需要完成的函数定义为：int compute_reverse_polish_notation(char *str);

函数接收一个字符指针，该指针指向一个字符串形式的后缀表达式，函数返回该表达式的计算结果。
*/
#include <stdbool.h>

#define Stack_Size 50
typedef struct {
  int elem[Stack_Size];
  int top;
} Stack;

bool push(Stack *S, int x);
bool pop(Stack *S, int *x);
void init_stack(Stack *S);
void init_stack(Stack *S) { S->top = -1; }

#include "list.h" // 请不要删除，否则检查不通过
#include <stdio.h>
#include <stdlib.h>


int compute_reverse_polish_notation(char *str) {
  Stack *numStack = (Stack *)malloc(sizeof(Stack));
  if (numStack == NULL) {
    printf("Failed to allocate memory for numStack\n");
    return -1;
  }
  init_stack(numStack);

  int res = 0;
  char temp[30];
  int offset = 0;
  while (sscanf(str, "%29s%n", temp, &offset) == 1) {
    str += offset;
    if (temp[0] >= '0' && temp[0] <= '9') {
      push(numStack, atoi(temp));
    } else {
      int x, y;
      pop(numStack, &y);
      pop(numStack, &x);
      switch (temp[0]) {
      case '+':
        push(numStack, x + y);
        break;
      case '-':
        push(numStack, x - y);
        break;
      case '*':
        push(numStack, x * y);
        break;
      case '/':
        push(numStack, x / y);
        break;
      case '%':
        push(numStack, x % y);
        break;
      }
    }
    for (int i = 0; i < 30; i++) {
      temp[i] = '\0';
    }
  }
  pop(numStack, &res);
  return res;
}