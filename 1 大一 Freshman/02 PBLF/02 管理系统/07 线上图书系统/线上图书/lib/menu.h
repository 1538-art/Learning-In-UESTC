#include <stdio.h>
#include "userSystem.h"
#include "adminSystem.h"
#include "loginSystem.h"
#include "bookList.h"
#include "userList.h"
#include "statsInfo.h"
#include "infoSearch.h"
#include "network.h"

#ifndef MENU_H
#define MENU_H

userNode *loginSystem(userList *ulist, userList *alist, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "\n\n\t\t    登录系统\n\n");
    strcat(buffer, "**********************************************");
    strcat(buffer, "\n\n\t\t1:普通用户登录\n\n");
    strcat(buffer, "\n\n\t\t2:管理员登录\n\n");
    strcat(buffer, "\n\n\t\t其他:退出系统\n\n");
    strcat(buffer, "\n\n\t    请按键选择，回车确定\n");
    strcat(buffer, "**********************************************\n");
    sendLongMessage(sockfd, buffer);

    int choice = recvInt(sockfd, buffer);
    switch (choice)
    {
    case 1:
        return loginUser(ulist, sockfd);
    case 2:
        return loginAdmin(alist, sockfd);
    default:
        return NULL;
    }
    return NULL;
}

userNode *createAccount(userList *ulist, userList *alist, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    strcpy(buffer, "\n\n\t\t    注册账号\n\n");
    strcat(buffer, "**********************************************");
    strcat(buffer, "\n\n\t\t1:普通用户注册\n\n");
    strcat(buffer, "\n\n\t\t2:管理员注册\n\n");
    strcat(buffer, "\n\n\t\t其他:退出系统\n\n");
    strcat(buffer, "\n\n\t    请按键选择，回车确定\n");
    strcat(buffer, "**********************************************\n");
    sendLongMessage(sockfd, buffer);

    int choice = recvInt(sockfd, buffer);
    switch (choice)
    {
    case 1:
        return registerUser(ulist, sockfd);
    case 2:
        return registerAdmin(alist, sockfd);
    default:
        break;
    }
    return NULL;
}

void userMenu(bookList *list, userNode *user, int sockfd)
{
    while (1)
    {
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));

        strcpy(buffer, "\n\n\t      普通用户系统菜单\n\n");
        strcat(buffer, "**********************************************");
        strcat(buffer, "\n\n\t\t1:图书信息查询\n\n");
        strcat(buffer, "\n\n\t\t2:自助借阅系统\n\n");
        strcat(buffer, "\n\n\t\t3:图书归还系统\n\n");
        strcat(buffer, "\n\n\t\t4:热门图书推荐\n\n");
        strcat(buffer, "\n\n\t\t其他:退出系统\n\n");
        strcat(buffer, "\n\n\t    请按键选择，回车确定\n");
        strcat(buffer, "**********************************************\n");
        sendLongMessage(sockfd, buffer);

        int choice = recvInt(sockfd, buffer);
        switch (choice)
        {
        case 1:
            bookInfoSearch(list, sockfd);
            break;
        case 2:
            borrowBook(list, user, sockfd);
            break;
        case 3:
            returnBook(list, user, sockfd);
            break;
        case 4:
            generateBookRanking(list, sockfd);
            break;
        default:
            return;
        }
        recvMessage(sockfd, buffer);
    }
}

void sortBookMenu(bookList *list, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    strcpy(buffer, "\n\n\t    图书排序菜单\n\n");
    strcat(buffer, "**********************************************");
    strcat(buffer, "\n\n\t\t1:按书号从小到大排序\n\n");
    strcat(buffer, "\n\n\t\t2:按借阅人数从大到小排序\n\n");
    strcat(buffer, "\n\n\t\t其他:退出系统\n\n");
    strcat(buffer, "\n\n\t    请按键选择，回车确定\n");
    strcat(buffer, "**********************************************\n");
    sendLongMessage(sockfd, buffer);
    int temp = 1;
    do
    {
        int choice = recvInt(sockfd, buffer);
        switch (choice)
        {
        case 1:
            sortBookCode(list, sockfd);
            temp = 1;
            break;
        case 2:
            sortBookReader(list, sockfd);
            temp = 1;
            break;
        default:
            temp = 0;
            sendShortMessage(sockfd, "无效的选项,请重新输入:");
            break;
        }
    } while (temp == 0);
}

