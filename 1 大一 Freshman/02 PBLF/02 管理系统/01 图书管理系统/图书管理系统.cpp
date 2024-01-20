/*图书管理系统   终极确定版*/ 

#include<stdio.h>
#include<stdlib.h>  //有system函数
#include<conio.h>   //有通过控制台进行数据输入和数据输出的函数
#include<string.h>  //有字符数组
#include<math.h>
#define  LEN   sizeof(struct library)//有关图书信息的结构体
#define  LEN1  sizeof(struct reader) //有关读者信息的结构体

struct library//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%图书馆结构体
{
	int xcl;//库存
	float price;//单价
	char name[20],author[20],chuban[20],kind[20],shuhao[20];
	struct library *next;
};


struct reader//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%读者结构体
{
	int zhenghao;
	char mingzi[20],riqi[20],zname[20];
	struct reader *next;
};


void mainmenu()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~主菜单
{ 
	system ("cls");//清除屏幕先前显示的内容 ,往下运行（在stdlib.h头文件中） 
	printf("\n\n\n				^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ");
	printf("\n\n\n						1.__库存图书信息__\n\n");
	printf("\n\n 						2.__借阅图书系统__\n\n");
	printf("\n\n 						3.__退出管理系统__\n\n");
	//printf("\n\n 					 ^~^请您按键选择and回车确定哦~.~\n\n\n");
	printf(" 				^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ \n");
}


void menu1() //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~显示 图书信息 菜单
{ 
	system ("cls");
	printf("\n\n\n				 ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ");
	printf("\n\n 				    		1.__图书入库__\n\n");
	printf("\n 						2.__图书清理__\n\n");
	printf("\n 						3.__图书查询__\n\n");
	printf("\n 						4.__库存概览__\n\n");
	printf("\n 						5..返回上一层..\n\n");
	//printf("\n 					^~^请您按键选择and回车确定哦*.*\n\n");
	printf(" 				 ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ \n");
}


void menu2() //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~显示 借阅系统 菜单
{ 
	system ("cls");
	printf("请输入书号,书名,作者或类别查询：\n");
	printf("类别（科学技术 语言文学 政治经济 历史地理 意识形态 艺术）\n\n");
}


void main1()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~main1函数
{
	void tsgxx();//声明 图书馆信息 函数 
	void jieshuxitong();//声明 借书系统 函数
	char choose;
	
	mainmenu();//显示主菜单 
	scanf("%c",&choose);
	
	switch(choose)//功能函数选择
	{ 
		case '1':	tsgxx();
		break;
		
		case '2':	jieshuxitong();	
		break;	
		
		case '3':   system ("cls");
		printf("\n\n\n  删改内容已经保存了呢 ^、^\n\n\n  任意键安全退出哦 ^、^\n\n");
		exit(0);//exit关闭所有文件，终止正在执行的程序。exit(0):正常退出
		break;
	}
}


void tsgxx()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~图书馆信息函数
{ 
	void tsjinku();//声明 图书进库 函数 
	void shanchu();//声明 删除图书信息 函数 
	void chaxunts();//声明 查询图书 函数 
	void kucunxinxi();//声明 显示库存 函数 
	char choose;
	
	menu1();//显示 图书信息 菜单 
	getchar();//吞掉一个显示出menu1函数后的进行下一步的回车      
	
	scanf("%c",&choose);
	
	for (;;)//在返回上一级前循环输入                                                                                                                                                    //？？？ 
		switch(choose)
	{ 
		case '1':	tsjinku();
		break;
		case '2':	shanchu();
		break;
		case '3':	chaxunts();
		break;
		case '4':	kucunxinxi();
		break;
		case '5':	main1();//返回上一级 
		break;
	}
}


int kucungs()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~统计库存图书文本个数函数
{ 
	FILE *fp;//定义一个指针 
	int txcl=0,n;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},tchuban[20]={'\0'},tkind[20]={'\0'},tshuhao[20]={'\0'};
	
	fp=fopen("library.txt","r");//打开文件  fopen("文件名.文件类型"，"权限")； 
	
	for (n=0;!feof(fp);n++)//逐个读文件(feof(fp):检测是否以及读取到文件尾部,到达尾部返回1，否则返回0)
		fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);
	n--;
	
	fclose(fp);//关闭文件
	return (n);//返回个数
}


