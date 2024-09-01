#pragma once


//头文件
#include <graphics.h>
#include <conio.h>
#include <stdio.h>




//宏
#define TOTAL_LEVEL 10   //关卡数  
#define LINE 12         //最大行数
#define COLUMN 15       //最大列数
#define LENGTH 50       //每个元素的边长
//游戏窗口的大小
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 750
//初始第一块元素的位置
#define START_X 100
#define START_Y 120
//按下键盘上的键所对应字符,之后放到别的文件中
#define KEY_UP      'w'  //上移
#define KEY_DOWN    's'  //下移
#define KEY_LEFT    'a'  //左移
#define KEY_RIGHT   'd'  //右移
#define KEY_RESTART 'r'  //重新开始
//a
#define KEY_CHOOSE  'c'  //选择关卡
#define KEY_OUT     'o'  //返回主界面



//枚举
//元素
enum _OBJECT {
    empty,           //0  不加载图片
    wall,            //1  墙  
    des,		     //2  箱子目的地
    manicon,		 //3  小人
    box,	         //4  箱子
    desBox,			 //5  箱子达到目的地后变成desBox
    Floor,           //6  地板
    desMan,     //7  小人在目的地上的状态
    total            //  元素数量

};
//用数字表示↑↓←→,作为gameControl的参数
enum _DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
typedef _DIRECTION direction;



//结构
//表示元素坐标
struct _POS {
    int x;
    int y;
};
typedef _POS pos;


//函数
void setWindowSize();
void setBackground(int* level);
void addPictures(int* level, int* X, int* Y,int map[TOTAL_LEVEL][LINE][COLUMN]);
void getKey(int* level, int map[TOTAL_LEVEL][LINE][COLUMN], int* X, int* Y,int* status,int* out,bool* menutool);
void chooseLevel(int* level);




