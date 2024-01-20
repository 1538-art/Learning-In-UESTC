#ifndef BOOKLIST_H
#define BOOKLIST_H

#define MAX_BOOK_NAME_LEN 100
#define MAX_AUTHOR_NAME_LEN 100
#define MAX_PUBLISH_HOUSE_NAME_LEN 100
#define POSITION_LEN 100
#define DATE_LEN 11

typedef struct bookInfo // 图书基本信息
{
    int bookCode;                                  // 书号
    char bookName[MAX_BOOK_NAME_LEN];              //
    char author[MAX_AUTHOR_NAME_LEN];              //
    char publishHouse[MAX_PUBLISH_HOUSE_NAME_LEN]; // 出版社
    char bookClass[15];                            // 类别
    char islend[4];                                // 判断是否借出
    char location[POSITION_LEN];                   // 位置(未借出的话)
    char lendDate[DATE_LEN];                       // 借出时间
    char returnDate[DATE_LEN];                     // 应该归还的最迟时间
    int lendTimes;                                 // 借阅次数
    int publicationDate;
    char borrower[100];
} bookInfo;

typedef struct bookInfoNode // 图书信息节点
{
    struct bookInfo bookInfomation;
    struct bookInfoNode *next;
} bookNode;

typedef struct bookList // 图书信息链表
{
    bookNode *head;
} bookList;

#endif