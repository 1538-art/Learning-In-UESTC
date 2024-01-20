#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include "prepare.h"


extern int saveflag;
void Modify(Link l)
{
    Node *p ;
    char tnum[10],ch ;
    p=l->next;
    if(!p)
    {
        printf("\nthere isn't record for you to modify!\n");
        return ;
    }
    else
    {
	    printf("\nDo you want to modify it?(y/n)\n");
            getchar();
            scanf("%c",&ch);
            if(ch=='y'||ch=='Y')
            {
                printf("\nInput the number of the train:");
		scanf("%s",tnum);
	while(p!=NULL)
	if(strcmp(p->data.num,tnum)==0)/*查找与输入的车号相匹配的记录*/
	    break;
        else
            p=p->next;
                if(p)
                {
                    printf("Input new number of train:");
                    scanf("%s",p->data.num);
		    printf("Input new city the train will start:");
                    scanf("%s",p->data.startcity);
                    printf("Input new city the train will reach:");
                    scanf("%s",p->data.reachcity);
                    printf("Input new time the train take off");
		    scanf("%s",p->data.takeofftime);
                    printf("Input new time the train reach:");
		    scanf("%s",p->data.receivetime);
                    printf("Input new price of the ticket::");
                    scanf("%d",&p->data.price);
                    printf("Input new number of people who have booked ticket:");
                    scanf("%d",&p->data.ticketnum);
                    printf("\nmodifying record is sucessful!\n");
                    saveflag=1 ;
                }
                else
                printf("\tcan't find the record!");
            }
    }
}
void showtrain(Link l)/*自定义函数显示列车信�?*/
{
Node *p;
p=l->next;
printheader();
if(l->next==NULL)
printf("no records!");
else
 while(p!=NULL)
{
	printdata(p);
	p=p->next;
}
}
/*保存火车信息*/
void SaveTrainInfo(Link l)
{
    FILE*fp ;
    Node*p ;
    int count=0,flag=1 ;
    fp=fopen("f:\\train.txt","wb");
    if(fp==NULL)
    {
        printf("the file can't be opened!");
        return ;
    }
    p=l->next ;
    while(p)
    {
        if(fwrite(p,sizeof(Node),1,fp)==1)
        {
            p=p->next ;
            count++;
        }
        else
        {
            flag=0 ;
            break ;
        }
    }
    if(flag)
    {
        printf(" saved %d train records\n",count);
        saveflag=0 ;
    }
    fclose(fp);
}
/*保存订票人的信息*/
void SaveBookInfo(bookLink k)
{
    FILE*fp ;
    book *p ;
    int count=0,flag=1 ;
    fp=fopen("f:\\man.txt","wb");
    if(fp==NULL)
    {
        printf("the file can't be opened!");
        return ;
    }
    p=k->next ;
    while(p)
    {
	if(fwrite(p,sizeof(book),1,fp)==1)
        {
            p=p->next ;
            count++;
        }
        else
        {
            flag=0 ;
            break ;
        }
    }
    if(flag)
    {
        printf(" saved %d booking records\n",count);
        saveflag=0 ;
    }
    fclose(fp);
}