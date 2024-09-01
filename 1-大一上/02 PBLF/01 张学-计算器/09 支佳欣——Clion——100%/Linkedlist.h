#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//节点定义
typedef struct ListNode{
    struct ListNode *pNextNode;//指针域
    void *pElement;//数据域
}ListNode;

//定义链表
typedef struct {
    ListNode *pFirstNode;//节点
    int elementSize;//数据长度
    int length;//链表长度
}List;

//构造链表
List* List_Construct(int sizeOfElement);
//生成一个链表，链表的元素大小为sizeOfElement，返回指向新链表的指针

//生成节点
ListNode* List_MakeNode(List* pList,void *pElement);
//在pList指向的链表中生节点，节点的元素为pElement所指向的值，返回一个指向新节点的指针

//释放节点
void List_FreeNode(ListNode *pNode);

//清空链表
void List_Clear(List* pList);

//析构链表
void List_Destruct(List* pList);

//获取链表场长度
int List_GetLength(List* pList);
//返回pList指向的链表的长度

//获取链栈栈顶元素的值
void* List_GetElement(List* pList);

//判断链表是否为空
bool List_IsEmpty(List* pList);
//如果pList指向的链表不为空，则返回false。否则返回true

//链头插入元素
bool List_InsertAtFront(List* pList,void * pElement);
//将pElement指向的元素存入pList指向的链表的头结点，如果插入成功，返回true，否则返回false

//弹出头结点
void* List_DeleteFirstNode(List* pList);

//取节点上的数据
void* List_GetData(ListNode* pNode);

//在尾部追加数据
bool List_AppendToEnd(List* pList,void* pElement);
//将pElement指向的元素加到pList指向的链表的末尾，若添加成功，返回true，否则返回false

//在某节点后插入数据
bool List_InsertAfter(List* pList,ListNode* pNode,void* pElement);
//在pList指向的链表中找到pNode指向的节点，在此节点之后添加一个新的节点，新的节点的数据域元素是pElement指向的元素
//若添加成功则返回ture，否则返回false

//在某节点前插入数据
bool List_InsertBefore(List* pList,ListNode* pNode,void* pElement){

}

//把数据插入链表的第i个位置
bool List_Insert(List* pList,int i,void* pElement);
//向pList所指的链表中的第i个位置上添加节点，节点的数据为pElement所指数据，成功返回true，否则返回false

//删除最后一个节点
bool List_DeleteLastNode(List* pList);
//删除pList指向的链表的最后一个节点，若删除成功则返回true，否则返回false

//删除指定节点
bool List_DeleteNode(List* pList,ListNode* pNode);
//删除pList指向的链表中的pNode所指向的节点，删除成功返回true，否则返回false

//查找数据
ListNode* List_Srearch(List* pList,void* pKey,bool (*isThisOne)(void*,void*));
//在pList指向的链表中查找关键字为pKey所指向的值的节点，若找到，则返回指向这个节点的指针，否则返回空指针
//传入的函数为判断数据记录的关键字是否与给定的关键字相等，若相等返回true，否则返回false
//bool IsThisOne(int* pData,int* pKey){return (*pData==*pKey)?True:FALSE;}


//遍历链表
bool List_Traverse(List* pList,bool (*visit)(void*));
//用visit操作遍历链表，如果成功，返回true，否则返回false，visit函数的参数是节点上的数据指针，成功返回true，否则返回false

//倒置链表
void ReverseList(List* pList);
//将pList指向的链表倒置翻转

//获取第一个节点的地址
ListNode* List_GetFirstNode(List* pList);
//返回指向第一个节点的指针

//返回最后一个节点的地址
ListNode* GetLastNode(List* pList);
//返回指向最后一个节点的指针

//返回第i个节点的地址
ListNode* List_GetNode(List* pList,int i);
//返回指向第i个节点的指针

//返回节点序号
int List_GetOrderNumber(List* pList,ListNode* pNode);
//返回pList指向的链表中的pNode所指向的节点的序号，如果成功，则返回该节点的序号，否则返回0

//返回节点的直接前驱
ListNode* List_GetPriorNode(List* pList,ListNode* pNode);
//返回pList所指向的链表中pNode所指节点的前一个节点的地址；

//返回节点的直接后继
ListNode* List_GetNextNode(ListNode* pNode);
//返回pNode所指向的节点的下一个节点的地址

//为某节点设置数据
bool List_SetData(ListNode* pNode,void* pElement){
    pNode->pElement=pElement;
};
//向pNode所指向的节点添加pElement所指的数据，成功返回true，否则返回false

//为链表上的数据排序
bool List_Sort(List* pList,void (*rule)(void*)){

};
//将链表中的数字按大小排序（顺序）（冒泡排序），成功返回true，否则返回false












