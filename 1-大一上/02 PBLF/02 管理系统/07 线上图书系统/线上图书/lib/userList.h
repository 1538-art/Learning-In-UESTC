#ifndef USERLIST_H
#define USERLIST_H

#define MAX_USER_NAME_LEN 100
#define MAX_PASSWORD_LEN 20
#define MAX_PHONE_NUMBER_LEN 30

typedef struct userInfo
{
    char userName[MAX_USER_NAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char phone[MAX_PHONE_NUMBER_LEN];
    int isAdmin;
    int borrowTimes; // 借书次数
    int numBeBor;    // 未归还数量
    int credibility; // 信誉积分
} userInfo;

typedef struct userInfoNode
{
    struct userInfo userInfomation;
    struct userInfoNode *next;
} userNode;

typedef struct userList
{
    userNode *head;
} userList;

#endif