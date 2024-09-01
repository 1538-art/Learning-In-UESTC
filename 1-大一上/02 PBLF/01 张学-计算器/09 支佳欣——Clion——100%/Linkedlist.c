#include "Linkedlist.h"
//构造链表
List* List_Construct(int sizeOfElement){
    List *pList;
    pList=(List*) malloc(sizeof (List));//动态分配链表内存
    if(pList==NULL){
        return NULL;
    }
    pList->pFirstNode=NULL;//初始化头结点
    pList->length=0;//初始链化长度
    pList->elementSize=sizeOfElement;//
    return pList;
}
//生成一个链表，链表的元素大小为sizeOfElement，返回指向新链表的指针
//创建节点
ListNode* List_MakeNode(List* pList,void *pElement){
    ListNode *pNewNode;
    pNewNode=(ListNode*)malloc(sizeof(ListNode));
    if(pNewNode==NULL){
        return NULL;
    }
    pNewNode->pElement= malloc(sizeof (pList->elementSize));
    if(pNewNode->pElement==NULL){
        free(pNewNode);
        return NULL;
    }
    memcpy(pNewNode->pElement,pElement,sizeof (pList->elementSize));
    pNewNode->pNextNode=NULL;
    return pNewNode;
}
//在pList指向的链表中生节点，节点的元素为pElement所指向的值，返回一个指向新节点的指针
//释放节点
void List_FreeNode(ListNode *pNode){
    if(pNode==NULL){
        return;
    }
    free(pNode->pElement);
    free(pNode);
    return;
}

//清空链表
void List_Clear(List* pList){
    ListNode *pCurrentNode,*pNextNode;
    pCurrentNode=pList->pFirstNode;
    while (pCurrentNode!=NULL){
        pNextNode=pCurrentNode->pNextNode;
        List_FreeNode(pCurrentNode);
        pCurrentNode=pNextNode;
    }
    pList->pFirstNode=NULL;
    pList->length=0;
    return;
}

//析构链表(销毁)
void List_Destruct(List* pList){
    List_Clear(pList);
    free(pList);//清空后释放动态分配的内存
    return;
}

//求链表长度
int List_GetLength(List* pList){
    return pList->length;
}

//取第一个节点上的数据
void* List_GetElement(List* pList){
    return pList->pFirstNode->pElement;
}

//判断链表是否为空
bool List_IsEmpty(List* pList){
    if(pList->length==0){
        return true;
    } else{
        return false;
    }
}

//在头部插入数据
bool List_InsertAtFront(List* pList,void * pElement){
    ListNode *pNewNode;
    pNewNode= List_MakeNode(pList,pElement);
    if(pNewNode==NULL){
        return false;
    }
    pNewNode->pNextNode=pList->pFirstNode;
    pList->pFirstNode=pNewNode;
    pList->length++;
    return true;
}

//移出第一个节点（出栈）
void* List_DeleteFirstNode(List* pList){
    ListNode *pTempNode;
    if(pList->length==0){
        return false;
    }
    pTempNode=pList->pFirstNode;
    pList->pFirstNode=pTempNode->pNextNode;
    pList->length--;
    return pTempNode->pElement;
}
//将pList指向的链表的链头节点弹出，返回指向该节点的数据的指针

void* List_GetData(ListNode* pNode){
    return pNode->pElement;
}

//在尾部追加数据
bool List_AppendToEnd(List* pList,void* pElement){
    ListNode *pNewNode,*pTail;
    pNewNode= List_MakeNode(pList,pElement);
    if(pNewNode==NULL){
        return false;
    }
    if(pList->pFirstNode==NULL){
        pList->pFirstNode=pNewNode;
    } else{
        pTail=pList->pFirstNode;
        while (pTail->pNextNode!=NULL){
            pTail=pTail->pNextNode;
        }
        pTail->pNextNode=pNewNode;
    }
    pList->length++;
    return true;
}

bool List_InsertAfter(List* pList,ListNode* pNode,void* pElement){
    ListNode* pNewNode;
    pNewNode= List_MakeNode(pList,pElement);
    if(pNewNode==NULL){
        return NULL;
    }
    pNewNode->pElement=pNode->pNextNode;
    pNode->pNextNode=pNewNode;
    pList->length++;
    return true;
}

