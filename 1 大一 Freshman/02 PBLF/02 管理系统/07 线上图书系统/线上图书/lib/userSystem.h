#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bookList.h"
#include "userList.h"
#include "saveInfo.h"
#include "calTime.h"
#include "infoSearch.h"
#include "network.h"

#ifndef USER_H
#define USER_H

void bookInfoSearch(bookList *list, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    sendShortMessage(sockfd, "请选择要如何查询:\n\t1-按图书编号来查询     2-按图书名字查询    3-按种类查询图书\n");
    int choice = recvInt(sockfd, buffer);
    switch (choice)
    {
    case 1:
        sendShortMessage(sockfd, "请输入编号:");
        int bookCode = recvInt(sockfd, buffer);

        bookNode *current = searchBookCode(list, bookCode, sockfd);
        if (current)
        {
            sprintf(buffer, "书号: %d\n书名: %s\n作者: %s\n书类: %s\n位置: %s\n是否借出: %s\n\n输入任意内容继续\n",
                    current->bookInfomation.bookCode, current->bookInfomation.bookName,
                    current->bookInfomation.author, current->bookInfomation.bookClass,
                    current->bookInfomation.location, current->bookInfomation.islend);
            sendLongMessage(sockfd, buffer);
        }
        return;
    case 2:
        char bookName[MAX_BOOK_NAME_LEN];
        memset(bookName, 0, sizeof(bookName));
        sendShortMessage(sockfd, "请输入书名:");
        recvMessage(sockfd, bookName);

        naivePatternMatching(list, bookName, sockfd);
        return;
    case 3:
        char bookClass[15];
        memset(bookClass, 0, sizeof(bookClass));
        sendShortMessage(sockfd, "请输入您要查询的图书种类:");
        recvMessage(sockfd, bookClass);

        searchBookClass(list, bookClass, sockfd);
        return;
    default:
        sendShortMessage(sockfd, "未知选择!\n输入任意内容继续\n");
        return;
    }
}

void borrowBook(bookList *list, userNode *user, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    char tempBuffer[4096];
    memset(tempBuffer, 0, sizeof(tempBuffer));

    if (user->userInfomation.numBeBor >= 5)
    {
        sendShortMessage(sockfd, "对不起，您的借阅次数已达上限\n输入任意内容继续\n");
        return;
    }
    if (user->userInfomation.credibility <= 0)
    {
        sendShortMessage(sockfd, "你没有借阅资格!\n输入任意内容继续\n");
        return;
    }

    sendShortMessage(sockfd, "请输入要借阅的图书编号: ");
    int bookcode = recvInt(sockfd, buffer);

    bookNode *p = NULL;
    bool found = false;

    for (p = list->head; p; p = p->next)
    {
        if (p->bookInfomation.bookCode == bookcode)
        {
            found = true;
            if (strcmp(p->bookInfomation.islend, "yes") == 0)
            {
                sendShortMessage(sockfd, "对不起，该书已经借出!\n输入任意内容继续\n");
            }
            else
            {
                strcpy(p->bookInfomation.islend, "yes");
                strcpy(p->bookInfomation.borrower, user->userInfomation.userName);

                getCurrentDate(p->bookInfomation.lendDate);
                calculateFutureDate(p->bookInfomation.lendDate, 45, p->bookInfomation.returnDate);

                user->userInfomation.borrowTimes++;
                user->userInfomation.numBeBor++;

                strcpy(buffer, "借阅成功!\n");
                sprintf(tempBuffer, "现在是 %s , 归还截至时间为 %s.\n输入任意内容继续\n", p->bookInfomation.lendDate, p->bookInfomation.returnDate);
                strcat(buffer, tempBuffer);
                sendLongMessage(sockfd, buffer);

                // 增加借阅次数
                p->bookInfomation.lendTimes++;
            }
            break;
        }
    }

    if (!found)
    {
        sendShortMessage(sockfd, "对不起，图书馆暂时没有这本书!\n输入任意内容继续\n");
    }
}

