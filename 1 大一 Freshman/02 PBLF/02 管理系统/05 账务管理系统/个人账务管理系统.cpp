#include<stdio.h>
#include<time.h>
#include<graphics.h>
#include<string.h>
#include<conio.h>
#include <stdlib.h>
#pragma warning(disable:4996)


int menu_page[2] = { 700,600 };//����������ڳ�����
RECT warning_text = { menu_page[0] / 4,menu_page[1] / 16, menu_page[0] * 3 / 4, menu_page[0] * 5 / 32 };//���澯��/��ʾ���ڳ�����
FILE* fp;//������ļ����ļ�ָ��
#define name_length 10//�û������ȣ������޸�
TCHAR file_name[name_length + 1 + 4] = "";//�ļ���
TCHAR name[name_length + 1] = "";//�˻���

#define root_length 12//���볤��
TCHAR root[root_length + 1] = "";//�˻�����

#define question_length 100//���ⳤ�ȣ������޸�
#define answer_length 100//�𰸳��ȣ������޸�
TCHAR question[question_length] = "";//�����ܱ�����
TCHAR answer[answer_length] = "";//���������ܱ������

TCHAR wayway[2][20] = { "����","֧��" };//��������״̬��
#define funct_in_num 4
TCHAR funct_in[funct_in_num][20] = { "����","�����", "���", "����" };//���������Ӧ״̬��
#define funct_out_num 5
TCHAR funct_out[funct_out_num][20] = { "����", "����", "��ͨ", "�罻", "����" };//����֧����Ӧ״̬����������ʱ��̬ת��
//�����Ӧ״̬��������ʱ��̬ת��


int show_num_all = 0;//�������������˵���
int page_num_all = -1;//������������ҳ��
int show_page = 0;//������ʾ�ĵ�ǰҳ��

COLORREF base_color = RGB(173, 193, 226);
COLORREF page_color = RGB(52, 66, 112);
COLORREF tips_color = RGB(101, 130, 186);//�������ֻ���ɫ��������ʹ��

int sum_in_month[12][4];//�ֱ�������·������0���룬1֧����2���࣬3�·�


struct chart {
	int num;//���кţ���ѯʱ�Ÿ�ֵ 
	int year;//��
	int month;//��
	int day;//��
	int money;//���
	int way;//֧��1������0
	int function;//��;����Դ0,1,2,3,
	//                       0,1,2,3,4
	struct chart* next;
};
//�˵�����

int sum = 0;
TCHAR SUM[15] = "";//�ܽ���

int sum_in_all = 0;
TCHAR SUM_IN[15] = "";//������

int sum_out_all = 0;
TCHAR SUM_OUT[15] = "";//��֧��

struct chart p_chart = { 0,0,0,0,0,0,NULL };//����������ɸѡ����ȫ���˵�
struct chart* p_last = &p_chart;//�����������һλ

int year_new = 2023;
int month_new = 1;
int day_new = 1;
int money_new = 0;
int way_new = 0;
int function_new = 0;
TCHAR year_new_text[5] = "2023";
TCHAR month_new_text[3] = "1";
TCHAR day_new_text[3] = "1";
TCHAR money_new_text[6] = "0";//���5λ�� 
//��ʱ�����洢�˵�������

int msg_state_former = -1;//���ǰ��״̬
int msg_state = -1;//�������״̬��������

void warning(LPCTSTR str, UINT uFormat)
{
	setbkmode(OPAQUE);//д����ʱ�ı������������ɫ����ȥ������
	settextcolor(RED);//���ֺ�ɫ����
	drawtext(str, &warning_text, uFormat);//��ʾ����
	Sleep(2000);
	drawtext("                                  ", &warning_text, uFormat);//Ҫȥȥ�������ϲ������������������������
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	settextcolor(WHITE);//�ָ�����
}
//���ھ���/��ʾ

void msg_to_RED(int page[][4], int page_num, MOUSEMSG msg)//���ֿ����꣬�ְ���������հף�
{
	msg_state = -1;
	for (int i = 0; i <= page_num - 1; i++)
	{
		if (msg.x <page[i][2] && msg.x >page[i][0] && msg.y <page[i][3] && msg.y >page[i][1])
			msg_state = i;
	}
	//�ж����λ��

	if (msg_state_former >= 0 && msg_state != msg_state_former)
	{
		setlinecolor(WHITE);
		rectangle(page[msg_state_former][0], page[msg_state_former][1], page[msg_state_former][2], page[msg_state_former][3]);
	}
	//�������֮ǰ����߿�ˢ��
	if (msg_state >= 0)
	{
		setlinecolor(RED);
		rectangle(page[msg_state][0], page[msg_state][1], page[msg_state][2], page[msg_state][3]);
	}
	setlinecolor(WHITE);
}
//����������������ȥ�߿�ͱ�죬�뿪�ͱ� �ذ�ɫ

void text_takeplace(LPCTSTR str, RECT* pRect, UINT uFormat, COLORREF page_color)
{
	setbkcolor(page_color);
	setbkmode(OPAQUE);
	drawtext("            ", pRect, uFormat);
	setbkmode(TRANSPARENT);
	drawtext(str, pRect, uFormat);
	setbkcolor(base_color);//��ͼɫ
}
//�����滻,Ҫ�ı䱳��ɫ����

int logonok()
{
	if (strlen(name) == 0)
	{
		if (strlen(root) == 0)
		{
			warning("�������˻���������", DT_CENTER);
			return 0;
		}
		//δ�����˻���������
		else
		{
			warning("�������˻���", DT_CENTER);
			return 0;
		}
	}
	//δ�����˻���
	else if (strlen(root) != root_length)
	{
		warning("���볤�ȴ�������������", DT_CENTER);
		return 0;
	}
	//���볤������
	else
	{
		fp = fopen(file_name, "a+");
		fseek(fp, 0l, SEEK_SET);//�ļ���ͷ
		TCHAR c = fgetc(fp);
		fseek(fp, 0l, SEEK_SET);//�ļ���ͷ

		if (c == EOF)
		{
			fprintf(fp, "%s\n", root);
			warning("ע��ɹ������������ܱ����⣡", DT_CENTER);
			fclose(fp);
			return 2;
		}
		//ע��
		else
		{
			TCHAR root2[root_length + 1];
			fscanf(fp, "%s\n", root2);
			if (strcmp(root, root2) != 0)
			{
				warning("�����������������", DT_CENTER);
				fclose(fp);
				return 0;
			}
			else
			{
				fscanf(fp, "%s\n", question);
				fscanf(fp, "%s\n", answer);
				strcpy(file_name, name);
				strcat(file_name, ".txt");
				warning("��¼�ɹ����������룡", DT_CENTER);
				fclose(fp);
				return 1;
			}
		}
		//��¼
	}
}
//ȷ�����
void logon()
{
	//����׼��

	int graph[2] = { 1000,700 };
	//��¼���ڴ��ڳ�����
	int logon_page[4] = { graph[0] / 8,graph[1] / 4,graph[0] * 4 / 8,graph[1] * 3 / 4 };
	//��¼����
	int logon_name[4] = { graph[0] * 3 / 16,logon_page[1] + (logon_page[3] - logon_page[1]) * 3 / 10,graph[0] * 7 / 16,logon_page[1] + (logon_page[3] - logon_page[1]) * 4 / 10 };
	//�˻���
	int logon_root[4] = { graph[0] * 3 / 16,logon_page[1] + (logon_page[3] - logon_page[1]) * 5 / 10,graph[0] * 7 / 16,logon_page[1] + (logon_page[3] - logon_page[1]) * 6 / 10 };
	//�����
	int logon_ok[4] = { graph[0] * 10 / 32 - 3,logon_page[1] + (logon_page[3] - logon_page[1]) * 7 / 10,graph[0] * 11 / 32,logon_page[1] + (logon_page[3] - logon_page[1]) * 15 / 20 };
	//ȷ�Ͽ�
	int tips[4] = { graph[0] * 4 / 8 ,graph[1] / 4, graph[0] * 6 / 8,graph[1] * 3 / 4 };
	//��ʾ��
	int logon_question[4] = { graph[0] * 11 / 12,0,graph[0],graph[1] / 24 };
	//���������
	int msg_to_RED_logon[4][4] = { logon_name[0] ,logon_name[1] , logon_name[2] , logon_name[3] , logon_root[0] ,logon_root[1] ,logon_root[2] ,logon_root[3] ,logon_ok[0] ,logon_ok[1] ,logon_ok[2] ,logon_ok[3],logon_question[0],logon_question[1], logon_question[2], logon_question[3] };
	//�����������һ�𣬷������



	//ҳ�����
	initgraph(graph[0], graph[1]);

	setbkcolor(base_color);//��ͼ
	cleardevice();//����ˢ��
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	settextcolor(WHITE);//����
	setfillcolor(page_color);//��¼����ɫ
	setlinecolor(WHITE);//������ɫ
	fillrectangle(logon_page[0], logon_page[1], logon_page[2], logon_page[3]);//����¼��
	for (int i = 0; i < 4; i++)
	{
		fillrectangle(msg_to_RED_logon[i][0], msg_to_RED_logon[i][1], msg_to_RED_logon[i][2], msg_to_RED_logon[i][3]);
	}
	//���˻������룬ȷ�ϣ����������
	setfillcolor(tips_color);//tips��ɫ
	fillrectangle(tips[0], tips[1], tips[2], tips[3]);//��tips��

	LOGFONT f;
	gettextstyle(&f);//�ݴ�Ĭ������

	RECT text_name_tips = { logon_name[0],logon_name[1],logon_name[0] + 60,logon_name[3] };//��ʾ���˻���
	RECT text_name = { logon_name[0] + 60,logon_name[1],logon_name[2],logon_name[3] };
	settextstyle(30, 10, "����");//�����壨�޸ĳ����ǵø����壡����������
	drawtext("�˻�  ", &text_name_tips, DT_CENTER);//��ʾ���˻���

	RECT text_root_tips = { logon_root[0],logon_root[1],logon_root[0] + 60,logon_root[3] };//��ʾ�����롱
	RECT text_root = { logon_root[0] + 60,logon_root[1],logon_root[2],logon_root[3] };
	drawtext("����  ", &text_root_tips, DT_CENTER);//��ʾ�����롱

	settextstyle(&f);//�Ļ�Ĭ������
	RECT text_ok = { logon_ok[0],logon_ok[1],logon_ok[2],logon_ok[3] };
	drawtext("ȷ��", &text_ok, DT_CENTER);//��ʾ"ȷ��"

	RECT tip_text = { tips[0],tips[1],tips[2],tips[3] };
	settextstyle(30, 9, "����");//�޸ĳ����ǵø����壡��������
	drawtext("tips:\n1.���ε�½��ע�᣻\n2.�����˺ţ��˺ų�������10λ����֧�����֡���ĸ�ͷ��ţ�\n3.�������룬����ӦΪ12λ����֧�����֡���ĸ�ͷ��ţ�\n4.��������ʱ��ͨ�������ܱ�������ȷ�����ʾ����5��.\n5��ֹ�˻���test����������������Ը���", &tip_text, DT_WORDBREAK);
	//��ʾ��ʾ

	RECT question_text = { logon_question[0],logon_question[1], logon_question[2], logon_question[3] };
	drawtext("��������", &question_text, DT_WORDBREAK); //��ʾ"��������"

	//��������

	msg_state_former = -1;//!
	while (1)
	{
		MOUSEMSG msg;//������
		msg = GetMouseMsg();//��ȡ���״̬
		msg_to_RED(msg_to_RED_logon, 4, msg);//����
		int msg_t = msg_state;
		if (msg_state == 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(name, name_length + 1, "�������û�����");
			text_takeplace(name, &text_name, DT_CENTER, RGB(52, 66, 112));
			strcpy(file_name, name);
			strcat(file_name, ".txt");
		}
		//�û�������
		else if (msg_state == 1 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(root, root_length + 1, "���������룺");
			text_takeplace(root, &text_root, DT_CENTER, RGB(52, 66, 112));
		}
		//��������
		else if (msg_state == 2 && msg.uMsg == WM_LBUTTONDOWN)
		{
			int logonok_answer = logonok();
			if (logonok_answer == 1)
			{
				closegraph();
				break;
			}
			//��ɵ�¼
			else if (logonok_answer == 2)
			{
				InputBox(question, 100, "�������ܱ����⣺");
				InputBox(answer, 100, "�������ܱ�����𰸣�");
				fp = fopen(file_name, "a");
				fprintf(fp, "%s\n", question);
				fprintf(fp, "%s\n", answer);
				fclose(fp);
				closegraph();
				break;
			}
			//���ע��
		}
		//ȷ��
		else if (msg_state == 3 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (strlen(name) == 0)
			{
				warning("�������˻���", DT_CENTER);
			}
			//δ�����˻���
			else
			{
				fp = fopen(file_name, "r");
				if (fp == NULL)	warning("�˻���������", DT_CENTER);
				else
				{
					TCHAR root_true[root_length + 1];
					TCHAR question_true[question_length];
					TCHAR answer_true[answer_length];
					fscanf(fp, "%s\n", root_true);
					fscanf(fp, "%s\n", question_true);
					fscanf(fp, "%s\n", answer_true);
					warning(question_true, DT_CENTER);
					InputBox(answer, answer_length, "�������ܱ�����𰸣�");
					if (strcmp(answer, answer_true) == 0)
					{
						warning(root_true, DT_CENTER);
						Sleep(1000);
					}
					//����ȷ
					else warning("�𰸴���", DT_CENTER);
					fclose(fp);
				}
			}
		}
		//��������
		msg_state_former = msg_t;
	}
}
//��¼

