#ifndef LINkEDLIST_H
#define LINKEDLIST_H

//包含Status和Bool类型的定义
#include "common.h" 

//定义链表节点
typedef struct ListNode{
	struct ListNode *pNextNode;
	void *pData;
} ListNode;
//定义链表类型
typedef struct {
	ListNode* pFirstNode;
	int length;
	int dataSize;
} List;

ListNode* List_makeNode(List* pList, void* pData);
/* 函数：List_makeNode
 * --------------------
 * 创建一个新节点，并存储指定的数据。
 *
 * pList：指向要创建新节点的链表的指针。
 * pData：指向要存储在新节点中的数据的指针。
 * 返回值：指向新节点的指针。如果创建失败，返回NULL。
 */

void List_freeNode(ListNode* pNode);
/* 函数：List_freeNode
 * --------------------
 * 释放一个节点及其存储的数据内存。
 *
 * pNode：指向要释放的节点的指针。
 */

List* List_Construct(int sizeOfData); 
/* 函数：ListConstruct
 * --------------------
 * 创建一个空链表。
 *
 * sizeOfData：节点中数据的大小。
 * 返回值：指向新链表的指针。如果创建失败，返回NULL。
 */

void List_Destruct(List* pList);
/* 函数：ListDestruct
 * -------------------
 * 销毁一个链表，释放其中的所有节点和数据内存。
 *
 * pList：指向要销毁的链表的指针。
 */

void List_Clear(List* pList);
/* 函数：ListClear
 * ----------------
 * 清空一个链表，释放其中的所有节点和数据内存。
 *
 * pList：指向要清空的链表的指针。
 */

int List_GetLength(List* pList);
/* 函数：ListGetLength
 * --------------------
 * 获取链表中节点的数量。
 *
 * pList：指向要获取节点数量的链表的指针。
 * 返回值：链表中节点的数量。
 */

void* List_GetData(ListNode* pNode);
/* 函数：ListGetData
 * -----------------
 * 获取链表节点中存储的数据指针。
 *
 * pNode：指向要获取数据指针的节点的指针。
 * 返回值：存储在节点中的数据指针。
 */

Bool List_IsEmpty(List* pList);
/* 函数：ListIsEmpty
 * -----------------
 * 判断链表是否为空。
 *
 * pList：指向要判断的链表的指针。
 * 返回值：如果链表为空，返回TRUE，否则返回FALSE。
 */

Status List_InsertAtFront(List* pList, void* pData);
/* 函数：ListInsertAtFront
 * -----------------------
 * 在链表头部插入一个节点。
 *
 * pList：指向要插入节点的链表的指针。
 * pData：指向要存储在新节点中的数据的指针。
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

Status List_AppendToEnd(List* pList, void* pData);
/* 函数：ListAppendToEnd
 * ---------------------
 * 在链表末尾添加一个节点。
 *
 * pList：指向要添加节点的链表的指针。
 * pData：指向要存储在新节点中的数据的指针。
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

Status List_InsertAfter(List* pList, ListNode* pNode, void* pData);
/* 函数：ListInsertAfter
 * ---------------------
 * 在指定节点后面插入一个节点。
 *
 * pList：指向要插入节点的链表的指针。
 * pNode：指向要在其后面插入新节点的节点的指针。
 * pData：指向要存储在新节点中的数据的指针。
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

Status List_DeleteFirstNode(List* pList);
/* 函数：ListDeleteFirstNode
 * -------------------------
 * 删除链表头部的节点。
 *
 * pList：指向要删除节点的链表的指针。
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

Status List_DeleteLastNode(List* pList);
/* 函数：ListDeleteLastNode
 * ------------------------
 * 删除链表末尾的节点。
 *
 * pList：指向要删除节点的链表的指针。
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

Status List_DeleteNode(List* pList, ListNode* pNode);
/* 函数：ListDeleteNode
 * --------------------
 * 删除指定的节点。
 *
 * pList：指向要删除节点的链表的指针。
 * pNode：指向要删除的节点的指针。
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

ListNode* List_Search(List* pList, void* pKey, Bool (*isThisOne)(void*, void*));
/* 函数：ListSearch
 * -----------------
 * 在链表中查找指定的数据。
 *
 * pList：指向要查找数据的链表的指针。
 * pKey：指向要查找的数据的指针。
 * isThisOne：指向用于比较数据的函数的指针。
 * 返回值：如果找到指定的数据，返回指向包含该数据的节点的指针，否则返回NULL。
 */

Status List_Traverse(List* pList, Status (*visit)(void*));
/* 函数：ListTraverse
 * -------------------
 * 遍历链表中的所有节点，并对每个节点执行指定的操作。
 *
 * pList：指向要遍历的链表的指针。
 * visit：指向要执行的操作的函数的指针。
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */
ListNode* List_GetFirstNode(List* pList);
/* 函数：List_GetFirstNode
 * -----------------------
 * 获取链表的第一个节点。
 *
 * pList: 链表指针。
 *
 * 返回值：第一个节点的指针，如果链表为空则返回NULL。
 */

ListNode* List_GetLastNode(List* pList);
/* 函数：List_GetLastNode
 * ----------------------
 * 获取链表的最后一个节点。
 *
 * pList: 链表指针。
 *
 * 返回值：最后一个节点的指针，如果链表为空则返回NULL。
 */

ListNode* List_GetNode(List* pList, int i);
/* 函数：List_GetNode
 * -------------------
 * 获取链表的第i个节点。
 *
 * pList: 链表指针。
 * i: 节点索引，从0开始。
 *
 * 返回值：第i个节点的指针，如果不存在第i个节点则返回NULL。
 */




#endif
