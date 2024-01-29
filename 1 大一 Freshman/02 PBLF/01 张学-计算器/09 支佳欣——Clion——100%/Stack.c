#include "Stack.h"

//通用栈构造器，返回指向一个栈的指针
Stack* Stack_Construct(int SizeOfElement) {
    Stack* pStack;
    pStack = (Stack*)malloc(sizeof(Stack));//给栈动态分配内存
    if (pStack == NULL) {
        return NULL;
    }
    //给栈底指针自动分配内存
    pStack->pBase = (void*)malloc(  SizeOfElement);
    if (pStack->pBase == NULL) {
        free(pStack);
        return NULL;
    }
    pStack->pTop = pStack->pBase;//空栈定义
    pStack->elementSize = SizeOfElement;//栈内元素大小
    return pStack;
}

//析构栈
void Stack_Destruct(Stack* pStack) {
    if (pStack == NULL) {
        return;
    }
    free(pStack->pBase);//释放内存
    free(pStack);//释放内存
    return;
}

//判断栈内是否为空
bool Stack_IsEmpty(Stack* pStack) {
    if (pStack->pTop == pStack->pBase) {
        return true;
    }
    else {
        return false;
    }
}

//取栈顶元素
void* Stack_GetTop(Stack* pStack) {
    if (pStack->pTop == pStack->pBase) {
        return NULL;
    }
    return pStack->pTop - pStack->elementSize;
}

//入栈
bool Stack_Push(Stack* pStack, void* Element) {
    memcpy(pStack->pTop, Element, pStack->elementSize);
    pStack->pTop+=pStack->elementSize;//栈顶指针偏移的距离大小应为栈内元素的大小
    return true;
}//向pStack所指向的栈中压入pElement所指向的元素，如果成功入栈，返回true，否则返回false

//出栈
void* Stack_Pop(Stack* pStack) {
    if (pStack->pTop == pStack->pBase) {
        return NULL;
    }
    else {
        int a;
        void *Element=&a;
        pStack->pTop-=pStack->elementSize;
        memcpy(Element,pStack->pTop,pStack->elementSize);//将栈顶元素存入Element中
        return Element;
    }
}//将pStack所指的栈的栈顶元素弹出，并存入Element指针中返回出来