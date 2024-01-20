#include"list.h"

//创建结点
ListNode* List_makeNode(List* pList, void* pData) {
    ListNode* pNewNode;
    pNewNode = (ListNode*)malloc(sizeof(ListNode));
    if (pNewNode == NULL) {
        return NULL;
    }
    pNewNode->pData = malloc(pList->elementSize);
    if (pNewNode->pData == NULL) {
        free(pNewNode);
        return NULL;
    }
    memcpy(pNewNode->pData, pData, pList->elementSize);
    pNewNode->pNextNode = NULL;
    return pNewNode;
}

//释放结点
void List_freeNode(ListNode* pNode) {
    if (pNode == NULL) {
        return;
    }
    free(pNode->pData);
    free(pNode);
    return;
}

//清空链表
void ListClear(List* pList) {
    ListNode* pCurrentNode, * pNextNode;
    pCurrentNode = pList->pFirstNode;
    while (pCurrentNode != NULL) { //释放结点，但不释放链表(即保留头结点)
        pNextNode = pCurrentNode->pNextNode;
        List_freeNode(pCurrentNode);
        pCurrentNode = pNextNode;
    }
    pList->pFirstNode = NULL;
    pList->length = 0;
    return;
}

//取结点上的数据
void* ListGetData(ListNode* pNode) {
    if (pNode->pData == NULL) return NULL;
    return pNode->pData;
}

//判断结点是否为空
Bool Empyt_Node(ListNode* pNode) {
    return pNode == NULL ? TRUE : FALSE;
}

//尾部插入数据
Status ListAppendToEnd(List* pList, void* pData) {
    ListNode* pNewNode, * pTail;
    pNewNode = List_makeNode(pList, pData);//创建一个结点
    if (pNewNode == NULL) {
        return ERROR;
    }
    if (pList->pFirstNode == NULL) {
        pList->pFirstNode = pNewNode;//当链表为空(即只有头结点)
    }
    else {
        pTail = pList->pFirstNode;
        while (pTail->pNextNode != NULL) {
            pTail = pTail->pNextNode;
        }
        pTail->pNextNode = pNewNode;//将创造的结点插入到链表尾部
    }
    pList->length++;
    return OK;
}

//某节点后插入数据
Status ListInsertAfter(List* pList, ListNode* pNode, void* pData) {
    ListNode* pNewNode;
    pNewNode = List_makeNode(pList, pData);//创建结点
    if (pNewNode == NULL) {
        return ERROR;
    }
    pNewNode->pNextNode = pNode->pNextNode;
    pNode->pNextNode = pNewNode;
    pList->length++;
    return OK;
}

//删除第一个结点
Status ListDeleteFirstNode(List* pList) {
    ListNode* pTempNode;
    if (pList->length == 0) {
        return ERROR;
    }
    pTempNode = pList->pFirstNode;
    pList->pFirstNode = pTempNode->pNextNode;
    List_freeNode(pTempNode);
    pTempNode = NULL;
    pList->length--;
    return OK;
}

//删除最后一个结点
Status ListDeleteLastNode(List* pList) {
    ListNode* p, * q;
    p = NULL;
    if (pList->length == 0) {
        return ERROR;
    }
    q = pList->pFirstNode;
    if (q->pNextNode == NULL) {//q的nest域为空，说明链表(除头结点外)只有一个结点
        return ListDeleteFirstNode(pList);//删除第一个结点
    }
    while (q->pNextNode != NULL) {
        p = q;
        q = q->pNextNode;//将p、q不断往链表尾部移动，直到q的next域为空，则说明已经遍历到了链表尾部
    }
    p->pNextNode = NULL;//此时p变成了新链表的尾部
    List_freeNode(q);//释放原链表的尾部
    q = NULL;
    pList->length--;//链表长度减1
    return OK;
}

//删除某一结点
Status ListDeleteNode(List* pList, ListNode* pNode) {
    ListNode* pTempNode;
    if (pNode == NULL) {
        return OK;
    }  
    if (pList->length == 0) {
        return ERROR;
    }
    pTempNode = pList->pFirstNode;
    if (pTempNode == pNode) {
        pList->pFirstNode = pNode->pNextNode;
    }
    else {
        while (pTempNode != NULL && pTempNode->pNextNode != pNode) {
            pTempNode = pTempNode->pNextNode;//找到所要删除的结点位置
        }
        if (pTempNode == NULL) {
            return ERROR;
        }
        pTempNode->pNextNode = pNode->pNextNode;//删除结点
    }
    List_freeNode(pNode);
    pList->length--;
    return OK;
}

//判断两个数据是否相同
Bool isThisOne(void* listData, void* pData) {
    return strcmp(listData, pData) == 0 ? TRUE : FALSE;
}

//查找数据的位置
ListNode* ListSearch(List* pList, void* pKey, Bool(*isThisOne)(void*, void*)) {
    ListNode* pTempNode;
    pTempNode = pList->pFirstNode;
    while (pTempNode != NULL) {
        if (isThisOne(pTempNode->pData, pKey) == TRUE) {
            return pTempNode;
        }
        pTempNode = pTempNode->pNextNode;
    }
    return NULL;
}
