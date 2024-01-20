#ifndef LINKED_STACK_H
#define LINKED_STACK_H

//包含List链表的.h文件 
#include "List.h"


//链式栈定义
typedef List Stack;

Stack* Stack_Construct();
/* 函数：Stack_Construct
 * ---------------------
 * 构造并初始化一个链式栈。
 *
 * 
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

Status Stack_Traverse(Stack* pStack); 

/* 函数：Stack_Traverse
 * -------------------
 * 用visit遍历栈 
 *
 * pStack：指向栈的指针。
 * visit：访问数据的函数指针，参数为数据指针。 
 *
 * 返回值：成功遍历则返回TRUE，否则返回FALSE。
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
 
