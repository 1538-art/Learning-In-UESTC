#include<stdio.h>
#include<stdlib.h>
#define SIZE 21
#define INCREASEMENT 10
typedef enum {ERROR=0,OK=1} Status;
typedef enum {FALSE=0,TRUE=1} Bool;
typedef struct{ //栈的结构
    float *pBase;
    float *pTop;
    int size;
} Stack1;
typedef struct{ //栈的结构
    char *pBase;
    char *pTop;
    int size;
} Stack2;
typedef struct{ //优先级
    char a;
    int b;
} Rank;
Status Stack1_Intit(Stack1* pStack);
/*函数功能：初始化浮点数栈。
 *输入参数：pStack指向被初始化的浮点数栈。
 *返回值：如果成功，返回OK；如果失败，返回ERROR。
 */
Status Stack2_Intit(Stack2* pStack);
/*函数功能：初始化字符栈。
 *输入参数：pStack指向被初始化的字符栈。
 *返回值：如果成功，返回OK；如果失败，返回ERROR。
 */
void Stack1_Free(Stack1* pStack);
/*函数功能：释放浮点数栈。
 *输入参数：pStack指向被释放的浮点数栈。
 *返回值：无。
 */
void Stack2_Free(Stack2* pStack);
/*函数功能：释放字符栈。
 *输入参数：pStack指向被释放的字符栈。
 *返回值：无。
 */
void Stack1_Clear(Stack1* pStack); 
/*函数功能：清空浮点数栈。
 *输入参数：pStack指向被清空的浮点数栈。
 *返回值：无。
 */
void Stack2_Clear(Stack2* pStack);
/*函数功能：清空字符栈。
 *输入参数：pStack指向被清空的字符栈。
 *返回值：无。
 */
int Stack1_Length(Stack1* pStack); 
/*函数功能：求浮点数栈的长度。
 *输入参数：pStack指向查询的浮点数栈。
 *返回值：栈的长度。
 */
int Stack2_Length(Stack2* pStack);
/*函数功能：求字符栈的长度。
 *输入参数：pstack指向查询的字符栈。
 *返回值：栈的长度。
 */
Status Stack1_GetTop(Stack1* pStack,float* pElem); 
/*函数功能：取浮点数栈的顶部元素。
 *输入参数：pStack指向被操作的栈，*pElem存放取出的数据元素。
 *返回值：如果成功，返回OK；如果失败，返回ERROR。
 */
Status Stack2_GetTop(Stack2* pStack,char* pElem);
/*函数功能：取字符栈的顶部元素。
 *输入参数：pStack指向被操作的栈，*pElem存放取出的数据元素。
 *返回值：如果成功，返回OK；如果失败，返回ERROR。
 */
Status Stack1_Push(Stack1* pStack,float* pElem); 
/*函数功能：浮点数入栈。
 *输入参数：pStack指向被操作的栈，pElem指向被压入的数据元素。
 *返回值：如果成功，返回OK；如果失败，返回ERROR。
 */
Status Stack2_Push(Stack2* pStack,char* pElem);
/*函数功能：字符入栈。
 *输入参数：pStack指向被操作的栈，pElem指向被压入的数据元素。
 *返回值：如果成功，返回OK；如果失败，返回ERROR。
 */
Status Stack1_Pop(Stack1* pStack,float* pElem); 
/*函数功能：浮点数出栈。
 *输入参数：pStack指向被操作的栈，*pElem存储弹出的数据元素。
 *返回值：如果成功，返回OK；如果失败，返回ERROR。
 */
Status Stack2_Pop(Stack2* pStack,char* pElem);
/*函数功能：字符出栈。
 *输入参数：pStack指向被操作的栈，*pElem存储弹出的数据元素。
 *返回值：如果成功，返回OK；如果失败，返回ERROR。
 */
Bool Stack1_IsEmpty(Stack1* pStack);
/*函数功能：判断浮点数栈是否为空。
 *输入参数：pStack指向判断的浮点数栈。
 *返回值：如果栈为空，返回TRUE；如果栈不为空，返回FALSE。
 */
