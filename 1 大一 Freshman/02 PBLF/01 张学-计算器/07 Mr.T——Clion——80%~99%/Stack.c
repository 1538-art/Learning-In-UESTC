
#include "Stack.h"

Stack *StackConstruct(int sizeOfElement) {
    Stack *pStack;
    pStack = (Stack *) malloc(sizeof(Stack));
    if (pStack == NULL) {
        return NULL;
    }
    pStack->pBase = malloc(
            STACK_INIT_SIZE * sizeOfElement);
    if (pStack->pBase == NULL) {
        free(pStack);
        return NULL;
    }
    pStack->pTop = pStack->pBase;
    pStack->elemSize = sizeOfElement;
    pStack->stackSize = STACK_INIT_SIZE;
    return pStack;
}

void StackDestruct(Stack *pStack) {
    if (pStack == NULL) {
        return;
    }
    free(pStack->pBase);
    free(pStack);
}

void StackClear(Stack *pStack) {
    pStack->pTop = pStack->pBase;
}

Bool StackIsEmpty(Stack *pStack) {
    if (pStack->pBase == pStack->pTop)return TRUE;
    else return FALSE;
}

int StackGetLength(Stack *pStack) {
    return (pStack->pTop - pStack->pBase) / pStack->elemSize;
}

Status StackPop(Stack *pStack, void *pElem) {
    void *pc;
    if (pStack->pTop == pStack->pBase) {
        return ERROR;
    } else {
        pStack->pTop -= pStack->elemSize;   //此处不能用“pStack->pTop--”，否则只减少一个字节
        memcpy(pElem, pStack->pTop,
               pStack->elemSize);       //将 pTop 指向的内存地址复制给 pElem
        return OK;
    }
}

Status StackPush(Stack *pStack, void *pElem) {
    int newSize;
    void *pTemp;
    if (StackGetLength(pStack) >= pStack->stackSize) {
        newSize = pStack->stackSize + STACK_INCREASE_SIZE;
        pTemp = realloc(pStack->pBase, newSize * pStack->elemSize);
        if (pTemp == NULL) {
            return ERROR;
        } else {
            pStack->pBase = pTemp;
            pStack->pTop = pStack->pBase + pStack->stackSize * pStack->elemSize;
            pStack->stackSize = newSize;
        }
    }
    memcpy(pStack->pTop, pElem, pStack->elemSize);
    pStack->pTop += pStack->elemSize;
    return OK;
}

Status StackGetTop(Stack *pStack, void *pElem) {
    if (pStack->pTop == pStack->pBase) return ERROR;
    memcpy(pElem, pStack->pTop - 1, pStack->elemSize);
    return OK;
}

Status StackTraverse(Stack *pStack, Status (*visit)(void *)) {
    void *pElem = pStack->pBase;
    while (pElem != pStack->pTop) {
        if (visit(pElem) != OK) {
            return ERROR;
        }
        pElem += pStack->elemSize;
    }
    return OK;
}
