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
	//�������
	srand((unsigned)time(NULL));
	//������ͼ
	for (int i = 1; i <= 998; i++)
		for (int j = 1; j <= 998; j++)
			boom[i][j] = ' ', surface[i][j] = '.';
	//ִ�в���
	while (action != 1 && action != 2 && action != 3 && action != 4) {
		//�����ʾ
		printf("1������(20X20,80����)\n");
		printf("2���м�(40X40,480����)\n");
		printf("3���߼�(80X80,2560����)\n");
		//printf("4���Զ���\n");
		//printf("5��ͼ��\n");
		printf("������ģʽ��ţ�");
		scanf("%d", &action);
		//�ж�
		if (action == 1)
			m = 20, n = 20, totalBoomCount = 80;
		else if (action == 2)
			m = 40, n = 40, totalBoomCount = 480;
		else if (action == 3)
			m = 80, n = 80, totalBoomCount = 2560;
		/*else if (action == 4) {
			printf("����������(9-30)��");
			scanf("%d", &m);
			if (m > 30)
				m = 30;
			else if (m < 9)
				m = 9;
			printf("����������(9-16)��");
			scanf("%d", &n);
			if (n > 16)
				n = 16;
			else if (n < 9)
				n = 9;
			printf("����������(10-99)��");
			scanf("%d", &totalBoomCount);
			if (totalBoomCount > 99)
				totalBoomCount = 99;
			else if (totalBoomCount < 10)
				totalBoomCount = 10;
			if (totalBoomCount == n * m)
				totalBoomCount--;
		}
		else if (action == 5) {
			printf("������...\n\n");
			system("cls");
			printf("\".\"-->�˸���δ�������\n");
			printf("\"*\"-->��\n");
			printf("\" \"-->��\n");
			printf("\"&\"-->�����Ϊ��\n");
			printf("\"?\"-->�����Ϊ��֪��\n\n\n");
			Sleep(3000);
		}*/
		else {
			printf("\n��������\n���������룡");
			Sleep(500);
			system("cls");
		}
	}
	//��ʼ��
	printf("������...\n\n");
	currentBoomCount = totalBoomCount;
	system("cls");
	printf(" %d X %d , %d ����\n", m, n, totalBoomCount);
	//���ɵ���
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
	//��������
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			number[i][j] = num(i, j);
	}
	//���ɵ�ͼ
	while (1) {
		printf("ʣ��%d����\n\n", currentBoomCount);
		printf("    ");
		for (int i = 1; i <= m; i++)
			printf("%d ", i / 100);
		printf("\n    ");
		for (int i = 1; i <= m; i++)
			printf("%d ", i % 100 / 10);
		printf("\n    ");
		for (int i = 1; i <= m; i++)
			printf("%d ", i % 100 % 10);
		printf("\n   ��");
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
			printf("\n\n������5����Զ��ر�\r");
			for (int i = 5; i >= 0; i--) {
				Sleep(1000);
				printf("������%d����Զ��ر�\r", i);
			}
			Sleep(100);
			return 0;
		}
		//�������
		printf("\n\n");
		int x = 1000, y = 1000;
		printf("��0���������к���\n");
		while (x > n || x < 1) {
		flag:
			printf("��������в������У�");
			scanf("%d", &x);
			if (x > n || x < 1)
				if (x == 0)
					goto flag;
				else
					printf("���������룡\n");
		}
		while (y > m || y < 1) {
			printf("��������в������У�");
			scanf("%d", &y);
			if (y > m || y < 1)
				if (y == 0)
					goto flag;
				else
					printf("���������룡\n");
		}
		action = 0;
		while (action != 1 && action != 2 && action != 3) {
			printf("��ѡ����еĲ�����\n1��̽��\n2������\n3�����Ϊ��ȷ��\n���������");
			scanf("%d", &action);
			if (action != 1 && action != 2 && action != 3)
				printf("���������룡\n");
		}
		//�����ж�

		//ѡ��̽��
		if (action == 1) {
			//��ԭ���
			if (surface[x][y] == '&')
				currentBoomCount++;
			surface[x][y] = ' ';
			system("cls");
			//����
			if (boom[x][y] == '*') {
				printf("��Ϸ����\n��ϲ���ȵ����ˣ�\n\n");
				gameOver = true;
				continue;
			}
			//δ����
			else
				usedSquareCount++;
			//ʤ��
			if (n * m - usedSquareCount == totalBoomCount) {
				printf("��Ϸ����\n��ϲ�������������ף�\n\n");
				currentBoomCount = 0;
				gameOver = true;
				continue;
			}
			//�����ͼ
			if (number[x][y] == 0) {
				mapChange(x, y);
			}
		}
		//ѡ����
		else if (action == 2) {
			//���
			surface[x][y] = '&';
			system("cls");
			currentBoomCount--;
			//�ж��Ƿ�����ȷ
			if (boom[x][y] == '*')
				markCount++;
			//�ж��Ƿ�����
			if (markCount == totalBoomCount) {
				printf("��Ϸ����\n��ϲ�������������ף�\n\n");
				currentBoomCount = 0;
				gameOver = true;
				continue;
			}
		}
		//ѡ��δ֪
		else if (action == 3) {
			//��ԭ���
			if (surface[x][y] == '&')
			{
				currentBoomCount++;
				if (boom[x][y] == '*')
					markCount--;
			}
			//���
			surface[x][y] = '?';
			system("cls");
		}
	}
	return 0;
}