int duzhegs()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~统计读者文本个数函数
{ 
	FILE *fp;
	int zhenghao=0,n;
	char mingzi[20]={'\0'},riqi[20]={'\0'},zname[20]={'\0'};
	
	fp=fopen("reader.txt","r");//打开文件
	
	for (n=0;!feof(fp);n++)//逐个读文件
		fscanf(fp,"%d%s%s%s ",&zhenghao,&mingzi,&riqi,&zname);
	
	fclose(fp);//关闭文件
	return (n);//返回个数
}


void tsjinku()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~图书进库函数
{ 
	FILE *fp;
	int xcl=0,n=0;
	float price=0;
	char name[20]={'\0'},author[20]={'\0'},kind[20]={'\0'},chuban[20]={'\0'},shuhao[20]={'\0'};
	char hitkey; 
	
	system ("cls");
	
	if ((fp=fopen("library.txt","a"))==NULL)//打开图书馆文件，不存在此文件则新建
	{ 
		fp=fopen("library.txt","w");
		fclose(fp);
	}
	
	fp=fopen("library.txt","a");//追加写打开进行录入数据 
	
	printf("\n	请您输入需要添加的图书信息:\n\n	书号	书名	作者	出版社	类别	进库量	单价");
	printf("\n\n	（类别:哲学，文学，教育，艺术，科学，教材，小说，其它）\n	（书号：(XXX) ）\n"); 
	
	for (;hitkey!=27;)//如果输入一组数据后敲了回车键则循环输入 
	{ 
		if (n!=0)
			printf("请输入:\n");//从第二次输入开始提示请输入 
		
		scanf("%s%s%s%s%s%d%f",shuhao,name,author,chuban,kind,&xcl,&price);		
		fprintf(fp,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",shuhao,name,author,chuban,kind,xcl,price);
		
		printf("继续输入请按回车\n结束输入请按Esc\n");
		n++;
		
		hitkey=getch();//记录敲击进来的键                                                                                                                                          		
		for (;hitkey!=13&&hitkey!=27;)//13：\r回车  27：ESC退出                                                                                                                          
			hitkey=getch();//敲击错误可重复敲击 
	}
	fclose(fp);
	
	printf("\n保存成功，按任意键返回上一层!");
	getch();
	tsgxx();//返回上一层
}


void shanchu()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~删除图书信息
{ 
	struct library *head=NULL;
	struct library *p,*p1,*p2;
	int txcl=0,n=0,j,i;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},tchuban[20]={'\0'},tkind[20]={'\0'},ttname[20]={'\0'},tshuhao[20]={'\0'};
	char hitkey;
	FILE *fp;
	
	if ((fp=fopen("library.txt","r"))==NULL)//打开文件
	{ 
		system ("cls");
		
		printf("\n库存图书为零!无法删除图书！\n请按任意键返回\n");
		getch();
		
		tsgxx();
	}
	else
	{ 
		system ("cls");
		
		printf("\n请输入你要删除的书名:");//输入删除图书书名
		scanf("%s",&ttname);
		
		printf("\n确认删除请回车，取消请按Esc\n");
		
		hitkey=getch();
		
		for(;hitkey!=13&&hitkey!=27;)
			hitkey=getch();
		
		if (hitkey==27)
			tsgxx();
		
		fp=fopen("library.txt","r");
		
		for (j=0;!feof(fp);)//读文件夹信息，统计在库图书个数
		{ 
			j++;
			fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);
		}
		
		fclose(fp);
		
		fp=fopen("library.txt","r");
		
		for (i=1;i<j;i++)
		{ 
			fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);
			
			if (strcmp(ttname,tname))//比较名字，将不同名字的信息复制到链表                                                                                     //？？？ 
			{ 
				n++;//相同返回值为0不执行if语句继续循环，不同则执行直到将所有不同的书名建立成链表
				if (n==1)//建立链表
				{ 
					p1=p2=(struct library*)malloc(LEN);
					head=p1;
				}
				else
				{ 
					p2->next=p1;
					p2=p1;
					p1=(struct library*)malloc(LEN);//新建链表
				}
				
				strcpy(p1->shuhao,tshuhao);//复制书号
				strcpy(p1->name,tname);//复制书名
				strcpy(p1->author,tauthor);//复制作者名字
				strcpy(p1->chuban,tchuban);//复制出版社
				strcpy(p1->kind,tkind);//复制类别
				p1->xcl=txcl;//复制个数
				p1->price=tprice;//复制单价
			}
		}
		
		if (n==0)//如果图书只有一项且这一项刚好和要删除的相同
		{ 
			head=NULL;
		}
		else//建立链表的最后剩余一个储存空间，所以封底
		{
			p2->next=p1;
			p1->next=NULL;
			fclose(fp);
		}
	}
	
	fp=fopen("library.txt","w");//清空文件，只写打开，然后关闭
	fclose(fp);
	
	fp=fopen("library.txt","a");//追加文件
	p=head;
	
	for (;p!=NULL;)//把链表内容覆盖到文件
	{
		fprintf(fp,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",p->shuhao,p->name,p->author,p->chuban,p->kind,p->xcl,p->price);
		p=p->next;
	}
	
	fclose(fp);//关闭文件
	system ("cls");
	
	printf("\n删除成功 \n按任意键返回上一层\n");
	getch();//返回上一层
	tsgxx();
}


