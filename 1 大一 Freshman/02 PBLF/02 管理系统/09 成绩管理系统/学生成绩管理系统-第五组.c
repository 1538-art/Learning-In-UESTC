#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// ��������ڵ�


//���ѧ��,ѧ���ڵ� 
typedef struct _node
{
	char name[10];
	char student_id[14]; // ����ѧ��ѧ��,���ʮ��λ(�ο����ѧ��)
	float score;
	int number;//��¼�ڼ��γɼ� 
	struct _node *next;//����ָ��ѧ����ָ�� 
} Node;

//���ڴ����˺�����Ľڵ�
typedef struct _idnode {
	char student_id[14];//���ڴ���ѧ��ѧ�� 
	char code[13];//���ڴ����û����� 
	int data_id;//����ʶ���û����,1Ϊ��ʦ,0Ϊѧ�� 
	struct _idnode *nextId;
} idNode; 

//���巵����ҳ�溯��
void goBack(){
	printf("��������������ҳ��");
			getchar();
			getchar();
			int i=0;
			for(i=0;i<=10;i++){
			printf("\n");
			}
} 
//��Ⱦ����
 //��Ⱦ�˺�
 void renderA(idNode *headId){
 	//������Ⱦ
		 	FILE*pAcountNew;
		 	
			pAcountNew= fopen("accountAndCode.txt","w");
 		idNode *tpNow=(idNode*)malloc(sizeof(idNode));
			for(tpNow->nextId=headId->nextId;tpNow;){
				tpNow=tpNow->nextId;
				if(tpNow){
				fprintf(pAcountNew,"%s ",tpNow->student_id);
				fprintf(pAcountNew,"%s ",tpNow->code);
				fprintf(pAcountNew,"%d\n",tpNow->data_id);
				}
				
			} 
			free(tpNow);
			fclose(pAcountNew);
 } 
 //��Ⱦ�ɼ�
 void renderS(Node *head){
 	//������Ⱦ
		 	FILE*pScoreNew;
			pScoreNew= fopen("score.txt","w"); 
 		Node *tpNow=(Node*)malloc(sizeof(Node));
			for(tpNow->next=head->next;tpNow;){
				tpNow=tpNow->next;
				if(tpNow){
				fprintf(pScoreNew,"%s ",tpNow->name);
				fprintf(pScoreNew,"%s ",tpNow->student_id);
				fprintf(pScoreNew,"%.2f ",tpNow->score);
				fprintf(pScoreNew,"%d\n",tpNow->number);
				}
			} 
			free(tpNow);
			fclose(pScoreNew);
 } 
