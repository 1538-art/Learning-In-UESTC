/*ͼ�����ϵͳ   �ռ�ȷ����*/ 

#include<stdio.h>
#include<stdlib.h>  //��system����
#include<conio.h>   //��ͨ������̨���������������������ĺ���
#include<string.h>  //���ַ�����
#include<math.h>
#define  LEN   sizeof(struct library)//�й�ͼ����Ϣ�Ľṹ��
#define  LEN1  sizeof(struct reader) //�йض�����Ϣ�Ľṹ��

struct library//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ͼ��ݽṹ��
{
	int xcl;//���
	float price;//����
	char name[20],author[20],chuban[20],kind[20],shuhao[20];
	struct library *next;
};


struct reader//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%���߽ṹ��
{
	int zhenghao;
	char mingzi[20],riqi[20],zname[20];
	struct reader *next;
};


void mainmenu()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~���˵�
{ 
	system ("cls");//�����Ļ��ǰ��ʾ������ ,�������У���stdlib.hͷ�ļ��У� 
	printf("\n\n\n				^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ");
	printf("\n\n\n						1.__���ͼ����Ϣ__\n\n");
	printf("\n\n 						2.__����ͼ��ϵͳ__\n\n");
	printf("\n\n 						3.__�˳�����ϵͳ__\n\n");
	//printf("\n\n 					 ^~^��������ѡ��and�س�ȷ��Ŷ~.~\n\n\n");
	printf(" 				^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ ^.^ \n");
}


void menu1() //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~��ʾ ͼ����Ϣ �˵�
{ 
	system ("cls");
	printf("\n\n\n				 ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ");
	printf("\n\n 				    		1.__ͼ�����__\n\n");
	printf("\n 						2.__ͼ������__\n\n");
	printf("\n 						3.__ͼ���ѯ__\n\n");
	printf("\n 						4.__������__\n\n");
	printf("\n 						5..������һ��..\n\n");
	//printf("\n 					^~^��������ѡ��and�س�ȷ��Ŷ*.*\n\n");
	printf(" 				 ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ ^~^ \n");
}


void menu2() //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~��ʾ ����ϵͳ �˵�
{ 
	system ("cls");
	printf("���������,����,���߻�����ѯ��\n");
	printf("��𣨿�ѧ���� ������ѧ ���ξ��� ��ʷ���� ��ʶ��̬ ������\n\n");
}


void main1()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~main1����
{
	void tsgxx();//���� ͼ�����Ϣ ���� 
	void jieshuxitong();//���� ����ϵͳ ����
	char choose;
	
	mainmenu();//��ʾ���˵� 
	scanf("%c",&choose);
	
	switch(choose)//���ܺ���ѡ��
	{ 
		case '1':	tsgxx();
		break;
		
		case '2':	jieshuxitong();	
		break;	
		
		case '3':   system ("cls");
		printf("\n\n\n  ɾ�������Ѿ��������� ^��^\n\n\n  �������ȫ�˳�Ŷ ^��^\n\n");
		exit(0);//exit�ر������ļ�����ֹ����ִ�еĳ���exit(0):�����˳�
		break;
	}
}


void tsgxx()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ͼ�����Ϣ����
{ 
	void tsjinku();//���� ͼ����� ���� 
	void shanchu();//���� ɾ��ͼ����Ϣ ���� 
	void chaxunts();//���� ��ѯͼ�� ���� 
	void kucunxinxi();//���� ��ʾ��� ���� 
	char choose;
	
	menu1();//��ʾ ͼ����Ϣ �˵� 
	getchar();//�̵�һ����ʾ��menu1������Ľ�����һ���Ļس�      
	
	scanf("%c",&choose);
	
	for (;;)//�ڷ�����һ��ǰѭ������                                                                                                                                                    //������ 
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
		case '5':	main1();//������һ�� 
		break;
	}
}


