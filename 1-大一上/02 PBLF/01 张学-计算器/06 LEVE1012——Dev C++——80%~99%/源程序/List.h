#ifndef LISTNODE_H
#define LISTNODE_H

//����Status��Bool���͵Ķ���
#include "common.h"

//����ڵ㶨��
typedef struct ListNode {
    struct ListNode *pNextNode;
    void* pData;
} ListNode;

//����ͷ�ڵ㶨��
typedef struct {
	ListNode *pFirstNode;
	int length;
	int dataSize; 
} List;

Status visit(void* pData);
/* ������freeData
 * ------------------
 * ���pData������������Ƶķ������ݵĺ��� 
 *
 * pData����Ҫ���ʵ�����ָ�롣
 *
 * ����ֵ���ɹ������򷵻�TRUE�����򷵻�FALSE��
 */

ListNode* List_makeNode(List *pList, void* pData);
/* ������List_makeNode 
 * ------------------
 * ����һ���ڵ㡣
 *
 * pList��ָ�������ָ�� 
 * pData����Ҫ���������ָ�롣
 *
 * ����ֵ��ָ���½ڵ��ָ�롣
 */

void List_freeNode(ListNode* pNode);
/* ������List_freeNode 
 * ------------------
 * �ͷŽڵ㣬����freeData�����ͷŽڵ�����ݡ� 
 *
 * pNode��ָ��ڵ��ָ�롣
 *
 * ����ֵ���ޡ�
 */

List* List_Construct(int sizeOfData);
/* ������List_Construct
 * ---------------------
 * ���첢��ʼ��һ������
 *
 * ����ֵ��ָ�������ָ�롣
 */
 
void* List_GetData(ListNode* pNode);
/* ������List_GetData 
 * ------------------
 * ���pNode�ڵ������ָ�롣
 *
 * pNode����ִ�в����Ľڵ㡣
 *
 * ����ֵ��ָ��pNode������ָ�롣
 */

void List_Clear(List* pList);
/* ������List_Clear 
 * ------------------
 * ��������ա� 
 *
 * pList��ָ�������ָ�롣
 *
 * ����ֵ���ޡ� 
 */
 
int List_GetLength(List* pList);
/* ������List_Length
 * ------------------
 * ��������ĳ��ȡ�
 *
 * pList��ָ�������ָ�롣
 *
 * ����ֵ������ĳ��ȡ�
 */

Status List_InsertAtFront(List* pList, void* pData);
/* ������List_InsertAtFront
 * ----------------
 * �������ͷ���������ݡ� 
 *
 * pList��ָ��ջ��ָ�롣
 * pData��ָ��Ҫ��������ݵ�ָ�롣
 *
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */

Status List_AppendToEnd(List* pList, void* pData);
/* ������List_AppendToEnd
 * ----------------
 * �������β��׷�����ݡ� 
 *
 * pList��ָ�������ָ�롣
 * pData��ָ��Ҫ׷�ӵ����ݵ�ָ�롣
 *
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */
 
Status List_InsertAfter(List* pList,ListNode *pNode, void* pData);
/* ������List_InsertAfter
 * ----------------
 * �������pNode�ڵ��������ݡ� 
 *
 * pList��ָ�������ָ�롣
 * pNode�����������ݵĽڵ�ָ�롣 
 * pData��ָ��Ҫ׷�ӵ����ݵ�ָ�롣
 *
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */
 
Status List_DeleteFirstNode(List* pList);
/* ������List_DeleteFirstNode
 * ----------------
 * ɾ����һ���ڵ㡣 
 *
 * pList��ָ�������ָ�롣
 *
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */ 
 
Status List_DeleteLastNode(List* pList);
/* ������List_DeleteLastNode
 * ----------------
 * ɾ�����һ���ڵ㡣 
 *
 * pList��ָ�������ָ�롣
 *
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */ 
 
Status List_DeleteNode(List* pList, ListNode* pNode);
/* ������List_DeleteNode
 * ----------------
 * ɾ��ָ���ڵ㡣 
 *
 * pList��ָ�������ָ�롣
 * pNode����Ҫɾ����ָ���ڵ㡣 
 *
 * ����ֵ������״̬���ɹ�����OK��ʧ�ܷ���ERROR��
 */ 
 
Bool List_IsEmpty(List* pList);
/* ������List_IsEmpty
 * -------------------
 * ��������Ƿ�Ϊ�ա�
 *
 * pList��ָ�������ָ�롣
 *
 * ����ֵ��������Ϊ�շ���TRUE�����򷵻�FALSE��
 */

Status List_Traverse(List* pList, Status (*visit) (void*)); 
/* ������List_Traverse 
 * -------------------
 * ��visit������������ 
 *
 * pList��ָ�������ָ�롣
 * visit��ʵ�ֱ����Ĳ�������������Ϊ����ָ�롣 
 *
 * ����ֵ���ɹ������򷵻�TRUE�����򷵻�FALSE��
 */
 
void List_Destruct(List* pList);
/* ������List_Destroy
 * -------------------
 * ���������ͷ��ڴ档
 *
 * pStack��ָ��ջ��ָ�롣
 *
 * ����ֵ���ޡ�
 */


 #endif
 