void returnBook(bookList *list, userNode *user, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    sprintf(buffer, "您还有%d本书没有归还。\n请输入要归还的图书编号: ", user->userInfomation.numBeBor);
    sendLongMessage(sockfd, buffer);

    int bookcode = recvInt(sockfd, buffer);
    char returnDate[11];

    bookNode *p = NULL;
    bool found = false;
    getCurrentDate(returnDate);
    for (p = list->head; p; p = p->next)
    {
        if (p->bookInfomation.bookCode == bookcode)
        {
            found = true;
            if (strcmp(p->bookInfomation.borrower, user->userInfomation.userName) != 0)
            {
                sendShortMessage(sockfd, "你没有借这本书\n输入任意内容继续\n");
                break;
            }
            if (dateDifference(p->bookInfomation.lendDate, returnDate) <= 45)
            {
                sendShortMessage(sockfd, "归还成功!输入任意内容继续\n");
            }
            else
            {
                sprintf(buffer, "您的借阅时间已超时,已扣除1信誉积分,现在剩余%d分,下次请注意及时还书!\n输入任意内容继续\n", user->userInfomation.credibility - 1);
                sendLongMessage(sockfd, buffer);
                user->userInfomation.credibility--;
            }
            user->userInfomation.numBeBor--;
            strcpy(p->bookInfomation.islend, "not");
            strcpy(p->bookInfomation.lendDate, "NULL");
            strcpy(p->bookInfomation.returnDate, "NULL");
            strcpy(p->bookInfomation.borrower, "NULL");
        }
    }
    if (!found)
    {
        sendShortMessage(sockfd, "对不起，您输入的编码无效!\n输入任意内容继续\n");
    }
}

void generateBookRanking(bookList *list, int sockfd) // 图书排行榜
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    char tempBuffer[4096];
    memset(tempBuffer, 0, sizeof(tempBuffer));

    // 创建临时链表，用于存储排序结果
    bookList *rankingList = (bookList *)malloc(sizeof(bookList));
    rankingList->head = NULL;

    // 遍历原链表，将图书按照借阅次数插入到排行榜链表中
    bookNode *current = list->head;
    while (current != NULL)
    {
        // 创建新节点
        bookNode *newNode = (bookNode *)malloc(sizeof(bookNode));
        newNode->bookInfomation = current->bookInfomation;
        newNode->next = NULL;

        // 在排行榜链表中找到插入位置
        bookNode *prev = NULL;
        bookNode *temp = rankingList->head;
        while (temp && temp->bookInfomation.lendTimes > newNode->bookInfomation.lendTimes)
        {
            prev = temp;
            temp = temp->next;
        }

        // 插入新节点
        if (prev == NULL)
        {
            newNode->next = rankingList->head;
            rankingList->head = newNode;
        }
        else
        {
            newNode->next = prev->next;
            prev->next = newNode;
        }

        current = current->next;
    }

    // 打印图书排行榜
    strcpy(buffer, "热门图书排行榜：\n");
    int rank = 1;
    bookNode *currentRank = rankingList->head;
    while (currentRank != NULL && rank <= 20)
    {
        sprintf(tempBuffer, "%d. %s (作者：%s, 书号: %d) - 借阅次数：%d\n", rank, currentRank->bookInfomation.bookName,
                currentRank->bookInfomation.author, currentRank->bookInfomation.bookCode, currentRank->bookInfomation.lendTimes);
        currentRank = currentRank->next;
        strcat(buffer, tempBuffer);
        memset(tempBuffer, 0, sizeof(tempBuffer));
        rank++;
    }
    strcat(buffer, "\n输入任意内容继续\n");
    sendLongMessage(sockfd, buffer);

    // 释放排行榜链表的内存
    bookNode *currentRankNode = rankingList->head;
    while (currentRankNode != NULL)
    {
        bookNode *temp = currentRankNode;
        currentRankNode = currentRankNode->next;
        free(temp);
    }

    free(rankingList);
}

#endif