Bool Stack2_IsEmpty(Stack2* pStack);
/*函数功能：判断字符栈是否为空。
 *输入参数：pStack指向判断的字符栈。
 *返回值：如果栈为空，返回TRUE；如果栈不为空，返回FALSE。
 */
Status Stack1_Traverse(Stack1*pStack,Status(*visit)());
/*函数功能：遍历栈。
 *输入参数：pStack指向要遍历的浮点数栈，visit指向操作函数。
 *返回值：如果函数对栈中每个元素操作成功，返回OK，否则返回ERROR。
 */
Status Stack2_Traverse(Stack2*pStack,Status(*visit)());
/*函数功能：遍历栈。
 *输入参数：pStack指向要遍历的字符栈，visit指向操作函数。
 *返回值：如果函数对栈中每个元素操作成功，返回OK，否则返回ERROR。
 */
float power(float x,int a);
/*函数功能：计算乘方。
 *输入参数：x是底数，a是指数。
 *返回值：乘方计算结果。
 */
float CharToFloat(char a[]); 
/*函数功能：将字符转成浮点数。
 *输入参数：a是字符串数组。
 *返回值：浮点数值。
 */
void Priority(Rank bt[]); 
/*函数功能：定义符号的优先级。
 *输入参数：bt存储对优先级的定义。
 *返回值：无。
 */
int GetRank(char c);
/*函数功能：判断具体字符对应的优先级。
 *输入参数：c是要判断的字符。
 *返回值：字符对应的优先级。
 */
float Operate(float a,float b,char c);
/*函数功能：简单计算操作。
 *输入参数：a和b是操作数，c是操作符号，d存储计算结果。
 *返回值：无。
 */
void Clear_Array(char b[SIZE]);
/*函数功能：清空数组。
 *输入参数：b是要清空的数组。
 *返回值：无。
 */
float Calculating(char a[]);
/*函数功能：表达式计算。
 *输入参数：a是字符串数组。
 *返回值：计算结果。
 */

