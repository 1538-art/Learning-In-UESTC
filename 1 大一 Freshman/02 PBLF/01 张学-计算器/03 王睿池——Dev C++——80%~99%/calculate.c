/* 计算器 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define SIZE 50
#define EXTRA_SIZE 5

typedef double DoubleElement;//定义一个数据栈
typedef char CharElement;//定义一个字符栈
typedef enum {ERROR=0,OK=1} Status;
typedef enum {FLASE=0,TRUE=1} Bool;
typedef struct{
	DoubleElement *pBase;
	DoubleElement *pTop;
	int size;
}Stack1;
typedef struct{
	CharElement *pBase;
	CharElement *pTop;
	int size;
}Stack2;

Status InitStack1(Stack1 *pStack);
Status InitStack2(Stack2 *pStack);
/*功能:将栈初始化
 *参数:pStack指向被初始化的栈
 *返回:初始化成功返回OK，失败返回ERROR
 */
void FreeStack1(Stack1 *pStack);
void FreeStack2(Stack2 *pStack);
/*功能:释放栈元素的内存
 *参数:pStack指向栈的指针
 *返回值:无
 */
void ClearStack1(Stack1 *pStack);
void ClearStack2(Stack2 *pStack);
/*功能:清空栈中数据元素
 *参数:pStack指向栈的指针
 *返回值:无
 */
Bool Stack_IsEmpty1(Stack1 *pStack);
Bool Stack_IsEmpty2(Stack2 *pStack);
/*功能:判断一个栈是否为空
 *参数pStack:指向栈的指针
 *返回值:如果为空返回TRUE，不为空返回FLASE
 */
int Stack_Length1(Stack1 *pStack);
int Stack_Length2(Stack2 *pStack);
/*功能:计算栈的长度
 *参数pStack:指向栈的指针
 *返回值:栈的长度
 */
Status Stack_GetTop1(Stack1 *pStack,DoubleElement *pElem);
Status Stack_GetTop2(Stack2 *pStack,CharElement *pElem);
/*功能:读取栈顶元素
 *参数:pStack是栈指针，pElem是数据元素指针
 *返回值:读取的栈顶元素放在*pElem里，成功返回OK，失败返回ERROR
 */
Status Stack_Push1(Stack1 *pStack,DoubleElement *pElem);
Status Stack_Push2(Stack2 *pStack,CharElement *pElem);
/*功能:将元素压入栈
 *参数:pStack指向栈的指针，pElem是指向进栈数据元素的指针
 *返回值:把pElem指向的数据压入pStack指向的栈,成功返回OK，失败返回ERROR
 */
Status Stack_Pop1(Stack1 *pStack,DoubleElement *pElem);
Status Stack_Pop2(Stack2 *pStack,CharElement *pElem);
/*功能:弹出栈顶元素
 *参数:pStack指向栈的指针，pElem指向弹出栈数据元素的指针
 *返回值:弹出的元素指向pElem指向的内存中，成功返回OK，失败返回ERROR
 */
Status StackTraverse1(Stack1* pStack,Status(*visit)(DoubleElement*));
Status StackTraverse2(Stack2* pStack,Status(*visit)(CharElement*));
/*功能:遍历由pStack指向的栈
 *参数:pStack指向栈的指针
 *visit:函数指针，参数是元素数据的指针
 *返回值:对栈的每一个元素进行visit操作，成功返回OK，失败返回ERROR
 */
int priority(char op);
/*功能:判断符号的优先级
 *参数:op表示字符
 *返回值:如果是其他返回0
 *如果是'+''-'返回1
 *如果是'*''/'返回2
 *如果是'^'返回3
 */
double myPow(double a,int b);
/*功能:对乘方进行运算
 *参数:a(底数)，b(指数)，result(最终结果)
 *返回值:返回result
 */
Status calculate(char* expression,double* result);
/*功能:将栈中的数据进行运算
 *参数:expression(存放数据的数组),result(取值时的最终结果)
 *返回值:如果栈为空，返回ERROR,若栈不为空，返回OK
 */

Status InitStack1(Stack1 *pStack){
	pStack->pBase=(DoubleElement*)malloc(
	SIZE*sizeof(DoubleElement));
	if(pStack->pBase==NULL){
		return ERROR;
	}
	pStack->pTop=pStack->pBase;
	pStack->size=SIZE;
	return OK;
}

