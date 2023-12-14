/*栈（Stack）

修改如下程序，使它存储字符而不是整数。

增加 main
函数，用来要求用户输入一串圆括号或花括号，然后指出它们之间的嵌套是否正确。

输出范例：


Enter parentheses and/or braces: ()({})({})
Parentheses/braces are nested properly


Enter parentheses and/or braces: ((}
Parentheses/braces are NOT nested properly

#include <stdbool.h>    //C99 only
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

// external variables
char contents[STACK_SIZE];
int top = 0;

void stack_overflow(void) {
  printf("Stack overflow\n");
  exit(EXIT_FAILURE);
}

void stack_underflow(void) {
  printf("Stack underflow\n");
  exit(EXIT_FAILURE);
}

void make_empty(void) { top = 0; }

bool is_empty(void) { return top == 0; }

bool is_full(void) { return top == STACK_SIZE; }

void push(char ch) {
  if (is_full())
    stack_overflow();
  else
    contents[top++] = ch;
}

char pop(void) {
  if (is_empty())
    stack_underflow();
  else
    return contents[--top];

  return '\0'; // prevents compiler warning due to stack_underflow() call
}

int main(void) { return 0; }

*/
#include <stdbool.h> // C99 only
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

// external variables
char contents[STACK_SIZE];
int top = 0;

// 定义栈溢出的处理函数
void stack_overflow(void) {
  printf("Stack overflow\n");
  exit(EXIT_FAILURE);
}

// 定义栈为空的处理函数
void stack_underflow(void) {
  printf("Stack underflow\n");
  exit(EXIT_FAILURE);
}

// 定义将栈置为空的函数
void make_empty(void) { top = 0; }

// 定义检查栈是否为空的函数
bool is_empty(void) { return top == 0; }

// 定义检查栈是否已满的函数
bool is_full(void) { return top == STACK_SIZE; }

// 定义将字符压入栈的函数
void push(char ch) {
  if (is_full())
    stack_overflow();
  else
    contents[top++] = ch;
}

// 定义从栈中弹出一个字符的函数
char pop(void) {
  if (is_empty())
    stack_underflow();
  else
    return contents[--top];

  return '\0'; // 防止编译器警告 due to stack_underflow() call
}

int main(void) {
  char ch;
  int correct = 1;
  while (correct && (ch = getchar()) != '\n') {
    if (ch == '(' || ch == '{')
      push(ch);
    else if (ch == ')')
      correct = !is_empty() && pop() == '(';
    else if (ch == '}')
      correct = !is_empty() && pop() == '{';
  }
  if (correct && is_empty()) {
    printf("Parentheses/braces are nested properly\n");
  } else
    printf("Parentheses/braces are NOT nested properly\n");
  return 0;
}