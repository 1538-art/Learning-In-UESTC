#ifndef CALCULATOR_H
#define CALCULATOR_H

//包含链表实现的栈
//#include "LinkedStack.h"

//包含动态数组实现的泛型栈
#include "Generic_Stack.h"

//调试模式
#define DEBUG 0

//定义表达式最大长度
#define EXPRESSION_MAX_SIZE 100
// 最多支持计算的表达式个数
#define MAX_EXPRESSIONS 1000 

// 计算器对象的结构体定义
typedef struct {
    char* pExp; // 存储表达式的字符串
    double result; // 存储计算结果
} Calculator;

Calculator* Calculator_Construct();
/* 函数：Calculator_Construct
 * ---------------------------
 * 创建并返回一个新的计算器对象。
 *
 * 返回值：指向新创建的计算器对象的指针。
 */

void Calculator_Destruct(Calculator* pCalculator);
/* 函数：Calculator_Destruct
 * --------------------------
 * 销毁指定的计算器对象。
 *
 * pCalculator: 指向要销毁的计算器对象的指针。
 */

void Calculator_InputExpression(Calculator* pCalculator);
/* 函数：Calculator_InputExpression
 * ---------------------------------
 * 从标准输入读取表达式并将其存储在计算器对象中。
 *
 * pCalculator: 指向计算器对象的指针。
 */

double Calculator_OutputResult(Calculator* pCalculator);
/* 函数：Calculator_OutputResult
 * ------------------------------
 * 计算存储在计算器对象中的表达式，并返回结果。
 *
 * pCalculator: 指向计算器对象的指针。
 *
 * 返回值：计算结果。
 */

Bool Calculator_isSpace(char c);
/* 函数：Calculator_isSpace
 * -------------------------
 * 判断指定字符是否为空格。
 *
 * c: 要判断的字符。
 *
 * 返回值：如果指定字符为空格，返回TRUE，否则返回FALSE。
 */

Bool Calculator_isUnaryOperator(const char c);
/* 函数：Calculator_isUnaryOperator
 * --------------------------------
 * 判断指定字符是否为一元运算符。
 *
 * c: 要判断的字符。
 *
 * 返回值：如果指定字符是一元运算符，返回TRUE，否则返回FALSE。
 */

void Calculator_BatchCalculate(const char* inputFilePath, const char* outputFilePath);
/* 函数：Calculator_BatchCalculate
 * --------------------------------
 * 从指定文件中读取多个表达式，并将计算结果写入到另一个文件中。
 *
 * inputFilePath: 指向包含输入表达式的文件的路径的指针。
 * outputFilePath: 指向要写入计算结果的文件的路径的指针。
 */

int Calculator_getPriority(const char op);
/* 函数：Calculator_getPriority
 * -----------------------------
 * 获取指定运算符的优先级。
 *
 * op: 要获取优先级的运算符。
 *
 * 返回值：指定运算符的优先级。
 */

Bool Calculator_isDigit(char elem);
/* 函数：Calculator_isDigit
 * -------------------------
 * 判断指定字符是否为数字。
 *
 * elem: 要判断的字符。
 *
 * 返回值：如果指定字符是数字，返回TRUE，否则返回FALSE。
 */

Bool Calculator_isBinaryOperator(const char c);
/* 函数：Calculator_isBinaryOperator
 * ---------------------------------
 * 判断指定字符是否为二元运算符。
 *
 * c: 要判断的字符。
 *
 * 返回值：如果指定字符是二元运算符，返回TRUE，否则返回FALSE。
 */

double Calculator_convertToFloat(char str[]);
/* 函数：Calculator_convertToFloat
 * --------------------------------
 * 将指定字符串转换为浮点数。
 *
 * str: 要转换的字符串。
 *
 * 返回值：转换后的浮点数。
 */

Bool Calculator_IsValidExpression(const char str[]);
/* 函数：Calculator_IsValidExpression
 * ----------------------------------
 * 判断指定字符串是否为合法的表达式。
 *
 * str: 要判断的字符串。
 *
 * 返回值：如果指定字符串是合法的表达式，返回TRUE，否则返回FALSE。
 */

void Calculator_transform(char infix[], char postfix[], int n);
/* 函数：Calculator_transform
 * ---------------------------
 * 将中缀表达式转换为后缀表达式。
 *
 * infix: 指向中缀表达式的字符串的指针。
 * postfix: 指向后缀表达式的字符串的指针。
 * n: 中缀表达式字符串的长度。
 */

double Calculator_calculate(char postfix[]);
/* 函数：Calculator_calculate
 * ---------------------------
 * 计算指定的后缀表达式，并返回结果。
 *
 * postfix: 指向后缀表达式的字符串的指针。
 *
 * 返回值：计算结果。
 */


#endif