Status Stack1_Intit(Stack1* pStack){ //初始化栈
    pStack->pBase=(float*)malloc(SIZE*sizeof(float));
    if(pStack->pBase==NULL){
        return ERROR;
    }
    pStack->pTop=pStack->pBase;
    pStack->size=SIZE;
    return OK;    
}  
Status Stack2_Intit(Stack2* pStack){ //初始化栈
    pStack->pBase=(char*)malloc(SIZE*sizeof(char));
    if(pStack->pBase==NULL){
        return ERROR;
    }
    pStack->pTop=pStack->pBase;
    pStack->size=SIZE;
    return OK;    
}  
void Stack1_Free(Stack1* pStack){ //释放栈
    free(pStack->pBase);
    pStack->pBase=NULL;
    pStack->pTop=NULL;
    pStack->size=0;
    return;
}
void Stack2_Free(Stack2* pStack){ //释放栈
    free(pStack->pBase);
    pStack->pBase=NULL;
    pStack->pTop=NULL;
    pStack->size=0; 
    return;
}
void Stack1_Clear(Stack1* pStack){ //清空栈
    pStack->pTop=pStack->pBase;
}
void Stack2_Clear(Stack2* pStack){ //清空栈
    pStack->pTop=pStack->pBase;
}
int Stack1_Length(Stack1* pStack){ //求栈的长度
    return pStack->pTop-pStack->pBase;
}
int Stack2_Length(Stack2* pStack){ //求栈的长度
    return pStack->pTop-pStack->pBase;
}
Status Stack1_GetTop(Stack1* pStack,float* pElem){ //取栈顶指针
    if(pStack->pTop==pStack->pBase){
        return ERROR;
    }
    *pElem=*(pStack->pTop-1);
    return OK;
}
Status Stack2_GetTop(Stack2* pStack,char* pElem){ //取栈顶指针
    if(pStack->pTop==pStack->pBase){
        return ERROR;
    }
    *pElem=*(pStack->pTop-1);
    return OK;
}
Status Stack1_Push(Stack1* pStack,float* pElem){ //入栈
    
    int newSize=0;
    float* pTemp;
    if(Stack1_Length(pStack)>=pStack->size){
        newSize=pStack->size+INCREASEMENT;
        pTemp=realloc(pStack->pBase,newSize*pStack->size);
        if(pTemp==NULL){
            return ERROR;
        }
        else{
            pStack->pBase=pTemp;
            pStack->size==newSize;
            pStack->pTop=pStack->pBase+pStack->size;
        }
    }
    float a=0;
    a=*pElem;
    *(pStack->pTop)=a;
    pStack->pTop++;
    return OK;
}
Status Stack2_Push(Stack2* pStack,char* pElem){ //入栈
    
    int newSize=0;
    char* pTemp;
    if(Stack2_Length(pStack)>=pStack->size){
        newSize=pStack->size+INCREASEMENT;
        pTemp=(char*)realloc(pStack->pBase,newSize*sizeof(char));
        if(pTemp==NULL){
            return ERROR;
        }
        else{
            pStack->pBase=pTemp;
            pStack->pTop=pStack->pBase+pStack->size;
            pStack->size==newSize;
        }
    }
    char a;
    a=*pElem;
    *(pStack->pTop)=a;
    pStack->pTop++;
    return OK;
}
Status Stack1_Pop(Stack1* pStack,float* pElem){ //出栈
    if(pStack->pTop==pStack->pBase){
        return ERROR;
    }
    else{
        pStack->pTop--;
        *pElem=*(pStack->pTop);
        return OK;
    }
}
Status Stack2_Pop(Stack2* pStack,char* pElem){ //出栈
    if(pStack->pTop==pStack->pBase){
        return ERROR;
    }
    else{
        pStack->pTop--;
        *pElem=*(pStack->pTop);
        return OK;
    }
}
Bool Stack1_IsEmpty(Stack1* pStack){
    if(pStack->pTop==pStack->pBase){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
Bool Stack2_IsEmpty(Stack2* pStack){
    if(pStack->pTop==pStack->pBase){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
Status Stack1_Traverse(Stack1*pStack,Status(*visit)()){
    int i,n;
    n=Stack1_Length(pStack);
    for(i=0;i<n;i++){
        if(visit(&(pStack->pBase[i]))==ERROR){
            return ERROR;
        }
    }
    return OK;
}
Status Stack2_Traverse(Stack2*pStack,Status(*visit)()){
    int i,n;
    n=Stack2_Length(pStack);
    for(i=0;i<n;i++){
        if(visit(&(pStack->pBase[i]))==ERROR){
            return ERROR;
        }
    }
    return OK;
}
float power(float x,int a){ //计算乘方
    int i=0;
    int n=0;
    float d=0;
    n=x;
    for(i=0;i<a-1;i++){
    
        x=x*n;
    }
    d=x;
    return d;
}
float CharToFloat(char a[]){ //将字符转成数值
    int i=0;
    float value=0;
    while(a[i]!='\0'&&a[i]!='.'){
        value=value*10+(a[i]-'0');
        i=i+1;
    }
    if (a[i]=='\0'){
        return value;
    }
    i=i+1;
    float weight=0.1;
    while(a[i]!='\0'){
        value=value+(int)(a[i]-'0')*weight;
        weight=weight*0.1;
        i=i+1;
    }
    return value;
}
void Priority(Rank bt[]){ //定义符号的优先级
    Rank pound,bracket,plus,minus,multiply,divide,power;
    bt[0].a='#';
    bt[0].b=0;
    bt[1].a='(';
    bt[1].b=1;
    bt[2].a='+';
    bt[2].b=2;
    bt[3].a='-';
    bt[3].b=2;
    bt[4].a='*';
    bt[4].b=3;
    bt[5].a='/';
    bt[5].b=3;
    bt[6].a='^';
    bt[6].b=4;
}
int GetRank(char c){ //判断字符对应的优先级
    int k=0,rankC=0;
    Rank bt[7]; 
    Priority(bt);//定义优先级
    k=0;
    for(k=0;k<8;k++){
        while(c==bt[k].a){
            rankC=bt[k].b;
            break;
        }
    }
    return rankC;
}
float Operate(float a,float b,char c){
    float d;
    if(c=='+'){
        d=a+b;
    }
    if(c=='-'){
        d=a-b;
    }
    if(c=='*'){
        d=a*b;
    }
    if(c=='/'){
        d=a/b;
    }
    if(c=='^'){
        d=power(a,b);
    }
    return d;
}
void Clear_Array(char b[SIZE]){
    int i=0;
    for(i=0;i<SIZE;i++){
        b[i]=0;
    }
}
float Calculating(char a[]){ //计算
    Stack1 operandStack;
    Stack2 operatorStack;
    Stack1* pOperandStack;
    Stack2* pOperatorStack; 
    pOperandStack=&operandStack;
    pOperatorStack=&operatorStack;
    Stack2_Intit(pOperatorStack);
    Stack1_Intit(pOperandStack);
    if(Stack1_IsEmpty(pOperandStack)==FALSE){
        Stack1_Free(pOperandStack);
    }
    if(Stack2_IsEmpty(pOperatorStack)==FALSE){
        Stack2_Free(pOperatorStack);
    }
    
    Rank bt[7]; 
    Priority(bt);//定义优先级
 
    float i1=0,i2=0,d=0,num=0;
    int i,j,k,bTop=0,m=0;
    char top,c,bottom;
    bottom='#';
    float *pI1,*pI2,*pD,*pNum;
    pI1=&i1;
    pI2=&i2;
    pD=&d;
    pNum=&num;
    char *pTop,*pC,*pBottom;
    pBottom=&bottom;
    pTop=&top;
    pC=&c;
    Stack2_Push(pOperatorStack,pBottom);//将'#'作为最低位压入字符栈
    j=0;
    char b[SIZE]={0};
    for(i=0;i<SIZE;i++){
        if((int)a[i]>=48 && (int)a[i]<=57||a[i]=='.'){ //将单个数字字符组合转换成浮点数
            b[j]=a[i];
            j++;
        }
        else if(a[i]=='\0'){
            if((int)a[i-1]>=48 && (int)a[i-1]<=57||a[i-1]=='.'){
                num=CharToFloat(b);
                Stack1_Push(pOperandStack,pNum); 
            }
            
            Stack2_Pop(pOperatorStack,pC);   
            Stack1_Pop(pOperandStack,pI1);
            Stack1_Pop(pOperandStack,pI2);
            d=Operate(i2,i1,c);
            
            break;
        }
        else{
            m=0;
            bTop=0;
            if((int)a[i-1]>=48 && (int)a[i-1]<=57||a[i-1]=='.'){
                num=CharToFloat(b);
                Clear_Array(b);
                j=0;
                Stack1_Push(pOperandStack,pNum); 
            }
            
            if(a[i]!=')'){
                m=GetRank(a[i]); //判断优先级
                Stack2_GetTop(pOperatorStack,pTop);
                bTop=GetRank(top);
            }
            
            char n=a[i];
            char* pN;
            pN=&n;
            if(m>bTop||(n=='(')){
                Stack2_Push(pOperatorStack,pN);
                continue;
            }
            while(n==')'){
                Stack2_Pop(pOperatorStack,pC);   
                Stack1_Pop(pOperandStack,pI1);
                Stack1_Pop(pOperandStack,pI2);
                d=Operate(i2,i1,c);
                Stack1_Push(pOperandStack,pD);
                Stack2_GetTop(pOperatorStack,pTop);
                if(top!='('){
                    
                    continue;
                }
                else{
                    Stack2_Pop(pOperatorStack,pTop);
                    top=0;
                    break;
                }
            }
            while(m<=bTop&&m!=0){
                Stack2_Pop(pOperatorStack,pC);   
                Stack1_Pop(pOperandStack,pI1);
                Stack1_Pop(pOperandStack,pI2);
                d=Operate(i2,i1,c);
                Stack1_Push(pOperandStack,pD);
                Stack2_GetTop(pOperatorStack,pTop);
                bTop=GetRank(top);
                if(m>bTop){
                    Stack2_Push(pOperatorStack,pN);
                } 
            }         
            
        }
    }
    
    Stack1_Free(pOperandStack);
    Stack2_Free(pOperatorStack);
    return d;
}

int main(){
    float result=0;
    char a[SIZE]={0};
    scanf("%s",&a);
    result=Calculating(a);
    printf("%f",result);
    return 0;
}