#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

//遍历链表所使用的visit函数 
Status visit(void* pData) {
    int* pIntData = (int*)pData;
    printf("%d ", *pIntData);
    return OK;
}

//创建一个节点
ListNode* List_makeNode(List* pList, void* pData){
	ListNode* pNewNode;
	pNewNode = (ListNode*)malloc(sizeof(ListNode));
	if(pNewNode == NULL){
		return NULL;
	}
	pNewNode->pData = malloc(pList->dataSize);
	if(pNewNode->pData == NULL){
		free(pNewNode);
		return NULL;
	}
	memcpy(pNewNode->pData, pData, pList->dataSize);
	pNewNode->pNextNode = NULL;
	return pNewNode;
}

//释放节点
void List_freeNode(ListNode* pNode){
	if(pNode == NULL){
		return; 
	}
	free(pNode->pData);
	free(pNode);
	return;
}

//构造并初始化一个链表 
List* List_Construct(int sizeOfData){
    List* pList = (List*)malloc(sizeof(List));
    if(pList == NULL){
    	return NULL;
	}
	pList->pFirstNode = NULL;
	pList->length = 0;
	pList->dataSize = sizeOfData;
	return pList;
}
 
//获得pNode节点的数据指针 
void* List_GetData(ListNode* pNode){
	return pNode->pData;
}

//清空链表 
void List_Clear(List* pList){
    ListNode *pCurrentNode,*pNextNode;
    pCurrentNode = pList->pFirstNode;
    while(pCurrentNode != NULL){
    	pNextNode = pCurrentNode->pNextNode;
    	List_freeNode(pCurrentNode);
    	pCurrentNode = pNextNode;
	}
	pList->pFirstNode = NULL;
	pList->length = 0;
	return;
}
 
//求链表的长度 
int List_GetLength(List* pList){
	return pList->length;
}

//在头部插入数据 
Status List_InsertAtFront(List* pList, void* pData){
	ListNode* pNewNode;
	pNewNode = List_makeNode(pList, pData);
	if(pNewNode == NULL){
		return ERROR;
	} 
	pNewNode->pNextNode = pList->pFirstNode;
	pList->pFirstNode = pNewNode;
	pList->length++;
	return OK;
}

//在链表的尾部追加数据。
Status List_AppendToEnd(List* pList, void* pData){
	ListNode *pNewNode,*pTail;
	pNewNode = List_makeNode(pList, pData);
	if(pNewNode == NULL){
		return ERROR;
	} 
	if(pList->pFirstNode == NULL){
		pList->pFirstNode = pNewNode;
	}
	else{
		pTail = pList->pFirstNode;
		while (pTail->pNextNode != NULL){
			pTail = pTail->pNextNode;
		}
		pTail->pNextNode = pNewNode;
	}
	pList->length++;
	return OK;
}

//在链表的某节点后插入数据 
Status List_InsertAfter(List* pList, ListNode* pNode, void* pData){
	ListNode* pNewNode;
	pNewNode = List_makeNode(pList, pData);
	if(pNewNode == NULL){
		return ERROR;
	}
	pNewNode->pNextNode = pNode->pNextNode;
	pNode->pNextNode = pNewNode;
	pList->length++;
	return OK; 
}

//删除第一个节点 
Status List_DeleteFirstNode(List* pList){
	ListNode *pTempNode;
	if(pList->length == 0){
		return ERROR;
	}
	pTempNode = pList->pFirstNode;
	pList->pFirstNode = pTempNode->pNextNode;
	List_freeNode(pTempNode);
	pTempNode = NULL;
	pList->length--;
	return OK;
}
 
//删除最后一个节点。 
Status List_DeleteLastNode(List* pList){
    ListNode *p,*q;
	if(pList->length == 0){
		return ERROR;
	} 
	q = pList->pFirstNode;
	if(q->pNextNode == NULL){
		return List_DeleteFirstNode(pList);
	}	
	while(q->pNextNode != NULL){
		p = q;
		q = q->pNextNode;
	}
	p->pNextNode = NULL;
	List_freeNode(q);
	q = NULL;
	pList->length--;
	return OK;
}

//删除指定节点
Status List_DeleteNode(List* pList, ListNode* pNode){
	ListNode* pTempNode;
	if(pNode == NULL){
		return OK;
	} 
	if(pList->length == 0){
		return ERROR;
	}
	pTempNode = pList->pFirstNode;
	if(pTempNode == pNode){
		pList->pFirstNode = pNode->pNextNode;
	}
	else{
		while(pTempNode != NULL && pTempNode->pNextNode != pNode){
			pTempNode = pTempNode->pNextNode;
		}
		if(pTempNode == NULL){
			return ERROR;
		}
		pTempNode->pNextNode = pNode->pNextNode;
	}
	List_freeNode(pNode);
	pList->length--;
	return OK; 
}

//判断链表是否为空 
Bool List_IsEmpty(List* pList){
	if(pList->length == 0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

//遍历链表 
Status ListTraverse(List* pList, Status (*visit)(void*)) {
    ListNode* pTempNode;
    pTempNode = pList->pFirstNode;
    
    while (pTempNode != NULL) {
        if (visit(pTempNode->pData) == ERROR) {
            return ERROR;
        }
        pTempNode = pTempNode->pNextNode;
    }
    
    return OK;
}

 
//析构链表 
void List_Destruct(List* pList){
	List_Clear(pList);
	free(pList);
	return;
}

