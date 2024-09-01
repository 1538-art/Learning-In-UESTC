#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Generic_Stack.h"


// 栈的构造函数
Stack* Stack_Construct(int sizeOfElement) {
    Stack* pStack;// 定义一个Stack类型的指针变量pStack  
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
    return pStack; // 返回创建的栈的指针，作为函数的结果
}

// 获取栈的长度
int Stack_Length(Stack* pStack) {
	//结束地址减去开始地址得到字节差
	//字节差除以每个元素的大小来得到栈中的元素数量
	return (int)((char*)pStack->pTop - (char*)pStack->pBase) / pStack->elementSize;
}

// 入栈
Status Stack_Push(Stack* pStack, void* pData) {
    int newsize;
    void* pTemp;
    if (Stack_Length(pStack) >= pStack->size) {
        newsize = pStack->size + STACK_INCREASE_SIZE;
        // 定义一个变量pTemp，用于临时存储重新分配的内存地址  
		pTemp = realloc(pStack->pBase, newsize * pStack->elementSize);
        if (pTemp == NULL) {
            return ERROR;
        } else {
            pStack->pBase = pTemp;
            pStack->pTop = (char*)pStack->pBase + pStack->size * pStack->elementSize;
            pStack->size = newsize;
        }
    }
    // 使用memcpy函数将pData复制到堆栈的顶部
    // 函数原型void *memcpy(void *dest, const void *src, size_t n);
    memcpy(pStack->pTop, pData, pStack->elementSize);
    pStack->pTop = (char*)pStack->pTop + pStack->elementSize;
    return OK;
}

// 出栈
Status Stack_Pop(Stack* pStack, void* pData) {
    if (pStack->pTop == pStack->pBase) {
        return ERROR;
    }
    pStack->pTop = (char*)pStack->pTop - pStack->elementSize;
    memcpy(pData, pStack->pTop, pStack->elementSize);
    return OK;
}

// 获取栈顶元素 
Status Stack_GetTop(Stack* pStack, void* pData) {
    if (pStack->pTop == pStack->pBase) {
        return ERROR;
    }
    pStack->pTop = (char*)pStack->pTop - pStack->elementSize;
    memcpy(pData, pStack->pTop, pStack->elementSize);
    pStack->pTop = (char*)pStack->pTop + pStack->elementSize;
    return OK;
}

// 判断栈是否为空
Bool Stack_IsEmpty(Stack* pStack) {
    if ((void*)pStack->pTop == (void*)pStack->pBase) {
        return TRUE;
    }
    return FALSE;
}

// 判断栈是否已满
Bool Stack_IsFull(Stack* pStack) {
    if ((char*)pStack->pTop - (char*)pStack->pBase >= pStack->size * pStack->elementSize) {
        return TRUE;
    }
    return FALSE;
}

// 销毁栈
void Stack_Destroy(Stack* pStack) {
    if (pStack != NULL) {
        free(pStack->pBase);
        free(pStack);
    }
}
