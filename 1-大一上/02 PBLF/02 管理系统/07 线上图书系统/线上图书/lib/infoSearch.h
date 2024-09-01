#include <stdio.h>
#include <string.h>
#include "bookList.h"
#include "userList.h"
#include "network.h"

#ifndef SEARCH_H
#define SEARCH_H

bookNode *searchBookCode(bookList *list, int bookCode, int sockfd)
{
    bookNode *current = NULL;
    bool found = false;

    for (current = list->head; current; current = current->next)
    {
        if (current->bookInfomation.bookCode == bookCode)
        {
            found = true;
            return current;
        }
    }

    if (!found)
    {
        sendShortMessage(sockfd, "对不起，图书馆暂时没有这本书!输入任意内容继续\n");
        return NULL;
    }
}

void naivePatternMatching(bookList *list, const char *pattern, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    char tempBuffer[4096];

    int patternLen = strlen(pattern);
    bool found = false;
    int bookCount = 0;
    for (bookNode *current = list->head; current != NULL; current = current->next)
    {
        int textLen = strlen(current->bookInfomation.bookName);
        if (bookCount >= 20)
            break;
        for (int i = 0; i <= textLen - patternLen; ++i)
        {
            int j;
            for (j = 0; j < patternLen; ++j)
            {
                if (current->bookInfomation.bookName[i + j] != pattern[j])
                {
                    break;
                }
            }

            if (j == patternLen)
            {
                if (!found)
                {
                    sprintf(buffer, "书号: %d\n书名: %s\n作者: %s\n书类: %s\n位置: %s\n是否借出: %s\n\n",
                            current->bookInfomation.bookCode, current->bookInfomation.bookName,
                            current->bookInfomation.author, current->bookInfomation.bookClass,
                            current->bookInfomation.location, current->bookInfomation.islend);

                    found = true;
                    bookCount++;
                }
                else
                {
                    memset(tempBuffer, 0, sizeof(tempBuffer));
                    sprintf(tempBuffer, "书号: %d\n书名: %s\n作者: %s\n书类: %s\n位置: %s\n是否借出: %s\n\n",
                            current->bookInfomation.bookCode, current->bookInfomation.bookName,
                            current->bookInfomation.author, current->bookInfomation.bookClass,
                            current->bookInfomation.location, current->bookInfomation.islend);
                    strcat(buffer, tempBuffer);
                    bookCount++;
                }
            }
        }
    }

    if (found)
    {
        memset(tempBuffer, 0, sizeof(tempBuffer));
        sprintf(tempBuffer, "共 %d 个结果\n输入任意内容继续\n", bookCount);
        strcat(buffer, tempBuffer);
        sendLongMessage(sockfd, buffer);
    }
    else
    {
        sendShortMessage(sockfd, "对不起，图书馆暂时没有这本书!\n输入任意内容继续\n");
    }
}

void searchBookClass(bookList *list, char *bookClass, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    char tempBuffer[4096];

    bookNode *current = NULL;
    bool found = false;
    int bookCount = 0;

    for (current = list->head; current && bookCount < 30; current = current->next)
    {
        if (strcmp(current->bookInfomation.bookClass, bookClass) == 0)
        {
            if (!found)
            {
                sprintf(buffer, "书号: %d\n书名: %s\n作者: %s\n书类: %s\n位置: %s\n是否借出: %s\n\n",
                        current->bookInfomation.bookCode, current->bookInfomation.bookName,
                        current->bookInfomation.author, current->bookInfomation.bookClass,
                        current->bookInfomation.location, current->bookInfomation.islend);

                found = true;
                bookCount++;
            }
            else
            {
                memset(tempBuffer, 0, sizeof(tempBuffer));
                sprintf(tempBuffer, "书号: %d\n书名: %s\n作者: %s\n书类: %s\n位置: %s\n是否借出: %s\n\n",
                        current->bookInfomation.bookCode, current->bookInfomation.bookName,
                        current->bookInfomation.author, current->bookInfomation.bookClass,
                        current->bookInfomation.location, current->bookInfomation.islend);
                strcat(buffer, tempBuffer);
                bookCount++;
            }
        }
    }

    if (found)
    {
        memset(tempBuffer, 0, sizeof(tempBuffer));
        sprintf(tempBuffer, "共 %d 个结果\n输入任意内容继续\n", bookCount);
        strcat(buffer, tempBuffer);
        sendLongMessage(sockfd, buffer);
    }
    else
    {
        sendShortMessage(sockfd, "对不起，图书馆暂时没有这本书!\n输入任意内容继续\n");
    }
}

void userInfoSearch(userList *ulist, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    sendShortMessage(sockfd, "输入要查询的用户名:\n");
    char userName[MAX_USER_NAME_LEN];
    recvMessage(sockfd, userName);

    userNode *current = ulist->head;
    while (current)
    {
        if (strcmp(current->userInfomation.userName, userName) == 0)
        {
            sprintf(buffer, "用户名:%s 密码:%s 电话:%s 借书次数:%d 在借图书数:%d\n\n输入任意内容继续\n",
                    current->userInfomation.userName, current->userInfomation.password,
                    current->userInfomation.phone, current->userInfomation.borrowTimes,
                    current->userInfomation.numBeBor);
            sendLongMessage(sockfd, buffer);
            return; // 找到用户后立即返回
        }
        current = current->next;
    }

    // 循环结束，用户不存在
    sendShortMessage(sockfd, "用户不存在!输入任意内容继续\n");
}

#endif