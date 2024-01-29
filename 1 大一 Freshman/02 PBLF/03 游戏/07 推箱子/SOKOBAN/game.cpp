#include "game.h"


//存储元素图片的数组
IMAGE images[total];
//为0时,为manicon,为1时为desMan
int mark = 0;
//人的坐标
pos man;
//存储背景图的数组
IMAGE bg[10];



//函数：设定游戏的窗口大小
void setWindowSize() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}


//函数：加载并插入背景图片
void setBackground(int* level) {
	char name[100];
	memset(name, 0, 100);
	sprintf_s(name, "./background/%d.bmp", *level);
	int num = MultiByteToWideChar(0, 0, name, -1, NULL, 0);
	wchar_t* wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, name, -1, wide, num);
	loadimage(&bg[*level], wide, SCREEN_WIDTH, SCREEN_HEIGHT, true);
    putimage(0, 0, &bg[*level]);
}


/*
* 函数:loadimage
* 作用:加载并插入图片元素,同时记录小人初始位置
* 参数:关卡,小人初始坐标,地图
*/
void addPictures(int* level, int* X, int* Y, int map[TOTAL_LEVEL][LINE][COLUMN]) {
	for (int i = 1; i < total; i++)
	{
		char name[100];
		memset(name, 0, 100);
		sprintf_s(name, "./level%d/%d.bmp", *level + 1, i);
		int num = MultiByteToWideChar(0, 0, name, -1, NULL, 0);
		wchar_t* wide = new wchar_t[num];
		MultiByteToWideChar(0, 0, name, -1, wide, num);
		loadimage(&images[i], wide, LENGTH, LENGTH, true);
	}
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (map[*level][i][j] == manicon) {
				*X = j;
				*Y = i;
			}
			putimage(START_X + LENGTH * j, START_Y + LENGTH * i, &images[map[*level][i][j]]);
		}
	}
}


//函数:替换图片(小人移动是通过替换图片实现的)     参数一:待替换坐标  参数二:要变成的物体 
void changeMap(pos* pos, _OBJECT object, int* level, int map[TOTAL_LEVEL][LINE][COLUMN]) {
	map[*level][pos->y][pos->x] = object;
	putimage(START_X + pos->x * LENGTH, START_Y + pos->y * LENGTH, &images[object]);
}



