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
    printf("Ҫ�޸ļ����Ű��");
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
    fprintf(pf, "�Ű��%d\n", k);
    printf("������������Ա����Ϣ��:\n");
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
    printf("�Ű��(��Ϣ��):\n");
    printf("��\tǮ\t��\t��\t��\t��\t��\t\n");
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
    FILE* file = fopen(TEMP_FILE, "a");  // ���ļ��Խ���д��
    if (file != NULL) {
        char arr[20];
        fprintf(file, "\n�Ű��%d\n", ++(*n));
        printf("������������Ա����Ϣ��(ÿ��һ�죬��ʽ������һ):\n");
        for (int i = 0; i < NUM_GUARDS; i++)
        {
            printf("%s:", name[i]);
            scanf("%s", arr);
            getchar();
            fprintf(file, "%s\t", arr);
        }
        fclose(file);
        file = NULL;
        printf("�Ű����ѱ��浽�ļ� %s �С�\n", TEMP_FILE);
    }
    else {
        printf("�޷����ļ� %s ����д�롣\n", TEMP_FILE);
    }
}

void loadSchedule(int (*guards)[NUM_DAYS], char **guard_names) {
    FILE *file;
    file = fopen("schedule.txt", "r"); // ���ļ�
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file); // �ر��ļ�
}

void schedule_control(char* username, int* n, char name[NUM_GUARDS][5])
{
    
    int choice;
again:
    printf("|| ==    �û��˵�     == ||\n");
    printf("|| == ����1�����Ű�� == ||\n");
    printf("|| == ����2��ѯ�Ű�� == ||\n");
    printf("|| == ����3�޸��Ű�� == ||\n");
    printf("|| == ����4ɾ���Ű�� == ||\n");
    printf("|| == ����5�����Ű�� == ||\n");
    printf("|| == ����6�˻���һ�� == ||\n");
    printf("��ѡ��:");
    scanf("%d", &choice); // ����ѡ��

    switch (choice) {
        case 1:fflush(stdin); system("cls");
            return;
        case 2:fflush(stdin); system("cls");
            printSchedule(n); // ���ز���ӡ�Ű��
            goto again;
        case 3:fflush(stdin); system("cls");
            changeSchedule(name, n); push(); printSchedule(n);
            goto again;
        case 4:fflush(stdin); system("cls");
            if (remove("temp.txt") == 0) { // ɾ���Ű���ļ�
                *n = 0;
                printf("�Ű��ɾ���ɹ�\n\n");
            } else {
                printf("�Ű��ɾ��ʧ��\n\n");
            }
            goto again;
        case 5:fflush(stdin); system("cls"); saveScheduleToFile(n, name);
            goto again;
        case 6:fflush(stdin); system("cls");
            break;
        default:
            printf("��Чѡ��\n"); system("pause"); fflush(stdin); system("cls");
            goto again;
    }
    main();
}