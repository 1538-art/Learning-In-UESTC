#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include "head.h" 


void control(char a[15][50], int* y, int* ming, int s)  //�ƶ���s!=0���ϣ�s=0����
{
	if (s)
	{
		*y -= 1;  //�ƶ����ǵ�����
		if (a[*y][7] == '#')
		{
			*ming = 0;  //����ǽ�ھ͹���
		}
		a[*y][7] = '*';
		a[*y + 1][7] = ' ';  //����Ϊ*���ƶ���ԭ����λ��Ϊ�ո�
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

	while (r == ' ')  //��Ϸ�����ո��ؿ�
	{
		for (i = 0; i < 14; i++)		// 
			for (j = 0; j < 50; j++)	// 
				a[i][j] = ' ';	//��ʼ����ͼ

		for (i = 0; i < 50; i++)		//
		{
			a[0][i] = '#';		//���컨��
			a[14][i] = '#';		//�̵ذ�
		}

		y = 7;
		a[y][7] = '*';  //��ʼ��λ��
		ming = 1;  //��ʼ������ֵ
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
			printf("\t��ķ�����%d\t��߷�:%d  ", fen, zgfen);  //��ӡ��ͼ�ͷ���
			if (wuhu != 0)
			{
				printf("���ո���Ծ");
			}
			else
			{
				printf("�ߺ�~~~   ");
			}

			if (jump != 0)  //��Ϊ�㣬������һ��
			{
				control(a, &y, &ming, 1);
				jump -= 1;
			}

			if (_kbhit())
			{
				shuru = _getch();
				if (shuru == ' ') //�ո��������Ծ
				{
					jump = 2;
					wuhu = 0;
				}
			}
			else if (step % 2 == 0 && jump == 0)
			{
				control(a, &y, &ming, 0);  //ǰ�������½�һ��
			}

			if (step % 20 == 0)  //ÿ��20��������һ��ǽ
			{
				wall = rand() % (13 - dong) + 2;
				for (i = 1; i < 14; i++)
				{
					if (i < wall || i >= wall + dong)  //�������¿ռ�
					{
						a[i][49] = '#';
					}
					else
					{
						a[i][49] = ' ';
					}
				}
			}

			for (j = 0; j < 50; j++)  //�ƶ�ǽ
			{
				if (a[1][j] == '#')
				{
					if (j == 0)
					{
						for (i = 1; i < 14; i++)  //ǽ�ߵ�ͷ������,��ɿո�
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
							fen += 1;  //ǽ�����˾ͼ�1��
						}

					}
				}
			}

			zgfen = (fen > zgfen) ? fen : zgfen;

			if (step % 90 == 0) //ÿǰ��90����С��
			{
				dong -= 1;
			}

			step += 1;
			Sleep(100);

		}
		system("cls");
		printf("\n\n\t����û�ˣ�����\n\n\t��ķ�����%d\t��߷֣�%d\n\n", fen, zgfen);
		printf("\t���ո���ؿ�");
		printf("\t���������˳�");
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

