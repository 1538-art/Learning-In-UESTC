#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#define size 10000  //蛇长度
#define Width 600
#define Length 880 //绘图框长度

#define LAZY_head "head.jpg"
#define BEAUTY_HEAD "beauty_head.jpg"
#define STR_HEAD "str_head.jpg"
#define UI "界面.jpg"
#define HELP_UI "游戏说明.jpg"
#define BACK_1 "back.jpg"
#define GREY "grey.jpg"
#define GRASS "grass.jpg"
#define CAKE "cake.jpg"
double seconds = 0.0;
double seconds2 = 0.0;
int seconds3 = 0, seconds4 = 0, seconds5 = 0;
int count = 1;
int grade = 0;
TCHAR result[1000];



//1.数据分析：基本数据成员分析
//坐标属性，蛇属性，食物属性

//坐标属性
typedef struct pointXY
{
	int x;
	int y;
}MYPOINT;


//蛇属性
struct Snake
{
	int num;//蛇的节数
	MYPOINT xy[size]; //蛇最多有100节
	char direction;//蛇的方向
	IMAGE head;
};

struct enemy
{
	MYPOINT enxy;
	int flag = 0;
};//敌人属性

struct poison {
	MYPOINT poxy;
	int flag = 0;
};

struct antidote {
	MYPOINT anxy;
	int flag = 0;
};//解药

//食物的属性
struct Food
{
	MYPOINT fdxy;
	int eatgrade = 0;//吃食物的分数
	int flag = 0;//食物是否存在，0表示存在，1表示不存在
};

struct bigfood
{
	MYPOINT bigfd;
	int flag = 0;//大食物是否存在
};

//方向
enum movedirection { right = 77, left = 75, down = 80, up = 72 };

enum headskin { BEAUTY = 0, LAZY = 1, STR = 2 };

//主窗口
static HWND hwnd = NULL;

struct obstacle {
	int length;
	MYPOINT xy[20];
}obstacle_1, obstacle_2, obstacle_3, obstacle_4, * obs_1, * obs_2, * obs_3, * obs_4;//障碍属性

void deadpoison(struct poison* poison1, struct poison* poison2, struct Snake* snake) {
	if (poison1->poxy.x <= snake->xy[0].x && poison1->poxy.x + 70 > snake->xy[0].x) {
		if (poison1->poxy.y <= snake->xy[0].y && poison1->poxy.y + 70 > snake->xy[0].y)
			snake->num += 2;
	}
	if (poison2->poxy.x <= snake->xy[0].x && poison2->poxy.x + 70 > snake->xy[0].x) {
		if (poison2->poxy.y <= snake->xy[0].y && poison2->poxy.y + 70 > snake->xy[0].y)
			snake->num += 2;
	}
}
void drawantidote(struct antidote* anti) {
	setlinecolor(BLACK);//矩形边框线的颜色
	setfillcolor(RGB(255, 192, 203));
	fillrectangle(anti->anxy.x, anti->anxy.y, anti->anxy.x + 10, anti->anxy.y + 10);
}
void drawbigfood(struct bigfood* bigfd) {
	IMAGE straw;
	loadimage(&straw, _T(CAKE));
	putimage(bigfd->bigfd.x, bigfd->bigfd.y, &straw);
}
void drawenemy(struct enemy* enemy) {
	IMAGE straw;
	loadimage(&straw, _T(GREY));
	putimage(enemy->enxy.x, enemy->enxy.y, &straw);
}
void drawfood(struct Food* food) {
	IMAGE straw;
	loadimage(&straw, _T(GRASS));
	putimage(food->fdxy.x, food->fdxy.y, &straw);
}
void drawobstacle_1(struct obstacle* obs_1, struct obstacle* obs_2) {
	setfillcolor(RED);
	setlinecolor(YELLOW);

	for (int i = 0; i < obs_1->length; i++)
	{

		fillrectangle(obs_1->xy[i].x, obs_1->xy[i].y, obs_1->xy[i].x + 30, obs_1->xy[i].y + 20);
		fillrectangle(obs_2->xy[i].x, obs_2->xy[i].y, obs_2->xy[i].x + 30, obs_2->xy[i].y + 20);
	}

}
void drawobstacle_2(struct obstacle* obs_3, struct obstacle* obs_4) {
	setfillcolor(RED);
	setlinecolor(YELLOW);

	for (int i = 0; i < obs_3->length; i++)
	{

		fillrectangle(obs_3->xy[i].x, obs_3->xy[i].y, obs_3->xy[i].x + 30, obs_3->xy[i].y + 20);
		fillrectangle(obs_4->xy[i].x, obs_4->xy[i].y, obs_4->xy[i].x + 30, obs_4->xy[i].y + 20);
	}

}
void drawpoison(struct poison* poison1, struct poison* poison2) {
	setlinecolor(BLACK);//矩形边框线的颜色
	setfillcolor(RGB(220, 208, 255));
	fillrectangle(poison1->poxy.x, poison1->poxy.y, poison1->poxy.x + 70, poison1->poxy.y + 70);
	fillrectangle(poison2->poxy.x, poison2->poxy.y, poison2->poxy.x + 70, poison2->poxy.y + 70);
}
void eatantidote(struct antidote* anti, struct Snake* snake, struct enemy* enemy) {
	if (snake->xy[0].x == anti->anxy.x && snake->xy[0].y == anti->anxy.y) {
		anti->flag = 0;
		anti->anxy.x = -20;
		anti->anxy.y = -20;
		snake->num -= 2;
	}
	if (enemy->enxy.x <= anti->anxy.x && enemy->enxy.x + 40 > anti->anxy.x) {
		if (enemy->enxy.y <= anti->anxy.y && enemy->enxy.y + 40 > anti->anxy.y) {
			anti->flag = 0;
			anti->anxy.x = -20;
			anti->anxy.y = -20;
		}
	}
}
void eatbigfood(struct bigfood* bigfood, struct Snake* snake, int* eatgrade) {
	if (bigfood->flag == 1) {
		seconds += 0.1;
		if (snake->xy[0].x >= bigfood->bigfd.x && snake->xy[0].y >= bigfood->bigfd.y) {
			if (snake->xy[0].x <= bigfood->bigfd.x + 10 && snake->xy[0].y <= bigfood->bigfd.y + 10) {
				snake->num += 1;
				bigfood->flag = 0;
				bigfood->bigfd.x = -20;
				bigfood->bigfd.y = -20;
				*eatgrade += 4;
				seconds = 0.0;
				count += 1;
			}
		}
		if (seconds >= 8.0) {
			bigfood->bigfd.x = -20;
			bigfood->bigfd.y = -20;
			if (snake->num % 6 == 5) {
				bigfood->flag = 0;
				seconds = 0.0;
			}
		}
	}
}//判断是否吃大食物
void eatfood(struct Food* food, struct Snake* snake, int* eatgrade) {
	if (snake->xy[0].x == food->fdxy.x && snake->xy[0].y == food->fdxy.y)
	{
		snake->num += 1;
		food->flag = 0;
		*eatgrade += 1;
		count += 1;
	    
	}
}//判断是否吃食物

