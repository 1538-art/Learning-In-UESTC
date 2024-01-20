#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <ctype.h>
#include "SuperStack.h"

#define MAX_SIZE 100
/*输入表达式的最大容量*/ 
#define PI 3.14


int IsOperator(char c);
/*函数功能：判断读取到的元素是否是操作符 
 *输入参数：读取的字符c 
 *返回值：该字符是操作符返回0，否则返回-1 
 */
int Precedence(char op);
/*函数功能：返回操作符优先级 
 *输入参数：操作符op 
 *返回值：符号级别 
 */
double Evaluate(char *pArray);
/*函数功能：计算四则运算表达式 
 *输入参数：指向计算的表达式的指针pArray 
 *返回值：四则运算表达式的值 
 */
void AddZero(char *infix, char *newInfix); 
/*函数功能：在表达式的负号前面添0并生成一个新的表达式
 *输入参数：原始的表达式的指针infix，新的表达式的指针newInfix 
 *返回值：无
 */ 
double Power(double m, double n);
/*函数功能：乘方函数
 *输入参数：底数m；指数n
 *返回值：m的n次方
 */


int IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/'||c=='^';
}


int Precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/'||op=='^') {
        return 2;
    } else {
        return 0;
    }
}

double Power(double m, double n){
	int i = 1;
	double result = 1;
	if (n == 0){
		return result;
	}
	for (i = 1; i <= n; i++){
		result *= m;
	}
	return result;
	#if DEBUG
    printf("the result is%f",result);
    #endif // DEBUG
}

double Evaluate(char *pArray) {
	char topEle;
	double a,b;
	double result,result1;
	
    Stack *operand_stack;
	operand_stack=Stack_Construct(sizeof(double));
    Stack *operator_stack;
	operator_stack=Stack_Construct(sizeof(char)); 
    

    while (*pArray != '\0') {
//如果读取到数字和小数点，用strtod函数将这一串含数字和小数点的字符传换成浮点数 
//使用digit函数判断十进制数字字符 
        if (isdigit(*pArray) || *pArray == '.') {
            double value = strtod(pArray, &pArray);            
			Stack_Push(operand_stack, &value);
        } 
		else if (IsOperator(*pArray)) {
//当操作符栈栈顶元素优先级大于等于读取到的符号优先级时，弹出操作符栈栈顶元素，并弹出操作数栈中的两个浮点数 
            Stack_GetTop(operator_stack,&topEle);
            while (!Stack_IsEmpty(operator_stack) && Precedence(topEle) >= Precedence(*pArray)) {
            	Stack_Pop(operator_stack,&topEle);
                char op = topEle;
                Stack_Pop(operand_stack,&a);
                Stack_Pop(operand_stack,&b);
//判断符号后，将两个浮点数运算后的结果重新压入操作数栈中 
                switch (op) {
                    case '+':
                    	result=a+b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '-':
                    	result=a-b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '*':
                    	result=a*b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '/':
                    	result=a/b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '^':
					    result=Power(b, a);
						Stack_Push(operand_stack, &result);
						break;    
                }
            }
//当操作符栈栈顶元素优先级小于读取到的符号优先级时，将读取到的符号直接压入操作符栈中            
            Stack_Push(operator_stack, pArray);
            pArray++;
        }
        //识别到三角函数直接进行计算        
        else if (*pArray == 's'){
        	pArray=pArray+3;
        	double value1 = strtod(pArray, &pArray);
        	value1=value1/180*PI;
			value1=sin(value1);       
			Stack_Push(operand_stack, &value1);
		}
		else if (*pArray == 'c'){
        	pArray=pArray+3;
        	double value1 = strtod(pArray, &pArray);
        	value1=value1/180*PI;
			value1=cos(value1);       
			Stack_Push(operand_stack, &value1);
		}
		else if (*pArray == 't'){
        	pArray=pArray+3;
        	double value1 = strtod(pArray, &pArray);
        	value1=value1/180*PI;
			value1=tan(value1);       
			Stack_Push(operand_stack, &value1);
		}
//识别到反三角函数直接进行计算 
		else if(*pArray=='a'&&*(pArray+3)=='s'){
			pArray=pArray+6;
        	double value1 = strtod(pArray, &pArray);
			value1=asin(value1);       
			Stack_Push(operand_stack, &value1);
		}
		else if(*pArray=='a'&&*(pArray+3)=='c'){
			pArray=pArray+6;
        	double value1 = strtod(pArray, &pArray);
			value1=acos(value1);       
			Stack_Push(operand_stack, &value1);
		}
		else if(*pArray=='a'&&*(pArray+3)=='t'){
			pArray=pArray+6;
        	double value1 = strtod(pArray, &pArray);
			value1=atan(value1);       
			Stack_Push(operand_stack, &value1);
		}
		
//读到左括号，直接压入栈操作符栈 
		else if (*pArray == '(') {
            Stack_Push(operator_stack, pArray);
            pArray++;
        } 
		else if (*pArray == ')') {
//读到右括号，当操作符栈栈顶元素不是左括号时，操作符栈栈顶元素弹出，操作数栈弹出两个浮点数进行运算并压入操作数栈中
            Stack_GetTop(operator_stack,&topEle);
            while (topEle != '(') {
                Stack_Pop(operator_stack,&topEle);
                char op = topEle;
                Stack_Pop(operand_stack,&a);
                Stack_Pop(operand_stack,&b);
                switch (op) {
                    case '+':
                    	result=a+b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '-':
                    	result=a-b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '*':
                    	result=a*b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '/':
                    	result=a/b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '^':
					    result=Power(b, a);
						Stack_Push(operand_stack, &result);
						break;        
            }
//读到右括号，当操作符栈栈顶元素是左括号时，栈顶元素直接弹出 
            Stack_Pop(operator_stack,&topEle);
            pArray++;
        }
    }
		else {
            pArray++;
        }
		
    }
//当操作符栈不为空时，弹出最后一个操作符和最后两个浮点数，将操作后的值返回 
    while (!Stack_IsEmpty(operator_stack)) {
        Stack_Pop(operator_stack,&topEle);
                char op = topEle;
                Stack_Pop(operand_stack,&a);
                Stack_Pop(operand_stack,&b);
                switch (op) {
                    case '+':
                    	result=a+b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '-':
                    	result=a-b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '*':
                    	result=a*b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '/':
                    	result=a/b;
                        Stack_Push(operand_stack, &result);
                        break;
                    case '^':
					    result=Power(b, a);
						Stack_Push(operand_stack, &result);
						break;        
        }
    }
    
     Stack_Pop(operand_stack,&result1);
     return result1;
}
void AddZero(char *infix, char *newInfix) {
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (infix[i] == '-') {
            if (i == 0 || infix[i - 1] == '(' || IsOperator(infix[i - 1])) {
                newInfix[j++] = '0';
            }
        }
        newInfix[j] = infix[i];
        j++;
        i++;
    }
    newInfix[j] = '\0';
}    

