#include<stdio.h>
#include<string.h>
#include<math.h>
#include "malloc.h"
#include <stdlib.h>

#define   MAX_LEN  10                	   /* �ַ�����󳤶� */
#define   STU_NUM 30                       /* ����ѧ������ */
#define   COURSE_NUM 6                     /* ���Ŀ��Կ�Ŀ�� */
#define   LEN sizeof(struct Student)
#define   MAX_LENTH  4 //mbti
#define PASSWORD "1234"

typedef struct Student
{
	long num;	                    /* ÿ��ѧ����ѧ�� */
	char name[MAX_LEN];            	/* ÿ��ѧ�������� */
	float score[COURSE_NUM];	    /* ÿ��ѧ��COURSE_NUM�Ź��εĳɼ� */
	float sum;                      /* ÿ��ѧ�����ܳɼ� */
	float aver;						/* ÿ��ѧ����ƽ���ɼ� */
	float weight; //��Ȩ�ɼ� 
	char mbti[MAX_LENTH];    //mbti
	struct Student *next;
}STU;


int   Menu(void);                                      //�����˵�
void  Print(STU *head, int n, int m);                  //��ӡ����
void  AverSumofEveryStudent(STU *head, int n, int m);  //����ÿ�ſγ̵��ֺܷ�ƽ����
void  AverSumofEveryCourse(STU *head, int n, int m);   //����ÿ��ѧ�����ֺܷ�ƽ����
void  weightedscore(STU *head, int n, int m, int w[]);//����ÿ��ѧ���ļ�Ȩ�ɼ�����Ȩ������100�� 
STU  *SortbyScore(STU *head, int n);				   //��ÿ��ѧ�����ܷ��ɸߵ����ų����α�
STU  *Creat(int n, int m);                             //��������¼����Ϣ
STU  *Creat1(int n, int m);
STU  *SortbyScore1(STU *head, int n);                  //��ÿ��ѧ�����ܷ��ɵ͵����ų����α�
STU  *SortbyNum(STU *head);                            //��ѧ����С�����ų��ɼ���
STU  *SortbyName(STU *head, int n);                    //���������ֵ�˳���ų��ɼ���
void  SearchbyNum(STU *head, int n, int m);            //��ѧ�Ų�ѯѧ���������俼�Գɼ�
void  SearchbyName(STU *head, int n, int m);           //��������ѯѧ���������俼�Գɼ�
void  StatisticAnalysis(STU *head, int n, int m);      //����𼰱������
void  WritetoFile(STU *head, int n, int m);            //��ÿ��ѧ���ļ�¼��Ϣд���ļ�
STU  *ReadfromFile(STU *head, int *n, int *m);         //���ļ��ж���ÿ��ѧ���ļ�¼��Ϣ����ʾ

void  personalities16_creat(STU *head, int n);
void  per16_score_correlation(STU *head, int n, int m);       //ʮ�����˸� 

