#include <stdio.h>
#include "Calculate.h"
#include "Stack.h"
//判断优先级
int GetPriority(void* operator) {
    switch (*(char*)operator) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case '^':
                return 3;
            default:
                return 0;
    }
}//返回operator所指向的值的优先级大小

//执行法则并返回运算后的值(后缀表达式计算时用)
float Perform(float operand1, float operand2, char operator) {
    switch (operator) {
            case '+':
                return operand1 + operand2;
            case '-':
                return operand1 - operand2;
            case '*':
                return operand1 * operand2;
            case '/':
                return operand1 / operand2;
            case '^':
                return pow(operand1,operand2);
            default:
                return 0;
    }
}//返回计算结果

//计算三角函数
float sanjiao(char *expression,float a){
    char sin[]="sin",cos[]="cos",tan[]="tan";
    char arcsin[]="arcsin",arccos[]="arccos",arctan[]="arctan";//用字符数组存储三角函数前缀，之后用来比较判断
    if(strcmp(expression,sin)==0){
        return sinf(a);
    }
    if(strcmp(expression,cos)==0){
        return cosf(a);
    }
    if(strcmp(expression,tan)==0){
        return tanf(a);
    }
    if(strcmp(expression,arcsin)==0){
        return asinf(a);
    }
    if(strcmp(expression,arccos)==0){
        return acosf(a);
    }
    if(strcmp(expression,arctan)==0){
        return atanf(a);
    }else{
        printf("wrong input");//处理异常输入
    }

}
//计算表达式的值，传入参数（表达式）
float Calculates(const char* expression) {
    //构造局部数字栈
    Stack *operandStack = Stack_Construct(sizeof(float));
    //构造局部运算符栈
    Stack *operatorStack = Stack_Construct(sizeof(char));
    int i=0;
    //遍历表达式
    while (expression[i] != '\n') {
        //处理数字
        if (expression[i] <= '9' && expression[i] >= '0') {
            float operand1 = 0, operand2 = 0, operand = 0;
            //整数部分，遍历捕获多位数
            while (expression[i] <= '9' && expression[i] >= '0') {
                operand1 = 10 * operand1 + (expression[i] - '0');
                i++;
            }
            //小数部分
            if (expression[i] == '.') {
                i++;
                int z=1;
                //遍历捕获多位小数
                while (expression[i] <= '9' && expression[i] >= '0') {
                    operand2 = operand2 + (expression[i] - '0') / pow(10.0,z);
                    i++;
                    z++;
                }
            }
            operand = operand1 + operand2;
            //将计算结果入栈
            Stack_Push(operandStack, &operand);
        }
            //处理左括号
        else if (expression[i] == '(') {
            //左括号直接入栈
            Stack_Push(operatorStack, &expression[i]);
            i++;
        }
            //处理右括号
        else if (expression[i] == ')') {
            while (Stack_IsEmpty(operatorStack) != true && *(char *) Stack_GetTop(operatorStack) != '(') {
                float operand2 = *(float *) Stack_Pop(operandStack);
                float operand1 = *(float *) Stack_Pop(operandStack);
                char operator = *(char *) Stack_Pop(operatorStack);
                float result = Perform(operand1, operand2, operator);
                //括号内计算
                Stack_Push(operandStack, &result);//结果入栈
            }
            //当遇到左括号时弹出左括号
            if (Stack_IsEmpty(operatorStack) != true && *(char *) Stack_GetTop(operatorStack) == '(') {
                Stack_Pop(operatorStack);  //弹出左括号
            }
            i++;
        }
            //处理运算符
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*'
                 || expression[i] == '/' || expression[i] == '^') {
            //当栈顶运算符优先级较高时，先取出栈顶运算符进行计算，再将结果压入栈
            while (Stack_IsEmpty(operatorStack) != true
                   && GetPriority(Stack_GetTop(operatorStack)) >= GetPriority(&expression[i])) {
                float operand2 = *(float *) Stack_Pop(operandStack);
                float operand1 = *(float *) Stack_Pop(operandStack);
                char operator = *(char *) Stack_Pop(operatorStack);
                float result = Perform(operand1, operand2, operator);
                Stack_Push(operandStack, &result);
            }
            //若栈顶运算符较低，将表达式中运算符直接入栈
            Stack_Push(operatorStack, &expression[i]);
            i++;
        }
            //处理三角函数
        else if (expression[i] >= 'a' && expression[i] <= 'z') {
            char P[ARRAY_SIZE] = {0};//存放字母的数组，初始化为0
            int j = 0;//数组的索引
            //收集三角函数前缀，存入P数组中
            while (expression[i] != '(') {
                P[j] = expression[i];//将表达式中字母存进去
                i++;
                j++;
            }       //此时expression[i]=='('
            char* pos= strchr(expression+i,'(');   //从索引位置 i 开始查找‘（’
            char newexpresion[ARRAY_SIZE];//定义数组表示“（”之后的所有字符
            char subnewexpression[ARRAY_SIZE];//定义数组表示“（”与“）”之间的表达式，即子表达式
            int count=0,s=0;//count是左括号的个数。
            strcpy(newexpresion,pos);
            for(int m=0;m< strlen(newexpresion);m++){
                if(newexpresion[m]=='('){
                    count++;//左括号个数加一
                }if(newexpresion[m]==')'){
                    count--;//左括号个数减一
                    if(count==0){
                        subnewexpression[s]=')';//子表达式成型
                        subnewexpression[s+1]='\n';//将子表达式“)"之后的一位传入'\n'以满足Calculates函数遍历条件
                        break;//结束循环，不在进行之后步骤
                    }
                }
                subnewexpression[s]=newexpresion[m];//将值传入子表达式
                s++;
            }
            if(P=="sin"||P=="cos"||P=="tan"||P=="arctan"||P=="arcsin"||P=="arccos"){
                float results=sanjiao(P, Calculates(subnewexpression));//递归计算三角函数值
                Stack_Push(operandStack,&results);//将值压入栈
                subnewexpression[s+2]='\0';
                i += strlen(subnewexpression)-1;//索引移动到除去
            }else{
                printf("wrong input");
            }
        } else {
            printf("Please enter the proper form");//处理异常
            break;
        }
    }
    //遍历操作符栈，进行后缀表达式求值
    while (Stack_IsEmpty(operatorStack) != true) {
        float operand2 = *(float *) Stack_Pop(operandStack);
        float operand1 = *(float *) Stack_Pop(operandStack);//每次弹出两个数字栈值
        char operator = *(char *) Stack_Pop(operatorStack);
        float result = Perform(operand1, operand2, operator);
        Stack_Push(operandStack, &result);//每计算一次将新的值压入数字栈
    }
    float FinalResult = *(float *) Stack_Pop(operandStack);//遍历结束后数字栈中只剩最终结果，弹出即可
    Stack_Destruct(operatorStack);//析构局部操作符栈
    Stack_Destruct(operandStack);//析构局部数字栈
    return FinalResult;//返回结果
}