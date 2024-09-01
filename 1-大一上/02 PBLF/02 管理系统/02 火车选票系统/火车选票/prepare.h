#ifndef  PRETREATMENT_H_
#define  PRETREATMENT_H

struct train 
{
    char num[10];/*列车�?*/
    char startcity[10];/*出发城市*/
    char reachcity[10];/*目的城市*/
    char takeofftime[10];/*发车时间*/
    char receivetime[10];/*到达时间*/
    int  price;/*票价*/
    int  ticketnum ;/*票数*/
};
/*订票人的信息*/
struct man 
{
    char num[10];/*ID*/
    char name[10];/*姓名*/
    int  bookNum ;/*订的票数*/
};
/*定义火车信息链表的结点结�?*/
typedef struct node 
{
    struct train data ;
    struct node * next ;
}Node,*Link ;
/*定义订票人链表的结点结构*/
typedef struct Man 
{
    struct man data ;
    struct Man *next ;
}book,*bookLink ;

void menu();
void Traininfo(Link linkhead);
void printheader();
void printdata(Node *q);
void searchtrain(Link l);
void Bookticket(Link l,bookLink k);


#endif
