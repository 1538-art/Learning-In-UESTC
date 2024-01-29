#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

// ����һ���½ڵ㣬���洢ָ��������
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
// �ͷ�һ���ڵ㼰��洢�������ڴ档
void List_freeNode(ListNode* pNode){
	if(pNode==NULL){
		return;
 	}
	free(pNode->pData);
 	free(pNode);
	 return;
}
// ����һ��������
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

// ���һ�������ͷ����е����нڵ�������ڴ�
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

// ����һ�������ͷ����е����нڵ�������ڴ�
void List_Destruct(List* pList){
	List_Clear(pList);
	free(pList);
	return;
}

// ��ȡ�����нڵ������
int List_GetLength(List* pList){
	return pList->length;
}

// ��ȡ����ڵ��д洢������ָ��
void* List_GetData(ListNode* pNode){
	return pNode->pData;
}

// �ж������Ƿ�Ϊ��
Bool List_IsEmpty(List* pList){
	if(pList->length==0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

// ������ͷ������һ���ڵ�
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

// ������ĩβ���һ���ڵ�
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
// ��ָ���ڵ�������һ���ڵ�
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

// ɾ������ͷ���Ľڵ�
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

// ɾ������ĩβ�Ľڵ�
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
// ɾ��ָ���Ľڵ�
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
// �������в���ָ��������
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
// ���������е����нڵ㣬����ÿ���ڵ�ִ��ָ���Ĳ���
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

// ��ȡ����ĵ�һ���ڵ�
ListNode* List_GetFirstNode(List* pList) {
    if (pList == NULL || pList->pFirstNode == NULL) {
        return NULL;
    }
    return pList->pFirstNode;
}

// ��ȡ��������һ���ڵ�
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

// ��ȡ����ĵ�i���ڵ�
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