void bookInfoMenu(bookList *list, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    strcpy(buffer, "\n\n\t      图书信息管理\n\n");
    strcat(buffer, "**********************************************");
    strcat(buffer, "\n\n\t\t1:查询图书\n\n");
    strcat(buffer, "\n\n\t\t2:录入图书\n\n");
    strcat(buffer, "\n\n\t\t3:删除图书\n\n");
    strcat(buffer, "\n\n\t\t4:图书排序\n\n");
    strcat(buffer, "\n\n\t\t5:图书信息统计\n\n");
    strcat(buffer, "\n\n\t    请按键选择，回车确定\n");
    strcat(buffer, "**********************************************\n");
    sendLongMessage(sockfd, buffer);
    int temp = 1;
    do
    {
        int choice = recvInt(sockfd, buffer);
        switch (choice)
        {
        case 1:
            bookInfoSearch(list, sockfd);
            temp = 1;
            break;
        case 2:
            bookInput(list, sockfd);
            temp = 1;
            break;
        case 3:
            deleteBook(list, sockfd);
            temp = 1;
            break;
        case 4:
            sortBookMenu(list, sockfd);
            temp = 1;
            break;
        case 5:
            bookData(list);
            sendShortMessage(sockfd, "统计文件已生成在服务端的stats文件夹下\n输入任意内容继续\n");
            temp = 1;
            break;
        default:
            temp = 0;
            sendShortMessage(sockfd, "无效的选项,请重新输入:");
            break;
        }
    } while (temp == 0);
}

void userInfoMenu(userList *ulist, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    strcpy(buffer, "\n\n\t      用户信息管理\n\n");
    strcat(buffer, "**********************************************");
    strcat(buffer, "\n\n\t\t1:查询用户\n\n");
    strcat(buffer, "\n\n\t\t2:删除用户\n\n");
    strcat(buffer, "\n\n\t\t3:用户排序\n\n");
    strcat(buffer, "\n\n\t\t4:用户信息统计\n\n");
    strcat(buffer, "\n\n\t    请按键选择，回车确定\n");
    strcat(buffer, "**********************************************\n");
    sendLongMessage(sockfd, buffer);
    int temp = 1;
    do
    {
        int choice = recvInt(sockfd, buffer);
        switch (choice)
        {
        case 1:
            userInfoSearch(ulist, sockfd);
            temp = 1;
            break;
        case 2:
            deleteUser(ulist, sockfd);
            temp = 1;
            break;
        case 3:
            sortUser(ulist, sockfd);
            temp = 1;
            break;
        case 4:
            userData(ulist);
            sendShortMessage(sockfd, "统计文件已生成在服务端的stats文件夹下\n输入任意内容继续\n");
            temp = 1;
            break;
        default:
            temp = 0;
            sendShortMessage(sockfd, "无效的选项,请重新输入:");
            break;
        }
    } while (temp == 0);
}

void adminMenu(bookList *list, userList *ulist, int sockfd)
{
    while (1)
    {
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));

        strcpy(buffer, "\n\n\t\t    信息管理\n\n");
        strcat(buffer, "**********************************************");
        strcat(buffer, "\n\n\t\t1:图书信息管理\n\n");
        strcat(buffer, "\n\n\t\t2:用户信息管理\n\n");
        strcat(buffer, "\n\n\t\t其他:退出系统\n\n");
        strcat(buffer, "\n\n\t    请按键选择，回车确定\n");
        strcat(buffer, "**********************************************\n");
        sendLongMessage(sockfd, buffer);

        int choice = recvInt(sockfd, buffer);
        switch (choice)
        {
        case 1:
            bookInfoMenu(list, sockfd);
            break;
        case 2:
            userInfoMenu(ulist, sockfd);
            break;
        default:
            return;
        }
        recvMessage(sockfd, buffer);
    }
}

userNode *welcomeMenu(bookList *list, userList *ulist, userList *alist, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    strcpy(buffer, "\n\n\t    欢迎使用图书管理系统\n\n");
    strcat(buffer, "**********************************************");
    strcat(buffer, "\n\n\t\t1:登录系统\n\n");
    strcat(buffer, "\n\n\t\t2:创建账号\n\n");
    strcat(buffer, "\n\n\t\t3:修改密码\n\n");
    strcat(buffer, "\n\n\t\t其他:退出系统\n\n");
    strcat(buffer, "\n\n\t    请按键选择，回车确定\n");
    strcat(buffer, "**********************************************\n");
    sendLongMessage(sockfd, buffer);

    int choice = recvInt(sockfd, buffer);
    switch (choice)
    {
    case 1:
        return loginSystem(ulist, alist, sockfd);
    case 2:
        return createAccount(ulist, alist, sockfd);
    case 3:
        return resetPassword(ulist, sockfd);
    default:
        break;
    }
    return NULL;
}

#endif