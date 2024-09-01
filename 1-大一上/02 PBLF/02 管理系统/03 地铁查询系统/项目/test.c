#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define M 618
#define INF 0x3f3f3f3f

typedef struct users//�����û����ݴ洢��Ԫ
{
	char  name[20];
	char  zh[20];
	char  mm[20];
}A;
struct station {			//����վ��Žṹ�� 
	char stationName[30];	//վ�� 
	int IsChange;			//�ܷ񻻳� 
};
struct vertex {				//����ͼ�ṹ�� 
	int weight;				//Ȩ�� 
	int lineID;				//·����� 
};
struct station StationID_list[M];	//����վ������� 
struct vertex map[M][M];	//����ͼ 
//int VerNum = 0;
int lineID, StationNum, lineNum, IsChange, VerNum;	//·����ţ�һ��·���е���վ������·�߸������Ƿ񻻳ˣ��ܵ���վ���� 
int now = 1;
int i;
int prev[M], dist[M], path[M], top, pathID[M][M];	//�������飬���·����ֵ���飬dijkstra���·��������飬ջ����Floyd���·���������
char StationBegin[30], StationEnd[30];	//���վ���յ�վ 
void DrawSubwayMap(FILE* fp);		//��ͼ 
int SearchMap(char* s);				//��վ���Ƿ���ֹ� 
void dijkstra(int vs, int ve);		//dijkstra�㷨 
void PrintPath(int v1, int v2);		//��ӡ·�� 
void menu();//�˵�
int start(int math);//��ת����
int zhuce();//ע��ģ��
int denglu();//��¼ģ��
void firstmenu(void)
{
	printf("--------------------------\n");
	printf("   ��ӭ����������·ϵͳ�� \n");
	printf("1.�������ѡ��ϵͳ 0.�˳�\n");
	printf("    ���������ѡ��>\n");
	printf("--------------------------\n");
}
int main()
{
	menu();
	firstmenu();
	int i, j, v1, v2, t;
	int input = 0;
	scanf("%d", &input);
	if (input == 0) {
		printf("�˳�ϵͳ\n");
	}
	if (input) {
		printf("�������Ƿ��ڸ߷�����·(0/1 NO/YES)\n");
		int input1 = 0;
		scanf("%d", &input1);
		if (input1 == 1) {
			printf("������߷�����·��ţ��������֣�");
			int input3 = 0;
			scanf("%d", &input3);
			if (input3 == 1) {
				FILE* fp = fopen("bgstations1.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 2) {
				FILE* fp = fopen("bgstations2.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 3) {
				FILE* fp = fopen("bgstations3.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 4) {
				FILE* fp = fopen("bgstations4.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 5) {
				FILE* fp = fopen("bgstations5.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 6) {
				FILE* fp = fopen("bgstations6.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 7) {
				FILE* fp = fopen("bgstations7.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 8) {
				FILE* fp = fopen("bgstations8.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 9) {
				FILE* fp = fopen("bgstations9.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 10) {
				FILE* fp = fopen("bgstations10.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 17) {
				FILE* fp = fopen("bgstations17.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
			else if (input3 == 18) {
				FILE* fp = fopen("bgstations18.txt", "r");
				printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//��ʼ��ͼ 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
						map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
					}
				DrawSubwayMap(fp);		//��ͼ 
				v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
				v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
				dijkstra(v1, v2);	//�����· 
				for (t = v2; t != v1; t = prev[t])	//·��׷�� 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//��ӡ��� 
				return;
			}
		}
		printf("�����������ڵ���ʼ�ص����Ҫ������յ�:\n");
		if (input1 == 0) {
			FILE* fp = fopen("bgstations.txt", "r");

			scanf("%s %s", StationBegin, StationEnd);
			for (i = 0; i < M; i++)			//��ʼ��ͼ 
				for (j = 0; j < M; j++)
				{
					map[i][j].weight = map[j][i].weight = INF;	//Ȩ������� 
					map[i][j].lineID = map[j][i].lineID = 0;	//���Ϊ0 
				}
			DrawSubwayMap(fp);		//��ͼ 
			v1 = SearchMap(StationBegin);	//�ҵ����վ��� 
			v2 = SearchMap(StationEnd);	//�ҵ��յ�վ���  
			dijkstra(v1, v2);	//�����· 
			for (t = v2; t != v1; t = prev[t])	//·��׷�� 
			{
				path[top] = t;
				top++;
			}
			PrintPath(v1, v2);	//��ӡ��� 
		}
	}
	return 0;
}
void DrawSubwayMap(FILE* fp)
{
	int i, j, ContainID, EdgeLast;//�������������ڵĵ���վ�ı�ţ��ߵ���� 
	char stationName[30];		//վ�� 
	fscanf(fp, "%d", &lineNum);
	for (i = 0; i < lineNum; i++)
	{
		fscanf(fp, "%d %d", &lineID, &StationNum);
		EdgeLast = -1;	//ÿһ��·��һ��ʼ���� -1 
		for (j = 0; j < StationNum; j++)
		{
			fscanf(fp, "%s %d", stationName, &IsChange);
			ContainID = SearchMap(stationName);	//������û�� 
			if (ContainID == -1)		//û�� 
			{
				strcpy(StationID_list[VerNum].stationName, stationName);	//�洢 
				StationID_list[VerNum].IsChange = IsChange;				//�洢 
				if (EdgeLast != -1)		//����бߵ���� 
				{
					map[EdgeLast][VerNum].lineID = map[VerNum][EdgeLast].lineID = lineID;	//�洢 
					map[EdgeLast][VerNum].weight = map[VerNum][EdgeLast].weight = 1;		//�洢 
				}
				EdgeLast = VerNum;	//�յ����� 
				VerNum++;			//���� +1 
			}
			else
			{
				if (EdgeLast != -1)	//����бߵ���� 
				{
					map[EdgeLast][ContainID].lineID = map[ContainID][EdgeLast].lineID = lineID;//�洢 
					map[EdgeLast][ContainID].weight = map[ContainID][EdgeLast].weight = 1;	//�洢 
				}
				EdgeLast = ContainID;	//�յ�����
			}
		}
	}
}
int SearchMap(char* s)
{
	int i;
	for (i = 0; i < VerNum; i++)
		if (strcmp(s, StationID_list[i].stationName) == 0)
			return i;	//������� 
	return -1;
}
void dijkstra(int vs, int ve)
{
	int i, j, k, min, tmp;
	int flag[M];      				// flag[i]=1��ʾ"����vs"��"����i"�����·���ѳɹ���ȡ��
	for (i = 0; i < VerNum; i++)	// ��ʼ��
	{
		flag[i] = 0;              	// ����i�����·����û��ȡ����
		prev[i] = vs;             	 // ����i��ǰ������Ϊ0��
		dist[i] = map[vs][i].weight;	// ����i�����·��Ϊ"����vs"��"����i"��Ȩ��
	}
	dist[vs] = 0, flag[vs] = 1;		// ��"����vs"������г�ʼ��
	for (i = 0; i < VerNum - 1; i++)	// ����1�Σ�ÿ���ҳ�һ����������·����
	{								// Ѱ�ҵ�ǰ��С��·����������δ��ȡ���·���Ķ����У��ҵ���vs����Ķ���(k)��
		min = INF;
		for (j = 0; j < VerNum; j++)
		{
			if (flag[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}
		flag[k] = 1;				// ���"����k"Ϊ�Ѿ���ȡ�����·��
		// ������ǰ���·����ǰ������:  �����Ѿ�"����k�����·��"֮�󣬸���"δ��ȡ���·���Ķ�������·����ǰ������"��
		if (k == ve)	return;
		for (j = 0; j < VerNum; j++)
		{
			tmp = (map[k][j].weight == INF ? INF : (min + map[k][j].weight)); // ��ֹ���
			if (flag[j] == 0 && (tmp < dist[j]) && map[k][j].lineID > 0)
			{
				dist[j] = tmp;
				prev[j] = k;	//��¼ǰ�� 
			}
		}
	}
}
void PrintPath(int v1, int v2)
{
	int i, EdgeLast = v1, pathLen = 1, u = path[top - 1];//i�Ǳ������ߵ���㣬���ȣ��ߵ��յ� 
	int lineId = map[EdgeLast][u].lineID;	//��ʼ·�߱�� 
	printf("%s-%d", StationID_list[v1].stationName, lineId); //��ӡ���վ�����վ��·�� 
	EdgeLast = u;
	for (i = top - 2; i >= 0; i--)	//����ջ������Ѱ�� 
	{
		u = path[i];	//�����յ� 
		if (lineId != map[EdgeLast][u].lineID)	//���� 
		{
			lineId = map[EdgeLast][u].lineID;
			printf("(%d)-%s-%d", pathLen, StationID_list[EdgeLast].stationName, lineId);
			pathLen = 0;
		}
		pathLen++;		//���� +1 
		EdgeLast = u;	//�������
	}
	printf("(%d)-%s", pathLen, StationID_list[v2].stationName);//��ӡ�յ�վ
}

void menu()//�˵�
{
	int select = 0;
	printf("\n\t\t\t++++++++++++++++++++++++\n\t\t\t+  ��ӭʹ��XX��¼ϵͳ  +\n\t\t\t++++++++++++++++++++++++\n");

	while (now)
	{
		system("cls");
		do
		{
			printf("\n		******************�˵���*****************\n");
			printf("\t\t*\t      �ٵ�¼                    *\n");
			printf("\t\t*\t      ��ע��                    *\n");
			printf("\t\t*\t      ���˳�ϵͳ\t\t*\n");
			printf("		*****************************************\n");
			printf("\n");
			printf("\t\t������ѡ�[\t]\b\b\b");
			scanf("%d", &select);
		} while (select > 5 || select < 1);
		int ret = start(select);
		if (ret) {
			break;
		}
	}
}

int start(int math)//��ת
{

	switch (math)
	{
	case 1:
		return denglu();
		break;
	case 2:
		return zhuce();
		break;
	case 3:
		printf("��л����֧�֣�\n��ӭ�´�ʹ�ã�");
		now = 0;
		exit(0);
	}
}

int zhuce()//ע��ģ��
{
	system("cls");
	char c[20];
	A a, b;
	FILE* fp;
	printf("\n\t\t��ӭ����ע����棡\n");
	Sleep(500);
	fp = fopen("Users.txt", "r");
	fread(&b, sizeof(A), 1, fp);
	printf("\n\t\t�������˺�:[ \t\t ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%s", &a.zh);
	while (1)
	{
		if (strcmp(a.zh, b.zh))
		{
			if (!feof(fp))
			{
				fread(&b, sizeof(A), 1, fp);
			}
			else
			{
				break;
			}
		}
		else
		{
			printf("���˺��Ѵ��ڣ�����");
			Sleep(1000);
			fclose(fp);
			return 1;
		}
	}
	int time = 2;
	do
	{
		printf("\t\t����������:[ \t\t ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
		i = 0;
		for (i = 0; i < 20; i++)
		{
			a.mm[i] = _getch();
			if (a.mm[i] == '\r')
			{
				break;
			}
			else
			{
				printf("*");
			}
		}
		a.mm[i] = '\0';
		printf("\n");
		printf("\t\t��ȷ�����룺[ \t\t ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
		i = 0;
		for (i = 0; i < 20; i++)
		{
			c[i] = _getch();
			if (c[i] == '\r')
			{
				break;
			}
			else
			{
				printf("*");
			}
		}
		c[i] = '\0';
		printf("\n");
		if (!strcmp(a.mm, c))
		{

			printf("\t\t�������û�����");
			scanf("%s", &a.name);
			fp = fopen("Users.txt", "a");
			fwrite(&a, sizeof(A), 1, fp);
			printf("%s,ע��ɹ�������", a.name);
			fclose(fp);
			Sleep(1500);
			return 0;
		}
		else
		{
			if (time != 0)
			{
				printf("�������\n\n�������������룡��\n\n������%d�λ��ᣡ����", time);
				time--;
				continue;
			}
			else
			{
				printf("\n\t\t���������󣬼����˳���");
				fclose(fp);
				Sleep(1500);
				return 0;
			}
		}
	} while (time >= 0);
}


int denglu()
{
	system("cls");
	A a, b;
	FILE* fp;
	printf("��ӭ������¼���棡");
	printf("�˺ţ�\n");
	scanf("%s", &b.zh);
	printf("���룺\n");
	i = 0;
	for (i = 0; i < 20; i++)
	{
		b.mm[i] = _getch();
		if (b.mm[i] == '\r')
		{
			break;
		}
		else
		{
			printf("*");
		}
	}
	b.mm[i] = '\0';
	printf("\n");
	fp = fopen("Users.txt", "r");
	while (1)
	{
		fread(&a, sizeof(A), 1, fp);
		//printf("%s %s %s\n",a.name,a.zh,a.mm);
		if (strcmp(b.zh, a.zh) == 0)
		{
			break;

		}
		else
		{
			if (!feof(fp))
			{
				fread(&a, sizeof(A), 1, fp);
			}
			else
			{
				printf("�˺Ż�������󣡣���\n");
				fclose(fp);
				Sleep(1000);
				system("cls");
				return 0;
			}
		}
	}
	if (strcmp(b.mm, a.mm) == 0)
	{
		printf("%s����ӭ����������\n", a.name);
		fclose(fp);
		Sleep(1000);
		system("cls");
		return 1;
	}
	else
	{
		printf("������󣡣���\n");
		fclose(fp);
		Sleep(1000);
		system("cls");
		return 0;
	}
}