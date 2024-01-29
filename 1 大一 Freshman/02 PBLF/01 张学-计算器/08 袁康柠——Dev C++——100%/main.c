#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Calculator.h"

#define EXPRESSION_SIZE 100

int main(){
    // 创建计算器对象
    Calculator* pCalculator = Calculator_Construct();
    
    // 计算模式选择
    int mode;
    printf("请选择计算模式：\n");
    printf("1. 批量计算模式\n");
    printf("2. 普通计算模式\n");
    scanf("%d", &mode);

    if (mode == 1) {
        // 批量计算表达式
        char sFilename[EXPRESSION_SIZE];
        printf("请输入要批量计算的文件名:\n");
        scanf("%s", sFilename);
        FILE* file = fopen(sFilename, "r");
        if (file == NULL) {
            printf("无法打开文件 %s\n", sFilename);
            return 1;
        }
        Calculator_BatchCalculate(sFilename,"output.txt");
    } else if (mode == 2) {
        // 获取用户输入的表达式
        getchar(); // 读取上一个输入操作留下的换行符
        Calculator_InputExpression(pCalculator);
        
        // 判断用户输入的表达式是否合法	
        if (!Calculator_IsValidExpression(pCalculator->pExp)) {
            printf("输入的表达式不合法。\n");
        } else {
            // 计算表达式结果
            double result = Calculator_OutputResult(pCalculator);
            printf("Result: %lf\n", result);
        
        }
    } else {
        printf("无效的计算模式。\n");
    }
	Calculator_Destruct(pCalculator);//释放计算器对象内存 
    return 0;
}
