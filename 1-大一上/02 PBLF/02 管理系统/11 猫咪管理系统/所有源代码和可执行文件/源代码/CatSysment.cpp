#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<graphics.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>//用到了定时函数sleep()
#include <math.h>
#include<string>

#define MAX_PEOPLE 1000
#define MAX_PERSONAL 20
#define code_account "shaheye"
#define PASSWORD "666"


//初始化
typedef struct Date
{
    int year;
    int month;
    int day;
} Date_t;
typedef struct Cat
{
    char name[10];
    int age;
    char type[10];
    Date_t date;
    int condition;//1--被领养  2---未领养
    char gender;
} Cat_t;
typedef struct node
{
    Cat_t data;
    struct node* next;
}CatList;
struct Personal
{
    char account[30];
    char password[30];
};

using namespace std;
int num = 0;
struct Personal personals[MAX_PERSONAL];
struct Personal personals_temp[MAX_PERSONAL];
int personal_num = 0;

//申明函数
int login();
void add_Code();
void user_manage();
void admin_manage();
void guess_mamage();

void Initialize(CatList** L);
void creat(const char* cats, CatList** head);
void save(CatList* L);
int compare(struct Date date1, struct Date date2);

void cat_inquire(CatList* pt);
void cat_inquire_all(CatList* head);
void cat_inquire_name(CatList* pt);
void cat_inquire_type(CatList* pt);
void cat_inquire_gender(CatList* pt);
void cat_inquire_condition(CatList* pt);
void cat_inquire_age(CatList* pt);
void cat_inquire_date(CatList* pt);
void cat_sort_age(CatList** pt);
void Cat_age_sort1(CatList** pt);
void Cat_age_sort2(CatList** pt);
void cat_sort_date(CatList* pt);
void Cat_date_sort1(CatList* pt);
void Cat_date_sort2(CatList* pt);

void cat_information_changing(CatList** L);
void cat_interp(CatList** L);
void cat_delete(CatList** L);

int main()
{
    
    //登录
    int flag_login = login();
    if(flag_login == 1){
        admin_manage();
    }else if(flag_login == 0){
        guess_mamage();
    }
    return 0;
}

int login() {
    struct Personal Code;
    char zhanghao[30];
    char code[30];
    int j;
    int k = 3;
    char k_str[100];

    initgraph(800, 600, 0);
    SetWindowText(GetHWnd(), "登录界面");

    denglu:
    FILE* fp = fopen("users.txt", "r");
    int i = 0;
    if (fp == NULL)
    {
        printf("文件夹打开失败！\n");
    }
    else
    {
        while (feof(fp) == 0)
        {
            fscanf(fp, "%s %s\n", personals[i].account, personals[i].password);
            personal_num++;
            i++;
        }
    }
    fclose(fp);
    printf("用户读取成功！\n");

    //return 1;

    cleardevice();
    IMAGE img;
    loadimage(&img, "./image/backimage.jpg",800,600);
    putimage(0,0, &img);
    setcolor(BLACK);
    //绘制文字
    //设置颜色
    settextcolor(BLACK);//画板里的三原色数据
    //设置文字样式，大小，字体
    settextstyle(30, 0, "黑体");
    //设置背景模式  tran sparent 透明
    setbkmode(TRANSPARENT);
    fillrectangle(300,250,500,300);
    fillrectangle(300,300,500,350);
    outtextxy(370,260,"登录");
    outtextxy(370,310,"注册");
    
    while (1)  // 不断地处理事务，需要循环
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            //判断鼠标是否在矩形中
            //若放在wm_lbuttondown这种，就点击再输出
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 300 && msg.x < 500 && msg.y>250 && msg.y < 300)
                {
                    login_index:
                    cleardevice();
                    IMAGE img;
                    loadimage(&img, "./image/backimage.jpg", 800, 600);
                    putimage(0, 0, &img);
                    fillroundrect(350, 200, 500, 240, 5, 5);//账户白框
                    fillroundrect(350, 280, 500, 320, 5, 5);//密码白框
                    settextstyle(30, 0, "黑体");
                    outtextxy(280, 205, "账号");
                    outtextxy(280, 285, "密码");
                    fillroundrect(370, 400, 430, 430, 5, 5);//确认键白框
                    settextstyle(20, 0, "黑体");
                    outtextxy(380, 405, "确认");
                    settextstyle(50, 0, "黑体");
                    outtextxy(360, 100, "登录");

                    sprintf(k_str,"您还有%d次机会输入您的账号与密码！",k);
                    settextstyle(15, 0, "黑体");
                    outtextxy(280,450, k_str);
                    //鼠标信息
                    while (1)  // 不断地处理事务，需要循环
                    {
                        if (MouseHit())
                        {
                            msg = GetMouseMsg();
                            if (msg.uMsg == WM_LBUTTONDOWN)
                            {
                                if (msg.x > 350 && msg.x < 500 && msg.y>200 && msg.y < 240)
                                {
                                    printf("鼠标在账户框里\n");
                                    InputBox(zhanghao, 30, "请输入账户");
                                    settextstyle(30, 0, "黑体");
                                    outtextxy(350, 205, zhanghao);
                                }
                                else if (msg.x > 350 && msg.x < 500 && msg.y>280 && msg.y < 320)
                                {
                                    printf("鼠标在密码框里\n");
                                    InputBox(code, 30, "请输入密码");
                                    settextstyle(30, 0, "黑体");
                                    outtextxy(350, 285, code);
                                }
                                else if (msg.x > 370 && msg.x < 430 && msg.y>400 && msg.y < 430)
                                {

                                    printf("点击确认键");
                                    //执行比对函数
                                    k--;
                                    for (j = personal_num; j >= 0; j--)
                                    {
                                        Code = personals[j];
                                        if ((strcmp(Code.account, zhanghao) == 0 && strcmp(Code.password, code) == 0) || (strcmp(code_account, zhanghao) == 0 && strcmp(PASSWORD, code) == 0))
                                        {
                                            if (strcmp(code_account, zhanghao) == 0 && strcmp(PASSWORD, code) == 0) {
                                                printf("管理员登录成功！\n");
                                                return 1;
                                            }
                                            else if (strcmp(Code.account, zhanghao) == 0 && strcmp(Code.password, code) == 0)
                                            {
                                                printf("用户登录成功！\n");
                                                return 0;
                                            }
                                        }
                                    }
                                    if (k==0) {
                                        HWND hnd = GetHWnd();
                                        MessageBox(hnd, "账号或密码输入错误多次，自动退出系统！", "提示", MB_OKCANCEL);
                                        goto denglu;
                                    }
                                    else {
                                        HWND hnd = GetHWnd();
                                        MessageBox(hnd, "账号或密码有误!", "提示", MB_OKCANCEL);
                                        goto login_index;
                                    }
                                }
                            }

                        }

                    }
                }
                else if (msg.x > 300 && msg.x < 500 && msg.y>300 && msg.y < 350) 
                {
                    add_Code();
                    goto denglu;
                }
            }
        }
    }
    closegraph();
}

