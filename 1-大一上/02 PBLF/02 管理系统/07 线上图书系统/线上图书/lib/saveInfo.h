#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookList.h"
#include "userList.h"

#ifndef SAVEINFO_H
#define SAVEINFO_H

void saveBookInfo(bookList *list)
{
    bookNode *current = list->head;
    FILE *fp = fopen("info/BookInfo.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file : BookInfo.txt\n");
        return;
    }
    while (current)
    {
        fprintf(fp, "%s ", current->bookInfomation.bookClass);
        fprintf(fp, "%s ", current->bookInfomation.bookName);
        fprintf(fp, "%s ", current->bookInfomation.author);
        fprintf(fp, "%d ", current->bookInfomation.bookCode);
        fprintf(fp, "%d ", current->bookInfomation.publicationDate);
        fprintf(fp, "%s ", current->bookInfomation.publishHouse);
        fprintf(fp, "%s ", current->bookInfomation.islend);
        fprintf(fp, "%s ", current->bookInfomation.location);
        fprintf(fp, "%s ", current->bookInfomation.lendDate);
        fprintf(fp, "%s ", current->bookInfomation.returnDate);
        fprintf(fp, "%d ", current->bookInfomation.lendTimes);
        fprintf(fp, "%s\n", current->bookInfomation.borrower);

        current = current->next;
    }
    fclose(fp);
}

void saveUserInfo(userList *ulist)
{
    userNode *current = ulist->head;
    FILE *fp = fopen("info/UserInfo.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file : UserInfo.txt\n");
        return;
    }
    while (current)
    {
        fprintf(fp, "%d ", current->userInfomation.isAdmin);
        fprintf(fp, "%s ", current->userInfomation.userName);
        fprintf(fp, "%s ", current->userInfomation.password);
        fprintf(fp, "%s ", current->userInfomation.phone);
        fprintf(fp, "%d ", current->userInfomation.borrowTimes);
        fprintf(fp, "%d ", current->userInfomation.numBeBor);
        fprintf(fp, "%d\n", current->userInfomation.credibility);

        current = current->next;
    }
    fclose(fp);
}

#endif