#pragma once
#define USER_FILE "user.txt"      //�û���Ϣ
#define TEMP_FILE "temp.txt"      //�洢�����Ű���
#define RECORD_FILE "record.txt"  //�����Ű�����
#define TIME_FILE "time.txt"      //�������ʱ��
#define CLOCK_FILE "clock_in.txt" //�����ʱ��


//�Ű���Ϣ�ṹ��

void arranging(char* username, char* use);
void ask_desire(char name[7][5], int desire[7][7]);                                                          //ѯ����Ը
void sort(int day[7], int tmp[7], int* n, int desire[7][7], int order);                                   //ʵ���Ű�
void fail(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                           //����Ű��Ƿ�ʧ��
void add_arrage(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                     //�����Ű�
void user_menu(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);             //�û����ܲ˵�
void esc(int* n, char name[7][5], int desire[7][7], int tmp[7], int day[7], char* use);                   //����