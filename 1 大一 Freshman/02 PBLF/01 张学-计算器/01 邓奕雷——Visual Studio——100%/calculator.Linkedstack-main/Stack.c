#include"Stack.h"

//构建栈
Stack* Stack_Construct(int sizeOfElment) {
    Stack* pStack;
    pStack = (Stack*)malloc(sizeof(Stack));
    if (pStack == NULL) {
        return NULL;
    }
    pStack->pBase = malloc(SIZE * sizeOfElment);
    if (pStack->pBase == NULL) {
        free(pStack);
        return NULL;
    }
    pStack->pTop = pStack->pBase;
    pStack->elementSize = sizeOfElment;
    pStack->size = SIZE;
    return pStack;
}

//析构栈
void StackDestruct(Stack* pStack) {
    if (pStack == NULL) {
        return;
    }
    free(pStack->pBase);
    free(pStack);
}

//入栈
Status Stack_Push(Stack* pStack, void* pElem) {
    int NewSize;
    void* pTemp = NULL;  //realloc使用，自定义一个新的指针申请内存
    if (Stack_Length(pStack) >= pStack->size) {
        NewSize = pStack->size + ADDSIZE;
        pTemp = (void*)realloc(pStack->pBase, NewSize * sizeof(pStack->elementSize));
        if (pTemp == NULL) {
            return ERROR;
        }
        else { //成功申请内存后，要重新赋值，因为realloc可能导致栈不在原来的地方。
            pStack->pBase = pTemp;
            pStack->pTop = (char*)pStack->pBase + pStack->size;
            pStack->size = NewSize;
        }
    }
    memcpy(pStack->pTop, pElem, pStack->elementSize);
    pStack->pTop = (char*)pStack->pTop + pStack->elementSize;
    return OK;
}

//出栈
Status Stack_Pop(Stack* pStack, void* pElem) {
    if (pStack->pTop == pStack->pBase) {
        return ERROR;
    }
    else {
        pStack->pTop = (char*)pStack->pTop - pStack->elementSize;
        memcpy(pElem, pStack->pTop, pStack->elementSize);//把pStack->pTop的pStack->element给个字节内存拷贝给pElem，
        //此时pElem即指向存储的内容
        return OK;
    }
}

//取栈顶元素
void* StackGetTop(Stack* pStack) {
    void* pElem = (char*)pStack->pTop - 1;
    return pElem;
}

//求栈的长度
int Stack_Length(Stack* pStack) {
    return ((int*)pStack->pTop - (int*)pStack->pBase) / pStack->elementSize;
}

//判断栈是否为空:
Bool Is_Empty(Stack* pStack) {
    return(pStack->pTop == pStack->pBase) ? TRUE : FALSE;
}

//定义visit函数
Status Visit(void* pElem) {
    if (!pElem) return ERROR;
    char* ch = (char*)pElem;
    printf("%s", ch);
    return OK;
}
//遍历栈：
Status Stack_Traverse(Stack* pStack, Status(*visit)(void*)) {
    if (pStack->pTop == pStack->pBase || pStack->pTop == NULL) return ERROR;
    void* p = pStack->pBase;
    char* temp = (char*)p;
    while (p != pStack->pTop) {
        Visit(p);
        temp++;
        p = temp;
    }
    return OK;
}




