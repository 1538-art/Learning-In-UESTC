/*
表达式求值（Expression Evaluation）

编写程序对表达式求值。

Enter an expression: 1+2.5*3
Value of expression: 10.5


表达式中的操作数是浮点数，运算符是+、-、*和/。表达式从左向右求值（所有运算符的优先级都⼀样）。


输出范例：


Enter an expression: 2+3*4-5/2
Value of expression: 7.5
*/
#include <stdio.h>   // 引入标准输入输出库
int main() {         // 主函数
  float a, b;        // 定义两个浮点型变量a和b
  char c;            // 定义一个字符变量c
  scanf("%f", &a);   // 读取一个浮点数，并将其存储在变量a中
  while (1) {        // 循环直到换行
    c = getchar();   // 从标准输入读取一个字符
    if (c == '\n')   // 如果读取到换行符
      break;         // 跳出循环
    scanf("%f", &b); // 读取一个浮点数，并将其存储在变量b中
    switch (c) {     // 按照字符c进行switch判断
    case '+':
      a = a + b;
      break; // 如果c为'+'，将a和b相加，并将结果存储在变量a中
    case '-':
      a = a - b;
      break; // 如果c为'-'，将a和b相减，并将结果存储在变量a中
    case '*':
      a = a * b;
      break; // 如果c为'*'，将a和b相乘，并将结果存储在变量a中
    case '/':
      a = a / b;
      break; // 如果c为'/'，将a和b相除，并将结果存储在变量a中
    }
  }
  printf("%.1f", a); // 输出变量a的值，保留1位小数
  return 0;          // 返回0，表示程序执行成功
}