void add()
{
	setbkcolor(base_color);//��ͼ
	cleardevice();//����ˢ��
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	setlinecolor(WHITE);//����
	settextcolor(WHITE);//����
	COLORREF add_page_color = page_color;
	setfillcolor(add_page_color);

	//����׼��
	int add_choice[8][4];

	add_choice[0][0] = 0;
	add_choice[0][1] = 0;
	add_choice[0][2] = menu_page[0] * 5 / 32;
	add_choice[0][3] = menu_page[1] / 32;

	add_choice[1][0] = menu_page[0] / 4;
	add_choice[1][1] = menu_page[1] / 4;
	add_choice[1][2] = menu_page[0] * 5 / 12;
	add_choice[1][3] = menu_page[1] * 5 / 12;

	add_choice[2][0] = menu_page[0] * 5 / 12;
	add_choice[2][1] = menu_page[1] / 4;
	add_choice[2][2] = menu_page[0] * 7 / 12;
	add_choice[2][3] = menu_page[1] * 5 / 12;

	add_choice[3][0] = menu_page[0] * 7 / 12;
	add_choice[3][1] = menu_page[1] / 4;
	add_choice[3][2] = menu_page[0] * 3 / 4;
	add_choice[3][3] = menu_page[1] * 5 / 12;

	add_choice[4][0] = menu_page[0] / 4;
	add_choice[4][1] = menu_page[1] * 5 / 12;
	add_choice[4][2] = menu_page[0] * 3 / 4;
	add_choice[4][3] = menu_page[1] * 7 / 12;

	add_choice[5][0] = menu_page[0] / 4;
	add_choice[5][1] = menu_page[1] * 7 / 12;
	add_choice[5][2] = menu_page[0] / 2;
	add_choice[5][3] = menu_page[1] * 3 / 4;

	add_choice[6][0] = menu_page[0] / 2;
	add_choice[6][1] = menu_page[1] * 7 / 12;
	add_choice[6][2] = menu_page[0] * 3 / 4;
	add_choice[6][3] = menu_page[1] * 3 / 4;

	add_choice[7][0] = menu_page[0] / 2 - 15;
	add_choice[7][1] = menu_page[1] * 20 / 24;
	add_choice[7][2] = menu_page[0] / 2 + 15;
	add_choice[7][3] = menu_page[1] * 21 / 24;
	//add������

	RECT add_text[8];
	for (int i = 0; i <= 7; i++)
	{
		add_text[i] = { add_choice[i][0], add_choice[i][1], add_choice[i][2], add_choice[i][3] };
		fillrectangle(add_choice[i][0], add_choice[i][1], add_choice[i][2], add_choice[i][3]);
	}
	//�����������ɾ���

	drawtext("�����ϼ�ҳ��", &add_text[0], DT_LEFT);
	drawtext("�꣺", &add_text[1], DT_LEFT);
	drawtext("�£�", &add_text[2], DT_LEFT);
	drawtext("�գ�", &add_text[3], DT_LEFT);
	drawtext("��", &add_text[4], DT_LEFT);
	drawtext("�˵����ͣ�", &add_text[5], DT_LEFT);
	drawtext("��;/��Դ��", &add_text[6], DT_LEFT);
	drawtext("ȷ��", &add_text[7], DT_LEFT);
	//�����ʾ��

	add_text[4] = { add_choice[4][0] - 10, add_choice[4][1], add_choice[4][2] + 20, add_choice[4][3] };
	add_text[5] = { add_choice[5][0] + 30, add_choice[5][1], add_choice[5][2], add_choice[5][3] };
	add_text[6] = { add_choice[6][0] + 30, add_choice[6][1], add_choice[6][2], add_choice[6][3] };
	//΢����ʾ��λ�ã�ʹ�ֿɼ�

	year_new = 2023;
	month_new = 1;
	day_new = 1;
	money_new = 0;
	way_new = 0;
	function_new = 0;
	text_takeplace(year_new_text, &add_text[1], DT_CENTER, add_page_color);
	text_takeplace(month_new_text, &add_text[2], DT_CENTER, add_page_color);
	text_takeplace(day_new_text, &add_text[3], DT_CENTER, add_page_color);
	text_takeplace(money_new_text, &add_text[4], DT_CENTER, add_page_color);
	text_takeplace(wayway[way_new], &add_text[5], DT_CENTER, add_page_color);
	text_takeplace(funct_in[function_new], &add_text[6], DT_CENTER, add_page_color);
	//��ʱ������˵�������

	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(add_choice, 8, msg);//��ȡ���״̬������
		int msg_t = msg_state;//!
		if (msg_state == 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			cleardevice();
			break;
		}
		//����
		else if (msg_state == 1 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(year_new_text, 5, "��������:");
			text_takeplace(year_new_text, &add_text[1], DT_CENTER, add_page_color);
		}
		//��
		else if (msg_state == 2 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(month_new_text, 3, "��������:");
			text_takeplace(month_new_text, &add_text[2], DT_CENTER, add_page_color);
		}
		//��
		else if (msg_state == 3 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(day_new_text, 3, "��������:");
			text_takeplace(day_new_text, &add_text[3], DT_CENTER, add_page_color);
		}
		//��
		else if (msg_state == 4 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(money_new_text, 6, "��������:");
			text_takeplace(money_new_text, &add_text[4], DT_CENTER, add_page_color);
		}
		//���
		else if (msg_state == 5 && msg.uMsg == WM_LBUTTONDOWN)
		{
			way_new = 1 - way_new;
			text_takeplace(wayway[way_new], &add_text[5], DT_CENTER, add_page_color);
			function_new = 0;
			if (way_new == 0)	text_takeplace(funct_in[function_new], &add_text[6], DT_CENTER, add_page_color);
			else text_takeplace(funct_out[function_new], &add_text[6], DT_CENTER, add_page_color);
		}
		//��֧����
		else if (msg_state == 6 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (way_new == 0)
			{
				function_new = (function_new + 1) % funct_in_num;
				text_takeplace(funct_in[function_new], &add_text[6], DT_CENTER, add_page_color);
			}
			//����������
			else
			{
				function_new = (function_new + 1) % funct_out_num;
				text_takeplace(funct_out[function_new], &add_text[6], DT_CENTER, add_page_color);
			}
			//֧������
		}
		//��;
		else if (msg_state == 7 && msg.uMsg == WM_LBUTTONDOWN)
		{
			fp = fopen(file_name, "a");
			fprintf(fp, "%d %d %d %d %d %d\n", atoi(year_new_text), atoi(month_new_text), atoi(day_new_text), atoi(money_new_text), way_new, function_new);
			fclose(fp);
			warning("��ӳɹ���", DT_CENTER);
			cleardevice();
			break;
		}
		//ȷ�����
		msg_state_former = msg_t;//!
	}
}
//��ӹ���

