#ifndef _UI_H_
#define _UI_H_
#include "Status.h"
#include "File.h"
#include "ShortestPath.h"
#include "Flow.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
void MainMenu();
void HintInput();
Status GetOpNum(char* op, const char* ops[], int size, int *opnum);
void ShowERROR();
void Manage();
void Calc();
void ShowHelp();
#endif // _UI_H_