int main()
{
	int n, m;
	int w[7]={0}; 
	int i;
	STU *head;  //����ͷ�ڵ�
	head = (STU *)malloc(LEN);
	char input[20]; 
	printf("Enter the password to access the system: ");
	scanf("%s", input);
	if (strcmp(input, PASSWORD) == 0) {
    printf("Access granted!\n");
    
	while (1)
	{
		i = Menu();
		if (i == 1)
		{
			system("cls");  //����
			printf("\t\t\t******************************************************************************\n");
			printf("\t\t\tInput student number(n<30):\n"); //����ѧ����
			printf("\t\t\t");
			scanf("%d", &n);
			printf("\t\t\tInput course number(m<=6):\n");
			printf("\t\t\t");
			scanf("%d", &m);
		}
		switch (i)
		{
		case 1:
			printf("\t\t\tInput student's ID, name and score:\n");
			head = Creat(n, m);
			system("cls");  //����
			break;
		case 2:
			system("cls");  //����
			AverSumofEveryStudent(head, n, m);
			break;
		case 3:
			system("cls");  //����
			AverSumofEveryCourse(head, n, m);
			break;
		case 4:
			system("cls");
			printf("\t\t\tInput the weight of every course(percentage system):\n");
			for(i = 0; i < m; i++)
			{
				scanf("%ld", &w[i]);
			}
			weightedscore(head, n, m, w); 
			break;
		case 5:
			system("cls");  //����
			printf("\n\n\n");
			printf("\t\t\tSort in ascending order by score:\n");
			head = SortbyScore(head, n);
			Print(head, n, m);
			break;
		case 6:
			system("cls");  //����
			printf("\n\n\n");
			printf("\t\t\tSort in ascending order by score:\n");
			head = SortbyScore1(head, n);
			Print(head, n, m);
			break;
		case 7:
			system("cls");  //����
			printf("\n\n\n");
			printf("\t\t\tSort in ascending order by number:\n");
			head = SortbyNum(head);
			Print(head, n, m);
			break;
		case 8:
			system("cls");  //����
			printf("\n\n\n");
			printf("\t\t\tSort in dictionary order by name:\n");
			head = SortbyName(head, n);
			Print(head, n, m);
			break;
		case 9:
			system("cls");  //����
			printf("\n\n\n");
			printf("\t\t\t******************************************************************************\n");
			printf("\t\t\tInput the number you want to search:\n");
			SearchbyNum(head, n, m);
			break;
		case 10:
			system("cls");  //����
			printf("\n\n\n");
			printf("\t\t\t******************************************************************************\n");
			printf("\t\t\tInput the name you want to search:\n");
			SearchbyName(head, n, m);
			break;
		case 11:
			system("cls");  //����
			StatisticAnalysis(head, n, m);
			break;
		case 12:
			system("cls");  //����
			printf("\n\n\n");
			Print(head, n, m);
			break;
		case 13:
			system("cls");  //����
			
			personalities16_creat(head, n);
			break;
		case 14:
			system("cls");  //����
			//head = ReadfromFile(head, &n, &m);
			per16_score_correlation(head, n, m);
			break;
		case 15:
			system("cls");  //����
			WritetoFile(head, n, m);
			//head = ReadfromFile(head, &n, &m);
			//per16_score_correlation(head, n, m);
			break;
		case 16:
			system("cls");  //����
			head = ReadfromFile(head, &n, &m);
			//per16_score_correlation(head, n, m);
			break;	
		case 0:
			system("cls");  //����
			printf("\n\n\n");
			printf("\t\t\t******************************************************************************\n");
			printf("\t\t\tEnd of program!\n");
			printf("\t\t\t******************************************************************************\n");
			return 0;
		default:
			system("cls");  //����
			printf("\n\n\n");
			printf("\t\t\t******************************************************************************\n");
			printf("\t\t\tInput error!\n");
			printf("\t\t\t******************************************************************************\n");

		}
	}
	
	}else{
	    printf("Access denied.Incorrect password!\n");
		return 1;
	}
	return 0;


}
// �����˵�
int   Menu(void)
{
	int i;
	system("title ѧ���ɼ�����ϵͳ  By  somebody");
	printf("\n\n");
	printf("\t\t\t                         ѧ���ɼ�����ϵͳ\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                Management for Students' scores                             *\n");
	printf("\t\t\t*                1.  Input record                                            *\n");
	printf("\t\t\t*                2.  Caculate total and average score of every student       *\n");
	printf("\t\t\t*                3.  Caculate total and average score of every course        *\n");
	printf("\t\t\t*                4.  Caculate weighted score of every student                *\n");
	printf("\t\t\t*                5.  Sort in descending order by score                       *\n");
	printf("\t\t\t*                6.  Sort in ascending order by score                        *\n");
	printf("\t\t\t*                7.  Sort in ascending order by number                       *\n");
	printf("\t\t\t*                8.  Sort in dictionary order by name                        *\n");
	printf("\t\t\t*                9.  Search by number                                        *\n");
	printf("\t\t\t*                10. Search by name                                          *\n");
	printf("\t\t\t*                11. Statistic analysis                                      *\n");
	printf("\t\t\t*                12. List record                                             *\n");
	printf("\t\t\t*                13. add mbti data                                           *\n");
	printf("\t\t\t*                14. find out the correlation of mbti and scores             *\n");
	printf("\t\t\t*                15. Write to a file                                         *\n");
	printf("\t\t\t*                16. Read from a file                                        *\n");
	printf("\t\t\t*                0.  Exit                                                    *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************Please Input your choice:");
	scanf("%d", &i);
	return i;

}

