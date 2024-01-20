#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Generic_Stack.h"


// ջ�Ĺ��캯��
Stack* Stack_Construct(int sizeOfElement) {
    Stack* pStack;// ����һ��Stack���͵�ָ�����pStack  
    pStack = (Stack*)malloc(sizeof(Stack));//
    if (pStack == NULL) {
        return NULL;
    }
    pStack->pBase = malloc(STACK_SIZE * sizeOfElement);
    if (pStack->pBase == NULL) {
        free(pStack);
        return NULL;
    }
    pStack->pTop = pStack->pBase;
    pStack->size = STACK_SIZE;
    pStack->elementSize = sizeOfElement;
    return pStack; // ���ش�����ջ��ָ�룬��Ϊ�����Ľ��
}

// ��ȡջ�ĳ���
int Stack_Length(Stack* pStack) {
	//������ַ��ȥ��ʼ��ַ�õ��ֽڲ�
	//�ֽڲ����ÿ��Ԫ�صĴ�С���õ�ջ�е�Ԫ������
	return (int)((char*)pStack->pTop - (char*)pStack->pBase) / pStack->elementSize;
}

// ��ջ
Status Stack_Push(Stack* pStack, void* pData) {
    int newsize;
    void* pTemp;
    if (Stack_Length(pStack) >= pStack->size) {
        newsize = pStack->size + STACK_INCREASE_SIZE;
        // ����һ������pTemp��������ʱ�洢���·�����ڴ��ַ  
		pTemp = realloc(pStack->pBase, newsize * pStack->elementSize);
        if (pTemp == NULL) {
            return ERROR;
        } else {
            pStack->pBase = pTemp;
            pStack->pTop = (char*)pStack->pBase + pStack->size * pStack->elementSize;
            pStack->size = newsize;
        }
    }
    // ʹ��memcpy������pData���Ƶ���ջ�Ķ���
    // ����ԭ��void *memcpy(void *dest, const void *src, size_t n);
    memcpy(pStack->pTop, pData, pStack->elementSize);
    pStack->pTop = (char*)pStack->pTop + pStack->elementSize;
    return OK;
}

// ��ջ
Status Stack_Pop(Stack* pStack, void* pData) {
    if (pStack->pTop == pStack->pBase) {
        return ERROR;
    }
    pStack->pTop = (char*)pStack->pTop - pStack->elementSize;
    memcpy(pData, pStack->pTop, pStack->elementSize);
    return OK;
}

// ��ȡջ��Ԫ�� 
Status Stack_GetTop(Stack* pStack, void* pData) {
    if (pStack->pTop == pStack->pBase) {
        return ERROR;
    }
    pStack->pTop = (char*)pStack->pTop - pStack->elementSize;
    memcpy(pData, pStack->pTop, pStack->elementSize);
    pStack->pTop = (char*)pStack->pTop + pStack->elementSize;
    return OK;
}

// �ж�ջ�Ƿ�Ϊ��
Bool Stack_IsEmpty(Stack* pStack) {
    if ((void*)pStack->pTop == (void*)pStack->pBase) {
        return TRUE;
    }
    return FALSE;
}

// �ж�ջ�Ƿ�����
Bool Stack_IsFull(Stack* pStack) {
    if ((char*)pStack->pTop - (char*)pStack->pBase >= pStack->size * pStack->elementSize) {
        return TRUE;
    }
    return FALSE;
}

// ����ջ
void Stack_Destroy(Stack* pStack) {
    if (pStack != NULL) {
        free(pStack->pBase);
        free(pStack);
    }
}
