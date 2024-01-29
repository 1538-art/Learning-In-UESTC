#include "../include/File.h"
#include "../include/Flow.h"
#include "../include/UI.h"
#include "../include/ShortestPath.h"
#include "../include/Status.h"
#define N 10005
int main() {
    const char* MainMenuOperations[] = {"manage", "calc", "help", "quit"};
    while(true) {
        MainMenu:
        MainMenu();
        HintInput();
        char operation[100];
        scanf("%s", operation);
        int opnum; 
        if(GetOpNum(operation, MainMenuOperations, 4, &opnum) == ERROR) {
            ShowERROR();
            goto MainMenu;
        } 
        switch (opnum) {
            case 0: // manage
                Manage();
                break;
            case 1: // calc
                Calc();
                break;
            case 2: // help 
                ShowHelp();
                break;
            case 3: // quit
                exit(0);
                break;
            default: // 
                break;
        }
    }

    return 0;
}