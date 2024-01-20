#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include "head.h"

void openfile(user** head){
	FILE *fp=fopen("userdata.txt","r");
	
	user *current=NULL;
	user *pre=NULL;

	
	while(1){	
	user *pnew=(user*)malloc(sizeof(user));
	if (fscanf(fp, "%s %d %s %d %d %d %d %d %d %d %d %d\n", pnew->name,&(pnew->acc) , pnew->pas ,
	&(pnew->score[0][0]),&(pnew->score[0][1]),&(pnew->score[0][2]),
	&(pnew->score[1][0]),&(pnew->score[1][1]),&(pnew->score[1][2]),
	&(pnew->score[2][0]),&(pnew->score[2][1]),&(pnew->score[2][2])
	) !=12 ){
	    free(pnew);
		break;
	}
	    pnew->pnext=NULL;
		if(current==NULL){
			current=pnew;
			*head=pnew;
		}
		else{
			current=pnew;
			pre->pnext=pnew;
		}
		pre=current;
	}
	
	fclose(fp);
}

void login(user *head){
	system("cls");
	user a;
	user *tem=head;
	printf("请输入您的账号（仅限数字）:\n");
    scanf("%d",&a.acc );
 
    while(head!=NULL){
    	if(a.acc ==head->acc){   
		printf("请输入您的密码(10个字符以内):\n");
        scanf("%s",a.pas );
    	if(strcmp(a.pas,head->pas)==0){
    		printf("登录成功!\n"); 
    		sleep(1);
    		system("cls");
    	    gamepage(&tem,a.acc);
		} 	
        else{
        	printf("\n您输入的密码错误!\n"); 
        	sleep(1);
        	loginpage(tem);
		}
		}
		head=head->pnext;
        }   
        
      printf("\n\t\t账号错误，请重新输入!\n");  
      sleep(1);
      loginpage(tem);
}

void loginpage(user *head){
	system("cls");
	for(int j=0;j<48;j++){
		printf("*");
	}
	printf("\n\n"); 
	printf("\t\t欢迎来到登录界面\n\n");
	printf("\t\t1.登录\n\n");
	printf("\t\t2.退回首页\n\n");
	for(int j=0;j<48;j++)
{
	printf("*");
	}	
	printf("\n\n\t请选择:");
	int choice;
	scanf("%d",&choice);
	
	switch(choice){
		case 1:
			login(head);
			break;
		case 2:
			homepage(head);
		default :
			printf("请输入1或者2\n");
			Sleep(500);
			system("cls"); 
			loginpage(head);
	} 
}


void regist(user **head){
	system("cls");
	user a;
	user **tem=head;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			a.score[i][j]=-1;
		}
	}
		
	printf("请输入您的账号（仅限数字）:\n");
	scanf("%d",&a.acc);
	printf("请输入您的用户名（十个字符以内）:\n");
	scanf("%s",&a.name);
	printf("请输入您的密码（十个字符以内）\n");
	scanf("%s",&a.pas);
	
	
	 while(*head!=NULL){
	 	if(a.acc ==(*head)->acc){
	 		printf("\n账号重复!");
	 		sleep(1);
	 		system("cls");
	 		registpage(tem);
		 }
		 	if(a.name==(*head)->name){
	 		printf("\n用户名重复，请重新输入!");
	 		sleep(1);
	 		system("cls");
	 		registpage(tem);
		 }
		 *head=(*head)->pnext;
	 }
	 
	 
	 FILE *fp=fopen("userdata.txt","a+");
	 fprintf(fp,"%s %d %s %d %d %d %d %d %d %d %d %d\n",a.name,a.acc,a.pas,
	 a.score[0][0],a.score[0][1],a.score[0][2],
	 a.score[1][0],a.score[1][1],a.score[1][2],
	 a.score[2][0],a.score[2][1],a.score[2][2]);
	 fclose(fp);
	 printf("注册成功");
	 sleep(1);
	 user *b=NULL;
	 openfile(&b);
	 homepage(b);
}

void homepage(user *head){
	system("cls");
	for(int j=0;j<48;j++){
		printf("*");
	}
	printf("\n");
	printf("\n");
	printf("\t\t");
	printf("欢迎来到小游戏合集\n");
	printf("\n");
	printf("\t\t1.登录\n"); 
	printf("\n");
	printf("\t\t2.注册\n\n"); 

	for(int j=0;j<48;j++){
		printf("*");
	}
		
	printf("\n\n");
	printf("\t    请选择：");
    int chioce;
    scanf("%d",&chioce); 
    switch(chioce){
    	case 1:
    		loginpage(head);
    		break;
    	case 2:
		    registpage(&head);
			break;	
		default :
			printf("\n请输入1或者2\n");
			Sleep(500);
			system("cls"); 
			homepage(head);
	}
}

