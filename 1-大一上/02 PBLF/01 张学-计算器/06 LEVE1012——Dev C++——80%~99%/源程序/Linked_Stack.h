#ifndef LINKED_STACK_H
#define LINKED_STACK_H

//����List�����.h�ļ� 
#include "List.h"


//��ʽջ����
typedef List Stack;

Stack* Stack_Construct();
/* ������Stack_Construct
 * ---------------------
 * ���첢��ʼ��һ����ʽջ��
 *
 * 
 *
 * ����ֵ��ָ��ջ��ָ�롣
 */

int Stack_Length(Stack* pStack);
/* ������Stack_Length
 * ------------------
 * ����ջ�ĳ��ȡ�
 *
 * pStack��ָ��ջ��ָ�롣
 *
 * ����ֵ��ջ�ĳ��ȡ�
 */

Status Stack_Push(Stack* pStack, void* pData);
/* ������Stack_Push
 * ----------------
 * ������ѹ��ջ��
 *
 * pStack��ָ��ջ��ָ�롣
 * pData��ָ��Ҫѹ������ݵ�ָ�롣
 *
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

Status Stack_Pop(Stack* pStack, void* pData);
/* ������Stack_Pop
 * ---------------
 * ����ջ��Ԫ�ز�������ֵ��
 *
 * pStack��ָ��ջ��ָ�롣
 * pData�����ڴ洢����Ԫ��ֵ��ָ�롣
 *
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

Status Stack_GetTop(Stack* pStack, void* pData);
/* ������Stack_GetTop
 * ------------------
 * ��ȡջ��Ԫ�ص�ֵ������������
 *
 * pStack��ָ��ջ��ָ�롣
 * pData�����ڴ洢ջ��Ԫ��ֵ��ָ�롣
 *
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

Bool Stack_IsEmpty(Stack* pStack);
/* ������Stack_IsEmpty
 * -------------------
 * ���ջ�Ƿ�Ϊ�ա�
 *
 * pStack��ָ��ջ��ָ�롣
 *
 * ����ֵ����ջΪ�շ���TRUE�����򷵻�FALSE��
 */

Status Stack_Traverse(Stack* pStack); 

/* ������Stack_Traverse
 * -------------------
 * ��visit����ջ 
 *
 * pStack��ָ��ջ��ָ�롣
 * visit���������ݵĺ���ָ�룬����Ϊ����ָ�롣 
 *
 * ����ֵ���ɹ������򷵻�TRUE�����򷵻�FALSE��
 */
 
void Stack_Destroy(Stack* pStack);
/* ������Stack_Destroy
 * -------------------
 * ����ջ���ͷ��ڴ档
 *
 * pStack��ָ��ջ��ָ�롣
 *
 * ����ֵ���ޡ�
 */


 #endif
 
