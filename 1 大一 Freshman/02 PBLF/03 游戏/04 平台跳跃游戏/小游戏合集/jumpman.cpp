#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include "head.h" 


void control(char a[15][50], int* y, int* ming, int s)  //移动，s!=0向上，s=0向下
{
	if (s)
	{
		*y -= 1;  //移动主角的坐标
		if (a[*y][7] == '#')
		{
			*ming = 0;  //碰到墙壁就挂了
		}
		a[*y][7] = '*';
		a[*y + 1][7] = ' ';  //主角为*，移动后原来的位置为空格
	}
	else
	{
		*y += 1;
		if (a[*y][7] == '#')
		{
			*ming = 0;
		}
		a[*y][7] = '*';
		a[*y - 1][7] = ' ';
	}
}
int jumpman()
{system("cls");
	system("mode con cols=50 lines=16");
	system("title jump man");


	int dong = 7, ming, step = 1, i, j, y, jump = 0, fen = 0, wall = 0, zgfen = 0, wuhu;
	char a[15][50];
	char shuru, r = ' ';

	while (r == ' ')  //游戏结束空格重开
	{
		for (i = 0; i < 14; i++)		// 
			for (j = 0; j < 50; j++)	// 
				a[i][j] = ' ';	//初始化地图

		for (i = 0; i < 50; i++)		//
		{
			a[0][i] = '#';		//铺天花板
			a[14][i] = '#';		//铺地板
		}

		y = 7;
		a[y][7] = '*';  //初始化位置
		ming = 1;  //初始化生命值
		fen = 0;
		wuhu = 1;
		dong = 7;

		while (ming)
		{
			system("cls");
			for (i = 0; i < 15; i++)
			{
				for (j = 0; j < 50; j++)
				{
					putchar(a[i][j]);
				}
				putchar(10);
			}
			printf("\t你的分数：%d\t最高分:%d  ", fen, zgfen);  //打印地图和分数
			if (wuhu != 0)
			{
				printf("按空格跳跃");
			}
			else
			{
				printf("芜湖~~~   ");
			}

			if (jump != 0)  //不为零，向上跳一格
			{
				control(a, &y, &ming, 1);
				jump -= 1;
			}

			if (_kbhit())
			{
				shuru = _getch();
				if (shuru == ' ') //空格键向上跳跃
				{
					jump = 2;
					wuhu = 0;
				}
			}
			else if (step % 2 == 0 && jump == 0)
			{
				control(a, &y, &ming, 0);  //前进两格下降一格
			}

			if (step % 20 == 0)  //每走20步，生成一道墙
			{
				wall = rand() % (13 - dong) + 2;
				for (i = 1; i < 14; i++)
				{
					if (i < wall || i >= wall + dong)  //给洞留下空间
					{
						a[i][49] = '#';
					}
					else
					{
						a[i][49] = ' ';
					}
				}
			}

			for (j = 0; j < 50; j++)  //移动墙
			{
				if (a[1][j] == '#')
				{
					if (j == 0)
					{
						for (i = 1; i < 14; i++)  //墙走到头就消掉,变成空格
						{
							a[i][j] = ' ';
						}
					}
					else
					{
						for (i = 1; i < 14; i++)
						{
							if (a[i][j] == '#')
							{
								a[i][j - 1] = '#';
								a[i][j] = ' ';
							}
						}
						if (j == 7)
						{
							fen += 1;  //墙经过人就加1分
						}

					}
				}
			}

			zgfen = (fen > zgfen) ? fen : zgfen;

			if (step % 90 == 0) //每前进90格缩小洞
			{
				dong -= 1;
			}

			step += 1;
			Sleep(100);

		}
		system("cls");
		printf("\n\n\t你人没了！！！\n\n\t你的分数：%d\t最高分：%d\n\n", fen, zgfen);
		printf("\t按空格键重开");
		printf("\t按其他键退出");
		r = _getch();
	}
	while (r != ' ')
	{
		system("cls");
	    return zgfen;
	
	}
	system("cls");
	return zgfen;
}

