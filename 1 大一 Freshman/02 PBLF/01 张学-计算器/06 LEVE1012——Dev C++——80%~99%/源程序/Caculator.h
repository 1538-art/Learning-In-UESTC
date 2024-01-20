#ifndef CACULATOR_H
#define CACULATOR_H

//包含链式栈的头文件
//#include "Linked_Stack" 

//包含通用栈的头文件 
#include "Generic_Stack.h"

int GetPriority(char op);
/* 函数：GetPriority
 * -----------------
 * 获取操作符的优先级。
 *
 * op：操作符。
 *
 * 返回值：操作符的优先级，值越大表示优先级越高。
 */

int IsSpace(char c);
/* 函数：IsSpace
 * --------------------
 * 判断字符是否为空格或制表符。
 *
 * c：要判断的字符。
 *
 * 返回值：如果字符为空格或制表符，返回 TRUE；否则返回 FALSE。
 */
 
Bool IsDigit(char elem);
/* 函数：IsDigit
 * -------------
 * 检查字符是否为数字。
 *
 * elem：字符。
 *
 * 返回值：若字符为数字返回TRUE，否则返回FALSE。
 */

 Bool IsUnaryOperator(const char c);
/* 函数：IsUnaryOperator
 * ---------------------
 * 判断字符是否为单目运算符。
 *
 * c：要判断的字符。
 *
 * 返回值：如果字符为单目运算符，返回 TRUE；否则返回 FALSE。
 */

Bool IsBinaryOperator(const char c);
/* 函数：IsBinaryOperator
 * ----------------
 * 检查字符是否为双目运算符。
 *
 * c：字符。
 *
 * 返回值：若字符为操作符返回TRUE，否则返回FASLE。
 */

double ConvertToFloat(char str[]);
/* 函数：ConvertToFloat
 * --------------------
 * 将字符串转换为浮点数。
 *
 * str：字符串。
 *
 * 返回值：转换后的浮点数。
 */

Bool IsValidExpression(const char str[]);
/* 函数：IsValidExpression
 * --------------------
 * 判断用户输入的表达式是否合法
 *
 * str：字符串。
 *
 * 返回值：若合法返回TRUE，否则返回FASLE。
 */
 
void InfixToSuffix(char infix[], char postfix[]);
/* 函数：InfixToPostfix
 * --------------------
 * 将中缀表达式转换为后缀表达式。
 *
 * infix：中缀表达式字符串。
 * postfix：用于存储后缀表达式的字符串。
 *
 * 返回值：无。
 */

double Calculate(char suffix[]);
/* 函数：Calculate
 * ---------------------
 * 计算后缀表达式并返回结果。
 *
 * suffix：后缀表达式 
 *
 * 返回值：后缀表达式的计算结果，以浮点数形式返回。
 */
 
Status Stdin_Caculate(void);
/* 函数：Stdin_Caculate
 * ---------------------
 * 进行键盘输入表达式的计算并返回结果。
 *
 * 无参数 
 *
 * 返回值：计算成功则返回OK，否则返回ERROR。 
 */

Status Butch_caculate(const char* inputFilePath, const char* outputFilePath);
/* 函数：Butch_Caculate
 * ---------------------
 * 进行文件输入表达式的批量计算并返回结果。
 *
 * inputFilePath：输入文件路径
 * outputFilePath：输出文件路径 
 *
 * 返回值：计算成功返回OK，否则返回ERROR。 
 */

Status Butch_Caculate();
/* 函数：Butch_Caculate
 * ---------------------
 * 批量计算。 
 *
 * 返回值：计算成功返回OK，否则返回ERROR。 
 */
 #endif
