#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedStack.h"

// 栈的构造函数
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

// 获取栈的长度
int Stack_Length(Stack* pStack) {
    return pStack->length;
}

// 入栈
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

// 出栈
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

// 获取栈顶元素
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

// 判断栈是否为空
Bool Stack_IsEmpty(Stack* pStack) {
    return List_IsEmpty(pStack);
}

// 销毁栈
void Stack_Destroy(Stack* pStack) {
    if (pStack == NULL) {
        return;
    }
    List_Destruct(pStack);
}

