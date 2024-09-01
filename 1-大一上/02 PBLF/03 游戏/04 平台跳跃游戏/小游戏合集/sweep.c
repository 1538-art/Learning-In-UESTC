#include<cstdio>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include <stdlib.h> 
#include "head.h"

using namespace std;
char boom[999][999], surface[999][999];
int number[999][999];
int m, n, totalBoomCount, action = -1, markCount, usedSquareCount, currentBoomCount;
bool gameOver = false;
void mapChange(int x, int y) {
	if (boom[x][y] == '*')
		return;
	if (x - 1 != 0 && y - 1 != 0)
		if (surface[x - 1][y - 1] == '.') {
			usedSquareCount++;
			surface[x - 1][y - 1] = ' ';
			if (number[x - 1][y - 1] == 0)
				mapChange(x - 1, y - 1);
		}
	if (x - 1 != 0)
		if (surface[x - 1][y] == '.') {
			usedSquareCount++;
			surface[x - 1][y] = ' ';
			if (number[x - 1][y] == 0)
				mapChange(x - 1, y);
		}
	if (x - 1 != 0 && y != m)
		if (surface[x - 1][y - 1] == '.') {
			usedSquareCount++;
			surface[x - 1][y - 1] = ' ';
			if (number[x - 1][y - 1] == 0)
				mapChange(x - 1, y - 1);
		}
	if (y - 1 != 0)
		if (surface[x][y - 1] == '.') {
			usedSquareCount++;
			surface[x][y - 1] = ' ';
			if (number[x][y - 1] == 0)
				mapChange(x, y - 1);
		}
	if (y != m)
		if (surface[x][y + 1] == '.') {
			usedSquareCount++;
			surface[x][y + 1] = ' ';
			if (number[x][y + 1] == 0)
				mapChange(x, y + 1);
		}
	if (x != n && y - 1 != 0)
		if (surface[x + 1][y - 1] == '.') {
			usedSquareCount++;
			surface[x + 1][y - 1] = ' ';
			if (number[x + 1][y - 1] == 0)
				mapChange(x + 1, y - 1);
		}
	if (x != n)
		if (surface[x + 1][y] == '.') {
			usedSquareCount++;
			surface[x + 1][y] = ' ';
			if (number[x + 1][y] == 0)
				mapChange(x + 1, y);
		}
	if (x != n && y != m)
		if (surface[x + 1][y + 1] == '.') {
			usedSquareCount++;
			surface[x + 1][y + 1] = ' ';
			if (number[x + 1][y + 1] == 0)
				mapChange(x + 1, y + 1);
		}
}
int num(int x, int y) {
	if (boom[x][y] == '*')
		return 0;
	int boomCount = 0;
	if (x - 1 != 0 && y - 1 != 0)
		if (boom[x - 1][y - 1] == '*')
			boomCount++;
	if (x - 1 != 0)
		if (boom[x - 1][y] == '*')
			boomCount++;
	if (x - 1 != 0 && y != m)
		if (boom[x - 1][y + 1] == '*')
			boomCount++;
	if (y - 1 != 0)
		if (boom[x][y - 1] == '*')
			boomCount++;
	if (y != m)
		if (boom[x][y + 1] == '*')
			boomCount++;
	if (x != n && y - 1 != 0)
		if (boom[x + 1][y - 1] == '*')
			boomCount++;
	if (x != n)
		if (boom[x + 1][y] == '*')
			boomCount++;
	if (x != n && y != m)
		if (boom[x + 1][y + 1] == '*')
			boomCount++;
	return boomCount;
}
int sweep() {
	system("cls");
	//随机种子
	srand((unsigned)time(NULL));
	//构建地图
	for (int i = 1; i <= 998; i++)
		for (int j = 1; j <= 998; j++)
			boom[i][j] = ' ', surface[i][j] = '.';
	//执行操作
	while (action != 1 && action != 2 && action != 3 && action != 4) {
		//输出提示
		printf("1、初级(20X20,80颗雷)\n");
		printf("2、中级(40X40,480颗雷)\n");
		printf("3、高级(80X80,2560颗雷)\n");
		//printf("4、自定义\n");
		//printf("5、图例\n");
		printf("请输入模式编号：");
		scanf("%d", &action);
		//判定
		if (action == 1)
			m = 20, n = 20, totalBoomCount = 80;
		else if (action == 2)
			m = 40, n = 40, totalBoomCount = 480;
		else if (action == 3)
			m = 80, n = 80, totalBoomCount = 2560;
		/*else if (action == 4) {
			printf("请输入列数(9-30)：");
			scanf("%d", &m);
			if (m > 30)
				m = 30;
			else if (m < 9)
				m = 9;
			printf("请输入行数(9-16)：");
			scanf("%d", &n);
			if (n > 16)
				n = 16;
			else if (n < 9)
				n = 9;
			printf("请输入雷数(10-99)：");
			scanf("%d", &totalBoomCount);
			if (totalBoomCount > 99)
				totalBoomCount = 99;
			else if (totalBoomCount < 10)
				totalBoomCount = 10;
			if (totalBoomCount == n * m)
				totalBoomCount--;
		}
		else if (action == 5) {
			printf("加载中...\n\n");
			system("cls");
			printf("\".\"-->此格子未被点击过\n");
			printf("\"*\"-->雷\n");
			printf("\" \"-->空\n");
			printf("\"&\"-->被标记为雷\n");
			printf("\"?\"-->被标记为不知道\n\n\n");
			Sleep(3000);
		}*/
		else {
			printf("\n输入有误\n请重新输入！");
			Sleep(500);
			system("cls");
		}
	}
	//初始化
	printf("加载中...\n\n");
	currentBoomCount = totalBoomCount;
	system("cls");
	printf(" %d X %d , %d 颗雷\n", m, n, totalBoomCount);
	//生成地雷
	for (int i = 1; i <= totalBoomCount; i++) {
		int x, y;
		x = rand() % n;
		if (x == 0)
			x = n;
		y = rand() % m;
		if (y == 0)
			y = m;
		if (boom[x][y] == '*')
			i--;
		boom[x][y] = '*';
	}
	//数字生成
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			number[i][j] = num(i, j);
	}
	//生成地图
	while (1) {
		printf("剩余%d颗雷\n\n", currentBoomCount);
		printf("    ");
		for (int i = 1; i <= m; i++)
			printf("%d ", i / 100);
		printf("\n    ");
		for (int i = 1; i <= m; i++)
			printf("%d ", i % 100 / 10);
		printf("\n    ");
		for (int i = 1; i <= m; i++)
			printf("%d ", i % 100 % 10);
		printf("\n   ┍");
		for (int i = 1; i <= m; i++)
			printf("--");
		printf("\n");
		for (int i = 1; i <= n; i++) {
			printf("%03d|", i);
			for (int j = 1; j <= m; j++) {
				if (gameOver == 1) {
					printf("%c|", boom[i][j]);
					continue;
				}
				if (surface[i][j] == '.' || surface[i][j] == '?' || surface[i][j] == '&')
					printf("%c|", surface[i][j]);
				else if (number[i][j] != 0)
					printf("%d|", number[i][j]);
				else
					printf("%c|", boom[i][j]);
			}
			printf("\n   |");
			for (int i = 1; i <= m; i++)
				printf("--");
			printf("\n");
		}
		if (gameOver) {
			printf("\n\n窗口在5秒后自动关闭\r");
			for (int i = 5; i >= 0; i--) {
				Sleep(1000);
				printf("窗口在%d秒后自动关闭\r", i);
			}
			Sleep(100);
			return 0;
		}
		//玩家输入
		printf("\n\n");
		int x = 1000, y = 1000;
		printf("按0重新输入行和列\n");
		while (x > n || x < 1) {
		flag:
			printf("请输入进行操作的行：");
			scanf("%d", &x);
			if (x > n || x < 1)
				if (x == 0)
					goto flag;
				else
					printf("请重新输入！\n");
		}
		while (y > m || y < 1) {
			printf("请输入进行操作的列：");
			scanf("%d", &y);
			if (y > m || y < 1)
				if (y == 0)
					goto flag;
				else
					printf("请重新输入！\n");
		}
		action = 0;
		while (action != 1 && action != 2 && action != 3) {
			printf("请选择进行的操作：\n1、探查\n2、排雷\n3、标记为不确定\n输入操作：");
			scanf("%d", &action);
			if (action != 1 && action != 2 && action != 3)
				printf("请重新输入！\n");
		}
		//输入判断

		//选择探查
		if (action == 1) {
			//复原标记
			if (surface[x][y] == '&')
				currentBoomCount++;
			surface[x][y] = ' ';
			system("cls");
			//踩雷
			if (boom[x][y] == '*') {
				printf("游戏结束\n恭喜您踩到雷了！\n\n");
				gameOver = true;
				continue;
			}
			//未踩雷
			else
				usedSquareCount++;
			//胜利
			if (n * m - usedSquareCount == totalBoomCount) {
				printf("游戏结束\n恭喜您排完了所有雷！\n\n");
				currentBoomCount = 0;
				gameOver = true;
				continue;
			}
			//处理地图
			if (number[x][y] == 0) {
				mapChange(x, y);
			}
		}
		//选择标记
		else if (action == 2) {
			//标记
			surface[x][y] = '&';
			system("cls");
			currentBoomCount--;
			//判断是否标记正确
			if (boom[x][y] == '*')
				markCount++;
			//判断是否标记完
			if (markCount == totalBoomCount) {
				printf("游戏结束\n恭喜您排完了所有雷！\n\n");
				currentBoomCount = 0;
				gameOver = true;
				continue;
			}
		}
		//选择未知
		else if (action == 3) {
			//复原标记
			if (surface[x][y] == '&')
			{
				currentBoomCount++;
				if (boom[x][y] == '*')
					markCount--;
			}
			//标记
			surface[x][y] = '?';
			system("cls");
		}
	}
	return 0;
}
