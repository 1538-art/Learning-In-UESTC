#include <math.h>
#include "Stack.h"
#define ARRAY_SIZE 100  //常用数组长度

//获取操作符的优先值
int GetPriority(void* operator);
//返回operator所指向的值的优先级大小

//进行后缀表达式计算
float Perform(float operand1, float operand2, char operator);
//返回新的值

//计算器
float Calculates(const char* expression);
//返回该表达式的最终结果