Status InitStack2(Stack2 *pStack){
	pStack->pBase=(CharElement*)malloc(
	SIZE*sizeof(CharElement));
	if(pStack->pBase==NULL){
		return ERROR;
	}
	pStack->pTop=pStack->pBase;
	pStack->size=SIZE;
	return OK;
}

void FreeStack1(Stack1 *pStack){
	free(pStack->pBase);
	pStack->pBase=NULL;
	pStack->pTop=NULL;
	pStack->size=0;
	return;
}

void FreeStack2(Stack2 *pStack){
	free(pStack->pBase);
	pStack->pBase=NULL;
	pStack->pTop=NULL;
	pStack->size=0;
	return;
}

void ClearStack1(Stack1 *pStack){
	pStack->pTop=pStack->pBase;
}

void ClearStack2(Stack2 *pStack){
	pStack->pTop=pStack->pBase;
}

Bool Stack_IsEmpty1(Stack1 *pStack){
	if(pStack->pTop=pStack->pBase){
		return TRUE;
	}
	else{
		return FLASE;
	}
}

Bool Stack_IsEmpty2(Stack2 *pStack){
	if(pStack->pTop=pStack->pBase){
		return TRUE;
	}
	else{
		return FLASE;
	}
}

int Stack_Length1(Stack1 *pStack){
	return pStack->pTop-pStack->pBase;
}

int Stack_Length2(Stack2 *pStack){
	return pStack->pTop-pStack->pBase;
}

Status Stack_GetTop1(Stack1 *pStack,DoubleElement *pElem){
	if(pStack->pTop==pStack->pBase){
		return ERROR;
	}
	*pElem=*(pStack->pTop-1);
	return OK;
}

Status Stack_GetTop2(Stack2 *pStack,CharElement *pElem){
	if(pStack->pTop==pStack->pBase){
		return ERROR;
	}
	*pElem=*(pStack->pTop-1);
	return OK;
}

Status Stack_Push1(Stack1 *pStack,DoubleElement *pElem){
	int newSize;
	DoubleElement *pTemp;
	DoubleElement *pTop;
	if(pStack->pTop-pStack->pBase>=pStack->size){
		newSize=pStack->size+EXTRA_SIZE;
		pTemp=(DoubleElement*)realloc(pStack->pBase,newSize*sizeof(DoubleElement));
     	if(pTemp==NULL){
	  	return ERROR;
	}
	    else{
		pStack->pBase=pTemp;
		pStack->pTop=pStack->pBase+pStack->size;
		pStack->size=newSize;
	}
}
    *(pStack->pTop)=*pElem;
    pStack->pTop++;
    return OK;
}

Status Stack_Push2(Stack2 *pStack,CharElement *pElem){
	int newSize;
	CharElement *pTemp;
	CharElement *pTop;
	if(pStack->pTop-pStack->pBase>=pStack->size){
		newSize=pStack->size+EXTRA_SIZE;
		pTemp=(CharElement*)realloc(pStack->pBase,newSize*sizeof(CharElement));
     	if(pTemp==NULL){
	  	return ERROR;
	}
	    else{
		pStack->pBase=pTemp;
		pStack->pTop=pStack->pBase+pStack->size;
		pStack->size=newSize;
	}
}
    *(pStack->pTop)=*pElem;
    pStack->pTop++;
    return OK;
}

Status Stack_Pop1(Stack1 *pStack,DoubleElement *pElem){
	if(pStack->pTop=pStack->pBase){
		return ERROR;
	}
	else{
		pStack->pTop--;
		*pElem=*(pStack->pTop);
		return OK;
	}
}

Status Stack_Pop2(Stack2 *pStack,CharElement *pElem){
	if(pStack->pTop=pStack->pBase){
		return ERROR;
	}
	else{
		pStack->pTop--;
		*pElem=*(pStack->pTop);
		return OK;
	}
}

Status StackTraverse1(Stack1* pStack,Status(*visit)(DoubleElement*)){
    int i,n;
    n=Stack_Length1(pStack);
    for(i=0;i<n;i++){
        if(visit(&(pStack->pBase[i]))==ERROR){
            return ERROR;
        }
    }
    return OK;
}

Status StackTraverse2(Stack2* pStack,Status(*visit)(CharElement*)){
    int i,n;
    n=Stack_Length2(pStack);
    for(i=0;i<n;i++){
        if(visit(&(pStack->pBase[i]))==ERROR){
            return ERROR;
        }
    }
    return OK;
}