void countnum(struct obstacle* obs_1, struct obstacle* obs_2,struct obstacle* obs_3, struct obstacle* obs_4) {
	if (count <= 10) {
		obs_1->length = count;
		obs_2->length = count;
	}
	else if (count > 10 && count < 17) {
		obs_3->length = count - 10;
		obs_4->length = count - 10;
		obs_1->length = count;
		obs_2->length = count;
	}
	else if (count >= 17 && count <= 22) {
		obs_3->length = count - 10;
		obs_4->length = count - 10;
	}
}

void effect_init(int skin) {
	if (skin == LAZY)
	{
		mciSendString("open 幸福的生活.mp3 alias effect_1", NULL, 0, NULL);
		mciSendString("open 吃西瓜.mp3 alias effect_2", NULL, 0, NULL);
		mciSendString("open 谁来背背我.mp3 alias effect_3", NULL, 0, NULL);
		mciSendString("open 好朋友.mp3 alias effect_4", NULL, 0, NULL);
	}
	if (skin == BEAUTY)
	{
		mciSendString("open beauty1贪嘴.mp3 alias effect_1", NULL, 0, NULL);
		mciSendString("open beauty2你没事吧.mp3 alias effect_2", NULL, 0, NULL);
		mciSendString("open beauty2斯文一点.mp3 alias effect_3", NULL, 0, NULL);
		mciSendString("open 阿里嘎多美羊羊.mp3 alias effect_4", NULL, 0, NULL);
	}
	if (skin == STR)
	{
		mciSendString("open str_1.mp3 alias effect_1", NULL, 0, NULL);
		mciSendString("open str_2.mp3 alias effect_2", NULL, 0, NULL);
		mciSendString("open str_3.mp3 alias effect_3", NULL, 0, NULL);
		mciSendString("open str_4斯文一点.mp3 alias effect_4", NULL, 0, NULL);
	}
}
void effect_judge(int mark) {
	if (mark >= 5)
		mciSendString("play effect_1", NULL, 0, NULL);
	if (mark >= 10)
		mciSendString("play effect_2", NULL, 0, NULL);
	if (mark >= 15)
		mciSendString("play effect_3", NULL, 0, NULL);
	if (mark >= 20)
		mciSendString("play effect_4", NULL, 0, NULL);
}
void existenemy(struct enemy* enemy) {
	if (enemy->flag == 0) {
		seconds2 += 0.1;
		if (seconds2 >= 5.0) {
			enemy->flag = 1;
			enemy->enxy.x = 0;
			enemy->enxy.y = 0;
		}
	}
}
void existpoison(struct poison* poison1, struct poison* poison2) {
	if (poison1->flag == 1) {
		seconds4 += 1;
		if (seconds4 % 50 == 0) {
			poison1->flag = 0;
			poison1->poxy.x = -80;
			poison1->poxy.y = -80;
			poison2->flag = 0;
			poison2->poxy.x = -80;
			poison2->poxy.y = -80;
			seconds4 = 0;
		}
	}
}

