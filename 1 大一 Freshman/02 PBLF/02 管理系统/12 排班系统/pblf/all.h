#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include <stdbool.h>
/*最大用户数量*/
#define MAX_USERS 20
#define NUM_GUARDS 7 // 定义保安人数
#define NUM_DAYS 7 // 定义排班天数
 /*用户结构*/
typedef struct User {
	char username[20];
	char password[20];
	char realname[20];
}User;