void registpage(user **head){
	system("cls");
	for(int j=0;j<48;j++){
		printf("*");
	}
	printf("\n\n");
	printf("\t\t欢迎来到注册界面\n\n");
	printf("\t\t1.注册\n\n");
	printf("\t\t2.返回首页\n\n");
	for(int j=0;j<48;j++){
		printf("*");
	}
	printf("\n\n");
	printf("\t    请选择：");
	
	int choice;
	scanf("%d",&choice);
	
	switch(choice){
		case 1:
			regist(head);
		case 2:
		    homepage((*head)) ;
		default :
			printf("请输入1或者2\n");
			Sleep(500);
			system("cls"); 
			registpage(head);
	}
}
void gamepage(user **head,int account){
	
	for(int j=0;j<48;j++){
		printf("*");
	}
	printf("\n");
	printf("\t\t欢迎来到游戏界面\n\n");
	printf("\t    1.扫雷\n\n");
	printf("\t    2.贪吃蛇\n\n");
	printf("\t    3.跳跃小子\n\n");
	printf("\t    4.注销账户\n\n");
	printf("\t    5.查看本地历史记录\n\n");
	printf("\t    6.返回首页\n\n");
	 for(int j=0;j<48;j++){
		printf("*");
	}
	printf("\n\n");
	
	printf("\t    请选择:");
	
	int choice;
	int a;
	scanf("%d",&choice);
	switch(choice){
		case 1:
			a=sweep();
			putinlocallist(head,account,a,choice-1);
	    case 2:
	    	a=snake();
	    	putinlocallist(head,account,a,choice-1);
	   	case 3:
	   		a=jumpman();
	   		putinlocallist(head,account,a,choice-1);
	    case 4:
	    	dele(head,account);
	    case 5:
	    	locallist(head,account);
	    case 6:
	    	homepage(*head);
	    default :
			printf("请输入1到6之间的整数\n");
			Sleep(500);
			system("cls"); 
			gamepage(head,account);
	}

}

void locallist(user **head,int account){
	system("cls");
	user **tem=head;
	while(head!=NULL){
	if(account==(*head)->acc){
		for(int j=0;j<48;j++){
			printf("*");
		}
		printf("\n\n");
		printf("\t\t扫雷分数\n");
		for(int j=0;j<3;j++){
			if((*head)->score[0][j]>=0){
				printf("\t\t%d.%d分\n",j+1,(*head)->score[0][j]);
				}
			else printf("\t\t无\n");
		}
		printf("\n");
		printf("\t\t贪吃蛇分数\n");
		for(int j=0;j<3;j++){
			if((*head)->score[1][j]>=0){
				printf("\t\t%d.%d分\n",j+1,(*head)->score[1][j]);
				}
			else printf("\t\t无\n");
	    }
	    printf("\n");
	    printf("\t\t跳跃小子分数\n");
		for(int j=0;j<3;j++){
			if((*head)->score[2][j]>=0){
				printf("\t\t%d.%d分\n",j+1,(*head)->score[2][j]);
				}
			else printf("\t\t无\n");
	    }
	    for(int j=0;j<48;j++){
	    	printf("*");
		} 
		break;}
	(*head)=(*head)->pnext;
	}
	printf("\n\n按任意键返回首页");
	char c;
	scanf("%c\n",&c);
	getchar();
	system("cls");
	gamepage(tem,account);
}

void dele(user **head,int account){
 	user *pre=NULL;
	user *tem=*head;
	int cnt=1;
	
  while((*head)!=NULL){
		if((*head)->acc==account){
			
		if(cnt==1){
			tem=(*head)->pnext;
			break;
		}
		
			pre->pnext=(*head)->pnext;
			break;
		}
		
		if(cnt==1){
		pre=*head;
		*head=(*head)->pnext;
		}
		
		else{
		pre->pnext=*head;
		pre=pre->pnext;
		*head=(*head)->pnext;
		}
		
		cnt++; 
	}
	
	pre=tem;
	
	FILE *fp=fopen("userdata.txt","w");
	while(pre!=NULL){
		fprintf(fp,"%s %d %s %d %d %d %d %d %d %d %d %d\n",pre->name,pre->acc,pre->pas,
		pre->score[0][0],pre->score[0][1],pre->score[0][2],
		pre->score[1][0],pre->score[1][1],pre->score[1][2],
		pre->score[2][0],pre->score[2][1],pre->score[2][2]);
		pre=pre->pnext;
	}
	
	fclose(fp);
	printf("删除成功");
	sleep(1);
	system("cls");
    homepage(tem);
}
void putinlocallist(user** head,int account ,int scorenum,int num){
	user *pre=*head;
	user *tem=*head;
	while(tem!=NULL){
	if(tem->acc==account){
		int num1=tem->score[num][0];
		int num2=tem->score[num][1];
		int num3=tem->score[num][2];
		if(scorenum>=num1){
			tem->score[num][0]=scorenum;
			tem->score[num][1]=num1;
			tem->score[num][2]=num2;
			break;
		}
		if(scorenum>=num2){
			tem->score[num][0]=num1;
			tem->score[num][1]=scorenum;
			tem->score[num][2]=num2;
			break;
		}
		if(scorenum>=num3){
			tem->score[num][0]=num1;
			tem->score[num][1]=num2;
			tem->score[num][2]=scorenum;
			break;
		}
	}
	tem=tem->pnext;		
}
    
	FILE *fp=fopen("userdata.txt","w");
	while(pre!=NULL){
		fprintf(fp,"%s %d %s %d %d %d %d %d %d %d %d %d\n",pre->name,pre->acc,pre->pas,
		pre->score[0][0],pre->score[0][1],pre->score[0][2],
		pre->score[1][0],pre->score[1][1],pre->score[1][2],
		pre->score[2][0],pre->score[2][1],pre->score[2][2]);
		pre=pre->pnext;
	}
	
	fclose(fp);
	sleep(1);
	system("cls");
	gamepage(head,account);
}
