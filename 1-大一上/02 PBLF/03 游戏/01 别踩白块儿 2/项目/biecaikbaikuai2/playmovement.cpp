#include "sumup.h"
#include "drawpicture.h"

void gameOver()
{
	settextstyle(25, 0, "黑体");
	settextcolor(RED);
	//输出文字游戏结束
	outtextxy(150, 30, "Game Over！");
	MessageBox(GetHWnd(), "Game Over！", "LLLL", MB_OK);
}