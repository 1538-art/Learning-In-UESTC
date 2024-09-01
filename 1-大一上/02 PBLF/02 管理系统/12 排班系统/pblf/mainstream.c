#define _CRT_SECURE_NO_WARNINGS
#include "all.h"//已包含各种头文件
#include "information_control.h"
#include "mainstream.h"
#include "user_control.h"


void ask_desire(char name[7][5], int desire[7][7]);                                                          //询问意愿
void sort(int day[7], int tmp[7], int* n, int desire[7][7], int order);                                   //实现排班
void fail(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                           //检测排班是否失败
void add_arrage(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                     //增加排班
void user_menu(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);             //用户功能菜单
void esc(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                   //返回


void arranging(char* username, char* use)
{
    int n = 0;
    char name[NUM_GUARDS][5] = { "赵","钱","孙","李","周","吴","陈" };
    int desire[7][7] = { 0 };
    int tmp[7] = { 0 };  //用来记录每个人安排的结果
    int day[7] = { 0 };  //用来记录每个人哪一天被选走
    printSchedule(&n);
    fflush(stdin); system("cls");
    schedule_control(username, &n, name);
    fflush(stdin);  //清空缓存区
    user_menu(&n, name, desire, tmp, day, use);  //调用函数主菜单
    system("pause");//防止主程序闪退

    return;
}

//询问保安的意愿
void ask_desire(char name[7][5], int desire[7][7])
{
    int i, j, k;
    char week[7][10] = { "一","二","三","四","五","六","日" };
    char ch[30];
    printf("请输入下列人员的休息日：\n");
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
                desire[i][k] = j + 1; //存储意愿  人物/日期
                k++;
            }
        }

    }

}

//实现排班
void sort(int day[7], int tmp[7], int* n, int desire[7][7], int order)
{
    int i, j;
    if (order == 7)
    {
        (*n)++;
        FILE* fp = fopen(TEMP_FILE, "a+");
        printf("\n排班表%d\n", *n);
        fprintf(fp, "排班表%d\n", *n);
        printf("赵\t钱\t孙\t李\t周\t吴\t陈\t\n");


        for (i = 0; i < 7; i++)
        {
            switch (tmp[i]) {
            case 1:printf("星期一\t"); fputs("星期一\t", fp); break;
            case 2:printf("星期二\t"); fputs("星期二\t", fp); break;
            case 3:printf("星期三\t"); fputs("星期三\t", fp); break;
            case 4:printf("星期四\t"); fputs("星期四\t", fp); break;
            case 5:printf("星期五\t"); fputs("星期五\t", fp); break;
            case 6:printf("星期六\t"); fputs("星期六\t", fp); break;
            case 7:printf("星期日\t"); fputs("星期日\t", fp); break;
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
        if (day[desire[order][j] - 1] != 0)  //该时间被占有
        {
            continue;
        }
        day[desire[order][j] - 1] = 1;
        tmp[order] = desire[order][j];

        sort(day, tmp, n, desire, order + 1);  //递归

        day[desire[order][j] - 1] = 0;
        //递归后将这一天置0去遍历这一天不选的情况
    }
}

//检测排班是否失败
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

        if (xq[0] == 0)  printf("星期日");
        if (xq[1] == 0)  printf("星期一");
        if (xq[2] == 0)  printf("星期二");
        if (xq[3] == 0)  printf("星期三");
        if (xq[4] == 0)  printf("星期四");
        if (xq[5] == 0)  printf("星期五");
        if (xq[6] == 0)  printf("星期六");
        printf("无法排班\n");
        esc(n, name, desire, tmp, day, use);

    }
}

void add_arrage(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use)
{
    int t;
    int r;
    char ch[100];
    printf("\n请输入你需要增加的排班序号:");
    scanf("%d", &t);
    if (t > *n || t < 0)
    {
        printf("无效输入\n");
        add_arrage(n, name, desire, tmp, day, use);
    }
    FILE* fp = fopen(TIME_FILE, "r");
    while (1)
    {
        fscanf(fp, "%d", &r);
        if (r == t)
        {
            fgets(ch, 100, fp);
            printf("赵\t钱\t孙\t李\t周\t吴\t陈\n");
            puts(ch);
            fclose(fp);
            fp = fopen(TIME_FILE, "w");  //清除缓存为下一次排班做准备
            fclose(fp);
            fp = fopen(TIME_FILE, "w");  //保存数据
            fputs(ch, fp);
            fclose(fp);
            printf("排班成功:\n");
            time_t t;  //将t声明为时间变量
            struct tm* p;
            time(&t);
            p = localtime(&t);//获得当地的时间
            printf("用户%s于%d-%d-%d %d:%d:%d进行增加排班操作\n", use, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
            fp = fopen(TIME_FILE, "a+");
            fprintf(fp, "用户%s于%d-%d-%d %d:%d:%d进行增加排班操作\n", use, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
            fclose(fp);
            break;
        }
        else
        {
            fgets(ch, 100, fp); //换行
        }
    }
    esc(n, name, desire, tmp, day, use);
}


//用户功能菜单
void user_menu(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use)
{
    int ret = 0;

    printf("=======欢迎来到排班模块=======\n");
    printf("[-----Press 1 : 进行排班-----]\n");
    printf("[-----Press 2 : 主菜单-------]\n");
    printf("[-----Press 0 : 退出系统-----]\n");

    printf("请输入您的选择：");
    scanf("%d", &ret);
    switch (ret)
    {
    case 1:fflush(stdin); ask_desire(name, desire); sort(day, tmp, n, desire, 0); fail(n, name, desire, tmp, day, use); break;
    case 2:fflush(stdin); system("cls"); main(); break;
    case 0:printf("您已退出系统！\n"); exit(0); break;
    default:printf("输入有误！！\n\n"); fflush(stdin); system("cls"); system("pause"); user_menu(n, name, desire, tmp, day, use); break;
    }
}

void esc(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use)
{
    int t;
    printf("按0退出,按1返回上一级,按2返回主菜单\n");
    scanf("%d", &t);
    switch (t)
    {
    case 0:fflush(stdin); system("cls"); exit(0); break;
    case 1:fflush(stdin); system("cls"); user_menu(n, name, desire, tmp, day, use); break;
    case 2:fflush(stdin); system("cls"); main(); break;
    default:fflush(stdin); esc(n, name, desire, tmp, day, use); break;
    }
}