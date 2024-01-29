#include "game.h"


//�洢Ԫ��ͼƬ������
IMAGE images[total];
//Ϊ0ʱ,Ϊmanicon,Ϊ1ʱΪdesMan
int mark = 0;
//�˵�����
pos man;
//�洢����ͼ������
IMAGE bg[10];



//�������趨��Ϸ�Ĵ��ڴ�С
void setWindowSize() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}


//���������ز����뱳��ͼƬ
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
* ����:loadimage
* ����:���ز�����ͼƬԪ��,ͬʱ��¼С�˳�ʼλ��
* ����:�ؿ�,С�˳�ʼ����,��ͼ
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


//����:�滻ͼƬ(С���ƶ���ͨ���滻ͼƬʵ�ֵ�)     ����һ:���滻����  ������:Ҫ��ɵ����� 
void changeMap(pos* pos, _OBJECT object, int* level, int map[TOTAL_LEVEL][LINE][COLUMN]) {
	map[*level][pos->y][pos->x] = object;
	putimage(START_X + pos->x * LENGTH, START_Y + pos->y * LENGTH, &images[object]);
}



void gameControl(direction direct, int* level, int map[TOTAL_LEVEL][LINE][COLUMN],int* steps)
{

	//��ʼ��
	pos next_pos = man, next_next_pos = man;
	//��ȡ��һ�������¸�λ��
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
	* 1:   ǰ��Ϊ�ذ壨�˱�أ��ر��ˣ�
	* 2(1):ǰ��Ϊ����,������ǰ��Ϊ�ذ�,ǰǰ������,ǰ����,�˱��
	* 2(2):ǰ��Ϊ����,������ǰ��ΪĿ�ĵ�,ǰǰ��desBox,ǰ����,�˱��
	* 3:   ǰ��Ϊdes��des���desMan���˱��
	* 4(1):ǰ��ΪdesBox,��ǰǰ��Ϊ�ذ�,ǰǰ�������,ǰ��desMan,�˱��
	* 4(2):ǰ��ΪdesBox,��ǰǰ��Ϊdes,ǰǰ���desBox,ǰ��desMan,�˱��
	*
	* For desMan(С��վ��Ŀ�ĵ��ϱ��desMan):
	* 1:   ǰ��Ϊ�ذ壨�˱�des���ر��ˣ�
	* 2(1):ǰ��Ϊ����, ������ǰ��Ϊ�ذ�, ǰǰ������, ǰ����, �˱�des
	* 2(2):ǰ��Ϊ����, ������ǰ��ΪĿ�ĵ�, ǰǰ��desBox, ǰ����, �˱�des
	* 3:   ǰ��Ϊdes��des���desMan���˱�des
	* 4(1):ǰ��ΪdesBox, ��ǰǰ��Ϊ�ذ�, ǰǰ�������, ǰ��desMan, �˱��
	* 4(2):ǰ��ΪdesBox,��ǰǰ��Ϊdes,ǰǰ���desBox,ǰ��desMan,�˱��For manicon
	*/
	
	//markΪ0��ʾmanicon,Ϊ1��ʾdesMan

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


//����:�����Ӷ�����Ŀ�ĵ�ʱִ��, ������ȷ, ���ں���gameOver
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


//����:��ѡ��ʱ�����йؿ�����,����true
bool clickYes(MOUSEMSG* m, int i, int x[TOTAL_LEVEL], int y[TOTAL_LEVEL]) {
	return(m->x >= x[i] && m->x < x[i] + LENGTH * 2 && m->y >= y[i] && m->y < y[i] + LENGTH * 2);
}


//����:ѡ��ؿ�
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
		m = GetMouseMsg();                     //��ȡ�����Ϣ,����ṹm��
		if (m.uMsg == WM_LBUTTONDOWN) {        //�������
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





//����:������Ϸ
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


//������ͳ�Ʋ���ʾ����
void showsteps(int* steps) {

	char words[100];
	memset(words, 0, 100);
	settextcolor(BLACK);
	settextstyle(40, 0, _T("����"));
	setbkmode(TRANSPARENT);
	sprintf_s(words, "���߲�����%d", *steps);
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


//����:���ռ�����������gameControl
void getKey(int* level, int map[TOTAL_LEVEL][LINE][COLUMN], int* X, int* Y, int* status, int* out, bool* menutool) {
	man.x = *X;
	man.y = *Y;
	int steps=0;
	

	IMAGE caidan,menuground;
	loadimage(&caidan, _T("caidan.bmp"), 600, 400, true);

	MOUSEMSG mToMenu;


	bool endGame;
	do {


		//ͨ��������������������
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
			if (mToMenu.uMsg == WM_LBUTTONDOWN) {  //������������ʱ

				if (mToMenu.x >= 45 && mToMenu.x <= 120 && mToMenu.y >= 20 && mToMenu.y <= 110) {  //���в˵�Сͼ��
					loadimage(&menuground, _T("menuground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
					putimage(0, 0, &menuground);
					putimage(150, 150, &caidan);   //�򿪲˵�
					while (1) {
						mToMenu = GetMouseMsg();
						if (mToMenu.uMsg == WM_LBUTTONDOWN) {
							//�ؿ�
							if (mToMenu.x >= 315 && mToMenu.x <= 585 && mToMenu.y >= 263 && mToMenu.y <= 306) {
								*status = 0;
								closegraph();
								return;
							}

							//ѡ��
							else if (mToMenu.x >= 315 && mToMenu.x <= 585 && mToMenu.y >= 361 && mToMenu.y <= 414) {
								*status = 0;
								closegraph();
								chooseLevel(level);
								return;
							}

							//�������˵�
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