void chaxunts()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~查询函数
{
	FILE *fp;
	char choose;
	int txcl=0,n=0,k=0,i,l;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},chazhao[20]={'\0'},tchuban[20]={'\0'},
	tshuhao[20]={'\0'},tkind[20]={'\0'};
	
	if ((fp=fopen("library.txt","r"))==NULL)//打开文件
	{ 
		system ("cls");
		printf("\n记录文件不存在!按任意键返回");
		getch();
		tsgxx();
	}
	
	l=kucungs();//获得库存图书个数
	menu2();//提示输入菜单 
	scanf("%s",chazhao);
	system ("cls");
	
	for (i=0;i<l;i++)
	{ 
		fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);//读文件信息
		if(!strcmp(chazhao,tshuhao)||!strcmp(chazhao,tname)||!strcmp(chazhao,tauthor)||!strcmp(chazhao,tkind))//在库存图书里面模糊检索 
		{
			if (k==0)
			{
				printf("查询结果:\n\n");
				printf("书号\t书名\t作者\t\t出版社\t\t类别\t\t现存量\t单价\n");
			}
			printf("%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",tshuhao,tname,tauthor,tchuban,tkind,txcl,tprice);
			k++;
		}
	}
	
	if (k==0)//没有这本书 
	{ 
		system ("cls");
		printf("\n无符合记录!\n");
		getch();
		tsgxx();
	}
	
	fclose(fp);
	getch();//返回
	tsgxx();
}


void kucunxinxi()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~显示库存图书信息
{
	FILE *fp;
	int xcl=0,n=0,i=0,j=0;
	float price=0;
	char name[20]={'\0'},author[20]={'\0'},kind[20]={'\0'},chuban[20]={'\0'},shuhao[20]={'\0'};
	
	if ((fp=fopen("library.txt","r"))==NULL)//打开文件夹
	{
		system ("cls");
		printf("\n记录文件不存在!");
	}
	n= kucungs();
	
	if (n==0)
	{ 
		system ("cls");
		printf("\n无任何记录!");
	}
	
	fp=fopen("library.txt","r");//打开只读文件
	system ("cls");
	printf("书号\t书名\t作者\t\t出版社\t\t类别\t\t库存量\t单价\n");
	
	for (i=0;i<n;i++)//输出所有在库图书信息
	{
		fscanf(fp,"%s%s%s%s%s%d%f",shuhao,name,author,chuban,kind,&xcl,&price);
		printf("%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",shuhao,name,author,chuban,kind,xcl,price);
	}
	
	fclose(fp);
	printf("\n按任意键返回\n");
	getch();//返回
	tsgxx();
}


