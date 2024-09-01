//编码格式：UTF-8，在cmd运行可能乱码，如果想在cmd打开程序，请运行“maliao-cmd”程序并将窗口调至最大~~

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include<unistd.h>
#include <stdlib.h>

#define MAP_WIDTH 150
#define MAP_HEIGHT 12

#define EMPTY ' '
#define WALL '#'
#define COIN '$'
#define PLAYER '@'
#define EXIT 'X'
#define MOSTER 'Q'

#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100
#define KEY_QUIT 48

void init(char map3[22][52], int snake[400][3]);
void makeMap3(char map3[22][52], int snake[400][3], int food[]);
void move(int snake[400][3], int direct);
void makeFood(int food[]);
void showView(char map3[22][52]);  
int ifEat(int head, int food[2]); 
int ifReprat(int snake[400][3], int x, int y);
int ifBump(int head);
void getKey();

int flag = 1;
int mark2 = 1,mark3 = 1,mark4 = 1,mark5 = 1,mark6 = 1;

int food[2];
int head;
int snake[400][3];
int W = 52;
int H = 22;
int direct = 4;

char map3[22][52];

char map[MAP_HEIGHT][MAP_WIDTH] = 
{
    "################################################",
    "#@                                     $       #",
    "#      $                                       #",
    "#                                              #",
    "#         $                     $              #",
    "#                                              #",
    "#                                              #",
    "#                $                             #",
    "#    X                                  $      #",
    "################################################"
};

char map2[MAP_HEIGHT][MAP_WIDTH] = 
{
    "################################################################################################################################################",
    "#                  $                                                                   $                                               $       #",
    "#           ############                        --------->                         ## ##  #  #  #  #########           $                       #",
    "#                                               --------->                                                             ##########              #",
    "#                           ###                                               ###                                                              #",
    "#      ###                  ###                                             ###                                $                    ##         #",
    "#      ###                  ###                                           ###                                                       ##         #",
    "#      ###          $       ###                                         ## X              $                                         ##         #",
    "###################################################    #########################################################################################",
    "                                                  #    #                                                                                        ",
    "                                                  #$   #                                                                                        ",
    "                                                  ######                                                                                        "
};

void drawMap(int s)
{
    printf("\033[2J");
    printf("Use wasd to control your direction.\n");
    for (int i = 0; i < MAP_HEIGHT; i++) {
        printf("%s\n", map[i]);
    }
    printf("your score:%d\n",s);
}

void drawMap2(int s)
{
    printf("\033[2J");
    printf("Use wasd to control your direction.\n");
    for (int i = 0; i < MAP_HEIGHT; i++) {
        printf("%s\n", map2[i]);
    }
    printf("your score:%d\n",s);
}

void moster1(int *my,int *mx)
{
    int x,y;
    x = *mx;
    y = *my;
    srand((unsigned)time(NULL));
    int m=rand()%4;
    switch(m)
            {
                case 0:
                if(map[*my + 1][*mx] != WALL && map[*my + 1][*mx] != COIN && map[*my + 1][*mx] != EXIT)
                (*my)++;
                break;
                case 1:
                if(map[*my - 1][*mx] != WALL && map[*my - 1][*mx] != COIN && map[*my - 1][*mx] != EXIT)
                (*my)--;
                break;
                case 2:
                if(map[*my][*mx + 1] != WALL && map[*my][*mx + 1] != COIN && map[*my][*mx + 1] != EXIT)
                (*mx)++;
                break;
                case 3:
                if(map[*my][*mx - 1] != WALL && map[*my][*mx - 1] != COIN && map[*my][*mx - 1] != EXIT)
                (*mx)--;
                break;
                default:
                break;
            }
    map[y][x] = EMPTY;
    map[*my][*mx] = MOSTER;
}

