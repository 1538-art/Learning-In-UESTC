#include "linked-list.h"

//NO.1
ListNode *List_makeNode(List *pList, void *pData) {
  ListNode *pNewNode;
  pNewNode = (ListNode*)malloc(sizeof(ListNode));         //为Node分配内存
  if (pNewNode == NULL) {
    return NULL;
  }
  pNewNode->pData = malloc(pList->dataSize);   //为Node中的Data分配内存，若失败，应释放Node的内存
  if (pNewNode->pData == NULL) {
    free(pNewNode);
    return NULL;
  }
  memcpy(pNewNode->pData, pData, pList->dataSize);    //将pData指向的地址复制给pNewNode
  pNewNode->pNextNode = NULL;
  return pNewNode;
}

//NO.2
void List_freeNode(ListNode *pNode) {
  if (pNode == NULL) {
    return;
  }
  free(pNode->pData);
  free(pNode);
}

//NO.3
List *ListConstruct(int dataSize) {
  List *pList = (List*)malloc(sizeof(List));
  if (pList == NULL) {
    return NULL;
  }
  pList->pFirstNode = NULL;
  pList->length = 0;
  pList->dataSize = dataSize;
  return pList;
}

//NO.4
void ListClear(List *pList) {
  ListNode *pCurrentNode, *pNextNode;
  pCurrentNode = pList->pFirstNode;
  while (pCurrentNode != NULL) {
    pNextNode = pCurrentNode->pNextNode;
    List_freeNode(pCurrentNode);
    pCurrentNode = pNextNode;
  }
  pList->pFirstNode = NULL;
  pList->length = 0;
}

//NO.5
void ListDestruct(List *pList) {
  ListClear(pList);
  free(pList);
}

//NO.6
int List_GetLength(List *pList) {
  return pList->length;
}

//NO.7
void *ListGetData(ListNode *pNode) {
  return pNode->pData;
}

