#define _CRT_SECURE_NO_WARNINGS
#include "all.h"
#include "information_control.h"
#include "mainstream.h"
#include "user_control.h"
/*�û��ṹ*/


void menu()
{
	printf("=======��ӭʹ���Ű�ϵͳ=======\n");
	printf("[------����1�����û�ע��-----]\n");
	printf("[------����2�����û���¼-----]\n");
	printf("[------����3��ѯ�򿨼�¼-----]\n");
	printf("[------����0�˳�����---------]\n");
}

int main()
{
	/*�û�����*/
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
		printf("��ѡ��");
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
			printf("����������������룺"); 
			continue;
		}
	} while (cho);
	return 0;
}