int kucungs()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ͳ�ƿ��ͼ���ı���������
{ 
	FILE *fp;//����һ��ָ�� 
	int txcl=0,n;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},tchuban[20]={'\0'},tkind[20]={'\0'},tshuhao[20]={'\0'};
	
	fp=fopen("library.txt","r");//���ļ�  fopen("�ļ���.�ļ�����"��"Ȩ��")�� 
	
	for (n=0;!feof(fp);n++)//������ļ�(feof(fp):����Ƿ��Լ���ȡ���ļ�β��,����β������1�����򷵻�0)
		fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);
	n--;
	
	fclose(fp);//�ر��ļ�
	return (n);//���ظ���
}


int duzhegs()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ͳ�ƶ����ı���������
{ 
	FILE *fp;
	int zhenghao=0,n;
	char mingzi[20]={'\0'},riqi[20]={'\0'},zname[20]={'\0'};
	
	fp=fopen("reader.txt","r");//���ļ�
	
	for (n=0;!feof(fp);n++)//������ļ�
		fscanf(fp,"%d%s%s%s ",&zhenghao,&mingzi,&riqi,&zname);
	
	fclose(fp);//�ر��ļ�
	return (n);//���ظ���
}


void tsjinku()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ͼ����⺯��
{ 
	FILE *fp;
	int xcl=0,n=0;
	float price=0;
	char name[20]={'\0'},author[20]={'\0'},kind[20]={'\0'},chuban[20]={'\0'},shuhao[20]={'\0'};
	char hitkey; 
	
	system ("cls");
	
	if ((fp=fopen("library.txt","a"))==NULL)//��ͼ����ļ��������ڴ��ļ����½�
	{ 
		fp=fopen("library.txt","w");
		fclose(fp);
	}
	
	fp=fopen("library.txt","a");//׷��д�򿪽���¼������ 
	
	printf("\n	����������Ҫ��ӵ�ͼ����Ϣ:\n\n	���	����	����	������	���	������	����");
	printf("\n\n	�����:��ѧ����ѧ����������������ѧ���̲ģ�С˵��������\n	����ţ�(XXX) ��\n"); 
	
	for (;hitkey!=27;)//�������һ�����ݺ����˻س�����ѭ������ 
	{ 
		if (n!=0)
			printf("������:\n");//�ӵڶ������뿪ʼ��ʾ������ 
		
		scanf("%s%s%s%s%s%d%f",shuhao,name,author,chuban,kind,&xcl,&price);		
		fprintf(fp,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",shuhao,name,author,chuban,kind,xcl,price);
		
		printf("���������밴�س�\n���������밴Esc\n");
		n++;
		
		hitkey=getch();//��¼�û������ļ�                                                                                                                                          		
		for (;hitkey!=13&&hitkey!=27;)//13��\r�س�  27��ESC�˳�                                                                                                                          
			hitkey=getch();//�û�������ظ��û� 
	}
	fclose(fp);
	
	printf("\n����ɹ����������������һ��!");
	getch();
	tsgxx();//������һ��
}


void shanchu()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ɾ��ͼ����Ϣ
{ 
	struct library *head=NULL;
	struct library *p,*p1,*p2;
	int txcl=0,n=0,j,i;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},tchuban[20]={'\0'},tkind[20]={'\0'},ttname[20]={'\0'},tshuhao[20]={'\0'};
	char hitkey;
	FILE *fp;
	
	if ((fp=fopen("library.txt","r"))==NULL)//���ļ�
	{ 
		system ("cls");
		
		printf("\n���ͼ��Ϊ��!�޷�ɾ��ͼ�飡\n�밴���������\n");
		getch();
		
		tsgxx();
	}
	else
	{ 
		system ("cls");
		
		printf("\n��������Ҫɾ��������:");//����ɾ��ͼ������
		scanf("%s",&ttname);
		
		printf("\nȷ��ɾ����س���ȡ���밴Esc\n");
		
		hitkey=getch();
		
		for(;hitkey!=13&&hitkey!=27;)
			hitkey=getch();
		
		if (hitkey==27)
			tsgxx();
		
		fp=fopen("library.txt","r");
		
		for (j=0;!feof(fp);)//���ļ�����Ϣ��ͳ���ڿ�ͼ�����
		{ 
			j++;
			fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);
		}
		
		fclose(fp);
		
		fp=fopen("library.txt","r");
		
		for (i=1;i<j;i++)
		{ 
			fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);
			
			if (strcmp(ttname,tname))//�Ƚ����֣�����ͬ���ֵ���Ϣ���Ƶ�����                                                                                     //������ 
			{ 
				n++;//��ͬ����ֵΪ0��ִ��if������ѭ������ͬ��ִ��ֱ�������в�ͬ����������������
				if (n==1)//��������
				{ 
					p1=p2=(struct library*)malloc(LEN);
					head=p1;
				}
				else
				{ 
					p2->next=p1;
					p2=p1;
					p1=(struct library*)malloc(LEN);//�½�����
				}
				
				strcpy(p1->shuhao,tshuhao);//�������
				strcpy(p1->name,tname);//��������
				strcpy(p1->author,tauthor);//������������
				strcpy(p1->chuban,tchuban);//���Ƴ�����
				strcpy(p1->kind,tkind);//�������
				p1->xcl=txcl;//���Ƹ���
				p1->price=tprice;//���Ƶ���
			}
		}
		
		if (n==0)//���ͼ��ֻ��һ������һ��պú�Ҫɾ������ͬ
		{ 
			head=NULL;
		}
		else//������������ʣ��һ������ռ䣬���Է��
		{
			p2->next=p1;
			p1->next=NULL;
			fclose(fp);
		}
	}
	
	fp=fopen("library.txt","w");//����ļ���ֻд�򿪣�Ȼ��ر�
	fclose(fp);
	
	fp=fopen("library.txt","a");//׷���ļ�
	p=head;
	
	for (;p!=NULL;)//���������ݸ��ǵ��ļ�
	{
		fprintf(fp,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",p->shuhao,p->name,p->author,p->chuban,p->kind,p->xcl,p->price);
		p=p->next;
	}
	
	fclose(fp);//�ر��ļ�
	system ("cls");
	
	printf("\nɾ���ɹ� \n�������������һ��\n");
	getch();//������һ��
	tsgxx();
}


