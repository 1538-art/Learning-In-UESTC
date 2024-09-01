#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <ctype.h>
#include "SuperStack.h"

#define MAX_SIZE 100
/*������ʽ���������*/ 
#define PI 3.14


int IsOperator(char c);
/*�������ܣ��ж϶�ȡ����Ԫ���Ƿ��ǲ����� 
 *�����������ȡ���ַ�c 
 *����ֵ�����ַ��ǲ���������0�����򷵻�-1 
 */
int Precedence(char op);
/*�������ܣ����ز��������ȼ� 
 *���������������op 
 *����ֵ�����ż��� 
 */
double Evaluate(char *pArray);
/*�������ܣ���������������ʽ 
 *���������ָ�����ı��ʽ��ָ��pArray 
 *����ֵ������������ʽ��ֵ 
 */
void AddZero(char *infix, char *newInfix); 
/*�������ܣ��ڱ��ʽ�ĸ���ǰ����0������һ���µı��ʽ
 *���������ԭʼ�ı��ʽ��ָ��infix���µı��ʽ��ָ��newInfix 
 *����ֵ����
 */ 
double Power(double m, double n);
/*�������ܣ��˷�����
 *�������������m��ָ��n
 *����ֵ��m��n�η�
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
//�����ȡ�����ֺ�С���㣬��strtod��������һ�������ֺ�С������ַ������ɸ����� 
//ʹ��digit�����ж�ʮ���������ַ� 
        if (isdigit(*pArray) || *pArray == '.') {
            double value = strtod(pArray, &pArray);            
			Stack_Push(operand_stack, &value);
        } 
		else if (IsOperator(*pArray)) {
//��������ջջ��Ԫ�����ȼ����ڵ��ڶ�ȡ���ķ������ȼ�ʱ������������ջջ��Ԫ�أ�������������ջ�е����������� 
            Stack_GetTop(operator_stack,&topEle);
            while (!Stack_IsEmpty(operator_stack) && Precedence(topEle) >= Precedence(*pArray)) {
            	Stack_Pop(operator_stack,&topEle);
                char op = topEle;
                Stack_Pop(operand_stack,&a);
                Stack_Pop(operand_stack,&b);
//�жϷ��ź󣬽����������������Ľ������ѹ�������ջ�� 
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
//��������ջջ��Ԫ�����ȼ�С�ڶ�ȡ���ķ������ȼ�ʱ������ȡ���ķ���ֱ��ѹ�������ջ��            
            Stack_Push(operator_stack, pArray);
            pArray++;
        }
        //ʶ�����Ǻ���ֱ�ӽ��м���        
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
//ʶ�𵽷����Ǻ���ֱ�ӽ��м��� 
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
		
//���������ţ�ֱ��ѹ��ջ������ջ 
		else if (*pArray == '(') {
            Stack_Push(operator_stack, pArray);
            pArray++;
        } 
		else if (*pArray == ')') {
//���������ţ���������ջջ��Ԫ�ز���������ʱ��������ջջ��Ԫ�ص�����������ջ���������������������㲢ѹ�������ջ��
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
//���������ţ���������ջջ��Ԫ����������ʱ��ջ��Ԫ��ֱ�ӵ��� 
            Stack_Pop(operator_stack,&topEle);
            pArray++;
        }
    }
		else {
            pArray++;
        }
		
    }
//��������ջ��Ϊ��ʱ���������һ����������������������������������ֵ���� 
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

//��������һ��ʵ�֣� 
int main() {
    char infix[MAX_SIZE], newInfix[MAX_SIZE];
    printf("������ʹ����ʾ:\n1.֧�ֵ��������+��-��*��/��^��sin��cos��tan��arcsin��arccos��arctan\n2.֧�ֵĲ�������������С��������\n3.ʹ�����Ǻ���ʱ������Ƕ��ƣ�eg��sin60��ʾ60��ǵ�����ֵ\n");
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
    FILE *input_file1 = fopen("input1.txt", "r");//�������ļ� 
    FILE *output_file1 = fopen("output1.txt", "w");//������ļ� 

    if (input_file1 == NULL) {//�ж������ļ��Ƿ�򿪳ɹ� 
        printf("Failed to open input file.\n");
        exit(EXIT_FAILURE);
    }

    if (output_file1 == NULL) {//�ж�����ļ��Ƿ�򿪳ɹ� 
        printf("Failed to open output file.\n");
        exit(EXIT_FAILURE);
    }

    char infix[MAX_SIZE], newInfix[MAX_SIZE];
    while (fgets(infix, MAX_SIZE, input_file1) != NULL) {
    	AddZero(infix, newInfix);//��ԭ���ʽ�еĸ�����0ת��Ϊ���� 
        double result = Evaluate(newInfix);//������0��ı��ʽ 
        fprintf(output_file1, "%g\n", result);//��ÿ�����ʽ�Ľ����������ļ� 
    }

    fclose(input_file1);//�ر������ļ� 
    fclose(output_file1);//�ر�����ļ� 

    return 0;
}*/
