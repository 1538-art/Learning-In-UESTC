#define _CRT_SECURE_NO_WARNINGS
#include "all.h"
#include "information_control.h"
#include "mainstream.h"
#include "user_control.h"

/*注册函数*/
void registerUser(User users[MAX_USERS]) 
{
    if (MAX_USERS <= 0) {
        printf("注册失败：用户数量已达上限\n");
        return;
    }
    int i = 0;

    printf("请输入用户名：");
    char newUsername[20];
    scanf("%s", newUsername);

    /*检查用户名是否已存在*/
    for (i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, newUsername) == 0) {
            printf("注册失败：用户名已存在\n");
            return;
        }
    }

    printf("输入密码:");
    char newPassword[20];
    scanf("%s", newPassword);
    
    printf("输入实名:");
    char newRealname[20];
    scanf("%s", newRealname);

    /*将新用户添加到数组*/
    for (i = 0; i < MAX_USERS; ++i) {
        if (users[i].username) {
            strcpy(users[i].username, newUsername);
            strcpy(users[i].password, newPassword);
            strcpy(users[i].realname, newRealname);
            break;
        }
    }
    FILE* file = fopen("user.txt", "a");
    fprintf(file, "%s %s %s\n", users[i].username, users[i].password, users[i].realname);
    if (file == NULL) 
    {
        printf("Error opening file\n");
        return;
    }
    fclose(file);
    file = NULL;
    printf("注册成功！\n");
    int t;
    printf("按0退出,按1返回主菜单\n");
    scanf("%d", &t);
    switch (t)
    {
    case 0:fflush(stdin); system("cls"); exit(0); break;
    case 1:fflush(stdin); system("cls"); main(); break;
    default:fflush(stdin); exit(0); break;
    }
}
/*登录系统*/
void loginUser(User users[MAX_USERS]) {
    printf("请输入用户名:");
    char inputUsername[20];
    scanf("%s", inputUsername);

    printf("请输入密码:");
    char inputPassword[20];
    scanf("%s", inputPassword);
    /*验证用户身份*/
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, inputUsername) == 0 && strcmp(users[i].password, inputPassword) == 0) {
            printf("登录成功，按1进行打卡，按2跳转到用户菜单,按0返回上一级\n");
            int choice = 0;
            again:
            printf("请选择：");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:clock_in(&users[i]); break;
            case 2:arranging(users[i].realname, users[i].username); break;
            case 0:break;
            default:printf("输入错误！"); goto again;
            }
            return;
        }
    }
    printf("登录失败：用户名或密码错误\n");
    system("pause");
}

//打卡考勤
void clock_in(User* use)
{
    time_t t;
    struct tm* p;
    time(&t);
    p = localtime(&t);
    printf("\n\n%s于%d-%d-%d %d:%d:%d进行打卡考勤\n\n\n", use->realname, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    FILE* fp = fopen(CLOCK_FILE, "a+");
    fprintf(fp, "%s于%d-%d-%d %d:%d:%d进行打卡考勤\n", use->realname, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    fclose(fp);
    system("pause");
    return;
}
//查询打卡记录
void clock_record()
{
    char ch[100] = { 0 };
    FILE* fp = fopen(CLOCK_FILE, "r");
    fgets(ch, 100, fp);
    if (strlen(ch) == 0)
    {
        printf("还没有考勤信息！\n");
        fclose(fp);
        return;
    }
    while (1)
    {
        if (feof(fp))
            break;
        else
        {
            puts(ch);
                fgets(ch, 100, fp);
        }
    }
    fclose(fp);
    int t;
    printf("按0退出，按1返回上一级，按2清空记录\n");
    scanf("%d", &t);
    switch (t)
    {
    case 0:fflush(stdin); system("cls"); exit(0); break;
    case 1:fflush(stdin); system("cla"); return;
    case 2:fflush(stdin);
        fp = fopen(CLOCK_FILE, "w");
        fclose(fp);
        printf("清除成功\n");
        return;
    default:fflush(stdin); return;
    }
}