void gameControl(direction direct, int* level, int map[TOTAL_LEVEL][LINE][COLUMN],int* steps)
{

	//初始化
	pos next_pos = man, next_next_pos = man;
	//获取下一个与下下个位置
	switch (direct) {
	case UP:
		next_pos.y = man.y - 1;
		next_next_pos.y = man.y - 2;
		break;
	case DOWN:
		next_pos.y = man.y + 1;
		next_next_pos.y = man.y + 2;
		break;
	case LEFT:
		next_pos.x = man.x - 1;
		next_next_pos.x = man.x - 2;
		break;
	case RIGHT:
		next_pos.x = man.x + 1;
		next_next_pos.x = man.x + 2;
		break;
	}


	/*For manicon:
	* 1:   前面为地板（人变地，地变人）
	* 2(1):前面为箱子,若箱子前面为地板,前前变箱子,前变人,人变地
	* 2(2):前面为箱子,若箱子前面为目的地,前前变desBox,前变人,人变地
	* 3:   前面为des，des变成desMan，人变地
	* 4(1):前面为desBox,若前前面为地板,前前面变箱子,前变desMan,人变地
	* 4(2):前面为desBox,若前前面为des,前前面变desBox,前变desMan,人变地
	*
	* For desMan(小人站在目的地上变成desMan):
	* 1:   前面为地板（人变des，地变人）
	* 2(1):前面为箱子, 若箱子前面为地板, 前前变箱子, 前变人, 人变des
	* 2(2):前面为箱子, 若箱子前面为目的地, 前前变desBox, 前变人, 人变des
	* 3:   前面为des，des变成desMan，人变des
	* 4(1):前面为desBox, 若前前面为地板, 前前面变箱子, 前变desMan, 人变地
	* 4(2):前面为desBox,若前前面为des,前前面变desBox,前变desMan,人变地For manicon
	*/
	
	//mark为0表示manicon,为1表示desMan

	if (mark == 0) {
		//1:
		if (map[*level][next_pos.y][next_pos.x] == Floor) {
			changeMap(&next_pos, manicon, level, map);
			changeMap(&man, Floor, level, map);
			man = next_pos;
			mark = 0;
			(*steps)++;
		}
		//2:
		else if (map[*level][next_pos.y][next_pos.x] == box) {
			//2(1):   
			if (map[*level][next_next_pos.y][next_next_pos.x] == Floor) {
				changeMap(&next_next_pos, box, level, map);
				changeMap(&next_pos, manicon, level, map);
				changeMap(&man, Floor, level, map);
				man = next_pos;
				mark = 0;
				(*steps)++;
			}
			//2(2):
			else if (map[*level][next_next_pos.y][next_next_pos.x] == des) {
				changeMap(&next_next_pos, desBox, level, map);
				changeMap(&next_pos, manicon, level, map);
				changeMap(&man, Floor, level, map);
				man = next_pos;
				mark = 0;
				(*steps)++;
			}
		}
		//3:
		else if (map[*level][next_pos.y][next_pos.x] == des) {
			changeMap(&next_pos, desMan, level, map);
			changeMap(&man, Floor, level, map);
			man = next_pos;
			mark = 1;
			(*steps)++;
		}
		//4:
		else if (map[*level][next_pos.y][next_pos.x] == desBox) {
			//4(1):   
			if (map[*level][next_next_pos.y][next_next_pos.x] == Floor) {
				changeMap(&next_next_pos, box, level, map);
				changeMap(&next_pos, desMan, level, map);
				changeMap(&man, Floor, level, map);
				man = next_pos;
				mark = 1;
				(*steps)++;
			}
			//4(2):
			else if (map[*level][next_next_pos.y][next_next_pos.x] == des) {
				changeMap(&next_next_pos, desBox, level, map);
				changeMap(&next_pos, desMan, level, map);
				changeMap(&man, Floor, level, map);
				man = next_pos;
				mark = 1;
				(*steps)++;
			}
		}
	}
	//For desMan
	else if (mark == 1) {
		//1:
		if (map[*level][next_pos.y][next_pos.x] == Floor) {
			changeMap(&next_pos, manicon, level, map);
			changeMap(&man, des, level, map);
			man = next_pos;
			mark = 0;
			(*steps)++;
		}
		//2:
		else if (map[*level][next_pos.y][next_pos.x] == box) {
			//2(1):   
			if (map[*level][next_next_pos.y][next_next_pos.x] == Floor) {
				changeMap(&next_next_pos, box, level, map);
				changeMap(&next_pos, manicon, level, map);
				changeMap(&man, des, level, map);
				man = next_pos;
				mark = 0;
				(*steps)++;
			}
			//2(2):
			else if (map[*level][next_next_pos.y][next_next_pos.x] == des) {
				changeMap(&next_next_pos, desBox, level, map);
				changeMap(&next_pos, manicon, level, map);
				changeMap(&man, des, level, map);
				man = next_pos;
				mark = 0;
				(*steps)++;
			}
		}
		//3:
		else if (map[*level][next_pos.y][next_pos.x] == des) {
			changeMap(&next_pos, desMan, level, map);
			changeMap(&man, des, level, map);
			man = next_pos;
			mark = 1;
			(*steps)++;
		}
		//4:
		else if (map[*level][next_pos.y][next_pos.x] == desBox) {
			//4(1):   
			if (map[*level][next_next_pos.y][next_next_pos.x] == Floor) {
				changeMap(&next_next_pos, box, level, map);
				changeMap(&next_pos, desMan, level, map);
				changeMap(&man, des, level, map);
				man = next_pos;
				mark = 1;
				(*steps)++;
			}
			//4(2):
			else if (map[*level][next_next_pos.y][next_next_pos.x] == des) {
				changeMap(&next_next_pos, desBox, level, map);
				changeMap(&next_pos, desMan, level, map);
				changeMap(&man, des, level, map);
				man = next_pos;
				mark = 1;
				(*steps)++;
			}
		}
	}
}


//函数:当箱子都到达目的地时执行, 返回正确, 用于函数gameOver
bool finish(int* level, int map[TOTAL_LEVEL][LINE][COLUMN]) {
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (map[*level][i][j] == des || map[*level][i][j] == desMan) {
				return false;
			}
		}
	}
	return true;
}


//函数:在选关时鼠标点中关卡区域,返回true
bool clickYes(MOUSEMSG* m, int i, int x[TOTAL_LEVEL], int y[TOTAL_LEVEL]) {
	return(m->x >= x[i] && m->x < x[i] + LENGTH * 2 && m->y >= y[i] && m->y < y[i] + LENGTH * 2);
}


