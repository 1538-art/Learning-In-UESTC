#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "LinkedList.h"

typedef List Stack;

Bool Stack_IsEmpty(List* pList);
/* ������List_IsEmpty
 * -----------------
 * �ж������Ƿ�Ϊ�ա�
 *
 * pList: ָ��Ҫ�жϵ������ָ�롣
 *
 * ����ֵ���������Ϊ�գ�����TRUE�����򷵻�FALSE��
 */

Stack* Stack_Construct(int dataSize);
/* ������Stack_Construct
 * ---------------------
 * ջ�Ĺ��캯����
 *
 * dataSize: ջ��ÿ��Ԫ�صĴ�С��
 *
 * ����ֵ�������´�����ջ������ڴ����ʧ���򷵻�NULL��
 */

int Stack_Length(Stack* pStack);
/* ������Stack_Length
 * ------------------
 * ��ȡջ�ĳ��ȡ�
 *
 * pStack: ջָ�롣
 *
 * ����ֵ��ջ�ĳ��ȡ�
 */

Status Stack_Push(Stack* pStack, void* pData);
/* ������Stack_Push
 * ----------------
 * ��ջ
 *
 * pStack: ջָ��
 * pData: ��ջ��Ԫ��ָ��
 *
 * ����ֵ������״̬����������ɹ�����OK�����򷵻�ERROR
 */

Status Stack_Pop(Stack* pStack, void* pData);
/* ������Stack_Pop
 * ---------------
 * ��ջ
 *
 * pStack: ջָ��
 * pData: ��ջ��Ԫ��ָ��
 *
 * ����ֵ������״̬����������ɹ�����OK�����򷵻�ERROR
 */

Status Stack_GetTop(Stack* pStack, void* pData);
/* ������Stack_GetTop
 * ------------------
 * ��ȡջ��Ԫ��
 *
 * pStack: ջָ�롣
 * pData: ��ȡ��ջ��Ԫ��ָ�롣
 *
 * ����ֵ������״̬����������ɹ�����OK�����򷵻�ERROR��
 */

Bool Stack_IsEmpty(Stack* pStack);
/* ������Stack_IsEmpty
 * -------------------
 * �ж�ջ�Ƿ�Ϊ�ա�
 *
 * pStack: ջָ�롣
 *
 * ����ֵ�����ջΪ�շ���TRUE�����򷵻�FALSE��
 */

void Stack_Destroy(Stack* pStack);
/* ������Stack_Destroy
 * -------------------
 * ����ջ��
 *
 * pStack: ջָ�롣
 */


#endif
