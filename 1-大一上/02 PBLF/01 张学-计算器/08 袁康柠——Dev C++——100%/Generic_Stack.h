#ifndef GENERIC_STACK_H
#define GENERIC_STACK_H

//����Status��Bool���͵Ķ���
#include "common.h"

//����ջ��ʼ����
#define STACK_SIZE 100
//����ջ��������
#define STACK_INCREASE_SIZE 10

//ͨ��ջ����
typedef struct {
    void* pBase;
    void* pTop;
    int elementSize;
    int size;
} Stack;

Stack* Stack_Construct(int sizeOfElement);
/* ������Stack_Construct
 * ---------------------
 * ���첢��ʼ��һ��ͨ��ջ��
 *
 * sizeOfElement���������͵Ĵ�С��
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

Bool Stack_IsFull(Stack* pStack);
/* ������Stack_IsFull
 * ------------------
 * ���ջ�Ƿ�������
 *
 * pStack��ָ��ջ��ָ�롣
 *
 * ����ֵ����ջ��������TRUE�����򷵻�FALSE��
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
 