//删除最后一个节点
bool List_DeleteLastNode(List* pList){
    ListNode *p,*q;
    if(pList->length==0){
        return false;
    }
    q=pList->pFirstNode;
    if(q->pNextNode==NULL){
        return false;
    }
    while (q->pNextNode!=NULL){
        p=q;
        q=q->pNextNode;
    }
    p->pNextNode=NULL;
    List_FreeNode(q);
    q=NULL;
    pList->length--;
    return true;
}

//删除指定节点
bool List_DeleteNode(List* pList,ListNode* pNode){
    ListNode* pTempNode;
    if(pNode==NULL){
        return true;
    }
    if(pList->length==0){
        return false;
    }
    pTempNode=pList->pFirstNode;
    if(pTempNode==pNode){
        pList->pFirstNode=pNode->pNextNode;
    } else{
        while (pTempNode!=NULL&&pTempNode->pNextNode!=pNode){
            pTempNode=pTempNode->pNextNode;
        }
        if(pTempNode==NULL){
            return false;
        }
        pTempNode->pNextNode=pNode->pNextNode;
    }
    List_FreeNode(pNode);
    pList->length--;
    return true;
}

//查找数据
ListNode* List_Srearch(List* pList,void* pKey,bool (*isThisOne)(void*,void*)){
    ListNode* pTemNode;
    pTemNode=pList->pFirstNode;
    while (pTemNode!=NULL){
        if(isThisOne(pTemNode->pElement,pKey)==true){
            return pTemNode;
        }
        pTemNode=pTemNode->pNextNode;
    }
    return NULL;
}

//遍历链表
bool List_Traverse(List* pList,bool (*visit)(void*)){
    ListNode* pTemNode;
    pTemNode=pList->pFirstNode;
    while (pTemNode!=NULL){
        if(visit(pTemNode->pElement)==false){
            return false;
        }
        pTemNode=pTemNode->pNextNode;
    }
    return true;
}

//倒置链表
void reverseStack(List* s)
{
    ListNode *p = s->pFirstNode, *q;
    s->pFirstNode = NULL;
    while(p)
    {
        q = p->pNextNode;
        p->pNextNode = NULL;//断开p与后面的连接
        s->pFirstNode = p;//p为新栈顶
        p = q;//p移动到下一个节点
    }//q用来防止断开联系
}

//获取第一个节点的地址
ListNode*   List_GetFirstNode(List* pList){
    ListNode *pTempNode;
    if(pList->length==0){
        return false;
    }
    pTempNode=pList->pFirstNode;
    return pTempNode;
}

ListNode* GetLastNode(List* pList){
    ListNode *pTemNode;
    if(pList->length==0){
        return false;
    }
    pTemNode=pList->pFirstNode;
    while (pTemNode->pNextNode!=NULL){
        pTemNode=pTemNode->pNextNode;
    }
    return pTemNode;
}

ListNode* List_GetNode(List* pList,int i){
    ListNode *pTemNode;
    if(pList->length==NULL){
        return false;
    }
    pTemNode=pList->pFirstNode;
    int j=1;
    while (j!=i){
        pTemNode=pTemNode->pNextNode;
        j++;
    }
    return pTemNode;
}

int List_GetOrderNumber(List* pList,ListNode* pNode){
    ListNode *TemNode;
    if(pList->length==0){
        return 0;
    }
    TemNode=pList->pFirstNode;
    int i=1;
    while (TemNode->pElement!=pNode->pElement){
        TemNode=TemNode->pNextNode;
        i++;
    }
    return i;
}
ListNode* List_GetPriorNode(List* pList,ListNode* pNode){
    ListNode *TemNode;
    if(pList->length==0){
        return NULL;
    }
    TemNode=pList->pFirstNode;
    int i=0;
    while (TemNode->pElement!=pNode->pElement){
        TemNode=TemNode->pNextNode;
        i++;
    }
    ListNode *P;
    P=pList->pFirstNode;
    while (i!=1){
        P=P->pNextNode;
        i--;
    }
    return P;
};

ListNode* List_GetNextNode(ListNode* pNode){
    return pNode->pNextNode;
};


bool List_SetData(ListNode* pNode,void* pElement){
    pNode->pElement=pElement;

};