void str_to_num(TCHAR* search_str)
{
	int i = 0;
	while (search_str[i] <= '9' && search_str[i] >= '0')
	{
		search_str[i] = '0';
		i++;
	}
	search_str[i] = '0';
}
//���������������ȡ����

void show(RECT show_list_text[], int onepage_list_num, COLORREF show_color)
{

	struct chart* p_show = &p_chart;
	for (int i = 0; i <= onepage_list_num * show_page; i++)
	{
		p_show = p_show->next;
	}
	//���˵������ƶ���Ҫ��ʾ��ǰһ��

	for (int t = 0; t < 7; t++)
	{
		for (int i = 0; i < 10; i++)
		{
			text_takeplace("", &show_list_text[7 * i + t], DT_CENTER, show_color);
		}
	}
	TCHAR NUM[5];
	TCHAR YEAR[5];
	TCHAR MONTH[3];
	TCHAR DAY[3];
	TCHAR MONEY[15];
	//��ʾ��ҳ������Ա������ַ�����ʹ����Щ������ʱ����

	int i = 0;//�ڼ���
	while (p_show != NULL && i < onepage_list_num)
	{
		text_takeplace(itoa(p_show->num, NUM, 10), &show_list_text[i * 7 + 0], DT_CENTER, show_color);
		text_takeplace(itoa(p_show->year, YEAR, 10), &show_list_text[i * 7 + 1], DT_CENTER, show_color);
		text_takeplace(itoa(p_show->month, MONTH, 10), &show_list_text[i * 7 + 2], DT_CENTER, show_color);
		text_takeplace(itoa(p_show->day, DAY, 10), &show_list_text[i * 7 + 3], DT_CENTER, show_color);
		text_takeplace(itoa(p_show->money, MONEY, 10), &show_list_text[i * 7 + 4], DT_CENTER, show_color);
		text_takeplace(wayway[p_show->way], &show_list_text[i * 7 + 5], DT_CENTER, show_color);
		if (p_show->way == 0)	text_takeplace(funct_in[p_show->function], &show_list_text[i * 7 + 6], DT_CENTER, show_color);
		else text_takeplace(funct_out[p_show->function], &show_list_text[i * 7 + 6], DT_CENTER, show_color);
		p_show = p_show->next;
		i++;
	}
	//��ʾ���˵�
}
//���˵���ʾ�ڲ�ѯҳ��

void delete_p_chart()
{
	while (show_num_all != -1)
	{
		p_last = &p_chart;
		for (int i = 0; i <= show_num_all; i++)
		{
			p_last = p_last->next;
		}
		free(p_last);
		show_num_all--;
	}
	p_last = &p_chart; show_num_all;
}
//���������

void search_in_all()
{
	delete_p_chart();//���������
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//���к�
	show_num_all = -1;//���������˵���
	while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF)
	{
		i++;
		show_num_all++;
		p_last->next = (struct chart*)malloc(sizeof(struct chart));
		p_last = p_last->next;
		p_last->num = i;
		p_last->year = year_new;
		p_last->month = month_new;
		p_last->day = day_new;
		p_last->money = money_new;
		p_last->way = way_new;
		p_last->function = function_new;
		p_last->next = NULL;
	}
	//����
	fclose(fp);
}
//�����˵�����p_chart
void search_in_year(int search_year)
{
	delete_p_chart();//���������
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//���к�
	show_num_all = -1;//���������˵���
	while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF)
	{
		i++;
		if (year_new == search_year)
		{
			show_num_all++;
			p_last->next = (struct chart*)malloc(sizeof(struct chart));
			p_last = p_last->next;
			p_last->num = i;
			p_last->year = year_new;
			p_last->month = month_new;
			p_last->day = day_new;
			p_last->money = money_new;
			p_last->way = way_new;
			p_last->function = function_new;
			p_last->next = NULL;
		}
	}
	//����
	fclose(fp);
}
//�ض�����˵�����p_chart
void search_in_month(int search_year, int search_month)
{
	delete_p_chart();//���������
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//���к�
	show_num_all = -1;//���������˵���
	while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF)
	{
		i++;
		if (year_new == search_year && month_new == search_month)
		{
			show_num_all++;
			p_last->next = (struct chart*)malloc(sizeof(struct chart));
			p_last = p_last->next;
			p_last->num = i;
			p_last->year = year_new;
			p_last->month = month_new;
			p_last->day = day_new;
			p_last->money = money_new;
			p_last->way = way_new;
			p_last->function = function_new;
			p_last->next = NULL;
		}
	}
	//����
	fclose(fp);
}
//�ض��µ��˵�����p_chart
void search_in_day(int search_year, int search_month, int search_day)
{
	delete_p_chart();//���������
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//���к�
	show_num_all = -1;//���������˵���
	while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF)
	{
		i++;
		if (year_new == search_year && month_new == search_month && day_new == search_day)
		{
			show_num_all++;
			p_last->next = (struct chart*)malloc(sizeof(struct chart));
			p_last = p_last->next;
			p_last->num = i;
			p_last->year = year_new;
			p_last->month = month_new;
			p_last->day = day_new;
			p_last->money = money_new;
			p_last->way = way_new;
			p_last->function = function_new;
			p_last->next = NULL;
		}
	}
	//����
	fclose(fp);
}
//�ض��յ��˵�����p_chart

