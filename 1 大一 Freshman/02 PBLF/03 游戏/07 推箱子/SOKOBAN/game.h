#pragma once


//ͷ�ļ�
#include <graphics.h>
#include <conio.h>
#include <stdio.h>




//��
#define TOTAL_LEVEL 10   //�ؿ���  
#define LINE 12         //�������
#define COLUMN 15       //�������
#define LENGTH 50       //ÿ��Ԫ�صı߳�
//��Ϸ���ڵĴ�С
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 750
//��ʼ��һ��Ԫ�ص�λ��
#define START_X 100
#define START_Y 120
//���¼����ϵļ�����Ӧ�ַ�,֮��ŵ�����ļ���
#define KEY_UP      'w'  //����
#define KEY_DOWN    's'  //����
#define KEY_LEFT    'a'  //����
#define KEY_RIGHT   'd'  //����
#define KEY_RESTART 'r'  //���¿�ʼ
//a
#define KEY_CHOOSE  'c'  //ѡ��ؿ�
#define KEY_OUT     'o'  //����������



//ö��
//Ԫ��
enum _OBJECT {
    empty,           //0  ������ͼƬ
    wall,            //1  ǽ  
    des,		     //2  ����Ŀ�ĵ�
    manicon,		 //3  С��
    box,	         //4  ����
    desBox,			 //5  ���ӴﵽĿ�ĵغ���desBox
    Floor,           //6  �ذ�
    desMan,     //7  С����Ŀ�ĵ��ϵ�״̬
    total            //  Ԫ������

};
//�����ֱ�ʾ��������,��ΪgameControl�Ĳ���
enum _DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
typedef _DIRECTION direction;



//�ṹ
//��ʾԪ������
struct _POS {
    int x;
    int y;
};
typedef _POS pos;


//����
void setWindowSize();
void setBackground(int* level);
void addPictures(int* level, int* X, int* Y,int map[TOTAL_LEVEL][LINE][COLUMN]);
void getKey(int* level, int map[TOTAL_LEVEL][LINE][COLUMN], int* X, int* Y,int* status,int* out,bool* menutool);
void chooseLevel(int* level);




