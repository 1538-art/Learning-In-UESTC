#include "Calculate.h"
#include <stdio.h>
#if DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x) do {} while (0)
#endif


int main() {
    DEBUG_PRINT(("Variable x: %d\n", x));
    // 文件指针
    FILE *file;

    // 打开文件，以写入方式创建或覆盖已有文件
    file = fopen("example.txt", "w");

    // 检查文件是否成功打开
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 提示用户输入表达式，直到用户输入空行
    printf("Enter expressions (press Enter to finish):\n");
    char expression[ARRAY_SIZE];  // 适当选择一个足够大的缓冲区

    while (fgets(expression, sizeof(expression), stdin) != NULL && expression[0] != '\n') {
        // 将用户输入的表达式写入文件
        fputs(expression, file);
    }

    // 关闭文件
    fclose(file);

    // 重新打开文件，以只读方式打开
    file = fopen("example.txt", "r");

    // 检查文件是否成功打开
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 读取文件中的每一行
    printf("The result of each expression:\n");
    int i=0;
    while (fgets(expression, sizeof(expression), file) != NULL) {
        // 处理每一行
        float result=Calculates(expression);
        printf("%s",expression);
        printf("result=%f\n", result);
        printf("\n");
        i++;
    }

    // 关闭文件
    fclose(file);

    return 0;
}



