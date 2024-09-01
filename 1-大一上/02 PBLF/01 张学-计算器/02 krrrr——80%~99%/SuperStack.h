#ifndef SUPERSTACK_H
#define SUPERSTACK_H

#define DEBUG 0
/*调试模式*/

#define STACK_INIT_SIZE 1000
/*栈的初始容量*/ 
#define STACK_INCREMENT 10
/*栈满时扩充的容量 */


typedef enum {ERROR=0,OK=1} Status;
typedef enum {FALSE=0,TRUE=1} Bool;

typedef struct {
    void* pBase;
    void* pTop;
    int elementSize;
    int stackSize;
}Stack;
/*通用栈的构建*/ 

Stack* Stack_Construct(int sizeOfElement);
/*函数功能：构造新的栈
 *输入参数：栈元素大小sizeofElement
 *返回值：新栈,失败返回空指针
 */

void Stack_Destruct(Stack* pStack);
/*函数功能：析构栈
 *输入参数：栈指针pStack
 *返回值：无
 */

void Stack_Clear(Stack* pStack);
/*函数功能：清空栈
 *输入参数：栈指针pStack
 *返回值：无
 */

Bool Stack_IsEmpty(Stack* pStack);
/*函数功能：判断栈是否为空
 *输入参数：栈指针pStack
 *返回值：布尔型
 */

int Stack_Length(Stack* pStack);
/*函数功能：获取栈的长度
 *输入参数；栈指针pStack
 *返回值：栈长度
 */

Status Stack_GetTop(Stack* pStack,void* pElem);
/*函数功能：取栈顶元素
 *输入参数：栈指针pStack，栈顶元素指针pElem
 *返回值：执行状态
 */

Status Stack_Push(Stack* pStack,void* pElem);
/*函数功能：入栈
 *输入参数：栈指针pStack，进栈元素指针pElem
 *返回值：执行状态
 */

Status Stack_Pop(Stack* pStack,void* pElem);
/*函数功能：出栈
 *输入参数：栈指针pStack，出栈元素指针pElem
 *返回值：执行状态
 */

Status Stack_Traverse(Stack* pStack,Status (*visit)(void*));
/*函数功能：遍历栈
 *输入参数：栈指针pStack，数据元素指针pElem
 *返回值：执行状态
 */
#endif 