//主函数的一种实现： 
int main() {
    char infix[MAX_SIZE], newInfix[MAX_SIZE];
    printf("计算器使用提示:\n1.支持的运算符：+、-、*、/、^、sin、cos、tan、arcsin、arccos、arctan\n2.支持的操作数：整数、小数、负数\n3.使用三角函数时请输入角度制，eg：sin60表示60°角的正弦值\n");
    printf("Enter an expression: ");
    while(scanf("%s",infix)!=EOF){
    	AddZero(infix, newInfix);
        printf("Result: %g\n", Evaluate(newInfix));
        printf("Enter an expression again:" );
	}
    return 0;
}

/*
int main() {
    FILE *input_file1 = fopen("input1.txt", "r");//打开输入文件 
    FILE *output_file1 = fopen("output1.txt", "w");//打开输出文件 

    if (input_file1 == NULL) {//判断输入文件是否打开成功 
        printf("Failed to open input file.\n");
        exit(EXIT_FAILURE);
    }

    if (output_file1 == NULL) {//判断输出文件是否打开成功 
        printf("Failed to open output file.\n");
        exit(EXIT_FAILURE);
    }

    char infix[MAX_SIZE], newInfix[MAX_SIZE];
    while (fgets(infix, MAX_SIZE, input_file1) != NULL) {
    	AddZero(infix, newInfix);//将原表达式中的负号添0转化为减号 
        double result = Evaluate(newInfix);//计算添0后的表达式 
        fprintf(output_file1, "%g\n", result);//将每个表达式的结果串到输出文件 
    }

    fclose(input_file1);//关闭输入文件 
    fclose(output_file1);//关闭输出文件 

    return 0;
}*/
