#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "LinkedList.h"

typedef List Stack;

Bool Stack_IsEmpty(List* pList);
/* 函数：List_IsEmpty
 * -----------------
 * 判断链表是否为空。
 *
 * pList: 指向要判断的链表的指针。
 *
 * 返回值：如果链表为空，返回TRUE，否则返回FALSE。
 */

Stack* Stack_Construct(int dataSize);
/* 函数：Stack_Construct
 * ---------------------
 * 栈的构造函数。
 *
 * dataSize: 栈中每个元素的大小。
 *
 * 返回值：返回新创建的栈，如果内存分配失败则返回NULL。
 */

int Stack_Length(Stack* pStack);
/* 函数：Stack_Length
 * ------------------
 * 获取栈的长度。
 *
 * pStack: 栈指针。
 *
 * 返回值：栈的长度。
 */

Status Stack_Push(Stack* pStack, void* pData);
/* 函数：Stack_Push
 * ----------------
 * 入栈
 *
 * pStack: 栈指针
 * pData: 入栈的元素指针
 *
 * 返回值：操作状态，如果操作成功返回OK，否则返回ERROR
 */

Status Stack_Pop(Stack* pStack, void* pData);
/* 函数：Stack_Pop
 * ---------------
 * 出栈
 *
 * pStack: 栈指针
 * pData: 出栈的元素指针
 *
 * 返回值：操作状态，如果操作成功返回OK，否则返回ERROR
 */

Status Stack_GetTop(Stack* pStack, void* pData);
/* 函数：Stack_GetTop
 * ------------------
 * 获取栈顶元素
 *
 * pStack: 栈指针。
 * pData: 获取的栈顶元素指针。
 *
 * 返回值：操作状态，如果操作成功返回OK，否则返回ERROR。
 */

Bool Stack_IsEmpty(Stack* pStack);
/* 函数：Stack_IsEmpty
 * -------------------
 * 判断栈是否为空。
 *
 * pStack: 栈指针。
 *
 * 返回值：如果栈为空返回TRUE，否则返回FALSE。
 */

void Stack_Destroy(Stack* pStack);
/* 函数：Stack_Destroy
 * -------------------
 * 销毁栈。
 *
 * pStack: 栈指针。
 */


#endif