void add_Code() 
{
    res:
    cleardevice();
    IMAGE img;
    loadimage(&img, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img);
    fillroundrect(350, 200, 500, 240, 5, 5);//账户白框
    fillroundrect(350, 260, 500, 300, 5, 5);//密码白框
    fillroundrect(350, 320, 500, 360, 5, 5);
    settextstyle(30, 0, "黑体");
    outtextxy(280, 205, "账号");
    outtextxy(280, 265, "密码");
    outtextxy(220, 325, "确认密码");
    fillroundrect(370, 400, 430, 430, 5, 5);//确认键白框
    settextstyle(20, 0, "黑体");
    outtextxy(380, 405, "确认");
    settextstyle(50, 0, "黑体");
    outtextxy(360, 100, "注册");
    if (personal_num >= MAX_PERSONAL)
    {
        HWND hnd = GetHWnd();
        MessageBox(hnd, "用户注册人数已满！", "提示", MB_OKCANCEL);
        return;
    }
    struct Personal code;
    char mima[30];
    int index = -1;
    int i;
    while (1)  // 不断地处理事务，需要循环
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 350 && msg.x < 500 && msg.y>200 && msg.y < 240)
                {
                    printf("鼠标在账户框里\n");
                    InputBox(code.account, 30, "请输入账户");
                    settextstyle(30, 0, "黑体");
                    outtextxy(350, 205, code.account);
                }
                else if (msg.x > 350 && msg.x < 500 && msg.y>260 && msg.y < 300)
                {
                    printf("鼠标在密码框里\n");
                    InputBox(code.password, 30, "请输入密码");
                    settextstyle(30, 0, "黑体");
                    outtextxy(350, 265, code.password);
                }
                else if (msg.x > 300 && msg.x < 500 && msg.y>320 && msg.y < 360)
                {
                    printf("鼠标在再次密码框里\n");
                    InputBox(mima, 30, "请确认密码：");
                    settextstyle(30, 0, "黑体");
                    outtextxy(350, 325, mima);
                }
                else if (msg.x > 370 && msg.x < 430 && msg.y>400 && msg.y < 430)
                {

                    printf("点击确认键");
                    //执行比对函数
                    if (strcmp(code.password, mima) == 0)
                    {
                        personals[personal_num] = code;
                        personal_num++;

                        FILE* fp;
                        fp = fopen("users.txt", "w");
                        if (fp == NULL)
                        {
                            printf("文件夹为空！\n");
                        }
                        else
                        {
                            for (i = 0; i < personal_num; i++)
                            {
                                fprintf(fp, "%s %s\n", personals[i].account, personals[i].password);
                            }
                        }
                        fclose(fp);
                        printf("用户保存成功！\n");

                        HWND hnd = GetHWnd();
                        MessageBox(hnd, "创建用户成功！", "提示", MB_OKCANCEL);
                        return;
                    }
                    else
                    {
                        HWND hnd = GetHWnd();
                        MessageBox(hnd, "与前面密码不同，请重新输入：", "提示", MB_OKCANCEL);
                        goto res;
                    }
                }
            }
        }
    }
}

void admin_manage() {
    //初始化
    CatList* head = NULL; // Declare head as a pointer to Catlist and initialize it to NULL
    Initialize(&head);    // Pass the address of head to Initialize
    creat("cats.txt", &head);
    //initgraph(800, 600, 0);
    SetWindowText(GetHWnd(), "菜单");
    cleardevice();

    while (1) 
    {

        IMAGE img1;
        loadimage(&img1, "./image/backimage.jpg", 800, 600);
        putimage(0, 0, &img1);

        setcolor(BLACK);
        fillrectangle(300, 200, 500, 250);//增加白框
        fillrectangle(300, 250, 500, 300);//删除白框
        fillrectangle(300, 300, 500, 350);//查询框
        fillrectangle(300, 350, 500, 400);//修改框
        fillrectangle(300, 400, 500, 450);
        fillrectangle(300, 450, 500, 500);//退出框
        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, "黑体");
        outtextxy(240,100,"欢迎进入猫咪之家！");
        outtextxy(300, 150, "请选择功能");
        settextstyle(30, 0, "黑体");
        outtextxy(305, 210, "增加猫咪信息");
        outtextxy(305, 260, "删除猫咪信息");
        outtextxy(305, 310, "查询猫咪信息");
        outtextxy(305, 360, "修改猫咪信息");
        outtextxy(305, 410, "管理用户信息");
        outtextxy(370, 460, "退出");
        while (1)
        {
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                //判断鼠标是否在上面的矩形中
                //若放在wm_lbuttondown这种，就点击再输出
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    if (msg.x > 300 && msg.x < 500 && msg.y>200 && msg.y < 250)
                    {
                        cat_interp(&head);
                        break;
                    }
                    else if (msg.x > 300 && msg.x < 500 && msg.y>250 && msg.y < 300)
                    {
                        cat_delete(&head);
                        break;
                    }
                    else if (msg.x > 300 && msg.x < 430 && msg.y>300 && msg.y < 350)
                    {
                        cat_inquire(head);
                        break;
                    }
                    else if (msg.x > 300 && msg.x < 430 && msg.y>350 && msg.y < 400)
                    {
                        cat_information_changing(&head);
                        break;
                    }
                    else if (msg.x > 300 && msg.x < 430 && msg.y>400 && msg.y < 450)
                    {
                        user_manage();
                        break;
                    }
                    else if (msg.x > 300 && msg.x < 430 && msg.y>450 && msg.y < 500)
                    {
                        printf("已退出");
                        HWND hnd = GetHWnd();
                        MessageBox(hnd, "期待与您的再次相遇！", "提示", MB_OKCANCEL);
                        exit(0);
                    }
                }

            }
        }
    }
    closegraph();
}

void user_manage() 
{
    
    
    while (1)
    {
        int y1 = 100, y2 = 150;
        cleardevice();
        IMAGE img1;
        loadimage(&img1, "./image/backimage.jpg", 800, 600);
        putimage(0, 0, &img1);
        settextstyle(20, 0, "黑体");
        fillroundrect(720, 520, 760, 550, 5, 5);
        outtextxy(720, 525, "返回");
        fillrectangle(300,100,500,150);
        line(400,100,400,150);
        settextstyle(30, 0, "黑体");
        outtextxy(320,110,"账号");
        outtextxy(420, 110, "密码");
        
        for (int i = 0; i < personal_num; i++) 
        {
            if (personals[i].account[0] != '\0') {
                fillrectangle(300, y1 + 50, 500, y2 + 50);
                line(400, y1 + 50, 400, y2 + 50);
                settextstyle(30, 0, "黑体");
                outtextxy(320, y1 + 60, personals[i].account);
                outtextxy(420, y1 + 60, personals[i].password);
                fillrectangle(540, y1 + 50, 600, y2 + 50);
                outtextxy(540, y1 + 60, "删除");
                y1 = y1 + 50;
                y2 = y2 + 50;
            }
        }
        while (1)
        {
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                //判断鼠标是否在上面的矩形中
                //若放在wm_lbuttondown这种，就点击再输出
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    if (msg.x > 540 && msg.x < 600 && msg.y>100 && msg.y < y2)
                    {
                        int index = ((msg.y - 100) / 50)-1;
                        for (int i = 0; i < index; i++)
                        {
                            personals_temp[i] = personals[i];
                        }
                        for (int i = index + 1; i < personal_num; i++)
                        {
                            personals_temp[i - 1] = personals[i];
                        }
                        personal_num--;
                        for (int i = 0; i < personal_num; i++)
                        {
                            personals[i] = personals_temp[i];
                        }
                        printf("管理员账号删除成功!\n");
                        
                        FILE* fp;
                        fp = fopen("users.txt", "w");
                        if (fp == NULL)
                        {
                            printf("文件夹为空！\n");
                        }
                        else
                        {
                            for (int i = 0; i < personal_num; i++)
                            {
                                fprintf(fp, "%s %s\n", personals[i].account, personals[i].password);
                            }
                        }
                        fclose(fp);
                        break;
                    }
                    else if (msg.x > 720 && msg.x < 760 && msg.y>520 && msg.y < 550) 
                    {
                        return;
                    }
                }
            }
        }
    }
}