void chaxunts()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~��ѯ����
{
	FILE *fp;
	char choose;
	int txcl=0,n=0,k=0,i,l;
	float tprice=0;
	char tname[20]={'\0'},tauthor[20]={'\0'},chazhao[20]={'\0'},tchuban[20]={'\0'},
	tshuhao[20]={'\0'},tkind[20]={'\0'};
	
	if ((fp=fopen("library.txt","r"))==NULL)//���ļ�
	{ 
		system ("cls");
		printf("\n��¼�ļ�������!�����������");
		getch();
		tsgxx();
	}
	
	l=kucungs();//��ÿ��ͼ�����
	menu2();//��ʾ����˵� 
	scanf("%s",chazhao);
	system ("cls");
	
	for (i=0;i<l;i++)
	{ 
		fscanf(fp,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);//���ļ���Ϣ
		if(!strcmp(chazhao,tshuhao)||!strcmp(chazhao,tname)||!strcmp(chazhao,tauthor)||!strcmp(chazhao,tkind))//�ڿ��ͼ������ģ������ 
		{
			if (k==0)
			{
				printf("��ѯ���:\n\n");
				printf("���\t����\t����\t\t������\t\t���\t\t�ִ���\t����\n");
			}
			printf("%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",tshuhao,tname,tauthor,tchuban,tkind,txcl,tprice);
			k++;
		}
	}
	
	if (k==0)//û���Ȿ�� 
	{ 
		system ("cls");
		printf("\n�޷��ϼ�¼!\n");
		getch();
		tsgxx();
	}
	
	fclose(fp);
	getch();//����
	tsgxx();
}