void search_in_time()
{
	setbkcolor(base_color);//��ͼ
	cleardevice();//����ˢ��
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	setlinecolor(WHITE);//����
	settextcolor(WHITE);//����

	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;

	setfillcolor(show_color);

	//����׼��

	int show_title[4];
	show_title[0] = menu_page[0] / 4;
	show_title[1] = menu_page[1] * 29 / 88;
	show_title[2] = menu_page[0] * 3 / 4;
	show_title[3] = menu_page[1] * 33 / 88;
	RECT show_title_text[7];
	//��ʾ����

	int show_list[10][4];//10���˵�
	for (int i = 0; i < 10; i++)
	{
		show_list[i][0] = menu_page[0] / 4;
		show_list[i][1] = menu_page[1] * (33 + 4 * i) / 88;
		show_list[i][2] = menu_page[0] * 3 / 4;
		show_list[i][3] = menu_page[1] * (37 + 4 * i) / 88;
		fillrectangle(show_list[i][0], show_list[i][1], show_list[i][2], show_list[i][3]);
	}
	//���˵�λ��

	RECT show_list_text[10 * 7];
	for (int t = 0; t < 5; t++)
	{
		for (int i = 0; i < 10; i++)
		{
			show_list_text[7 * i + t] = { show_list[i][0] + (show_list[i][2] - show_list[i][0]) * t * 4 / 35,  show_list[i][1] ,   show_list[i][0] + (show_list[i][2] - show_list[i][0]) * (t + 1) * 4 / 35,      show_list[i][3] };
			drawtext("", &show_list_text[7 * i + t], DT_CENTER);
		}
		show_title_text[t] = { show_title[0] + (show_title[2] - show_title[0]) * t * 4 / 35,show_title[1] ,show_title[0] + (show_title[2] - show_title[0]) * (t + 1) * 4 / 35,show_title[3] };
	}
	for (int t = 5; t < 7; t++)
	{
		for (int i = 0; i < 10; i++)
		{
			show_list_text[7 * i + t] = { show_list[i][0] + (show_list[i][2] - show_list[i][0]) * (3 * t - 7) / 14,  show_list[i][1] ,   show_list[i][0] + (show_list[i][2] - show_list[i][0]) * (3 * t - 4) / 14 ,      show_list[i][3] };
			drawtext("??", &show_list_text[7 * i + t], DT_CENTER);
		}
		show_title_text[t] = { show_title[0] + (show_title[2] - show_title[0]) * (3 * t - 7) / 14,show_title[1] ,show_title[0] + (show_title[2] - show_title[0]) * (3 * t - 4) / 14,show_title[3] };
	}
	//�����˵�λ�����ִ���show_list_text

	int search_in_time_choice[8][4];//��ѯѡ���С����
	setfillcolor(choice_color);//�޸����ɫΪ���ܼ���ɫ

	RECT search_in_time_choice_text[8];
	search_in_time_choice[0][0] = 0;
	search_in_time_choice[0][1] = 0;
	search_in_time_choice[0][2] = menu_page[0] * 5 / 32;
	search_in_time_choice[0][3] = menu_page[1] / 32;
	search_in_time_choice_text[0] = { search_in_time_choice[0][0] ,search_in_time_choice[0][1] ,search_in_time_choice[0][2] ,search_in_time_choice[0][3] };
	fillrectangle(search_in_time_choice[0][0], search_in_time_choice[0][1], search_in_time_choice[0][2], search_in_time_choice[0][3]);
	//0 ����

	for (int i = 1; i <= 3; i++)
	{
		search_in_time_choice[i][0] = menu_page[0] * (1 + 2 * i) / 12;
		search_in_time_choice[i][1] = menu_page[1] / 8;
		search_in_time_choice[i][2] = menu_page[0] * (3 + 2 * i) / 12;
		search_in_time_choice[i][3] = menu_page[1] * 2 / 8;
		search_in_time_choice_text[i] = { search_in_time_choice[i][0] ,search_in_time_choice[i][1] ,search_in_time_choice[i][2] ,search_in_time_choice[i][3] };
		fillrectangle(search_in_time_choice[i][0], search_in_time_choice[i][1], search_in_time_choice[i][2], search_in_time_choice[i][3]);
	}
	//1��
	//2��
	//3��
	for (int i = 1; i <= 3; i++)
	{
		search_in_time_choice_text[i] = { search_in_time_choice[i][0] ,(search_in_time_choice[i][1] + search_in_time_choice[i][3]) / 2 - menu_page[1] / 64 ,search_in_time_choice[i][2] ,(search_in_time_choice[i][1] + search_in_time_choice[i][3]) / 2 + menu_page[1] / 64 };
	}
	//΢�����������
	for (int i = 4; i <= 7; i++)
	{
		search_in_time_choice[i][0] = menu_page[0] * (i + 8) / 16;
		search_in_time_choice[i][1] = menu_page[1] * 7 / 8;
		search_in_time_choice[i][2] = menu_page[0] * (i + 9) / 16;
		search_in_time_choice[i][3] = menu_page[1] * 29 / 32;
		search_in_time_choice_text[i] = { search_in_time_choice[i][0] ,search_in_time_choice[i][1] ,search_in_time_choice[i][2] ,search_in_time_choice[i][3] };
		fillrectangle(search_in_time_choice[i][0], search_in_time_choice[i][1], search_in_time_choice[i][2], search_in_time_choice[i][3]);
	}
	//4
	// 5
	// 6
	// 7
	//���ø����ܼ�λ�����ı�λ��

	show(show_list_text, 10, show_color);
	drawtext("�����ϼ�ҳ��", &search_in_time_choice_text[0], DT_CENTER);
	drawtext("�����ѯ", &search_in_time_choice_text[1], DT_CENTER);
	drawtext("���²�ѯ", &search_in_time_choice_text[2], DT_CENTER);
	drawtext("���ղ�ѯ", &search_in_time_choice_text[3], DT_CENTER);
	drawtext("��һҳ", &search_in_time_choice_text[4], DT_CENTER);
	drawtext("��һҳ", &search_in_time_choice_text[5], DT_CENTER);
	drawtext("��ҳ", &search_in_time_choice_text[6], DT_CENTER);
	drawtext("βҳ", &search_in_time_choice_text[7], DT_CENTER);
	//������ʾ��

	drawtext("���к�", &show_title_text[0], DT_CENTER);
	drawtext("��", &show_title_text[1], DT_CENTER);
	drawtext("��", &show_title_text[2], DT_CENTER);
	drawtext("��", &show_title_text[3], DT_CENTER);
	drawtext("���", &show_title_text[4], DT_CENTER);
	drawtext("��֧����", &show_title_text[5], DT_CENTER);
	drawtext("��;��Դ", &show_title_text[6], DT_CENTER);
	//����

	search_in_all();
	show(show_list_text, 10, show_color);
	msg_state_former = -1;//!
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(search_in_time_choice, 8, msg);
		int msg_t = msg_state;//��ȡ���״̬
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//����
			else if (msg_state == 1)
			{
				InputBox(year_new_text, 5, "�������꣺");
				search_in_year(atoi(year_new_text));
			}
			//��
			else if (msg_state == 2)
			{
				TCHAR search_month[8];
				InputBox(search_month, 8, "�����밴2023.12��ʽ�����£�");
				year_new = atoi(search_month);
				str_to_num(search_month);
				month_new = atoi(search_month);
				search_in_month(year_new, month_new);
			}
			//��
			else if (msg_state == 3)
			{
				TCHAR search_day[11];
				InputBox(search_day, 11, "�����밴2023.12.23��ʽ�����գ�");
				year_new = atoi(search_day);
				str_to_num(search_day);
				month_new = atoi(search_day);
				str_to_num(search_day);
				day_new = atoi(search_day);
				search_in_day(year_new, month_new, day_new);
			}
			//��
			if (show_num_all == -1 && msg_state >= 1)
			{
				warning("������", DT_CENTER);
				msg_state_former = msg_t;//!
				continue;
			}
			//������
			else
			{
				page_num_all = (show_num_all + 10) / 10 - 1;//ˢ����ҳ��
				if (page_num_all > 0)
				{
					if (msg_state == 4)
					{
						show_page = (show_page + 2 * page_num_all + 2 - 1) % (page_num_all + 1);
					}
					//��һҳ
					else if (msg_state == 5)
					{
						show_page = (show_page + 1) % (page_num_all + 1);
					}
					//��һҳ
					else if (msg_state == 6)
					{
						show_page = 0;
					}
					//��ҳ
					else if (msg_state == 7)
					{
						show_page = page_num_all;
					}
					//βҳ
				}
				else show_page = 0;
			}
			//����ҳ������Ѱ������ҳ����βҳ
			if (msg_state >= 1 && msg.uMsg == WM_LBUTTONDOWN)	show(show_list_text, 10, show_color);//��ʾ
		}
		msg_state_former = msg_t;//!
	}
}
//��ʱ���ѯ

void search_in_function_main(int search_function)
{
	delete_p_chart();//���������
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//���к�
	show_num_all = -1;//���������˵���
	while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF)
	{
		i++;
		if (function_new == search_function)
		{
			show_num_all++;
			p_last->next = (struct chart*)malloc(sizeof(struct chart));
			p_last = p_last->next;
			p_last->num = i;
			p_last->year = year_new;
			p_last->month = month_new;
			p_last->day = day_new;
			p_last->money = money_new;
			p_last->way = way_new;
			p_last->function = function_new;
			p_last->next = NULL;
		}
	}
	//����
	fclose(fp);
}
void search_in_function()
{
	setbkcolor(base_color);//��ͼ
	cleardevice();//����ˢ��
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	setlinecolor(WHITE);//����
	settextcolor(WHITE);//����

	//����׼��
	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;

	setfillcolor(show_color);

	int show_title[4];
	show_title[0] = menu_page[0] / 4;
	show_title[1] = menu_page[1] * 29 / 88;
	show_title[2] = menu_page[0] * 3 / 4;
	show_title[3] = menu_page[1] * 33 / 88;
	RECT show_title_text[7];
	//��ʾ����

	int show_list[10][4];//10���˵�
	for (int i = 0; i < 10; i++)
	{
		show_list[i][0] = menu_page[0] / 4;
		show_list[i][1] = menu_page[1] * (33 + 4 * i) / 88;
		show_list[i][2] = menu_page[0] * 3 / 4;
		show_list[i][3] = menu_page[1] * (37 + 4 * i) / 88;
		solidrectangle(show_list[i][0], show_list[i][1], show_list[i][2], show_list[i][3]);
	}
	//���˵�λ��

	RECT show_list_text[11 * 7];
	for (int t = 0; t < 7; t++)
	{
		for (int i = 0; i < 10; i++)
		{
			show_list_text[7 * i + t] = { show_list[i][0] + (show_list[i][2] - show_list[i][0]) * t / 7,  show_list[i][1] ,   show_list[i][0] + (show_list[i][2] - show_list[i][0]) * (t + 1) / 7 ,      show_list[i][3] };
			drawtext("", &show_list_text[7 * i + t], DT_CENTER);
		}
		show_title_text[t] = { show_title[0] + (show_title[2] - show_title[0]) * t / 7,show_title[1] ,show_title[0] + (show_title[2] - show_title[0]) * (t + 1) / 7 ,show_title[3] };
	}
	//�����˵�λ�����ִ���show_list_text

	for (int t = 0; t < 5; t++)
	{
		for (int i = 0; i < 10; i++)
		{
			show_list_text[7 * i + t] = { show_list[i][0] + (show_list[i][2] - show_list[i][0]) * t * 4 / 35,  show_list[i][1] ,   show_list[i][0] + (show_list[i][2] - show_list[i][0]) * (t + 1) * 4 / 35,      show_list[i][3] };
		}
		show_title_text[t] = { show_title[0] + (show_title[2] - show_title[0]) * t * 4 / 35,show_title[1] ,show_title[0] + (show_title[2] - show_title[0]) * (t + 1) * 4 / 35,show_title[3] };
	}
	for (int t = 5; t < 7; t++)
	{
		for (int i = 0; i < 10; i++)
		{
			show_list_text[7 * i + t] = { show_list[i][0] + (show_list[i][2] - show_list[i][0]) * (3 * t - 7) / 14,  show_list[i][1] ,   show_list[i][0] + (show_list[i][2] - show_list[i][0]) * (3 * t - 4) / 14 ,      show_list[i][3] };
		}
		show_title_text[t] = { show_title[0] + (show_title[2] - show_title[0]) * (3 * t - 7) / 14,show_title[1] ,show_title[0] + (show_title[2] - show_title[0]) * (3 * t - 4) / 14,show_title[3] };
	}
	//΢��

	int search_in_function_choice[8][4];//��ѯѡ���С����
	setfillcolor(choice_color);//�޸����ɫΪ���ܼ���ɫ

	RECT search_in_function_choice_text[8];
	search_in_function_choice[0][0] = 0;
	search_in_function_choice[0][1] = 0;
	search_in_function_choice[0][2] = menu_page[0] * 5 / 32;
	search_in_function_choice[0][3] = menu_page[1] / 32;
	search_in_function_choice_text[0] = { search_in_function_choice[0][0] ,search_in_function_choice[0][1] ,search_in_function_choice[0][2] ,search_in_function_choice[0][3] };
	fillrectangle(search_in_function_choice[0][0], search_in_function_choice[0][1], search_in_function_choice[0][2], search_in_function_choice[0][3]);
	//0����

	for (int i = 1; i <= 3; i++)
	{
		search_in_function_choice[i][0] = menu_page[0] * (1 + 2 * i) / 12;
		search_in_function_choice[i][1] = menu_page[1] / 8;
		search_in_function_choice[i][2] = menu_page[0] * (3 + 2 * i) / 12;
		search_in_function_choice[i][3] = menu_page[1] * 2 / 8;
		search_in_function_choice_text[i] = { search_in_function_choice[i][0] ,search_in_function_choice[i][1] ,search_in_function_choice[i][2] ,search_in_function_choice[i][3] };
		fillrectangle(search_in_function_choice[i][0], search_in_function_choice[i][1], search_in_function_choice[i][2], search_in_function_choice[i][3]);
	}
	//1��֧����
	//2��;
	//3ȷ��
	for (int i = 1; i <= 3; i++)
	{
		search_in_function_choice_text[i] = { search_in_function_choice[i][0] ,(search_in_function_choice[i][1] + search_in_function_choice[i][3]) / 2 - menu_page[1] / 64 ,search_in_function_choice[i][2] ,(search_in_function_choice[i][1] + search_in_function_choice[i][3]) / 2 + menu_page[1] / 64 };
	}
	//΢�����������
	for (int i = 4; i <= 7; i++)
	{
		search_in_function_choice[i][0] = menu_page[0] * (i + 8) / 16;
		search_in_function_choice[i][1] = menu_page[1] * 7 / 8;
		search_in_function_choice[i][2] = menu_page[0] * (i + 9) / 16;
		search_in_function_choice[i][3] = menu_page[1] * 29 / 32;
		search_in_function_choice_text[i] = { search_in_function_choice[i][0] ,search_in_function_choice[i][1] ,search_in_function_choice[i][2] ,search_in_function_choice[i][3] };
		fillrectangle(search_in_function_choice[i][0], search_in_function_choice[i][1], search_in_function_choice[i][2], search_in_function_choice[i][3]);
	}
	//4��һҳ
	//5��һҳ
	//6��ҳ
	// 7βҳ
	//���ø����ܼ�λ�����ı�λ��

	drawtext("�����ϼ�ҳ��", &search_in_function_choice_text[0], DT_CENTER);
	drawtext(wayway[0], &search_in_function_choice_text[1], DT_CENTER);
	drawtext(funct_in[0], &search_in_function_choice_text[2], DT_CENTER);
	drawtext("ȷ��", &search_in_function_choice_text[3], DT_CENTER);
	drawtext("��һҳ", &search_in_function_choice_text[4], DT_CENTER);
	drawtext("��һҳ", &search_in_function_choice_text[5], DT_CENTER);
	drawtext("��ҳ", &search_in_function_choice_text[6], DT_CENTER);
	drawtext("βҳ", &search_in_function_choice_text[7], DT_CENTER);
	//������ʾ��

	drawtext("���к�", &show_title_text[0], DT_CENTER);
	drawtext("��", &show_title_text[1], DT_CENTER);
	drawtext("��", &show_title_text[2], DT_CENTER);
	drawtext("��", &show_title_text[3], DT_CENTER);
	drawtext("���", &show_title_text[4], DT_CENTER);
	drawtext("��֧����", &show_title_text[5], DT_CENTER);
	drawtext("��;��Դ", &show_title_text[6], DT_CENTER);
	//����

	way_new = 0;
	function_new = 0;
	//��ʱ��״̬

	search_in_all();
	show(show_list_text, 10, show_color);
	msg_state_former = -1;//!
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(search_in_function_choice, 8, msg);
		int msg_t = msg_state;//��ȡ���״̬
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//����
			else if (msg_state == 1)
			{
				way_new = 1 - way_new;
				text_takeplace(wayway[way_new], &search_in_function_choice_text[1], DT_CENTER, choice_color);
				function_new = 0;
				if (way_new == 0)	text_takeplace(funct_in[function_new], &search_in_function_choice_text[2], DT_CENTER, choice_color);
				else text_takeplace(funct_out[function_new], &search_in_function_choice_text[2], DT_CENTER, choice_color);
			}
			//�޸�Ҫ���ҵ���֧����
			else if (msg_state == 2)
			{
				if (way_new == 0)
				{
					function_new = (function_new + 1) % funct_in_num;
					text_takeplace(funct_in[function_new], &search_in_function_choice_text[2], DT_CENTER, choice_color);
				}
				//��������
				else
				{
					function_new = (function_new + 1) % funct_out_num;
					text_takeplace(funct_out[function_new], &search_in_function_choice_text[2], DT_CENTER, choice_color);
				}
				//֧������
			}
			//�޸�Ҫ���ҵ���;
			if (show_num_all == -1 && msg_state >= 3)
			{
				warning("������", DT_CENTER);
				msg_state_former = msg_t;//!
				continue;
			}
			//������
			else
			{
				page_num_all = (show_num_all + 10) / 10 - 1;//ˢ����ҳ��
				if (page_num_all > 0)
				{
					if (msg_state == 4)
					{
						show_page = (show_page + 2 * page_num_all + 2 - 1) % (page_num_all + 1);
					}
					//��һҳ
					else if (msg_state == 5)
					{
						show_page = (show_page + 1) % (page_num_all + 1);
					}
					//��һҳ
					else if (msg_state == 6)
					{
						show_page = 0;
					}
					//��ҳ
					else if (msg_state == 7)
					{
						show_page = page_num_all;
					}
					//βҳ
				}
				else show_page = 0;
			}
			//����ҳ������Ѱ������ҳ����βҳ
			if (msg_state >= 3)	show(show_list_text, 10, show_color);//��ʾ
		}
		msg_state_former = msg_t;//!
	}
}
//�����ܲ�ѯ

