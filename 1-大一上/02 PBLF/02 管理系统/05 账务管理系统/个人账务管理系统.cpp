#include<stdio.h>
#include<time.h>
#include<graphics.h>
#include<string.h>
#include<conio.h>
#include <stdlib.h>
#pragma warning(disable:4996)


int menu_page[2] = { 700,600 };//贮存软件窗口长，宽
RECT warning_text = { menu_page[0] / 4,menu_page[1] / 16, menu_page[0] * 3 / 4, menu_page[0] * 5 / 32 };//贮存警告/提示窗口长，宽
FILE* fp;//贮存打开文件的文件指针
#define name_length 10//用户名长度，方便修改
TCHAR file_name[name_length + 1 + 4] = "";//文件名
TCHAR name[name_length + 1] = "";//账户名

#define root_length 12//密码长度
TCHAR root[root_length + 1] = "";//账户密码

#define question_length 100//问题长度，方便修改
#define answer_length 100//答案长度，方便修改
TCHAR question[question_length] = "";//贮存密保问题
TCHAR answer[answer_length] = "";//贮存贮存密保问题答案

TCHAR wayway[2][20] = { "收入","支出" };//贮存两种状态名
#define funct_in_num 4
TCHAR funct_in[funct_in_num][20] = { "工资","生活费", "红包", "其他" };//贮存收入对应状态名
#define funct_out_num 5
TCHAR funct_out[funct_out_num][20] = { "餐饮", "购物", "交通", "社交", "其他" };//贮存支出对应状态名，方便点击时动态转换
//贮存对应状态，方便点击时动态转换


int show_num_all = 0;//贮存搜索后总账单数
int page_num_all = -1;//贮存搜索后总页数
int show_page = 0;//贮存显示的当前页数

COLORREF base_color = RGB(173, 193, 226);
COLORREF page_color = RGB(52, 66, 112);
COLORREF tips_color = RGB(101, 130, 186);//定义三种基本色调，方便使用

int sum_in_month[12][4];//分别贮存各月份情况，0收入，1支出，2结余，3月份


struct chart {
	int num;//序列号，查询时才赋值 
	int year;//年
	int month;//月
	int day;//日
	int money;//金额
	int way;//支出1或收入0
	int function;//用途或来源0,1,2,3,
	//                       0,1,2,3,4
	struct chart* next;
};
//账单链表

int sum = 0;
TCHAR SUM[15] = "";//总结余

int sum_in_all = 0;
TCHAR SUM_IN[15] = "";//总收入

int sum_out_all = 0;
TCHAR SUM_OUT[15] = "";//总支出

struct chart p_chart = { 0,0,0,0,0,0,NULL };//贮存搜索后筛选出的全部账单
struct chart* p_last = &p_chart;//用于贮存最后一位

int year_new = 2023;
int month_new = 1;
int day_new = 1;
int money_new = 0;
int way_new = 0;
int function_new = 0;
TCHAR year_new_text[5] = "2023";
TCHAR month_new_text[3] = "1";
TCHAR day_new_text[3] = "1";
TCHAR money_new_text[6] = "0";//最多5位数 
//暂时变量存储账单各属性

int msg_state_former = -1;//鼠标前刻状态
int msg_state = -1;//鼠标现在状态（分区）

void warning(LPCTSTR str, UINT uFormat)
{
	setbkmode(OPAQUE);//写文字时的背景是软件背景色可以去掉警告
	settextcolor(RED);//文字红色警告
	drawtext(str, &warning_text, uFormat);//显示文字
	Sleep(2000);
	drawtext("                                  ", &warning_text, uFormat);//要去去掉警告或恭喜！！！！！！！！！！！！
	setbkmode(TRANSPARENT);//写文字的背景透明
	settextcolor(WHITE);//恢复白字
}
//用于警告/提示

void msg_to_RED(int page[][4], int page_num, MOUSEMSG msg)//各分块坐标，分板块数（除空白）
{
	msg_state = -1;
	for (int i = 0; i <= page_num - 1; i++)
	{
		if (msg.x <page[i][2] && msg.x >page[i][0] && msg.y <page[i][3] && msg.y >page[i][1])
			msg_state = i;
	}
	//判断鼠标位置

	if (msg_state_former >= 0 && msg_state != msg_state_former)
	{
		setlinecolor(WHITE);
		rectangle(page[msg_state_former][0], page[msg_state_former][1], page[msg_state_former][2], page[msg_state_former][3]);
	}
	//视情况将之前区域边框刷白
	if (msg_state >= 0)
	{
		setlinecolor(RED);
		rectangle(page[msg_state][0], page[msg_state][1], page[msg_state][2], page[msg_state][3]);
	}
	setlinecolor(WHITE);
}
//点亮操作，鼠标放上去边框就变红，离开就变 回白色

void text_takeplace(LPCTSTR str, RECT* pRect, UINT uFormat, COLORREF page_color)
{
	setbkcolor(page_color);
	setbkmode(OPAQUE);
	drawtext("            ", pRect, uFormat);
	setbkmode(TRANSPARENT);
	drawtext(str, pRect, uFormat);
	setbkcolor(base_color);//底图色
}
//文字替换,要改变背景色搭配