void kucunxinxi()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~��ʾ���ͼ����Ϣ
{
	FILE *fp;
	int xcl=0,n=0,i=0,j=0;
	float price=0;
	char name[20]={'\0'},author[20]={'\0'},kind[20]={'\0'},chuban[20]={'\0'},shuhao[20]={'\0'};
	
	if ((fp=fopen("library.txt","r"))==NULL)//���ļ���
	{
		system ("cls");
		printf("\n��¼�ļ�������!");
	}
	n= kucungs();
	
	if (n==0)
	{ 
		system ("cls");
		printf("\n���κμ�¼!");
	}
	
	fp=fopen("library.txt","r");//��ֻ���ļ�
	system ("cls");
	printf("���\t����\t����\t\t������\t\t���\t\t�����\t����\n");
	
	for (i=0;i<n;i++)//��������ڿ�ͼ����Ϣ
	{
		fscanf(fp,"%s%s%s%s%s%d%f",shuhao,name,author,chuban,kind,&xcl,&price);
		printf("%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",shuhao,name,author,chuban,kind,xcl,price);
	}
	
	fclose(fp);
	printf("\n�����������\n");
	getch();//����
	tsgxx();
}


void menu3() //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~��ʾ����ϵͳ���˵�
{
	system ("cls");
	
	printf("\n 				`~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` ");
	printf("\n\n						1.����Ǽ�\n\n");
	printf("\n\n						2.����Ǽ�\n\n");
	printf("\n\n						3.��������鿴\n\n");
	printf("\n\n						4.������һ��\n\n");
	//printf("\n\n					^~^�밴��ѡ��and�س�ȷ��Ŷ *��*\n");
	printf("\n 				`~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~` `~`\n ");	
	
	return ;
}


void jieshuxitong()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~����ϵͳ����
{ 
	void jieshu();
	void huanshu();
	void duzhexinxi();//��������
	char choose;
	
	menu3();
	getchar();//�̵�һ����ʾ��menu3������Ľ�����һ���Ļس� 
	
	scanf("%c",&choose);//ѡ����
	
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


void jieshu()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~���麯��
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
		if ((fp=fopen("library.txt","r"))==NULL)//��ͼ����ļ�
		{
			system ("cls");
			printf("\n ͼ����޿��!��������˳�!");
			getch();
			exit (0);
		}
		else
		{
			{
				printf("\n�������������:\n������:\n");//��������
				scanf("%s",zname);
				k= kucungs();//ͳ��ͼ����ļ�����
				for (i=0;i<k;i++)//����ͼ�����Ϣ���洢������
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
						p1=(struct library*)malloc(LEN);//�½�����
					}
					
					strcpy(p1->shuhao,tshuhao);//�������	
					strcpy(p1->name,tname);//��������
					strcpy(p1->author,tauthor);//��������
					strcpy(p1->chuban,tchuban);//���Ƴ�����
					strcpy(p1->kind,tkind);//�������
					p1->xcl=txcl;//�����ִ���
					p1->price=tprice;//���Ƶ���
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
		for (;p!=NULL;)//������
		{
			if(!(strcmp(p->name,zname)))//�ж�Ҫ������Ƿ����
			{
				flag=1;//���ȡ1
				loop=p->xcl;//�ִ�����1
				(p->xcl)--;
			}
			p=p->next;
		}
		
		if(flag&&(loop>0))//���ڽ����������ִ�������0���ѿ�����仯�����������ļ�
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
			free(p);//���������ݸ����ļ�
			fclose(fp);
		}
		
		if(flag&&(loop>0))//���ڽ����������ִ�������0
		{
			{
				if ((fp3=fopen("reader.txt","r"))==NULL)//�������ļ���
				{ 
					fp3=fopen("reader.txt","w");//��ֻ���ļ�
					fclose(fp3);			
				}			
				fp3=fopen("reader.txt","a");//�Ը��ӵķ�ʽ���ļ�		
			}
			
			{
				{
					if (n!=0)
						printf("\n�밴���¸�ʽ���������Ϣ:\n ֤�� ���� �黹���� ��������\n������:");//¼�������Ϣ
					
					scanf("%d %s %s %s",&zhenghao,&mingzi[20],&riqi[20],&zname[20]);
					fprintf(fp3,"\n%-8d%-23s%-18s%-10s\n",zhenghao,&mingzi[20],&riqi[20],&zname[20]);
					fp=fopen("library.txt","w");//ɾ��ͼ����ļ���Ϣ
					fclose(fp);
					fp=fopen("library.txt","a");//����׷����Ϣ
					p=head;
					
					for (;p!=NULL;)//���������ݸ���ͼ����ļ�
					{
						fprintf(fp,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",p->shuhao,p->name,p->author,p->chuban,p->kind,p->xcl,p->price);	
						p=p->next;
					}
					
					fclose(fp);
					fclose(fp3);
					printf("�ɹ�!�����������\n");
					getch();//����
					
					jieshuxitong();//���ý���ϵͳ
				}
			}
			jieshuxitong();//���ý���ϵͳ
		}
		else
			printf("�����ѱ�����!�����������!");//������������ѱ�����
		
		getch();//����		
		jieshuxitong();//���ý���ϵͳ
	}
}