//函数:选择关卡
void chooseLevel(int* level) {
	
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	IMAGE chooseground;
	loadimage(&chooseground, _T("chooseground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &chooseground);
	int x[10];
	int y[10];
	IMAGE levelPictures[2][5];
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 5; i++) {
			char name[100];
			memset(name, 0, 100);
			if (j == 0)
				sprintf_s(name, "./level%d/8.bmp",i + 1);
			else
				sprintf_s(name, "./level%d/8.bmp", i + 6);
			int num = MultiByteToWideChar(0, 0, name, -1, NULL, 0);
			wchar_t* wide = new wchar_t[num];
			MultiByteToWideChar(0, 0, name, -1, wide, num);
			loadimage(&levelPictures[j][i], wide, LENGTH*2, LENGTH*2, true);

			
			x[i + j * 5] = 120 + 140 * i;
			y[i + j * 5] = 230 + 180 * j;
			putimage(x[i + j * 5], y[i + j * 5], &levelPictures[j][i]);
		}
	}



	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();                     //获取鼠标信息,存入结构m中
		if (m.uMsg == WM_LBUTTONDOWN) {        //按下左键
			for (int i = 0; i < TOTAL_LEVEL; i++) {
				if (clickYes(&m, i, x, y)) {
					*level = i;
					closegraph();
					return;
				}
			}
		}
	}
}





//函数:结束游戏
bool gameOver(int* level, int map[TOTAL_LEVEL][LINE][COLUMN]) {
	if (finish(level, map)) {
		closegraph();
		if (*level <= 8) {
			(*level)++;
			return false;
		}
		else {
			chooseLevel(level);
			return false;
		}


	}
	else {
		return true;
	}
}


//函数：统计并显示步数
void showsteps(int* steps) {

	char words[100];
	memset(words, 0, 100);
	settextcolor(BLACK);
	settextstyle(40, 0, _T("楷体"));
	setbkmode(TRANSPARENT);
	sprintf_s(words, "已走步数：%d", *steps);
	int num = MultiByteToWideChar(0, 0, words, -1, NULL, 0);
	wchar_t* wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, words, -1, wide, num);
	int width = textwidth(wide);
	int height = textheight(wide);
	SCREEN_WIDTH, SCREEN_HEIGHT;
	setfillcolor(WHITE);
	fillrectangle(200, 36, 200 + width, 110);
	/*mToMenu.x >= 45 && mToMenu.x <= 120 && mToMenu.y >= 20 && mToMenu.y <= 110*/
	outtextxy(200, 36 + (110 - 36) / 2 - height / 2, wide);

}


//作用:接收键盘输入后调用gameControl
void getKey(int* level, int map[TOTAL_LEVEL][LINE][COLUMN], int* X, int* Y, int* status, int* out, bool* menutool) {
	man.x = *X;
	man.y = *Y;
	int steps=0;
	

	IMAGE caidan,menuground;
	loadimage(&caidan, _T("caidan.bmp"), 600, 400, true);

	MOUSEMSG mToMenu;


	bool endGame;
	do {


		//通过键盘来控制上下左右
		if (_kbhit()) {
			
			char ch = _getch();

			if (ch == KEY_UP) {
				gameControl(UP, level, map,&steps);
			}
			else if (ch == KEY_DOWN) {
				gameControl(DOWN, level, map,&steps);
			}
			else if (ch == KEY_LEFT) {
				gameControl(LEFT, level, map,&steps);
			}
			else if (ch == KEY_RIGHT) {
				gameControl(RIGHT, level, map,&steps);
			}
			

		}





		if (MouseHit()) {
			mToMenu = GetMouseMsg();
			if (mToMenu.uMsg == WM_LBUTTONDOWN) {  //当按下鼠标左键时

				if (mToMenu.x >= 45 && mToMenu.x <= 120 && mToMenu.y >= 20 && mToMenu.y <= 110) {  //点中菜单小图标
					loadimage(&menuground, _T("menuground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
					putimage(0, 0, &menuground);
					putimage(150, 150, &caidan);   //打开菜单
					while (1) {
						mToMenu = GetMouseMsg();
						if (mToMenu.uMsg == WM_LBUTTONDOWN) {
							//重开
							if (mToMenu.x >= 315 && mToMenu.x <= 585 && mToMenu.y >= 263 && mToMenu.y <= 306) {
								*status = 0;
								closegraph();
								return;
							}

							//选关
							else if (mToMenu.x >= 315 && mToMenu.x <= 585 && mToMenu.y >= 361 && mToMenu.y <= 414) {
								*status = 0;
								closegraph();
								chooseLevel(level);
								return;
							}

							//返回主菜单
							else if (mToMenu.x >= 300 && mToMenu.x <= 600 && mToMenu.y >= 460 && mToMenu.y <= 500) {
								*status = 0;
								*out = 1;
								closegraph();
								return;
							}
						}
					}
				}
			}
		}


		

		showsteps(&steps);
		endGame = gameOver(level, map);
	} while (endGame);
}