int logonok()
{
	if (strlen(name) == 0)
	{
		if (strlen(root) == 0)
		{
			warning("请输入账户名和密码", DT_CENTER);
			return 0;
		}
		//未输入账户名和密码
		else
		{
			warning("请输入账户名", DT_CENTER);
			return 0;
		}
	}
	//未输入账户名
	else if (strlen(root) != root_length)
	{
		warning("密码长度错误，请重新输入", DT_CENTER);
		return 0;
	}
	//密码长度有误
	else
	{
		fp = fopen(file_name, "a+");
		fseek(fp, 0l, SEEK_SET);//文件开头
		TCHAR c = fgetc(fp);
		fseek(fp, 0l, SEEK_SET);//文件开头

		if (c == EOF)
		{
			fprintf(fp, "%s\n", root);
			warning("注册成功，即将设置密保问题！", DT_CENTER);
			fclose(fp);
			return 2;
		}
		//注册
		else
		{
			TCHAR root2[root_length + 1];
			fscanf(fp, "%s\n", root2);
			if (strcmp(root, root2) != 0)
			{
				warning("密码错误，请重新输入", DT_CENTER);
				fclose(fp);
				return 0;
			}
			else
			{
				fscanf(fp, "%s\n", question);
				fscanf(fp, "%s\n", answer);
				strcpy(file_name, name);
				strcat(file_name, ".txt");
				warning("登录成功，即将进入！", DT_CENTER);
				fclose(fp);
				return 1;
			}
		}
		//登录
	}
}
//确认情况
void logon()
{
	//数据准备

	int graph[2] = { 1000,700 };
	//登录窗口窗口长，宽
	int logon_page[4] = { graph[0] / 8,graph[1] / 4,graph[0] * 4 / 8,graph[1] * 3 / 4 };
	//登录界面
	int logon_name[4] = { graph[0] * 3 / 16,logon_page[1] + (logon_page[3] - logon_page[1]) * 3 / 10,graph[0] * 7 / 16,logon_page[1] + (logon_page[3] - logon_page[1]) * 4 / 10 };
	//账户框
	int logon_root[4] = { graph[0] * 3 / 16,logon_page[1] + (logon_page[3] - logon_page[1]) * 5 / 10,graph[0] * 7 / 16,logon_page[1] + (logon_page[3] - logon_page[1]) * 6 / 10 };
	//密码框
	int logon_ok[4] = { graph[0] * 10 / 32 - 3,logon_page[1] + (logon_page[3] - logon_page[1]) * 7 / 10,graph[0] * 11 / 32,logon_page[1] + (logon_page[3] - logon_page[1]) * 15 / 20 };
	//确认框
	int tips[4] = { graph[0] * 4 / 8 ,graph[1] / 4, graph[0] * 6 / 8,graph[1] * 3 / 4 };
	//提示框
	int logon_question[4] = { graph[0] * 11 / 12,0,graph[0],graph[1] / 24 };
	//忘记密码框
	int msg_to_RED_logon[4][4] = { logon_name[0] ,logon_name[1] , logon_name[2] , logon_name[3] , logon_root[0] ,logon_root[1] ,logon_root[2] ,logon_root[3] ,logon_ok[0] ,logon_ok[1] ,logon_ok[2] ,logon_ok[3],logon_question[0],logon_question[1], logon_question[2], logon_question[3] };
	//将各个框合在一起，方便点亮



	//页面设计
	initgraph(graph[0], graph[1]);

	setbkcolor(base_color);//底图
	cleardevice();//清屏刷新
	setbkmode(TRANSPARENT);//写文字的背景透明
	settextcolor(WHITE);//白字
	setfillcolor(page_color);//登录界面色
	setlinecolor(WHITE);//白线颜色
	fillrectangle(logon_page[0], logon_page[1], logon_page[2], logon_page[3]);//画登录框
	for (int i = 0; i < 4; i++)
	{
		fillrectangle(msg_to_RED_logon[i][0], msg_to_RED_logon[i][1], msg_to_RED_logon[i][2], msg_to_RED_logon[i][3]);
	}
	//画账户，密码，确认，忘记密码框
	setfillcolor(tips_color);//tips颜色
	fillrectangle(tips[0], tips[1], tips[2], tips[3]);//画tips框

	LOGFONT f;
	gettextstyle(&f);//暂存默认字体

	RECT text_name_tips = { logon_name[0],logon_name[1],logon_name[0] + 60,logon_name[3] };//提示“账户”
	RECT text_name = { logon_name[0] + 60,logon_name[1],logon_name[2],logon_name[3] };
	settextstyle(30, 10, "楷体");//改字体（修改长宽后记得改字体！！！！！）
	drawtext("账户  ", &text_name_tips, DT_CENTER);//提示“账户”

	RECT text_root_tips = { logon_root[0],logon_root[1],logon_root[0] + 60,logon_root[3] };//提示“密码”
	RECT text_root = { logon_root[0] + 60,logon_root[1],logon_root[2],logon_root[3] };
	drawtext("密码  ", &text_root_tips, DT_CENTER);//提示“密码”

	settextstyle(&f);//改回默认字体
	RECT text_ok = { logon_ok[0],logon_ok[1],logon_ok[2],logon_ok[3] };
	drawtext("确认", &text_ok, DT_CENTER);//提示"确认"

	RECT tip_text = { tips[0],tips[1],tips[2],tips[3] };
	settextstyle(30, 9, "楷体");//修改长宽后记得改字体！！！！！
	drawtext("tips:\n1.初次登陆即注册；\n2.设置账号，账号长度至多10位，仅支持数字、字母和符号；\n3.设置密码，密码应为12位，仅支持数字、字母和符号；\n4.忘记密码时可通过输入密保问题正确后会显示密码5秒.\n5禁止账户名test，否则程序崩溃后果自负。", &tip_text, DT_WORDBREAK);
	//显示提示

	RECT question_text = { logon_question[0],logon_question[1], logon_question[2], logon_question[3] };
	drawtext("忘记密码", &question_text, DT_WORDBREAK); //提示"忘记密码"

	//数据输入

	msg_state_former = -1;//!
	while (1)
	{
		MOUSEMSG msg;//鼠标变量
		msg = GetMouseMsg();//获取鼠标状态
		msg_to_RED(msg_to_RED_logon, 4, msg);//点亮
		int msg_t = msg_state;
		if (msg_state == 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(name, name_length + 1, "请输入用户名：");
			text_takeplace(name, &text_name, DT_CENTER, RGB(52, 66, 112));
			strcpy(file_name, name);
			strcat(file_name, ".txt");
		}
		//用户名输入
		else if (msg_state == 1 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(root, root_length + 1, "请输入密码：");
			text_takeplace(root, &text_root, DT_CENTER, RGB(52, 66, 112));
		}
		//输入密码
		else if (msg_state == 2 && msg.uMsg == WM_LBUTTONDOWN)
		{
			int logonok_answer = logonok();
			if (logonok_answer == 1)
			{
				closegraph();
				break;
			}
			//完成登录
			else if (logonok_answer == 2)
			{
				InputBox(question, 100, "请输入密保问题：");
				InputBox(answer, 100, "请输入密保问题答案：");
				fp = fopen(file_name, "a");
				fprintf(fp, "%s\n", question);
				fprintf(fp, "%s\n", answer);
				fclose(fp);
				closegraph();
				break;
			}
			//完成注册
		}
		//确认
		else if (msg_state == 3 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (strlen(name) == 0)
			{
				warning("请输入账户名", DT_CENTER);
			}
			//未输入账户名
			else
			{
				fp = fopen(file_name, "r");
				if (fp == NULL)	warning("账户名不存在", DT_CENTER);
				else
				{
					TCHAR root_true[root_length + 1];
					TCHAR question_true[question_length];
					TCHAR answer_true[answer_length];
					fscanf(fp, "%s\n", root_true);
					fscanf(fp, "%s\n", question_true);
					fscanf(fp, "%s\n", answer_true);
					warning(question_true, DT_CENTER);
					InputBox(answer, answer_length, "请输入密保问题答案：");
					if (strcmp(answer, answer_true) == 0)
					{
						warning(root_true, DT_CENTER);
						Sleep(1000);
					}
					//答案正确
					else warning("答案错误", DT_CENTER);
					fclose(fp);
				}
			}
		}
		//忘记密码
		msg_state_former = msg_t;
	}
}
//登录