void huanshu()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~���麯��
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
		if ((fp=fopen("reader.txt","r"))==NULL)//�����ڶ����ļ�����������ܻ���
		{
			system ("cls");
			printf("\n �����ڽ�����!��������˳�!");
			getch();
			exit (0);
		}
		else
		{
			{			
				printf("\n���������֤�ź�����:\n������:");	
				scanf("%d %s",&ttzhenghao,ttzname);//���뻹��֤�ź�����
				k=duzhegs();//��ȡ�����ļ�����Ϣ����
				
				for (i=0;i<k;i++)//��ȡ�����ļ�����Ϣ
				{
					fscanf(fp,"%d%s%s%s\n ",&tzhenghao,tmingzi,triqi,tzname);
					if((ttzhenghao==tzhenghao)&&!strcmp(ttzname,tzname))//���֤���������ڣ�����Ϊ1
						flag=1;//strcmp:�������ַ������бȽϷ��رȽϽ������ͬ����0 
				}
				fclose(fp);
				
				fp=fopen("reader.txt","r");//�򿪶����ļ�
				if(flag)
				{	
					for (i=0;i<k;i++)//�������ļ����Ƶ�����
					{
						fscanf(fp,"%d%s%s%s\n ",&tzhenghao,tmingzi,triqi,tzname);//��ȡ�ļ���Ϣ	
						if(!((ttzhenghao==tzhenghao)&&!strcmp(ttzname,tzname)))
						{ 
							n++;
							if (n==1)
							{ 
								p1=p2=(struct reader*)malloc(LEN1);//�½��������ڴ� 
								head=p1;//headָ���һ���ڵ� 
							}
							else
							{ 
								p2->next=p1;
								p2=p1;
								p1=(struct reader*)malloc(LEN1);//�½�����
							}
							
							p1->zhenghao=tzhenghao;//����֤��
							strcpy(p1->mingzi,tmingzi);//���ƶ�������						
							strcpy(p1->riqi,triqi);//��������						
							strcpy(p1->zname,tzname);//��������					
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
					
					fp=fopen("reader.txt","w");//��ն����ļ�
					fclose(fp);
					
					fp=fopen("reader.txt","a");//׷����Ϣ
					
					p=head;
					
					for (;p!=NULL;)//���������ݸ��Ƕ����ļ�			
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
	
	if(flag)//���Ϊ1��������ʱ
	{
		{
			{
				printf("ȷ�ϻ����밴�س�!");
				
				for (;hitkey!=13&&hitkey!=27;)
					
					hitkey=getch();
				
				if (hitkey==13)
					printf("�ɹ�!�����������!");
				
				n=0;flag=0;
				fp3=fopen("library.txt","r");//��ͼ����ļ�
				k=kucungs();//��ȡͼ����ļ�����
				
				for (i=0;i<k;i++)//��ͼ����ļ����Ƶ�����
				{					
					fscanf(fp3,"%s%s%s%s%s%d%f",tshuhao,tname,tauthor,tchuban,tkind,&txcl,&tprice);//��ȡ��Ϣ					
					n++;				
					if (n==1)				
					{ 
						lp1=lp2=(struct library*)malloc(LEN);//�½�����
						lhead1=lp1;
					}
					else
					{ 
						lp2->next=lp1;
						lp2=lp1;
						lp1=(struct library*)malloc(LEN);//�½�����
					}
					
					strcpy(lp1->shuhao,tshuhao);//�������				
					strcpy(lp1->name,tname);//��������			
					strcpy(lp1->author,tauthor);//��������					
					strcpy(lp1->chuban,tchuban);//���Ƴ�����					
					strcpy(lp1->kind,tkind);//�������					
					lp1->xcl=txcl; //�����ִ���					
					lp1->price=tprice;//���Ƶ���					
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
			if(!(strcmp(zp1->name,ttzname)))//Ѱ��������ͬ			
				++(zp1->xcl);//�ִ�����1			
			zp1=zp1->next;
		}
		
		fp3=fopen("library.txt","w");//���ͼ����ļ�
		fclose(fp);
		fp3=fopen("library.txt","a");//׷����Ϣ
		zp1=lhead1;
		
		for (;zp1!=NULL;)//���������ݸ���ͼ����ļ�
		{
			fprintf(fp3,"%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",		
				zp1->shuhao,zp1->name,zp1->author,zp1->chuban,zp1->kind,zp1->xcl,zp1->price);		
			zp1=zp1->next;
		}
		
		fclose(fp3);
		getch();//����
		jieshuxitong();//���ý���ϵͳ
	}
	else
		printf("�����ڴ���Ϣ!�����������!");
	
	getch();//����
	jieshuxitong();//���ý���ϵͳ
}


void duzhexinxi()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~��ʾ���߽����������
{
	FILE *fp;
	int zhenghao=0,xcl=0,n=0,i=0,j=0;
	char mingzi[20]={'\0'},riqi[20]={'\0'},zname[20]={'\0'};
	
	if ((fp=fopen("reader.txt","r"))==NULL)//�򿪶����ļ���
	{
		system ("cls");
		printf("\n��¼�ļ�������!");
	}
	n=duzhegs();
	
	if (n==0)
	{ 
		system ("cls");
		printf("\n���κμ�¼!");
	}
	
	fp=fopen("reader.txt","r");
	system ("cls");
	printf("\n֤��\t��������\t\t��������\t����\n");
	
	for (i=0;i<n;i++)//����ļ���Ϣ
	{	
		fscanf(fp,"%d%s%s%s\n ",&zhenghao,mingzi,riqi,zname);	
		printf("\n%-8d%-23s%-18s%-10s\n", zhenghao,mingzi,riqi,zname);
	}
	
	fclose(fp);
	printf("\n�����������\n");
	getch();//����
	jieshuxitong();//���ý���ϵͳ
}

void begin()
{
	char num;
	printf("\n\n\n\n					��ʦ�˵�¼�밴 1 \n\n					ѧ���˵�¼�밴 2 \n\n");
	scanf("%c",&num);getchar();
}

int main()//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~����������
{
	system("color 3F");//��ɫ������ɫ���� 
	begin();
	main1();
	return 0;
}