void guess_mamage() 
{
    //初始化
    CatList* head = NULL; // Declare head as a pointer to Catlist and initialize it to NULL
    Initialize(&head);    // Pass the address of head to Initialize
    creat("cats.txt", &head);
    //initgraph(800, 600, 0);
    SetWindowText(GetHWnd(), "菜单");
    cleardevice();

    while (1)
    {
        cleardevice();
        IMAGE img2;
        loadimage(&img2, "./image/backimage.jpg", 800, 600);
        putimage(0, 0, &img2);
        setcolor(BLACK);
        settextstyle(40, 0, "黑体");
        setbkmode(TRANSPARENT);
        outtextxy(240, 100, "欢迎进入猫咪之家！");
        outtextxy(220, 150, "请选择下列查询方式");

        fillrectangle(200, 200, 600, 450);
        line(400, 200, 400, 450);
        line(200, 250, 600, 250);
        line(200, 300, 600, 300);
        line(200, 350, 600, 350);
        line(200, 400, 600, 400);
        settextstyle(30, 0, "黑体");
        outtextxy(240, 210, "查询全部");
        outtextxy(440, 210, "姓名查询");
        outtextxy(240, 260, "品种查询");
        outtextxy(440, 260, "性别查询");
        outtextxy(210, 310, "领养状态查询");
        outtextxy(440, 310, "年龄查询");
        outtextxy(210, 360, "到校时间查询");
        outtextxy(440, 360, "年龄排序");
        outtextxy(210, 410, "到校时间排序");
        outtextxy(470, 410, "返回");
        while (1)
        {
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                //判断鼠标是否在上面的矩形中
                //若放在wm_lbuttondown这种，就点击再输出
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    if (msg.x > 200 && msg.x < 400 && msg.y>200 && msg.y < 250)
                    {
                        cat_inquire_all(head);
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>200 && msg.y < 250)
                    {
                        cat_inquire_name(head);
                        break;
                    }
                    else if (msg.x > 200 && msg.x < 400 && msg.y>250 && msg.y < 300)
                    {
                        cat_inquire_type(head);
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>250 && msg.y < 300)
                    {
                        cat_inquire_gender(head);
                        break;
                    }
                    else if (msg.x > 200 && msg.x < 400 && msg.y>300 && msg.y < 350)
                    {
                        cat_inquire_condition(head);
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>300 && msg.y < 350)
                    {
                        cat_inquire_age(head);
                        break;
                    }
                    else if (msg.x > 200 && msg.x < 400 && msg.y>350 && msg.y < 400)
                    {
                        cat_inquire_date(head);
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>350 && msg.y < 400)
                    {
                        cat_sort_age(&head);
                        break;
                    }
                    else if (msg.x > 200 && msg.x < 400 && msg.y>400 && msg.y < 450)
                    {
                        cat_sort_date(head);
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>400 && msg.y < 450)
                    {
                        HWND hnd = GetHWnd();
                        MessageBox(hnd, "期待与您的再次相遇！", "提示", MB_OKCANCEL);
                        return;
                    }
                }

            }
        }
    }
}

void creat(const char* cats, CatList** head)
{
    FILE* file = fopen(cats, "a+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fscanf(file, "%d", &num);
    for (int i = 1; i <= num; i++) {
        CatList* newCat = (CatList*)malloc(sizeof(CatList));
        if (newCat == NULL) {
            perror("Memory allocation failed");
            break;
        }
        fscanf(file, "%s %d %s %d %d %d %d %c", newCat->data.name, &newCat->data.age, newCat->data.type,
            &newCat->data.date.year, &newCat->data.date.month, &newCat->data.date.day, &newCat->data.condition, &newCat->data.gender);

        newCat->next = (*head)->next;
        (*head)->next = newCat;
        //printf("%s ",newCat->data.name);
    }

    fclose(file);
}

void save(CatList* pt) {
    CatList* head = pt->next;
    FILE* fp;
    fp = fopen("cats.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败!\n");
        exit(0);
    }
    fprintf(fp, "%d\n", num);
    for (int i = 0; i < num; i++) {
        fprintf(fp, "%s %d %s %d %d %d %d %c\n", head->data.name, head->data.age, head->data.type, head->data.date.year, head->data.date.month, head->data.date.day, head->data.condition, head->data.gender);
        head = head->next;
    }
    fclose(fp);
}

void cat_inquire(CatList* pt)
{
    CatList* head = pt;

    while (1) 
    {
        cleardevice();
        IMAGE img2;
        loadimage(&img2, "./image/backimage.jpg", 800, 600);
        putimage(0, 0, &img2);
        setcolor(BLACK);
        settextstyle(40, 0, "黑体");
        setbkmode(TRANSPARENT);
        outtextxy(220, 150, "请选择下列查询方式");

        fillrectangle(200, 200, 600, 450);
        line(400, 200, 400, 450);
        line(200, 250, 600, 250);
        line(200, 300, 600, 300);
        line(200, 350, 600, 350);
        line(200, 400, 600, 400);
        settextstyle(30, 0, "黑体");
        outtextxy(240, 210, "查询全部");
        outtextxy(440, 210, "姓名查询");
        outtextxy(240, 260, "品种查询");
        outtextxy(440, 260, "性别查询");
        outtextxy(210, 310, "领养状态查询");
        outtextxy(440, 310, "年龄查询");
        outtextxy(210, 360, "到校时间查询");
        outtextxy(440, 360, "年龄排序");
        outtextxy(210, 410, "到校时间排序");
        outtextxy(470, 410, "返回");
        while (1)
        {
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                //判断鼠标是否在上面的矩形中
                //若放在wm_lbuttondown这种，就点击再输出
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    if (msg.x > 200 && msg.x < 400 && msg.y>200 && msg.y < 250)
                    {
                        cat_inquire_all(head);
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>200 && msg.y < 250)
                    {
                        cat_inquire_name(head);
                        break;
                    }
                    else if (msg.x > 200 && msg.x < 400 && msg.y>250 && msg.y < 300)
                    {
                        cat_inquire_type(head);
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>250 && msg.y < 300)
                    {
                        cat_inquire_gender(head);
                        break;
                    }
                    else if (msg.x > 200 && msg.x < 400 && msg.y>300 && msg.y < 350)
                    {
                        cat_inquire_condition(head); 
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>300 && msg.y < 350)
                    {
                        cat_inquire_age(head);
                        break;
                    }
                    else if (msg.x > 200 && msg.x < 400 && msg.y>350 && msg.y < 400)
                    {
                        cat_inquire_date(head); 
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>350 && msg.y < 400)
                    {
                        cat_sort_age(&head);
                        break;
                    }
                    else if (msg.x > 200 && msg.x < 400 && msg.y>400 && msg.y < 450)
                    {
                        cat_sort_date(head);
                        break;
                    }
                    else if (msg.x > 400 && msg.x < 600 && msg.y>400 && msg.y < 450)
                    {
                        return;
                    }
                }

            }
        }
    }
}

