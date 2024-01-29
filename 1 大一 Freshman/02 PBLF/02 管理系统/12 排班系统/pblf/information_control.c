#define _CRT_SECURE_NO_WARNINGS
#include "all.h"
#include "information_control.h"
#include "mainstream.h"
#include "user_control.h"

void push()
{
    char arr[50];
    FILE* pf = fopen("tempx.txt", "r");
    if (pf == NULL)
    {
        printf("%s\n", strerror(errno));
        return;
    }
    FILE* pe = fopen("temp.txt", "w");
    if (pe == NULL)
    {
        printf("%s\n", strerror(errno));
        return;
    }
    while (fgets(arr, 50, pf) != NULL)
    {
        fputs(arr, pe);
    }
    fclose(pf);
    fclose(pe);
}

void changeSchedule(char name[NUM_GUARDS][5], int* n)
{
    printSchedule(n);
    printf("要修改几号排班表：");
    int k = 0, i = 0, j = 0;
    char arr[50];
    scanf("%d", &k);
    FILE* pf = fopen("tempx.txt", "w");
    if (pf == NULL)
    {
        printf("%s\n", strerror(errno));
        return;
    }
    FILE* pe = fopen("temp.txt", "r");
    if (pe == NULL)
    {
        printf("%s\n", strerror(errno));
        return;
    }
    fgets(arr, 50, pe);
    fputs(arr, pf);
    for (i = 1; i < k; i++)
    {
        fgets(arr, 50, pe);
        if (arr[0] == '\n')
            fgets(arr, 50, pe);
        fputs(arr, pf);
        fgets(arr, 50, pe);
        fputs(arr, pf);
    }
    fprintf(pf, "\n");
    fprintf(pf, "排班表%d\n", k);
    printf("请输入下列人员的休息日:\n");
    for (j = 0; j < NUM_GUARDS; j++)
    {
        printf("%s:", name[j]);
        scanf("%s", arr);
        fprintf(pf, "%s\t", arr);
    }
    fprintf(pf, "\n");
    for (j = 0; j <= k; j++)
    {
        fgets(arr, 50, pe);
    }
    while (fgets(arr, 50, pe) != NULL)
    {
        fputs(arr, pf);
    }
    fclose(pf); pf = NULL;
    fclose(pe); pe = NULL;
    return;
}

void printSchedule(int* n) {
    printf("排班表(休息日):\n");
    printf("赵\t钱\t孙\t李\t周\t吴\t陈\t\n");
    char tmp[NUM_DAYS][10];
    FILE* pf = fopen("temp.txt", "r");
    if (pf == NULL)
    {
        perror("fopen");
        return;
    }
    else
    {
        char arr[10];
        while (fscanf(pf, "%s", arr) != EOF)
        {
            (*n)++;
            printf("%s\n", arr);
            for (int i = 0; i < NUM_DAYS; i++)
            {
                fscanf(pf, "%s", tmp[i]);
                printf("%s\t", tmp[i]);
            }
            printf("\n");
        }
    }
    fclose(pf);
    printf("\n");
    return;
}


void saveScheduleToFile(int* n, char name[7][5]) {
    FILE* file = fopen(TEMP_FILE, "a");  // 打开文件以进行写入
    if (file != NULL) {
        char arr[20];
        fprintf(file, "\n排班表%d\n", ++(*n));
        printf("请输入下列人员的休息日(每人一天，格式：星期一):\n");
        for (int i = 0; i < NUM_GUARDS; i++)
        {
            printf("%s:", name[i]);
            scanf("%s", arr);
            getchar();
            fprintf(file, "%s\t", arr);
        }
        fclose(file);
        file = NULL;
        printf("排班表格已保存到文件 %s 中。\n", TEMP_FILE);
    }
    else {
        printf("无法打开文件 %s 进行写入。\n", TEMP_FILE);
    }
}

void loadSchedule(int (*guards)[NUM_DAYS], char **guard_names) {
    FILE *file;
    file = fopen("schedule.txt", "r"); // 打开文件
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file); // 关闭文件
}

void schedule_control(char* username, int* n, char name[NUM_GUARDS][5])
{
    
    int choice;
again:
    printf("|| ==    用户菜单     == ||\n");
    printf("|| == 输入1创建排班表 == ||\n");
    printf("|| == 输入2查询排班表 == ||\n");
    printf("|| == 输入3修改排班表 == ||\n");
    printf("|| == 输入4删除排班表 == ||\n");
    printf("|| == 输入5增加排班表 == ||\n");
    printf("|| == 输入6退回上一级 == ||\n");
    printf("请选择:");
    scanf("%d", &choice); // 输入选项

    switch (choice) {
        case 1:fflush(stdin); system("cls");
            return;
        case 2:fflush(stdin); system("cls");
            printSchedule(n); // 加载并打印排班表
            goto again;
        case 3:fflush(stdin); system("cls");
            changeSchedule(name, n); push(); printSchedule(n);
            goto again;
        case 4:fflush(stdin); system("cls");
            if (remove("temp.txt") == 0) { // 删除排班表文件
                *n = 0;
                printf("排班表删除成功\n\n");
            } else {
                printf("排班表删除失败\n\n");
            }
            goto again;
        case 5:fflush(stdin); system("cls"); saveScheduleToFile(n, name);
            goto again;
        case 6:fflush(stdin); system("cls");
            break;
        default:
            printf("无效选择\n"); system("pause"); fflush(stdin); system("cls");
            goto again;
    }
    main();
}