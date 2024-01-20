#include <stdio.h>
#include "bookList.h"
#include "userList.h"

#ifndef STATS_H
#define STATS_H

void bookData(bookList *list)
{
    FILE *fp = fopen("stats/book.csv", "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    fprintf(fp, "Book Code,Book Name,Author,Publish House,Book Class,Is Lend,Position,Lend Date,Latest Return Date,Lend Times,Publication Date,Borrower\n");
    bookNode *currentBook = list->head;
    while (currentBook)
    {
        fprintf(fp, "%d ,%s ,%s ,%s ,%s ,%s ,%s ,%s ,%s ,%d ,%d ,%s\n",
                currentBook->bookInfomation.bookCode, currentBook->bookInfomation.bookName,
                currentBook->bookInfomation.author, currentBook->bookInfomation.publishHouse,
                currentBook->bookInfomation.bookClass, currentBook->bookInfomation.islend,
                currentBook->bookInfomation.location, currentBook->bookInfomation.lendDate,
                currentBook->bookInfomation.returnDate, currentBook->bookInfomation.lendTimes,
                currentBook->bookInfomation.publicationDate, currentBook->bookInfomation.borrower);
        currentBook = currentBook->next;
    }
    fclose(fp);
}
void userData(userList *list)
{
    FILE *fp = fopen("stats/user.csv", "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    fprintf(fp, "Username,Password,Phone Number,Borrow Times,Unreturned Books,Credit Points\n");
    userNode *currentUser = list->head;
    while (currentUser != NULL)
    {
        fprintf(fp, "%s,%s,%s,%d,%d,%d\n",
                currentUser->userInfomation.userName, currentUser->userInfomation.password,
                currentUser->userInfomation.phone, currentUser->userInfomation.borrowTimes,
                currentUser->userInfomation.numBeBor, currentUser->userInfomation.credibility);
        currentUser = currentUser->next;
    }
    fclose(fp);
}

#endif