void add()
{
	setbkcolor(base_color);//底图
	cleardevice();//清屏刷新
	setbkmode(TRANSPARENT);//写文字的背景透明
	setlinecolor(WHITE);//白线
	settextcolor(WHITE);//白字
	COLORREF add_page_color = page_color;
	setfillcolor(add_page_color);

	//数据准备
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
	//add各区域

	RECT add_text[8];
	for (int i = 0; i <= 7; i++)
	{
		add_text[i] = { add_choice[i][0], add_choice[i][1], add_choice[i][2], add_choice[i][3] };
		fillrectangle(add_choice[i][0], add_choice[i][1], add_choice[i][2], add_choice[i][3]);
	}
	//将各区域生成矩形

	drawtext("返回上级页面", &add_text[0], DT_LEFT);
	drawtext("年：", &add_text[1], DT_LEFT);
	drawtext("月：", &add_text[2], DT_LEFT);
	drawtext("日：", &add_text[3], DT_LEFT);
	drawtext("金额：", &add_text[4], DT_LEFT);
	drawtext("账单类型：", &add_text[5], DT_LEFT);
	drawtext("用途/来源：", &add_text[6], DT_LEFT);
	drawtext("确认", &add_text[7], DT_LEFT);
	//填充提示语

	add_text[4] = { add_choice[4][0] - 10, add_choice[4][1], add_choice[4][2] + 20, add_choice[4][3] };
	add_text[5] = { add_choice[5][0] + 30, add_choice[5][1], add_choice[5][2], add_choice[5][3] };
	add_text[6] = { add_choice[6][0] + 30, add_choice[6][1], add_choice[6][2], add_choice[6][3] };
	//微调提示语位置，使字可见

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
	//暂时填充新账单各属性

	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(add_choice, 8, msg);//获取鼠标状态并点亮
		int msg_t = msg_state;//!
		if (msg_state == 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			cleardevice();
			break;
		}
		//返回
		else if (msg_state == 1 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(year_new_text, 5, "请输入年:");
			text_takeplace(year_new_text, &add_text[1], DT_CENTER, add_page_color);
		}
		//年
		else if (msg_state == 2 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(month_new_text, 3, "请输入月:");
			text_takeplace(month_new_text, &add_text[2], DT_CENTER, add_page_color);
		}
		//月
		else if (msg_state == 3 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(day_new_text, 3, "请输入日:");
			text_takeplace(day_new_text, &add_text[3], DT_CENTER, add_page_color);
		}
		//日
		else if (msg_state == 4 && msg.uMsg == WM_LBUTTONDOWN)
		{
			InputBox(money_new_text, 6, "请输入金额:");
			text_takeplace(money_new_text, &add_text[4], DT_CENTER, add_page_color);
		}
		//金额
		else if (msg_state == 5 && msg.uMsg == WM_LBUTTONDOWN)
		{
			way_new = 1 - way_new;
			text_takeplace(wayway[way_new], &add_text[5], DT_CENTER, add_page_color);
			function_new = 0;
			if (way_new == 0)	text_takeplace(funct_in[function_new], &add_text[6], DT_CENTER, add_page_color);
			else text_takeplace(funct_out[function_new], &add_text[6], DT_CENTER, add_page_color);
		}
		//收支类型
		else if (msg_state == 6 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (way_new == 0)
			{
				function_new = (function_new + 1) % funct_in_num;
				text_takeplace(funct_in[function_new], &add_text[6], DT_CENTER, add_page_color);
			}
			//是收入类型
			else
			{
				function_new = (function_new + 1) % funct_out_num;
				text_takeplace(funct_out[function_new], &add_text[6], DT_CENTER, add_page_color);
			}
			//支出类型
		}
		//用途
		else if (msg_state == 7 && msg.uMsg == WM_LBUTTONDOWN)
		{
			fp = fopen(file_name, "a");
			fprintf(fp, "%d %d %d %d %d %d\n", atoi(year_new_text), atoi(month_new_text), atoi(day_new_text), atoi(money_new_text), way_new, function_new);
			fclose(fp);
			warning("添加成功！", DT_CENTER);
			cleardevice();
			break;
		}
		//确定添加
		msg_state_former = msg_t;//!
	}
}
//添加功能

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
//将输入的年月日提取出来

void show(RECT show_list_text[], int onepage_list_num, COLORREF show_color)
{

	struct chart* p_show = &p_chart;
	for (int i = 0; i <= onepage_list_num * show_page; i++)
	{
		p_show = p_show->next;
	}
	//将账单链表移动到要显示的前一条

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
	//显示在页面的属性必须是字符串，使用这些变量临时贮存

	int i = 0;//第几条
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
	//显示各账单
}
//将账单显示在查询页面

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
//清空总链表

void search_in_all()
{
	delete_p_chart();//清空总链表
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//序列号
	show_num_all = -1;//搜索后总账单数
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
	//搜索
	fclose(fp);
}
//所有账单存入p_chart
void search_in_year(int search_year)
{
	delete_p_chart();//清空总链表
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//序列号
	show_num_all = -1;//搜索后总账单数
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
	//搜索
	fclose(fp);
}
//特定年的账单存入p_chart
void search_in_month(int search_year, int search_month)
{
	delete_p_chart();//清空总链表
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//序列号
	show_num_all = -1;//搜索后总账单数
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
	//搜索
	fclose(fp);
}
//特定月的账单存入p_chart
void search_in_day(int search_year, int search_month, int search_day)
{
	delete_p_chart();//清空总链表
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//序列号
	show_num_all = -1;//搜索后总账单数
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
	//搜索
	fclose(fp);
}
//特定日的账单存入p_chart

