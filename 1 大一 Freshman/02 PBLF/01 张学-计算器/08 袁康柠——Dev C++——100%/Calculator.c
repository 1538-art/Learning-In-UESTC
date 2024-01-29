#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Calculator.h"

// ���캯�������ڴ���һ���µļ���������
Calculator* Calculator_Construct() {
    Calculator* pCalculator = (Calculator*)malloc(sizeof(Calculator));
    if (pCalculator == NULL) {
        return NULL;
    }
    pCalculator->pExp = NULL;
    pCalculator->result = 0.0;
    return pCalculator;
}
// �ͷż������������Դ
void Calculator_Destruct(Calculator* pCalculator) {
    if (pCalculator->pExp != NULL) {
        free(pCalculator->pExp);
        pCalculator->pExp = NULL;
    }
    free(pCalculator);
}
// ������ʽ
void Calculator_InputExpression(Calculator* pCalculator) {
    char expression[EXPRESSION_MAX_SIZE+1];
    printf("Enter an arithmetic expression: ");
    
    fgets(expression, EXPRESSION_MAX_SIZE, stdin);
    // ȥ����׺���ʽ�еĻ��з�
    char lastchar = expression[strlen(expression) - 1];
    if (lastchar == '\n') {
        expression[strlen(expression) - 1] = '\0';
    }
    // ����洢���ʽ���ڴ�
    pCalculator->pExp = (char*)malloc(sizeof(strlen(expression) + 1));   
    strcpy(pCalculator->pExp, expression);
}
//��ȡ����������ȼ�
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
// �ж��ַ��Ƿ�Ϊ����
Bool Calculator_isDigit(char elem) {
    if (elem >= '0' && elem <= '9') {
        return TRUE;
    } else {
        return FALSE;
    }
}
// �ж�һ���ַ��Ƿ��ǿո�
Bool Calculator_isSpace(char c) {
    if(c == ' ' || c == '\t' || c == '\r' || c == '\n'){
		return TRUE;
	}else{
		return FALSE;
	}
}
// �ж��ַ��Ƿ�Ϊ˫Ŀ�����
Bool Calculator_isBinaryOperator(const char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return TRUE;
    } else {
        return FALSE;
    }
}
// �ж��ַ��Ƿ�Ϊ��Ŀ�����
Bool Calculator_isUnaryOperator(const char c) {
    if (c == 's' || c == 'c' || c == 't' || c == 'a'||
		c == 'b' || c == 'g' ){
        return TRUE;
    } else {
        return FALSE;
    }
}
// ���ַ���ת��Ϊ������
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
//�ж��û�����ı��ʽ�Ƿ�Ϸ�
Bool Calculator_IsValidExpression(const char str[]){
	return TRUE;
}
// ����׺���ʽת��Ϊ��׺���ʽ
void Calculator_transform(char infix[], char postfix[], int n) {
    Stack* pOperator;
    pOperator = Stack_Construct(sizeof(char));//���첢��ʼ��һ�������ջ
    
	int i = 0, j = 0;
    while (infix[i] != '\0') {
        //�������ֺ�С����
		if (Calculator_isDigit(infix[i]) || infix[i] == '.') {
            while (Calculator_isDigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
        } 
		//����˫Ŀ�����
		else if (Calculator_isBinaryOperator(infix[i])) {
        	//����������
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
		//����Ŀ�����
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
		//����������
		else if (infix[i] == '(') {
            char op = infix[i++];
            Stack_Push(pOperator, &op);
        } 
		//����������
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
        // ��Ӷ� postfix ���鳤�ȵļ��
		else if (j >= n - 2) {  // ��������λ�ø��ո���ַ���������
		    printf("postfix ���鳬����󳤶ȣ�\n");
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
    postfix[j] = '\0';//����ַ���������־
    Stack_Destroy(pOperator);//����ջ���ͷ��ڴ�
    
	#if DEBUG
	    printf("����ģʽ: ��׺���ʽתΪ��׺���ʽ\n");
	    printf("��׺���ʽ: %s\n", infix);
	    printf("ת����ĺ�׺���ʽ: %s\n", postfix);
	#endif
}
// �����׺���ʽ��ֵ
double Calculator_calculate(char postfix[]) {
    Stack* pOperand;
    pOperand = Stack_Construct(sizeof(double));//���첢��ʼ��һ��������ջ
    
	int i = 0;
    while (postfix[i] != '\0') {
        //����������ջ
		if (Calculator_isDigit(postfix[i])) {
            char num[EXPRESSION_MAX_SIZE];//����һ��������ʱ��Ų��������ַ�������
            int j = 0;
            while (Calculator_isDigit(postfix[i]) || postfix[i] == '.') {
                num[j++] = postfix[i++];
            }
            num[j] = '\0';
            double value = Calculator_convertToFloat(num);//�������ַ���ת��Ϊ������
            Stack_Push(pOperand, &value);//����������ջ
        } 
		//�����ո�������
		else if (postfix[i] == ' ') {
            i++;
        } 
		//����˫Ŀ��������򵯳�������������������Ӧ������
		else if (Calculator_isBinaryOperator(postfix[i])) {
    		double operand2, operand1, result;
			
			Stack_Pop(pOperand, &operand2);//��������������
            Stack_Pop(pOperand, &operand1);
            //��������������������
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
            	Stack_Push(pOperand, &result);//����������ջ	
        } 
		//������Ŀ��������򵯳�һ����������������Ӧ������
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
			Stack_Push(pOperand, &result);//����������ջ
		}
		
    }
    double finalResult;
    Stack_Pop(pOperand, &finalResult);//��ջ�����һ������������Ϊ���ս��
    Stack_Destroy(pOperand);//����ջ���ͷ��ڴ�
    
	#if DEBUG
       printf("����ģʽ: ��׺���ʽ����\n");
       printf("��׺���ʽ: %s\n", postfix);
       printf("������: %lf\n", finalResult);
	#endif
    
	return finalResult;
}
// ��ȡ�ļ��еı��ʽ�����м��㣬�������д����һ���ļ���
void Calculator_BatchCalculate(const char* inputFilePath, const char* outputFilePath) {
    char expressions[MAX_EXPRESSIONS][EXPRESSION_MAX_SIZE];
    double results[MAX_EXPRESSIONS];
    int numExpressions = 0;

    // ���ļ��ж�ȡ���ʽ
    FILE* inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL) {
        printf("�޷��������ļ�: %s\n", inputFilePath);
        return;
    }
    while (fgets(expressions[numExpressions], EXPRESSION_MAX_SIZE, inputFile) != NULL) {
        // ȥ�������еĿո�ͻ��з�
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

    // ��ÿ�����ʽ���м���
    for (int i = 0; i < numExpressions; i++) {
        if (!Calculator_IsValidExpression(expressions[i])) {
            printf("���ʽ %s ���Ϸ�\n", expressions[i]);
            results[i] = NAN;
            continue;
        }
        char postfix[EXPRESSION_MAX_SIZE];    
		Calculator_transform(expressions[i],postfix,EXPRESSION_MAX_SIZE);
        results[i] = Calculator_calculate(postfix);
    }

    // ��������д���ļ�
    FILE* outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        printf("�޷�������ļ�: %s\n", outputFilePath);
        return;
    }
    for (int i = 0; i < numExpressions; i++) {
        fprintf(outputFile, "%lf\n", results[i]);
    }
    fclose(outputFile);

    printf("������ɣ��������� %d �����ʽ��\n", numExpressions);
    printf("�������ѱ������ļ� %s �С�\n", outputFilePath);
}
// ���������
double Calculator_OutputResult(Calculator* pCalculator) {
    char postfix[EXPRESSION_MAX_SIZE];
    
    Calculator_transform(pCalculator->pExp,postfix,EXPRESSION_MAX_SIZE);
    pCalculator->result = Calculator_calculate(postfix);
	return pCalculator->result;
}