bool foodhitobstacle(struct Food* food,struct obstacle* obs_1,struct obstacle*obs_2, struct obstacle* obs_3,struct obstacle* obs_4)
{
	if (food->fdxy.x >= -10 && food->fdxy.x <= 550 && food->fdxy.y >= 380 && food->fdxy.y <= 440)
		return true;
	else if (food->fdxy.x <= 890 && food->fdxy.x >= 300 && food->fdxy.y >= 190 && food->fdxy.y <= 230)
		return true;
	else if (food->fdxy.x >= 180 && food->fdxy.x <= 250 && food->fdxy.y >= -10 && food->fdxy.y <= 250)
		return true;
	else if (food->fdxy.x >= 590 && food->fdxy.x <= 650 && food->fdxy.y <= Width + 10 && food->fdxy.y >= 350)
		return true;
	else  return false;
}
bool bigfoodhitobstacle(struct bigfood* bigfood, struct obstacle* obs_1, struct obstacle* obs_2, struct obstacle* obs_3, struct obstacle* obs_4)
{

	 
	if (bigfood->bigfd.x + 10 >= -10 && bigfood->bigfd.x <= 560 && bigfood->bigfd.y + 10 >= 370 && bigfood->bigfd.y <= 450)
		return true;
	else if (bigfood->bigfd.x + 10 <= 890 && bigfood->bigfd.x >=290 && bigfood->bigfd.y + 10 >= 180 && bigfood->bigfd.y <= 240)
		return true;
	else if (bigfood->bigfd.x + 10 >= 180 && bigfood->bigfd.x <= 260 && bigfood->bigfd.y + 10 >= -10 && bigfood->bigfd.y <= 260)
		return true;
	else if (bigfood->bigfd.x + 10 >= 580 && bigfood->bigfd.x + 10 <= 660 && bigfood->bigfd.y + 10 <= Width + 10 && bigfood->bigfd.y >= 340)
		return true;
	else return false;

}
bool antidotehitobstacle(struct antidote* anti, struct obstacle* obs_1, struct obstacle* obs_2, struct obstacle* obs_3, struct obstacle* obs_4) {
	if (anti->anxy.x >= -10 && anti->anxy.x < 550 && anti->anxy.y >= 380 && anti->anxy.y <= 440)
		return true;
	else if (anti->anxy.x <= 890 && anti->anxy.x > 300 && anti->anxy.y >= 190 && anti->anxy.y <= 230)
		return true;
	else if (anti->anxy.x >= 180 && anti->anxy.x <= 250 && anti->anxy.y >= -10 && anti->anxy.y <= 250)
		return true;
	else if (anti->anxy.x >= 590 && anti->anxy.x <= 650 && anti->anxy.y <= Width + 10 && anti->anxy.y >= 350)
		return true;
	else return false;
}
void help()
{
	IMAGE help;
	loadimage(&help, _T(HELP_UI));//图片形式展出
	putimage(0, 0, &help);
}
bool hitwall(struct Snake* snake) {
	if (snake->xy[0].x > Length - 10 || snake->xy[0].x < 0 || snake->xy[0].y > Width - 10 || snake->xy[0].y < 0)
	{
		HWND hnd = GetHWnd();//获取窗口句柄
		SetWindowText(hnd, "欢迎");//设置窗口标题 第一个参数传入窗口句柄第二个参数设置字符串
		MessageBox(NULL, "撞墙", "提示", MB_OKCANCEL);

		return true;
	}
	else return false;
}
void initantidote(struct antidote* anti, struct Food* food, struct Snake* snake, struct bigfood* bigfood, struct enemy* enemy,
	struct obstacle* obs_1, struct obstacle* obs_2, struct obstacle* obs_3, struct obstacle* obs_4) {
	if (anti->flag == 0) {
		seconds5 += 1;
		if (seconds5 != 0 && seconds5 % 400 == 0) {
			anti->anxy.x = rand() % (Length / 10) * 10;
			anti->anxy.y = rand() % (Width / 10) * 10;
			anti->flag = 1;
			for (int i = 0; i <= snake->num; i++) {
				if (anti->anxy.x == snake->xy[i].x && anti->anxy.y == snake->xy[i].y) {
					anti->anxy.x = rand() % (Length / 10) * 10;
					anti->anxy.y = rand() % (Width / 10) * 10;
				}
				else if (anti->anxy.x >= bigfood->bigfd.x && anti->anxy.y >= bigfood->bigfd.y) {
					if (anti->anxy.x <= bigfood->bigfd.x + 10 && anti->anxy.y <= bigfood->bigfd.y + 10) {
						anti->anxy.x = rand() % (Length / 10) * 10;
						anti->anxy.y = rand() % (Width / 10) * 10;
					}
				}
				else if (anti->anxy.x == food->fdxy.x && anti->anxy.y == food->fdxy.y) {
					anti->anxy.x = rand() % (Length / 10) * 10;
					anti->anxy.y = rand() % (Width / 10) * 10;
				}
				else if (anti->anxy.x >= enemy->enxy.x && anti->anxy.y >= enemy->enxy.y) {
					if (anti->anxy.x <= enemy->enxy.x + 30 && anti->anxy.y <= enemy->enxy.y + 30) {
						anti->anxy.x = rand() % (Length / 10) * 10;
						anti->anxy.y = rand() % (Width / 10) * 10;
					}
				}
				else while (antidotehitobstacle(anti, obs_1, obs_2, obs_3, obs_4)) {
					anti->anxy.x = rand() % (Length / 10) * 10;
					anti->anxy.y = rand() % (Width / 10) * 10;
				}
			}
		}
	}
}
void initbigfood(struct Food* food, struct Snake* snake, struct bigfood* bigfood, struct antidote* anti,
	struct obstacle* obs_1, struct obstacle* obs_2, struct obstacle* obs_3, struct obstacle* obs_4) {
	if (snake->num % 6 == 0 && bigfood->flag == 0)
	{
		bigfood->bigfd.x = rand() % (Length / 10) * 10;
		bigfood->bigfd.y = rand() % (Width / 10) * 10;
		bigfood->flag = 1;
		for (int i = 0; i <= snake->num; i++)
		{
			if (bigfood->bigfd.x <= snake->xy[i].x && bigfood->bigfd.y <= snake->xy[i].y)
			{
				if (bigfood->bigfd.x + 10 >= snake->xy[i].x && bigfood->bigfd.y + 10 >= snake->xy[i].y)
				{
					bigfood->bigfd.x = rand() % (Length / 10) * 10;
					bigfood->bigfd.y = rand() % (Width / 10) * 10;

				}//如果大食物出现在蛇身上，重新产生坐标
			}
			else if (bigfood->bigfd.x <= food->fdxy.x && bigfood->bigfd.y <= food->fdxy.y)
			{
				if (bigfood->bigfd.x + 10 >= food->fdxy.x && bigfood->bigfd.y + 10 >= food->fdxy.y)
				{
					bigfood->bigfd.x = rand() % (Length / 10) * 10;
					bigfood->bigfd.y = rand() % (Width / 10) * 10;
				}//如果大食物出现在食物上，重新产生坐标
			}
			else if (bigfood->bigfd.x <= anti->anxy.x && bigfood->bigfd.y <= anti->anxy.y)
			{
				if (bigfood->bigfd.x + 10 >= anti->anxy.x && bigfood->bigfd.y + 10 >= anti->anxy.y)
				{
					bigfood->bigfd.x = rand() % (Length / 10) * 10;
					bigfood->bigfd.y = rand() % (Width / 10) * 10;
				}
			}//
			else while (bigfoodhitobstacle(bigfood, obs_1, obs_2, obs_3, obs_4))
			{

				bigfood->bigfd.x = rand() % (Length / 10) * 10;
				bigfood->bigfd.y = rand() % (Width / 10) * 10;

			}
		}
	}
}//初始化大食物
void initenemy(struct enemy* enemy) {
	enemy->enxy.x = -40;
	enemy->enxy.y = -40;
}
void initFood(struct Food* food, struct Snake* snake, struct bigfood* bigfood, struct antidote* anti,
	struct obstacle* obs_1, struct obstacle* obs_2, struct obstacle* obs_3, struct obstacle* obs_4) {
	if (food->flag == 0) {
		food->fdxy.x = rand() % (Length / 10) * 10;
		food->fdxy.y = rand() % (Width / 10) * 10;
		food->flag = 1;
		for (int i = 0; i <= snake->num; i++)
		{
			if (food->fdxy.x == snake->xy[i].x && food->fdxy.y == snake->xy[i].y)
			{
				food->fdxy.x = rand() % (Length / 10) * 10;
				food->fdxy.y = rand() % (Width / 10) * 10;
			}//如果食物出现在蛇身上，重新产生坐标
			else if (food->fdxy.x >= bigfood->bigfd.x && food->fdxy.y >= bigfood->bigfd.y)
			{
				if (food->fdxy.x <= bigfood->bigfd.x + 10 && food->fdxy.y <= bigfood->bigfd.y + 10)
				{
					food->fdxy.x = rand() % (Length / 10) * 10;
					food->fdxy.y = rand() % (Width / 10) * 10;
				}
			}//如果食物出现在大食物上，重新产生坐标
			else if (food->fdxy.x == anti->anxy.x && food->fdxy.y == anti->anxy.y) {
				food->fdxy.x = rand() % (Length / 10) * 10;
				food->fdxy.y = rand() % (Width / 10) * 10;
			}//
			else while (foodhitobstacle(food, obs_1, obs_2, obs_3, obs_4))
			{   
				food->fdxy.x = rand() % (Length / 10) * 10;
				food->fdxy.y = rand() % (Width / 10) * 10;

			}
		}
	}
}//初始化食物
struct obstacle* initobstacle_1(struct obstacle obstacle_1) {
	obs_1 = &obstacle_1;
	obs_1->length = 1;
	obs_1->xy[0].x = 0;
	obs_1->xy[0].y = 400;
	for (int i = 1; i < 17; i++)
	{
		obs_1->xy[i].x = obs_1->xy[i - 1].x + 30;
		obs_1->xy[i].y = obs_1->xy[i - 1].y;
	}
	return obs_1;
}
struct obstacle* initobstacle_2(struct obstacle obstacle_2) {
	obs_2 = &obstacle_2;
	obs_2->length = 1;
	obs_2->xy[0].x = Length - 30;
	obs_2->xy[0].y = 200;
	for (int i = 1; i < 17; i++)
	{
		obs_2->xy[i].x = obs_2->xy[i - 1].x - 30;
		obs_2->xy[i].y = obs_2->xy[i - 1].y;
	}
	return obs_2;
}
struct obstacle* initobstacle_3(struct obstacle obstacle_3) {
	obs_3 = &obstacle_3;
	obs_3->length = 1;
	obs_3->xy[0].x = 200;
	obs_3->xy[0].y = 0;
	for (int i = 1; i <= 12; i++)
	{
		obs_3->xy[i].x = obs_3->xy[i - 1].x;
		obs_3->xy[i].y = obs_3->xy[i - 1].y + 20;
	}
	return obs_3;
}
struct obstacle* initobstacle_4(struct obstacle obstacle_4) {
	obs_4 = &obstacle_4;
	obs_4->length = 1;
	obs_4->xy[0].x = 600;
	obs_4->xy[0].y = Width - 20;
	for (int i = 1; i <= 12; i++)
	{
		obs_4->xy[i].x = obs_4->xy[i - 1].x;
		obs_4->xy[i].y = obs_4->xy[i - 1].y - 20;

	}
	return obs_4;
}
void  initpoison(struct poison* poison1, struct poison* poison2, struct Snake* snake) {
	if (seconds3 != 0 && seconds3 % 150 == 0) {
		poison1->poxy.x = rand() % (Length / 10) * 10;
		poison1->poxy.y = rand() % (Width / 10) * 10;
		poison1->flag = 1;
		poison2->poxy.x = rand() % (Length / 10) * 10;
		poison2->poxy.y = rand() % (Width / 10) * 10;
		poison2->flag = 1;
		if (poison1->poxy.x <= snake->xy[0].x && poison1->poxy.x + 70 >= snake->xy[0].x) {
			if (poison1->poxy.y <= snake->xy[0].y && poison1->poxy.y + 70 >= snake->xy[0].y) {
				poison1->poxy.x = rand() % (Length / 10) * 10;
				poison1->poxy.y = rand() % (Width / 10) * 10;
			}
		}
		if (poison2->poxy.x <= snake->xy[0].x && poison2->poxy.x + 70 >= snake->xy[0].x) {
			if (poison2->poxy.y <= snake->xy[0].y && poison2->poxy.y + 70 >= snake->xy[0].y) {
				poison2->poxy.x = rand() % (Length / 10) * 10;
				poison2->poxy.y = rand() % (Width / 10) * 10;
			}
		}
		if (poison2->poxy.x <= poison1->poxy.x + 60 && poison2->poxy.x >= poison1->poxy.x - 60) {
			if (poison2->poxy.y <= poison1->poxy.y + 60 && poison2->poxy.y >= poison1->poxy.y - 60) {
				poison2->poxy.x = rand() % (Length / 10) * 10;
				poison2->poxy.y = rand() % (Width / 10) * 10;
			}
		}
	}
}
void initSnakeFood(struct Snake* snake, struct Food* food) {
	snake->xy[2].x = 0;
	snake->xy[2].y = 0;

	snake->xy[1].x = 10;//隔十个像素点，之后设置矩形蛇身
	snake->xy[1].y = 0;

	snake->xy[0].x = 20;
	snake->xy[0].y = 0;

	snake->num = 5;//开始有五节

	snake->direction = right;//初始化方向为右

	food->eatgrade = 0;
}

