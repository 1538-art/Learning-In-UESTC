#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Caculator.h"

//����ģʽ
#define DEBUG 0

//������ʽ��󳤶�
#define EXPRESSION_SIZE 1000 
// ���֧�ּ���ı��ʽ����
#define MAX_EXPRESSIONS 1000 


//��ȡ����������ȼ�
int GetPriority(const char op) {
    if (op == '(') {
        return 1;
    } else if (op == '+' || op == '-') {
        return 2;
    } else if (op == '*' || op == '/') {
        return 3;
    } else if(op == '^'){
	    return 4;
    } else if (op == 's' || op == 'c' || op == 't' ||
    		   op == 'a' || op == 'b' || op == 'g' ||
			   op == 'l' ) {
        return 5;
    }
    return 0;
}

// �ж��ַ��Ƿ�Ϊ����
Bool IsDigit(char elem) {
    if (elem >= '0' && elem <= '9') {
        return TRUE;
    } else {
        return FALSE;
    }
}

// �ж�һ���ַ��Ƿ��ǿո�
int IsSpace(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

// �ж��ַ��Ƿ�Ϊ˫Ŀ�����
Bool IsBinaryOperator(const char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return TRUE;
    } else {
        return FALSE;
    }
}

// �ж��ַ��Ƿ�Ϊ��Ŀ�����
Bool IsUnaryOperator(const char c) {
    if (c == 's' || c == 'c' || c == 't' || c == 'a'||
		c == 'b' || c == 'g' || c == 'l' ){
        return TRUE;
    } else {
        return FALSE;
    }
}

// ���ַ���ת��Ϊ������
double ConvertToFloat(char str[]) {
    double result = 0.0;
    double weight= 1.0;
    int i = 0;

    while (str[i] != '\0' && str[i] != '.') {
        if (IsDigit(str[i])) {
            result = result * 10.0 + (str[i] - '0');
            i++;
        } else {
            exit(1);
        }
    }

    if (str[i] == '.') {
        i++;
        while (str[i] != '\0') {
            if (IsDigit(str[i])) {
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
Bool IsValidExpression(const char str[]) {
    return TRUE; 
}

// ����׺���ʽת��Ϊ��׺���ʽ
void InfixToSuffix(char infix[], char postfix[]) {
    Stack* pOperator;
    pOperator = Stack_Construct(sizeof(char));//���첢��ʼ��һ�������ջ
    
	int i = 0, j = 0;
    while (infix[i] != '\0') {
        //�������ֺ�С����
		if (IsDigit(infix[i]) || infix[i] == '.') {
            while (IsDigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
        } 
		//����˫Ŀ�����
		else if (IsBinaryOperator(infix[i])) {
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
                if (GetPriority(top) >= GetPriority(infix[i])) {
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
		else if(IsUnaryOperator(infix[i])){
			if(infix[i] == 'a' && infix[i+3] == 'c'){
				infix[i] = 'b';
			}else if(infix[i] == 'a' && infix[i+3] == 't'){
				infix[i] ='g';	
			}else if(infix[i] == '\x1A'){
				infix[i] ='r';
			}
			while (!Stack_IsEmpty(pOperator)) {                
				char top;
                Stack_GetTop(pOperator, &top);
                if (GetPriority(top) >= GetPriority(infix[i])) {
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
double Calculate(char postfix[]) {
    Stack* pOperand;
    pOperand = Stack_Construct(sizeof(double));//���첢��ʼ��һ��������ջ
    
	int i = 0;
    while (postfix[i] != '\0') {
        //����������ջ
		if (IsDigit(postfix[i])) {
            char num[EXPRESSION_SIZE];//����һ��������ʱ��Ų��������ַ�������
            int j = 0;
            while (IsDigit(postfix[i]) || postfix[i] == '.') {
                num[j++] = postfix[i++];
            }
            num[j] = '\0';
            double value = ConvertToFloat(num);//�������ַ���ת��Ϊ������
            Stack_Push(pOperand, &value);//����������ջ
        } 
		//�����ո�������
		else if (postfix[i] == ' ') {
            i++;
        } 
		//����˫Ŀ��������򵯳�������������������Ӧ������
		else if (IsBinaryOperator(postfix[i])) {
           
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
				    result = pow(operand1, operand2);
				    break;
               	default:
                   	exit(1);
            }
            	Stack_Push(pOperand, &result);//����������ջ	
        } 
		else if(IsUnaryOperator(postfix[i])){
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
			case 'r':
				result = sqrt(operand1);
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

//���м���������ʽ�ļ��㲢���ؽ����
Status Stdin_Caculate(void){

    char infix[EXPRESSION_SIZE];
    char postfix[EXPRESSION_SIZE];
    printf("Enter an arithmetic expression: ");
    fgets(infix, EXPRESSION_SIZE, stdin);

    // ȥ����׺���ʽ�еĻ��з�
    char lastchar = infix[strlen(infix) - 1];
    if (lastchar == '\n') {
        infix[strlen(infix) - 1] = '\0';
    }

    // �ж��û�����ı��ʽ�Ƿ�Ϸ�	
    if (!IsValidExpression(infix)) {
        printf("����ı��ʽ���Ϸ���\n");
    } else {
        // ������ʽ���
        InfixToSuffix(infix, postfix);
        double result =Calculate(postfix);
        printf("Result: %lf\n", result);
    } 
	return OK;

}

// ��ȡ�ļ��еı��ʽ�������������㣬�������д����һ���ļ���
void Batch_calculate(const char* inputFilePath, const char* outputFilePath) {
    char expressions[MAX_EXPRESSIONS][EXPRESSION_SIZE];
    double results[MAX_EXPRESSIONS];
    int numExpressions = 0;

    // ���ļ��ж�ȡ���ʽ
    FILE* inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL) {
        printf("�޷��������ļ�: %s\n", inputFilePath);
        return;
    }
    while (fgets(expressions[numExpressions], EXPRESSION_SIZE, inputFile) != NULL) {
        
		// ȥ�����ʽ�еĿո�ͻ��з�
        int len = strlen(expressions[numExpressions]);
        while (len > 0 && IsSpace(expressions[numExpressions][len - 1])) {
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
    int i = 0;
    for (i = 0; i < numExpressions; i++) {
        char postfix[EXPRESSION_SIZE];
        InfixToSuffix(expressions[i], postfix);
        results[i] = Calculate(postfix);
    }

    // ��������д���ļ�
    FILE* outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        printf("�޷�������ļ�: %s\n", outputFilePath);
        return;
    }
    
    for (i = 0; i < numExpressions; i++) {
        fprintf(outputFile, "%lf\n", results[i]);
    }
    fclose(outputFile);

    printf("������ɣ��������� %d �����ʽ��\n", numExpressions);
    printf("�������������ļ�%s��",outputFilePath);
}

//��������
Status Batch_Caculate() {
	char sFilename[EXPRESSION_SIZE];
        printf("������Ҫ����������ļ���:\n");
        scanf("%s", sFilename);
        FILE* file = fopen(sFilename, "r");
        if (file == NULL) {
            printf("�޷����ļ� %s\n", sFilename);
            return ERROR;
        }
    Batch_calculate(sFilename , "output.txt");
}