void cat_inquire_all(CatList* head)
{
    CatList* pt;
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);
    //表头
    fillrectangle(100, 95, 700, 125);
    line(175, 95, 175, 125);
    line(230, 95, 230, 125);
    line(300, 95, 300, 125);
    line(420, 95, 420, 125);
    line(650, 95, 650, 125);
    settextstyle(20, 0, "黑体");
    outtextxy(100, 100, " 姓名   年龄  品种   入校时间   是否被领养(1->是 0->否) 性别");
    int ry1=95,ry2=125;
    pt = head->next;
    while (pt != NULL)
    {
        ry1 = ry1 + 30;
        ry2 = ry2 + 30;
        fillrectangle(100, ry1, 700, ry2);
        line(175, ry1, 175, ry2);
        line(230, ry1, 230, ry2);
        line(300, ry1, 300, ry2);
        line(420, ry1, 420, ry2);
        line(650, ry1, 650, ry2);
        outtextxy(100, ry1 + 5, pt->data.name);
        char str[100];
        itoa(pt->data.age, str, 10);
        outtextxy(175, ry1 + 5, str);
        outtextxy(230, ry1 + 5, pt->data.type);
        sprintf(str, "%d-%d-%d", pt->data.date.year, pt->data.date.month, pt->data.date.day);
        outtextxy(300, ry1 + 5, str);
        itoa(pt->data.condition, str, 10);
        outtextxy(500, ry1 + 5, str);
        outtextxy(655, ry1 + 5, pt->data.gender);
        pt = pt->next;
    }
    fillroundrect(720,520,760,550,5,5);
    outtextxy(720, 525, "返回");
    while (1) {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 720 && msg.x < 760 && msg.y>520 && msg.y < 550) {
                    return;
                }
            }
        }
    }
}
void cat_inquire_name(CatList* pt)
{
    CatList* i = pt->next;
    char search_name[10];
    begin_inquire_name:
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);
    InputBox(search_name,10,"请输入要查询的姓名：");
    fillrectangle(200,100,450,140);
    settextstyle(30, 0, "黑体");
    outtextxy(205,105,search_name);
    fillroundrect(500,105,550,135,5,5);
    settextstyle(20,0,"黑体");
    outtextxy(505,110,"确定");
    for (; i != NULL; i = i->next) {
        if (strcmp(search_name, i->data.name) == 0) {
            printf("找到了");
            char path[100];
            sprintf(path,"./image/%s.jpg", i->data.name);
            IMAGE cat_img;
            loadimage(&cat_img, path, 320, 240);
            putimage(50,200, &cat_img);
            setcolor(BROWN);
            fillroundrect(400,200,750,440,10,10);
            setcolor(BLACK);
            char str[100];
            sprintf(str,"姓名：%s",i->data.name);
            outtextxy(410,210,str);
            sprintf(str,"年龄：%d",i->data.age);
            outtextxy(410,250,str);
            sprintf(str, "品种：%s", i->data.type);
            outtextxy(410, 290, str);
            sprintf(str, "入校时间：%d-%d-%d", i->data.date.year, i->data.date.month, i->data.date.day);
            outtextxy(410, 330, str);
            sprintf(str, "领养状态(1->是 0->否)：%d", i->data.condition);
            outtextxy(410, 370, str);
            sprintf(str, "性别：%c", i->data.gender);
            outtextxy(410, 410, str);
            fillroundrect(720, 520, 760, 550, 5, 5);
            outtextxy(720, 525, "返回");
            while (1) {
                if (MouseHit())
                {
                    MOUSEMSG msg = GetMouseMsg();
                    if (msg.uMsg == WM_LBUTTONDOWN)
                    {
                        if (msg.x > 720 && msg.x < 760 && msg.y>520 && msg.y < 550) {
                            return;
                        }
                    }
                }
            }
        }
    }
    i = pt->next;
    HWND hnd = GetHWnd();
    MessageBox(hnd, "没有此猫咪信息!", "提示", MB_OKCANCEL);
    goto begin_inquire_name;
}
void cat_inquire_type(CatList* pt)
{
    CatList* i = pt->next;
    char search_type[10];
    int search_num = 0;
    begin_inquire_type:
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);
    
    InputBox(search_type, 10, "请输入要查询的品种：");
    fillrectangle(200, 100, 450, 140);
    outtextxy(205, 105, search_type);
    fillroundrect(500, 105, 550, 135, 5, 5);
    settextstyle(20, 0, "黑体");
    outtextxy(505, 110, "确定");
    //表头
    int ry1 = 150, ry2 = 180;
    fillrectangle(100, ry1, 700, ry2);
    line(175, ry1, 175, ry2);
    line(230, ry1, 230, ry2);
    line(300, ry1, 300, ry2);
    line(420, ry1, 420, ry2);
    line(650, ry1, 650, ry2);
    settextstyle(20, 0, "黑体");
    outtextxy(100, 155, " 姓名   年龄  品种   入校时间   是否被领养(1->是 0->否) 性别");
    for (; i != NULL; i = i->next) {
        if (strcmp(search_type, i->data.type) == 0) {
            ry1 = ry1 + 30;
            ry2 = ry2 + 30;
            fillrectangle(100, ry1, 700, ry2);
            line(175, ry1, 175, ry2);
            line(230, ry1, 230, ry2);
            line(300, ry1, 300, ry2);
            line(420, ry1, 420, ry2);
            line(650, ry1, 650, ry2);
            outtextxy(100, ry1 + 5, i->data.name);
            char str[100];
            itoa(i->data.age, str, 10);
            outtextxy(175, ry1 + 5, str);
            outtextxy(230, ry1 + 5, i->data.type);
            sprintf(str, "%d-%d-%d", i->data.date.year, i->data.date.month, i->data.date.day);
            outtextxy(300, ry1 + 5, str);
            itoa(i->data.condition, str, 10);
            outtextxy(500, ry1 + 5, str);
            outtextxy(655, ry1 + 5, i->data.gender);
            search_num++;
            
        }
    }
    char result_num[100];
    sprintf(result_num, "一共%d个结果", search_num);
    outtextxy(100,ry2+5,result_num);
    fillroundrect(720, 520, 760, 550, 5, 5);
    outtextxy(720, 525, "返回");
    while (1) {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 720 && msg.x < 760 && msg.y>520 && msg.y < 550) {
                    return;
                }
            }
        }
    }

}
void cat_inquire_gender(CatList* pt) {
    CatList* i = pt->next;
    char search_gender;
    int search_num = 0;
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);
    char str[10];
    InputBox(str, 10, "请输入要查询的性别：");
    search_gender = str[0];
    fillrectangle(200, 100, 450, 140);
    outtextxy(205, 105, search_gender);
    fillroundrect(500, 105, 550, 135, 5, 5);
    settextstyle(20, 0, "黑体");
    outtextxy(505, 110, "确定");
    //表头
    int ry1 = 150, ry2 = 180;
    fillrectangle(100, ry1, 700, ry2);
    line(175, ry1, 175, ry2);
    line(230, ry1, 230, ry2);
    line(300, ry1, 300, ry2);
    line(420, ry1, 420, ry2);
    line(650, ry1, 650, ry2);
    settextstyle(20, 0, "黑体");
    outtextxy(100, 155, " 姓名   年龄  品种   入校时间   是否被领养(1->是 0->否) 性别");
    for (; i != NULL; i = i->next) {
        if (search_gender == i->data.gender) {
            ry1 = ry1 + 30;
            ry2 = ry2 + 30;
            fillrectangle(100, ry1, 700, ry2);
            line(175, ry1, 175, ry2);
            line(230, ry1, 230, ry2);
            line(300, ry1, 300, ry2);
            line(420, ry1, 420, ry2);
            line(650, ry1, 650, ry2);
            outtextxy(100, ry1 + 5, i->data.name);
            char str[100];
            itoa(i->data.age, str, 10);
            outtextxy(175, ry1 + 5, str);
            outtextxy(230, ry1 + 5, i->data.type);
            sprintf(str, "%d-%d-%d", i->data.date.year, i->data.date.month, i->data.date.day);
            outtextxy(300, ry1 + 5, str);
            itoa(i->data.condition, str, 10);
            outtextxy(500, ry1 + 5, str);
            outtextxy(655, ry1 + 5, i->data.gender);
            search_num++;

        }
    }
    char result_num[100];
    sprintf(result_num, "一共%d个结果", search_num);
    outtextxy(100, ry2 + 5, result_num);
    fillroundrect(720, 520, 760, 550, 5, 5);
    outtextxy(720, 525, "返回");
    while (1) {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 720 && msg.x < 760 && msg.y>520 && msg.y < 550) {
                    return;
                }
            }
        }
    }
}
void cat_inquire_condition(CatList* pt) {
    CatList* i = pt->next;
    int search_condition;
    int search_num = 0;
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);
    char str[10];
    InputBox(str, 10, "请输入要查询的领养状态：");
    search_condition = atoi(str);
    fillrectangle(200, 100, 450, 140);
    outtextxy(205, 105, str);
    fillroundrect(500, 105, 550, 135, 5, 5);
    settextstyle(20, 0, "黑体");
    outtextxy(505, 110, "确定");
    //表头
    int ry1 = 150, ry2 = 180;
    fillrectangle(100, ry1, 700, ry2);
    line(175, ry1, 175, ry2);
    line(230, ry1, 230, ry2);
    line(300, ry1, 300, ry2);
    line(420, ry1, 420, ry2);
    line(650, ry1, 650, ry2);
    settextstyle(20, 0, "黑体");
    outtextxy(100, 155, " 姓名   年龄  品种   入校时间   是否被领养(1->是 0->否) 性别");
    for (; i != NULL; i = i->next) {
        if (search_condition == i->data.condition) {
            ry1 = ry1 + 30;
            ry2 = ry2 + 30;
            fillrectangle(100, ry1, 700, ry2);
            line(175, ry1, 175, ry2);
            line(230, ry1, 230, ry2);
            line(300, ry1, 300, ry2);
            line(420, ry1, 420, ry2);
            line(650, ry1, 650, ry2);
            outtextxy(100, ry1 + 5, i->data.name);
            char str[100];
            itoa(i->data.age, str, 10);
            outtextxy(175, ry1 + 5, str);
            outtextxy(230, ry1 + 5, i->data.type);
            sprintf(str, "%d-%d-%d", i->data.date.year, i->data.date.month, i->data.date.day);
            outtextxy(300, ry1 + 5, str);
            itoa(i->data.condition, str, 10);
            outtextxy(500, ry1 + 5, str);
            outtextxy(655, ry1 + 5, i->data.gender);
            search_num++;

        }
    }
    char result_num[100];
    sprintf(result_num, "一共%d个结果", search_num);
    outtextxy(100, ry2 + 5, result_num);
    fillroundrect(720, 520, 760, 550, 5, 5);
    outtextxy(720, 525, "返回");
    while (1) {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 720 && msg.x < 760 && msg.y>520 && msg.y < 550) {
                    return;
                }
            }
        }
    }
}
void cat_inquire_age(CatList* pt) {
    CatList* i = pt->next;
    int search_age_low;
    int search_age_high;
    int search_num = 0;
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);
    char str[10];
    InputBox(str, 10, "请输入要查询的年龄下限和上限(格式如low-high):");
    fillrectangle(200, 100, 450, 140);
    fillroundrect(500, 105, 550, 135, 5, 5);
    settextstyle(20, 0, "黑体");
    outtextxy(505, 110, "确定");
    settextstyle(30, 0, "黑体");
    outtextxy(205, 105, str);
    const char* delim = "-";
    char* temp = strtok(str, delim);
    search_age_low = atoi(temp);
    temp = strtok(NULL, delim);
    search_age_high = atoi(temp);
    
    //表头
    int ry1 = 150, ry2 = 180;
    fillrectangle(100, ry1, 700, ry2);
    line(175, ry1, 175, ry2);
    line(230, ry1, 230, ry2);
    line(300, ry1, 300, ry2);
    line(420, ry1, 420, ry2);
    line(650, ry1, 650, ry2);
    settextstyle(20, 0, "黑体");
    outtextxy(100, 155, " 姓名   年龄  品种   入校时间   是否被领养(1->是 0->否) 性别");
    for (; i != NULL; i = i->next) {
        if (search_age_low <= i->data.age && search_age_high >= i->data.age) {
            ry1 = ry1 + 30;
            ry2 = ry2 + 30;
            fillrectangle(100, ry1, 700, ry2);
            line(175, ry1, 175, ry2);
            line(230, ry1, 230, ry2);
            line(300, ry1, 300, ry2);
            line(420, ry1, 420, ry2);
            line(650, ry1, 650, ry2);
            outtextxy(100, ry1 + 5, i->data.name);
            char str[100];
            itoa(i->data.age, str, 10);
            outtextxy(175, ry1 + 5, str);
            outtextxy(230, ry1 + 5, i->data.type);
            sprintf(str, "%d-%d-%d", i->data.date.year, i->data.date.month, i->data.date.day);
            outtextxy(300, ry1 + 5, str);
            itoa(i->data.condition, str, 10);
            outtextxy(500, ry1 + 5, str);
            outtextxy(655, ry1 + 5, i->data.gender);
            search_num++;

        }
    }
    char result_num[100];
    sprintf(result_num, "一共%d个结果", search_num);
    outtextxy(100, ry2 + 5, result_num);
    fillroundrect(720, 520, 760, 550, 5, 5);
    outtextxy(720, 525, "返回");
    while (1) {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 720 && msg.x < 760 && msg.y>520 && msg.y < 550) {
                    return;
                }
            }
        }
    }
}
void cat_inquire_date(CatList* pt) {
    CatList* i = pt->next;
    int low_year, low_month, low_day, high_year, high_month, high_day;
    int search_num = 0;
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);
    char str[100];
    InputBox(str, 100, "请输入要查询的日期下限和上限(格式如2010-3-12 2021-4-21):");
    settextstyle(20, 0, "黑体");
    fillrectangle(200, 100, 450, 140);
    outtextxy(205, 110, str);
    fillroundrect(500, 105, 550, 135, 5, 5);
    settextstyle(20, 0, "黑体");
    outtextxy(505, 110, "确定");

    const char* delim = "-";
    char* temp = strtok(str, delim);
    low_year = atoi(temp);
    temp = strtok(NULL, delim);
    low_month = atoi(temp);
    delim = " ";
    temp = strtok(NULL, delim);
    low_day = atoi(temp);
    delim = "-";
    temp = strtok(NULL, delim);
    high_year = atoi(temp);
    temp = strtok(NULL, delim);
    high_month = atoi(temp);
    temp = strtok(NULL, delim);
    high_day = atoi(temp);

    struct Date date_low = { low_year,low_month,low_day };
    struct Date date_high = { high_year,high_month,high_day };

    //表头
    int ry1 = 150, ry2 = 180;
    fillrectangle(100, ry1, 700, ry2);
    line(175, ry1, 175, ry2);
    line(230, ry1, 230, ry2);
    line(300, ry1, 300, ry2);
    line(420, ry1, 420, ry2);
    line(650, ry1, 650, ry2);
    settextstyle(20, 0, "黑体");
    outtextxy(100, 155, " 姓名   年龄  品种   入校时间   是否被领养(1->是 0->否) 性别");
    for (; i != NULL; i = i->next) {
        if (compare(date_low, i->data.date) <= 0 && compare(date_high, i->data.date) >= 0) {
            ry1 = ry1 + 30;
            ry2 = ry2 + 30;
            fillrectangle(100, ry1, 700, ry2);
            line(175, ry1, 175, ry2);
            line(230, ry1, 230, ry2);
            line(300, ry1, 300, ry2);
            line(420, ry1, 420, ry2);
            line(650, ry1, 650, ry2);
            outtextxy(100, ry1 + 5, i->data.name);
            char str[100];
            itoa(i->data.age, str, 10);
            outtextxy(175, ry1 + 5, str);
            outtextxy(230, ry1 + 5, i->data.type);
            sprintf(str, "%d-%d-%d", i->data.date.year, i->data.date.month, i->data.date.day);
            outtextxy(300, ry1 + 5, str);
            itoa(i->data.condition, str, 10);
            outtextxy(500, ry1 + 5, str);
            outtextxy(655, ry1 + 5, i->data.gender);
            search_num++;

        }
    }
    char result_num[100];
    sprintf(result_num, "一共%d个结果", search_num);
    outtextxy(100, ry2 + 5, result_num);
    fillroundrect(720, 520, 760, 550, 5, 5);
    outtextxy(720, 525, "返回");
    while (1) {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 720 && msg.x < 760 && msg.y>520 && msg.y < 550) {
                    return;
                }
            }
        }
    }
    
    /*CatList* i = pt->next;
    int low_year, low_month, low_day, high_year, high_month, high_day;
    printf("请输入要查询的日期下限和上限(格式如2010-3-12 2021-4-21):");
    scanf("%d-%d-%d %d-%d-%d", &low_year, &low_month, &low_day, &high_year, &high_month, &high_day);
    struct Date date_low = { low_year,low_month,low_day };
    struct Date date_high = { high_year,high_month,high_day };
    printf("姓名\t 年龄\t 品种\t 入住时间\t 是否被领养(1->是 0->否)\t 性别\n");
    int search_num = 0;
    for (; i != NULL; i = i->next) {
        if (compare(date_low, i->data.date) <= 0 && compare(date_high, i->data.date) >= 0) {
            printf("%s\t %d\t %s\t %d-%d-%d\t %d\t\t\t\t %c\n", i->data.name, i->data.age, i->data.type, i->data.date.year, i->data.date.month, i->data.date.day, i->data.condition, i->data.gender);
            search_num++;
        }
    }

    printf("一共%d个结果\n", search_num);*/
    
}
int compare(struct Date date1, struct Date date2) {
    int date1_int = date1.year * 10000 + date1.month * 100 + date1.day;
    int date2_int = date2.year * 10000 + date2.month * 100 + date2.day;

    if (date1_int < date2_int) {
        return -1;
    }
    else if (date1_int > date2_int) {
        return 1;
    }
    else {
        return 0;
    }
}
void cat_sort_age(CatList** pt) {
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);
    char str[10];
    InputBox(str,10,"选择排序方法:1->升序 2->降序");
    int chose = atoi(str);

    switch (chose)
    {
    case 1:Cat_age_sort1(pt); break;
    case 2:Cat_age_sort2(pt); break;
    default:break;
    }

}
/*年龄排序1*/
void Cat_age_sort1(CatList** pt)//年龄从小到大排序
{

    CatList* head = *pt;
    CatList* a = head;
    CatList* p = a->next->next;//指向第二个数据节点
    CatList* front = a->next;
    while (p != NULL)
    {
        while (a->next != p)
        {
            if (a->next->data.age > p->data.age)
            {
                CatList* back = p->next;
                p->next = a->next;//让p指向插入位置的节点
                a->next = p;
                front->next = back;
                p = front;
                break;
            }
            a = a->next;
        }
        front = p;
        p = p->next;
        a = head;
    }
    cat_inquire_all(*pt);
}
/*年龄排序2*/
void Cat_age_sort2(CatList** pt)//年龄从小到大排序
{

    CatList* head = *pt;
    CatList* a = head;
    CatList* p = a->next->next;//指向第二个数据节点
    CatList* front = a->next;
    while (p != NULL)
    {
        while (a->next != p)
        {
            if (a->next->data.age < p->data.age)
            {
                CatList* back = p->next;
                p->next = a->next;//让p指向插入位置的节点
                a->next = p;
                front->next = back;
                p = front;
                break;
            }
            a = a->next;
        }
        front = p;
        p = p->next;
        a = head;
    }
    cat_inquire_all(*pt);
}