void moster2(int *my,int *mx)
{
    int x,y;
    x = *mx;
    y = *my;
    usleep(100);
    srand((unsigned)time(NULL));
    int m=rand()%4;
    switch(m)
            {
                case 0:
                if(map[*my + 1][*mx] != WALL && map[*my + 1][*mx] != COIN && map[*my + 1][*mx] != EXIT)
                (*my)++;
                break;
                case 1:
                if(map[*my - 1][*mx] != WALL && map[*my - 1][*mx] != COIN && map[*my - 1][*mx] != EXIT)
                (*my)--;
                break;
                case 2:
                if(map[*my][*mx + 1] != WALL && map[*my][*mx + 1] != COIN && map[*my][*mx + 1] != EXIT)
                (*mx)++;
                break;
                case 3:
                if(map[*my][*mx - 1] != WALL && map[*my][*mx - 1] != COIN && map[*my][*mx - 1] != EXIT)
                (*mx)--;
                break;
                default:
                break;
            }
    map[y][x] = EMPTY;
    map[*my][*mx] = MOSTER;
}

void moster3(int *my,int *mx)
{
    int x,y;
    x = *mx;
    y = *my;
    srand((unsigned)time(NULL));
    int m=rand()%4;
    switch(m)
            {
                case 3:
                if(map[*my + 1][*mx] != WALL && map[*my + 1][*mx] != COIN && map[*my + 1][*mx] != EXIT)
                (*my)++;
                break;
                case 0:
                if(map[*my - 1][*mx] != WALL && map[*my - 1][*mx] != COIN && map[*my - 1][*mx] != EXIT)
                (*my)--;
                break;
                case 2:
                if(map[*my][*mx + 1] != WALL && map[*my][*mx + 1] != COIN && map[*my][*mx + 1] != EXIT)
                (*mx)++;
                break;
                case 1:
                if(map[*my][*mx - 1] != WALL && map[*my][*mx - 1] != COIN && map[*my][*mx - 1] != EXIT)
                (*mx)--;
                break;
                default:
                break;
            }
    map[y][x] = EMPTY;
    map[*my][*mx] = MOSTER;
}

void moster4(int *my,int *mx)
{
    int x,y;
    x = *mx;
    y = *my;
    srand((unsigned)time(NULL)*(unsigned)time(NULL));
    int m=rand()%4;
    switch(m)
            {
                case 0:
                if(map[*my + 1][*mx] != WALL && map[*my + 1][*mx] != COIN && map[*my + 1][*mx] != EXIT)
                (*my)++;
                break;
                case 3:
                if(map[*my - 1][*mx] != WALL && map[*my - 1][*mx] != COIN && map[*my - 1][*mx] != EXIT)
                (*my)--;
                break;
                case 2:
                if(map[*my][*mx + 1] != WALL && map[*my][*mx + 1] != COIN && map[*my][*mx + 1] != EXIT)
                (*mx)++;
                break;
                case 1:
                if(map[*my][*mx - 1] != WALL && map[*my][*mx - 1] != COIN && map[*my][*mx - 1] != EXIT)
                (*mx)--;
                break;
                default:
                break;
            }
    map[y][x] = EMPTY;
    map[*my][*mx] = MOSTER;
}

void Movemoster2(int *my,int *mx)
{
    int x,y;
    x = *mx;
    y = *my;
    if((map2[*my][*mx + 1] == EMPTY||map2[*my][*mx + 1] == PLAYER) && map2[*my + 1][*mx + 1] == WALL && mark2 == 1)
    {
        (*mx)++;
    }
    else if((map2[*my][*mx - 1] == EMPTY||map2[*my][*mx - 1] == PLAYER) && map2[*my + 1][*mx - 1] == WALL)
    {
        (*mx)--;
        mark2 = 0;
    }
    else
    {
        mark2 = 1;
    }
    map2[y][x] = EMPTY;
    map2[*my][*mx] = MOSTER;
}

void Movemoster3(int *my,int *mx)
{
    int x,y;
    x = *mx;
    y = *my;
    if((map2[*my][*mx + 1] == EMPTY||map2[*my][*mx + 1] == PLAYER) && map2[*my + 1][*mx + 1] == WALL && mark3 == 1)
    {
        (*mx)++;
    }
    else if((map2[*my][*mx - 1] == EMPTY||map2[*my][*mx - 1] == PLAYER) && map2[*my + 1][*mx - 1] == WALL)
    {
        (*mx)--;
        mark3 = 0;
    }
    else 
    {
        mark3 = 1;
    }
    map2[y][x] = EMPTY;
    map2[*my][*mx] = MOSTER;
}