//判断符号的优先级
int priority(char op){
	if(op=='^')
	    return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}
//进行乘方的运算
double myPow(double a,int b){
	double result=1.0;
	int i;
	for(i=1;i<=abs(b);i++){
	    result*=a;
	}
	if(b<0){
		result=1.0/result;
	}
	return result;
}

//calculate
Status calculate(char* expression,double* result){
    Stack1 numStack;//定义一个数据栈
    Stack2 charStack;//定义一个字符栈
    if(InitStack1(&numStack)==ERROR||InitStack2(&charStack)==ERROR){
    	printf("ERROR");
    	return ERROR;
	}
	
	int i=0;
    char ch;
    double num = 0.0;
    double num1, num2;
    while ((ch = expression[i]) != '\n'){
    	if(isdigit(ch)||ch=='.'){
            //判断数字
    		char temp[50];
            int j = 0;
            while (isdigit(ch) || ch == '.') {
                temp[j++] = ch;
                i++;
                ch = expression[i];
            }
            i--;
            temp[j] = '\0';
            num = atof(temp);//将字符转为数字
            Stack_Push1(&numStack,&num);//将数字压入数据栈内
		}else if(ch=='('){
			Stack_Push2(&charStack,&ch);//若为左括号，直接进入字符栈
		}
		else if((ch==')'||(priority(ch) > priority(*(charStack.pTop - 1)) || (*(charStack.pTop - 1) == '(' && ch != ')')||Stack_IsEmpty2(&charStack)))){
            // 当为右括号、当前运算符优先级高、栈顶是左括号且当前运算符不是右括号(左括号不输出)
			Stack_Push2(&charStack,&ch);
			if(!Stack_IsEmpty2(&charStack)){
				printf("OK");
			}
		}
		else{
            //优先级不高于栈顶，压出形成后缀表达式，进行运算
			while(!Stack_IsEmpty2(&charStack)&&((priority(ch)<=priority(*(charStack.pTop - 1))) || (*(charStack.pTop - 1) == '(' && ch != ')'))){
				Stack_Pop2(&charStack,&ch);
				Stack_Pop1(&numStack,&num2);
				Stack_Pop1(&numStack,&num1);
				
				switch(ch){
					case '+':
						num=num1+num2;//加法
						break;
					case '-':
						num=num1-num2;//减法
						break;
					case '*':
						num=num1*num2;//乘法
						break;
					case '/':
						if(num2==0){
							FreeStack1(&numStack);
							FreeStack2(&charStack);
							return ERROR;//除数不为0
						}
						num=num1/num2;//除法
						break;
					case '^':
					    num=myPow(num1,num2);//乘方
						break;
				}
				Stack_Push1(&numStack,&num);//将结果压入栈
			}
			if(ch!=')'){
				Stack_Push2(&charStack,&ch);//将字符压入栈
			}else{
				char topchar;
				Stack_Pop2(&charStack,&topchar);//弹出栈顶元素
			}
		}
		i++;//进行循环
	}
	while(!Stack_IsEmpty2(&charStack)){
		        Stack_Pop2(&charStack,&ch);//将字符压出
				Stack_Pop1(&numStack,&num2);//将
				Stack_Pop1(&numStack,&num1);
				switch(ch){
					case '+'://加法
						num=num1+num2;
						break;
					case '-'://减法
						num=num1-num2;
						break;
					case '*'://乘法
						num=num1*num2;
						break;
					case '/':
						if(num2==0){//除数不为0
							FreeStack1(&numStack);
							FreeStack2(&charStack);
							return ERROR;
						}
						num=num1/num2;//除法
						break;
					case '^':
					    num=myPow(num1,num2);//乘方
						break;
			}
			Stack_Push1(&numStack,&num);//将结果入栈
	}
	if (!Stack_IsEmpty1(&numStack)) {
        Stack_GetTop1(&numStack,result); //获得最终结果
    }
    FreeStack1(&numStack);//释放数据栈
	FreeStack2(&charStack);//释放字符栈
	return OK;
}
//主函数
int main(){
	char expression[SIZE];//定义一个数组
	double result;//一个数字表示结果
	
	printf("请输入您的表达式:");
	fgets(expression,sizeof(expression),stdin);
	result = calculate(expression, &result);
    printf("您的结果为:%lf",result);
	return 0;
}