// ��������
STU *Creat(int n, int m) {
	STU *head;
	STU *p1, *p2;
	int i, j;
	// system("cls");
	for (i = 1; i<n + 1; i++)
	{
		p1 = (STU *)malloc(LEN);
		printf("\t\t\t");
		scanf("%ld", &p1->num);
		printf("\t\t\t");
		scanf("%s", p1->name);
		for (j = 0; j<m; j++)
		{
			printf("\t\t\t");
			scanf("%f", &p1->score[j]);
		}
		p1->next = NULL;
		if (i == 1)
		{
			head = p2 = p1;
		}
		else
		{
			p2->next = p1;
			p2 = p1;
		}
	}
	return(head);
}

STU *Creat1(int n, int m)
{
	STU *head;
	STU *p1, *p2;
	int i, j;
	// system("cls");
	for (i = 1; i<n + 1; i++)
	{
		p1 = (STU *)malloc(LEN);
		p1->next = NULL;
		if (i == 1)
		{
			head = p2 = p1;
		}
		else
		{
			p2->next = p1;
			p2 = p1;
		}
	}
	return(head);
}
void  AverSumofEveryStudent(STU *head, int n, int m)
{
	STU *p;
	int i, j = 1;
	char ch;
	float sum;
	p = head;
	if (head != NULL)
	{
		printf("\t\t\t******************************************************************************\n");
		for (i = 0; i<m; i++)
		{
			p = head;
			sum = 0.0;
			do {
				sum += p->score[i];
				p = p->next;
			} while (p != NULL);

			printf("\t\t\tcourse %d:    sum=%.0f , aver=%.0f\n", j, sum, sum / n);
			j++;
		}
		printf("\t\t\t******************************************************************************\n");

	}
}

void  AverSumofEveryCourse(STU *head, int n, int m)
{
	STU *p;
	int i, j;
	p = head;
	if (head != NULL)
	{
		printf("\n\n\n");
		printf("\t\t\t******************************************************************************\n");
		for (i = 0; i<n; i++)
		{
			p->sum = 0.0;
			for (j = 0; j<m; j++)
			{
				p->sum += p->score[j];
			}
			p->aver = p->sum / m;
			printf("\t\t\tstudent %d:    sum=%.0f , aver=%.0f\n", i + 1, p->sum, p->aver);
			p = p->next;
		}
		printf("\t\t\t******************************************************************************\n");
	}
}

void weightedscore(STU *head, int n, int m, int w[])
{
	
	STU *p;
	int i, j;
	p = head;
	if (head != NULL)
	{
		printf("\n\n\n");
		printf("\t\t\t******************************************************************************\n");
		for (i = 0; i<n; i++)
		{
			p->weight = 0.0;
			for (j = 0; j<m; j++)
			{
				p->weight += p->score[j]*w[j]/100;
			}
			printf("\t\t\tstudent %s:    weightedscore=%.0f\n", p->name, p->weight);
			p = p->next;
		}
		printf("\t\t\t******************************************************************************\n");
	}
 } 

STU  *SortbyScore(STU *head, int n)
{
	STU *endpt;    //����ѭ���Ƚ�
	STU *p;        //��ʱָ�����
	STU *p1, *p2;

	p1 = (STU *)malloc(LEN);
	p1->next = head;        //ע����⣺��������һ���ڵ㣬���ڵ�һ���ڵ��ǰ�棬��Ҫ��Ϊ�˱��ڱȽϡ���Ϊ��һ���ڵ�û��ǰ�������ǲ��ܽ�����ַ
	head = p1;                 //��headָ��p1�ڵ㣬������ɺ������ٰ�p1�ڵ��ͷŵ�

	for (endpt = NULL; endpt != head; endpt = p)
	{
		for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)
		{
			if (p1->next->sum < p1->next->next->sum)  //���ǰ��Ľڵ��ֵ�Ⱥ���ڵ�ļ�ֵ���򽻻�
			{
				p2 = p1->next->next;
				p1->next->next = p2->next;
				p2->next = p1->next;
				p1->next = p2;
				p = p1->next->next;
			}
		}
	}

	p1 = head;              //��p1����Ϣȥ��
	head = head->next;       //��headָ�������ĵ�һ���ڵ�
	free(p1);          //�ͷ�p1
	p1 = NULL;          //p1��ΪNULL����֤��������Ұָ�롱������ַ��ȷ����ָ�����

	return head;
}