void Movemoster4(int *my,int *mx)
{
    int x,y;
    x = *mx;
    y = *my;
    if((map2[*my][*mx + 1] == EMPTY||map2[*my][*mx + 1] == PLAYER) && map2[*my + 1][*mx + 1] == WALL && mark4 == 1)
    {
        (*mx)++;
    }
    else if((map2[*my][*mx - 1] == EMPTY||map2[*my][*mx - 1] == PLAYER) && map2[*my + 1][*mx - 1] == WALL)
    {
        (*mx)--;
        mark4 = 0;
    }
    else
    {
        mark4 = 1;
    }
    map2[y][x] = EMPTY;
    map2[*my][*mx] = MOSTER;
}

void Movemoster5(int *my,int *mx)
{
    int x,y;
    x = *mx;
    y = *my;
    if((map2[*my][*mx + 1] == EMPTY||map2[*my][*mx + 1] == PLAYER) && map2[*my + 1][*mx + 1] == WALL && mark5 == 1)
    {
        (*mx)++;
    }
    else if((map2[*my][*mx - 1] == EMPTY||map2[*my][*mx - 1] == PLAYER) && map2[*my + 1][*mx - 1] == WALL)
    {
        (*mx)--;
        mark5 = 0;
    }
    else
    {
        mark5 = 1;
    }
    map2[y][x] = EMPTY;
    map2[*my][*mx] = MOSTER;
}

void Movemoster6(int *my,int *mx)
{
    int x,y;
    x = *mx;
    y = *my;
    if((map2[*my][*mx + 1] == EMPTY||map2[*my][*mx + 1] == PLAYER) && map2[*my + 1][*mx + 1] == WALL && mark6 == 1)
    {
        (*mx)++;
    }
    else if((map2[*my][*mx - 1] == EMPTY||map2[*my][*mx - 1] == PLAYER) && map2[*my + 1][*mx - 1] == WALL)
    {
        (*mx)--;
        mark6 = 0;
    }
    else 
    {
        mark6 = 1;
    }
    map2[y][x] = EMPTY;
    map2[*my][*mx] = MOSTER;
}

void jump(int *playerY,int *playerX,int *s)
{
if (flag == 1)
{
for(int i=0;i<=2;i++)
{
    if (map2[*playerY - 1][*playerX] != WALL && map2[*playerY - 1][*playerX + 1] != WALL) 
    {
        map2[*playerY][*playerX] = EMPTY;
        *playerY = *playerY - 1;
        *playerX = *playerX + 1;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
        else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
        usleep(200000);
        drawMap2(*s);
    }
    else if(map2[*playerY - 1][*playerX] != WALL && map2[*playerY - 1][*playerX + 1] == WALL)
    {
        map2[*playerY][*playerX] = EMPTY;
        *playerY = *playerY - 1;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        } 
        else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
        usleep(300000);
        drawMap2(*s);
    }
    else if(map2[*playerY - 1][*playerX] == WALL && map2[*playerY][*playerX + 1] != WALL)
    {
        map2[*playerY][*playerX] = EMPTY;
        *playerX = *playerX+1;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
        else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
        usleep(300000);
        drawMap2(*s);
    }
}

while (map2[*playerY + 1][*playerX] != WALL && map2[*playerY + 1][*playerX + 1] != WALL)
{
    map2[*playerY][*playerX] = EMPTY;
    *playerY = *playerY + 1;
    *playerX = *playerX + 1;
    if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
    else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        }   
    map2[*playerY][*playerX] = PLAYER;
    usleep(300000);
    drawMap2(*s);
}

while((map2[*playerY + 1][*playerX] != WALL && map2[*playerY + 1][*playerX + 1] == WALL)||(map2[*playerY + 1][*playerX] != WALL && map2[*playerY][*playerX + 1] == WALL) || (map2[*playerY + 1][*playerX] != WALL && map2[*playerY + 1][*playerX + 1] != WALL))
{
    map2[*playerY][*playerX] = EMPTY;
    *playerY = *playerY+1;
    if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
    else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        }  
    map2[*playerY][*playerX] = PLAYER;
    usleep(300000);
    drawMap2(*s);
}
}

