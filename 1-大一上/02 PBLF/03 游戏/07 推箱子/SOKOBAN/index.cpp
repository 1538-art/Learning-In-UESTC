/*******************************************************************************
                                  SOKOBAN 1.0
 *******************************************************************************

*******************************************************************************/

#include <ctype.h>
#include <signal.h>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>

extern "C" {
#include "game_rankings.h"
}

#include "loop.h"

#pragma comment(lib, "winmm.lib")

#define COMMAND_NUM 4

LinkNode* L = NULL;

int main()
{
    mciSendString(_T("open  song.mp3 alias music"), 0, 0, 0);
    mciSendString(TEXT("play music repeat"), 0, 0, 0);
        
    while (1) {
        char name[NAME_SIZE] = { '\0' };
        initgraph(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        IMAGE mainMenu;
        loadimage(&mainMenu, _T("zhujiemian.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
        putimage(0, 0, &mainMenu);
        MOUSEMSG msg;
        int getOut = 1;
        do {

            if (MouseHit()) {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    if (msg.x > 145 && msg.x < 380 && msg.y > 257 && msg.y < 330) {
                        closegraph();
                        int out = 0;
                        getOut = 0;
                        int scores = 0;
                        char ch;
                        int pos = 0;
                        printf("\n\n\n\n\n\n\n\n\n\n\n\n                                        Please input player's name:  ");
                        while ((ch = getchar()) != '\n')
                        {
                            name[pos++] = ch;
                        }
                        name[pos] = '\0';
                        load_rankings(&L);
                        loop(&out, name, &scores);
                        add_rankings(name, scores, &L);
                        sort_rankings(&L);
                        save_to_file(L);
                        system("cls");
                    }
                    else if (msg.x > 145 && msg.x < 380 && msg.y > 345 && msg.y < 420) {
                        closegraph();
                        printf("Ranking List\n");
                        show_rankings();
                        printf("Enter 1 to return to the main menu");
                        bool goOn = true;
                        while (goOn) {
                            int a;
                            scanf("%d", &a);
                            if (a == 1) {
                                goOn = false;
                                getchar();
                            }
                            getOut = 0;
                            system("cls");
                        }
                    }
                    else if (msg.x > 145 && msg.x < 380 && msg.y > 430 && msg.y < 495) {
                        closegraph();
                        exit(0);
                    }
                    else if (msg.x > 430 && msg.x < 650 && msg.y > 257 && msg.y < 330) {
                        closegraph();
                        reset_rankings(&L);
                        delete_file();
                        getOut = 0;
                    }
                    else if (msg.x > 430 && msg.x < 650 && msg.y > 345 && msg.y < 420) {
                        closegraph();
                        load_rankings(&L);
                        printf("Enter the ID you want to delete:");
                        char ch;
                        int pos = 0;
                        while ((ch = getchar()) != '\n')
                        {
                            name[pos] = ch;
                            pos++;
                        }
                        name[pos] = '\0';
                        delete_rankings(&L, name);
                        save_to_file(L);
                        getOut = 0;
                        system("cls");
                    }
                }
            } 
        } while (getOut == 1);
    }
    return 0;
}

           
       
        
        
        
  
    
