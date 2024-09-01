#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedStack.h"

// ջ�Ĺ��캯��
Stack* Stack_Construct(int dataSize) {
    Stack* pStack = (Stack*)malloc(sizeof(Stack));
    if (pStack == NULL) {
        return NULL;
    }
	pStack = List_Construct(dataSize);
    if (pStack == NULL) {
        free(pStack);
        return NULL;
    }
    return pStack;
}

// ��ȡջ�ĳ���
int Stack_Length(Stack* pStack) {
    return pStack->length;
}

// ��ջ
Status Stack_Push(Stack* pStack, void* pData) {
    if (pStack == NULL || pData == NULL) {
        return ERROR;
    }
    ListNode* pNode = List_makeNode(pStack, pData);
    if (pNode == NULL) {
        return ERROR;
    }
    List_AppendToEnd(pStack, pNode);
    return OK;
}

// ��ջ
Status Stack_Pop(Stack* pStack, void* pData) {
    if (pStack == NULL || pData == NULL) {
        return ERROR;
    }
    ListNode* pNode = List_GetLastNode(pStack);
    if (pNode == NULL) {
        return ERROR;
    }
    memcpy(pData, pNode->pData, pStack->dataSize);
    List_DeleteLastNode(pStack);
    return OK;
}

// ��ȡջ��Ԫ��
Status Stack_GetTop(Stack* pStack, void* pData) {
    if (pStack == NULL || pData == NULL) {
        return ERROR;
    }
    ListNode* pNode = List_GetLastNode(pStack);
    if (pNode == NULL) {
        return ERROR;
    }
    memcpy(pData, pNode->pData, pStack->dataSize);
    return OK;
}

// �ж�ջ�Ƿ�Ϊ��
Bool Stack_IsEmpty(Stack* pStack) {
    return List_IsEmpty(pStack);
}

// ����ջ
void Stack_Destroy(Stack* pStack) {
    if (pStack == NULL) {
        return;
    }
    List_Destruct(pStack);
}

