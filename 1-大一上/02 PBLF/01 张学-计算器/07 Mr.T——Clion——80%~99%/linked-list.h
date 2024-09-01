#ifndef CALCULATOR_V2_0_LINKED_LIST_H
#define CALCULATOR_V2_0_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    OK = 1, ERROR = 0
} Status;
typedef enum {
    TRUE = 1, FALSE = 0
} Bool;

typedef struct ListNode {
    struct ListNode *pNextNode; //递归
    void *pData;
} ListNode;
typedef struct {
    ListNode *pFirstNode;
    int length;
    int dataSize;
} List;

/*没有dataSize
typedef struct {
    ListNode* pFirstNode;
    unsigned int length;
} List;
*/

/*双向链表
typedef struct Node2 {
    struct Node2 *prevNode;
    struct Node2 *nextNode;
}Node2;
typedef struct {
    struct ListNode *firstNode;
    int length;
    int dataSize;
} DoublyLinkedList;
*/

//NO.1
//因为这个函数只供List的其他操作函数调用，而使用List的人根本用不到，所以这个函数可视为List的私有函数。
//为了便于区分私有和公有，在为私有函数命名时，在类型前缀后加下划线并用小驼峰表示。
/// \param pList 目标链表
/// \param pData 新节点的数据
/// \return 返回新节点的指针
ListNode *List_makeNode(List *pList, void *pData);

//NO.2
/// \param pNode 目标节点
void List_freeNode(ListNode *pNode);

//NO.3
/// \param dataSize 数据占用字节数
/// \return 返回新链表的指针
List *ListConstruct(int dataSize);

//NO.4
/// \param pList 目标链表
void ListClear(List *pList);

//NO.5
/// \param pList 目标链表
void ListDestruct(List *pList);

//NO.6
/// \param pList 目标链表
/// \return 返回链表的长度
int List_GetLength(List *pList);

//NO.7
/// \param pNode 目标节点
/// \return 返回目标节点所存数据的指针
void *ListGetData(ListNode *pNode);

//NO.8
/// \param pList 目标链表
/// \return 若目标链表为空，则返回TRUE，否则返回FALSE
Bool ListIsEmpty(List *pList);

//NO.9
/// \param pList 目标链表
/// \param pData 加入的数据
/// \return 若成功则返回OK，否则返回ERROR
Status ListInsertAtFront(List *pList, void *pData);

//NO.10
/// \param pList 目标链表
/// \param pData 加入的数据
/// \return 若成功则返回OK，否则返回ERROR
Status ListAppend(List *pList, void *pData);

//NO.11
/// \param pList 目标链表
/// \param pNode 目标节点
/// \param pData 加入的数据
/// \return 若成功则返回OK，否则返回ERROR
Status ListInsertAfter(List *pList, ListNode *pNode, void *pData);

//NO.12
/// \param pList 目标链表
/// \return 若成功则返回OK，否则返回ERROR
Status ListDeleteFirstNode(List *pList);

//NO.13
/// \param pList 目标链表
/// \return 若成功则返回OK，否则返回ERROR
Status ListDeleteLastNode(List *pList);

//NO.14
/// \param pList 目标链表
/// \param pNode 目标节点
/// \return 若成功则返回OK，否则返回ERROR
Status ListDeleteNode(List *pList, ListNode *pNode);

//NO.15
/// \param pList 目标链表
/// \param pKey 关键字
/// \param isThisOne 用户自定义的比较函数，以适应不同类型的数据和不同的比较需求
/// \return 返回关键字对应的节点指针
ListNode *ListSearch(List *pList, void *pKey, Bool (*isThisOne)(void *, void *));

//NO.16
/// \param pList 目标链表
/// \param visit 对每个数据
/// \return 若成功则返回OK，否则返回ERROR
Status ListTraverse(List *pList, Status (*visit)(void *));

// NO.17
/// \param pList 目标链表
/// \return 返回链表的第一个节点的指针
ListNode* ListGetFirstNode(List* pList);

// NO.18
/// \param pList 目标链表
/// \return 返回链表的最后一个节点的指针
ListNode* ListGetLastNode(List* pList);

// NO.19
/// \param pList 目标链表
/// \param i 节点的索引
/// \return 返回链表中第i个节点的指针
ListNode* ListGetNode(List* pList, int i);

// NO.20
/// \param pList 目标链表
/// \param pNode 节点
/// \return 返回节点在链表中的序号
int ListGetOrderNumber(List* pList, ListNode* pNode);

// NO.21
/// \param pList 目标链表
/// \param pNode 节点
/// \return 返回节点在链表中的前一个节点的指针
ListNode* ListGetPriorNode(List* pList, ListNode* pNode);

// NO.22
/// \param pNode 节点
/// \return 返回节点的下一个节点的指针
ListNode* ListGetNextNode(ListNode* pNode);

// NO.23
/// \param pList 目标链表
/// \param pNode 节点
/// \param pData 要插入的数据
/// \return 若成功则返回OK，否则返回ERROR
Status ListInsertBefore(List* pList, ListNode* pNode, void* pData);

// NO.24
/// \param pList 目标链表
/// \param i 要插入数据的索引
/// \param pData 要插入的数据
/// \return 若成功则返回OK，否则返回ERROR
Status ListInsert(List* pList, int i, void* pData);

// NO.25
/// \param pList 目标链表
/// \param pNode 节点
/// \param pData 要设置的数据
/// \return 若成功则返回OK，否则返回ERROR
Status ListSetData(List* pList, ListNode* pNode, void* pData);

// NO.26
/// \param pList 目标链表
/// \param compare 用户自定义的比较函数，以适应不同类型的数据和不同的比较需求
/// \return 若成功则返回OK，否则返回ERROR
Status ListSort(List* pList, int (*compare)(void*, void*));



#endif //CALCULATOR_V2_0_LINKED_LIST_H