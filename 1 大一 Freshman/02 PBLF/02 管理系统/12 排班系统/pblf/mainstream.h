#pragma once
#define USER_FILE "user.txt"      //用户信息
#define TEMP_FILE "temp.txt"      //存储所有排班表格
#define RECORD_FILE "record.txt"  //保存排班数据
#define TIME_FILE "time.txt"      //保存操作时间
#define CLOCK_FILE "clock_in.txt" //保存打卡时间


//排班信息结构体

void arranging(char* username, char* use);
void ask_desire(char name[7][5], int desire[7][7]);                                                          //询问意愿
void sort(int day[7], int tmp[7], int* n, int desire[7][7], int order);                                   //实现排班
void fail(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                           //检测排班是否失败
void add_arrage(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                     //增加排班
void user_menu(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);             //用户功能菜单
void esc(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                   //返回