STU  *SortbyScore1(STU *head, int n)
{
	STU *endpt;    //����ѭ���Ƚ�
	STU *p;        //��ʱָ�����
	STU *p1, *p2;

	p1 = (STU *)malloc(LEN);
	p1->next = head;        //ע����⣺��������һ���ڵ㣬���ڵ�һ���ڵ��ǰ�棬��Ҫ��Ϊ�˱��ڱȽϡ���Ϊ��һ���ڵ�û��ǰ�������ǲ��ܽ�����ַ
	head = p1;                 //��headָ��p1�ڵ㣬������ɺ������ٰ�p1�ڵ��ͷŵ�

	for (endpt = NULL; endpt != head; endpt = p)
	{
		for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)
		{
			if (p1->next->sum > p1->next->next->sum)  //���ǰ��Ľڵ��ֵ�Ⱥ���ڵ�ļ�ֵ���򽻻�
			{
				p2 = p1->next->next;
				p1->next->next = p2->next;
				p2->next = p1->next;
				p1->next = p2;
				p = p1->next->next;
			}
		}
	}

	p1 = head;              //��p1����Ϣȥ��
	head = head->next;       //��headָ�������ĵ�һ���ڵ�
	free(p1);          //�ͷ�p1
	p1 = NULL;          //p1��ΪNULL����֤��������Ұָ�롱������ַ��ȷ����ָ�����

	return head;
}

STU *SortbyNum(STU *head)
{
	STU *first;    //Ϊԭ����ʣ������ֱ�Ӳ�������Ľڵ�ͷָ��
	STU *t;        //��ʱָ�����������ڵ�
	STU *p, *q;     //��ʱָ�����

	first = head->next;      //ԭ����ʣ������ֱ�Ӳ�������Ľڵ������ɸ���ͼ12�����
	head->next = NULL;       //ֻ����һ���ڵ����������������ɸ���ͼ11�����

	while (first != NULL)        //����ʣ�����������
	{
		//ע�⣺����for����������ֱ�Ӳ�������˼��ĵط�
		for (t = first, q = head; ((q != NULL) && (q->num < t->num)); p = q, q = q->next);  //����ڵ��������������Ҳ����λ��

		first = first->next; //���������еĽڵ��뿪���Ա������뵽����������

		if (q == head)      //���ڵ�һ���ڵ�֮ǰ
		{
			head = t;
		}
		else            //p��q��ǰ��
		{
			p->next = t;
		}
		t->next = q;     //��ɲ��붯��
						 //first = first->next;
	}
	return head;
}

STU  *SortbyName(STU *head, int n)
{
	STU *endpt;    //����ѭ���Ƚ�
	STU *p;        //��ʱָ�����
	STU *p1, *p2;

	p1 = (STU *)malloc(LEN);
	p1->next = head;        //ע����⣺��������һ���ڵ㣬���ڵ�һ���ڵ��ǰ�棬��Ҫ��Ϊ�˱��ڱȽϡ���Ϊ��һ���ڵ�û��ǰ�������ǲ��ܽ�����ַ
	head = p1;                 //��headָ��p1�ڵ㣬������ɺ������ٰ�p1�ڵ��ͷŵ�

	for (endpt = NULL; endpt != head; endpt = p)
	{
		for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)
		{
			if (strcmp(p1->next->name, p1->next->next->name)>0)  //���ǰ��Ľڵ��ֵ�Ⱥ���ڵ�ļ�ֵ���򽻻�
			{
				p2 = p1->next->next;
				p1->next->next = p2->next;
				p2->next = p1->next;
				p1->next = p2;     //��ϵ�4�����
				p = p1->next->next;   //��ϵ�6�����
			}
		}
	}

	p1 = head;              //��p1����Ϣȥ��
	head = head->next;       //��headָ�������ĵ�һ���ڵ�
	free(p1);          //�ͷ�p1
	p1 = NULL;          //p1��ΪNULL����֤��������Ұָ�롱������ַ��ȷ����ָ�����

	return head;
}


void Print(STU *head, int n, int m)
{
	STU *p;
	int i;
	p = head;

	if (head != NULL)        //ֻҪ���ǿ�������������������нڵ�
	{
		printf("\t\t\t******************************************************************************\n");
		do
		{

			printf("\t\t\t%ld\t%s\t", p->num, p->name);
			for (i = 0; i<m; i++)
			{
				printf("%.0f\t", p->score[i]);
			}
			printf("%.0f\t%.0f\n", p->sum, p->sum / m);
			p = p->next;     //�Ƶ���һ���ڵ�
		} while (p != NULL);
		printf("\t\t\t******************************************************************************\n");
	}
}