void menu3() //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~显示借书系统主菜单
{
	system ("cls");
	
	printf("\n 				`~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` ");
	printf("\n\n						1.借书登记\n\n");
	printf("\n\n						2.还书登记\n\n");
	printf("\n\n						3.借阅情况查看\n\n");
	printf("\n\n						4.返回上一层\n\n");
	//printf("\n\n					^~^请按键选择and回车确定哦 *·*\n");
	printf("\n 				`~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~`\n ");	
	
	return ;
}


void jieshuxitong()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~借书系统函数
{ 
	void jieshu();
	void huanshu();
	void duzhexinxi();//函数声明
	char choose;
	
	menu3();
	getchar();//吞掉一个显示出menu3函数后的进行下一步的回车 
	
	scanf("%c",&choose);//选择功能
	
	for (;;)
		switch(choose)
	{ 
		case '1':	jieshu();
		break;	
		
		case '2':	huanshu();
		break;
		
		case '3':	duzhexinxi();
		break;
		
		case '4':	main1();
		break;
	}
}


void jieshu()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~借书函数
{
	FILE *fp,*fp3;
	struct library *head=NULL;
	struct library *p,*p1,*p2;
	int txcl=0,i,loop,zhenghao=0,n=0,k=0,t=0,flag=0;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},tchuban[20]={'\0'},tkind[20]={'\0'},tshuhao[20]={'\0'},
	ttname[20]={'\0'},mingzi[20]={'\0'},riqi[20]={'\0'},zname[20]={'\0'};
	char hitkey=0;
	
	system ("cls");
	
	{
		if ((fp=fopen("library.txt","r"))==NULL)//打开图书馆文件
		{
			system ("cls");
			printf("\n 图书馆无库存!按任意键退出!");
			getch();
			exit (0);
		}
		else
		{
			{
				printf("\n请输入借阅书名:\n请输入:\n");//输入书名
				scanf("%s",zname);
				k= kucungs();//统计图书馆文件个数
				for (i=0;i<k;i++)//读入图书馆信息，存储到链表
				{
					fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);
					n++;
					if (n==1)
					{ 
						p1=p2=(struct library*)malloc(LEN);
						head=p1;
					}
					else
					{ 
						p2->next=p1;
						p2=p1;
						p1=(struct library*)malloc(LEN);//新建链表
					}
					
					strcpy(p1->shuhao,tshuhao);//复制书号	
					strcpy(p1->name,tname);//复制书名
					strcpy(p1->author,tauthor);//复制作者
					strcpy(p1->chuban,tchuban);//复制出版社
					strcpy(p1->kind,tkind);//复制类别
					p1->xcl=txcl;//复制现存量
					p1->price=tprice;//复制单价
				}
				
				if (n==0)
					head=NULL;
				else
				{
					p2->next=p1;
					p1->next=NULL;
					fclose(fp);
				}
			}
		}
		
		p=head;
		for (;p!=NULL;)//读链表
		{
			if(!(strcmp(p->name,zname)))//判断要借书的是否存在
			{
				flag=1;//标记取1
				loop=p->xcl;//现存量减1
				(p->xcl)--;
			}
			p=p->next;
		}
		
		if(flag&&(loop>0))//存在借书书名且现存量大于0，把库存量变化后的链表存入文件
		{ 
			fp=fopen("library.txt","w");
			fclose(fp);
			fp=fopen("library.txt","a");
			p=head;
			
			for (;p!=NULL;)
			{
				fprintf(fp,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",p->shuhao,p->name,p->author,p->chuban,p->kind,p->xcl,p->price);
				p=p->next;
			}
			free(p);//把链表内容覆盖文件
			fclose(fp);
		}
		
		if(flag&&(loop>0))//存在借书书名且现存量大于0
		{
			{
				if ((fp3=fopen("reader.txt","r"))==NULL)//建读者文件夹
				{ 
					fp3=fopen("reader.txt","w");//打开只读文件
					fclose(fp3);			
				}			
				fp3=fopen("reader.txt","a");//以附加的方式打开文件		
			}
			
			{
				{
					if (n!=0)
						printf("\n请按以下格式输入读者信息:\n 证号 姓名 归还日期 借书书名\n请输入:");//录入读者信息
					
					scanf("%d %s %s %s",&zhenghao,&mingzi[20],&riqi[20],&zname[20]);
					fprintf(fp3,"\n%-8d%-23s%-18s%-10s\n",zhenghao,&mingzi[20],&riqi[20],&zname[20]);
					fp=fopen("library.txt","w");//删除图书馆文件信息
					fclose(fp);
					fp=fopen("library.txt","a");//重新追加信息
					p=head;
					
					for (;p!=NULL;)//把链表内容覆盖图书馆文件
					{
						fprintf(fp,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",p->shuhao,p->name,p->author,p->chuban,p->kind,p->xcl,p->price);	
						p=p->next;
					}
					
					fclose(fp);
					fclose(fp3);
					printf("成功!按任意键返回\n");
					getch();//返回
					
					jieshuxitong();//调用借阅系统
				}
			}
			jieshuxitong();//调用借阅系统
		}
		else
			printf("此书已被借完!按任意键返回!");//否则输出此书已被借完
		
		getch();//返回		
		jieshuxitong();//调用借阅系统
	}
}