void drawSnake(struct Snake* snake)
{
	for (int i = 0; i < snake->num; i++)
	{
		setlinecolor(BLACK);//矩形边框线的颜色
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));//内部填充颜色
		fillrectangle(snake->xy[i].x, snake->xy[i].y, snake->xy[i].x + 10, snake->xy[i].y + 10);
	}
}

void moveenemy(struct enemy* enemy, struct Snake* snake) {
	if (enemy->flag == 1) {
		seconds3 += 1;
		if (seconds3 % 2 == 0) {
			int a = snake->xy[0].x - (enemy->enxy.x + 15);
			int b = snake->xy[0].y - (enemy->enxy.y + 15);
			if (b >= 0) {
				if (a >= b)
					enemy->enxy.x += 10;
				else if (-a >= b)
					enemy->enxy.x -= 10;
				else
					enemy->enxy.y += 10;
			}
			else {
				if (a >= -b)
					enemy->enxy.x += 10;
				else if (-a >= -b)
					enemy->enxy.x -= 10;
				else
					enemy->enxy.y -= 10;
			}
		}
	}
}
void movesnake(struct Snake* snake, char keyboard[5])
{
	for (int i = snake->num; i > 0; i--) {
		snake->xy[i].x = snake->xy[i - 1].x;
		snake->xy[i].y = snake->xy[i - 1].y;
	}
	switch (keyboard[1]) {
	case'd':case'D': case 77:
		snake->xy[0].x += 10;
		break;

	case'a':case'A': case 75:
		snake->xy[0].x -= 10;
		break;

	case's':case'S': case 80:
		snake->xy[0].y += 10;
		break;

	case'w':case'W': case 72:
		snake->xy[0].y -= 10;
		break;
	}
	putimage(snake->xy[1].x - 5, snake->xy[1].y - 5, &snake->head);//这里是直接将图片在第一个蛇头前面，判定应该需要修改一下
}
void pre_cur(char keyboard[5]) {
	if (keyboard[1] == 'a' || keyboard[1] == 'A' || keyboard[1] == 75)
	{
		if (keyboard[0] == 'd' || keyboard[0] == 'D' || keyboard[0] == 77)
		{
			keyboard[1] = keyboard[0];
		}
		else  keyboard[0] = keyboard[1];
	}
	else if (keyboard[1] == 'd' || keyboard[1] == 'D' || keyboard[1] == 77)
	{
		if (keyboard[0] == 'a' || keyboard[0] == 'A' || keyboard[0] == 75)
		{
			keyboard[1] = keyboard[0];
		}
		else  keyboard[0] = keyboard[1];
	}
	else if (keyboard[1] == 's' || keyboard[1] == 'S' || keyboard[1] == 80)
	{
		if (keyboard[0] == 'w' || keyboard[0] == 'W' || keyboard[0] == 72)
		{
			keyboard[1] = keyboard[0];
		}
		else  keyboard[0] = keyboard[1];
	}
	else
	{
		if (keyboard[0] == 'S' || keyboard[0] == 's' || keyboard[0] == 80)
		{
			keyboard[1] = keyboard[0];
		}
		else  keyboard[0] = keyboard[1];
	}
}
void print_grade(int grade) {
	settextcolor(RED);
	char s[4] = "\0\0\0";
	int i = 0;
	if (grade > 99) {
		s[i] = grade / 100 + '0';
		++i;
	}
	if (grade > 9) {
		s[i] = (grade % 100) / 10 + '0';
		++i;
	}
	s[i] = grade % 10 + '0';
	outtextxy(400, 20, _T("分数："));
	outtextxy(438, 20, s);
}
void change_skin(struct Snake* snake, const char* head) {
	loadimage(&snake->head, head);
}//对蛇的操作

