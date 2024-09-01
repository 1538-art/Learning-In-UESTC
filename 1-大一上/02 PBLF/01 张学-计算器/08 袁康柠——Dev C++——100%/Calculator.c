#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Calculator.h"

// 构造函数，用于创建一个新的计算器对象
Calculator* Calculator_Construct() {
    Calculator* pCalculator = (Calculator*)malloc(sizeof(Calculator));
    if (pCalculator == NULL) {
        return NULL;
    }
    pCalculator->pExp = NULL;
    pCalculator->result = 0.0;
    return pCalculator;
}
// 释放计算器对象的资源
void Calculator_Destruct(Calculator* pCalculator) {
    if (pCalculator->pExp != NULL) {
        free(pCalculator->pExp);
        pCalculator->pExp = NULL;
    }
    free(pCalculator);
}
// 输入表达式
void Calculator_InputExpression(Calculator* pCalculator) {
    char expression[EXPRESSION_MAX_SIZE+1];
    printf("Enter an arithmetic expression: ");
    
    fgets(expression, EXPRESSION_MAX_SIZE, stdin);
    // 去除中缀表达式中的换行符
    char lastchar = expression[strlen(expression) - 1];
    if (lastchar == '\n') {
        expression[strlen(expression) - 1] = '\0';
    }
    // 分配存储表达式的内存
    pCalculator->pExp = (char*)malloc(sizeof(strlen(expression) + 1));   
    strcpy(pCalculator->pExp, expression);
}
//获取运算符的优先级
int Calculator_getPriority(const char op) {
    if (op == '(') {
        return 1;
    } else if (op == '+' || op == '-') {
        return 2;
    } else if (op == '*' || op == '/') {
        return 3;
    } else if (op == '^' ){
			return 4;
    } else if (op == 's' || op == 'c' || op == 't' ||
    		   op == 'a' || op == 'b' || op == 'g') {
        	return 5;
    }
    return 0;
}
// 判断字符是否为数字
Bool Calculator_isDigit(char elem) {
    if (elem >= '0' && elem <= '9') {
        return TRUE;
    } else {
        return FALSE;
    }
}
// 判断一个字符是否是空格
Bool Calculator_isSpace(char c) {
    if(c == ' ' || c == '\t' || c == '\r' || c == '\n'){
		return TRUE;
	}else{
		return FALSE;
	}
}
// 判断字符是否为双目运算符
Bool Calculator_isBinaryOperator(const char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return TRUE;
    } else {
        return FALSE;
    }
}
// 判断字符是否为单目运算符
Bool Calculator_isUnaryOperator(const char c) {
    if (c == 's' || c == 'c' || c == 't' || c == 'a'||
		c == 'b' || c == 'g' ){
        return TRUE;
    } else {
        return FALSE;
    }
}
// 将字符串转换为浮点数
double Calculator_convertToFloat(char str[]) {
    double result = 0.0;
    double weight= 1.0;
    int i = 0;

    while (str[i] != '\0' && str[i] != '.') {
        if (Calculator_isDigit(str[i])) {
            result = result * 10.0 + (str[i] - '0');
            i++;
        } else {
            exit(1);
        }
    }

    if (str[i] == '.') {
        i++;
        while (str[i] != '\0') {
            if (Calculator_isDigit(str[i])) {
                weight *= 0.1;
                result += (str[i] - '0') * weight;
                i++;
            } else {
                exit(1);
            }
        }
    }

    return result;
}
//判断用户输入的表达式是否合法
Bool Calculator_IsValidExpression(const char str[]){
	return TRUE;
}
// 将中缀表达式转换为后缀表达式
void Calculator_transform(char infix[], char postfix[], int n) {
    Stack* pOperator;
    pOperator = Stack_Construct(sizeof(char));//构造并初始化一个运算符栈
    
	int i = 0, j = 0;
    while (infix[i] != '\0') {
        //处理数字和小数点
		if (Calculator_isDigit(infix[i]) || infix[i] == '.') {
            while (Calculator_isDigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
        } 
		//处理双目运算符
		else if (Calculator_isBinaryOperator(infix[i])) {
        	//处理正负号
			if (infix[i] == '+' || infix[i] == '-') {
			    if (i == 0 || infix[i - 1] == '(') {
			        postfix[j++] = '0';
			        postfix[j++] = ' ';
			    }
			}		
			while (!Stack_IsEmpty(pOperator)) {                
				char top;
                Stack_GetTop(pOperator, &top);
                if (Calculator_getPriority(top) >= Calculator_getPriority(infix[i])) {
                    Stack_Pop(pOperator, &top);
                    postfix[j++] = top;
                    postfix[j++] = ' ';
                } else {
                    break;
                }
            }
            char op = infix[i++];
            Stack_Push(pOperator, &op);
        } 
		//处理单目运算符
		else if(Calculator_isUnaryOperator(infix[i])){
							
			
			if(infix[i] == 'a' && infix[i+3] == 'c'){
				infix[i] = 'b';
			}else if(infix[i] == 'a' && infix[i+3] == 't'){
				infix[i] ='g';	
			}
			while (!Stack_IsEmpty(pOperator)) {                
				char top;
                Stack_GetTop(pOperator, &top);
                if (Calculator_getPriority(top) >= Calculator_getPriority(infix[i])) {
                    Stack_Pop(pOperator, &top);
                    postfix[j++] = top;
                    postfix[j++] = ' ';
                } else {
                    break;
                }
            }
            Stack_Push(pOperator, &infix[i]);
            			
			if(infix[i] == 's' || infix[i] == 'c' ||infix[i] == 't' ||
			   infix[i] == 'l' ){
			   	i+=3;
			}else if(infix[i] == 'a' || infix[i] == 'b' || infix[i] == 'g'){
			   	i+=6;
			}else{
				i+=1;
			}	
		}
		//处理左括号
		else if (infix[i] == '(') {
            char op = infix[i++];
            Stack_Push(pOperator, &op);
        } 
		//处理右括号
		else if (infix[i] == ')') {
            while (!Stack_IsEmpty(pOperator)) {
                char top;
                Stack_GetTop(pOperator, &top);
                if (top != '(') {
                    Stack_Pop(pOperator, &top);
                    postfix[j++] = top;
                    postfix[j++] = ' ';
                } else {
                    break;
                }
            }
            if (Stack_IsEmpty(pOperator)) {
                exit(1);
            }
            char left_paren;
            Stack_Pop(pOperator, &left_paren);
            i++;
        }
        // 添加对 postfix 数组长度的检查
		else if (j >= n - 2) {  // 留出两个位置给空格和字符串结束符
		    printf("postfix 数组超过最大长度！\n");
		    break;
		}
		else{
			i++;
		} 
    }
    while (!Stack_IsEmpty(pOperator)) {
        char top;
        Stack_Pop(pOperator, &top);
        postfix[j++] = top;
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';//添加字符串结束标志
    Stack_Destroy(pOperator);//销毁栈并释放内存
    
	#if DEBUG
	    printf("调试模式: 中缀表达式转为后缀表达式\n");
	    printf("中缀表达式: %s\n", infix);
	    printf("转换后的后缀表达式: %s\n", postfix);
	#endif
}
// 计算后缀表达式的值
double Calculator_calculate(char postfix[]) {
    Stack* pOperand;
    pOperand = Stack_Construct(sizeof(double));//构造并初始化一个操作数栈
    
	int i = 0;
    while (postfix[i] != '\0') {
        //将操作数入栈
		if (Calculator_isDigit(postfix[i])) {
            char num[EXPRESSION_MAX_SIZE];//定义一个用于临时存放操作数的字符串数组
            int j = 0;
            while (Calculator_isDigit(postfix[i]) || postfix[i] == '.') {
                num[j++] = postfix[i++];
            }
            num[j] = '\0';
            double value = Calculator_convertToFloat(num);//将数字字符串转变为浮点数
            Stack_Push(pOperand, &value);//将浮点数入栈
        } 
		//遇到空格则跳过
		else if (postfix[i] == ' ') {
            i++;
        } 
		//遇到双目运算符，则弹出两个操作数，进行相应的运算
		else if (Calculator_isBinaryOperator(postfix[i])) {
    		double operand2, operand1, result;
			
			Stack_Pop(pOperand, &operand2);//弹出两个操作数
            Stack_Pop(pOperand, &operand1);
            //将两个操作数进行运算
			char op = postfix[i++];
			switch (op) {
				case '+':
                   	result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                       	exit(1);
                    }
                   	result = operand1 / operand2;
                   	break;
               	case '^':
               		result = pow(operand1,operand2);
               		break;
				default:
                   	exit(1);
            }
            	Stack_Push(pOperand, &result);//将运算结果入栈	
        } 
		//遇到单目运算符，则弹出一个操作数，进行相应的运算
		else if(Calculator_isUnaryOperator(postfix[i])){
			double operand1, result;
			
			Stack_Pop(pOperand, &operand1);
			
			char op = postfix[i++];
		    switch (op) {
			case 's':
				result = sin(operand1);
				break;
			case 'c':
				result = cos(operand1);
			    break;
			case 't':
				result = tan(operand1);
			    break;
			case 'a':
			    result = asin(operand1);
			    break;
			case 'b':
				result = acos(operand1);
				break;
			case 'g':
				result = atan(operand1);
				break;
			case 'l':
				result = log10(operand1);
				break;
			default:
				exit(1);
			}
			Stack_Push(pOperand, &result);//将运算结果入栈
		}
		
    }
    double finalResult;
    Stack_Pop(pOperand, &finalResult);//将栈中最后一个数弹出，即为最终结果
    Stack_Destroy(pOperand);//销毁栈并释放内存
    
	#if DEBUG
       printf("调试模式: 后缀表达式计算\n");
       printf("后缀表达式: %s\n", postfix);
       printf("运算结果: %lf\n", finalResult);
	#endif
    
	return finalResult;
}
// 读取文件中的表达式，进行计算，并将结果写入另一个文件中
void Calculator_BatchCalculate(const char* inputFilePath, const char* outputFilePath) {
    char expressions[MAX_EXPRESSIONS][EXPRESSION_MAX_SIZE];
    double results[MAX_EXPRESSIONS];
    int numExpressions = 0;

    // 从文件中读取表达式
    FILE* inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL) {
        printf("无法打开输入文件: %s\n", inputFilePath);
        return;
    }
    while (fgets(expressions[numExpressions], EXPRESSION_MAX_SIZE, inputFile) != NULL) {
        // 去除数组中的空格和换行符
        int len = strlen(expressions[numExpressions]);
        while (len > 0 && Calculator_isSpace(expressions[numExpressions][len - 1])) {
            expressions[numExpressions][len - 1] = '\0';
            len--;
        }
        numExpressions++;
        if (numExpressions >= MAX_EXPRESSIONS) {
            break;
        }
    }
    fclose(inputFile);

    // 对每个表达式进行计算
    for (int i = 0; i < numExpressions; i++) {
        if (!Calculator_IsValidExpression(expressions[i])) {
            printf("表达式 %s 不合法\n", expressions[i]);
            results[i] = NAN;
            continue;
        }
        char postfix[EXPRESSION_MAX_SIZE];    
		Calculator_transform(expressions[i],postfix,EXPRESSION_MAX_SIZE);
        results[i] = Calculator_calculate(postfix);
    }

    // 将计算结果写入文件
    FILE* outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        printf("无法打开输出文件: %s\n", outputFilePath);
        return;
    }
    for (int i = 0; i < numExpressions; i++) {
        fprintf(outputFile, "%lf\n", results[i]);
    }
    fclose(outputFile);

    printf("计算完成，共计算了 %d 个表达式。\n", numExpressions);
    printf("计算结果已保存在文件 %s 中。\n", outputFilePath);
}
// 输出计算结果
double Calculator_OutputResult(Calculator* pCalculator) {
    char postfix[EXPRESSION_MAX_SIZE];
    
    Calculator_transform(pCalculator->pExp,postfix,EXPRESSION_MAX_SIZE);
    pCalculator->result = Calculator_calculate(postfix);
	return pCalculator->result;
}
