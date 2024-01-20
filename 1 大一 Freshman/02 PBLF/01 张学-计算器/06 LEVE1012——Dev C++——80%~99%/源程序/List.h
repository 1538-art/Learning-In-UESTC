#ifndef LISTNODE_H
#define LISTNODE_H

//包含Status和Bool类型的定义
#include "common.h"

//链表节点定义
typedef struct ListNode {
    struct ListNode *pNextNode;
    void* pData;
} ListNode;

//链表头节点定义
typedef struct {
	ListNode *pFirstNode;
	int length;
	int dataSize; 
} List;

Status visit(void* pData);
/* 函数：freeData
 * ------------------
 * 针对pData数据类型所设计的访问数据的函数 
 *
 * pData：需要访问的数据指针。
 *
 * 返回值：成功访问则返回TRUE，否则返回FALSE。
 */

ListNode* List_makeNode(List *pList, void* pData);
/* 函数：List_makeNode 
 * ------------------
 * 创建一个节点。
 *
 * pList：指向链表的指针 
 * pData：需要存入的数据指针。
 *
 * 返回值：指向新节点的指针。
 */

void List_freeNode(ListNode* pNode);
/* 函数：List_freeNode 
 * ------------------
 * 释放节点，调用freeData函数释放节点的数据。 
 *
 * pNode：指向节点的指针。
 *
 * 返回值：无。
 */

List* List_Construct(int sizeOfData);
/* 函数：List_Construct
 * ---------------------
 * 构造并初始化一个链表。
 *
 * 返回值：指向链表的指针。
 */
 
void* List_GetData(ListNode* pNode);
/* 函数：List_GetData 
 * ------------------
 * 获得pNode节点的数据指针。
 *
 * pNode：被执行操作的节点。
 *
 * 返回值：指向pNode的数据指针。
 */

void List_Clear(List* pList);
/* 函数：List_Clear 
 * ------------------
 * 将链表清空。 
 *
 * pList：指向链表的指针。
 *
 * 返回值：无。 
 */
 
int List_GetLength(List* pList);
/* 函数：List_Length
 * ------------------
 * 返回链表的长度。
 *
 * pList：指向链表的指针。
 *
 * 返回值：链表的长度。
 */

Status List_InsertAtFront(List* pList, void* pData);
/* 函数：List_InsertAtFront
 * ----------------
 * 在链表的头部插入数据。 
 *
 * pList：指向栈的指针。
 * pData：指向要插入的数据的指针。
 *
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */

Status List_AppendToEnd(List* pList, void* pData);
/* 函数：List_AppendToEnd
 * ----------------
 * 在链表的尾部追加数据。 
 *
 * pList：指向链表的指针。
 * pData：指向要追加的数据的指针。
 *
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */
 
Status List_InsertAfter(List* pList,ListNode *pNode, void* pData);
/* 函数：List_InsertAfter
 * ----------------
 * 在链表的pNode节点后插入数据。 
 *
 * pList：指向链表的指针。
 * pNode：被插入数据的节点指针。 
 * pData：指向要追加的数据的指针。
 *
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */
 
Status List_DeleteFirstNode(List* pList);
/* 函数：List_DeleteFirstNode
 * ----------------
 * 删除第一个节点。 
 *
 * pList：指向链表的指针。
 *
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */ 
 
Status List_DeleteLastNode(List* pList);
/* 函数：List_DeleteLastNode
 * ----------------
 * 删除最后一个节点。 
 *
 * pList：指向链表的指针。
 *
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */ 
 
Status List_DeleteNode(List* pList, ListNode* pNode);
/* 函数：List_DeleteNode
 * ----------------
 * 删除指定节点。 
 *
 * pList：指向链表的指针。
 * pNode：需要删除的指定节点。 
 *
 * 返回值：操作状态。成功返回OK，失败返回ERROR。
 */ 
 
Bool List_IsEmpty(List* pList);
/* 函数：List_IsEmpty
 * -------------------
 * 检查链表是否为空。
 *
 * pList：指向链表的指针。
 *
 * 返回值：若链表为空返回TRUE，否则返回FALSE。
 */

Status List_Traverse(List* pList, Status (*visit) (void*)); 
/* 函数：List_Traverse 
 * -------------------
 * 用visit操作遍历链表 
 *
 * pList：指向链表的指针。
 * visit：实现遍历的操作函数，参数为数据指针。 
 *
 * 返回值：成功遍历则返回TRUE，否则返回FALSE。
 */
 
void List_Destruct(List* pList);
/* 函数：List_Destroy
 * -------------------
 * 销毁链表并释放内存。
 *
 * pStack：指向栈的指针。
 *
 * 返回值：无。
 */


 #endif
 