void change(struct Snake* snake, int head) {
	if (head == BEAUTY)
		change_skin(snake, _T(BEAUTY_HEAD));
	if (head == LAZY)
		change_skin(snake, _T(LAZY_head));
	if (head == STR)
		change_skin(snake, _T(STR_HEAD));
}//对玩家选择的判定
bool snakehitenemy(struct enemy* enemy, struct Snake* snake) {
	if (snake->xy[0].x > enemy->enxy.x - 10 && snake->xy[0].x<enemy->enxy.x + 40 &&
		snake->xy[0].y>enemy->enxy.y - 10 && snake->xy[0].y < enemy->enxy.y + 40)
	{
		wsprintf(result, TEXT("被灰太狼吃啦，你的得分为%d"), grade);
		HWND hnd = GetHWnd();//获取窗口句柄
		SetWindowText(hnd, "欢迎");//设置窗口标题 第一个参数传入窗口句柄第二个参数设置字符串
		MessageBox(NULL, result, "提示", MB_OKCANCEL);
		return true;
	}
	else return false;
}
bool snakehitobstacle_1(struct obstacle* obs_1, struct obstacle* obs_2, struct Snake* snake) {
	if (snake->xy[0].x >= 0 && snake->xy[0].x < obs_1->xy[obs_1->length - 1].x + 30 && snake->xy[0].y >= 400
		&& snake->xy[0].y < 420)
		return true;

	else if (snake->xy[0].x <= Length && snake->xy[0].x > obs_2->xy[obs_2->length - 1].x - 10 &&
		snake->xy[0].y >= 200 && snake->xy[0].y < 220)
		return true;
	else return false;
}
bool snakehitobstacle_2(struct obstacle* obs_1, struct obstacle* obs_2,
	struct obstacle* obs_3, struct obstacle* obs_4, struct Snake* snake) {
	if (snake->xy[0].x >= 0 && snake->xy[0].x < obs_1->xy[obs_1->length - 1].x + 20 && snake->xy[0].y >= 400
		&& snake->xy[0].y < 420)
		return true;

	else if (snake->xy[0].x <= Length && snake->xy[0].x >= obs_2->xy[obs_2->length - 1].x - 10 &&
		snake->xy[0].y >= 200 && snake->xy[0].y < 220)
		return true;

	else if (snake->xy[0].x >= 200 && snake->xy[0].x < 230 && snake->xy[0].y >= 0 &&
		snake->xy[0].y <= obs_3->xy[obs_3->length - 1].y + 10)
		return true;

	else if (snake->xy[0].x >= 600 && snake->xy[0].x < 630 &&
		snake->xy[0].y <= Width && snake->xy[0].y >= obs_4->xy[obs_4->length - 1].y)
		return true;

	else return false;
}
bool suicide(struct Snake* snake)
{
	for (int i = 4; i <= snake->num - 1; i++)
	{
		if (snake->xy[0].x == snake->xy[i].x && snake->xy[0].y == snake->xy[i].y)
		{
			wsprintf(result, TEXT("撞自己，你的得分为%d"), grade);
			HWND hnd = GetHWnd();//获取窗口句柄
			SetWindowText(hnd, "欢迎");//设置窗口标题 第一个参数传入窗口句柄第二个参数设置字符串
			MessageBox(NULL, result, "提示", MB_OKCANCEL); return true;
		}
	}
	return false;
}