int main()
{	
	 
	//��ʼ������
	
	//��ʼ������

	//��ʼ���˺�����
	 idNode* headId=(idNode*)malloc(sizeof(idNode));
	 headId->nextId=NULL;
	//��ʼ���˺�
	 FILE *fpaccount;
	 fpaccount=fopen("accountAndCode.txt","r"); 
	while(1){
	 	idNode* pId=(idNode*)malloc(sizeof(idNode));
	 	pId->nextId=NULL;
	 	fscanf(fpaccount,"%s",pId->student_id);
	  	fscanf(fpaccount,"%s",pId->code);
	  	fscanf(fpaccount,"%d ",&pId->data_id);
	  	idNode* lastId=(idNode*)malloc(sizeof(idNode));
	  	lastId->nextId=headId;
	  	while(lastId->nextId){
	  		lastId=lastId->nextId;
		  }
		  lastId->nextId=pId;
	  	if(feof(fpaccount)){
		  	break;
		  }
}
	//��ʼ���ɼ����� 
	 Node* head=(Node*)malloc(sizeof(Node));
	 head->next=NULL;
	
	  //��ʼ���ɼ�
	  	FILE *fp;
		fp=fopen("score.txt","r");
		while(1){
	   	Node* p=(Node*)malloc(sizeof(Node));
	   	p->next=NULL;	
	   	if(feof(fp)){
		  	break;
		  }
	 	fscanf(fp,"%s",p->name);
	  	fscanf(fp,"%s",p->student_id);
	  	fscanf(fp,"%f ",&p->score);
	  	fscanf(fp,"%d",&p->number);
	  	Node* last=(Node*)malloc(sizeof(Node));
	  	last->next=head;
	  	while(last->next){
	  		last=last->next;
		  }
		  last->next=p;
		  p->next=NULL;
		  
		
}
	//�û���¼����
	int codeReal=0;
	int op=0;
	printf("���������ѧ�Ż��ʦ�˺�\n");
	char _account[13];
	scanf("%s",_account);
	printf("�������������(ps:ѧ����ʼ����Ϊ123456)\n");
	char _code[12];
	scanf("%s",_code);
	 //�����˺�����
	 idNode*pNowId=(idNode*)malloc(sizeof(idNode));
	 pNowId->nextId=NULL;
	  for(pNowId->nextId=headId->nextId;pNowId;){
	  	pNowId=pNowId->nextId;
	  		if(pNowId){
				if(!strcmp(pNowId->student_id,_account)){
					op=1;
					if(!strcmp(pNowId->code,_code)) {
						codeReal=1;
					}
					break;
				}
			}
	  }
	if(op==0){
				printf("δ���ҵ����û�\n");
				return 0;
			}
	if(codeReal==0){
			printf("�������\n");
			return 0;
	}else{
		//������ȷ,�ж������Ϣ 
		//ѧ��ϵͳ 
	if(pNowId->data_id==0){
		//������ȡѧ������ 
		 Node*pNow=(Node*)malloc(sizeof(Node));
	 pNow->next=NULL;
	  for(pNow->next=head->next;pNow;){
	  	pNow=pNow->next;
	  		if(pNow){
				if(!strcmp(pNow->student_id,_account)){
					break;
				}
			}
	  }
	  //��ӭ�� 
	  printf("��ӭ�����ѧ���ɼ�ϵͳ,%s\n",pNow->name);
	  //ѧ������ 
	  while(1){
	  printf("���������ֽ��в���\n");
	  printf("1:��ѯ�ɼ�\n");
	  printf("2:�˳�ϵͳ\n");
	  printf("3:�޸�����\n");
	  int num =0;
	  scanf("%d",&num);
	  if(num==3){
			//����
				idNode* pId=(idNode*)malloc(sizeof(idNode));
	 			pId->nextId=NULL;
			for(pId->nextId=headId->nextId;pId;){
				pId=pId->nextId;
				//ƥ��ѧ����Ϣ������� 
				if(pId){
				if(!strcmp(pId->student_id,_account)){
					printf("��������Ϊ:%s\n",pId->code);
					printf("�������޸ĺ������\n");
					scanf("%s",pId->code); 
					//������Ⱦ 
					renderA(headId);
				}
			}
		}
		printf("�����������ؽ���");
		getchar();
		getchar();
	  }
	if(num==2){
		return 0;
	}
	if(num==1){
			//x->�ڼ��ο��ԣ�y->�ɼ� 
			float xS=0;
			float yS=0;
			int cnt =0;
			float xy=0;
			float x2=0;//xi��ƽ�� 
			float y2=0;//yi��ƽ�� 
			//����
			Node *tpNow=(Node*)malloc(sizeof(Node));
			int op=0;
			for(tpNow->next=head->next;tpNow;){
				tpNow=tpNow->next;
				//ƥ��ѧ����Ϣ������� 
				if(tpNow){
				if(!strcmp(pNow->student_id,tpNow->student_id)){
					cnt++;
					yS+=tpNow->score;
					xS+=tpNow->number;
					xy+=tpNow->number*tpNow->score;
					x2+=tpNow->number*tpNow->number;
					y2+=tpNow->score*tpNow->score;
					printf("������%s\t",tpNow->name);
					printf("ѧ��:%s\t",tpNow->student_id);
					printf("�ɼ�:%.2f\t\n",tpNow->score);
					
				}
			}
		}
		//����ع鷽��б�� 
		float d=0;
		d=(xy-yS*xS/cnt)/((x2-cnt*(xS/cnt)*(xS/cnt)));
		//����ع鷽�̽ؾ�
		float a=0;
		a=yS/cnt-d*xS/cnt;
		if(d>0){
			printf("��ĳɼ����������ƣ����ٽ�����\n");
			printf("�������������ִ��ٶȽ���,��ô����һ�ο��Եĳɼ������ܵ���:%.2f\n",(a+d*(cnt+1)));
		}else{
			printf("��ĳɼ����½����ƣ�����\n"); 
			printf("����������,��ô����һ�εĳɼ������ܵ���:%.2f",(a+d*(cnt+1)));
		}
	  	printf("���������������������");
	  	getchar();
	  	getchar();
	}
	  }
	}
	//��ʦϵͳ 
	if(pNowId->data_id==1){
		//��ӭ��
		printf("��ӭ�����ʦϵͳ");
		 	while(1){
		int i=0;
			for(i=0;i<=10;i++){
			printf("\n");
			}
		printf("���������ֽ��в���\n");
		printf("0:�˳�����\n");
		printf("1:ѧ���ɼ���Ϣ����\n");
		printf("2:ѧ���ɼ���ѯ\n");
		printf("3:�ɼ��޸�\n");
		printf("4:�ɼ�ɾ��\n");
		printf("5:��ʾѧ���ɼ�\n");
		printf("6:�ɼ�ƽ����\n");
		printf("7:�ɼ���������\n");
			printf("8:�޸�����\n");
			for(i=0;i<=10;i++){
			printf("\n");
			}
		int num;
		scanf("%d", &num);
	

		
		//0:�˳����� 
		if (num == 0)
		{
			return 0;
		}
		
		
		
		
		
		
		//ѧ���ɼ���Ϣ���� 
		else if (num == 1)
		{
		//����׷���ļ� 
		//׷�ӳɼ�
		 	FILE*pScore;
			pScore=fopen("score.txt","a"); 
		//׷���˺� 
			FILE*pA;
			pA=fopen("accountAndCode.txt","a"); 
		
			//�����ڵ�
			Node *p = (Node *)malloc(sizeof(Node));
			//¼������
			printf("������ѧ������\n");
			scanf("%s",p->name);
			fprintf(pScore,"\n%s ",p->name);
			//¼��ѧ��
			printf("������ѧ��ѧ��\n");
			scanf("%s",&p->student_id);
			fprintf(pScore,"%s ",p->student_id);
			//�жϸ�ѧ���Ƿ����˺�
		
			op=0;
			idNode*pNowId=(idNode*)malloc(sizeof(idNode));
	 			pNowId->nextId=NULL;
	  			for(pNowId->nextId=headId;pNowId;){
	  				pNowId=pNowId->nextId;
	  				if(pNowId){
					if(!strcmp(pNowId->student_id,p->student_id)){
					op=1;
					break;
				}
			}
	  } 
			//����,ע��
			 	if(op==0){
			 		fprintf(pA,"\n%s ",p->student_id);
			 		fprintf(pA,"%s ","123456");
			 		fprintf(pA,"0");
				 }
				
			//¼��ɼ�
			printf("������ѧ���ɼ�\n");
			scanf("%f",&p->score);
			fprintf(pScore,"%.2f ",p->score);
			 //¼�����ǵڼ��γɼ�
				 //���� 
				 	//������ 
					int cnt =0;
				  	Node *pNow=(Node*)malloc(sizeof(Node));
						int op=0;
						for(pNow->next=head->next;pNow;){
						pNow=pNow->next;
			//��������ж��Ƿ���ѧ����Ϣ 
				//ƥ��ѧ����Ϣ������� 
				if(pNow){
				if(!strcmp(pNow->student_id,p->student_id)){
					cnt++;
				}
			}
		}
		fprintf(pScore,"%d",cnt+1);
			//��������
			Node* last=(Node*)malloc(sizeof(Node));
			last->next=head;
			while (last->next)
			{
				last=last->next;
			}
			//ƴ��
			last->next=p;
			last=last->next;
			p->next=NULL;
			printf("����ɹ�\n");
		goBack();
		
		}
		
		
		
		
		
		
		//ѧ���ɼ���ѯ 
		else if (num==2){
			//����ѧ��ѧ�� 
			printf("������ѧ��ѧ��\n");
			char id[13] ="0";
			scanf("%s",id);
			printf("�������ѯ�ڼ��ο��Գɼ�\n");
			//������� 
			int num=0;
			scanf("%d",&num);
			//��ʱ�� 
			int cnt =0;
		
			 
			//����
			Node *pNow=(Node*)malloc(sizeof(Node));
			int op=0;
			for(pNow->next=head->next;pNow;){
				pNow=pNow->next;
			//��������ж��Ƿ���ѧ����Ϣ 
				//ƥ��ѧ����Ϣ������� 
				if(pNow){
				if(!strcmp(pNow->student_id,id)){
					cnt++;
					if(cnt==num){
							op=1;
					
							
							printf("������%s\t",pNow->name);
							printf("ѧ��:%s\t",pNow->student_id);
							printf("�ɼ�:%.2f\t\n",pNow->score);
					}
				}
			}
		}
			//�ж��Ƿ���ѧ����Ϣ 
			if(op==0){
				printf("δ���ҵ���ѧ��\n");
		}
			goBack();
		}
		
		
		
		
		
		
		//ѧ���ɼ��޸� 
		else if(num==3){
				//����ѧ��ѧ�� 
			printf("������ѧ��ѧ��\n");
			char id[13] ="0";
			scanf("%s",id);
				printf("�������޸ĵڼ��ο��Գɼ�\n");
			//������� 
			int num=0;
			scanf("%d",&num);
			//��ʱ�� 
			int cnt =0;
			//����
			Node *pNow=(Node*)malloc(sizeof(Node));
			int op=0;
			for(pNow->next=head->next;pNow;){
				pNow=pNow->next;
			//��������ж��Ƿ���ѧ����Ϣ 
				//ƥ��ѧ����Ϣ������� 
				if(pNow){
				if(!strcmp(pNow->student_id,id)){
					cnt++;
					if(cnt==num){
					
					printf("������%s\t",pNow->name);
					printf("ѧ��:%s\t",pNow->student_id);
					printf("�ɼ�:%.2f\t\n",pNow->score);
					op=1;
					printf("������ѧ���޸ĺ�ɼ�\n");
					float _score=0;
					scanf("%f",&_score);
					pNow->score=_score;
					printf("�޸ĺ����ϢΪ��"); 
					printf("������%s\t",pNow->name);
					printf("ѧ��:%s\t",pNow->student_id);
					printf("�ɼ�:%.2f\t\n",pNow->score);
						//������Ⱦ
					renderS(head);
					break;
					}
				}
			}
		}
	
			//�ж��Ƿ���ѧ����Ϣ 
			if(op==0){
				printf("δ���ҵ���ѧ��\n");
			}
			
			goBack();
		}
		
		
		
		
		
		//ɾ��ѧ���ɼ� 
		else if(num==4){
			//�������б���ָ�� 
			Node*pNow1=(Node*)malloc(sizeof(Node));
			//������б���ָ��
			 Node*pNow2=(Node*)malloc(sizeof(Node));
			 printf("��������Ҫɾ����ѧ��ѧ��\n");
			 char id[13] ="0";
			scanf("%s",id);
			int op =0;
				printf("������ɾ���ڼ��ο��Գɼ�\n");
			//������� 
			int num=0;
			scanf("%d",&num);
			//��ʱ�� 
			int cnt =0;
			//���� 
				for(pNow1->next=head->next,pNow2->next=head;pNow1;){
				pNow1=pNow1->next;
				pNow2=pNow2->next;
			//��������ж��Ƿ���ѧ����Ϣ 
				//ƥ��ѧ����Ϣ
				if(pNow1){
				if(!strcmp(pNow1->student_id,id)){
					cnt++;
					pNow1->number+=1;
					if(cnt==num){
					
					printf("��ȷ���Ƿ�ɾ��������Ϣ,ȷ��������1,ȡ�����������������:\n");
					printf("������%s\t",pNow1->name);
					printf("ѧ��:%s\t",pNow1->student_id);
					printf("�ɼ�:%.2f\t\n",pNow1->score);
					int i=0;
					scanf("%d",&i);
					if(i==1){
						pNow2->next=pNow1->next;
						pNow1->next=NULL;
						free(pNow1);
							//������Ⱦ
						//�����ı�ڼ���
							//����
							Node *pNow=(Node*)malloc(sizeof(Node));
							int op=0;
							for(pNow->next=head->next;pNow;){
							pNow=pNow->next;
							//ƥ��ѧ����Ϣ������� 
							if(pNow){
							if(!strcmp(pNow->student_id,id)){
							pNow->number-=1;
				}
			}
		} 
							renderS(head);
						printf("ɾ���ɹ�");
					}
					op=1;
					break;
					}
				}
			}
		}
		
			//�ж��Ƿ���ѧ����Ϣ 
			if(op==0){
				printf("δ���ҵ���ѧ��\n");
			}
			
			goBack();
		}
		
		
		
		
		
		//��ʾѧ���ɼ� 
		else if(num==5){
				Node *pNow=(Node*)malloc(sizeof(Node));
			for(pNow->next=head->next;pNow;){
				pNow=pNow->next;
				if(pNow&&pNow->number<100){
				printf("������%s\t",pNow->name);
				printf("ѧ��:%s\t",pNow->student_id);
				printf("�ɼ�:%.2f\t\n",pNow->score);
				}
				
			}
			goBack();
		}
		//��ʾƽ����
		else if(num==6){
			printf("������鿴�ڼ��ο��Ե�ƽ����\n"); 
			int num =0;
			scanf("%d",&num);
			float average=0;           
			int number=0;
				Node *pNow=(Node*)malloc(sizeof(Node));
			for(pNow->next=head->next;pNow;){
				pNow=pNow->next;
				if(pNow&&pNow->number==num){
				average+=pNow->score;
				number++;
				}
			}
			printf("ƽ����Ϊ%.2f\n",average/number);
			goBack();
		}
		//�ɼ����� 
		else if(num==7){
				printf("������鿴�ڼ��ο��Եĳɼ�����\n"); 
				int num =0;
				scanf("%d",&num);
				//����ṹ��
				typedef struct {
					char name[10];
					float grade;
				} Student; 
				//��������
				Student students[50];
				//��ʼ��
				int i =0; 
				int j=0;
					for(i=0;i<49;i++){
						strcpy(students[i].name,"xxx");
						students[i].grade=0;
					}
						Node *pNow=(Node*)malloc(sizeof(Node));
						for(pNow->next=head->next,i=0;pNow;++i){
						pNow=pNow->next;
						if(pNow&&pNow->number==num){
						//����¼������
						strcpy(students[i].name,pNow->name);
						students[i].grade=pNow->score;		 
				}
			}
						//�����м����
						float t1=0;
						char t2[10]; 
						//ð������
						for(i=0;i<49;i++){
							for(j=0;j<49;j++){
								if(students[j].grade<students[j+1].grade){
									t1=students[j].grade;
									strcpy(t2,students[j].name);
									students[j].grade=students[j+1].grade;
									strcpy(students[j].name,students[j+1].name);
									students[j+1].grade=t1;
									strcpy(students[j+1].name,t2);
								}
							}
						} 
						//�������ǰ20����
						for(i=0;i<20;i++){
							printf("��%d��Ϊ��%s,����Ϊ��%.2f\n",i+1,students[i].name,students[i].grade);
						} 
						printf("�������������������");
						getchar();
						getchar();
		}
		
		
		//�޸����� 
		else if(num==8){
			printf("�������޸ĺ������,���12λ\n");
			 char codeT[13];
			 scanf("%s",codeT);
			  idNode*pNowId=(idNode*)malloc(sizeof(idNode));
			  pNowId=headId->nextId;
			  strcpy(pNowId->code,codeT);
			  renderA(headId);
			  printf("�޸ĳɹ�");
			  printf("�����������");
			  getchar();
			  getchar();
		}
		
		
		
		
		
	}
	}
}
	return 0;
}

