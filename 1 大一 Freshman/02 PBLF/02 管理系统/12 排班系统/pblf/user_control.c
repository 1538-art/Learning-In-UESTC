#define _CRT_SECURE_NO_WARNINGS
#include "all.h"
#include "information_control.h"
#include "mainstream.h"
#include "user_control.h"

/*ע�ắ��*/
void registerUser(User users[MAX_USERS]) 
{
    if (MAX_USERS <= 0) {
        printf("ע��ʧ�ܣ��û������Ѵ�����\n");
        return;
    }
    int i = 0;

    printf("�������û�����");
    char newUsername[20];
    scanf("%s", newUsername);

    /*����û����Ƿ��Ѵ���*/
    for (i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, newUsername) == 0) {
            printf("ע��ʧ�ܣ��û����Ѵ���\n");
            return;
        }
    }

    printf("��������:");
    char newPassword[20];
    scanf("%s", newPassword);
    
    printf("����ʵ��:");
    char newRealname[20];
    scanf("%s", newRealname);

    /*�����û���ӵ�����*/
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
    printf("ע��ɹ���\n");
    int t;
    printf("��0�˳�,��1�������˵�\n");
    scanf("%d", &t);
    switch (t)
    {
    case 0:fflush(stdin); system("cls"); exit(0); break;
    case 1:fflush(stdin); system("cls"); main(); break;
    default:fflush(stdin); exit(0); break;
    }
}
/*��¼ϵͳ*/
void loginUser(User users[MAX_USERS]) {
    printf("�������û���:");
    char inputUsername[20];
    scanf("%s", inputUsername);

    printf("����������:");
    char inputPassword[20];
    scanf("%s", inputPassword);
    /*��֤�û����*/
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, inputUsername) == 0 && strcmp(users[i].password, inputPassword) == 0) {
            printf("��¼�ɹ�����1���д򿨣���2��ת���û��˵�,��0������һ��\n");
            int choice = 0;
            again:
            printf("��ѡ��");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:clock_in(&users[i]); break;
            case 2:arranging(users[i].realname, users[i].username); break;
            case 0:break;
            default:printf("�������"); goto again;
            }
            return;
        }
    }
    printf("��¼ʧ�ܣ��û������������\n");
    system("pause");
}

//�򿨿���
void clock_in(User* use)
{
    time_t t;
    struct tm* p;
    time(&t);
    p = localtime(&t);
    printf("\n\n%s��%d-%d-%d %d:%d:%d���д򿨿���\n\n\n", use->realname, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    FILE* fp = fopen(CLOCK_FILE, "a+");
    fprintf(fp, "%s��%d-%d-%d %d:%d:%d���д򿨿���\n", use->realname, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    fclose(fp);
    system("pause");
    return;
}
//��ѯ�򿨼�¼
void clock_record()
{
    char ch[100] = { 0 };
    FILE* fp = fopen(CLOCK_FILE, "r");
    fgets(ch, 100, fp);
    if (strlen(ch) == 0)
    {
        printf("��û�п�����Ϣ��\n");
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
    printf("��0�˳�����1������һ������2��ռ�¼\n");
    scanf("%d", &t);
    switch (t)
    {
    case 0:fflush(stdin); system("cls"); exit(0); break;
    case 1:fflush(stdin); system("cla"); return;
    case 2:fflush(stdin);
        fp = fopen(CLOCK_FILE, "w");
        fclose(fp);
        printf("����ɹ�\n");
        return;
    default:fflush(stdin); return;
    }
}