void search()
{
BB:setbkcolor(base_color);//��ͼ
	cleardevice();//����ˢ��
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	setlinecolor(WHITE);//����
	settextcolor(WHITE);//����

	int search_choice[4][4];

	//����׼��
	search_choice[0][0] = 0;
	search_choice[0][1] = 0;
	search_choice[0][2] = menu_page[0] * 5 / 32;
	search_choice[0][3] = menu_page[1] / 32;

	search_choice[3][0] = menu_page[0] / 4;
	search_choice[3][1] = menu_page[1] / 4;
	search_choice[3][2] = menu_page[0] * 3 / 4;
	search_choice[3][3] = menu_page[1] * 5 / 12;//���ɵ�����

	search_choice[1][0] = menu_page[0] / 4;
	search_choice[1][1] = menu_page[1] * 5 / 12;
	search_choice[1][2] = menu_page[0] * 3 / 4;
	search_choice[1][3] = menu_page[1] * 7 / 12;

	search_choice[2][0] = menu_page[0] / 4;
	search_choice[2][1] = menu_page[1] * 7 / 12;
	search_choice[2][2] = menu_page[0] * 3 / 4;
	search_choice[2][3] = menu_page[1] * 3 / 4;
	//ѡ���ܼ�λ��

	RECT search_msg_to_RED[4];
	setfillcolor(page_color);
	settextcolor(WHITE);
	for (int i = 0; i <= 3; i++)
	{
		search_msg_to_RED[i] = { search_choice[i][0],search_choice[i][1], search_choice[i][2], search_choice[i][3] };
		fillrectangle(search_choice[i][0], search_choice[i][1], search_choice[i][2], search_choice[i][3]);
	}
	//�ɵ����ľ���

	RECT search_choice_text[3];
	for (int i = 0; i < 3; i++)
	{
		search_choice_text[i] = { search_choice[i + 1][0],(search_choice[i + 1][1] + search_choice[i + 1][3]) / 2 - menu_page[1] / 32,search_choice[i + 1][2],search_choice[i + 1][1] + search_choice[i + 1][3] + menu_page[1] / 32 };
	}
	drawtext("�����ϼ�ҳ�� ", &search_msg_to_RED[0], DT_CENTER);
	drawtext("��ʱ���ѯ", &search_choice_text[0], DT_CENTER);
	drawtext("����Ŀ��ѯ ", &search_choice_text[1], DT_CENTER);
	drawtext("ѡ���ѯ��ʽ", &search_choice_text[2], DT_CENTER);
	//�����ʾ��
	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(search_choice, 3, msg);
		int msg_t = msg_state;//��ȡ���״̬
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			cleardevice();
			if (msg_state == 0)	return;//����
			else if (msg_state == 1)	search_in_time();//��ʱ���ѯ
			else if (msg_state == 2)	search_in_function();//�����ܲ�ѯ
			break;
		}
		msg_state_former = msg_t;//!
	}
	goto BB;
}
//��ѯ����

