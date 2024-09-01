#ifndef CALCULATOR_H
#define CALCULATOR_H

//��������ʵ�ֵ�ջ
//#include "LinkedStack.h"

//������̬����ʵ�ֵķ���ջ
#include "Generic_Stack.h"

//����ģʽ
#define DEBUG 0

//������ʽ��󳤶�
#define EXPRESSION_MAX_SIZE 100
// ���֧�ּ���ı��ʽ����
#define MAX_EXPRESSIONS 1000 

// ����������Ľṹ�嶨��
typedef struct {
    char* pExp; // �洢���ʽ���ַ���
    double result; // �洢������
} Calculator;

Calculator* Calculator_Construct();
/* ������Calculator_Construct
 * ---------------------------
 * ����������һ���µļ���������
 *
 * ����ֵ��ָ���´����ļ����������ָ�롣
 */

void Calculator_Destruct(Calculator* pCalculator);
/* ������Calculator_Destruct
 * --------------------------
 * ����ָ���ļ���������
 *
 * pCalculator: ָ��Ҫ���ٵļ����������ָ�롣
 */

void Calculator_InputExpression(Calculator* pCalculator);
/* ������Calculator_InputExpression
 * ---------------------------------
 * �ӱ�׼�����ȡ���ʽ������洢�ڼ����������С�
 *
 * pCalculator: ָ������������ָ�롣
 */

double Calculator_OutputResult(Calculator* pCalculator);
/* ������Calculator_OutputResult
 * ------------------------------
 * ����洢�ڼ����������еı��ʽ�������ؽ����
 *
 * pCalculator: ָ������������ָ�롣
 *
 * ����ֵ����������
 */

Bool Calculator_isSpace(char c);
/* ������Calculator_isSpace
 * -------------------------
 * �ж�ָ���ַ��Ƿ�Ϊ�ո�
 *
 * c: Ҫ�жϵ��ַ���
 *
 * ����ֵ�����ָ���ַ�Ϊ�ո񣬷���TRUE�����򷵻�FALSE��
 */

Bool Calculator_isUnaryOperator(const char c);
/* ������Calculator_isUnaryOperator
 * --------------------------------
 * �ж�ָ���ַ��Ƿ�ΪһԪ�������
 *
 * c: Ҫ�жϵ��ַ���
 *
 * ����ֵ�����ָ���ַ���һԪ�����������TRUE�����򷵻�FALSE��
 */

void Calculator_BatchCalculate(const char* inputFilePath, const char* outputFilePath);
/* ������Calculator_BatchCalculate
 * --------------------------------
 * ��ָ���ļ��ж�ȡ������ʽ������������д�뵽��һ���ļ��С�
 *
 * inputFilePath: ָ�����������ʽ���ļ���·����ָ�롣
 * outputFilePath: ָ��Ҫд����������ļ���·����ָ�롣
 */

int Calculator_getPriority(const char op);
/* ������Calculator_getPriority
 * -----------------------------
 * ��ȡָ������������ȼ���
 *
 * op: Ҫ��ȡ���ȼ����������
 *
 * ����ֵ��ָ������������ȼ���
 */

Bool Calculator_isDigit(char elem);
/* ������Calculator_isDigit
 * -------------------------
 * �ж�ָ���ַ��Ƿ�Ϊ���֡�
 *
 * elem: Ҫ�жϵ��ַ���
 *
 * ����ֵ�����ָ���ַ������֣�����TRUE�����򷵻�FALSE��
 */

Bool Calculator_isBinaryOperator(const char c);
/* ������Calculator_isBinaryOperator
 * ---------------------------------
 * �ж�ָ���ַ��Ƿ�Ϊ��Ԫ�������
 *
 * c: Ҫ�жϵ��ַ���
 *
 * ����ֵ�����ָ���ַ��Ƕ�Ԫ�����������TRUE�����򷵻�FALSE��
 */

double Calculator_convertToFloat(char str[]);
/* ������Calculator_convertToFloat
 * --------------------------------
 * ��ָ���ַ���ת��Ϊ��������
 *
 * str: Ҫת�����ַ�����
 *
 * ����ֵ��ת����ĸ�������
 */

Bool Calculator_IsValidExpression(const char str[]);
/* ������Calculator_IsValidExpression
 * ----------------------------------
 * �ж�ָ���ַ����Ƿ�Ϊ�Ϸ��ı��ʽ��
 *
 * str: Ҫ�жϵ��ַ�����
 *
 * ����ֵ�����ָ���ַ����ǺϷ��ı��ʽ������TRUE�����򷵻�FALSE��
 */

void Calculator_transform(char infix[], char postfix[], int n);
/* ������Calculator_transform
 * ---------------------------
 * ����׺���ʽת��Ϊ��׺���ʽ��
 *
 * infix: ָ����׺���ʽ���ַ�����ָ�롣
 * postfix: ָ���׺���ʽ���ַ�����ָ�롣
 * n: ��׺���ʽ�ַ����ĳ��ȡ�
 */

double Calculator_calculate(char postfix[]);
/* ������Calculator_calculate
 * ---------------------------
 * ����ָ���ĺ�׺���ʽ�������ؽ����
 *
 * postfix: ָ���׺���ʽ���ַ�����ָ�롣
 *
 * ����ֵ����������
 */


#endif