void search_in_time()
{
	setbkcolor(base_color);//底图
	cleardevice();//清屏刷新
	setbkmode(TRANSPARENT);//写文字的背景透明
	setlinecolor(WHITE);//白线
	settextcolor(WHITE);//白字

	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;

	setfillcolor(show_color);

	//数据准备

	int show_title[4];
	show_title[0] = menu_page[0] / 4;
	show_title[1] = menu_page[1] * 29 / 88;
	show_title[2] = menu_page[0] * 3 / 4;
	show_title[3] = menu_page[1] * 33 / 88;
	RECT show_title_text[7];
	//提示标题

	int show_list[10][4];//10行账单
	for (int i = 0; i < 10; i++)
	{
		show_list[i][0] = menu_page[0] / 4;
		show_list[i][1] = menu_page[1] * (33 + 4 * i) / 88;
		show_list[i][2] = menu_page[0] * 3 / 4;
		show_list[i][3] = menu_page[1] * (37 + 4 * i) / 88;
		fillrectangle(show_list[i][0], show_list[i][1], show_list[i][2], show_list[i][3]);
	}
	//各账单位置

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
	//将各账单位置文字存入show_list_text

	int search_in_time_choice[8][4];//查询选择的小功能
	setfillcolor(choice_color);//修改填充色为功能键颜色

	RECT search_in_time_choice_text[8];
	search_in_time_choice[0][0] = 0;
	search_in_time_choice[0][1] = 0;
	search_in_time_choice[0][2] = menu_page[0] * 5 / 32;
	search_in_time_choice[0][3] = menu_page[1] / 32;
	search_in_time_choice_text[0] = { search_in_time_choice[0][0] ,search_in_time_choice[0][1] ,search_in_time_choice[0][2] ,search_in_time_choice[0][3] };
	fillrectangle(search_in_time_choice[0][0], search_in_time_choice[0][1], search_in_time_choice[0][2], search_in_time_choice[0][3]);
	//0 返回

	for (int i = 1; i <= 3; i++)
	{
		search_in_time_choice[i][0] = menu_page[0] * (1 + 2 * i) / 12;
		search_in_time_choice[i][1] = menu_page[1] / 8;
		search_in_time_choice[i][2] = menu_page[0] * (3 + 2 * i) / 12;
		search_in_time_choice[i][3] = menu_page[1] * 2 / 8;
		search_in_time_choice_text[i] = { search_in_time_choice[i][0] ,search_in_time_choice[i][1] ,search_in_time_choice[i][2] ,search_in_time_choice[i][3] };
		fillrectangle(search_in_time_choice[i][0], search_in_time_choice[i][1], search_in_time_choice[i][2], search_in_time_choice[i][3]);
	}
	//1年
	//2月
	//3日
	for (int i = 1; i <= 3; i++)
	{
		search_in_time_choice_text[i] = { search_in_time_choice[i][0] ,(search_in_time_choice[i][1] + search_in_time_choice[i][3]) / 2 - menu_page[1] / 64 ,search_in_time_choice[i][2] ,(search_in_time_choice[i][1] + search_in_time_choice[i][3]) / 2 + menu_page[1] / 64 };
	}
	//微调，字体居中
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
	//设置各功能键位置与文本位置

	show(show_list_text, 10, show_color);
	drawtext("返回上级页面", &search_in_time_choice_text[0], DT_CENTER);
	drawtext("按年查询", &search_in_time_choice_text[1], DT_CENTER);
	drawtext("按月查询", &search_in_time_choice_text[2], DT_CENTER);
	drawtext("按日查询", &search_in_time_choice_text[3], DT_CENTER);
	drawtext("上一页", &search_in_time_choice_text[4], DT_CENTER);
	drawtext("下一页", &search_in_time_choice_text[5], DT_CENTER);
	drawtext("首页", &search_in_time_choice_text[6], DT_CENTER);
	drawtext("尾页", &search_in_time_choice_text[7], DT_CENTER);
	//功能提示语

	drawtext("序列号", &show_title_text[0], DT_CENTER);
	drawtext("年", &show_title_text[1], DT_CENTER);
	drawtext("月", &show_title_text[2], DT_CENTER);
	drawtext("日", &show_title_text[3], DT_CENTER);
	drawtext("金额", &show_title_text[4], DT_CENTER);
	drawtext("收支类型", &show_title_text[5], DT_CENTER);
	drawtext("用途来源", &show_title_text[6], DT_CENTER);
	//标题

	search_in_all();
	show(show_list_text, 10, show_color);
	msg_state_former = -1;//!
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(search_in_time_choice, 8, msg);
		int msg_t = msg_state;//获取鼠标状态
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//返回
			else if (msg_state == 1)
			{
				InputBox(year_new_text, 5, "请输入年：");
				search_in_year(atoi(year_new_text));
			}
			//年
			else if (msg_state == 2)
			{
				TCHAR search_month[8];
				InputBox(search_month, 8, "请输入按2023.12格式输入月：");
				year_new = atoi(search_month);
				str_to_num(search_month);
				month_new = atoi(search_month);
				search_in_month(year_new, month_new);
			}
			//月
			else if (msg_state == 3)
			{
				TCHAR search_day[11];
				InputBox(search_day, 11, "请输入按2023.12.23格式输入日：");
				year_new = atoi(search_day);
				str_to_num(search_day);
				month_new = atoi(search_day);
				str_to_num(search_day);
				day_new = atoi(search_day);
				search_in_day(year_new, month_new, day_new);
			}
			//日
			if (show_num_all == -1 && msg_state >= 1)
			{
				warning("不存在", DT_CENTER);
				msg_state_former = msg_t;//!
				continue;
			}
			//不存在
			else
			{
				page_num_all = (show_num_all + 10) / 10 - 1;//刷新总页数
				if (page_num_all > 0)
				{
					if (msg_state == 4)
					{
						show_page = (show_page + 2 * page_num_all + 2 - 1) % (page_num_all + 1);
					}
					//下一页
					else if (msg_state == 5)
					{
						show_page = (show_page + 1) % (page_num_all + 1);
					}
					//上一页
					else if (msg_state == 6)
					{
						show_page = 0;
					}
					//首页
					else if (msg_state == 7)
					{
						show_page = page_num_all;
					}
					//尾页
				}
				else show_page = 0;
			}
			//根据页数，可寻找上下页，首尾页
			if (msg_state >= 1 && msg.uMsg == WM_LBUTTONDOWN)	show(show_list_text, 10, show_color);//显示
		}
		msg_state_former = msg_t;//!
	}
}
//按时间查询

