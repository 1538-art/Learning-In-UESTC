
#ifndef CALCULATOR_V2_0_CALCULATOR_H
#define CALCULATOR_V2_0_CALCULATOR_H
//#include "Stack.h"
#include <math.h>
#include "linked-list-stack.h"

/// \param a 数组
/// \param n 数组长度
/// \explanation 清空指定数组
void ClearArray(char a[], int n);

/// \param a 传入字符
/// \return 若传入字符是符号，返回TRUE，否则返回FALSE
Bool IsSign(char a);

/// \param a 传入字符
/// \return 若传入字符在规定之内，则返回TRUE,否则返回FALSE
/// \explanation 判断是否为合法字符
Bool IsIncluded(char a);

/// \param former 前一个运算符
/// \param latter 后一个运算符
/// \return 若后一个运算符优先级高于前一个，则返回TRUE，否则返回FALSE
/// \explanation 当返回TRUE时，两个运算符按顺序入栈，否则，前一个运算符运算后再让后一个入栈。
/// 这样操作使得最后可以直接按后缀表达式从栈顶挨个取出元素运算直到算完。
Bool IsLatterPriorToFormer(char former, char latter);

/// \param former 前一个数字的地址
/// \param latter 后一个数字的地址
/// \param sign 运算符
/// \explanation 根据运算符进行两数间的运算
void CalculateTwoNum(double *former, double *latter, char sign);

#endif //CALCULATOR_V2_0_CALCULATOR_H
