#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookList.h"
#include "userList.h"
#include "saveInfo.h"
#include "adminSystem.h"
#include "randomKey.h"
#include "network.h"

#ifndef LOGIN_H
#define LOGIN_H

userNode *registerUser(userList *ulist, int sockfd)
{
    userNode *newUser = (userNode *)malloc(sizeof(userNode));
    sendShortMessage(sockfd, "请输入用户名: ");
    recvMessage(sockfd, newUser->userInfomation.userName);
    sendShortMessage(sockfd, "请输入密码: ");
    recvMessage(sockfd, newUser->userInfomation.password);
    sendShortMessage(sockfd, "请输入手机号码: ");
    recvMessage(sockfd, newUser->userInfomation.phone);
    newUser->userInfomation.isAdmin = 0;
    newUser->userInfomation.borrowTimes = 0;
    newUser->userInfomation.numBeBor = 0;
    newUser->userInfomation.credibility = 5;

    FILE *fpAddUserInfo = fopen("info/UserInfo.txt", "a");
    fprintf(fpAddUserInfo, "0 ");
    fprintf(fpAddUserInfo, "%s ", newUser->userInfomation.userName);
    fprintf(fpAddUserInfo, "%s ", newUser->userInfomation.password);
    fprintf(fpAddUserInfo, "%s ", newUser->userInfomation.phone);
    fprintf(fpAddUserInfo, "0 ");
    fprintf(fpAddUserInfo, "0 ");
    fprintf(fpAddUserInfo, "5\n");
    fclose(fpAddUserInfo);

    if (ulist->head == NULL)
    {
        ulist->head = newUser;
    }
    else
    {
        userNode *current = ulist->head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newUser;
    }

    char buffer[2];
    sendShortMessage(sockfd, "注册成功!输入任意内容继续\n");
    recvMessage(sockfd, buffer);
    return newUser;
}

userNode *loginUser(userList *ulist, int sockfd)
{
    char username[MAX_USER_NAME_LEN];
    char password[MAX_PASSWORD_LEN];
    sendShortMessage(sockfd, "请输入用户名: ");
    recvMessage(sockfd, username);
    sendShortMessage(sockfd, "请输入密码: ");
    recvMessage(sockfd, password);
    for (userNode *current = ulist->head; current != NULL; current = current->next)
    {
        if (strcmp(current->userInfomation.userName, username) == 0 && strcmp(current->userInfomation.password, password) == 0)
        {
            char buffer[2];
            sendShortMessage(sockfd, "登录成功!输入任意内容继续\n");
            recvMessage(sockfd, buffer);
            return current;
        }
    }
    char buffer[2];
    sendShortMessage(sockfd, "用户名或密码错误!输入任意内容退出\n");
    recvMessage(sockfd, buffer);
    return NULL;
}

userNode *registerAdmin(userList *alist, int sockfd)
{
    char anwser[40], key[40];
    strcpy(key, generateKey());
    sendShortMessage(sockfd, "请输入管理员注册密钥(在info/key.txt中,需带上\"{}\"): ");
    recvMessage(sockfd, anwser);
    if (strcmp(anwser, key) != 0)
    {
        char buffer[2];
        sendShortMessage(sockfd, "密钥错误!注册失败!输入任意内容退出\n");
        recvMessage(sockfd, buffer);
        return NULL;
    }

    userNode *newAdmin = (userNode *)malloc(sizeof(userNode));
    sendShortMessage(sockfd, "请输入管理员用户名(至多20位): ");
    recvMessage(sockfd, newAdmin->userInfomation.userName);
    sendShortMessage(sockfd, "请输入管理员密码(至多20位): ");
    recvMessage(sockfd, newAdmin->userInfomation.password);
    newAdmin->userInfomation.isAdmin = 1;

    FILE *fp = fopen("info/AdminInfo.txt", "a");
    fprintf(fp, "1 ");
    fprintf(fp, "%s ", newAdmin->userInfomation.userName);
    fprintf(fp, "%s\n", newAdmin->userInfomation.password);
    fclose(fp);
    if (alist->head == NULL)
    {
        alist->head = newAdmin;
    }
    else
    {
        userNode *current = alist->head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newAdmin;
    }

    char buffer[2];
    sendShortMessage(sockfd, "管理员账号注册成功!输入任意内容继续\n");
    recvMessage(sockfd, buffer);
    return newAdmin;
}

userNode *loginAdmin(userList *alist, int sockfd)
{
    char username[MAX_USER_NAME_LEN];
    char password[MAX_PASSWORD_LEN];
    sendShortMessage(sockfd, "请输入管理员用户名: ");
    recvMessage(sockfd, username);
    sendShortMessage(sockfd, "请输入管理员密码: ");
    recvMessage(sockfd, password);

    for (userNode *current = alist->head; current != NULL; current = current->next)
    {
        if (strcmp(current->userInfomation.userName, username) == 0 && strcmp(current->userInfomation.password, password) == 0)
        {
            char buffer[2];
            sendShortMessage(sockfd, "登录成功!输入任意内容继续\n");
            recvMessage(sockfd, buffer);
            return current;
        }
    }
    char buffer[2];
    sendShortMessage(sockfd, "管理员用户名或密码错误!输入任意内容退出\n");
    recvMessage(sockfd, buffer);
    return NULL;
}

userNode *resetPassword(userList *ulist, int sockfd)
{
    char username[MAX_USER_NAME_LEN];
    char phone[MAX_PHONE_NUMBER_LEN];
    char newPassword[MAX_PASSWORD_LEN];

    sendShortMessage(sockfd, "请输入用户名: ");
    recvMessage(sockfd, username);
    sendShortMessage(sockfd, "请输入手机号码: ");
    recvMessage(sockfd, phone);

    for (userNode *current = ulist->head; current != NULL; current = current->next)
    {
        if (strcmp(current->userInfomation.userName, username) == 0 && strcmp(current->userInfomation.phone, phone) == 0)
        {
            sendShortMessage(sockfd, "请输入新密码(至多20位): ");
            recvMessage(sockfd, newPassword);
            strcpy(current->userInfomation.password, newPassword);

            char buffer[2];
            sendShortMessage(sockfd, "重置密码成功!输入任意内容继续\n");
            recvMessage(sockfd, buffer);
            saveUserInfo(ulist);
            return current;
        }
    }
    char buffer[2];
    sendShortMessage(sockfd, "验证失败，重置密码失败!输入任意内容退出\n");
    recvMessage(sockfd, buffer);
    return NULL;
}

#endif