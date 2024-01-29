#define _CRT_SECURE_NO_WARNINGS
#include "all.h"
#include "information_control.h"
#include "mainstream.h"
#include "user_control.h"
/*用户结构*/


void menu()
{
	printf("=======欢迎使用排班系统=======\n");
	printf("[------输入1进行用户注册-----]\n");
	printf("[------输入2进行用户登录-----]\n");
	printf("[------输入3查询打卡记录-----]\n");
	printf("[------输入0退出程序---------]\n");
}

int main()
{
	/*用户数组*/
	User users[MAX_USERS];
	int cho = 0;
	FILE* file = fopen("user.txt", "r");
	if (file == NULL) 
	{
		printf("Error opening file\n");
		return 0;
	}
	char op;
	int i = 0;
	while ((op = fscanf(file, "%s %s %s", &users[i].username, &users[i].password, &users[i].realname) != EOF))
	{
		i++;
	}
	fclose(file);
	file = NULL;
	do
	{
		fflush(stdin); system("cls");
		menu();
		printf("请选择：");
		scanf("%d", &cho);
		switch (cho)
		{
		case 1:
			registerUser(users);
			continue;
		case 2:
			loginUser(users);
			continue;
		case 3:
			clock_record();
			continue;
		case 0:
			break;
		default:
			printf("输入错误，请重新输入："); 
			continue;
		}
	} while (cho);
	return 0;
}