void change()
{

	setbkcolor(base_color);//��ͼ
	cleardevice();//����ˢ��
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	setlinecolor(WHITE);//����
	settextcolor(WHITE);//����

	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;
	setfillcolor(choice_color);

	int change_choice[10][4];

	//����׼��
	change_choice[0][0] = 0;
	change_choice[0][1] = 0;
	change_choice[0][2] = menu_page[0] * 5 / 32;
	change_choice[0][3] = menu_page[1] / 32;//����

	change_choice[1][0] = menu_page[0] / 4;
	change_choice[1][1] = menu_page[1] / 12;
	change_choice[1][2] = menu_page[0] * 3 / 8;
	change_choice[1][3] = menu_page[1] * 2 / 12;//�޸ļ�

	change_choice[2][0] = menu_page[0] / 2;
	change_choice[2][1] = menu_page[1] / 12;
	change_choice[2][2] = menu_page[0] * 5 / 8;
	change_choice[2][3] = menu_page[1] * 2 / 12;//ɾ����

	change_choice[3][0] = menu_page[0] / 2 - 20;
	change_choice[3][1] = menu_page[1] * 10 / 12;
	change_choice[3][2] = menu_page[0] / 2 + 20;
	change_choice[3][3] = menu_page[1] * 11 / 12;//ȷ��

	change_choice[7][0] = menu_page[0] / 4;
	change_choice[7][1] = menu_page[1] * 5 / 12;
	change_choice[7][2] = menu_page[0] * 3 / 4;
	change_choice[7][3] = menu_page[1] * 7 / 12;//���

	change_choice[8][0] = menu_page[0] / 4;
	change_choice[8][1] = menu_page[1] * 7 / 12;
	change_choice[8][2] = menu_page[0] / 2;
	change_choice[8][3] = menu_page[1] * 3 / 4;//�˵�����

	change_choice[9][0] = menu_page[0] / 2;
	change_choice[9][1] = menu_page[1] * 7 / 12;
	change_choice[9][2] = menu_page[0] * 3 / 4;
	change_choice[9][3] = menu_page[1] * 3 / 4;//��;/��Դ



	change_choice[4][0] = menu_page[0] / 4;
	change_choice[4][1] = menu_page[1] / 4;
	change_choice[4][2] = menu_page[0] * 5 / 12;
	change_choice[4][3] = menu_page[1] * 5 / 12;//��

	change_choice[5][0] = menu_page[0] * 5 / 12;
	change_choice[5][1] = menu_page[1] / 4;
	change_choice[5][2] = menu_page[0] * 7 / 12;
	change_choice[5][3] = menu_page[1] * 5 / 12;//��

	change_choice[6][0] = menu_page[0] * 7 / 12;
	change_choice[6][1] = menu_page[1] / 4;
	change_choice[6][2] = menu_page[0] * 3 / 4;
	change_choice[6][3] = menu_page[1] * 5 / 12;//��


	RECT change_text[10];
	for (int i = 3; i < 10; i++)
	{
		change_text[i] = { change_choice[i][0], change_choice[i][1], change_choice[i][2], change_choice[i][3] };
	}
	change_text[0] = { change_choice[0][0], change_choice[0][1], change_choice[0][2], change_choice[0][3] };
	change_text[1] = { (change_choice[1][0] + change_choice[1][2]) / 2 - 20,(change_choice[1][1] + change_choice[1][3]) / 2 - 20,(change_choice[1][0] + change_choice[1][2]) / 2 + 20, (change_choice[1][1] + change_choice[1][3]) / 2 + 20 };
	change_text[2] = { (change_choice[2][0] + change_choice[2][2]) / 2 - 20,(change_choice[2][1] + change_choice[2][3]) / 2 - 20,(change_choice[2][0] + change_choice[2][2]) / 2 + 20, (change_choice[2][1] + change_choice[2][3]) / 2 + 20 };
	//�ı���ʾ����
	for (int i = 0; i < 10; i++)
	{
		fillrectangle(change_choice[i][0], change_choice[i][1], change_choice[i][2], change_choice[i][3]);
	}

	drawtext("�����ϼ�ҳ��", &change_text[0], DT_LEFT);
	drawtext("�޸�", &change_text[1], DT_LEFT);
	drawtext("ɾ��", &change_text[2], DT_LEFT);
	drawtext("ȷ��", &change_text[3], DT_LEFT);
	drawtext("�꣺", &change_text[4], DT_LEFT);
	drawtext("�£�", &change_text[5], DT_LEFT);
	drawtext("�գ�", &change_text[6], DT_LEFT);
	drawtext("��", &change_text[7], DT_LEFT);
	drawtext("�˵����ͣ�", &change_text[8], DT_LEFT);
	drawtext("��;/��Դ��", &change_text[9], DT_LEFT);
	//������ʾ��

	TCHAR num_delete[5] = "";
	TCHAR num_change[5] = "";

	text_takeplace(wayway[way_new], &change_text[8], DT_CENTER, choice_color);
	if (way_new == 0)  text_takeplace(funct_in[function_new], &change_text[9], DT_CENTER, choice_color);
	//��������
	else  text_takeplace(funct_out[function_new], &change_text[9], DT_CENTER, choice_color);
	//֧������

	int change_state = 0;//0δѡ��״̬��2ѡ���޸�
	int way_new2 = 0;
	int function_new2 = 0;

	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(change_choice, 10, msg);
		int msg_t = msg_state;//��ȡ���״̬
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//����
			else if (msg_state == 1 && change_state == 0)
			{
				change_state = 2;
				InputBox(num_change, 5, "������Ҫ�޸ĵ����кţ�");
			}
			//�����޸ĵ���
			else if (msg_state == 2)
			{
				InputBox(num_delete, 5, "������Ҫɾ�������кţ�");
				int num_delete_atoi = atoi(num_delete);
				search_in_all();
				if (show_num_all < num_delete_atoi)
				{
					warning("�����кŲ�����", DT_CENTER);
				}
				else {
					FILE* fp_new = fopen("test.txt", "a+");
					fp = fopen(file_name, "r");
					fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
					int i = -1;
					while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF && i < num_delete_atoi - 1)
					{
						fprintf(fp_new, "%d %d %d %d %d %d\n", year_new, month_new, day_new, money_new, way_new, function_new);
						i++;
					}
					fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new);
					while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF)
					{
						fprintf(fp_new, "%d %d %d %d %d %d\n", year_new, month_new, day_new, money_new, way_new, function_new);
					}
					fclose(fp);
					fclose(fp_new);

					remove(file_name);

					fp_new = fopen("test.txt", "r");
					fseek(fp_new, 0l, SEEK_SET);
					fp = fopen(file_name, "a+");
					fprintf(fp, "%s\n%s\n%s\n", root, question, answer);
					TCHAR c;
					while ((c = getc(fp_new)) != EOF)
					{
						fprintf(fp, "%c", c);
					}
					fclose(fp_new);
					remove("test.txt");
					fclose(fp);
					msg_state = 0;
					warning("ok", DT_CENTER);
				}
			}
			//ɾ��
			else if (msg_state >= 3 && change_state == 2)
			{
				if (msg_state == 3)
				{
					int num_change_atoi = atoi(num_change);
					search_in_all();
					if (show_num_all < num_change_atoi)
					{
						warning("�����кŲ�����", DT_CENTER);
						change_state = 0;
					}
					else {
						fp = fopen(file_name, "r");
						FILE* fp_new = fopen("test.txt", "a+");
						fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
						int i = -1;
						while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF && i < num_change_atoi - 1)
						{
							fprintf(fp_new, "%d %d %d %d %d %d\n", year_new, month_new, day_new, money_new, way_new, function_new);
							i++;
						}
						fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new);
						fprintf(fp_new, "%d %d %d %d %d %d\n", atoi(year_new_text), atoi(month_new_text), atoi(day_new_text), atoi(money_new_text), way_new2, function_new2);
						while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF)
						{
							fprintf(fp_new, "%d %d %d %d %d %d\n", year_new, month_new, day_new, money_new, way_new, function_new);
						}
						fclose(fp);
						fclose(fp_new);
						remove(file_name);

						fp = fopen(file_name, "a+");
						fp_new = fopen("test.txt", "r");
						fseek(fp, 0l, SEEK_SET);
						fseek(fp_new, 0l, SEEK_SET);
						fprintf(fp, "%s\n%s\n%s\n", root, question, answer);
						TCHAR c;
						while ((c = getc(fp_new)) != EOF)
						{
							fprintf(fp, "%c", c);
						}
						fclose(fp_new);
						remove("test.txt");
						fclose(fp);
						warning("ok", DT_CENTER);
						change_state = 0;
					}
				}
				//ȷ��
				else if (msg_state == 4)
				{
					InputBox(year_new_text, 5, "��������:");
					text_takeplace(year_new_text, &change_text[4], DT_CENTER, choice_color);
				}
				//��
				else if (msg_state == 5)
				{
					InputBox(month_new_text, 3, "��������:");
					text_takeplace(month_new_text, &change_text[5], DT_CENTER, choice_color);
				}
				//��
				else if (msg_state == 6)
				{
					InputBox(day_new_text, 3, "��������:");
					text_takeplace(day_new_text, &change_text[6], DT_CENTER, choice_color);
				}
				//��
				if (msg_state == 7)
				{
					InputBox(money_new_text, 5, "��������:");
					text_takeplace(money_new_text, &change_text[7], DT_CENTER, choice_color);
				}
				//���
				else if (msg_state == 8)
				{
					way_new2 = 1 - way_new2;
					text_takeplace(wayway[way_new2], &change_text[8], DT_CENTER, choice_color);
					function_new2 = 0;
					if (way_new2 == 0)	text_takeplace(funct_in[function_new2], &change_text[9], DT_CENTER, choice_color);
					else text_takeplace(funct_out[function_new2], &change_text[9], DT_CENTER, choice_color);
				}
				//�޸�Ҫ���ҵ���֧����
				else if (msg_state == 9)
				{
					if (way_new2 == 0)
					{
						function_new2 = (function_new2 + 1) % funct_in_num;
						text_takeplace(funct_in[function_new2], &change_text[9], DT_CENTER, choice_color);
					}
					//��������
					else
					{
						function_new2 = (function_new2 + 1) % funct_out_num;
						text_takeplace(funct_out[function_new2], &change_text[9], DT_CENTER, choice_color);
					}
					//֧������
				}
				//�޸�Ҫ���ҵ���;
			}
			//�޸�����
		}
		msg_state_former = msg_t;//!
	}

}
//�޸Ĺ���

