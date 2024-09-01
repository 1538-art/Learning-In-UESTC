#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define M 618
#define INF 0x3f3f3f3f

typedef struct users//创建用户数据存储单元
{
	char  name[20];
	char  zh[20];
	char  mm[20];
}A;
struct station {			//地铁站序号结构体 
	char stationName[30];	//站名 
	int IsChange;			//能否换乘 
};
struct vertex {				//地铁图结构体 
	int weight;				//权重 
	int lineID;				//路线序号 
};
struct station StationID_list[M];	//地铁站序号数组 
struct vertex map[M][M];	//地铁图 
//int VerNum = 0;
int lineID, StationNum, lineNum, IsChange, VerNum;	//路线序号，一条路线中地铁站个数，路线个数，是否换乘，总地铁站个数 
int now = 1;
int i;
int prev[M], dist[M], path[M], top, pathID[M][M];	//跟踪数组，最短路径数值数组，dijkstra最短路径编号数组，栈顶，Floyd最短路径编号数组
char StationBegin[30], StationEnd[30];	//起点站，终点站 
void DrawSubwayMap(FILE* fp);		//建图 
int SearchMap(char* s);				//找站名是否出现过 
void dijkstra(int vs, int ve);		//dijkstra算法 
void PrintPath(int v1, int v2);		//打印路径 
void menu();//菜单
int start(int math);//中转程序
int zhuce();//注册模块
int denglu();//登录模块
void firstmenu(void)
{
	printf("--------------------------\n");
	printf("   欢迎来到地铁线路系统！ \n");
	printf("1.进入地铁选择系统 0.退出\n");
	printf("    请输入你的选择：>\n");
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
		printf("退出系统\n");
	}
	if (input) {
		printf("您现在是否处于高峰期线路(0/1 NO/YES)\n");
		int input1 = 0;
		scanf("%d", &input1);
		if (input1 == 1) {
			printf("请输入高峰期线路编号（输入数字）");
			int input3 = 0;
			scanf("%d", &input3);
			if (input3 == 1) {
				FILE* fp = fopen("bgstations1.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 2) {
				FILE* fp = fopen("bgstations2.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 3) {
				FILE* fp = fopen("bgstations3.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 4) {
				FILE* fp = fopen("bgstations4.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 5) {
				FILE* fp = fopen("bgstations5.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");
				scanf("%s %s", StationBegin, StationEnd);

				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 6) {
				FILE* fp = fopen("bgstations6.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 7) {
				FILE* fp = fopen("bgstations7.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 8) {
				FILE* fp = fopen("bgstations8.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 9) {
				FILE* fp = fopen("bgstations9.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 10) {
				FILE* fp = fopen("bgstations10.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 17) {
				FILE* fp = fopen("bgstations17.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
			else if (input3 == 18) {
				FILE* fp = fopen("bgstations18.txt", "r");
				printf("请输入你所在的起始地点和想要到达的终点:\n");

				scanf("%s %s", StationBegin, StationEnd);
				for (i = 0; i < M; i++)			//初始化图 
					for (j = 0; j < M; j++)
					{
						map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
						map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
					}
				DrawSubwayMap(fp);		//建图 
				v1 = SearchMap(StationBegin);	//找到起点站编号 
				v2 = SearchMap(StationEnd);	//找到终点站编号  
				dijkstra(v1, v2);	//找最短路 
				for (t = v2; t != v1; t = prev[t])	//路径追溯 
				{
					path[top] = t;
					top++;
				}
				PrintPath(v1, v2);	//打印编号 
				return;
			}
		}
		printf("请输入你所在的起始地点和想要到达的终点:\n");
		if (input1 == 0) {
			FILE* fp = fopen("bgstations.txt", "r");

			scanf("%s %s", StationBegin, StationEnd);
			for (i = 0; i < M; i++)			//初始化图 
				for (j = 0; j < M; j++)
				{
					map[i][j].weight = map[j][i].weight = INF;	//权重无穷大 
					map[i][j].lineID = map[j][i].lineID = 0;	//编号为0 
				}
			DrawSubwayMap(fp);		//建图 
			v1 = SearchMap(StationBegin);	//找到起点站编号 
			v2 = SearchMap(StationEnd);	//找到终点站编号  
			dijkstra(v1, v2);	//找最短路 
			for (t = v2; t != v1; t = prev[t])	//路径追溯 
			{
				path[top] = t;
				top++;
			}
			PrintPath(v1, v2);	//打印编号 
		}
	}
	return 0;
}
void DrawSubwayMap(FILE* fp)
{
	int i, j, ContainID, EdgeLast;//两个变量，存在的地铁站的编号，边的起点 
	char stationName[30];		//站名 
	fscanf(fp, "%d", &lineNum);
	for (i = 0; i < lineNum; i++)
	{
		fscanf(fp, "%d %d", &lineID, &StationNum);
		EdgeLast = -1;	//每一条路线一开始都是 -1 
		for (j = 0; j < StationNum; j++)
		{
			fscanf(fp, "%s %d", stationName, &IsChange);
			ContainID = SearchMap(stationName);	//看看有没有 
			if (ContainID == -1)		//没有 
			{
				strcpy(StationID_list[VerNum].stationName, stationName);	//存储 
				StationID_list[VerNum].IsChange = IsChange;				//存储 
				if (EdgeLast != -1)		//如果有边的起点 
				{
					map[EdgeLast][VerNum].lineID = map[VerNum][EdgeLast].lineID = lineID;	//存储 
					map[EdgeLast][VerNum].weight = map[VerNum][EdgeLast].weight = 1;		//存储 
				}
				EdgeLast = VerNum;	//终点变起点 
				VerNum++;			//总数 +1 
			}
			else
			{
				if (EdgeLast != -1)	//如果有边的起点 
				{
					map[EdgeLast][ContainID].lineID = map[ContainID][EdgeLast].lineID = lineID;//存储 
					map[EdgeLast][ContainID].weight = map[ContainID][EdgeLast].weight = 1;	//存储 
				}
				EdgeLast = ContainID;	//终点变起点
			}
		}
	}
}
int SearchMap(char* s)
{
	int i;
	for (i = 0; i < VerNum; i++)
		if (strcmp(s, StationID_list[i].stationName) == 0)
			return i;	//返回序号 
	return -1;
}
void dijkstra(int vs, int ve)
{
	int i, j, k, min, tmp;
	int flag[M];      				// flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。
	for (i = 0; i < VerNum; i++)	// 初始化
	{
		flag[i] = 0;              	// 顶点i的最短路径还没获取到。
		prev[i] = vs;             	 // 顶点i的前驱顶点为0。
		dist[i] = map[vs][i].weight;	// 顶点i的最短路径为"顶点vs"到"顶点i"的权。
	}
	dist[vs] = 0, flag[vs] = 1;		// 对"顶点vs"自身进行初始化
	for (i = 0; i < VerNum - 1; i++)	// 遍历1次；每次找出一个顶点的最短路径。
	{								// 寻找当前最小的路径；即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
		min = INF;
		for (j = 0; j < VerNum; j++)
		{
			if (flag[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}
		flag[k] = 1;				// 标记"顶点k"为已经获取到最短路径
		// 修正当前最短路径和前驱顶点:  即当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
		if (k == ve)	return;
		for (j = 0; j < VerNum; j++)
		{
			tmp = (map[k][j].weight == INF ? INF : (min + map[k][j].weight)); // 防止溢出
			if (flag[j] == 0 && (tmp < dist[j]) && map[k][j].lineID > 0)
			{
				dist[j] = tmp;
				prev[j] = k;	//记录前驱 
			}
		}
	}
}
void PrintPath(int v1, int v2)
{
	int i, EdgeLast = v1, pathLen = 1, u = path[top - 1];//i是变量，边的起点，长度，边的终点 
	int lineId = map[EdgeLast][u].lineID;	//开始路线编号 
	printf("%s-%d", StationID_list[v1].stationName, lineId); //打印起点站和起点站的路线 
	EdgeLast = u;
	for (i = top - 2; i >= 0; i--)	//利用栈倒过来寻找 
	{
		u = path[i];	//更新终点 
		if (lineId != map[EdgeLast][u].lineID)	//换乘 
		{
			lineId = map[EdgeLast][u].lineID;
			printf("(%d)-%s-%d", pathLen, StationID_list[EdgeLast].stationName, lineId);
			pathLen = 0;
		}
		pathLen++;		//长度 +1 
		EdgeLast = u;	//更新起点
	}
	printf("(%d)-%s", pathLen, StationID_list[v2].stationName);//打印终点站
}

void menu()//菜单
{
	int select = 0;
	printf("\n\t\t\t++++++++++++++++++++++++\n\t\t\t+  欢迎使用XX登录系统  +\n\t\t\t++++++++++++++++++++++++\n");

	while (now)
	{
		system("cls");
		do
		{
			printf("\n		******************菜单栏*****************\n");
			printf("\t\t*\t      ①登录                    *\n");
			printf("\t\t*\t      ②注册                    *\n");
			printf("\t\t*\t      ③退出系统\t\t*\n");
			printf("		*****************************************\n");
			printf("\n");
			printf("\t\t请输入选项：[\t]\b\b\b");
			scanf("%d", &select);
		} while (select > 5 || select < 1);
		int ret = start(select);
		if (ret) {
			break;
		}
	}
}

int start(int math)//中转
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
		printf("感谢您的支持！\n欢迎下次使用！");
		now = 0;
		exit(0);
	}
}

int zhuce()//注册模块
{
	system("cls");
	char c[20];
	A a, b;
	FILE* fp;
	printf("\n\t\t欢迎来到注册界面！\n");
	Sleep(500);
	fp = fopen("Users.txt", "r");
	fread(&b, sizeof(A), 1, fp);
	printf("\n\t\t请设置账号:[ \t\t ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
			printf("该账号已存在！！！");
			Sleep(1000);
			fclose(fp);
			return 1;
		}
	}
	int time = 2;
	do
	{
		printf("\t\t请设置密码:[ \t\t ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
		printf("\t\t请确认密码：[ \t\t ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
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

			printf("\t\t请输入用户名：");
			scanf("%s", &a.name);
			fp = fopen("Users.txt", "a");
			fwrite(&a, sizeof(A), 1, fp);
			printf("%s,注册成功！！！", a.name);
			fclose(fp);
			Sleep(1500);
			return 0;
		}
		else
		{
			if (time != 0)
			{
				printf("密码错误！\n\n请重新输入密码！！\n\n您还有%d次机会！！！", time);
				time--;
				continue;
			}
			else
			{
				printf("\n\t\t多次输入错误，即将退出！");
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
	printf("欢迎来到登录界面！");
	printf("账号：\n");
	scanf("%s", &b.zh);
	printf("密码：\n");
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
				printf("账号或密码错误！！！\n");
				fclose(fp);
				Sleep(1000);
				system("cls");
				return 0;
			}
		}
	}
	if (strcmp(b.mm, a.mm) == 0)
	{
		printf("%s，欢迎回来！！！\n", a.name);
		fclose(fp);
		Sleep(1000);
		system("cls");
		return 1;
	}
	else
	{
		printf("密码错误！！！\n");
		fclose(fp);
		Sleep(1000);
		system("cls");
		return 0;
	}
}