#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include "XMarkup.h"
#include "main.h"

#pragma comment(lib,"Winmm.lib")

#define RECORD_FILE_PATH "./maze_record.xml"

using namespace std;
int g_user_x = 0;
int g_user_y = 0;
time_t g_time_begin = 0;

player_t g_player;
player_t g_player_record[3][10];
int g_level1_player_num = 0;
int g_level2_player_num = 0;
int g_level3_player_num = 0;

char g_level1_map[LEVEL_1_NUM][LEVEL_1_NUM] = {
	{2,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,0,1},
	{1,0,0,1,1,0,0,1,0,1},
	{1,0,0,0,0,1,0,1,0,1},
	{1,0,1,1,0,1,0,0,0,1},
	{1,0,0,1,0,1,1,0,1,1},
	{1,1,0,1,0,0,1,0,1,1},
	{1,1,0,1,1,0,1,0,1,1},
	{1,1,3,1,1,0,0,0,1,1},
};
char g_level2_map[LEVEL_2_NUM][LEVEL_2_NUM] = {
	{2,0,1,0,0,0,0,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,1,0,0,0,0,0,1,1,1,1},
	{1,1,0,1,1,1,1,1,1,1,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,1,1,1,1,1,0,1},
	{1,0,1,1,0,1,1,0,1,0,0,0,1,0,1},
	{1,0,1,1,0,0,1,0,0,0,1,0,1,0,1},
	{1,0,0,0,1,0,1,1,1,0,0,0,1,0,1},
	{1,1,1,0,0,0,0,1,1,0,1,1,1,0,0},
	{3,0,1,1,1,1,0,0,0,0,1,1,1,1,0},
	{1,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{1,1,0,0,1,1,1,1,0,0,0,0,1,1,1},
	{1,1,1,0,1,0,0,1,0,1,1,1,1,1,1},
	{1,1,1,0,0,1,0,0,0,1,1,1,1,1,1},
	{1,1,1,1,0,1,0,1,1,1,1,1,1,1,1},
	{1,1,1,1,0,0,0,1,1,1,1,1,1,1,1}

};
char g_level3_map[LEVEL_3_NUM][LEVEL_3_NUM] = {
	{2,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1},
	{1,1,0,1,1,0,1,0,0,0,0,1,1,0,0,1,1,1},
	{1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1},
	{1,1,0,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0},
	{1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0},
	{1,1,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,1,1,1,0,0,0,0,0,1,0,0,1,1,1,1},
	{0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1},
	{1,0,1,1,1,0,0,0,0,1,0,1,0,1,1,1,1,1},
	{1,0,1,1,1,0,1,1,0,1,0,1,0,0,1,1,1,1},
	{0,0,1,1,1,0,1,1,0,1,0,0,1,0,0,1,1,1},
	{0,0,0,0,1,0,1,1,0,0,1,0,1,1,0,1,1,1},
	{1,1,1,1,1,0,0,0,1,0,1,0,1,1,0,1,1,1},
	{1,1,1,1,1,1,1,0,1,0,0,0,1,0,0,1,1,1},
	{3,0,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
	{1,1,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1}
};

//
//判断是否胜利了
//
int iswin()
{
	int status = 0;
	if (g_player.level == 1) {
		status = g_level1_map[g_user_x][g_user_y];
	}
	else if (g_player.level == 2) {
		status = g_level2_map[g_user_x][g_user_y];
	}if (g_player.level == 3) {
		status = g_level3_map[g_user_x][g_user_y];
	}
	if (status == ISEXIT) {
		return 1;
	}
	return 0;
}

//
//画图
//
void show()
{
	TCHAR str[250] = { 0 };

	BeginBatchDraw();
	setbkcolor(GREEN);
	cleardevice();
	setcolor(BLUE);

	if (g_player.level== 1) {
		for (int i = 0; i < LEVEL_1_NUM; i++) {
			for (int j = 0; j < LEVEL_1_NUM; j++) {
				if (g_level1_map[i][j] == ISWALL) {
					setfillcolor(RED);
				}
				else if (g_level1_map[i][j] == ISROAD) {
					setfillcolor(BLUE);
				}
				else if (g_level1_map[i][j] == ISENTRY) {
					setfillcolor(BLACK);
				}
				else if (g_level1_map[i][j] == ISEXIT) {
					setfillcolor(YELLOW);
				}
				fillrectangle(transfer_pos(i), transfer_pos(j), transfer_pos(i) + 28, transfer_pos(j) + 28);

			}
		}

		if (iswin() == 1) {
			_stprintf_s(str, _T("排行榜:(1级)"));
			outtextxy(570, 295, str);
			for (int i = 0; i < g_level1_player_num; i++) {
				_stprintf_s(str, _T("姓名:%-12s 步数:%d 时间:%d"),
					g_player_record[0][i].name,
					g_player_record[0][i].step,
					g_player_record[0][i].second);
				outtextxy(570, 335 + i * 20, str);				
			}

			setcolor(RED);
			line(565, 335, 565, 335 + g_level1_player_num * 20);
			line(798, 335, 798, 335 + g_level1_player_num * 20);
			line(565, 335, 798, 335);
			line(565, 335 + g_level1_player_num * 20, 798, 335 + g_level1_player_num * 20);
			_stprintf_s(str, _T("按回车键结束游戏"));
			outtextxy(570, 335 + g_level1_player_num * 20 + 20, str);
		}
	}
	else if (g_player.level == 2) {
		for (int i = 0; i < LEVEL_2_NUM; i++) {
			for (int j = 0; j < LEVEL_2_NUM; j++) {
				if (g_level2_map[i][j] == ISWALL) {
					setfillcolor(RED);
				}
				else if (g_level2_map[i][j] == ISROAD) {
					setfillcolor(BLUE);
				}
				else if (g_level2_map[i][j] == ISENTRY) {
					setfillcolor(BLACK);
				}
				else if (g_level2_map[i][j] == ISEXIT) {
					setfillcolor(YELLOW);
				}
				fillrectangle(transfer_pos(i), transfer_pos(j), transfer_pos(i) + 28, transfer_pos(j) + 28);

			}
		}
		if (iswin() == 1) {
			_stprintf_s(str, _T("排行榜:(2级)"));
			outtextxy(570, 295, str);
			for (int i = 0; i < g_level2_player_num; i++) {
				_stprintf_s(str, _T("姓名:%-12s 步数:%d 时间:%d"),
					g_player_record[1][i].name,
					g_player_record[1][i].step,
					g_player_record[1][i].second);
				outtextxy(570, 335 + i * 20, str);
			}

			setcolor(RED);
			line(565, 335, 565, 335 + g_level2_player_num * 20);
			line(798, 335, 798, 335 + g_level2_player_num * 20);
			line(565, 335, 798, 335);
			line(565, 335 + g_level2_player_num * 20, 798, 335 + g_level2_player_num * 20);
			_stprintf_s(str, _T("按回车键结束游戏"));
			outtextxy(570, 335 + g_level2_player_num * 20 + 20, str);
		}
	}
	else if (g_player.level == 3) {
		for (int i = 0; i < LEVEL_3_NUM; i++) {
			for (int j = 0; j < LEVEL_3_NUM; j++) {
				if (g_level3_map[i][j] == ISWALL) {
					setfillcolor(RED);
				}
				else if (g_level3_map[i][j] == ISROAD) {
					setfillcolor(BLUE);
				}
				else if (g_level3_map[i][j] == ISENTRY) {
					setfillcolor(BLACK);
				}
				else if (g_level3_map[i][j] == ISEXIT) {
					setfillcolor(YELLOW);
				}
				fillrectangle(transfer_pos(i), transfer_pos(j), transfer_pos(i) + 28, transfer_pos(j) + 28);
			}
		}
		if (iswin() == 1) {
			_stprintf_s(str, _T("排行榜:(3级)"));
			outtextxy(570, 295, str);
			for (int i = 0; i < g_level3_player_num; i++) {
				_stprintf_s(str, _T("姓名:%-12s 步数:%d 时间:%d"),
					g_player_record[2][i].name,
					g_player_record[2][i].step,
					g_player_record[2][i].second);
				outtextxy(570, 335 + i * 20, str);
			}

			setcolor(RED);
			line(565, 335, 565, 335 + g_level3_player_num * 20);
			line(798, 335, 798, 335 + g_level3_player_num * 20);
			line(565, 335, 798, 335);
			line(565, 335 + g_level3_player_num * 20, 798, 335 + g_level3_player_num * 20);
			_stprintf_s(str, _T("按回车键结束游戏"));
			outtextxy(570, 335 + g_level3_player_num * 20 + 20, str);
		}
	}

	setcolor(BLACK);

	_stprintf_s(str, _T("欢迎使用迷宫小游戏"));
	outtextxy(570, 5, str);

	_stprintf_s(str, _T("玩家姓名:%s"), g_player.name);
	outtextxy(570, 45, str);

	if (g_player.level <= 0) {
	}
	else {
		setfillcolor(YELLOW);
		fillcircle(transfer_pos(g_user_x) + 14, transfer_pos(g_user_y) + 14, 14);

		_stprintf_s(str, _T("游戏级别:%d"), g_player.level);
		outtextxy(570, 85, str);
	}	

	setcolor(BLACK);
	_stprintf_s(str, _T("所走步数:%d"), g_player.step);
	outtextxy(570, 125, str);

	_stprintf_s(str, _T("黑色方框为入口 黄色方框为出口"));
	outtextxy(570, 165, str);
	_stprintf_s(str, _T("使用上下左右键控制小球"));
	outtextxy(570, 205, str);
	_stprintf_s(str, _T("用最少的时间和步数走出迷宫吧"));
	outtextxy(570, 245, str);

	FlushBatchDraw();
	EndBatchDraw();
	return;
}

int pos_valid(int x, int y, int num) 
{
	if ((x >= 0) && (x < num) && (y >= 0) && (y < num)) {
		return 1;
	}
	return 0;
}

void dowith_key(char c) 
{
	switch (c) {
		//上键
#if 0
	case 72:
#else
	case VK_UP:
#endif
	case 'w':
	case 'W':
		if (g_player.level == 1) {
			if ((pos_valid(g_user_x, g_user_y - 1, LEVEL_1_NUM) == 1)
				&& g_level1_map[g_user_x][g_user_y - 1] != ISWALL) {
				g_user_y--;
				g_player.step++;
			}
		}
		else if (g_player.level == 2) {
			if ((pos_valid(g_user_x, g_user_y - 1, LEVEL_2_NUM) == 1)
				&& g_level2_map[g_user_x][g_user_y - 1] != ISWALL) {
				g_user_y--;
				g_player.step++;
			}
		}
		else if (g_player.level == 3) {
			if ((pos_valid(g_user_x, g_user_y - 1, LEVEL_3_NUM) == 1)
				&& g_level3_map[g_user_x][g_user_y - 1] != ISWALL) {
				g_user_y--;
				g_player.step++;
			}
		}
		break;
		//下键
#if 0
	case 80:
#else
	case VK_DOWN:
#endif
	case 's':
	case 'S':
		if (g_player.level == 1) {
			if ((pos_valid(g_user_x, g_user_y + 1, LEVEL_1_NUM) == 1)
				&& g_level1_map[g_user_x][g_user_y + 1] != ISWALL) {
				g_user_y++;
				g_player.step++;
			}
		}
		else if (g_player.level == 2) {
			if ((pos_valid(g_user_x, g_user_y + 1, LEVEL_2_NUM) == 1)
				&& g_level2_map[g_user_x][g_user_y + 1] != ISWALL) {
				g_user_y++;
				g_player.step++;
			}
		}
		else if (g_player.level == 3) {
			if ((pos_valid(g_user_x, g_user_y + 1, LEVEL_3_NUM) == 1)
				&& g_level3_map[g_user_x][g_user_y + 1] != ISWALL) {
				g_user_y++;
				g_player.step++;
			}
		}
		break;
		//左键
	case 'a':
	case 'A':
#if 0
	case 75:
#else
	case VK_LEFT:
#endif
		if (g_player.level == 1) {
			if ((pos_valid(g_user_x - 1, g_user_y, LEVEL_1_NUM) == 1)
				&& g_level1_map[g_user_x - 1][g_user_y] != ISWALL) {
				g_user_x--;
				g_player.step++;
			}
		}
		else if (g_player.level == 2) {
			if ((pos_valid(g_user_x - 1, g_user_y, LEVEL_2_NUM) == 1)
				&& g_level2_map[g_user_x - 1][g_user_y] != ISWALL) {
				g_user_x--;
				g_player.step++;
			}
		}
		else if (g_player.level == 3) {
			if ((pos_valid(g_user_x - 1, g_user_y, LEVEL_3_NUM) == 1)
				&& g_level3_map[g_user_x - 1][g_user_y] != ISWALL) {
				g_user_x--;
				g_player.step++;
			}
		}
		break;
		//右键
	case 'd':
	case 'D':
#if 0
	case 77:
#else
	case VK_RIGHT:
#endif
		if (g_player.level == 1) {
			if ((pos_valid(g_user_x + 1, g_user_y, LEVEL_1_NUM) == 1)
				&& g_level1_map[g_user_x + 1][g_user_y] != ISWALL) {
				g_user_x++;
				g_player.step++;
			}
		}
		else if (g_player.level == 2) {
			if ((pos_valid(g_user_x + 1, g_user_y, LEVEL_2_NUM) == 1)
				&& g_level2_map[g_user_x + 1][g_user_y] != ISWALL) {
				g_user_x++;
				g_player.step++;
			}
		}
		else if (g_player.level == 3) {
			if ((pos_valid(g_user_x + 1, g_user_y, LEVEL_3_NUM) == 1)
				&& g_level3_map[g_user_x + 1][g_user_y] != ISWALL) {
				g_user_x++;
				g_player.step++;
			}
		}
		break;
	}
}

//
//加载成绩记录
// 成功返回0
//
int load_record()
{
	const char* filename = RECORD_FILE_PATH;
	XMarkup xml;
	if (!xml.Load(filename))
	{
		return -1;
	}
	if (!xml.FindElem("MAZEGAME"))
	{
		return -1;
	}
	xml.IntoElem();

	//读取1级的玩家	
	if (!xml.FindElem("LEVEL1"))
	{
		return -1;
	}
	xml.IntoElem();	
	while (xml.FindElem("PLAYER"))
	{
		if (g_level1_player_num >= 10) {
			continue;
		}
		g_player_record[0][g_level1_player_num].level = 1;
		strcpy(g_player_record[0][g_level1_player_num].name, xml.GetAttrib("NAME").c_str());
		g_player_record[0][g_level1_player_num].step = atoi(xml.GetAttrib("STEP").c_str());
		g_player_record[0][g_level1_player_num].second = atoi(xml.GetAttrib("SECOND").c_str());
		g_level1_player_num++;
	}
	xml.OutOfElem();

	//读取2级的玩家
	if (!xml.FindElem("LEVEL2"))
	{
		return -1;
	}
	xml.IntoElem();
	while (xml.FindElem("PLAYER"))
	{
		if (g_level2_player_num >= 10) {
			continue;
		}
		g_player_record[1][g_level2_player_num].level = 2;
		strcpy(g_player_record[1][g_level2_player_num].name, xml.GetAttrib("NAME").c_str());
		g_player_record[1][g_level2_player_num].step = atoi(xml.GetAttrib("STEP").c_str());
		g_player_record[1][g_level2_player_num].second = atoi(xml.GetAttrib("SECOND").c_str());
		g_level2_player_num++;
	}
	xml.OutOfElem();

	//读取3级的玩家
	if (!xml.FindElem("LEVEL3"))
	{
		return -1;
	}
	xml.IntoElem();
	while (xml.FindElem("PLAYER"))
	{
		if (g_level3_player_num >= 10) {
			continue;
		}
		g_player_record[2][g_level3_player_num].level = 3;
		strcpy(g_player_record[2][g_level3_player_num].name, xml.GetAttrib("NAME").c_str());
		g_player_record[2][g_level3_player_num].step = atoi(xml.GetAttrib("STEP").c_str());
		g_player_record[2][g_level3_player_num].second = atoi(xml.GetAttrib("SECOND").c_str());
		g_level3_player_num++;
	}
	xml.OutOfElem();
	xml.OutOfElem();
	return 0;
}

int save_record()
{
	XMarkup xml;
	char buf[256] = {0};
	xml.AddElem("MAZEGAME");
	xml.AddAttrib("VERSION", "1.0");
	xml.IntoElem();

	//1级
	xml.AddElem("LEVEL1");
	xml.IntoElem();
	for (int i = 0;i < g_level1_player_num; i++)
	{
		xml.AddElem("PLAYER");
		xml.AddAttrib("NAME", g_player_record[0][i].name);
		sprintf(buf, "%d", g_player_record[0][i].step);
		xml.AddAttrib("STEP", buf);
		sprintf(buf, "%d", g_player_record[0][i].second);
		xml.AddAttrib("SECOND", buf);
	}
	xml.OutOfElem();

	//2级
	xml.AddElem("LEVEL2");
	xml.IntoElem();
	for (int i = 0;i < g_level2_player_num; i++)
	{
		xml.AddElem("PLAYER");
		xml.AddAttrib("NAME", g_player_record[1][i].name);
		sprintf(buf, "%d", g_player_record[1][i].step);
		xml.AddAttrib("STEP", buf);
		sprintf(buf, "%d", g_player_record[1][i].second);
		xml.AddAttrib("SECOND", buf);
	}
	xml.OutOfElem();

	//3级
	xml.AddElem("LEVEL3");
	xml.IntoElem();
	for (int i = 0;i < g_level3_player_num; i++)
	{
		xml.AddElem("PLAYER");
		xml.AddAttrib("NAME", g_player_record[2][i].name);
		sprintf(buf, "%d", g_player_record[2][i].step);
		xml.AddAttrib("STEP", buf);
		sprintf(buf, "%d", g_player_record[2][i].second);
		xml.AddAttrib("SECOND", buf);
	}
	xml.OutOfElem();

	if (!xml.Save(RECORD_FILE_PATH))
	{
		return -1;
	}
	return 0;
}

//玩家比较
//p1比p2优时返回1
int compare_player(player_t* p1, player_t* p2)
{
	if (p1->step < p2->step) {
		return 1;
	}
	else if (p1->step > p2->step) {
		return 0;
	}
	else {
		//步数相等时比较时间 时间短的 更优
		return (p1->second <= p2->second);
	}
}

//
//冒泡法排序
//
int sort_record() 
{
	for (int i = 0; i < g_level1_player_num - 1; i++) {
		for (int j = 0; j < g_level1_player_num - i - 1; j++) {
			if (compare_player(&g_player_record[0][j],&g_player_record[0][j + 1]) <= 0) {
				player_t ptmp;
				memcpy(&ptmp, &g_player_record[0][j], sizeof(player_t));
				memcpy(&g_player_record[0][j], &g_player_record[0][j + 1], sizeof(player_t));
				memcpy(&g_player_record[0][j + 1], &ptmp, sizeof(player_t));
			}
		}
	}

	for (int i = 0; i < g_level2_player_num - 1; i++) {
		for (int j = 0; j < g_level2_player_num - i - 1; j++) {
			if (compare_player(&g_player_record[1][j], &g_player_record[1][j + 1]) <= 0) {
				player_t ptmp;
				memcpy(&ptmp, &g_player_record[1][j], sizeof(player_t));
				memcpy(&g_player_record[1][j], &g_player_record[1][j + 1], sizeof(player_t));
				memcpy(&g_player_record[1][j + 1], &ptmp, sizeof(player_t));
			}
		}
	}

	for (int i = 0; i < g_level3_player_num - 1; i++) {
		for (int j = 0; j < g_level3_player_num - i - 1; j++) {
			if (compare_player(&g_player_record[2][j], &g_player_record[2][j + 1]) <= 0) {
				player_t ptmp;
				memcpy(&ptmp, &g_player_record[2][j], sizeof(player_t));
				memcpy(&g_player_record[2][j], &g_player_record[2][j + 1], sizeof(player_t));
				memcpy(&g_player_record[2][j + 1], &ptmp, sizeof(player_t));
			}
		}
	}
	return 0;
}

//
//查找相应级别的记录中是否已经存在改用户
// 存在则返回相应指针
//
player_t* find_player(const char* name, int level)
{
	if (level == 1) {
		for (int i = 0; i < g_level1_player_num; i++) {
			if (strcmp(name, g_player_record[0][i].name) == 0) {
				return &g_player_record[0][i];
			}
		}
	}
	else if (level == 2) {
		for (int i = 0; i < g_level2_player_num; i++) {
			if (strcmp(name, g_player_record[1][i].name) == 0) {
				return &g_player_record[1][i];
			}
		}
	}
	else if (level == 3) {
		for (int i = 0; i < g_level3_player_num; i++) {
			if (strcmp(name, g_player_record[2][i].name) == 0) {
				return &g_player_record[2][i];
			}
		}
	}
	return NULL;
}

//
//向数值中增加一个玩家
//
int add_player() 
{
	if (g_player.level == 1) {
		if (g_level1_player_num == 10) {
			if (compare_player(&g_player, &g_player_record[0][g_level1_player_num - 1]) > 0) {
				memcpy(&g_player_record[0][g_level1_player_num - 1], &g_player, sizeof(g_player));
			}
		}
		else {
			memcpy(&g_player_record[0][g_level1_player_num],&g_player, sizeof(g_player));
			g_level1_player_num++;
		}
	} 
	else if (g_player.level == 2) {
		if (g_level2_player_num == 10) {
			if (compare_player(&g_player, &g_player_record[1][g_level2_player_num - 1]) > 0) {
				memcpy(&g_player_record[1][g_level2_player_num - 1], &g_player, sizeof(g_player));
			}
		}
		else {
			memcpy(&g_player_record[1][g_level2_player_num], &g_player, sizeof(g_player));
			g_level2_player_num++;
		}
	}
	else if (g_player.level == 3) {
		if (g_level3_player_num == 10) {
			if (compare_player(&g_player, &g_player_record[2][g_level3_player_num - 1]) > 0) {
				memcpy(&g_player_record[2][g_level3_player_num - 1], &g_player, sizeof(g_player));
			}
		}
		else {
			memcpy(&g_player_record[2][g_level3_player_num], &g_player, sizeof(g_player));
			g_level3_player_num++;
		}
	}
	return 0;
}

void clear_info() 
{
	memset(&g_player, 0, sizeof(g_player));
	g_user_x = 0;
	g_user_y = 0;
	g_time_begin = 0;
}

int main() 
{
	ExMessage m;
	initgraph(800, 580);
	while (1) {

		show();

		while (strlen(g_player.name) == 0) {
			InputBox(g_player.name, sizeof(g_player.name), "请输入玩家姓名");
			show();
		}

		while (g_player.level <= 0) {
			char chlevel[64] = { 0 };
			InputBox(chlevel, sizeof(chlevel), "请输入等级(1或2或3)");
			if (atoi(chlevel) == 1) {
				g_player.level = 1;
				g_time_begin = time(NULL);
				show();
				break;
			}
			else if (atoi(chlevel) == 2) {
				g_player.level = 2;
				g_time_begin = time(NULL);
				show();
				break;
			}
			else if (atoi(chlevel) == 3) {
				g_player.level = 3;
				g_time_begin = time(NULL);
				show();
				break;
			}
			else {
			}
		}
#if 0
		char c = _gettch();
		dowith_key(c);
#else
		m = getmessage(EX_KEY);
		char c = m.vkcode;
		if (m.prevdown == 0) {
			dowith_key(c);
		}
#endif
		
		if (iswin() == 1) {
			g_player.second = (int)(time(NULL) - g_time_begin);
			g_level1_player_num = 0;
			g_level2_player_num = 0;
			g_level3_player_num = 0;
			memset(g_player_record, 0, sizeof(g_player_record));
			load_record();
			sort_record();
			player_t *ptmp = find_player(g_player.name, g_player.level);
			if (ptmp == NULL) {
				add_player();
			}
			else {
				if (compare_player(&g_player, ptmp) > 0) {
					memcpy(ptmp, &g_player, sizeof(player_t));
				}
			}
			sort_record();
			save_record();
			show();			
			//按回车结束游戏
			while ((c = getchar()) != '\n' && (c != EOF)) {}
			clear_info();
			break;
		}
	}
	closegraph();
}

