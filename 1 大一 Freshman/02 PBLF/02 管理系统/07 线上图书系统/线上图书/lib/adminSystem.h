#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookList.h"
#include "userList.h"
#include "saveInfo.h"
#include "network.h"

#ifndef ADMIN_H
#define ADMIN_H

void bookInput(bookList *list, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    bookNode *newbook = (bookNode *)malloc(sizeof(bookNode));
    sendShortMessage(sockfd, "请输入图书类别:");
    recvMessage(sockfd, newbook->bookInfomation.bookClass);
    sendShortMessage(sockfd, "请输入图书名:");
    recvMessage(sockfd, newbook->bookInfomation.bookName);
    sendShortMessage(sockfd, "请输入图书作者:");
    recvMessage(sockfd, newbook->bookInfomation.author);
    sendShortMessage(sockfd, "请输入图书书号:");
    newbook->bookInfomation.bookCode = recvInt(sockfd, buffer);
    sendShortMessage(sockfd, "请输入图书出版日期(仅输入年份):");
    newbook->bookInfomation.publicationDate = recvInt(sockfd, buffer);
    sendShortMessage(sockfd, "请输入图书出版社:");
    recvMessage(sockfd, newbook->bookInfomation.publishHouse);
    strcpy(newbook->bookInfomation.islend, "not");
    sendShortMessage(sockfd, "请输入图书位置:");
    recvMessage(sockfd, newbook->bookInfomation.location);

    strcpy(newbook->bookInfomation.lendDate, "NULL");
    strcpy(newbook->bookInfomation.returnDate, "NULL");
    newbook->bookInfomation.lendTimes = 0;
    strcpy(newbook->bookInfomation.borrower, "NULL");

    FILE *fp = fopen("info/BookInfo.txt", "a");
    fprintf(fp, "%s ", newbook->bookInfomation.bookClass);
    fprintf(fp, "%s ", newbook->bookInfomation.bookName);
    fprintf(fp, "%s ", newbook->bookInfomation.author);
    fprintf(fp, "%d ", newbook->bookInfomation.bookCode);
    fprintf(fp, "%d ", newbook->bookInfomation.publicationDate);
    fprintf(fp, "%s ", newbook->bookInfomation.publishHouse);
    fprintf(fp, "%s ", newbook->bookInfomation.islend);
    fprintf(fp, "%s ", newbook->bookInfomation.location);
    fprintf(fp, "%s ", newbook->bookInfomation.lendDate);
    fprintf(fp, "%s ", newbook->bookInfomation.returnDate);
    fprintf(fp, "%d ", newbook->bookInfomation.lendTimes);
    fprintf(fp, "%s\n", newbook->bookInfomation.borrower);

    fclose(fp);

    if (list->head == NULL)
    {
        list->head = newbook;
    }
    else
    {
        bookNode *current = list->head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newbook;
    }

    sendShortMessage(sockfd, "录入完成!\n输入任意内容继续\n");
}

void deleteBook(bookList *list, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    bookNode *current = list->head;
    bookNode *prev = NULL;
    sendShortMessage(sockfd, "请输入要删除的图书的图书编码：");
    int bookCode = recvInt(sockfd, buffer);

    while (current)
    {
        if (current->bookInfomation.bookCode == bookCode)
        {
            if (prev == NULL)
            {
                // 如果要删除的节点是链表的头节点
                list->head = current->next;
            }
            else
            {
                // 如果要删除的节点不是链表的头节点
                prev->next = current->next;
            }

            // 释放要删除的节点的内存
            free(current);

            sprintf(buffer, "%d 已删除!\n输入任意内容继续\n", bookCode);
            sendLongMessage(sockfd, buffer);
            return;
        }

        prev = current;
        current = current->next;
    }

    sprintf(buffer, "%d 不存在\n输入任意内容继续\n", bookCode);
    sendLongMessage(sockfd, buffer);
}

void deleteUser(userList *ulist, int sockfd)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    userNode *current = ulist->head;
    userNode *prev = NULL;
    sendShortMessage(sockfd, "请输入要删除的用户的用户名：");
    char user[MAX_USER_NAME_LEN];
    recvMessage(sockfd, user);

    while (current)
    {
        if (strcmp(current->userInfomation.userName, user) == 0)
        {
            if (prev == NULL)
            {
                // 如果要删除的节点是链表的头节点
                ulist->head = current->next;
            }
            else
            {
                // 如果要删除的节点不是链表的头节点
                prev->next = current->next;
            }

            // 释放要删除的节点的内存
            free(current);

            sprintf(buffer, "%s 已删除！\n输入任意内容继续\n", user);
            sendLongMessage(sockfd, buffer);
            return;
        }

        // 移动到链表中的下一个节点
        prev = current;
        current = current->next;
    }

    sprintf(buffer, "%s 未找到！\n输入任意内容继续\n", user);
    sendLongMessage(sockfd, buffer);
}

void sortBookCode(bookList *list, int sockfd)
{
    if (!list || !list->head || !list->head->next)
        return;

    bool swapped;
    bookNode *current;
    do
    {
        swapped = false;
        for (current = list->head; current->next != NULL; current = current->next)
        {
            if (current->bookInfomation.bookCode > current->next->bookInfomation.bookCode)
            {
                bookInfo temp = current->bookInfomation;
                current->bookInfomation = current->next->bookInfomation;
                current->next->bookInfomation = temp;
                swapped = true;
            }
        }
    } while (swapped);
    sendShortMessage(sockfd, "图书排序完成\n输入任意内容继续\n");
}

void sortBookReader(bookList *list, int sockfd)
{
    if (!list || !list->head || !list->head->next)
        return;

    bool swapped;
    bookNode *current;
    do
    {
        swapped = false;
        for (current = list->head; current->next != NULL; current = current->next)
        {
            if (current->bookInfomation.lendTimes < current->next->bookInfomation.lendTimes)
            {
                bookInfo temp = current->bookInfomation;
                current->bookInfomation = current->next->bookInfomation;
                current->next->bookInfomation = temp;
                swapped = true;
            }
        }
    } while (swapped);
    sendShortMessage(sockfd, "图书排序完成\n输入任意内容继续\n");
}

void sortUser(userList *ulist, int sockfd)
{
    if (!ulist || !ulist->head || !ulist->head->next)
        return;

    bool swapped;
    userNode *current;
    do
    {
        swapped = false;
        for (current = ulist->head; current->next != NULL; current = current->next)
        {
            if (current->userInfomation.borrowTimes < current->next->userInfomation.borrowTimes)
            {
                userInfo temp = current->userInfomation;
                current->userInfomation = current->next->userInfomation;
                current->next->userInfomation = temp;
                swapped = true;
            }
        }
    } while (swapped);
    sendShortMessage(sockfd, "用户排序完成\n输入任意内容继续\n");
}

#endif