else if(flag == -1)
{
    for(int i=0;i<=2;i++)
{
    if (map2[*playerY - 1][*playerX] != WALL && map2[*playerY - 1][*playerX - 1] != WALL) 
    {
        map2[*playerY][*playerX] = EMPTY;
        *playerY = *playerY - 1;
        *playerX = *playerX - 1;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
        else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
        usleep(200000);
        drawMap2(*s);
    }
    else if(map2[*playerY - 1][*playerX] != WALL && map2[*playerY - 1][*playerX - 1] == WALL)
    {
        map2[*playerY][*playerX] = EMPTY;
        *playerY = *playerY - 1;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
        else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
        usleep(300000);
        drawMap2(*s);
    }
    else if(map2[*playerY - 1][*playerX] == WALL && map2[*playerY][*playerX - 1] != WALL)
    {
        map2[*playerY][*playerX] = EMPTY;
        *playerX = *playerX - 1;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
         else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
        usleep(300000);
        drawMap2(*s);
    }
}
while (map2[*playerY + 1][*playerX] != WALL && map2[*playerY + 1][*playerX - 1] != WALL)
{
    map2[*playerY][*playerX] = EMPTY;
    *playerY = *playerY + 1;
    *playerX = *playerX - 1;
    if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
    else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
    map2[*playerY][*playerX] = PLAYER;
    usleep(300000);
    drawMap2(*s);
}

while((map2[*playerY + 1][*playerX] != WALL && map2[*playerY + 1][*playerX - 1] == WALL)||(map2[*playerY + 1][*playerX] != WALL && map2[*playerY][*playerX - 1] == WALL) || (map2[*playerY + 1][*playerX] != WALL && map2[*playerY + 1][*playerX - 1] != WALL))
{
    map2[*playerY][*playerX] = EMPTY;
    *playerY = *playerY + 1;
    if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
    else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
    map2[*playerY][*playerX] = PLAYER;
    usleep(300000);
    drawMap2(*s);
}
}
}

void goleft(int *playerY,int *playerX,int *s)
{
    if (map2[*playerY][*playerX - 1] != WALL && map2[*playerY][*playerX - 1] != EXIT) 
    {
        map2[*playerY][*playerX] = EMPTY;
        (*playerX)--;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
        else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
    }
    else if(map2[*playerY][*playerX - 1] == EXIT && *s == 8)
    {
        map2[*playerY][*playerX] = EMPTY;
        drawMap2(*s);
        printf("Congratulations!\n");
        sleep(10);
        exit(1);
    }
    else if(map2[*playerY][*playerX - 1] == EXIT && *s != 8)
    {
        map2[*playerY][*playerX] = EMPTY;
        drawMap2(*s);
        printf("Try harder next time ~~\n");
        sleep(10);
        exit(1);
    }

    while(map2[*playerY + 1][*playerX] != WALL)
    {
        map2[*playerY][*playerX] = EMPTY;
        (*playerY)++;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
        else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
        usleep(300000);
        drawMap2(*s);
    }
}

void goright(int *playerY,int *playerX,int *s)
{
    if (map2[*playerY][*playerX + 1] != WALL && map2[*playerY][*playerX + 1] != EXIT) 
    {
        map2[*playerY][*playerX] = EMPTY;
        (*playerX)++;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
        else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
    }
    else if(map2[*playerY][*playerX + 1] == EXIT && *s == 8)
    {
        map2[*playerY][*playerX] = EMPTY;
        drawMap2(*s);
        printf("Congratulations!\n");
        sleep(10);
        exit(1);
    }
    else if(map2[*playerY][*playerX + 1] == EXIT && *s != 8)
    {
        map2[*playerY][*playerX] = EMPTY;
        drawMap2(*s);
        printf("Try harder next time ~~\n");
        sleep(10);
        exit(1);
    }

    while(map2[*playerY + 1][*playerX] != WALL)
    {
        map2[*playerY][*playerX] = EMPTY;
        (*playerY)++;
        if (map2[*playerY][*playerX] == COIN) 
        {
            map2[*playerY][*playerX] = EMPTY;
            *s = *s + 1;
        }
        else if(map2[*playerY][*playerX] == MOSTER)
        {
            map2[*playerY][*playerX] = MOSTER;
            drawMap2(*s);
            printf("You lose the game!\n");
            sleep(10);
            exit(1);
        } 
        map2[*playerY][*playerX] = PLAYER;
        usleep(300000);
        drawMap2(*s);
    }
}

