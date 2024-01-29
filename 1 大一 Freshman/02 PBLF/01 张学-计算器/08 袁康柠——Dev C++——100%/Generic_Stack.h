#ifndef GENERIC_STACK_H
#define GENERIC_STACK_H

//包含Status和Bool类型的定义
#include "common.h"

//定义栈初始容量
#define STACK_SIZE 100
//定义栈容量增量
#define STACK_INCREASE_SIZE 10

//通用栈定义
typedef struct {
    void* pBase;
    void* pTop;
    int elementSize;
    int size;
} Stack;

Stack* Stack_Construct(int sizeOfElement);
/* 函数：Stack_Construct
 * ---------------------
 * 构造并初始化一个通用栈。
 *
 * sizeOfElement：数据类型的大小。
 *
 * 返回值：指向栈的指针。
 */

int Stack_Length(Stack* pStack);
/* 函数：Stack_Length
 * ------------------
 * 返回栈的长度。
 *
 * pStack：指向栈的指针。
 *
 * 返回值：栈的长度。
 */

Status Stack_Push(Stack* pStack, void* pData);
/* 函数：Stack_Push
 * ----------------
 * 将数据压入栈。
 *
 * pStack：指向栈的指针。
 * pData：指向要压入的数据的指针。
 *
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

Status Stack_Pop(Stack* pStack, void* pData);
/* 函数：Stack_Pop
 * ---------------
 * 弹出栈顶元素并返回其值。
 *
 * pStack：指向栈的指针。
 * pData：用于存储弹出元素值的指针。
 *
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

Status Stack_GetTop(Stack* pStack, void* pData);
/* 函数：Stack_GetTop
 * ------------------
 * 获取栈顶元素的值，但不弹出。
 *
 * pStack：指向栈的指针。
 * pData：用于存储栈顶元素值的指针。
 *
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

Bool Stack_IsEmpty(Stack* pStack);
/* 函数：Stack_IsEmpty
 * -------------------
 * 检查栈是否为空。
 *
 * pStack：指向栈的指针。
 *
 * 返回值：若栈为空返回TRUE，否则返回FALSE。
 */

Bool Stack_IsFull(Stack* pStack);
/* 函数：Stack_IsFull
 * ------------------
 * 检查栈是否已满。
 *
 * pStack：指向栈的指针。
 *
 * 返回值：若栈已满返回TRUE，否则返回FALSE。
 */

void Stack_Destroy(Stack* pStack);
/* 函数：Stack_Destroy
 * -------------------
 * 销毁栈并释放内存。
 *
 * pStack：指向栈的指针。
 *
 * 返回值：无。
 */


 #endif
 
