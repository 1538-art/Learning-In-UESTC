#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linked_Stack.h"


//栈的构造函数 
Stack* Stack_Construct(int sizeOfData){
	Stack* pStack = List_Construct(sizeOfData);
        return pStack;
}

//获取栈的长度 
int Stack_Length(Stack* pStack){
	return pStack->length;
}

//入栈
Status Stack_Push(Stack* pStack, void* pData){
    List_InsertAtFront(pStack, pData);
    return OK;
}

//出栈 
Status Stack_Pop(Stack* pStack, void* pData){
	pData = pStack->pFirstNode->pData;
	List_DeleteFirstNode(pStack);
	return OK;
}

//获取栈顶值 
Status Stack_GetTop(Stack* pStack, void* pData){
    pData = pStack->pFirstNode->pData;
    return OK;
}

//判断栈是否为空 
Bool Stack_IsEmpty(Stack* pStack){
	return(List_IsEmpty(pStack));
}


Status Stack_Traverse(Stack* pStack){
	Status ListTraverse(pStack, visit) {
    return OK;
    }
}
 
//析构栈 
void Stack_Destroy(Stack* pStack){
	List_Destruct(pStack);
}