void search_in_function_main(int search_function)
{
	delete_p_chart();//清空总链表
	fp = fopen(file_name, "r");
	fseek(fp, strlen(root) + 6 + strlen(question) + strlen(answer), SEEK_SET);
	int i = -1;//序列号
	show_num_all = -1;//搜索后总账单数
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
	//搜索
	fclose(fp);
}
void search_in_function()
{
	setbkcolor(base_color);//底图
	cleardevice();//清屏刷新
	setbkmode(TRANSPARENT);//写文字的背景透明
	setlinecolor(WHITE);//白线
	settextcolor(WHITE);//白字

	//数据准备
	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;

	setfillcolor(show_color);

	int show_title[4];
	show_title[0] = menu_page[0] / 4;
	show_title[1] = menu_page[1] * 29 / 88;
	show_title[2] = menu_page[0] * 3 / 4;
	show_title[3] = menu_page[1] * 33 / 88;
	RECT show_title_text[7];
	//提示标题

	int show_list[10][4];//10行账单
	for (int i = 0; i < 10; i++)
	{
		show_list[i][0] = menu_page[0] / 4;
		show_list[i][1] = menu_page[1] * (33 + 4 * i) / 88;
		show_list[i][2] = menu_page[0] * 3 / 4;
		show_list[i][3] = menu_page[1] * (37 + 4 * i) / 88;
		solidrectangle(show_list[i][0], show_list[i][1], show_list[i][2], show_list[i][3]);
	}
	//各账单位置

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
	//将各账单位置文字存入show_list_text

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
	//微调

	int search_in_function_choice[8][4];//查询选择的小功能
	setfillcolor(choice_color);//修改填充色为功能键颜色

	RECT search_in_function_choice_text[8];
	search_in_function_choice[0][0] = 0;
	search_in_function_choice[0][1] = 0;
	search_in_function_choice[0][2] = menu_page[0] * 5 / 32;
	search_in_function_choice[0][3] = menu_page[1] / 32;
	search_in_function_choice_text[0] = { search_in_function_choice[0][0] ,search_in_function_choice[0][1] ,search_in_function_choice[0][2] ,search_in_function_choice[0][3] };
	fillrectangle(search_in_function_choice[0][0], search_in_function_choice[0][1], search_in_function_choice[0][2], search_in_function_choice[0][3]);
	//0返回

	for (int i = 1; i <= 3; i++)
	{
		search_in_function_choice[i][0] = menu_page[0] * (1 + 2 * i) / 12;
		search_in_function_choice[i][1] = menu_page[1] / 8;
		search_in_function_choice[i][2] = menu_page[0] * (3 + 2 * i) / 12;
		search_in_function_choice[i][3] = menu_page[1] * 2 / 8;
		search_in_function_choice_text[i] = { search_in_function_choice[i][0] ,search_in_function_choice[i][1] ,search_in_function_choice[i][2] ,search_in_function_choice[i][3] };
		fillrectangle(search_in_function_choice[i][0], search_in_function_choice[i][1], search_in_function_choice[i][2], search_in_function_choice[i][3]);
	}
	//1收支类型
	//2用途
	//3确定
	for (int i = 1; i <= 3; i++)
	{
		search_in_function_choice_text[i] = { search_in_function_choice[i][0] ,(search_in_function_choice[i][1] + search_in_function_choice[i][3]) / 2 - menu_page[1] / 64 ,search_in_function_choice[i][2] ,(search_in_function_choice[i][1] + search_in_function_choice[i][3]) / 2 + menu_page[1] / 64 };
	}
	//微调，字体居中
	for (int i = 4; i <= 7; i++)
	{
		search_in_function_choice[i][0] = menu_page[0] * (i + 8) / 16;
		search_in_function_choice[i][1] = menu_page[1] * 7 / 8;
		search_in_function_choice[i][2] = menu_page[0] * (i + 9) / 16;
		search_in_function_choice[i][3] = menu_page[1] * 29 / 32;
		search_in_function_choice_text[i] = { search_in_function_choice[i][0] ,search_in_function_choice[i][1] ,search_in_function_choice[i][2] ,search_in_function_choice[i][3] };
		fillrectangle(search_in_function_choice[i][0], search_in_function_choice[i][1], search_in_function_choice[i][2], search_in_function_choice[i][3]);
	}
	//4上一页
	//5下一页
	//6首页
	// 7尾页
	//设置各功能键位置与文本位置

	drawtext("返回上级页面", &search_in_function_choice_text[0], DT_CENTER);
	drawtext(wayway[0], &search_in_function_choice_text[1], DT_CENTER);
	drawtext(funct_in[0], &search_in_function_choice_text[2], DT_CENTER);
	drawtext("确定", &search_in_function_choice_text[3], DT_CENTER);
	drawtext("上一页", &search_in_function_choice_text[4], DT_CENTER);
	drawtext("下一页", &search_in_function_choice_text[5], DT_CENTER);
	drawtext("首页", &search_in_function_choice_text[6], DT_CENTER);
	drawtext("尾页", &search_in_function_choice_text[7], DT_CENTER);
	//功能提示语

	drawtext("序列号", &show_title_text[0], DT_CENTER);
	drawtext("年", &show_title_text[1], DT_CENTER);
	drawtext("月", &show_title_text[2], DT_CENTER);
	drawtext("日", &show_title_text[3], DT_CENTER);
	drawtext("金额", &show_title_text[4], DT_CENTER);
	drawtext("收支类型", &show_title_text[5], DT_CENTER);
	drawtext("用途来源", &show_title_text[6], DT_CENTER);
	//标题

	way_new = 0;
	function_new = 0;
	//暂时存状态

	search_in_all();
	show(show_list_text, 10, show_color);
	msg_state_former = -1;//!
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(search_in_function_choice, 8, msg);
		int msg_t = msg_state;//获取鼠标状态
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//返回
			else if (msg_state == 1)
			{
				way_new = 1 - way_new;
				text_takeplace(wayway[way_new], &search_in_function_choice_text[1], DT_CENTER, choice_color);
				function_new = 0;
				if (way_new == 0)	text_takeplace(funct_in[function_new], &search_in_function_choice_text[2], DT_CENTER, choice_color);
				else text_takeplace(funct_out[function_new], &search_in_function_choice_text[2], DT_CENTER, choice_color);
			}
			//修改要查找的收支类型
			else if (msg_state == 2)
			{
				if (way_new == 0)
				{
					function_new = (function_new + 1) % funct_in_num;
					text_takeplace(funct_in[function_new], &search_in_function_choice_text[2], DT_CENTER, choice_color);
				}
				//收入类型
				else
				{
					function_new = (function_new + 1) % funct_out_num;
					text_takeplace(funct_out[function_new], &search_in_function_choice_text[2], DT_CENTER, choice_color);
				}
				//支出类型
			}
			//修改要查找的用途
			if (show_num_all == -1 && msg_state >= 3)
			{
				warning("不存在", DT_CENTER);
				msg_state_former = msg_t;//!
				continue;
			}
			//不存在
			else
			{
				page_num_all = (show_num_all + 10) / 10 - 1;//刷新总页数
				if (page_num_all > 0)
				{
					if (msg_state == 4)
					{
						show_page = (show_page + 2 * page_num_all + 2 - 1) % (page_num_all + 1);
					}
					//下一页
					else if (msg_state == 5)
					{
						show_page = (show_page + 1) % (page_num_all + 1);
					}
					//上一页
					else if (msg_state == 6)
					{
						show_page = 0;
					}
					//首页
					else if (msg_state == 7)
					{
						show_page = page_num_all;
					}
					//尾页
				}
				else show_page = 0;
			}
			//根据页数，可寻找上下页，首尾页
			if (msg_state >= 3)	show(show_list_text, 10, show_color);//显示
		}
		msg_state_former = msg_t;//!
	}
}
//按功能查询

void search()
{
BB:setbkcolor(base_color);//底图
	cleardevice();//清屏刷新
	setbkmode(TRANSPARENT);//写文字的背景透明
	setlinecolor(WHITE);//白线
	settextcolor(WHITE);//白字

	int search_choice[4][4];

	//数据准备
	search_choice[0][0] = 0;
	search_choice[0][1] = 0;
	search_choice[0][2] = menu_page[0] * 5 / 32;
	search_choice[0][3] = menu_page[1] / 32;

	search_choice[3][0] = menu_page[0] / 4;
	search_choice[3][1] = menu_page[1] / 4;
	search_choice[3][2] = menu_page[0] * 3 / 4;
	search_choice[3][3] = menu_page[1] * 5 / 12;//不可点亮处

	search_choice[1][0] = menu_page[0] / 4;
	search_choice[1][1] = menu_page[1] * 5 / 12;
	search_choice[1][2] = menu_page[0] * 3 / 4;
	search_choice[1][3] = menu_page[1] * 7 / 12;

	search_choice[2][0] = menu_page[0] / 4;
	search_choice[2][1] = menu_page[1] * 7 / 12;
	search_choice[2][2] = menu_page[0] * 3 / 4;
	search_choice[2][3] = menu_page[1] * 3 / 4;
	//选择功能键位置

	RECT search_msg_to_RED[4];
	setfillcolor(page_color);
	settextcolor(WHITE);
	for (int i = 0; i <= 3; i++)
	{
		search_msg_to_RED[i] = { search_choice[i][0],search_choice[i][1], search_choice[i][2], search_choice[i][3] };
		fillrectangle(search_choice[i][0], search_choice[i][1], search_choice[i][2], search_choice[i][3]);
	}
	//可点亮的矩形

	RECT search_choice_text[3];
	for (int i = 0; i < 3; i++)
	{
		search_choice_text[i] = { search_choice[i + 1][0],(search_choice[i + 1][1] + search_choice[i + 1][3]) / 2 - menu_page[1] / 32,search_choice[i + 1][2],search_choice[i + 1][1] + search_choice[i + 1][3] + menu_page[1] / 32 };
	}
	drawtext("返回上级页面 ", &search_msg_to_RED[0], DT_CENTER);
	drawtext("按时间查询", &search_choice_text[0], DT_CENTER);
	drawtext("按类目查询 ", &search_choice_text[1], DT_CENTER);
	drawtext("选择查询方式", &search_choice_text[2], DT_CENTER);
	//填充提示语
	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(search_choice, 3, msg);
		int msg_t = msg_state;//获取鼠标状态
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			cleardevice();
			if (msg_state == 0)	return;//返回
			else if (msg_state == 1)	search_in_time();//按时间查询
			else if (msg_state == 2)	search_in_function();//按功能查询
			break;
		}
		msg_state_former = msg_t;//!
	}
	goto BB;
}
//查询功能