void SearchbyNum(STU *head, int n, int m)
{
	long num1;
	int i;
	int flag = 1;
	int b;
	STU *p;
	p = head;
	printf("\t\t\t");
	A:
	b = scanf("%ld", &num1); 
    if (b != 1) 
	{  
        printf("\t\t\tinput error!\n\n");  
        fflush(stdin);
        printf("\t\t\t���������룺\n");
        printf("\t\t\t");  
        goto A;
	}else{  
	    system("cls");
	    printf("\t\t\t******************************************************************************\n");
	    if (head != NULL)
	    {
		    do
		    {
		        if (p->num == num1)		
		    	{
		    		printf("\t\t\t");
		    		printf("%ld\t%s\t", p->num, p->name);
			    	for (i = 0; i<m; i++)
				    {
					    printf("%.0f\t", p->score[i]);
				    }
				    printf("%.0f\t%.0f\n", p->sum, p->sum / m);
				    flag = 0;
			    }
			    p = p->next;
		    } while (p != NULL);
		    
		    if (flag)
	        {
			    printf("\t\t\t");
			    printf("Not found!\n");
	        }
	        
		    printf("\t\t\t******************************************************************************\n");
	    }
       
	}  
}

void  SearchbyName(STU *head, int n, int m)
{
	char name[MAX_LEN];
	int i;
	int flag = 1;
	printf("\t\t\t");
	scanf("%s", name);
	STU *p;
	p = head;
	if (head != NULL)
	{
		do {
			if (strcmp(name, p->name) == 0)
			{
				printf("\t\t\t");
				printf("%ld\t%s\t", p->num, p->name);
				for (i = 0; i<m; i++)
				{
					printf("%.0f\t", p->score[i]);
				}
				printf("%.0f\t%.0f\n", p->sum, p->sum / m);
				flag = 0;
			}
			p = p->next;

		} while (p != NULL);
		if (flag)
		{
			printf("\t\t\t");
			printf("Not found!\n");
		}
	}
	printf("\t\t\t******************************************************************************\n");

}

void  StatisticAnalysis(STU *head, int n, int m)
{
	int a[6];
	STU *p;
	p = head;
	int i, j;
	for (i = 0; i<m; i++)
	{
		p = head; // ???????????????????
		for (j = 0; j<6; j++)  // ?????
		{
			a[j] = 0;
		}
		do {
			if (p->score[i]<60)
			{
				a[0]++;
			}
			else if (p->score[i]<70)
			{
				a[1]++;
			}
			else if (p->score[i]<80)
			{
				a[2]++;
			}
			else if (p->score[i]<90)
			{
				a[3]++;
			}
			else if (p->score[i]<100)
			{
				a[4]++;
			}
			else
			{
				a[5]++;
			}

			p = p->next;

		} while (p != NULL);
		printf("\n\n\n");
		printf("\t\t\t******************************************************************************\n");
		printf("\t\t\t* For course %d:\n", i + 1);
		printf("\t\t\t* <60\t%d\t%.2f%%\n", a[0], 100 *(float)a[0]/ n);
		printf("\t\t\t* %d-%d\t%d\t%.2f%%\n", 60, 69, a[1], 100 * (float)a[1]/ n);
		printf("\t\t\t* %d-%d\t%d\t%.2f%%\n", 70, 79, a[2], 100 * (float)a[2]/ n);
		printf("\t\t\t* %d-%d\t%d\t%.2f%%\n", 80, 89, a[3], 100 * (float)a[3]/ n);
		printf("\t\t\t* %d-%d\t%d\t%.2f%%\n", 90, 99, a[4], 100 * (float)a[4]/ n);
		printf("\t\t\t* %d\t%d\t%.2f%%\n", 100, a[5], 100 *(float)a[5]/ n);
		printf("\t\t\t******************************************************************************\n");

	}
}

void  WritetoFile(STU *head, int n, int m)
{
	STU *p;
	p = head;
	FILE *fp;
	int i, j;
	printf("\n\n\n");
	printf("\t\t\t******************************************************************************\n");
	if ((fp = fopen("student.txt", "w")) == NULL)
	{
		printf("\t\t\tFail to open student.txt\n");
		return;
	}
	fprintf(fp, "%d\t%d\n", n, m);
	for (i = 0; i<n; i++)
	{
		fprintf(fp, "%12ld%12s", p->num, p->name);
		for (j = 0; j<m; j++)
		{
			fprintf(fp, "%12.0f", p->score[j]);
		}
		fprintf(fp, "%12.0f%12.0f\n", p->sum, p->sum / m);

		p = p->next;
	}
	printf("\t\t\tExport Successfully!\n");
	fclose(fp);
	printf("\t\t\t******************************************************************************\n");

}