void summary_to_show(int sum_in_month[][4], int summary_year, int summary_state, RECT summary_show_text[])
{
	TCHAR sum_in_money[5];
	TCHAR sum_out_money[5];
	TCHAR sum_in_and_out_money[5];
	TCHAR sum_month[5];
	for (int i = 0; i < 12; i++)
	{
		for (int t = 0; t < 3; t++)		sum_in_month[i][t] = 0;
		sum_in_month[i][3] = i + 1;
	}

	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF)
	{
		if (summary_year == year_new)
		{
			sum_in_month[month_new - 1][way_new] += money_new;
			sum_in_month[month_new - 1][2] = sum_in_month[month_new - 1][0] - sum_in_month[month_new - 1][1];
		}

	}
	//������˵�����
	if (summary_state == 1)
	{
		for (int i = 0; i < 12; i++)
		{
			for (int t = i; t < 12; t++)
			{
				if (sum_in_month[i][2] < sum_in_month[t][2])
				{
					for (int k = 0; k < 4; k++)
					{
						int m = sum_in_month[i][k];
						sum_in_month[i][k] = sum_in_month[t][k];
						sum_in_month[t][k] = m;
					}
				}
			}
		}
	}
	//����ģʽ�޸�����
	for (int i = 0; i < 12; i++)
	{
		text_takeplace(itoa(sum_in_month[i][0], sum_in_money, 10), &summary_show_text[4 * i + 1], DT_CENTER, page_color);
		text_takeplace(itoa(sum_in_month[i][1], sum_out_money, 10), &summary_show_text[4 * i + 2], DT_CENTER, page_color);
		text_takeplace(itoa(sum_in_month[i][2], sum_in_and_out_money, 10), &summary_show_text[4 * i + 3], DT_CENTER, page_color);
		text_takeplace(itoa(sum_in_month[i][3], sum_month, 10), &summary_show_text[4 * i], DT_CENTER, page_color);
	}
	//�������
}
void summary()
{
	setbkcolor(base_color);//��ͼ
	cleardevice();//����ˢ��
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	setlinecolor(WHITE);//����
	settextcolor(WHITE);//����

	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;

	setfillcolor(show_color);

	//����׼��
	int summary_choice[5][4];
	summary_choice[0][0] = 0;
	summary_choice[0][1] = 0;
	summary_choice[0][2] = menu_page[0] / 8;
	summary_choice[0][3] = menu_page[1] / 32;//�˳�

	summary_choice[1][0] = menu_page[0] / 4;
	summary_choice[1][1] = menu_page[1] / 16;
	summary_choice[1][2] = menu_page[0] * 9 / 32;
	summary_choice[1][3] = menu_page[1] * 2 / 16;//����

	summary_choice[2][0] = menu_page[0] * 9 / 32;
	summary_choice[2][1] = menu_page[1] / 16;
	summary_choice[2][2] = menu_page[0] * 23 / 32;
	summary_choice[2][3] = menu_page[1] * 2 / 16;//2023

	summary_choice[3][0] = menu_page[0] * 23 / 32;
	summary_choice[3][1] = menu_page[1] / 16;
	summary_choice[3][2] = menu_page[0] * 3 / 4;
	summary_choice[3][3] = menu_page[1] * 2 / 16;//>>

	summary_choice[4][0] = menu_page[0] * 14 / 16;
	summary_choice[4][1] = 0;
	summary_choice[4][2] = menu_page[015 / 16];
	summary_choice[4][3] = menu_page[1] / 32;//��ģʽ

	RECT summary_choice_text[5];
	for (int i = 0; i < 5; i++)
	{
		summary_choice_text[i] = { summary_choice[i][0],summary_choice[i][1], summary_choice[i][2], summary_choice[i][3] };
		fillrectangle(summary_choice[i][0], summary_choice[i][1], summary_choice[i][2], summary_choice[i][3]);
	}
	//�����ı���

	int summary__choice_to_RED[4][4] = { {summary_choice[0][0],summary_choice[0][1], summary_choice[0][2], summary_choice[0][3]} ,{summary_choice[1][0],summary_choice[1][1], summary_choice[1][2], summary_choice[1][3]} ,{summary_choice[3][0],summary_choice[3][1], summary_choice[3][2], summary_choice[3][3]},{summary_choice[4][0],summary_choice[4][1], summary_choice[4][2], summary_choice[4][3]} };
	RECT summary_show_title_text[4];
	RECT summary_show_text[12 * 4];
	int start_line = summary_choice[2][3];
	int end_line = menu_page[1];
	for (int t = 0; t < 4; t++)
	{
		for (int i = 0; i < 12; i++)
		{
			summary_show_text[4 * i + t] = { menu_page[0] * (t + 2) / 8,start_line + (end_line - start_line) * (i + 1) / 13, menu_page[0] * (t + 3) / 8,start_line + (end_line - start_line) * (i + 2) / 13 };
		}
		summary_show_title_text[t] = { menu_page[0] * (t + 2) / 8,start_line, menu_page[0] * (t + 3) / 8,start_line + (end_line - start_line) / 13 };
	}

	TCHAR summary_state_text[2][20] = { "��ʱ������","����������" };
	int summary_state = 0;

	TCHAR summary_year[5] = "2023";
	InputBox(summary_year, 5, "�������ܽ���ݣ�");

	drawtext("�·�", &summary_show_title_text[0], DT_CENTER);
	drawtext("����", &summary_show_title_text[1], DT_CENTER);
	drawtext("֧��", &summary_show_title_text[2], DT_CENTER);
	drawtext("����", &summary_show_title_text[3], DT_CENTER);
	summary_to_show(sum_in_month, atoi(summary_year), summary_state, summary_show_text);

	drawtext("�����ϼ�ҳ��", &summary_choice_text[0], DT_CENTER);
	drawtext("<<", &summary_choice_text[1], DT_CENTER);
	drawtext(summary_year, &summary_choice_text[2], DT_CENTER);
	drawtext(">>", &summary_choice_text[3], DT_CENTER);
	drawtext(summary_state_text[summary_state], &summary_choice_text[4], DT_CENTER);
	//������ʾ��
	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(summary__choice_to_RED, 4, msg);//��ȡ���״̬
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//����
			else
			{
				if (msg_state == 3)
				{
					summary_state = 1 - summary_state;
					text_takeplace(summary_state_text[summary_state], &summary_choice_text[4], DT_CENTER, show_color);
				}
				//�޸�ģʽ
				else if (msg_state == 1)
				{
					itoa(atoi(summary_year) - 1, summary_year, 10);
					text_takeplace(summary_year, &summary_choice_text[2], DT_CENTER, show_color);
				}
				//���-1
				else if (msg_state == 2 && msg.uMsg)
				{
					itoa(atoi(summary_year) + 1, summary_year, 10);
					text_takeplace(summary_year, &summary_choice_text[2], DT_CENTER, show_color);
				}
				//���+1
				summary_to_show(sum_in_month, atoi(summary_year), summary_state, summary_show_text);
				//��ʾ
			}
		}
		msg_state_former = msg_state;
	}
}
//�ܽṦ��

// ������������ȼ�
int getPriority(char op) {
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}

// ִ�ж�Ԫ����
int applyOp(int a, int b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	}
	return 0; // ����Ч�����������·���һ��Ĭ��ֵ
}

// ������ʽ��ֵ
int calculateExpression(char* expression) {
	int numStack[100] = { 0 }; // ����ջ
	char opStack[100] = { 0 }; // �����ջ
	int numTop = -1;
	int opTop = -1;

	for (int i = 0; expression[i] != '\0'; i++) {
		if (expression[i] == ' ')
			continue;

		if (expression[i] >= '0' && expression[i] <= '9') {
			// ��������
			int num = 0;
			while (expression[i] >= '0' && expression[i] <= '9') {
				num = num * 10 + (expression[i] - '0');
				i++;
			}
			i--;

			numStack[++numTop] = num;
		}
		else if (expression[i] == '(') {
			// ����������
			opStack[++opTop] = '(';
		}
		else if (expression[i] == ')') {
			// ����������
			while (opTop != -1 && opStack[opTop] != '(') {
				int b = numStack[numTop--];
				int a = numStack[numTop--];
				char op = opStack[opTop--];
				numStack[++numTop] = applyOp(a, b, op);
			}
			// ����������
			if (opTop != -1 && opStack[opTop] == '(') {
				opTop--;
			}
		}
		else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
			// ���������
			while (opTop != -1 && getPriority(opStack[opTop]) >= getPriority(expression[i]) && numTop >= 1) {
				int b = numStack[numTop--];
				int a = numStack[numTop--];
				char op = opStack[opTop--];
				numStack[++numTop] = applyOp(a, b, op);
			}
			// ����������opStack
			opStack[++opTop] = expression[i];
		}
	}

	// ����ʣ��������
	while (opTop != -1) {
		int b = numStack[numTop--];
		int a = numStack[numTop--];
		char op = opStack[opTop--];
		numStack[++numTop] = applyOp(a, b, op);
	}

	return numStack[numTop];
}

int do_caculater(TCHAR expression[100])
{
	int result = calculateExpression(expression);
	return result;
}
void caculater()
{
	setbkcolor(base_color);//��ͼ
	cleardevice();
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	settextcolor(WHITE);
	setlinecolor(WHITE);
	setfillcolor(page_color);

	int caculater_choice[3][4];

	caculater_choice[0][0] = 0;
	caculater_choice[0][1] = 0;
	caculater_choice[0][2] = menu_page[0] * 5 / 32;
	caculater_choice[0][3] = menu_page[1] / 32;

	caculater_choice[1][0] = menu_page[0] * 12 / 32;;
	caculater_choice[1][1] = menu_page[1] * 14 / 32;;
	caculater_choice[1][2] = menu_page[0] * 20 / 32;
	caculater_choice[1][3] = menu_page[1] * 18 / 32;

	caculater_choice[2][0] = menu_page[0] * 12 / 32;;
	caculater_choice[2][1] = menu_page[1] * 18 / 32;;
	caculater_choice[2][2] = menu_page[0] * 20 / 32;
	caculater_choice[2][3] = menu_page[1] * 22 / 32;

	for (int i = 0; i < 3; i++)
	{
		fillrectangle(caculater_choice[i][0], caculater_choice[i][1], caculater_choice[i][2], caculater_choice[i][3]);
	}

	RECT caculater_choice_text[3];
	caculater_choice_text[0] = { caculater_choice[0][0],caculater_choice[0][1], caculater_choice[0][2], caculater_choice[0][3] };
	caculater_choice_text[1] = { menu_page[0] * 14 / 32,menu_page[1] * 14 / 32, menu_page[0] * 18 / 32, menu_page[1] * 18 / 32 };
	caculater_choice_text[2] = { menu_page[0] * 12 / 32,menu_page[1] * 18 / 32, menu_page[0] * 20 / 32, menu_page[1] * 22 / 32 };

	text_takeplace("�����ϼ�ҳ��", &caculater_choice_text[0], DT_CENTER, page_color);
	text_takeplace("��ʼ����:", &caculater_choice_text[1], DT_CENTER, page_color);

	TCHAR caculater_test[100];
	int caculater_answer;
	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(caculater_choice, 3, msg);
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			else if (msg_state == 1)
			{
				InputBox(caculater_test, 100, "���������ʽ:");
				caculater_answer = do_caculater(caculater_test);
				text_takeplace("���Ϊ��", &caculater_choice_text[2], DT_LEFT, page_color);
				text_takeplace(itoa(caculater_answer, caculater_test, 10), &caculater_choice_text[2], DT_CENTER, page_color);
			}
		}
		msg_state_former = msg_state;
	}
}
//����������


void information()
{
	setbkcolor(base_color);//��ͼ
	cleardevice();//����ˢ��
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	setlinecolor(WHITE);//����
	settextcolor(WHITE);//����

	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;
	setfillcolor(page_color);

	//����׼��
	TCHAR root_test[root_length + 1];
	InputBox(root_test, root_length + 1, "�������˻�����");
	if (strcmp(root_test, root) != 0)
	{
		warning("�������", DT_CENTER);
		cleardevice();
		return;
	}
	//����������֤�Ƿ���޸�
	int information_choice[6][4];

	information_choice[0][0] = 0;
	information_choice[0][1] = 0;
	information_choice[0][2] = menu_page[0] * 5 / 32;
	information_choice[0][3] = menu_page[1] / 32;//���ؼ�

	for (int i = 0; i < 4; i++)
	{
		information_choice[i + 1][0] = menu_page[0] / 4;
		information_choice[i + 1][1] = menu_page[1] * (3 + 2 * i) / 12 - 10;
		information_choice[i + 1][2] = menu_page[0] * 3 / 4;
		information_choice[i + 1][3] = menu_page[1] * (3 + 2 * i) / 12 + 10;
	}

	information_choice[5][0] = menu_page[0] * 15 / 32;
	information_choice[5][1] = menu_page[1] * (3 + 2 * 4) / 12 - 10;
	information_choice[5][2] = menu_page[0] * 17 / 32;
	information_choice[5][3] = menu_page[1] * (3 + 2 * 4) / 12 + 10;//ȷ�ϼ�

	RECT information_choice_text[6];
	for (int i = 0; i < 6; i++)
	{
		information_choice_text[i] = { information_choice[i][0] ,information_choice[i][1] ,information_choice[i][2] ,information_choice[i][3] };
		fillrectangle(information_choice[i][0], information_choice[i][1], information_choice[i][2], information_choice[i][3]);

	}

	drawtext("�����ϼ�ҳ��", &information_choice_text[0], DT_LEFT);
	drawtext("�˻���", &information_choice_text[1], DT_LEFT);
	drawtext("�˻�����", &information_choice_text[2], DT_LEFT);
	drawtext("�ܱ�����", &information_choice_text[3], DT_LEFT);
	drawtext("�ܱ������", &information_choice_text[4], DT_LEFT);
	drawtext("ȷ��", &information_choice_text[5], DT_LEFT);
	//��ʾ��

	drawtext(name, &information_choice_text[1], DT_CENTER);
	drawtext(root, &information_choice_text[2], DT_CENTER);
	drawtext(question, &information_choice_text[3], DT_CENTER);
	drawtext(answer, &information_choice_text[4], DT_CENTER);

	TCHAR name_new[name_length + 1] = "";//�˻���
	TCHAR root_new[root_length + 1] = "";//�˻�����
	TCHAR question_new[question_length] = "";//�����ܱ�����
	TCHAR answer_new[answer_length] = "";//���������ܱ������

	strcpy(name_new, name);
	strcpy(root_new, root);
	strcpy(question_new, question);
	strcpy(answer_new, answer);
	//��ʱ
	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(information_choice, 6, msg);//��ȡ���״̬
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//����
			else if (msg_state == 1)
			{
				InputBox(name_new, name_length, "������ĺ��˻���");
				text_takeplace(name_new, &information_choice_text[1], DT_CENTER, page_color);
			}
			//�˻���
			else if (msg_state == 2)
			{
				InputBox(root_new, root_length, "������ĺ�����");
				text_takeplace(name, &information_choice_text[2], DT_CENTER, page_color);
			}
			//����
			else if (msg_state == 3)
			{
				InputBox(question_new, question_length, "������ĺ��ܱ�����");
				text_takeplace(question_new, &information_choice_text[3], DT_CENTER, page_color);
			}
			//�ܱ�����
			else if (msg_state == 4)
			{
				InputBox(answer_new, answer_length, "������ĺ��ܱ������");
				text_takeplace(answer_new, &information_choice_text[4], DT_CENTER, page_color);
			}
			//��
			else if (msg_state == 5)
			{
				fp = fopen(file_name, "r");
				FILE* fp_new = fopen("test.txt", "a+");
				fseek(fp, strlen(root) + strlen(question) + strlen(answer) + 6, SEEK_SET);
				TCHAR c;
				while ((c = getc(fp)) != EOF)
					putc(c, fp_new);
				fclose(fp);
				fclose(fp_new);
				remove(file_name);

				strcpy(name, name_new);
				strcpy(file_name, name);
				strcat(file_name, ".txt");
				strcpy(root, root_new);
				strcpy(question, question_new);
				strcpy(answer, answer_new);

				fp = fopen(file_name, "a+");
				fp_new = fopen("test.txt", "r");
				fseek(fp_new, 0l, SEEK_SET);
				fprintf(fp, "%s\n%s\n%s\n", root_new, question_new, answer_new);
				while ((c = getc(fp_new)) != EOF)
					putc(c, fp);
				fclose(fp);
				fclose(fp_new);
				remove("test.txt");

				break;
			}
			//ȷ��
		}
		msg_state_former = msg_state;
	}
}
//�˻���Ϣ����


void sum_in_and_sum_out()
{
	fp = fopen(file_name, "r");
	sum_in_all = 0;
	sum_out_all = 0;
	fseek(fp, strlen(root) + strlen(question) + strlen(answer) + 6, SEEK_SET);
	while (fscanf(fp, "%d%d%d%d%d%d\n", &year_new, &month_new, &day_new, &money_new, &way_new, &function_new) != EOF)
	{
		if (way_new == 0) sum_in_all += money_new;
		else sum_out_all += money_new;
	}
	sum = sum_in_all - sum_out_all;
	//ˢ������֧
	fclose(fp);
}
//ˢ������֧
void menu()
{
	initgraph(menu_page[0], menu_page[1]);

	//����׼��
	int menu[7][4];
	for (int i = 0; i <= 6; i++)
	{
		menu[i][0] = menu_page[0] * 3 / 8;
		menu[i][1] = menu_page[1] * (7 + i * 2) / 28;
		menu[i][2] = menu_page[0] * 5 / 8;
		menu[i][3] = menu_page[1] * (9 + i * 2) / 28;
	}
	//�������

	int in_and_out[3][4];
	for (int i = 0; i <= 2; i++)
	{
		in_and_out[i][0] = menu_page[0] * i / 3;
		in_and_out[i][1] = 0;
		in_and_out[i][2] = menu_page[0] * (i + 1) / 3;
		in_and_out[i][3] = menu_page[1] / 32;
	}
	//��֧���

	//ҳ�����
AA:setbkcolor(base_color);//��ͼ
	cleardevice();
	setbkmode(TRANSPARENT);//д���ֵı���͸��
	settextcolor(WHITE);
	setfillcolor(page_color);//���ܼ�ɫ
	setlinecolor(WHITE);//����ɫ


	RECT in_and_out_text[3];
	for (int i = 0; i <= 2; i++)
	{
		in_and_out_text[i] = { in_and_out[i][0],in_and_out[i][1],in_and_out[i][2],in_and_out[i][3] };
		fillrectangle(in_and_out[i][0], in_and_out[i][1], in_and_out[i][2], in_and_out[i][3]);
	}
	//����֧���

	sum_in_and_sum_out();//������֧
	fillrectangle(in_and_out[0][0], in_and_out[0][1], in_and_out[2][2], in_and_out[2][3]);
	text_takeplace("���ࣺ", &in_and_out_text[0], DT_LEFT, page_color);
	line(in_and_out[0][0], in_and_out[0][3], in_and_out[0][2], in_and_out[0][3]);
	text_takeplace(itoa(sum, SUM, 10), &in_and_out_text[0], DT_CENTER, page_color);
	text_takeplace("���룺", &in_and_out_text[1], DT_LEFT, page_color);
	text_takeplace(itoa(sum_in_all, SUM_IN, 10), &in_and_out_text[1], DT_CENTER, page_color);
	text_takeplace("֧����", &in_and_out_text[2], DT_LEFT, page_color);
	text_takeplace(itoa(sum_out_all, SUM_OUT, 10), &in_and_out_text[2], DT_CENTER, page_color);
	//������֧���

	RECT menu_text[7];
	for (int i = 0; i <= 6; i++)
	{
		menu_text[i] = { menu[i][0], menu[i][1], menu[i][2], menu[i][3] };
		fillrectangle(menu[i][0], menu[i][1], menu[i][2], menu[i][3]);
	}
	//���߲����ɶ�Ӧ���α���
	text_takeplace("�����֧��¼", &menu_text[0], DT_CENTER, page_color);
	text_takeplace("��ѯ��֧��¼", &menu_text[1], DT_CENTER, page_color);
	text_takeplace("�޸���֧��¼", &menu_text[2], DT_CENTER, page_color);
	text_takeplace("�˵��ܽ�", &menu_text[3], DT_CENTER, page_color);
	text_takeplace("������", &menu_text[4], DT_CENTER, page_color);
	text_takeplace("�˻���Ϣ", &menu_text[5], DT_CENTER, page_color);
	text_takeplace("�˳�ϵͳ", &menu_text[6], DT_CENTER, page_color);
	//��书����ʾ

	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(menu, 7, msg);
		int msg_t = msg_state;//!
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			cleardevice();
			if (msg_state == 0)	add();
			else if (msg_state == 1)	search();
			else if (msg_state == 2)	change();
			else if (msg_state == 3)	summary();
			else if (msg_state == 4)	caculater();
			else if (msg_state == 5)	information();
			else if (msg_state == 6)
			{
				delete_p_chart();
				closegraph();
				return;
			}
			//�˳�
			break;
		}
		//ѡ����
		msg_state_former = msg_t;//!
	}
	goto AA;
}
//���˵�
int main()
{
	logon();
	menu();
	return 0;
}