void cat_sort_date(CatList* pt) {
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);
    char str[10];
    InputBox(str, 10, "选择排序方法:1->升序 2->降序");
    int chose = atoi(str);
    switch (chose)
    {
    case 1:Cat_date_sort1(pt); break;
    case 2:Cat_date_sort2(pt); break;
    default:break;
    }
}
void Cat_date_sort1(CatList* pt) {
    CatList* first, * t, * p, * q;
    first = pt->next->next;
    pt->next->next = NULL;
    while (first != NULL)
    {
        for (t = first, q = pt->next; ((q != NULL) && (compare(q->data.date, t->data.date) < 0)); p = q, q = q->next);
        //for(t=first,q=pt->next;((q!=NULL)&&(q->data.date.year<t->data.date.year));p=q,q=q->next);
        first = first->next;
        if (q == pt->next)
            pt->next = t;
        else
            p->next = t;
        t->next = q;
    }
    cat_inquire_all(pt);
}
void Cat_date_sort2(CatList* pt) {
    CatList* first, * t, * p, * q;
    first = pt->next->next;
    pt->next->next = NULL;
    while (first != NULL)
    {
        for (t = first, q = pt->next; ((q != NULL) && (compare(q->data.date, t->data.date) > 0)); p = q, q = q->next);
        //for(t=first,q=pt->next;((q!=NULL)&&(q->data.date.year>t->data.date.year));p=q,q=q->next);
        first = first->next;
        if (q == pt->next)
            pt->next = t;
        else
            p->next = t;
        t->next = q;
    }
    cat_inquire_all(pt);
}
/*修改信息*/
void Initialize(CatList** L)
{
    *L = (CatList*)malloc(sizeof(CatList));
    if (*L != NULL) {
        (*L)->next = NULL;
    }
}
void cat_information_changing(CatList** L)
{
    CatList* i = *L;
    char name[10];
    char new_name[10];
    char new_type[10];
    int new_year;
    int new_month;
    int new_day;
    int new_condition = 0;
    char new_gender;
    begin_change:
    cleardevice();
    IMAGE img2;
    loadimage(&img2, "./image/backimage.jpg", 800, 600);
    putimage(0,0,&img2);
    setcolor(BLACK);
    settextstyle(40,0,"黑体");
    setbkmode(TRANSPARENT);
    outtextxy(200,200,"请输入要修改的对象名：");
    fillrectangle(300,300,500,340);
    
    
    fillrectangle(370,400,430,430);
    settextstyle(25, 0, "黑体");
    outtextxy(375, 405, "确认");

    while (1)  // 不断地处理事务，需要循环
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            //判断鼠标是否在上面的矩形中
            //若放在wm_lbuttondown这种，就点击再输出
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 300 && msg.x < 500 && msg.y>300 && msg.y < 340)
                {
                    InputBox(name, 10, "请输入要修改的对象名：");
                    settextstyle(30, 0, "黑体");
                    outtextxy(310, 305, name);
                }
                else if (msg.x > 370 && msg.x < 430 && msg.y>400 && msg.y < 430)
                {
                    for (; i != NULL; i = i->next)
                    {
                        if (strcmp(name, i->data.name) == 0)
                        {
                            cleardevice();
                            IMAGE img3;
                            loadimage(&img3, "./image/backimage.jpg", 800, 600);
                            putimage(0, 0, &img3);
                            //画表格
                            fillrectangle(100, 95, 700, 125);
                            fillrectangle(100, 125, 700, 155);
                            line(175,95,175,155);
                            line(230,95,230,155);
                            line(300,95,300,155);
                            line(420,95,420,155);
                            line(650,95,650,155);
                            settextstyle(20, 0, "黑体");
                            //char str[1000];
                            outtextxy(100, 100, " 姓名   年龄  品种   入校时间   是否被领养(1->是 0->否) 性别");
                            outtextxy(100,130,i->data.name);
                            char str[100];
                            itoa(i->data.age,str,10);
                            outtextxy(175,130,str);
                            outtextxy(230,130,i->data.type);
                            sprintf(str,"%d-%d-%d", i->data.date.year, i->data.date.month, i->data.date.day);
                            outtextxy(300,130,str);
                            itoa(i->data.condition, str, 10);
                            outtextxy(480,130,str);
                            outtextxy(655, 130, i->data.gender);

                            fillrectangle(100,200,180,230);
                            outtextxy(100,205,"修改姓名");
                            fillrectangle(180,200,260,230);
                            outtextxy(180,205,"修改年龄");
                            fillrectangle(260, 200, 340, 230);
                            outtextxy(260, 205, "修改品种");
                            fillrectangle(340,200,460,230);
                            outtextxy(340,205,"修改入校时间");
                            fillrectangle(460,200,580,230);
                            outtextxy(460,205,"修改领养状态");
                            fillrectangle(580,200,660,230);
                            outtextxy(580,205,"修改性别");

                            while (1) {
                                msg = GetMouseMsg();
                                if (msg.uMsg == WM_LBUTTONDOWN) {
                                    if (msg.x > 100 && msg.x < 180 && msg.y>200 && msg.y < 230)
                                    {
                                        InputBox(new_name,10,"请输入修改的名字：");
                                        fillrectangle(200, 300, 400, 330);
                                        fillroundrect(450, 300, 490, 330,5,5);
                                        outtextxy(450, 305, "确认");
                                        outtextxy(205,305,new_name);
                                        while (1) {
                                            msg = GetMouseMsg();
                                            if (msg.uMsg == WM_LBUTTONDOWN) {
                                                if (msg.x > 450 && msg.x < 490 && msg.y>300 && msg.y < 330) {
                                                    strcpy(i->data.name, new_name);
                                                    settextstyle(30, 0, "黑体");
                                                    save(*L);
                                                    outtextxy(340, 400, "修改成功");
                                                    Sleep(2000);//延时ms
                                                    return;
                                                }
                                            }
                                        }
                                        
                                    }
                                    else if (msg.x > 180 && msg.x < 260 && msg.y>200 && msg.y < 230) 
                                    {
                                        int new_age;
                                        char new_str[10];
                                        InputBox(new_str, 10, "请输入修改的年龄：");
                                        fillrectangle(200, 300, 400, 330);
                                        fillroundrect(450, 300, 490, 330, 5, 5);
                                        outtextxy(450, 305, "确认");
                                        outtextxy(205, 305, new_str);
                                        while (1) {
                                            msg = GetMouseMsg();
                                            if (msg.uMsg == WM_LBUTTONDOWN) {
                                                if (msg.x > 450 && msg.x < 490 && msg.y>300 && msg.y < 330) {
                                                    new_age = atoi(new_str);
                                                    i->data.age = new_age;
                                                    settextstyle(30, 0, "黑体");
                                                    save(*L);
                                                    outtextxy(340, 400, "修改成功");
                                                    Sleep(2000);//延时ms
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                    else if (msg.x > 260 && msg.x < 340 && msg.y>200 && msg.y < 230) {
                                        InputBox(new_type, 10, "请输入修改的品种名：");
                                        fillrectangle(200, 300, 400, 330);
                                        fillroundrect(450, 300, 490, 330, 5, 5);
                                        outtextxy(450, 305, "确认");
                                        outtextxy(205, 305, new_type);
                                        while (1) {
                                            msg = GetMouseMsg();
                                            if (msg.uMsg == WM_LBUTTONDOWN) {
                                                if (msg.x > 450 && msg.x < 490 && msg.y>300 && msg.y < 330) {
                                                    strcpy(i->data.type, new_type);
                                                    settextstyle(30, 0, "黑体");
                                                    save(*L);
                                                    outtextxy(340, 400, "修改成功");
                                                    Sleep(2000);//延时ms
                                                    return;
                                                }
                                            }
                                        }

                                    }
                                    else if (msg.x > 340 && msg.x < 460 && msg.y>200 && msg.y < 230) {
                                        char new_str[10];
                                        InputBox(new_str, 10, "请输入修改的时间(year-month-day)：");
                                        fillrectangle(200, 300, 400, 330);
                                        fillroundrect(450, 300, 490, 330, 5, 5);
                                        outtextxy(450, 305, "确认");
                                        outtextxy(205, 305, new_str);
                                        while (1) {
                                            msg = GetMouseMsg();
                                            if (msg.uMsg == WM_LBUTTONDOWN) {
                                                if (msg.x > 450 && msg.x < 490 && msg.y>300 && msg.y < 330) {
                                                    const char* delim = "-";
                                                    char* temp = strtok(new_str, delim);
                                                    new_year = atoi(temp);
                                                    temp = strtok(NULL, delim);
                                                    new_month = atoi(temp);
                                                    temp = strtok(NULL, delim);
                                                    new_day = atoi(temp);
                                                    i->data.date.year = new_year;
                                                    i->data.date.month = new_month;
                                                    i->data.date.day = new_day;
                                                    settextstyle(30, 0, "黑体");
                                                    save(*L);
                                                    outtextxy(340, 400, "修改成功");
                                                    Sleep(2000);//延时ms
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                    else if (msg.x > 460 && msg.x < 580 && msg.y>200 && msg.y < 230) {
                                        char new_str[10];
                                        InputBox(new_str, 10, "请输入领养状态:1已领养/0未领养");
                                        fillrectangle(200, 300, 400, 330);
                                        fillroundrect(450, 300, 490, 330, 5, 5);
                                        outtextxy(450, 305, "确认");
                                        outtextxy(205, 305, new_str);
                                        while (1) {
                                            msg = GetMouseMsg();
                                            if (msg.uMsg == WM_LBUTTONDOWN) {
                                                if (msg.x > 450 && msg.x < 490 && msg.y>300 && msg.y < 330) {
                                                    new_condition = atoi(new_str);
                                                    i->data.condition = new_condition;
                                                    settextstyle(30, 0, "黑体");
                                                    save(*L);
                                                    outtextxy(340, 400, "修改成功");
                                                    Sleep(2000);//延时ms
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                    else if (msg.x > 580 && msg.x < 660 && msg.y>200 && msg.y < 230) {
                                        char new_str[10];
                                        InputBox(new_str, 10, "请输入修改的性别：");
                                        fillrectangle(200, 300, 400, 330);
                                        fillroundrect(450, 300, 490, 330, 5, 5);
                                        outtextxy(450, 305, "确认");
                                        outtextxy(205, 305, new_str);
                                        while (1) {
                                            msg = GetMouseMsg();
                                            if (msg.uMsg == WM_LBUTTONDOWN) {
                                                if (msg.x > 450 && msg.x < 490 && msg.y>300 && msg.y < 330) {
                                                    new_gender = new_str[0];
                                                    i->data.gender = new_gender;
                                                    settextstyle(30, 0, "黑体");
                                                    save(*L);
                                                    outtextxy(340, 400, "修改成功");
                                                    Sleep(2000);//延时ms
                                                    return;
                                                }
                                            }
                                        }

                                    }
                                }
                            }
                        }
                        
                    }
                    HWND hnd = GetHWnd();
                    MessageBox(hnd, "没有此猫咪信息!", "提示", MB_OKCANCEL);
                    i = *L;
                    goto begin_change;
                }                
            }
        }
    }
}

/*增加信息*/
void cat_interp(CatList** L)
{
    CatList* i = *L;
    char name[10];
    int age;
    char new_type[10];
    char new_gender;
    int year, month, day;
    int condition;
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img1);

    fillrectangle(100, 95, 700, 125);
    fillrectangle(100, 125, 700, 155);
    line(175, 95, 175, 155);
    line(230, 95, 230, 155);
    line(300, 95, 300, 155);
    line(420, 95, 420, 155);
    line(650, 95, 650, 155);
    settextstyle(20, 0, "黑体");
    outtextxy(100, 100, " 姓名   年龄  品种   入校时间   是否被领养(1->是 0->否) 性别");
    fillroundrect(380,170,420,200,5,5);
    outtextxy(380,175,"确定");
    while (1)
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            //判断鼠标是否在上面的矩形中
            //若放在wm_lbuttondown这种，就点击再输出
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 100 && msg.x < 175 && msg.y>125 && msg.y < 155)
                {
                    InputBox(name,10,"请输入猫咪姓名：");
                    outtextxy(105,130,name);
                }
                else if (msg.x > 175 && msg.x < 230 && msg.y>125 && msg.y < 155)
                {
                    char str[10];
                    InputBox(str,10, "请输入猫咪年龄：");
                    age = atoi(str);
                    outtextxy(180,130,str);
                }
                else if (msg.x > 230 && msg.x < 300 && msg.y>125 && msg.y < 155)
                {
                    InputBox(new_type, 10, "请输入猫咪品种：");
                    outtextxy(235, 130, new_type);
                }
                else if (msg.x > 300 && msg.x < 420 && msg.y>125 && msg.y < 155)
                {
                    char str[100];
                    InputBox(str, 100, "请输入猫咪入住时间：");
                    outtextxy(305, 130, str);
                    const char* delim = "-";
                    char* temp = strtok(str, delim);
                    year = atoi(temp);
                    printf("year=%d",year);
                    temp = strtok(NULL, delim);
                    month = atoi(temp);
                    printf("month=%d", month);
                    temp = strtok(NULL, delim);
                    day = atoi(temp);
                    printf("day=%d", day);
                }
                else if (msg.x > 420 && msg.x < 650 && msg.y>125 && msg.y < 155)
                {
                    char str[10];
                    InputBox(str, 10, "请输入猫咪是否被领养(1->是 0->否）：");
                    condition = atoi(str);
                    outtextxy(425, 130, str);
                }
                else if (msg.x > 650 && msg.x < 700 && msg.y>125 && msg.y < 155)
                {
                    char str[10];
                    InputBox(str, 10, "请输入猫咪性别：");
                    new_gender = str[0];
                    outtextxy(655, 130, str);
                }
                else if (msg.x > 380 && msg.x < 420 && msg.y>170 && msg.y < 200)
                {
                    CatList* newCat = (CatList*)malloc(sizeof(CatList));
                    strcpy(newCat->data.name, name);
                    newCat->data.age = age;
                    strcpy(newCat->data.type, new_type);
                    newCat->data.date.year = year;
                    newCat->data.date.month = month;
                    newCat->data.date.day = day;
                    newCat->data.condition = condition;
                    newCat->data.gender = new_gender;

                    newCat->next = i->next;
                    i->next = newCat;
                    num++;

                    settextstyle(40,0,"黑体");
                    outtextxy(320,250,"添加成功");
                    save(*L);
                    Sleep(2000);//延时ms
                    return;
                }
            }
        }
    }
}
void cat_delete(CatList** L)
{
    CatList* i = *L;
    int flag;
    char s1[10];
    flag = 0;
    char age_str[100];
    char str[100];
    cleardevice();
    IMAGE img2;
    loadimage(&img2, "./image/backimage.jpg", 800, 600);
    putimage(0, 0, &img2);
    setcolor(BLACK);
    settextstyle(40, 0, "黑体");
    setbkmode(TRANSPARENT);
    outtextxy(200, 200, "请输入要删除的对象名：");
    fillrectangle(300, 300, 500, 340);

    fillrectangle(370, 400, 430, 430);
    settextstyle(25, 0, "黑体");
    outtextxy(375, 405, "确认");

    while (1)  // 不断地处理事务，需要循环
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            //判断鼠标是否在上面的矩形中
            //若放在wm_lbuttondown这种，就点击再输出
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x > 300 && msg.x < 500 && msg.y>300 && msg.y < 340)
                {
                    InputBox(s1, 10, "请输入要删除的对象名：");
                    settextstyle(30, 0, "黑体");
                    outtextxy(310, 305, s1);
                }
                else if (msg.x > 370 && msg.x < 430 && msg.y>400 && msg.y < 430)
                {
                    for (int j=0;j<num;j++)
                    {
                        if (strcmp(s1, i->next->data.name) == 0)
                        {
                            cleardevice();
                            IMAGE img3;
                            loadimage(&img3, "./image/backimage.jpg", 800, 600);
                            putimage(0, 0, &img3);
                            //画表格
                            fillrectangle(100, 95, 700, 125);
                            fillrectangle(100, 125, 700, 155);
                            line(175, 95, 175, 155);
                            line(230, 95, 230, 155);
                            line(300, 95, 300, 155);
                            line(420, 95, 420, 155);
                            line(650, 95, 650, 155);
                            settextstyle(20, 0, "黑体");
                            outtextxy(100, 100, " 姓名   年龄  品种   入校时间   是否被领养(1->是 0->否) 性别");
                            outtextxy(100, 130, i->next->data.name);
                            itoa(i->next->data.age, age_str, 10);
                            outtextxy(175, 130, age_str);
                            outtextxy(230, 130, i->next->data.type);
                            sprintf(str, "%d-%d-%d", i->next->data.date.year, i->next->data.date.month, i->next->data.date.day);
                            outtextxy(300, 130, str);
                            itoa(i->next->data.condition, str, 10);
                            outtextxy(480, 130, str);
                            outtextxy(655, 130, i->next->data.gender);

                            fillroundrect(380,170,420,200,5,5);
                            outtextxy(380,175,"确定");
                            while (1) {
                                msg = GetMouseMsg();
                                if (msg.uMsg == WM_LBUTTONDOWN) {
                                    if (msg.x > 360 && msg.x < 440 && msg.y>170 && msg.y < 200)
                                    {
                                        flag = 1;
                                        i->next = i->next->next;//直接把后面的都往前移动
                                        num--;
                                        settextstyle(30, 0, "黑体");
                                        save(*L);
                                        outtextxy(340, 400, "删除成功");
                                        Sleep(2000);//延时ms
                                        return;
                                    }
                                    
                                }
                            }
                        } 
                        i = i->next;
                        
                    }
                    if (0 == flag)
                    {
                        cleardevice();
                        IMAGE img3;
                        loadimage(&img3, "./image/backimage.jpg", 800, 600);
                        putimage(0, 0, &img3);
                        settextstyle(30, 0, "黑体");
                        outtextxy(270, 400, "该猫咪不存在！！！");
                        Sleep(2000);//延时ms
                        return;
                    }
                }
            }
        }
    }
}