void change()
{

	setbkcolor(base_color);//底图
	cleardevice();//清屏刷新
	setbkmode(TRANSPARENT);//写文字的背景透明
	setlinecolor(WHITE);//白线
	settextcolor(WHITE);//白字

	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;
	setfillcolor(choice_color);

	int change_choice[10][4];

	//数据准备
	change_choice[0][0] = 0;
	change_choice[0][1] = 0;
	change_choice[0][2] = menu_page[0] * 5 / 32;
	change_choice[0][3] = menu_page[1] / 32;//返回

	change_choice[1][0] = menu_page[0] / 4;
	change_choice[1][1] = menu_page[1] / 12;
	change_choice[1][2] = menu_page[0] * 3 / 8;
	change_choice[1][3] = menu_page[1] * 2 / 12;//修改键

	change_choice[2][0] = menu_page[0] / 2;
	change_choice[2][1] = menu_page[1] / 12;
	change_choice[2][2] = menu_page[0] * 5 / 8;
	change_choice[2][3] = menu_page[1] * 2 / 12;//删除键

	change_choice[3][0] = menu_page[0] / 2 - 20;
	change_choice[3][1] = menu_page[1] * 10 / 12;
	change_choice[3][2] = menu_page[0] / 2 + 20;
	change_choice[3][3] = menu_page[1] * 11 / 12;//确认

	change_choice[7][0] = menu_page[0] / 4;
	change_choice[7][1] = menu_page[1] * 5 / 12;
	change_choice[7][2] = menu_page[0] * 3 / 4;
	change_choice[7][3] = menu_page[1] * 7 / 12;//金额

	change_choice[8][0] = menu_page[0] / 4;
	change_choice[8][1] = menu_page[1] * 7 / 12;
	change_choice[8][2] = menu_page[0] / 2;
	change_choice[8][3] = menu_page[1] * 3 / 4;//账单类型

	change_choice[9][0] = menu_page[0] / 2;
	change_choice[9][1] = menu_page[1] * 7 / 12;
	change_choice[9][2] = menu_page[0] * 3 / 4;
	change_choice[9][3] = menu_page[1] * 3 / 4;//用途/来源



	change_choice[4][0] = menu_page[0] / 4;
	change_choice[4][1] = menu_page[1] / 4;
	change_choice[4][2] = menu_page[0] * 5 / 12;
	change_choice[4][3] = menu_page[1] * 5 / 12;//年

	change_choice[5][0] = menu_page[0] * 5 / 12;
	change_choice[5][1] = menu_page[1] / 4;
	change_choice[5][2] = menu_page[0] * 7 / 12;
	change_choice[5][3] = menu_page[1] * 5 / 12;//月

	change_choice[6][0] = menu_page[0] * 7 / 12;
	change_choice[6][1] = menu_page[1] / 4;
	change_choice[6][2] = menu_page[0] * 3 / 4;
	change_choice[6][3] = menu_page[1] * 5 / 12;//日


	RECT change_text[10];
	for (int i = 3; i < 10; i++)
	{
		change_text[i] = { change_choice[i][0], change_choice[i][1], change_choice[i][2], change_choice[i][3] };
	}
	change_text[0] = { change_choice[0][0], change_choice[0][1], change_choice[0][2], change_choice[0][3] };
	change_text[1] = { (change_choice[1][0] + change_choice[1][2]) / 2 - 20,(change_choice[1][1] + change_choice[1][3]) / 2 - 20,(change_choice[1][0] + change_choice[1][2]) / 2 + 20, (change_choice[1][1] + change_choice[1][3]) / 2 + 20 };
	change_text[2] = { (change_choice[2][0] + change_choice[2][2]) / 2 - 20,(change_choice[2][1] + change_choice[2][3]) / 2 - 20,(change_choice[2][0] + change_choice[2][2]) / 2 + 20, (change_choice[2][1] + change_choice[2][3]) / 2 + 20 };
	//文本提示区域
	for (int i = 0; i < 10; i++)
	{
		fillrectangle(change_choice[i][0], change_choice[i][1], change_choice[i][2], change_choice[i][3]);
	}

	drawtext("返回上级页面", &change_text[0], DT_LEFT);
	drawtext("修改", &change_text[1], DT_LEFT);
	drawtext("删除", &change_text[2], DT_LEFT);
	drawtext("确认", &change_text[3], DT_LEFT);
	drawtext("年：", &change_text[4], DT_LEFT);
	drawtext("月：", &change_text[5], DT_LEFT);
	drawtext("日：", &change_text[6], DT_LEFT);
	drawtext("金额：", &change_text[7], DT_LEFT);
	drawtext("账单类型：", &change_text[8], DT_LEFT);
	drawtext("用途/来源：", &change_text[9], DT_LEFT);
	//功能提示语

	TCHAR num_delete[5] = "";
	TCHAR num_change[5] = "";

	text_takeplace(wayway[way_new], &change_text[8], DT_CENTER, choice_color);
	if (way_new == 0)  text_takeplace(funct_in[function_new], &change_text[9], DT_CENTER, choice_color);
	//收入类型
	else  text_takeplace(funct_out[function_new], &change_text[9], DT_CENTER, choice_color);
	//支出类型

	int change_state = 0;//0未选择状态，2选择修改
	int way_new2 = 0;
	int function_new2 = 0;

	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(change_choice, 10, msg);
		int msg_t = msg_state;//获取鼠标状态
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//返回
			else if (msg_state == 1 && change_state == 0)
			{
				change_state = 2;
				InputBox(num_change, 5, "请输入要修改的序列号：");
			}
			//输入修改单号
			else if (msg_state == 2)
			{
				InputBox(num_delete, 5, "请输入要删除的序列号：");
				int num_delete_atoi = atoi(num_delete);
				search_in_all();
				if (show_num_all < num_delete_atoi)
				{
					warning("该序列号不存在", DT_CENTER);
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
			//删除
			else if (msg_state >= 3 && change_state == 2)
			{
				if (msg_state == 3)
				{
					int num_change_atoi = atoi(num_change);
					search_in_all();
					if (show_num_all < num_change_atoi)
					{
						warning("该序列号不存在", DT_CENTER);
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
				//确认
				else if (msg_state == 4)
				{
					InputBox(year_new_text, 5, "请输入年:");
					text_takeplace(year_new_text, &change_text[4], DT_CENTER, choice_color);
				}
				//年
				else if (msg_state == 5)
				{
					InputBox(month_new_text, 3, "请输入月:");
					text_takeplace(month_new_text, &change_text[5], DT_CENTER, choice_color);
				}
				//月
				else if (msg_state == 6)
				{
					InputBox(day_new_text, 3, "请输入日:");
					text_takeplace(day_new_text, &change_text[6], DT_CENTER, choice_color);
				}
				//日
				if (msg_state == 7)
				{
					InputBox(money_new_text, 5, "请输入金额:");
					text_takeplace(money_new_text, &change_text[7], DT_CENTER, choice_color);
				}
				//金额
				else if (msg_state == 8)
				{
					way_new2 = 1 - way_new2;
					text_takeplace(wayway[way_new2], &change_text[8], DT_CENTER, choice_color);
					function_new2 = 0;
					if (way_new2 == 0)	text_takeplace(funct_in[function_new2], &change_text[9], DT_CENTER, choice_color);
					else text_takeplace(funct_out[function_new2], &change_text[9], DT_CENTER, choice_color);
				}
				//修改要查找的收支类型
				else if (msg_state == 9)
				{
					if (way_new2 == 0)
					{
						function_new2 = (function_new2 + 1) % funct_in_num;
						text_takeplace(funct_in[function_new2], &change_text[9], DT_CENTER, choice_color);
					}
					//收入类型
					else
					{
						function_new2 = (function_new2 + 1) % funct_out_num;
						text_takeplace(funct_out[function_new2], &change_text[9], DT_CENTER, choice_color);
					}
					//支出类型
				}
				//修改要查找的用途
			}
			//修改属性
		}
		msg_state_former = msg_t;//!
	}

}
//修改功能

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
	//将年份账单存入
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
	//根据模式修改排序
	for (int i = 0; i < 12; i++)
	{
		text_takeplace(itoa(sum_in_month[i][0], sum_in_money, 10), &summary_show_text[4 * i + 1], DT_CENTER, page_color);
		text_takeplace(itoa(sum_in_month[i][1], sum_out_money, 10), &summary_show_text[4 * i + 2], DT_CENTER, page_color);
		text_takeplace(itoa(sum_in_month[i][2], sum_in_and_out_money, 10), &summary_show_text[4 * i + 3], DT_CENTER, page_color);
		text_takeplace(itoa(sum_in_month[i][3], sum_month, 10), &summary_show_text[4 * i], DT_CENTER, page_color);
	}
	//计算结余
}
void summary()
{
	setbkcolor(base_color);//底图
	cleardevice();//清屏刷新
	setbkmode(TRANSPARENT);//写文字的背景透明
	setlinecolor(WHITE);//白线
	settextcolor(WHITE);//白字

	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;

	setfillcolor(show_color);

	//数据准备
	int summary_choice[5][4];
	summary_choice[0][0] = 0;
	summary_choice[0][1] = 0;
	summary_choice[0][2] = menu_page[0] / 8;
	summary_choice[0][3] = menu_page[1] / 32;//退出

	summary_choice[1][0] = menu_page[0] / 4;
	summary_choice[1][1] = menu_page[1] / 16;
	summary_choice[1][2] = menu_page[0] * 9 / 32;
	summary_choice[1][3] = menu_page[1] * 2 / 16;//《《

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
	summary_choice[4][3] = menu_page[1] / 32;//换模式

	RECT summary_choice_text[5];
	for (int i = 0; i < 5; i++)
	{
		summary_choice_text[i] = { summary_choice[i][0],summary_choice[i][1], summary_choice[i][2], summary_choice[i][3] };
		fillrectangle(summary_choice[i][0], summary_choice[i][1], summary_choice[i][2], summary_choice[i][3]);
	}
	//设置文本框

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

	TCHAR summary_state_text[2][20] = { "按时间排序","按结余排序" };
	int summary_state = 0;

	TCHAR summary_year[5] = "2023";
	InputBox(summary_year, 5, "请输入总结年份：");

	drawtext("月份", &summary_show_title_text[0], DT_CENTER);
	drawtext("收入", &summary_show_title_text[1], DT_CENTER);
	drawtext("支出", &summary_show_title_text[2], DT_CENTER);
	drawtext("结余", &summary_show_title_text[3], DT_CENTER);
	summary_to_show(sum_in_month, atoi(summary_year), summary_state, summary_show_text);

	drawtext("返回上级页面", &summary_choice_text[0], DT_CENTER);
	drawtext("<<", &summary_choice_text[1], DT_CENTER);
	drawtext(summary_year, &summary_choice_text[2], DT_CENTER);
	drawtext(">>", &summary_choice_text[3], DT_CENTER);
	drawtext(summary_state_text[summary_state], &summary_choice_text[4], DT_CENTER);
	//功能提示语
	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(summary__choice_to_RED, 4, msg);//获取鼠标状态
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//返回
			else
			{
				if (msg_state == 3)
				{
					summary_state = 1 - summary_state;
					text_takeplace(summary_state_text[summary_state], &summary_choice_text[4], DT_CENTER, show_color);
				}
				//修改模式
				else if (msg_state == 1)
				{
					itoa(atoi(summary_year) - 1, summary_year, 10);
					text_takeplace(summary_year, &summary_choice_text[2], DT_CENTER, show_color);
				}
				//年份-1
				else if (msg_state == 2 && msg.uMsg)
				{
					itoa(atoi(summary_year) + 1, summary_year, 10);
					text_takeplace(summary_year, &summary_choice_text[2], DT_CENTER, show_color);
				}
				//年份+1
				summary_to_show(sum_in_month, atoi(summary_year), summary_state, summary_show_text);
				//显示
			}
		}
		msg_state_former = msg_state;
	}
}
//总结功能

