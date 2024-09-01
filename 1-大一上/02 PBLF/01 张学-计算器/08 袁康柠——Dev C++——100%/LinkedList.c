#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

// 创建一个新节点，并存储指定的数据
ListNode* List_makeNode(List* pList,void* pData){
	ListNode *pNewNode;
 	pNewNode=(ListNode*)malloc(sizeof(ListNode));
 	if(pNewNode==NULL){
 		return NULL;
 	}
 	pNewNode->pData=malloc(pList->dataSize);
 	if(pNewNode->pData==NULL){
 		free(pNewNode);
 		return NULL;
 	}
 	memcpy(pNewNode->pData,pData,pList->dataSize);
 	pNewNode->pNextNode=NULL;
 	return pNewNode;
}
// 释放一个节点及其存储的数据内存。
void List_freeNode(ListNode* pNode){
	if(pNode==NULL){
		return;
 	}
	free(pNode->pData);
 	free(pNode);
	 return;
}
// 创建一个空链表
List* List_Construct(int sizeOfData){
	List* pList=(List*)malloc(sizeof(List));
 	if(pList==NULL){
 		return NULL;
	}
 	pList->pFirstNode=NULL;
 	pList->length=0;
 	pList->dataSize=sizeOfData;
 	return pList;
}

// 清空一个链表，释放其中的所有节点和数据内存
void List_Clear(List* pList){
	ListNode *pCurrentNode,*pNextNode;
 	pCurrentNode=pList->pFirstNode;
 	while(pCurrentNode!=NULL){
 		pNextNode=pCurrentNode->pNextNode;
 		List_freeNode(pCurrentNode);
 		pCurrentNode=pNextNode;
	}
 	pList->pFirstNode=NULL;
 	pList->length=0;
	return;
}

// 销毁一个链表，释放其中的所有节点和数据内存
void List_Destruct(List* pList){
	List_Clear(pList);
	free(pList);
	return;
}

// 获取链表中节点的数量
int List_GetLength(List* pList){
	return pList->length;
}

// 获取链表节点中存储的数据指针
void* List_GetData(ListNode* pNode){
	return pNode->pData;
}

// 判断链表是否为空
Bool List_IsEmpty(List* pList){
	if(pList->length==0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

// 在链表头部插入一个节点
Status List_InsertAtFront(List* pList,void* pData){
	ListNode* pNewNode;
 	pNewNode=List_makeNode(pList,pData);
 	if(pNewNode==NULL){
 		return ERROR;
 	}
 	pNewNode->pNextNode=pList->pFirstNode;
 	pList->pFirstNode=pNewNode;
 	pList->length++;
 	return OK;
}

// 在链表末尾添加一个节点
Status List_AppendToEnd(List* pList,void* pData){
	ListNode *pNewNode,*pTail;
 	pNewNode=List_makeNode(pList,pData);
 	if(pNewNode==NULL){
 		return ERROR;
 	}
	if(pList->pFirstNode==NULL){
 		pList->pFirstNode=pNewNode;
 	}
 	else{
 		pTail=pList->pFirstNode;
 		while(pTail->pNextNode!=NULL){
 		pTail=pTail->pNextNode;
    	}
 		pTail->pNextNode=pNewNode;
 	}
 	pList->length++;
 	return OK;
 }
// 在指定节点后面插入一个节点
Status List_InsertAfter(List* pList,ListNode* pNode,void* pData){
 	ListNode* pNewNode;
	pNewNode=List_makeNode(pList,pData);
 	if(pNewNode==NULL){
 		return ERROR;
 	}
	pNewNode->pNextNode=pNode->pNextNode;
 	pNode->pNextNode=pNewNode;
	pList->length++;
 	return OK;
 }

// 删除链表头部的节点
Status List_DeleteFirstNode(List* pList){
 	ListNode *pTempNode;
 	if(pList->length==0){
 		return ERROR;
 	}
 	pTempNode=pList->pFirstNode;
 	pList->pFirstNode=pTempNode->pNextNode;
 	List_freeNode(pTempNode);
 	pTempNode=NULL;
 	pList->length--;
 	return OK;
}

// 删除链表末尾的节点
Status List_DeleteLastNode(List* pList){
 	ListNode *p,*q;
 	if(pList->length==0){
 		return ERROR;
	}

 	q=pList->pFirstNode;
 	if(q->pNextNode==NULL){
		return List_DeleteFirstNode(pList);
	}
 	while(q->pNextNode!=NULL){
 		p=q;
 		q=q->pNextNode;
 	}
 	p->pNextNode=NULL;
 	List_freeNode(q);
 	q=NULL;
 	pList->length--;
 	return OK;
 }
// 删除指定的节点
Status List_DeleteNode(List* pList, ListNode* pNode){
	ListNode* pTempNode;
 	if(pNode==NULL){
 		return OK;
 	}
 	if(pList->length==0){
 		return ERROR;
 	}
 	pTempNode=pList->pFirstNode;
 	if(pTempNode==pNode){
 		pList->pFirstNode=pNode->pNextNode;
	}
 	else{
 		while(pTempNode!=NULL && pTempNode->pNextNode!=pNode){
 			pTempNode=pTempNode->pNextNode;
 		}
 		if(pTempNode==NULL){
 			return ERROR;
 		}
 		pTempNode->pNextNode=pNode->pNextNode;
 	}
 	List_freeNode(pNode);
 	pList->length--;
 	return OK;
}
// 在链表中查找指定的数据
ListNode* List_Search(List* pList,void* pKey,Bool (*isThisOne)(void*,void*)){
 	ListNode* pTempNode;
 	pTempNode=pList->pFirstNode;
	while(pTempNode!=NULL){
 		if(isThisOne(pTempNode->pData,pKey)==TRUE){
 			return pTempNode;
 		}
 		pTempNode=pTempNode->pNextNode;
 	}
 	return NULL;
}
// 遍历链表中的所有节点，并对每个节点执行指定的操作
Status List_Traverse(List* pList,Status (*visit)(void*)){
	ListNode* pTempNode;
 	pTempNode=pList->pFirstNode;
 	while(pTempNode!=NULL){
 		if(visit(pTempNode->pData)==ERROR){
			return ERROR;
 		}
		pTempNode=pTempNode->pNextNode;
 	}
 	return OK;
}

// 获取链表的第一个节点
ListNode* List_GetFirstNode(List* pList) {
    if (pList == NULL || pList->pFirstNode == NULL) {
        return NULL;
    }
    return pList->pFirstNode;
}

// 获取链表的最后一个节点
ListNode* List_GetLastNode(List* pList) {
    if (pList == NULL || pList->pFirstNode == NULL) {
        return NULL;
    }
    ListNode* pNode = pList->pFirstNode;
    while (pNode->pNextNode != NULL) {
        pNode = pNode->pNextNode;
    }
    return pNode;
}

// 获取链表的第i个节点
ListNode* List_GetNode(List* pList, int i) {
    if (pList == NULL || pList->pFirstNode == NULL || i < 0 || i >= pList->length) {
        return NULL;
    }
    ListNode* pNode = pList->pFirstNode;
    int j = 0;
    while (pNode != NULL && j < i) {
        pNode = pNode->pNextNode;
        j++;
    }
    return pNode;
}
