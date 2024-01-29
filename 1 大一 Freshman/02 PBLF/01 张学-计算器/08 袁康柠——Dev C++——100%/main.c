#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Calculator.h"

#define EXPRESSION_SIZE 100

int main(){
    // ��������������
    Calculator* pCalculator = Calculator_Construct();
    
    // ����ģʽѡ��
    int mode;
    printf("��ѡ�����ģʽ��\n");
    printf("1. ��������ģʽ\n");
    printf("2. ��ͨ����ģʽ\n");
    scanf("%d", &mode);

    if (mode == 1) {
        // ����������ʽ
        char sFilename[EXPRESSION_SIZE];
        printf("������Ҫ����������ļ���:\n");
        scanf("%s", sFilename);
        FILE* file = fopen(sFilename, "r");
        if (file == NULL) {
            printf("�޷����ļ� %s\n", sFilename);
            return 1;
        }
        Calculator_BatchCalculate(sFilename,"output.txt");
    } else if (mode == 2) {
        // ��ȡ�û�����ı��ʽ
        getchar(); // ��ȡ��һ������������µĻ��з�
        Calculator_InputExpression(pCalculator);
        
        // �ж��û�����ı��ʽ�Ƿ�Ϸ�	
        if (!Calculator_IsValidExpression(pCalculator->pExp)) {
            printf("����ı��ʽ���Ϸ���\n");
        } else {
            // ������ʽ���
            double result = Calculator_OutputResult(pCalculator);
            printf("Result: %lf\n", result);
        
        }
    } else {
        printf("��Ч�ļ���ģʽ��\n");
    }
	Calculator_Destruct(pCalculator);//�ͷż����������ڴ� 
    return 0;
}