void huanshu()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~还书函数
{
	FILE *fp,*fp3;	
	struct reader *head=NULL;
	struct reader *p,*p1,*p2;
	struct library *lhead1=NULL;
	struct library *zp1,*lp1,*lp2;
	int txcl=0,i;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},tkind[20]={'\0'},
	tchuban[20]={'\0'},ttname[20]={'\0'},tshuhao[20]={'\0'};
	int ttzhenghao=0,tzhenghao=0,n=0,k=0,t=0,flag=0;
	char tmingzi[20]={'\0'},triqi[20]={'\0'},tzname[20]={'\0'},ttzname[20]={'\0'};
	char hitkey=0;
	
	system ("cls");
	
	{	
		if ((fp=fopen("reader.txt","r"))==NULL)//不存在读者文件，则输出不能还书
		{
			system ("cls");
			printf("\n 不存在借书者!按任意键退出!");
			getch();
			exit (0);
		}
		else
		{
			{			
				printf("\n请输入读者证号和书名:\n请输入:");	
				scanf("%d %s",&ttzhenghao,ttzname);//输入还书证号和书名
				k=duzhegs();//获取读者文件夹信息个数
				
				for (i=0;i<k;i++)//读取读者文件夹信息
				{
					fscanf(fp,"%d%s%s%s\n ",&tzhenghao,tmingzi,triqi,tzname);
					if((ttzhenghao==tzhenghao)&&!strcmp(ttzname,tzname))//如果证号书名存在，则标记为1
						flag=1;//strcmp:将两个字符串进行比较返回比较结果，相同返回0 
				}
				fclose(fp);
				
				fp=fopen("reader.txt","r");//打开读者文件
				if(flag)
				{	
					for (i=0;i<k;i++)//将读者文件复制到链表
					{
						fscanf(fp,"%d%s%s%s\n ",&tzhenghao,tmingzi,triqi,tzname);//读取文件信息	
						if(!((ttzhenghao==tzhenghao)&&!strcmp(ttzname,tzname)))
						{ 
							n++;
							if (n==1)
							{ 
								p1=p2=(struct reader*)malloc(LEN1);//新建链表开辟内存 
								head=p1;//head指向第一个节点 
							}
							else
							{ 
								p2->next=p1;
								p2=p1;
								p1=(struct reader*)malloc(LEN1);//新建链表
							}
							
							p1->zhenghao=tzhenghao;//复制证号
							strcpy(p1->mingzi,tmingzi);//复制读者名字						
							strcpy(p1->riqi,triqi);//复制日期						
							strcpy(p1->zname,tzname);//复制书名					
						}
					}
					
					if (n==0)
						head=NULL;
					else
					{
						p2->next=p1;				
						p1->next=NULL;					
						fclose(fp);				
					}
					
					fp=fopen("reader.txt","w");//清空读者文件
					fclose(fp);
					
					fp=fopen("reader.txt","a");//追加信息
					
					p=head;
					
					for (;p!=NULL;)//把链表内容覆盖读者文件			
					{				
						fprintf(fp,"\n%-8d%-23s%-18s%-10s\n",p->zhenghao,p->mingzi,p->riqi,p->zname);						
						p=p->next;					
					}
					
					free(p);				
					fclose(fp);				
				}
			}
		}
	}
	
	if(flag)//标记为1，即还书时
	{
		{
			{
				printf("确认还书请按回车!");
				
				for (;hitkey!=13&&hitkey!=27;)
					
					hitkey=getch();
				
				if (hitkey==13)
					printf("成功!按任意键返回!");
				
				n=0;flag=0;
				fp3=fopen("library.txt","r");//打开图书馆文件
				k=kucungs();//获取图书馆文件个数
				
				for (i=0;i<k;i++)//将图书馆文件复制到链表
				{					
					fscanf(fp3,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);//读取信息					
					n++;				
					if (n==1)				
					{ 
						lp1=lp2=(struct library*)malloc(LEN);//新建链表
						lhead1=lp1;
					}
					else
					{ 
						lp2->next=lp1;
						lp2=lp1;
						lp1=(struct library*)malloc(LEN);//新建链表
					}
					
					strcpy(lp1->shuhao,tshuhao);//复制书号				
					strcpy(lp1->name,tname);//复制书名			
					strcpy(lp1->author,tauthor);//复制作者					
					strcpy(lp1->chuban,tchuban);//复制出版社					
					strcpy(lp1->kind,tkind);//复制类别					
					lp1->xcl=txcl; //复制现存量					
					lp1->price=tprice;//复制单价					
				}
				
				if (n==0)
				{
					lhead1=NULL;
				}
				else				
				{				
					lp2->next=lp1;				
					lp1->next=NULL;	
					fclose(fp3);		
				}
			}
		}
		
		zp1=lhead1;		
		for (;zp1!=NULL;)
		{		
			if(!(strcmp(zp1->name,ttzname)))//寻找书名相同			
				++(zp1->xcl);//现存量加1			
			zp1=zp1->next;
		}
		
		fp3=fopen("library.txt","w");//清空图书馆文件
		fclose(fp);
		fp3=fopen("library.txt","a");//追加信息
		zp1=lhead1;
		
		for (;zp1!=NULL;)//把链表内容覆盖图书馆文件
		{
			fprintf(fp3,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",		
				zp1->shuhao,zp1->name,zp1->author,zp1->chuban,zp1->kind,zp1->xcl,zp1->price);		
			zp1=zp1->next;
		}
		
		fclose(fp3);
		getch();//返回
		jieshuxitong();//调用借阅系统
	}
	else
		printf("不存在此信息!按任意键返回!");
	
	getch();//返回
	jieshuxitong();//调用借阅系统
}


