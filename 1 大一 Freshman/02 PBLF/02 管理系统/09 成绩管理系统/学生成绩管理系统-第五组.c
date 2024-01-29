#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// 定义链表节点


//多个学生,学生节点 
typedef struct _node
{
	char name[10];
	char student_id[14]; // 定义学生学号,最大十三位(参考你电学号)
	float score;
	int number;//记录第几次成绩 
	struct _node *next;//用于指向学生的指针 
} Node;

//用于储存账号密码的节点
typedef struct _idnode {
	char student_id[14];//用于储存学生学号 
	char code[13];//用于储存用户密码 
	int data_id;//用于识别用户身份,1为老师,0为学生 
	struct _idnode *nextId;
} idNode; 

//定义返回主页面函数
void goBack(){
	printf("点击任意键返回主页面");
			getchar();
			getchar();
			int i=0;
			for(i=0;i<=10;i++){
			printf("\n");
			}
} 
//渲染函数
 //渲染账号
 void renderA(idNode *headId){
 	//重新渲染
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
 //渲染成绩
 void renderS(Node *head){
 	//重新渲染
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
	 
	//初始化数据
	
	//初始化链表

	//初始化账号链表
	 idNode* headId=(idNode*)malloc(sizeof(idNode));
	 headId->nextId=NULL;
	//初始化账号
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
	//初始化成绩链表 
	 Node* head=(Node*)malloc(sizeof(Node));
	 head->next=NULL;
	
	  //初始化成绩
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
	//用户登录界面
	int codeReal=0;
	int op=0;
	printf("请输入你的学号或教师账号\n");
	char _account[13];
	scanf("%s",_account);
	printf("请输入你的密码(ps:学生初始密码为123456)\n");
	char _code[12];
	scanf("%s",_code);
	 //遍历账号链表
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
				printf("未查找到该用户\n");
				return 0;
			}
	if(codeReal==0){
			printf("密码错误\n");
			return 0;
	}else{
		//密码正确,判断身份信息 
		//学生系统 
	if(pNowId->data_id==0){
		//遍历获取学生名字 
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
	  //欢迎语 
	  printf("欢迎你进入学生成绩系统,%s\n",pNow->name);
	  //学生操作 
	  while(1){
	  printf("请输入数字进行操作\n");
	  printf("1:查询成绩\n");
	  printf("2:退出系统\n");
	  printf("3:修改密码\n");
	  int num =0;
	  scanf("%d",&num);
	  if(num==3){
			//遍历
				idNode* pId=(idNode*)malloc(sizeof(idNode));
	 			pId->nextId=NULL;
			for(pId->nextId=headId->nextId;pId;){
				pId=pId->nextId;
				//匹配学生信息进行输出 
				if(pId){
				if(!strcmp(pId->student_id,_account)){
					printf("您的密码为:%s\n",pId->code);
					printf("请输入修改后的密码\n");
					scanf("%s",pId->code); 
					//重新渲染 
					renderA(headId);
				}
			}
		}
		printf("点击任意键返回界面");
		getchar();
		getchar();
	  }
	if(num==2){
		return 0;
	}
	if(num==1){
			//x->第几次考试，y->成绩 
			float xS=0;
			float yS=0;
			int cnt =0;
			float xy=0;
			float x2=0;//xi的平方 
			float y2=0;//yi的平方 
			//遍历
			Node *tpNow=(Node*)malloc(sizeof(Node));
			int op=0;
			for(tpNow->next=head->next;tpNow;){
				tpNow=tpNow->next;
				//匹配学生信息进行输出 
				if(tpNow){
				if(!strcmp(pNow->student_id,tpNow->student_id)){
					cnt++;
					yS+=tpNow->score;
					xS+=tpNow->number;
					xy+=tpNow->number*tpNow->score;
					x2+=tpNow->number*tpNow->number;
					y2+=tpNow->score*tpNow->score;
					printf("姓名：%s\t",tpNow->name);
					printf("学号:%s\t",tpNow->student_id);
					printf("成绩:%.2f\t\n",tpNow->score);
					
				}
			}
		}
		//定义回归方程斜率 
		float d=0;
		d=(xy-yS*xS/cnt)/((x2-cnt*(xS/cnt)*(xS/cnt)));
		//定义回归方程截距
		float a=0;
		a=yS/cnt-d*xS/cnt;
		if(d>0){
			printf("你的成绩呈增长趋势，请再接再厉\n");
			printf("如果你想继续保持此速度进步,那么你下一次考试的成绩将不能低于:%.2f\n",(a+d*(cnt+1)));
		}else{
			printf("你的成绩呈下降趋势，加油\n"); 
			printf("如果你想进步,那么你下一次的成绩将不能低于:%.2f",(a+d*(cnt+1)));
		}
	  	printf("请输入任意键返回主界面");
	  	getchar();
	  	getchar();
	}
	  }
	}
	//教师系统 
	if(pNowId->data_id==1){
		//欢迎语
		printf("欢迎进入教师系统");
		 	while(1){
		int i=0;
			for(i=0;i<=10;i++){
			printf("\n");
			}
		printf("请输入数字进行操作\n");
		printf("0:退出程序\n");
		printf("1:学生成绩信息输入\n");
		printf("2:学生成绩查询\n");
		printf("3:成绩修改\n");
		printf("4:成绩删除\n");
		printf("5:显示学生成绩\n");
		printf("6:成绩平均分\n");
		printf("7:成绩排名分析\n");
			printf("8:修改密码\n");
			for(i=0;i<=10;i++){
			printf("\n");
			}
		int num;
		scanf("%d", &num);
	

		
		//0:退出程序 
		if (num == 0)
		{
			return 0;
		}
		
		
		
		
		
		
		//学生成绩信息输入 
		else if (num == 1)
		{
		//定义追加文件 
		//追加成绩
		 	FILE*pScore;
			pScore=fopen("score.txt","a"); 
		//追加账号 
			FILE*pA;
			pA=fopen("accountAndCode.txt","a"); 
		
			//新增节点
			Node *p = (Node *)malloc(sizeof(Node));
			//录入姓名
			printf("请输入学生姓名\n");
			scanf("%s",p->name);
			fprintf(pScore,"\n%s ",p->name);
			//录入学号
			printf("请输入学生学号\n");
			scanf("%s",&p->student_id);
			fprintf(pScore,"%s ",p->student_id);
			//判断该学生是否有账号
		
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
			//若无,注册
			 	if(op==0){
			 		fprintf(pA,"\n%s ",p->student_id);
			 		fprintf(pA,"%s ","123456");
			 		fprintf(pA,"0");
				 }
				
			//录入成绩
			printf("请输入学生成绩\n");
			scanf("%f",&p->score);
			fprintf(pScore,"%.2f ",p->score);
			 //录入这是第几次成绩
				 //遍历 
				 	//计数器 
					int cnt =0;
				  	Node *pNow=(Node*)malloc(sizeof(Node));
						int op=0;
						for(pNow->next=head->next;pNow;){
						pNow=pNow->next;
			//定义变量判断是否有学生信息 
				//匹配学生信息进行输出 
				if(pNow){
				if(!strcmp(pNow->student_id,p->student_id)){
					cnt++;
				}
			}
		}
		fprintf(pScore,"%d",cnt+1);
			//遍历链表
			Node* last=(Node*)malloc(sizeof(Node));
			last->next=head;
			while (last->next)
			{
				last=last->next;
			}
			//拼接
			last->next=p;
			last=last->next;
			p->next=NULL;
			printf("保存成功\n");
		goBack();
		
		}
		
		
		
		
		
		
		//学生成绩查询 
		else if (num==2){
			//输入学生学号 
			printf("请输入学生学号\n");
			char id[13] ="0";
			scanf("%s",id);
			printf("请输入查询第几次考试成绩\n");
			//定义次数 
			int num=0;
			scanf("%d",&num);
			//计时器 
			int cnt =0;
		
			 
			//遍历
			Node *pNow=(Node*)malloc(sizeof(Node));
			int op=0;
			for(pNow->next=head->next;pNow;){
				pNow=pNow->next;
			//定义变量判断是否有学生信息 
				//匹配学生信息进行输出 
				if(pNow){
				if(!strcmp(pNow->student_id,id)){
					cnt++;
					if(cnt==num){
							op=1;
					
							
							printf("姓名：%s\t",pNow->name);
							printf("学号:%s\t",pNow->student_id);
							printf("成绩:%.2f\t\n",pNow->score);
					}
				}
			}
		}
			//判断是否有学生信息 
			if(op==0){
				printf("未查找到该学生\n");
		}
			goBack();
		}
		
		
		
		
		
		
		//学生成绩修改 
		else if(num==3){
				//输入学生学号 
			printf("请输入学生学号\n");
			char id[13] ="0";
			scanf("%s",id);
				printf("请输入修改第几次考试成绩\n");
			//定义次数 
			int num=0;
			scanf("%d",&num);
			//计时器 
			int cnt =0;
			//遍历
			Node *pNow=(Node*)malloc(sizeof(Node));
			int op=0;
			for(pNow->next=head->next;pNow;){
				pNow=pNow->next;
			//定义变量判断是否有学生信息 
				//匹配学生信息进行输出 
				if(pNow){
				if(!strcmp(pNow->student_id,id)){
					cnt++;
					if(cnt==num){
					
					printf("姓名：%s\t",pNow->name);
					printf("学号:%s\t",pNow->student_id);
					printf("成绩:%.2f\t\n",pNow->score);
					op=1;
					printf("请输入学生修改后成绩\n");
					float _score=0;
					scanf("%f",&_score);
					pNow->score=_score;
					printf("修改后的信息为："); 
					printf("姓名：%s\t",pNow->name);
					printf("学号:%s\t",pNow->student_id);
					printf("成绩:%.2f\t\n",pNow->score);
						//重新渲染
					renderS(head);
					break;
					}
				}
			}
		}
	
			//判断是否有学生信息 
			if(op==0){
				printf("未查找到该学生\n");
			}
			
			goBack();
		}
		
		
		
		
		
		//删除学生成绩 
		else if(num==4){
			//定义先行遍历指针 
			Node*pNow1=(Node*)malloc(sizeof(Node));
			//定义后行遍历指针
			 Node*pNow2=(Node*)malloc(sizeof(Node));
			 printf("请输入想要删除的学生学号\n");
			 char id[13] ="0";
			scanf("%s",id);
			int op =0;
				printf("请输入删除第几次考试成绩\n");
			//定义次数 
			int num=0;
			scanf("%d",&num);
			//计时器 
			int cnt =0;
			//遍历 
				for(pNow1->next=head->next,pNow2->next=head;pNow1;){
				pNow1=pNow1->next;
				pNow2=pNow2->next;
			//定义变量判断是否有学生信息 
				//匹配学生信息
				if(pNow1){
				if(!strcmp(pNow1->student_id,id)){
					cnt++;
					pNow1->number+=1;
					if(cnt==num){
					
					printf("请确认是否删除以下信息,确认请输入1,取消请输入其他任意键:\n");
					printf("姓名：%s\t",pNow1->name);
					printf("学号:%s\t",pNow1->student_id);
					printf("成绩:%.2f\t\n",pNow1->score);
					int i=0;
					scanf("%d",&i);
					if(i==1){
						pNow2->next=pNow1->next;
						pNow1->next=NULL;
						free(pNow1);
							//重新渲染
						//遍历改变第几次
							//遍历
							Node *pNow=(Node*)malloc(sizeof(Node));
							int op=0;
							for(pNow->next=head->next;pNow;){
							pNow=pNow->next;
							//匹配学生信息进行输出 
							if(pNow){
							if(!strcmp(pNow->student_id,id)){
							pNow->number-=1;
				}
			}
		} 
							renderS(head);
						printf("删除成功");
					}
					op=1;
					break;
					}
				}
			}
		}
		
			//判断是否有学生信息 
			if(op==0){
				printf("未查找到该学生\n");
			}
			
			goBack();
		}
		
		
		
		
		
		//显示学生成绩 
		else if(num==5){
				Node *pNow=(Node*)malloc(sizeof(Node));
			for(pNow->next=head->next;pNow;){
				pNow=pNow->next;
				if(pNow&&pNow->number<100){
				printf("姓名：%s\t",pNow->name);
				printf("学号:%s\t",pNow->student_id);
				printf("成绩:%.2f\t\n",pNow->score);
				}
				
			}
			goBack();
		}
		//显示平均分
		else if(num==6){
			printf("请输入查看第几次考试的平均分\n"); 
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
			printf("平均分为%.2f\n",average/number);
			goBack();
		}
		//成绩分析 
		else if(num==7){
				printf("请输入查看第几次考试的成绩分析\n"); 
				int num =0;
				scanf("%d",&num);
				//定义结构体
				typedef struct {
					char name[10];
					float grade;
				} Student; 
				//定义数组
				Student students[50];
				//初始化
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
						//遍历录入数据
						strcpy(students[i].name,pNow->name);
						students[i].grade=pNow->score;		 
				}
			}
						//定义中间变量
						float t1=0;
						char t2[10]; 
						//冒泡排序法
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
						//遍历输出前20排名
						for(i=0;i<20;i++){
							printf("第%d名为：%s,分数为：%.2f\n",i+1,students[i].name,students[i].grade);
						} 
						printf("输入任意键返回主界面");
						getchar();
						getchar();
		}
		
		
		//修改密码 
		else if(num==8){
			printf("请输入修改后的密码,最大12位\n");
			 char codeT[13];
			 scanf("%s",codeT);
			  idNode*pNowId=(idNode*)malloc(sizeof(idNode));
			  pNowId=headId->nextId;
			  strcpy(pNowId->code,codeT);
			  renderA(headId);
			  printf("修改成功");
			  printf("按任意键返回");
			  getchar();
			  getchar();
		}
		
		
		
		
		
	}
	}
}
	return 0;
}

