/*
这个程序不符合大型程序要求，5个函数紧耦合，可读性差，没有运用抽象数据类型
可能的借鉴意义：
    只运用了函数及其之前的知识完成了比较复杂的任务
    思路奇特
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH 500

double AddAndSubtract1(char **p);
/*用于处理加法和减法的函数，并在操作后移动指针
 *输入参数：主函数中p的地址或主调函数的p
 *返回值：最终结果
 */
double MultiplyAndDivide2(char **p);
/*用于处理乘法和除法的函数，并在操作后移动指针
 *输入参数：主调函数中p
 *返回值：中间结果
 */
double Rower3(char **p);
/*用于处理乘方的函数，并在操作后移动指针
 *输入参数：主调函数中p
 *返回值：中间结果
 */
double Bracket4(char **p);
/*用于处理圆括号的函数，并在操作后移动指针
 *输入参数：主调函数中p
 *返回值：括号内结果
 */
double Transform5(char **p);
/*用于处理数字的函数,将最前部的数字字符转换为浮点型，并在操作后移动指针
 *输入参数：主调函数中p的地址
 *返回值：中间结果
 */

double Transform5(char **p) {
    // 使用strtod函数将字符串转换为浮点数，并将字符串指针向前移动
    double result = strtod(*p, p);
    return result;
}

double Bracket4(char **p) {
    // 如果当前字符是'('，则处理括号内的表达式
    if (**p == '(') {
        (*p)++;  //跳过'('字符
        double result = AddAndSubtract1(p);
        (*p)++;  //跳过')'字符
        return result;
    } else {
        // 否则，处理数字
        return Transform5(p);
    }
}

double Rower3(char **p) {
    double result = Bracket4(p);
    // 如果当前字符是'^'，则处理乘方运算
    if (**p == '^') {
        (*p)++;
        result = pow(result, Bracket4(p));
    }
    return result;
}

double MultiplyAndDivide2(char **p) {    //这里的s是主函数的&s
    double result = Rower3(p);
    // 如果当前字符是'*'或'/'，则处理乘法或除法运算
    while (**p == '*' || **p == '/') {
        if (*(*p)++ == '*') {
            result *= Bracket4(p);
        } else {
            result /= Bracket4(p);
        }
    }
    return result;
}

double AddAndSubtract1(char **p) {
    double result = MultiplyAndDivide2(p);
    // 如果当前字符是'+'或'-'，则处理加法或减法运算
    while (**p == '+' || **p == '-') {
        if (*(*p)++ == '+') {
            result += MultiplyAndDivide2(p);
        } else {
            result -= MultiplyAndDivide2(p);
        }
    }
    return result;
}

int main() {
    char buffer[LENGTH];
    // 从标准输入读取每行表达式，并计算结果
    printf("输入一行表达式，按下Enter键结束程序\n");
    while (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
        char *p = buffer;
        printf("%.10g\n", AddAndSubtract1(&p));
        printf("再输入一行表达式，按下Enter键结束程序\n");
    }
    printf("再见");
    return 0;
}
/*by MO
**2023/11/20
*/