// 定义运算符优先级
int getPriority(char op) {
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}

// 执行二元运算
int applyOp(int a, int b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	}
	return 0; // 在无效的运算符情况下返回一个默认值
}

// 计算表达式的值
int calculateExpression(char* expression) {
	int numStack[100] = { 0 }; // 数字栈
	char opStack[100] = { 0 }; // 运算符栈
	int numTop = -1;
	int opTop = -1;

	for (int i = 0; expression[i] != '\0'; i++) {
		if (expression[i] == ' ')
			continue;

		if (expression[i] >= '0' && expression[i] <= '9') {
			// 处理数字
			int num = 0;
			while (expression[i] >= '0' && expression[i] <= '9') {
				num = num * 10 + (expression[i] - '0');
				i++;
			}
			i--;

			numStack[++numTop] = num;
		}
		else if (expression[i] == '(') {
			// 处理左括号
			opStack[++opTop] = '(';
		}
		else if (expression[i] == ')') {
			// 处理右括号
			while (opTop != -1 && opStack[opTop] != '(') {
				int b = numStack[numTop--];
				int a = numStack[numTop--];
				char op = opStack[opTop--];
				numStack[++numTop] = applyOp(a, b, op);
			}
			// 弹出左括号
			if (opTop != -1 && opStack[opTop] == '(') {
				opTop--;
			}
		}
		else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
			// 处理运算符
			while (opTop != -1 && getPriority(opStack[opTop]) >= getPriority(expression[i]) && numTop >= 1) {
				int b = numStack[numTop--];
				int a = numStack[numTop--];
				char op = opStack[opTop--];
				numStack[++numTop] = applyOp(a, b, op);
			}
			// 添加运算符到opStack
			opStack[++opTop] = expression[i];
		}
	}

	// 处理剩余的运算符
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
	setbkcolor(base_color);//底图
	cleardevice();
	setbkmode(TRANSPARENT);//写文字的背景透明
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

	text_takeplace("返回上级页面", &caculater_choice_text[0], DT_CENTER, page_color);
	text_takeplace("开始计算:", &caculater_choice_text[1], DT_CENTER, page_color);

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
				InputBox(caculater_test, 100, "请输入计算式:");
				caculater_answer = do_caculater(caculater_test);
				text_takeplace("结果为：", &caculater_choice_text[2], DT_LEFT, page_color);
				text_takeplace(itoa(caculater_answer, caculater_test, 10), &caculater_choice_text[2], DT_CENTER, page_color);
			}
		}
		msg_state_former = msg_state;
	}
}
//计算器功能


