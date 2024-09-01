#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookList.h"
#include "userList.h"

#ifndef INIT_H
#define ININ_H

void initList(bookList *list)
{
    FILE *fpReadBookLine = fopen("info/BookInfo.txt", "r");
    int bookCount, i;
    bookCount = i = 0;
    char ch;
    while ((ch = fgetc(fpReadBookLine)) != EOF)
    {
        if (ch == '\n')
        {
            bookCount++;
        }
    }
    fclose(fpReadBookLine);
    bookNode *current = NULL;
    FILE *fp = fopen("info/BookInfo.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file : BookInfo.txt\n");
        return;
    }
    for (list->head = NULL; i < bookCount; i++)
    {
        bookNode *newNode = (bookNode *)malloc(sizeof(bookNode));
        fscanf(fp, "%s", newNode->bookInfomation.bookClass);
        fscanf(fp, "%s", newNode->bookInfomation.bookName);
        fscanf(fp, "%s", newNode->bookInfomation.author);
        fscanf(fp, "%d", &newNode->bookInfomation.bookCode);
        fscanf(fp, "%d", &newNode->bookInfomation.publicationDate);
        fscanf(fp, "%s", newNode->bookInfomation.publishHouse);
        fscanf(fp, "%s", newNode->bookInfomation.islend);
        fscanf(fp, "%s", newNode->bookInfomation.location);
        fscanf(fp, "%s", newNode->bookInfomation.lendDate);
        fscanf(fp, "%s", newNode->bookInfomation.returnDate);
        fscanf(fp, "%d", &newNode->bookInfomation.lendTimes);
        fscanf(fp, "%s", newNode->bookInfomation.borrower);

        if (list->head == NULL)
        {
            list->head = newNode;
            current = list->head;
            current->next = NULL;
        }
        else
        {
            current->next = newNode;
            current = current->next;
            current->next = NULL;
        }
    }
    fclose(fp);
}

void initUserList(userList *ulist)
{
    FILE *fpReadUserLine = fopen("info/UserInfo.txt", "r");
    if (fpReadUserLine == NULL)
    {
        printf("Error opening file : UserInfo.txt\n");
        return;
    }
    int userCount, i;
    userCount = i = 0;
    char ch;
    while ((ch = fgetc(fpReadUserLine)) != EOF)
    {
        if (ch == '\n')
        {
            userCount++;
        }
    }
    fclose(fpReadUserLine);
    userNode *current = NULL;
    FILE *fp = fopen("info/UserInfo.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file : UserInfo.txt\n");
        return;
    }
    for (ulist->head = NULL; i < userCount; i++)
    {
        userNode *newNode = (userNode *)malloc(sizeof(userNode));
        fscanf(fp, "%d", &newNode->userInfomation.isAdmin);
        fscanf(fp, "%s", newNode->userInfomation.userName);
        fscanf(fp, "%s", newNode->userInfomation.password);
        fscanf(fp, "%s", newNode->userInfomation.phone);
        fscanf(fp, "%d", &newNode->userInfomation.borrowTimes);
        fscanf(fp, "%d", &newNode->userInfomation.numBeBor);
        fscanf(fp, "%d", &newNode->userInfomation.credibility);
        if (ulist->head == NULL)
        {
            ulist->head = newNode;
            current = ulist->head;
            current->next = NULL;
        }
        else
        {
            current->next = newNode;
            current = current->next;
            current->next = NULL;
        }
    }
    fclose(fp);
}

void initAdminList(userList *alist)
{
    FILE *fpReadUserLine = fopen("info/AdminInfo.txt", "r");
    if (fpReadUserLine == NULL)
    {
        printf("Error opening file : AdminInfo.txt\n");
        return;
    }

    int adminCount, i;
    adminCount = i = 0;
    char ch;
    while ((ch = fgetc(fpReadUserLine)) != EOF)
    {
        if (ch == '\n')
        {
            adminCount++;
        }
    }
    fclose(fpReadUserLine);

    userNode *current = NULL;
    FILE *fp = fopen("info/AdminInfo.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file : AdminInfo.txt\n");
        return;
    }
    for (alist->head = NULL; i < adminCount; i++)
    {
        userNode *newNode = (userNode *)malloc(sizeof(userNode));
        fscanf(fp, "%d", &newNode->userInfomation.isAdmin);
        fscanf(fp, "%s", newNode->userInfomation.userName);
        fscanf(fp, "%s", newNode->userInfomation.password);
        if (alist->head == NULL)
        {
            alist->head = newNode;
            current = alist->head;
            current->next = NULL;
        }
        else
        {
            current->next = newNode;
            current = current->next;
            current->next = NULL;
        }
    }
    fclose(fp);
    return;
}

void freeList(bookList *list, userList *ulist, userList *alist)
{
    userNode *currentU = ulist->head;
    while (currentU)
    {
        userNode *temp = currentU;
        currentU = currentU->next;
        free(temp);
    }
    ulist->head = NULL;
    free(ulist);

    userNode *currentA = alist->head;
    while (currentA)
    {
        userNode *temp = currentA;
        currentA = currentA->next;
        free(temp);
    }
    alist->head = NULL;
    free(alist);

    bookNode *current = list->head;
    while (current)
    {
        bookNode *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    free(list);
}

#endif