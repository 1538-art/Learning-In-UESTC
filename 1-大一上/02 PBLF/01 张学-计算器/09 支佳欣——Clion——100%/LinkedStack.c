#include "LinkedStack.h"
//通用栈构造器
Stack* Stack_Construct(int sizeOfElement){
    return List_Construct(sizeOfElement);
}
//生成一个元素大小为sizeOfElement的栈，返回指向这个新栈的指针

//析构栈
void Stack_Destruct(Stack* pStack){
    List_Destruct(pStack);
}

//判断栈内是否为空
bool Stack_IsEmpty(Stack* pStack) {
    return List_IsEmpty(pStack);
}
//如果为空栈，则返回true

//取栈顶元素
void* Stack_GetTop(Stack* pStack){
    return List_GetElement(pStack);
}

//入栈
bool Stack_Push(Stack* pStack, void* pElement){
    return List_InsertAtFront(pStack,pElement);
}
//向pStack所指向的栈中压入element所指向的元素，如果成功入栈，返回true，否则返回false

//出栈
void* Stack_Pop(Stack* pStack){
    return List_DeleteFirstNode(pStack);
}