void game(struct Snake* snake)
{
	int key = 0;
	IMAGE back_0;

	loadimage(&back_0, _T(BACK_1));
	struct Food food;
	struct bigfood bigfood;
	struct enemy enemy;
	struct poison poison1, poison2;
	struct antidote anti;

	int c = 0;
	char keyboard[5];keyboard[0] = 'd', keyboard[1] = 'd';
	setbkcolor(WHITE);
	do
	{
		initSnakeFood(snake, &food);//初始化蛇和食物的分数
		initenemy(&enemy);
		BeginBatchDraw(); //缓冲区打印，防止闪屏
		cleardevice();//刷新
		obs_1 = initobstacle_1(obstacle_1);
		obs_2 = initobstacle_2(obstacle_2);
		obs_4 = initobstacle_4(obstacle_4);
		obs_3 = initobstacle_3(obstacle_3);
		while (1)
		{
			putimage(0, 0, &back_0);
			initpoison(&poison1, &poison2, snake);
			drawobstacle_1(obs_1, obs_2);
			if (grade < 15) {
				if (snakehitobstacle_1(obs_1, obs_2, snake)) {
					wsprintf(result, TEXT("撞障碍，你的得分为%d"), grade);
					HWND hnd = GetHWnd();//获取窗口句柄
					SetWindowText(hnd, "欢迎");//设置窗口标题 第一个参数传入窗口句柄第二个参数设置字符串
					MessageBox(NULL, result, "提示", MB_OKCANCEL);
					return;
				}
			}
			effect_judge(grade);
			if (count >= 10) {
				if (count == 10 && c == 0) {
					HWND hnd = GetHWnd();//获取窗口句柄
					SetWindowText(hnd, "欢迎");//设置窗口标题 第一个参数传入窗口句柄第二个参数设置字符串
					MessageBox(NULL, "难度升级", "提示", MB_OKCANCEL);
					c = 1;
				}
				if (snakehitobstacle_2(obs_1, obs_2, obs_3, obs_4, snake)) {
					wsprintf(result, TEXT("撞障碍，你的得分为%d"), grade);
					HWND hnd = GetHWnd();//获取窗口句柄
					SetWindowText(hnd, "欢迎");//设置窗口标题 第一个参数传入窗口句柄第二个参数设置字符串
					MessageBox(NULL, result, "提示", MB_OKCANCEL);
					return;
				}
				drawobstacle_1(obs_1, obs_2);
				drawobstacle_2(obs_3, obs_4);
				snakehitobstacle_2(obs_1, obs_2, obs_3, obs_4, snake);
			}
			countnum(obs_1, obs_2, obs_3, obs_4);
			initFood(&food, snake, &bigfood, &anti, obs_1, obs_2, obs_3, obs_4);
			initantidote(&anti, &food, snake, &bigfood, &enemy, obs_1, obs_2, obs_3, obs_4);
			initbigfood(&food, snake, &bigfood, &anti, obs_1, obs_2, obs_3, obs_4);
			drawpoison(&poison1, &poison2);
			drawSnake(snake);
			drawantidote(&anti);
			drawbigfood(&bigfood);
			deadpoison(&poison1, &poison2, snake);
			drawenemy(&enemy);
			drawfood(&food);
			eatantidote(&anti, snake, &enemy);
			eatbigfood(&bigfood, snake, &grade);
			eatfood(&food, snake, &grade);
			existenemy(&enemy);
			existpoison(&poison1, &poison2);
			moveenemy(&enemy, snake);
			print_grade(grade);
			if (suicide(snake)) {
				return;
			}
			if (hitwall(snake)) {
				return;
			}
			if (snakehitenemy(&enemy, snake)) {
				return;	
			}
			while (_kbhit())
			{
				keyboard[1] = _getch();
			}
			pre_cur(keyboard);
			movesnake(snake, keyboard);//移动蛇
			EndBatchDraw();
			Sleep(90);
			//cleardevice();//刷新
			EndBatchDraw();
		}
	} while (1);
}
void jump(IMAGE back, struct Snake* snake) {
	IMAGE beauty, lazy, str;
	loadimage(&beauty, _T(BEAUTY_HEAD));
	loadimage(&lazy, _T(LAZY_head));
	loadimage(&str, _T(STR_HEAD));
	mciSendString("open beauty0.mp3 alias beauty_0", NULL, 0, NULL);//对玩家选择时进行音效初始化
	mciSendString("open lazy0.mp3 alias lazy_0", NULL, 0, NULL);
	mciSendString("open beauty0.mp3 alias str_0", NULL, 0, NULL);

	int x = 567, y = 125;
	int p = 700, q = 300;
	int m = 567, n = 475;
	while (1)
	{
		BeginBatchDraw(); //缓冲区打印，防止闪屏
		cleardevice();//刷新
		putimage(0, 0, &back);
		putimage(x, y, &beauty);
		putimage(p, q, &lazy);
		putimage(m, n, &str);
		EndBatchDraw();
		ExMessage msg = getmessage(EX_MOUSE);
		switch (msg.message)
		{
		case WM_MOUSEMOVE://鼠标移动到目的位置就触发
			if (msg.x > 567 && msg.x < 617 && msg.y>125 && msg.y < 175)
			{
				while (y > 90)//缓慢上升效果
				{
					y--;
					BeginBatchDraw(); //缓冲区打印，防止闪屏
					cleardevice();//刷新
					putimage(0, 0, &back);
					putimage(x, y, &beauty);
					EndBatchDraw();
					Sleep(10);
				}
				mciSendString("play beauty_0", NULL, 0, NULL);
				Sleep(300);
				change(snake, BEAUTY);
				effect_init(BEAUTY);
				game(snake);
			}
			if (msg.x > 700 && msg.x < 750 && msg.y > 300 && msg.y < 350)
			{
				while (q > 250) {
					q--;
					BeginBatchDraw(); //缓冲区打印，防止闪屏
					cleardevice();//刷新
					putimage(0, 0, &back);
					putimage(p, q, &lazy);
					EndBatchDraw();
					Sleep(10);
				}
				mciSendString("play lazy_0", NULL, 0, NULL);
				Sleep(300);
				change(snake, LAZY);
				effect_init(LAZY);
				game(snake);
			}
			if (msg.x > 567 && msg.x < 617 && msg.y>475 && msg.y < 525)
			{
				while (n > 425)
				{
					n--;
					BeginBatchDraw(); //缓冲区打印，防止闪屏
					cleardevice();//刷新
					putimage(0, 0, &back);
					putimage(m, n, &str);
					EndBatchDraw();
					Sleep(10);
				}
				mciSendString("play str_0", NULL, 0, NULL);
				Sleep(300);
				change(snake, STR);
				effect_init(STR);
				game(snake);
			}
		}
	}
}
int main() {
	initgraph(Length, Width, EX_SHOWCONSOLE);

	mciSendString("open music.mp3 alias music", NULL, 0, NULL);//背景音乐


	mciSendString("play music repeat", NULL, 0, NULL);//重复播放
	IMAGE straw;
	struct Snake snake;
	loadimage(&straw, _T(UI));
	putimage(0, 0, &straw);

	ExMessage msg;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		switch (msg.message)
		{
		case WM_LBUTTONDOWN:
			if (msg.x > 44 && msg.x < 352 && msg.y > 220 && msg.y < 300)
			{
				cleardevice();
				change(&snake, LAZY);
				effect_init(LAZY);
				game(&snake);
			}
			if (msg.x > 66 && msg.x < 300 && msg.y > 310 && msg.y < 350)
			{
				cleardevice();
				RECT r = { 0,0,879,599 };
				help();
				while (1)
				{
					msg = getmessage(EX_MOUSE);
					switch (msg.message)
					{
					case WM_LBUTTONDOWN:
						if (msg.x > 520 && msg.x < 880 && msg.y > 360 && msg.y < 489)
						{
							cleardevice();
							change(&snake, LAZY);
							game(&snake);
						}
						break;


					}
				}
			}
			if (msg.x > 44 && msg.x < 352 && msg.y > 350 && msg.y < 489)
			{
				cleardevice();
				IMAGE choose;
				loadimage(&choose, _T("choose.jpg"));
				while (1)
				{
					putimage(0, 0, &choose);
					jump(choose, &snake);//尝试过将这个内容放在main函数里但不可行

				}
			}
			break;


		}
	}
	system("pause");
	return 0;
} 