void init(char map3[22][52], int snake[400][3]) {
	
	snake[0][0] = 1, snake[0][1] = 9, snake[0][2] = 9;
	
	srand(time(0));
	food[0] = rand() % 19 + 2;
	food[1] = rand() % 49 + 2;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i == 0 || j == 0 || i == H - 1 || j == W - 1) {
				map3[i][j] = '*';
			}
			else {
				map3[i][j] = ' ';
			}
		}
	}
}

void getKey() {
	int key = _getch();
	switch (key) {
	case KEY_UP:
		if (direct != 2)
			direct = 1;
		break;
	case KEY_DOWN:
		if (direct != 1)
			direct = 2;
		break;
	case KEY_LEFT:
		if (direct != 4)
			direct = 3;
		break;
	case KEY_RIGHT:
		if (direct != 3)
			direct = 4;
		break;
    case KEY_QUIT:
            exit(1);
            break;
	}
}

void move(int snake[400][3], int direct) {
	int x, y;
	for (int i = 0; i < 400; i++) {
		if (snake[i][0] == 1) {
			head = i;
			break;
		}
	}
	
	x = snake[head][1];
	y = snake[head][2];
	switch (direct) {
	case 1:
		snake[head][1]--;
		break;
	case 2:
		snake[head][1]++;
		break;
	case 3:
		snake[head][2]--;
		break;
	case 4:
		snake[head][2]++;
		break;
	}
	
	if (ifEat(head, food)) {
		snake[head + 1][0] = 1, snake[head + 1][1] = food[0], snake[head + 1][2] = food[1];
		snake[head][0] = 0;
		food[0] = 0, food[1] = 0;
		switch (direct) {
		case 1:
			snake[head][1]++;
			break;
		case 2:
			snake[head][1]--;
			break;
		case 3:
			snake[head][2]++;
			break;
		case 4:
			snake[head][2]--;
			break;
		}
	}
	else
		for (int j = head - 1; j >= 0; j--) {
			int temp;
			temp = x, x = snake[j][1], snake[j][1] = temp;
			temp = y, y = snake[j][2], snake[j][2] = temp;
		}
}

int ifEat(int head, int food[2]) {
	if (snake[head][1] == food[0] && snake[head][2] == food[1])
		return 1;
	else
		return 0;
}

void makeFood(int food[]) {
	srand(time(0));
	int x = rand() % 49 + 2, y = rand() % 19 + 2;
	while (ifReprat(snake, x, y)) {
		x = rand() % 49 + 2, y = rand() % 19 + 2;
	}
	food[0] = y;
	food[1] = x;
}

int ifReprat(int snake[400][3], int x, int y) {
	for (int i = 0; i < 400; i++) {
		if ((snake[i][1] == x && snake[i][2] == y)) {
			return 1;
			if (snake[i][0] == 1) break;
		}
	}
	return 0;
}

void makeMap3(char map[22][52], int snake[400][3], int food[]) {
	int i;
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i == 0 || j == 0 || i == H - 1 || j == W - 1) {
				map[i][j] = '*';
			}
			else {
				map[i][j] = ' ';
			}
		}
	}
	
	for (i = 0; i < 400; i++) {
		if (snake[i][0] == 1) break;
		map[snake[i][1]][snake[i][2]] = '+';
	}
	
	map[snake[i][1]][snake[i][2]] = '@';
	map[food[0]][food[1]] = 'o';
}

