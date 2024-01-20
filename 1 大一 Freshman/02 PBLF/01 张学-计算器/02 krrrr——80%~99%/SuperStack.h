#ifndef SUPERSTACK_H
#define SUPERSTACK_H

#define DEBUG 0
/*����ģʽ*/

#define STACK_INIT_SIZE 1000
/*ջ�ĳ�ʼ����*/ 
#define STACK_INCREMENT 10
/*ջ��ʱ��������� */


typedef enum {ERROR=0,OK=1} Status;
typedef enum {FALSE=0,TRUE=1} Bool;

typedef struct {
    void* pBase;
    void* pTop;
    int elementSize;
    int stackSize;
}Stack;
/*ͨ��ջ�Ĺ���*/ 

Stack* Stack_Construct(int sizeOfElement);
/*�������ܣ������µ�ջ
 *���������ջԪ�ش�СsizeofElement
 *����ֵ����ջ,ʧ�ܷ��ؿ�ָ��
 */

void Stack_Destruct(Stack* pStack);
/*�������ܣ�����ջ
 *���������ջָ��pStack
 *����ֵ����
 */

void Stack_Clear(Stack* pStack);
/*�������ܣ����ջ
 *���������ջָ��pStack
 *����ֵ����
 */

Bool Stack_IsEmpty(Stack* pStack);
/*�������ܣ��ж�ջ�Ƿ�Ϊ��
 *���������ջָ��pStack
 *����ֵ��������
 */

int Stack_Length(Stack* pStack);
/*�������ܣ���ȡջ�ĳ���
 *���������ջָ��pStack
 *����ֵ��ջ����
 */

Status Stack_GetTop(Stack* pStack,void* pElem);
/*�������ܣ�ȡջ��Ԫ��
 *���������ջָ��pStack��ջ��Ԫ��ָ��pElem
 *����ֵ��ִ��״̬
 */

Status Stack_Push(Stack* pStack,void* pElem);
/*�������ܣ���ջ
 *���������ջָ��pStack����ջԪ��ָ��pElem
 *����ֵ��ִ��״̬
 */

Status Stack_Pop(Stack* pStack,void* pElem);
/*�������ܣ���ջ
 *���������ջָ��pStack����ջԪ��ָ��pElem
 *����ֵ��ִ��״̬
 */

Status Stack_Traverse(Stack* pStack,Status (*visit)(void*));
/*�������ܣ�����ջ
 *���������ջָ��pStack������Ԫ��ָ��pElem
 *����ֵ��ִ��״̬
 */
#endif 
