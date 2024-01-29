#ifndef LINkEDLIST_H
#define LINKEDLIST_H

//����Status��Bool���͵Ķ���
#include "common.h" 

//��������ڵ�
typedef struct ListNode{
	struct ListNode *pNextNode;
	void *pData;
} ListNode;
//������������
typedef struct {
	ListNode* pFirstNode;
	int length;
	int dataSize;
} List;

ListNode* List_makeNode(List* pList, void* pData);
/* ������List_makeNode
 * --------------------
 * ����һ���½ڵ㣬���洢ָ�������ݡ�
 *
 * pList��ָ��Ҫ�����½ڵ�������ָ�롣
 * pData��ָ��Ҫ�洢���½ڵ��е����ݵ�ָ�롣
 * ����ֵ��ָ���½ڵ��ָ�롣�������ʧ�ܣ�����NULL��
 */

void List_freeNode(ListNode* pNode);
/* ������List_freeNode
 * --------------------
 * �ͷ�һ���ڵ㼰��洢�������ڴ档
 *
 * pNode��ָ��Ҫ�ͷŵĽڵ��ָ�롣
 */

List* List_Construct(int sizeOfData); 
/* ������ListConstruct
 * --------------------
 * ����һ��������
 *
 * sizeOfData���ڵ������ݵĴ�С��
 * ����ֵ��ָ���������ָ�롣�������ʧ�ܣ�����NULL��
 */

void List_Destruct(List* pList);
/* ������ListDestruct
 * -------------------
 * ����һ�������ͷ����е����нڵ�������ڴ档
 *
 * pList��ָ��Ҫ���ٵ������ָ�롣
 */

void List_Clear(List* pList);
/* ������ListClear
 * ----------------
 * ���һ�������ͷ����е����нڵ�������ڴ档
 *
 * pList��ָ��Ҫ��յ������ָ�롣
 */

int List_GetLength(List* pList);
/* ������ListGetLength
 * --------------------
 * ��ȡ�����нڵ��������
 *
 * pList��ָ��Ҫ��ȡ�ڵ������������ָ�롣
 * ����ֵ�������нڵ��������
 */

void* List_GetData(ListNode* pNode);
/* ������ListGetData
 * -----------------
 * ��ȡ����ڵ��д洢������ָ�롣
 *
 * pNode��ָ��Ҫ��ȡ����ָ��Ľڵ��ָ�롣
 * ����ֵ���洢�ڽڵ��е�����ָ�롣
 */

Bool List_IsEmpty(List* pList);
/* ������ListIsEmpty
 * -----------------
 * �ж������Ƿ�Ϊ�ա�
 *
 * pList��ָ��Ҫ�жϵ������ָ�롣
 * ����ֵ���������Ϊ�գ�����TRUE�����򷵻�FALSE��
 */

Status List_InsertAtFront(List* pList, void* pData);
/* ������ListInsertAtFront
 * -----------------------
 * ������ͷ������һ���ڵ㡣
 *
 * pList��ָ��Ҫ����ڵ�������ָ�롣
 * pData��ָ��Ҫ�洢���½ڵ��е����ݵ�ָ�롣
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

Status List_AppendToEnd(List* pList, void* pData);
/* ������ListAppendToEnd
 * ---------------------
 * ������ĩβ���һ���ڵ㡣
 *
 * pList��ָ��Ҫ��ӽڵ�������ָ�롣
 * pData��ָ��Ҫ�洢���½ڵ��е����ݵ�ָ�롣
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

Status List_InsertAfter(List* pList, ListNode* pNode, void* pData);
/* ������ListInsertAfter
 * ---------------------
 * ��ָ���ڵ�������һ���ڵ㡣
 *
 * pList��ָ��Ҫ����ڵ�������ָ�롣
 * pNode��ָ��Ҫ�����������½ڵ�Ľڵ��ָ�롣
 * pData��ָ��Ҫ�洢���½ڵ��е����ݵ�ָ�롣
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

Status List_DeleteFirstNode(List* pList);
/* ������ListDeleteFirstNode
 * -------------------------
 * ɾ������ͷ���Ľڵ㡣
 *
 * pList��ָ��Ҫɾ���ڵ�������ָ�롣
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

Status List_DeleteLastNode(List* pList);
/* ������ListDeleteLastNode
 * ------------------------
 * ɾ������ĩβ�Ľڵ㡣
 *
 * pList��ָ��Ҫɾ���ڵ�������ָ�롣
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

Status List_DeleteNode(List* pList, ListNode* pNode);
/* ������ListDeleteNode
 * --------------------
 * ɾ��ָ���Ľڵ㡣
 *
 * pList��ָ��Ҫɾ���ڵ�������ָ�롣
 * pNode��ָ��Ҫɾ���Ľڵ��ָ�롣
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

ListNode* List_Search(List* pList, void* pKey, Bool (*isThisOne)(void*, void*));
/* ������ListSearch
 * -----------------
 * �������в���ָ�������ݡ�
 *
 * pList��ָ��Ҫ�������ݵ������ָ�롣
 * pKey��ָ��Ҫ���ҵ����ݵ�ָ�롣
 * isThisOne��ָ�����ڱȽ����ݵĺ�����ָ�롣
 * ����ֵ������ҵ�ָ�������ݣ�����ָ����������ݵĽڵ��ָ�룬���򷵻�NULL��
 */

Status List_Traverse(List* pList, Status (*visit)(void*));
/* ������ListTraverse
 * -------------------
 * ���������е����нڵ㣬����ÿ���ڵ�ִ��ָ���Ĳ�����
 *
 * pList��ָ��Ҫ�����������ָ�롣
 * visit��ָ��Ҫִ�еĲ����ĺ�����ָ�롣
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */
ListNode* List_GetFirstNode(List* pList);
/* ������List_GetFirstNode
 * -----------------------
 * ��ȡ����ĵ�һ���ڵ㡣
 *
 * pList: ����ָ�롣
 *
 * ����ֵ����һ���ڵ��ָ�룬�������Ϊ���򷵻�NULL��
 */

ListNode* List_GetLastNode(List* pList);
/* ������List_GetLastNode
 * ----------------------
 * ��ȡ��������һ���ڵ㡣
 *
 * pList: ����ָ�롣
 *
 * ����ֵ�����һ���ڵ��ָ�룬�������Ϊ���򷵻�NULL��
 */

ListNode* List_GetNode(List* pList, int i);
/* ������List_GetNode
 * -------------------
 * ��ȡ����ĵ�i���ڵ㡣
 *
 * pList: ����ָ�롣
 * i: �ڵ���������0��ʼ��
 *
 * ����ֵ����i���ڵ��ָ�룬��������ڵ�i���ڵ��򷵻�NULL��
 */




#endif