void duzhexinxi()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~显示读者借书情况函数
{
	FILE *fp;
	int zhenghao=0,xcl=0,n=0,i=0,j=0;
	char mingzi[20]={'\0'},riqi[20]={'\0'},zname[20]={'\0'};
	
	if ((fp=fopen("reader.txt","r"))==NULL)//打开读者文件夹
	{
		system ("cls");
		printf("\n记录文件不存在!");
	}
	n=duzhegs();
	
	if (n==0)
	{ 
		system ("cls");
		printf("\n无任何记录!");
	}
	
	fp=fopen("reader.txt","r");
	system ("cls");
	printf("\n证号\t读者姓名\t\t还书日期\t书名\n");
	
	for (i=0;i<n;i++)//输出文件信息
	{	
		fscanf(fp,"%d%s%s%s\n ",&zhenghao,mingzi,riqi,zname);	
		printf("\n%-8d%-23s%-18s%-10s\n", zhenghao,mingzi,riqi,zname);
	}
	
	fclose(fp);
	printf("\n按任意键返回\n");
	getch();//返回
	jieshuxitong();//调用借阅系统
}

void begin()
{
	char num;
	printf("\n\n\n\n					教师端登录请按 1 \n\n					学生端登录请按 2 \n\n");
	scanf("%c",&num);getchar();
}

int main()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~主函数调用
{
	system("color 3F");//蓝色背景白色字体 
	begin();
	main1();
	return 0;
}