void showView(char map[22][52]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

int ifBump(int head) {
	if ((snake[head][2] == 0 || snake[head][2] == 51) || (snake[head][1] == 0 || snake[head][1] == 21))
		return 1;
	for (int i = 0; i < head - 3; i++) {
		if ((snake[i][1] == snake[head][1] && snake[i][2] == snake[head][2])) {
			return 1;
		}
	}
	return 0;
}

int main() {
    
int x = 1,y = 1,score = 0;
int level; 

printf("\033[2J");
printf("Use wasd to control your direction.\n\n\nDon't be touched by the monster Q!\nTry your best to get more score $!\nWent to the exit X to get success!\n\n\nChoose a game(1 - 3)!\nPress 0 to quit the game.\n\nPS:请一下一下按按键，避免长按和连按哦！\nPSS:如果在独立窗口运行，请将窗口调至最大~~\n");
scanf("%d",&level);
if(level == 1)
{
    int moster1_X = 25,moster2_X = 15,moster3_X = 35,moster4_X = 10;
    int moster1_Y = 5,moster2_Y = 3,moster3_Y = 7,moster4_Y = 2;
    int playerX = 1;
    int playerY = 1;
    while (1) {
        drawMap(score);
        int key = getch();
        x = playerX;
        y = playerY;
        switch (key) {
            case KEY_UP:
                if (map[playerY - 1][playerX] != WALL) {
                    playerY--;
                }
                break;
            case KEY_DOWN:
                if (map[playerY + 1][playerX] != WALL) {
                    playerY++;
                }
                break;
            case KEY_LEFT:
                if (map[playerY][playerX - 1] != WALL) {
                    playerX--;
                }
                break;
            case KEY_RIGHT:
                if (map[playerY][playerX + 1] != WALL) {
                    playerX++;
                }
                break;
            case KEY_QUIT:
                return 0;
                break;
        }

        if (map[playerY][playerX] == COIN) 
        {
            map[playerY][playerX] = EMPTY;
            score = score+1;
        } 
        else if (map[playerY][playerX] == EXIT && score == 6) 
        {
            map[y][x] = EMPTY;
            drawMap(score);
            printf("Congratulations! NB!\n");
            sleep(10);
            return 0;
        }
        else if (map[playerY][playerX] == EXIT && score != 6) 
        {
            map[y][x] = EMPTY;
            drawMap(score);
            printf("Try harder next time ~~\n");
            sleep(10);
            return 0;
        }
        map[y][x] = EMPTY;
        map[playerY][playerX] = PLAYER;
        moster1(&moster1_Y,&moster1_X);
        moster2(&moster2_Y,&moster2_X);
        moster3(&moster3_Y,&moster3_X);
        moster4(&moster4_Y,&moster4_X);
        if(playerY == moster1_Y && playerX == moster1_X || playerY == moster2_Y && playerX == moster2_X || playerY == moster3_Y && playerX == moster3_X || playerY == moster4_Y && playerX == moster4_X)
        {
            drawMap(score);
            printf("You lose the game!\n");
            sleep(10);
            return 0;
        }
    }
}

else if(level == 2)
{
    int moster1_X = 12,moster2_X = 10,moster3_X = 53,moster4_X = 77,moster5_X = 120,moster6_X = 135,moster7_X = 83;
    int moster1_Y = 1,moster2_Y = 7,moster3_Y = 10,moster4_Y = 7,moster5_Y = 2,moster6_Y = 7,moster7_Y = 1;
    int player_X = 1;
    int player_Y = 7;
    int i=0;  
    map2[player_Y][player_X] = PLAYER;
while (1) 
{
    drawMap2(score);
    int key = getch();
    x = player_X;
    y = player_Y;
    switch (key) 
    {
        case KEY_UP:
            jump(&player_Y,&player_X,&score);
            break;
        case KEY_LEFT:
            goleft(&player_Y,&player_X,&score);
            flag = -1;
            break;
        case KEY_RIGHT:
            goright(&player_Y,&player_X,&score);
            flag = 1;
            break;
        case KEY_QUIT:
            return 0;
            break;
    }
Movemoster2(&moster2_Y,&moster2_X);
Movemoster3(&moster3_Y,&moster3_X);
Movemoster4(&moster4_Y,&moster4_X);
Movemoster5(&moster5_Y,&moster5_X);
Movemoster6(&moster6_Y,&moster6_X);

if(map2[player_Y][player_X] == MOSTER)
{
    map2[player_Y][player_X] = MOSTER;
    drawMap2(score);
    printf("You lose the game!\n");
    sleep(10);
    return 0;
} 
    map2[y][x] = EMPTY;
    map2[player_Y][player_X] = PLAYER;
}
return 0;
}

else if(level == 3)
{
    init(map3, snake);
	while (1) {
		printf("\033[2J");
		usleep(300);
		move(snake, direct);
		if (!food[0] && !food[1]) {
			makeFood(food);
		}
		makeMap3(map3, snake, food);
		showView(map3);
		if (ifBump(head)) {
			printf("GameOver!your score is: %d", head);
			break;
		}
		getKey();
	}
	return 0;
}
else
{
    return 0;
}
    return 0;
}