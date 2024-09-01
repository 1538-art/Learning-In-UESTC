#ifndef CALCULATOR_V2_0_LINKED_LIST_STACK_H
#define CALCULATOR_V2_0_LINKED_LIST_STACK_H
#include "linked-list.h"
typedef List Stack;

/// \param sizeOfElement 栈元素的大小
/// \return 指向栈的指针，失败时返回 NULL，需判断是否创建成功
/// \usage Stack *pIntStack;    pIntStack=StackConstruct(sizeof(int));
Stack *StackConstruct(int sizeOfElement);

/// \param pStack 目标栈的指针
/// \explanation 释放目标栈pBase和栈指针的内存
void StackDestruct(Stack *pStack);

/// \param pStack 目标栈的指针
/// \explanation 清空栈，即将pBase赋值给pTop
void StackClear(Stack *pStack);

/// \param pStack 目标栈的指针
/// \return 若目标栈中没有元素，则返回TRUE，否则返回FALSE
Bool StackIsEmpty(Stack *pStack);

/// \param pStack 目标栈的指针
/// \return 返回目标栈中的元素个数
int StackGetLength(Stack *pStack);

/// \param pStack 目标栈的指针
/// \param pElem 用于储存栈顶元素的变量地址
/// \return 若成功则返回 OK，否则返回 ERROR
/// \explanation 栈顶元素出栈
Status StackPop(Stack *pStack, void *pElem);

/// \param pStack 目标栈的指针
/// \param pElem 需要入栈的变量的地址
/// \return 若成功则返回 OK，否则返回 ERROR
/// \expanation 元素入栈
Status StackPush(Stack *pStack, void *pElem);

/// \param pStack 目标栈的指针
/// \param pElem 用于储存栈顶元素的值的变量地址
/// \return 若成功则返回 OK，否则返回 ERROR
/// \explanation 保留栈顶元素，将其值传给指定变量
Status StackGetTop(Stack *pStack, void *pElem);

/// \param pStack 目标栈的指针
/// \param visit 对目标栈每个元素所进行的操作
/// \return 若操作成功，返回OK，否则返回ERROR
Status StackTraverse(Stack *pStack, Status (*visit)(void *));

#endif //CALCULATOR_V2_0_LINKED_LIST_STACK_H
