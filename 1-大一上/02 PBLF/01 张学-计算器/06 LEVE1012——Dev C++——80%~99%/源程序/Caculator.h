#ifndef CACULATOR_H
#define CACULATOR_H

//������ʽջ��ͷ�ļ�
//#include "Linked_Stack" 

//����ͨ��ջ��ͷ�ļ� 
#include "Generic_Stack.h"

int GetPriority(char op);
/* ������GetPriority
 * -----------------
 * ��ȡ�����������ȼ���
 *
 * op����������
 *
 * ����ֵ�������������ȼ���ֵԽ���ʾ���ȼ�Խ�ߡ�
 */

int IsSpace(char c);
/* ������IsSpace
 * --------------------
 * �ж��ַ��Ƿ�Ϊ�ո���Ʊ����
 *
 * c��Ҫ�жϵ��ַ���
 *
 * ����ֵ������ַ�Ϊ�ո���Ʊ�������� TRUE�����򷵻� FALSE��
 */
 
Bool IsDigit(char elem);
/* ������IsDigit
 * -------------
 * ����ַ��Ƿ�Ϊ���֡�
 *
 * elem���ַ���
 *
 * ����ֵ�����ַ�Ϊ���ַ���TRUE�����򷵻�FALSE��
 */

 Bool IsUnaryOperator(const char c);
/* ������IsUnaryOperator
 * ---------------------
 * �ж��ַ��Ƿ�Ϊ��Ŀ�������
 *
 * c��Ҫ�жϵ��ַ���
 *
 * ����ֵ������ַ�Ϊ��Ŀ����������� TRUE�����򷵻� FALSE��
 */

Bool IsBinaryOperator(const char c);
/* ������IsBinaryOperator
 * ----------------
 * ����ַ��Ƿ�Ϊ˫Ŀ�������
 *
 * c���ַ���
 *
 * ����ֵ�����ַ�Ϊ����������TRUE�����򷵻�FASLE��
 */

double ConvertToFloat(char str[]);
/* ������ConvertToFloat
 * --------------------
 * ���ַ���ת��Ϊ��������
 *
 * str���ַ�����
 *
 * ����ֵ��ת����ĸ�������
 */

Bool IsValidExpression(const char str[]);
/* ������IsValidExpression
 * --------------------
 * �ж��û�����ı��ʽ�Ƿ�Ϸ�
 *
 * str���ַ�����
 *
 * ����ֵ�����Ϸ�����TRUE�����򷵻�FASLE��
 */
 
void InfixToSuffix(char infix[], char postfix[]);
/* ������InfixToPostfix
 * --------------------
 * ����׺���ʽת��Ϊ��׺���ʽ��
 *
 * infix����׺���ʽ�ַ�����
 * postfix�����ڴ洢��׺���ʽ���ַ�����
 *
 * ����ֵ���ޡ�
 */

double Calculate(char suffix[]);
/* ������Calculate
 * ---------------------
 * �����׺���ʽ�����ؽ����
 *
 * suffix����׺���ʽ 
 *
 * ����ֵ����׺���ʽ�ļ��������Ը�������ʽ���ء�
 */
 
Status Stdin_Caculate(void);
/* ������Stdin_Caculate
 * ---------------------
 * ���м���������ʽ�ļ��㲢���ؽ����
 *
 * �޲��� 
 *
 * ����ֵ������ɹ��򷵻�OK�����򷵻�ERROR�� 
 */

Status Butch_caculate(const char* inputFilePath, const char* outputFilePath);
/* ������Butch_Caculate
 * ---------------------
 * �����ļ�������ʽ���������㲢���ؽ����
 *
 * inputFilePath�������ļ�·��
 * outputFilePath������ļ�·�� 
 *
 * ����ֵ������ɹ�����OK�����򷵻�ERROR�� 
 */

Status Butch_Caculate();
/* ������Butch_Caculate
 * ---------------------
 * �������㡣 
 *
 * ����ֵ������ɹ�����OK�����򷵻�ERROR�� 
 */
 #endif
