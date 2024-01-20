#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include "prepare.h"
#define HEADER1 " -------------------------------BOOK TICKET----------------------------------\n"
#define HEADER2 " |  number  |start city|reach city|takeofftime|receivetime|price|ticketnumber|\n"
#define HEADER3 " |----------|----------|----------|-----------|-----------|-----|------------|\n"
#define FORMAT  " |%-10s|%-10s|%-10s|%-10s |%-10s |%5d|  %5d     |\n"
#define DATA p->data.num,p->data.startcity,p->data.reachcity,p->data.takeofftime,p->data.receivetime,p->data.price,p->data.ticketnum
int saveflag = 0;

/* 初始界面*/
void menu()
{
    puts("\n\n");
    puts("\t\t|------------------------------------------------------|");
    puts("\t\t|                   Booking Tickets                    |");
    puts("\t\t|------------------------------------------------------|");
    puts("\t\t|       0:quit the system                              |");
    puts("\t\t|       1:Insert a train information                   |");
    puts("\t\t|       2:Search a train information                   |");
    puts("\t\t|       3:Book a train ticket                          |");
    puts("\t\t|       4:Modify the train information                 |");
    puts("\t\t|       5:Show the train information                   |");
    puts("\t\t|       6:save information to file                     |");
    puts("\t\t|------------------------------------------------------|");
}
/*添加一个火车信�?*/
void Traininfo(Link linkhead)
{
    struct node *p,*r,*s ;
    char num[10];
    r = linkhead ;
    s = linkhead->next ;
    while(r->next!=NULL)
    r=r->next ;
    while(1)
    {
        printf("please input the number of the train(0-return)");
        scanf("%s",num);
        if(strcmp(num,"0")==0)
          break ;
        /*判断是否已经存在*/
        while(s)
        {
            if(strcmp(s->data.num,num)==0)
            {
                printf("the train '%s'is existing!\n",num);
                return ;
            }
            s = s->next ;
        }
        p = (struct node*)malloc(sizeof(struct node));
        strcpy(p->data.num,num);/*输入车号*/
	 printf("Input the city where the train will start:");
        scanf("%s",p->data.startcity);/*输入出发城市*/
        printf("Input the city where the train will reach:");
        scanf("%s",p->data.reachcity);/*输入到站城市*/
        printf("Input the time which the train take off:");
	scanf("%s",p->data.takeofftime);/*输入出发时间*/
        printf("Input the time which the train receive:");
	scanf("%s",p->data.receivetime);/*输入到站时间*/
        printf("Input the price of ticket:");
        scanf("%d",&p->data.price);/*输入火车票价*/
        printf("Input the number of booked tickets:");
	scanf("%d",&p->data.ticketnum);/*输入预定票数*/
        p->next=NULL ;
        r->next=p ;/*插入到链表中*/
        r=p ;
       saveflag = 1 ;
    }
}
/* */
void printheader() /*��ʽ����ӡ��ͷ*/
{
printf(HEADER1);
printf(HEADER2);
printf(HEADER3);
}
void printdata(Node *q) /*格式化输出表中数�?*/
{
Node* p;
p=q;
printf(FORMAT,DATA);
}

/*查询火车信息*/
void searchtrain(Link l)

{
    Node *s[10],*r;
    int sel,k,i=0 ;
    char str1[5],str2[10];
    if(!l->next)
    {
        printf("There is not any record !");
        return ;
    }
    printf("Choose the way:\n1:according to the number of train;\n2:according to the city:\n");
    scanf("%d",&sel);/*输入选择的序�?*/
    if(sel==1)
    {
        printf("Input the the number of train:");
        scanf("%s",str1);
        r=l->next;
	while(r!=NULL)
        if(strcmp(r->data.num,str1)==0)/*检索是否有与输入的车号相匹配的*/
        {
            s[i]=r;
	    i++;
	    break;
        }
        else 
            r=r->next;
    }
    else if(sel==2)
    {
        printf("Input the city  you want to go:");
        scanf("%s",str2);
        r=l->next;
	while(r!=NULL)
        if(strcmp(r->data.reachcity,str2)==0)/*检索是否有与输入的城市相匹配的火车*/
        {
            s[i]=r;
	    i++;
	    r=r->next;
        }
        else 
            r=r->next;
    }
    	if(i==0)
		printf("can not find!");
	else
	{
		printheader();
    for(k=0;k<i;k++)
printdata(s[k]);
	}
}

/*订票子模�?*/
void Bookticket(Link l,bookLink k)
{
    Node *r[10],*p ;
    char ch[2],tnum[10],str[10],str1[10],str2[10];
    book *q,*h ;
    int i=0,t=0,flag=0,dnum;
    q=k ;
    while(q->next!=NULL)
    q=q->next ;
    printf("Input the city you want to go: ");
    scanf("%s",str);/*输入要到达的城市*/
    p=l->next ;
    while(p!=NULL)
    {
        if(strcmp(p->data.reachcity,str)==0)
        {
            r[i]=p ;/*将满足条件的记录存到数组r�?*/
            i++;
        }
        p=p->next ;
    }
    printf("\n\nthe number of record have %d\n",i);
       printheader();
    for(t=0;t<i;t++)
	    printdata(r[t]);
    if(i==0)
    printf("\nSorry!Can't find the train for you!\n");
    else
    {
        printf("\ndo you want to book it?<y/n>\n");
        scanf("%s",ch);
	if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*判断是否订票*/
        {
	    h=(book*)malloc(sizeof(book));
            printf("Input your name: ");
            scanf("%s",str1);
            strcpy(h->data.name,str1);
            printf("Input your id: ");
            scanf("%s",str2);
            strcpy(h->data.num,str2);
	    printf("please input the number of the train:");
	    scanf("%s",tnum);
	    for(t=0;t<i;t++)
	    if(strcmp(r[t]->data.num,tnum)==0)
	    {
	       if(r[t]->data.ticketnum<1)/*判断剩余的供订票的票数是否为0*/
	       {
		       printf("sorry,no ticket!");
		       sleep(2);
		       return;
	       }
	      printf("remain %d tickets\n",r[t]->data.ticketnum);
               flag=1;
	       break;
	    }
	    if(flag==0)
	    {
		    printf("input error");
		   sleep(2);
                    return;
	    }
	    printf("Input your bookNum: ");
            scanf("%d",&dnum);
            r[t]->data.ticketnum=r[t]->data.ticketnum-dnum;/*定票成功则可供订的票数相应减�?*/
	    h->data.bookNum=dnum ;
            h->next=NULL ;
	    q->next=h ;
	    q=h ;
            printf("\nLucky!you have booked a ticket!");
            getchar();
            saveflag=1 ;
        }
    }
}
/*修改火车信息*/
