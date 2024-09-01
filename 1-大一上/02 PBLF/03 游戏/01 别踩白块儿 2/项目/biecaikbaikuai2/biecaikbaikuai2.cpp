#include "sumup.h"
#include "drawpicture.h"
#include "playmovement.h"

FILE* file1 = fopen("songs//Castle in the sky.txt", "r");
FILE* file2 = fopen("songs//Fish in the pool.txt", "r");
FILE* file3 = fopen("songs//MissaIceCity.txt", "r");
FILE* file4 = fopen("songs//Oceans of Stars.txt", "r");
FILE* file;//音乐文件
// 音符对应的频率映射表

const char* notes[] = { "C3,", "C3#", "D3,", "D3#", "E3,", "F3,", "F3#", "G3,", "G3#", "A3,", "A3#", "B3,",
				        "C4,", "C4#", "D4,", "D4#", "E4,", "F4,", "F4#", "G4,", "G4#", "A4,", "A4#", "B4,",
				        "C5,", "C5#", "D5,", "D5#", "E5,", "F5,", "F5#", "G5,", "G5#", "A5,", "A5#", "B5," };

double frequencies[] = { 130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94,
						 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88,
						 523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00, 932.33, 987.77 };  // 对应C3到B5

#define INTERVAL 100 //最上面的间隔
char note[4];//音符音名
int duration;//音符时长
double fre = 1.0;//改变fre来改变音乐的八度
double spe = 1.0;//改变音乐的速度
int score;
//表示黑块
int flag[4];

void initFlag()
{
	for (int i = 0; i < 4; i++)
	{
		flag[i] = rand() % 4;	//[0-4)
		//printf("%d ", flag[i]);
	}
}

void playNote(char* note, int duration)//音符播放函数
{
	// 查找音符在映射表中的位置
	int index = -1;
	for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); ++i)
	{
		if (strcmp(notes[i], note) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) 
	{
		// 处理无效音符
		fprintf(stderr, "Invalid note: %s\n", note);
		return;
	}

	// 计算音符对应的频率
	double frequency = frequencies[index];

	// 播放声音
	Beep(frequency * fre, duration * spe);
}

bool boardEvent()
{
	int x = flag[3] * 100;
	int y = 3 * 150 + INTERVAL;
	if (GetKeyState(68) < 0)
	{
		if (x == 0 && y == 550)
		{
			cleardevice();
			//整体移动，数组元素后移
			for (int i = 3; i > 0; i--)
			{
				flag[i] = flag[i - 1];
			}
			//把第一个黑快重新生成
			flag[0] = rand() % 4;
			score += 1;
			drawMap();
			if (fscanf(file, " %3s %d", note, &duration) == 2) // 从文件中读取音符和时长，然后播放声音
			{
				playNote(note, duration);
			}else return false;
		}else return false;
	}else if (GetKeyState(70) < 0)
	{
		if (x == 100 && y == 550)
		{
			cleardevice();
			for (int i = 3; i > 0; i--)
			{
				flag[i] = flag[i - 1];
			}
			flag[0] = rand() % 4;
			score += 1;
			drawMap();
			if (fscanf(file, " %3s %d", note, &duration) == 2)// 从文件中读取音符和时长，然后播放声音
			{
				playNote(note, duration);
			}else return false;
		}else return false;
	}else if (GetKeyState(74) < 0)
	{
		if (x == 200 && y == 550)
		{
			cleardevice();
			for (int i = 3; i > 0; i--)
			{
				flag[i] = flag[i - 1];
			}
			flag[0] = rand() % 4;
			score += 1;
			drawMap();
			if (fscanf(file, " %3s %d", note, &duration) == 2)// 从文件中读取音符和时长，然后播放声音
			{
				playNote(note, duration);
			}else return false;
		}else return false;
	}else if (GetKeyState(75) < 0)
	{
		if (x == 300 && y == 550)
		{
			cleardevice();
			for (int i = 3; i > 0; i--)
			{
				flag[i] = flag[i - 1];
			}
			flag[0] = rand() % 4;
			score += 1;
			drawMap();
			if (fscanf(file, " %3s %d", note, &duration) == 2)// 从文件中读取音符和时长，然后播放声音
			{
				playNote(note, duration);
			}else return false;
		}else return false;
	}
	return true;
}

void drawMap()
{
	settextstyle(25, 0, "黑体");
	settextcolor(RED);
	//输出文字
	outtextxy(150, 30, "别踩白块儿");

	TCHAR str[10] = { 0 };
	_stprintf_s(str, _T("score:%d"), score);
	outtextxy(0, 0, str);

	//设置线条样式
	setlinestyle(PS_SOLID, 2);
	setlinecolor(RGB(59, 59, 59));
	for (int i = 0; i < 5; i++)
	{
		line(0, i * 150 + INTERVAL, 400, i * 150 + INTERVAL);
		line(i * 100, INTERVAL, i * 100, 700);
	}
	//绘制黑快
	setfillcolor(BLACK);
	for (int i = 0; i < 4; i++)
	{
		int x = flag[i] * 100;
		int y = i * 150 + INTERVAL;
		fillrectangle(x, y, x + 100, y + 150);
	}
}

int main()
{
	mciSendString("open songs//12600.wav alias bgm", NULL, 0, NULL);

	int Play_message = 0;
	//main界面
		
	initgraph(400, 700);
	//设置背景颜色
	setbkcolor(WHITE);
	cleardevice();
	drawMainMap();
	flushmessage(EX_MOUSE);

	while (1) 
	{
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)	//左键按下
		{
			if (msg.y > 150 && msg.y < 250 && msg.x>100 && msg.x < 300)
			{
				file = file1;
				if (file == NULL)
				{
					perror("Error opening file");
					goto end;
				}
				break;
			}else if (msg.y > 280 && msg.y < 380 && msg.x>100 && msg.x < 300)
			{
				file = file2;
				if (file == NULL)
				{
					perror("Error opening file");
					goto end;
				}
				break;
			}else if (msg.y > 410 && msg.y < 510 && msg.x>100 && msg.x < 300)
			{
				fre = 2.0, spe = 1.05;
				file = file3;
				if (file == NULL)
				{
					perror("Error opening file");
					goto end;
				}
				break;
			}else if (msg.y > 540 && msg.y < 640 && msg.x>100 && msg.x < 300)
			{
				fre = 1.0, spe = 1.3;
				file = file4;
				if (file == NULL)
				{
					perror("Error opening file");
					goto end;
				}
				break;
			}else;
		}
		if (Play_message != 0) break;
	}
	mciSendString("play bgm", NULL, 0, NULL);
	Sleep(1500);
	mciSendString("close bgm", NULL, 0, NULL);

	//play界面
	initgraph(400, 700);
	setbkcolor(WHITE);
	cleardevice();

	//设置随机数种子
	srand((unsigned)time(NULL));

	initFlag();
	while (1)
	{
		drawMap();
		if (!boardEvent())
			break;
	}
	gameOver();
	closegraph();
    end:
	fclose(file);
	return 0;
}