/*

void  ReadfromFile(STU stu[], int *n, int *m)
{
FILE *fp;
int i, j;
printf("\n\n\n");
printf("\t\t\t******************************************************************************\n");
if ((fp = fopen("student.txt", "r")) == NULL)
{
printf("\t\t\tFail to open student.txt\n");
return;
}
fscanf(fp, "%d\t%d\n", n, m);
for (i = 0; i<*n; i++)
{
fscanf(fp, "%12ld", &stu[i].num);
fscanf(fp, "%12s", stu[i].name);
for (j = 0; j<*m; j++)
{
fscanf(fp, "%12f", &stu[i].score[j]);
}
fscanf(fp, "%12f%12f", &stu[i].sum, &stu[i].aver);

}
printf("\t\t\tImport Successfully!\n");
fclose(fp);


for (i = 0; i < *n; i++)
{
printf("\t\t\t%ld\t%s\t", stu[i].num, stu[i].name);
for (j = 0; j<*m; j++)
{
printf("%.0f\t", stu[i].score[j]);
}
printf("%.0f\t%.0f\n", stu[i].sum, stu[i].aver);
}

printf("\t\t\t******************************************************************************\n");

}*/


//��������ֱ��������һ���µ�����ȷ������ֱ�Ӷ�ȡ��õ�����
STU *ReadfromFile(STU *head, int *n, int *m)
{
	STU *p;
	FILE *fp;
	int i, j;
	if ((fp = fopen("student.txt", "r")) == NULL)
	{
		printf("\t\t\tFail to open student.txt\n");
		return NULL;
	}
	fscanf(fp, "%d\t%d\n", n, m);
	head = Creat1(*n, *m);  //������һ�����������Ҹ���head
	p = head;
	for (i = 0; i<*n; i++)
	{
		fscanf(fp, "%12ld", &p->num);
		fscanf(fp, "%12s", &p->name);
		for (j = 0; j<*m; j++)
		{
			fscanf(fp, "%12f", &p->score[j]);
		}
		fscanf(fp, "%12f%12f", &p->sum, &p->aver);

		p = p->next;

	}
	i = *n;
	j = *m;
	printf("\t\t\tImport Successfully!\n");
	fclose(fp);

	Print(head, i, j);

	return head;
}


void personalities16_creat(STU *head, int n) 
{
	//STU *head;
	STU *p1;
	p1 = head;
	int i;
	// system("cls");
	for (i = 1; i<n + 1; i++)
	{
		printf("\t\t\t");
		scanf("%s", p1->mbti);
	}
}

void per16_score_correlation(STU *head, int n, int m)
{
    float per[17][6] = {0.0};
    int s[17] = {0};
    int i;
    int flag = 1;
    char* pers[16] = {"isfj","esfj","istj","isfp","estj","esfp","enfp","istp","infp","estp","intp","entp","enfj","intj","entj","infj"};
    printf("\t\t\t");
    //scanf("%s", mbti);
    STU *p;
    p = head;
    int b;
    if (head != NULL)
    {
        for(int i = 0; i < n; i++)
        {
            for(int y = 0; y < 16; y++)
            {
            	b = strcmp(p->mbti,pers[y]);
            	if(b == 0)
                {
                    s[y] += 1;
                    for(int j = 0; j < m; j++)
                    {
                        per[y][j] += p->score[j];
                    }
                }
			}
			p = p->next;
	    }
    }
    float aver_per[16][6] = {0};
    for(int i = 0; i < 16; i++)
    {
        if(s[i] != 0)
        {
            for(int j = 0; j < m; j++)
            {
                aver_per[i][j] = per[i][j] / s[i];
            }
        }
    }
    for(int i = 0; i < 16; i++)
    {
        if(s[i] != 0)
        {
            for(int j = 0; j < m; j++)
            {
                printf("\t\t\tpersonalitis %s:  course %d,  aver_score=%.0f\n", pers[i-1], j+1, aver_per[i][j]);
                
            }
        }
    }
    printf("\t\t\t******************************************************************************\n");
}
