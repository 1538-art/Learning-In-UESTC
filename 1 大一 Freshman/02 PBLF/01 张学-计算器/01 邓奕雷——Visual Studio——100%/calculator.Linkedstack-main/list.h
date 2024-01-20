#ifndef LIST_H
#define LIST_H

#include"common.h"
//结点类型的定义
typedef struct ListNode {
    struct ListNode* pNextNode;
    void* pData;
}ListNode;

//链表的定义
typedef struct {
    ListNode* pFirstNode;
    int length;
    int elementSize;
}List;

ListNode* List_makeNode(List* pList, void* pData);
/*
功能：创建结点
参数：第一个参数是链表的指针，第二个参数是传入数据的指针，把pData指向的数据存入新节点。
返回值：如果成功，返回指向新节点的指针；如果失败，返回NULL。
*/

void List_freeNode(ListNode* pNode);
/*
功能：释放结点
参数：参数是结点的指针
返回值：无返回值
*/

void ListClear(List* pList);
/*
功能：清空链表。链表上的所有结点清空，但链表仍存在
参数：参数是链表的指针
返回值：无返回值
*/

void* ListGetData(ListNode* pNode);
/*
功能：取结点上的数据
参数：参数是结点的指针
返回值：返回pNode节点上数据的地址。参数pNode不能为NULL
*/

Bool Empyt_Node(ListNode* pNode);
/*
功能：判断结点是否为空
参数：参数是结点的指针
返回值：为空返回TRUE，不为空返回FALSE
*/

Status ListAppendToEnd(List* pList, void* pData);
/*
功能：尾部插入数据
参数：第一个参数是链表的指针，第二个参数是传入数据的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

Status ListInsertAfter(List* pList, ListNode* pNode, void* pData);
/*
功能：某节点后插入数据
参数：第一个参数是链表的指针，第二个参数是结点的指针，第三个参数是传入数据的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

Status ListDeleteFirstNode(List* pList);
/*
功能：删除第一个结点
参数：参数是链表的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

Status ListDeleteLastNode(List* pList);
/*
功能：删除最后一个结点
参数：参数是链表的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

Status ListDeleteNode(List* pList, ListNode* pNode);
/*
功能：删除某一结点
参数：第一个参数是链表的指针，第二个参数是结点的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

Bool isThisOne(void* listData, void* pData);
/*
功能：判断链表上的数据和关键字是否相同
参数：第一个参数为链表上数据的指针，第二个参数为关键字的指针
返回值：相同则返回TRUE，不同则返回FALSE
*/

ListNode* ListSearch(List* pList, void* pKey, Bool(*isThisOne)(void*, void*));
/*
功能：查找数据的位置
参数：第一个参数是链表的指针，第二个参数是查找数据的指针，第三个参数是函数指针，isThisOne是把数据记录和关键字做比较的函数
返回值：如果成功，返回指向节点的指针；如果失败，返回NULL。
*/


#endif