//NO.8
Bool ListIsEmpty(List *pList) {
  if (pList->length == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

//NO.9
Status ListInsertAtFront(List *pList, void *pData) {
  ListNode *pNewNode;
  pNewNode = List_makeNode(pList, pData);
  if (pNewNode == NULL) {
    return ERROR;
  }
  pNewNode->pNextNode = pList->pFirstNode;
  pList->pFirstNode = pNewNode;
  pList->length++;
  return OK;
}

//NO.10
Status ListAppend(List *pList, void *pData) {
  ListNode *pNewNode, *pTail;
  pNewNode = List_makeNode(pList, pData);
  if (pNewNode == NULL) {
    return ERROR;
  }
  if (pList->pFirstNode == NULL) {
    pList->pFirstNode = pNewNode;
  } else {
    pTail = pList->pFirstNode;
    while (pTail->pNextNode != NULL) {
      pTail = pTail->pNextNode;
    }
    pTail->pNextNode = pNewNode;
  }
  pList->length++;
  return OK;
}

//NO.11
Status ListInsertAfter(List *pList, ListNode *pNode, void *pData) {
  ListNode *pNewNode;
  pNewNode = List_makeNode(pList, pData);
  if (pNewNode == NULL) {
    return ERROR;
  }
  pNewNode->pNextNode = pNode->pNextNode;
  pNode->pNextNode = pNewNode;
  pList->length++;
  return OK;
}

//NO.12
Status ListDeleteFirstNode(List *pList) {
  ListNode *pTempNode;
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

//NO.13
Status ListDeleteLastNode(List *pList) {
  ListNode *p, *q;
  if (pList->length == 0) {
    return ERROR;
  }
  q = pList->pFirstNode;
  if (q->pNextNode == NULL) {
    return ListDeleteFirstNode(pList);
  }
  while (q->pNextNode != NULL) {
    p = q;
    q = q->pNextNode;
  }
  p->pNextNode = NULL;
  List_freeNode(q);
  pList->length--;
  return OK;
}

//NO.14
Status ListDeleteNode(List *pList, ListNode *pNode) {
  ListNode *pTempNode;
  if (pNode == NULL) {
    return OK;
  }
  if (pList->length == 0) {
    return ERROR;
  }
  pTempNode = pList->pFirstNode;
  if (pTempNode == pNode) {
    pList->pFirstNode = pNode->pNextNode;
  } else {
    while (pTempNode != NULL && pTempNode->pNextNode != pNode) {
      pTempNode = pTempNode->pNextNode;
    }
    if (pTempNode == NULL) {
      return ERROR;
    }
    pTempNode->pNextNode = pNode->pNextNode;
  }
  List_freeNode(pNode);
  pList->length--;
  return OK;
}

//NO.15
ListNode *ListSearch(List *pList, void *pKey, Bool (*isThisOne)(void *, void *)) {
  ListNode *pTempNode;
  pTempNode = pList->pFirstNode;
  while (pTempNode != NULL) {
    if (isThisOne(pTempNode->pData, pKey) == TRUE) {
      return pTempNode;
    }
    pTempNode = pTempNode->pNextNode;
  }
  return NULL;
}

//NO.16
Status ListTraverse(List *pList, Status (*visit)(void *)) {
  ListNode *pTempNode;
  pTempNode = pList->pFirstNode;
  while (pTempNode != NULL) {
    if (visit(pTempNode->pData) == ERROR) {
      return ERROR;
    }
    pTempNode = pTempNode->pNextNode;
  }
  return OK;
}

//NO.17
ListNode* ListGetFirstNode(List* pList) {
  return pList->pFirstNode;
}

//NO.18
ListNode* ListGetLastNode(List* pList) {
  ListNode* pNode = pList->pFirstNode;
  if (pNode == NULL) {
    return NULL;
  }
  while (pNode->pNextNode != NULL) {
    pNode = pNode->pNextNode;
  }
  return pNode;
}

//NO.19
ListNode* ListGetNode(List* pList, int i) {
  ListNode* pNode = pList->pFirstNode;
  int count = 1;
  while (pNode != NULL && count < i) {
    pNode = pNode->pNextNode;
    count++;
  }
  if (count == i) {
    return pNode;
  } else {
    return NULL;
  }
}

//NO.20
int ListGetOrderNumber(List* pList, ListNode* pNode) {
  ListNode* pTempNode = pList->pFirstNode;
  int count = 1;
  while (pTempNode != NULL && pTempNode != pNode) {
    pTempNode = pTempNode->pNextNode;
    count++;
  }
  if (pTempNode == pNode) {
    return count;
  } else {
    return -1;
  }
}

//NO.21
ListNode* ListGetPriorNode(List* pList, ListNode* pNode) {
  ListNode* pTempNode = pList->pFirstNode;
  if (pTempNode == pNode || pTempNode == NULL) {
    return NULL;
  }
  while (pTempNode->pNextNode != NULL && pTempNode->pNextNode != pNode) {
    pTempNode = pTempNode->pNextNode;
  }
  if (pTempNode->pNextNode == pNode) {
    return pTempNode;
  } else {
    return NULL;
  }
}

//NO.22
ListNode* ListGetNextNode(ListNode* pNode) {
  return pNode->pNextNode;
}

//NO.23
Status ListInsertBefore(List* pList, ListNode* pNode, void* pData) {
  if (pNode == pList->pFirstNode) {
    return ListInsertAtFront(pList, pData);
  }
  ListNode* pPriorNode = ListGetPriorNode(pList, pNode);
  return ListInsertAfter(pList, pPriorNode, pData);
}

//NO.24
Status ListInsert(List* pList, int i, void* pData) {
  if (i <= 0 || i > pList->length + 1) {
    return ERROR;
  }
  if (i == 1) {
    return ListInsertAtFront(pList, pData);
  }
  ListNode* pNode = ListGetNode(pList, i - 1);
  return ListInsertAfter(pList, pNode, pData);
}

//NO.25
Status ListSetData(List* pList, ListNode* pNode, void* pData) {
  memcpy(pNode->pData, pData, pList->dataSize);
  return OK;
}

//NO.26
Status ListSort(List* pList, int (*compare)(void*, void*)) {
  if (pList == NULL || compare == NULL) {
    return ERROR;
  }
  if (pList->length < 2) {
    return OK;
  }
  ListNode *p, *q;
  for (p = pList->pFirstNode; p != NULL && p->pNextNode != NULL; p = p->pNextNode) {
    for (q = p->pNextNode; q != NULL; q = q->pNextNode) {
      if (p->pData == NULL || q->pData == NULL) {
        return ERROR;
      }
      if (compare(p->pData, q->pData) > 0) {
        void* temp = p->pData;
        p->pData = q->pData;
        q->pData = temp;
      }
    }
  }
  return OK;
}

