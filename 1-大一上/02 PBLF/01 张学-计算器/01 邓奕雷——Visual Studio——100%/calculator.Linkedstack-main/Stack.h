#ifndef STACK_H
#define STACK_H

#include"common.h"
#define SIZE 10     //栈指针malloc的内存大小
#define ADDSIZE 5   //栈指针realloc增加的内存大小

typedef struct {
    void* pBase;
    void* pTop;
    int elementSize;
    int size;
} Stack;

//栈相关函数
Stack* Stack_Construct(int sizeOfElment);
/*
初始化栈
参数为栈元素的大小
返回值OK表示初始化成功，ERROR表示失败
*/

void StackDestruct(Stack* pStack);
/*
释放栈的内存
参数为栈的指针
*/

Bool Is_Empty(Stack* pStack);
/*
判断栈是否为空
参数为栈指针
返回值TRUE表示栈为空，FAULSE表示栈不为空
*/

int Stack_Length(Stack* pStack);
/*
求栈的长度
参数为栈的指针
返回值为栈的长度
*/

Status Stack_Push(Stack* pStack, void* pElem);
/*
入栈
第一个参数为栈指针，第二个参数为入栈元素的指针
返回值OK表示入栈成功，ERROR表示失败
*/

Status Stack_Pop(Stack* pStack, void* pElem);
/*
出栈
第一个参数为栈指针，第二个参数为出栈元素存放的数据位置的指针
返回值OK表示出栈成功，ERROR表示出栈失败
*/

void* StackGetTop(Stack* pStack);
/*
取栈顶元素
第一个参数为栈指针，第二个参数为存放栈顶元素的数据的指针
返回值OK表示成功，ERROR表示失败
*/

Status Visit(void* pElem);
/*
访问栈内一个元素，进行printf操作
参数为数据元素的指针
返回值OK表示visit成功，ERROR表示失败
*/

Status Stack_Traverse(Stack* pStack, Status(*visit)(void*));
/*
遍历栈
第二个参数为栈指针，第二个参数为函数指针
返回值OK表示成功，ERROR表示失败
*/
#endif
