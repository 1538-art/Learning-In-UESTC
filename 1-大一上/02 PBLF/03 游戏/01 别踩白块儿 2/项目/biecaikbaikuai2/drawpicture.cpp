#include "sumup.h"

void drawMainMap() {
	initgraph(400, 700, EW_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();

	settextstyle(45, 0, "黑体");
	settextcolor(BLACK);
	outtextxy(160, 30, "极音");

	setfillcolor(BLACK);
	fillroundrect(100, 150, 300, 250, 100, 100);
	settextstyle(25, 0, "黑体");
	outtextxy(155, 190, "song 1");

	setfillcolor(BLACK);
	fillroundrect(100, 280, 300, 380, 100, 100);
	settextstyle(25, 0, "黑体");
	outtextxy(155, 320, "song 2");

	setfillcolor(BLACK);
	fillroundrect(100, 410, 300, 510, 100, 100);
	settextstyle(25, 0, "黑体");
	outtextxy(155, 450, "song 3");

	setfillcolor(BLACK);
	fillroundrect(100, 540, 300, 640, 100, 100);
	settextstyle(25, 0, "黑体");
	outtextxy(155, 580, "song 4");
}
