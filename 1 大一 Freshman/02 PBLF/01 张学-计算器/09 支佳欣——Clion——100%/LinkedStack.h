#include "Linkedlist.h"
typedef List Stack;//将链表命名为栈以统一链栈与栈操作

//构造栈
Stack* Stack_Construct(int sizeOfElement);
//生成一个栈，栈内元素的大小为sizeOfElement，返回指向这个栈的指针

//析构栈
void Stack_Destruct(Stack* pStack);

//判断栈是否为空
bool Stack_IsEmpty(Stack* pStack);
//如果为空栈，则返回true

//取栈顶元素，返回一个指向的值为该元素的指针
void* Stack_GetTop(Stack* pStack);

//入栈操作
bool Stack_Push(Stack* pStack, void* pElement);
//向pStack所指向的栈中压入pElement所指向的元素，如果成功入栈，返回true，否则返回false

//出栈操作
void* Stack_Pop(Stack* pStack);