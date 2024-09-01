#define _CRT_SECURE_NO_WARNINGS
#include "all.h"//�Ѱ�������ͷ�ļ�
#include "information_control.h"
#include "mainstream.h"
#include "user_control.h"


void ask_desire(char name[7][5], int desire[7][7]);                                                          //ѯ����Ը
void sort(int day[7], int tmp[7], int* n, int desire[7][7], int order);                                   //ʵ���Ű�
void fail(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                           //����Ű��Ƿ�ʧ��
void add_arrage(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                     //�����Ű�
void user_menu(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);             //�û����ܲ˵�
void esc(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                   //����


void arranging(char* username, char* use)
{
    int n = 0;
    char name[NUM_GUARDS][5] = { "��","Ǯ","��","��","��","��","��" };
    int desire[7][7] = { 0 };
    int tmp[7] = { 0 };  //������¼ÿ���˰��ŵĽ��
    int day[7] = { 0 };  //������¼ÿ������һ�챻ѡ��
    printSchedule(&n);
    fflush(stdin); system("cls");
    schedule_control(username, &n, name);
    fflush(stdin);  //��ջ�����
    user_menu(&n, name, desire, tmp, day, use);  //���ú������˵�
    system("pause");//��ֹ����������

    return;
}

//ѯ�ʱ�������Ը
void ask_desire(char name[7][5], int desire[7][7])
{
    int i, j, k;
    char week[7][10] = { "һ","��","��","��","��","��","��" };
    char ch[30];
    printf("������������Ա����Ϣ�գ�\n");
    for (i = 0; i < 7; i++)
    {
        k = 0;
        printf("%s:", name[i]);
        fflush(stdin);
        scanf("%s", ch);
        for (j = 0; j < 7; j++)
        {
            if (strstr(ch, week[j]) != NULL)
            {
                desire[i][k] = j + 1; //�洢��Ը  ����/����
                k++;
            }
        }

    }

}

//ʵ���Ű�
void sort(int day[7], int tmp[7], int* n, int desire[7][7], int order)
{
    int i, j;
    if (order == 7)
    {
        (*n)++;
        FILE* fp = fopen(TEMP_FILE, "a+");
        printf("\n�Ű��%d\n", *n);
        fprintf(fp, "�Ű��%d\n", *n);
        printf("��\tǮ\t��\t��\t��\t��\t��\t\n");


        for (i = 0; i < 7; i++)
        {
            switch (tmp[i]) {
            case 1:printf("����һ\t"); fputs("����һ\t", fp); break;
            case 2:printf("���ڶ�\t"); fputs("���ڶ�\t", fp); break;
            case 3:printf("������\t"); fputs("������\t", fp); break;
            case 4:printf("������\t"); fputs("������\t", fp); break;
            case 5:printf("������\t"); fputs("������\t", fp); break;
            case 6:printf("������\t"); fputs("������\t", fp); break;
            case 7:printf("������\t"); fputs("������\t", fp); break;
            default:break;
            }
        }
        printf("\n");
        fputs("\n", fp);
        fclose(fp);
        return;
    }

    for (j = 0; j < 7 && desire[order][j]; j++)
    {
        if (day[desire[order][j] - 1] != 0)  //��ʱ�䱻ռ��
        {
            continue;
        }
        day[desire[order][j] - 1] = 1;
        tmp[order] = desire[order][j];

        sort(day, tmp, n, desire, order + 1);  //�ݹ�

        day[desire[order][j] - 1] = 0;
        //�ݹ����һ����0ȥ������һ�첻ѡ�����
    }
}

//����Ű��Ƿ�ʧ��
void fail(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use)
{
    int i, j;
    if (*n == 0)
    {
        int xq[7] = { 0,0,0,0,0,0,0 };
        for (i = 0; i < 7; i++)
        {
            for (j = 0; j < 7; j++)
            {
                if (desire[i][j] == 0) continue;
                if (desire[i][j] == 1) xq[1] = 1;
                if (desire[i][j] == 2) xq[2] = 1;
                if (desire[i][j] == 3) xq[3] = 1;
                if (desire[i][j] == 4) xq[4] = 1;
                if (desire[i][j] == 5) xq[5] = 1;
                if (desire[i][j] == 6) xq[6] = 1;
                if (desire[i][j] == 7) xq[0] = 1;
            }
        }

        if (xq[0] == 0)  printf("������");
        if (xq[1] == 0)  printf("����һ");
        if (xq[2] == 0)  printf("���ڶ�");
        if (xq[3] == 0)  printf("������");
        if (xq[4] == 0)  printf("������");
        if (xq[5] == 0)  printf("������");
        if (xq[6] == 0)  printf("������");
        printf("�޷��Ű�\n");
        esc(n, name, desire, tmp, day, use);

    }
}

void add_arrage(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use)
{
    int t;
    int r;
    char ch[100];
    printf("\n����������Ҫ���ӵ��Ű����:");
    scanf("%d", &t);
    if (t > *n || t < 0)
    {
        printf("��Ч����\n");
        add_arrage(n, name, desire, tmp, day, use);
    }
    FILE* fp = fopen(TIME_FILE, "r");
    while (1)
    {
        fscanf(fp, "%d", &r);
        if (r == t)
        {
            fgets(ch, 100, fp);
            printf("��\tǮ\t��\t��\t��\t��\t��\n");
            puts(ch);
            fclose(fp);
            fp = fopen(TIME_FILE, "w");  //�������Ϊ��һ���Ű���׼��
            fclose(fp);
            fp = fopen(TIME_FILE, "w");  //��������
            fputs(ch, fp);
            fclose(fp);
            printf("�Ű�ɹ�:\n");
            time_t t;  //��t����Ϊʱ�����
            struct tm* p;
            time(&t);
            p = localtime(&t);//��õ��ص�ʱ��
            printf("�û�%s��%d-%d-%d %d:%d:%d���������Ű����\n", use, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
            fp = fopen(TIME_FILE, "a+");
            fprintf(fp, "�û�%s��%d-%d-%d %d:%d:%d���������Ű����\n", use, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
            fclose(fp);
            break;
        }
        else
        {
            fgets(ch, 100, fp); //����
        }
    }
    esc(n, name, desire, tmp, day, use);
}


//�û����ܲ˵�
void user_menu(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use)
{
    int ret = 0;

    printf("=======��ӭ�����Ű�ģ��=======\n");
    printf("[-----Press 1 : �����Ű�-----]\n");
    printf("[-----Press 2 : ���˵�-------]\n");
    printf("[-----Press 0 : �˳�ϵͳ-----]\n");

    printf("����������ѡ��");
    scanf("%d", &ret);
    switch (ret)
    {
    case 1:fflush(stdin); ask_desire(name, desire); sort(day, tmp, n, desire, 0); fail(n, name, desire, tmp, day, use); break;
    case 2:fflush(stdin); system("cls"); main(); break;
    case 0:printf("�����˳�ϵͳ��\n"); exit(0); break;
    default:printf("�������󣡣�\n\n"); fflush(stdin); system("cls"); system("pause"); user_menu(n, name, desire, tmp, day, use); break;
    }
}

void esc(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use)
{
    int t;
    printf("��0�˳�,��1������һ��,��2�������˵�\n");
    scanf("%d", &t);
    switch (t)
    {
    case 0:fflush(stdin); system("cls"); exit(0); break;
    case 1:fflush(stdin); system("cls"); user_menu(n, name, desire, tmp, day, use); break;
    case 2:fflush(stdin); system("cls"); main(); break;
    default:fflush(stdin); esc(n, name, desire, tmp, day, use); break;
    }
}