void information()
{
	setbkcolor(base_color);//底图
	cleardevice();//清屏刷新
	setbkmode(TRANSPARENT);//写文字的背景透明
	setlinecolor(WHITE);//白线
	settextcolor(WHITE);//白字

	COLORREF show_color = tips_color;
	COLORREF choice_color = page_color;
	setfillcolor(page_color);

	//数据准备
	TCHAR root_test[root_length + 1];
	InputBox(root_test, root_length + 1, "请输入账户密码");
	if (strcmp(root_test, root) != 0)
	{
		warning("密码错误", DT_CENTER);
		cleardevice();
		return;
	}
	//输入密码验证是否可修改
	int information_choice[6][4];

	information_choice[0][0] = 0;
	information_choice[0][1] = 0;
	information_choice[0][2] = menu_page[0] * 5 / 32;
	information_choice[0][3] = menu_page[1] / 32;//返回键

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
	information_choice[5][3] = menu_page[1] * (3 + 2 * 4) / 12 + 10;//确认键

	RECT information_choice_text[6];
	for (int i = 0; i < 6; i++)
	{
		information_choice_text[i] = { information_choice[i][0] ,information_choice[i][1] ,information_choice[i][2] ,information_choice[i][3] };
		fillrectangle(information_choice[i][0], information_choice[i][1], information_choice[i][2], information_choice[i][3]);

	}

	drawtext("返回上级页面", &information_choice_text[0], DT_LEFT);
	drawtext("账户名", &information_choice_text[1], DT_LEFT);
	drawtext("账户密码", &information_choice_text[2], DT_LEFT);
	drawtext("密保问题", &information_choice_text[3], DT_LEFT);
	drawtext("密保问题答案", &information_choice_text[4], DT_LEFT);
	drawtext("确认", &information_choice_text[5], DT_LEFT);
	//提示语

	drawtext(name, &information_choice_text[1], DT_CENTER);
	drawtext(root, &information_choice_text[2], DT_CENTER);
	drawtext(question, &information_choice_text[3], DT_CENTER);
	drawtext(answer, &information_choice_text[4], DT_CENTER);

	TCHAR name_new[name_length + 1] = "";//账户名
	TCHAR root_new[root_length + 1] = "";//账户密码
	TCHAR question_new[question_length] = "";//贮存密保问题
	TCHAR answer_new[answer_length] = "";//贮存贮存密保问题答案

	strcpy(name_new, name);
	strcpy(root_new, root);
	strcpy(question_new, question);
	strcpy(answer_new, answer);
	//临时
	msg_state_former = -1;//!
	while (1)
	{

		MOUSEMSG msg;
		msg = GetMouseMsg();
		msg_to_RED(information_choice, 6, msg);//获取鼠标状态
		if (msg_state >= 0 && msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg_state == 0)
			{
				cleardevice();
				break;
			}
			//返回
			else if (msg_state == 1)
			{
				InputBox(name_new, name_length, "请输入改后账户名");
				text_takeplace(name_new, &information_choice_text[1], DT_CENTER, page_color);
			}
			//账户名
			else if (msg_state == 2)
			{
				InputBox(root_new, root_length, "请输入改后密码");
				text_takeplace(name, &information_choice_text[2], DT_CENTER, page_color);
			}
			//密码
			else if (msg_state == 3)
			{
				InputBox(question_new, question_length, "请输入改后密保问题");
				text_takeplace(question_new, &information_choice_text[3], DT_CENTER, page_color);
			}
			//密保问题
			else if (msg_state == 4)
			{
				InputBox(answer_new, answer_length, "请输入改后密保问题答案");
				text_takeplace(answer_new, &information_choice_text[4], DT_CENTER, page_color);
			}
			//答案
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
			//确认
		}
		msg_state_former = msg_state;
	}
}
//账户信息功能


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
	//刷新总收支
	fclose(fp);
}
//刷新总收支
void menu()
{
	initgraph(menu_page[0], menu_page[1]);

	//数据准备
	int menu[7][4];
	for (int i = 0; i <= 6; i++)
	{
		menu[i][0] = menu_page[0] * 3 / 8;
		menu[i][1] = menu_page[1] * (7 + i * 2) / 28;
		menu[i][2] = menu_page[0] * 5 / 8;
		menu[i][3] = menu_page[1] * (9 + i * 2) / 28;
	}
	//功能面板

	int in_and_out[3][4];
	for (int i = 0; i <= 2; i++)
	{
		in_and_out[i][0] = menu_page[0] * i / 3;
		in_and_out[i][1] = 0;
		in_and_out[i][2] = menu_page[0] * (i + 1) / 3;
		in_and_out[i][3] = menu_page[1] / 32;
	}
	//收支面板

	//页面设计
AA:setbkcolor(base_color);//底图
	cleardevice();
	setbkmode(TRANSPARENT);//写文字的背景透明
	settextcolor(WHITE);
	setfillcolor(page_color);//功能键色
	setlinecolor(WHITE);//线颜色


	RECT in_and_out_text[3];
	for (int i = 0; i <= 2; i++)
	{
		in_and_out_text[i] = { in_and_out[i][0],in_and_out[i][1],in_and_out[i][2],in_and_out[i][3] };
		fillrectangle(in_and_out[i][0], in_and_out[i][1], in_and_out[i][2], in_and_out[i][3]);
	}
	//画收支面板

	sum_in_and_sum_out();//更新收支
	fillrectangle(in_and_out[0][0], in_and_out[0][1], in_and_out[2][2], in_and_out[2][3]);
	text_takeplace("结余：", &in_and_out_text[0], DT_LEFT, page_color);
	line(in_and_out[0][0], in_and_out[0][3], in_and_out[0][2], in_and_out[0][3]);
	text_takeplace(itoa(sum, SUM, 10), &in_and_out_text[0], DT_CENTER, page_color);
	text_takeplace("收入：", &in_and_out_text[1], DT_LEFT, page_color);
	text_takeplace(itoa(sum_in_all, SUM_IN, 10), &in_and_out_text[1], DT_CENTER, page_color);
	text_takeplace("支出：", &in_and_out_text[2], DT_LEFT, page_color);
	text_takeplace(itoa(sum_out_all, SUM_OUT, 10), &in_and_out_text[2], DT_CENTER, page_color);
	//更新收支面板

	RECT menu_text[7];
	for (int i = 0; i <= 6; i++)
	{
		menu_text[i] = { menu[i][0], menu[i][1], menu[i][2], menu[i][3] };
		fillrectangle(menu[i][0], menu[i][1], menu[i][2], menu[i][3]);
	}
	//划线并生成对应矩形变量
	text_takeplace("添加收支记录", &menu_text[0], DT_CENTER, page_color);
	text_takeplace("查询收支记录", &menu_text[1], DT_CENTER, page_color);
	text_takeplace("修改收支记录", &menu_text[2], DT_CENTER, page_color);
	text_takeplace("账单总结", &menu_text[3], DT_CENTER, page_color);
	text_takeplace("计算器", &menu_text[4], DT_CENTER, page_color);
	text_takeplace("账户信息", &menu_text[5], DT_CENTER, page_color);
	text_takeplace("退出系统", &menu_text[6], DT_CENTER, page_color);
	//填充功能提示

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
			//退出
			break;
		}
		//选择功能
		msg_state_former = msg_t;//!
	}
	goto AA;
}
//主菜单
int main()
{
	logon();
	menu();
	return 0;
}