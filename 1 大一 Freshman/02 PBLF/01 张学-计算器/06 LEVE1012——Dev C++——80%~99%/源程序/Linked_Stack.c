#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linked_Stack.h"


//ջ�Ĺ��캯�� 
Stack* Stack_Construct(int sizeOfData){
	Stack* pStack = List_Construct(sizeOfData);
        return pStack;
}

//��ȡջ�ĳ��� 
int Stack_Length(Stack* pStack){
	return pStack->length;
}

//��ջ
Status Stack_Push(Stack* pStack, void* pData){
    List_InsertAtFront(pStack, pData);
    return OK;
}

//��ջ 
Status Stack_Pop(Stack* pStack, void* pData){
	pData = pStack->pFirstNode->pData;
	List_DeleteFirstNode(pStack);
	return OK;
}

//��ȡջ��ֵ 
Status Stack_GetTop(Stack* pStack, void* pData){
    pData = pStack->pFirstNode->pData;
    return OK;
}

//�ж�ջ�Ƿ�Ϊ�� 
Bool Stack_IsEmpty(Stack* pStack){
	return(List_IsEmpty(pStack));
}


Status Stack_Traverse(Stack* pStack){
	Status ListTraverse(pStack, visit) {
    return OK;
    }
}
 
//����ջ 
void Stack_Destroy(Stack* pStack){
	List_Destruct(pStack);
}


