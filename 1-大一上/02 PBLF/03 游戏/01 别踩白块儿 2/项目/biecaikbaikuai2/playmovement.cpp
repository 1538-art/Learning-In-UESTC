#include "sumup.h"
#include "drawpicture.h"

void gameOver()
{
	settextstyle(25, 0, "����");
	settextcolor(RED);
	//���������Ϸ����
	outtextxy(150, 30, "Game Over��");
	MessageBox(GetHWnd(), "Game Over��", "LLLL", MB_OK);
}