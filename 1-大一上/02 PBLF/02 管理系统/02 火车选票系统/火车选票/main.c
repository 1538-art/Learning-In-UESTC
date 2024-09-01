#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include"prepare.h"
#include"operation.h"
extern int saveflag;

 
int main()
{
    FILE*fp1,*fp2 ;
    Node *p,*r ;
    char ch1,ch2 ;
    Link l ;
    bookLink k ;
    book *t,*h ;
    int sel ;
    l=(Node*)malloc(sizeof(Node));
    l->next=NULL ;
    r=l ;
    k=(book*)malloc(sizeof(book));
    k->next=NULL ;
    h=k ;
    fp1=fopen("f:\\train.txt","ab+");/*打开存储车票信息的文�?*/
    if((fp1==NULL))
    {
        printf("can't open the file!");
        return 0 ;
    }
    while(!feof(fp1))
    {
        p=(Node*)malloc(sizeof(Node));
        if(fread(p,sizeof(Node),1,fp1)==1)/*从指定磁盘文件读取记�?*/
        {
            p->next=NULL ;
            r->next=p ;/*构造链�?*/
            r=p ;
        }
    }
    fclose(fp1);
    fp2=fopen("f:\\man.txt","ab+");
    if((fp2==NULL))
    {
        printf("can't open the file!");
        return 0 ;
    }
    
    while(!feof(fp2))
    {
        t=(book*)malloc(sizeof(book));
        if(fread(t,sizeof(book),1,fp2)==1)
        {
            t->next=NULL ;
            h->next=t ;
            h=t ;
        }
    }
    fclose(fp2);
    while(1)
    {
        system("CLS");
        menu();
        printf("\tplease choose (0~6):  ");
        scanf("%d",&sel);
        system("CLS"); 
        if(sel==0)
        {
	    if(saveflag==1)/*当退出时判断信息是否保存*/
            {
                getchar();
                printf("\nthe file have been changed!do you want to save it(y/n)?\n");
                scanf("%c",&ch1);
                if(ch1=='y'||ch1=='Y')
                {
		    SaveBookInfo(k);
                    SaveTrainInfo(l);
                }
            }
            printf("\nThank you!!You are welcome too\n");
            break ;

        }
        switch(sel)/*根据输入的sel值不同选择相应操作*/
        {
            case 1 :
              Traininfo(l);break ;
            case 2 :
              searchtrain(l);break ;
            case 3 :
              Bookticket(l,k);break ;
            case 4 :
              Modify(l);break ;
	    case 5:
		    showtrain(l);break;
            case 6 :
	      SaveTrainInfo(l);SaveBookInfo(k);break ;
            case 0:
            return 0;
        }
        printf("\nplease press any key to continue.......");
        getchar();
    }
}
