#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include <stdbool.h>
/*����û�����*/
#define MAX_USERS 20
#define NUM_GUARDS 7 // ���屣������
#define NUM_DAYS 7 // �����Ű�����
 /*�û��ṹ*/
typedef struct User {
	char username[20];
	char password[20];
	char realname[20];
}User;

