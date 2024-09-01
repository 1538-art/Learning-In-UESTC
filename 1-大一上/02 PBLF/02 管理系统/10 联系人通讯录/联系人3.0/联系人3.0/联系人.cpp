#include"main.h"

//主菜单界面
void mymainmeau() {

	//closegraph();

	IMAGE photo;//定义图片变量
	loadimage(&photo, "图片/联系人2.png");//导入图片
	putimage(0, 0, &photo);//把图片贴出来
	//IMAGE photo1;//定义图片变量
	//loadimage(&photo1, "图片/LOGO.jpg");//导入图片
	//putimage(20, 80, &photo1);//把图片贴出来
}

//副界面的界面 以及文字格式
void mytextwin() {
	//initgraph(400, 650);
	IMAGE photo;
	loadimage(&photo, "图片/联系人2.jpg");
	putimage(0, 0, &photo);
	//cleardevice()；

	settextstyle(20, 0, "宋体"); settextcolor(BLACK); setbkmode(TRANSPARENT); //设置文字的大小，形式，颜色，透明

	outtextxy(20, 70, "|姓名| |性别| |电话号码|      |地区|   ");//输出文字到窗口   outtextxy（坐标，字符串）
	settextstyle(30, 0, "宋体");
	setfillcolor(RGB(172, 172, 172));
	fillrectangle(130, 570, 280, 600);
	outtextxy(130, 570, "返回主界面");
	

	settextstyle(20, 0, "楷体");
	fillrectangle(20, 560, 80, 580);
	outtextxy(20, 560, "上一页");
	fillrectangle(300, 560, 360, 580);
	outtextxy(300,560,"下一页");
}



//联系人的的基本信息数据
class person {
private:
	string name;
	string sex;
	string number;
	string diqu;

public:

	person() {

	}
	person(string a, string b, string c, string d) {
		name = a;
		sex = b;
		number = c;
		diqu = d;
	}

	string getName() {
		return name;
	}

	string getSex() {
		return sex;
	}

	string getNumber() {
		return number;
	}

	string getDiqu() {
		return diqu;
	}

	void setName(string n) {
		name = n;
	}

	void setSex(string n) {
		sex = n;
	}

	void setNumber(string n) {
		number = n;
	}

	void setDiqu(string n) {
		diqu = n;
	}

};

//通讯录系统
class Txl_systeam {
private:
	vector<person> People;//用vector容器来存储数据

public:
	Txl_systeam() {
		MessageBox(NULL, "“右击”任意区域可保存通讯录", "TIP", MB_SYSTEMMODAL);
		//读取文件操作
		ifstream du("通讯录数据.txt", ios::in);//只读
		if (du.is_open()) {// 打开成功的话
			string name_;
			string sex_;
			string number_;
			string diqu_;

			while (du >> name_ >> sex_ >> number_ >> diqu_) { //依次读取每一行的四个字符串，直到读到空就停止
				person temp_(name_, sex_, number_, diqu_);

				People.push_back(temp_); //传入容器 People

			}
			du.close();
			int n = People.size();
			for (int i = 0; i < n - 1; i++) {
				bool flag = false; // 标记本轮是否有交换
				for (int j = 0; j < n - i - 1; j++) {
					if (People[j].getName() > People[j + 1].getName()) {
						swap(People[j], People[j + 1]);
						flag = true;
					}
				}
				if (!flag) break; // 如果本轮没有交换，说明已经有序，直接退出循环
			}
		}
		

		else {
			MessageBox(NULL, "当前通讯录数据为空，请添加联系人", "Tip", MB_SYSTEMMODAL);
		}
	}

	void SaveTxl_systeam() {//保存数据
		ofstream xie("通讯录数据.txt", ios::out);//只写

		vector<person>::iterator it = People.begin();
		for (; it != People.end(); it++) //vector 的遍历方法，用迭代器
		{
			xie << it->getName() << "  " << it->getSex() << "     " << it->getNumber() << "    " << it->getDiqu() << endl;
		}
		xie.close();
		MessageBox(NULL, "保存成功！", "TIP", MB_SYSTEMMODAL);

	}

	bool Delete() { //删除指定联系人
		char z[20];
		InputBox(z, 20, "请输入要删除的联系人姓名", NULL, NULL, 0, 0, false);

		for (vector<person>::iterator it = People.begin(); it != People.end(); )
		{
			// if ( mystrcmp(z, (*it).name) == 1 ) {
			if (z == it->getName()) {
				if (MessageBox(NULL, "再次确定是否删除此联系人信息", "匹配成功", MB_YESNO) == IDYES) {
					it = People.erase(it);
					MessageBox(NULL, "删除成功", "OK", MB_TASKMODAL);
					MessageBox(NULL, "右击任意区域可保存通讯录", "TIP", MB_SYSTEMMODAL);
					return true;
				}
				else return true;
			}
			else {
				++it;
			}
		}
		MessageBox(NULL, "无此联系人", "错误！", MB_SYSTEMMODAL);
		return false;
	}

	bool Find() { //查找指定联系人信息
		char z[200];
		//string z;
		InputBox(z, 200, "请输入要查找的联系人姓名", NULL, NULL, 0, 0, false);
		vector<person>::iterator it = People.begin();
		for (; it != People.end(); )
		{
			// if ( mystrcmp(z, (*it).name) == 1 ) {
			if (z == it->getName()) {
				string data;//整合四个 char[] 到一个 char[]里
				data += "姓名：";
				data += it->getName();
				data += "\n";
				data += "性别：";
				data += it->getSex();
				data += "\n";
				data += "号码：";
				data += it->getNumber();
				data += "\n";
				data += "地区：";
				data += it->getDiqu();

				MessageBox(NULL, (char*)data.data(), "详细信息为", MB_SYSTEMMODAL);
				if (MessageBox(NULL, (char*)data.data(), "是否修改此联系人信息", MB_YESNO) == IDYES) {
					Updata(z);
				}

				return true;
			}
			else {
				++it;
			}
		}
		MessageBox(NULL, "无此联系人", "错误！", MB_SYSTEMMODAL);
		return false;
	}

	bool Updata(char ming[]) {//更新指定联系人信息

		for (vector<person>::iterator it = People.begin(); it != People.end(); )
		{
			if (ming == it->getName()) {
				char name_[20], sex_[5], number_[20], diqu_[10];
				InputBox(name_, 20, "请重新输入联系人姓名", NULL, NULL, 0, 0, true);
				InputBox(sex_, 20, "请重新输入联系人性别", NULL, NULL, 0, 0, true);
				InputBox(number_, 20, "请重新输入联系人号码", NULL, NULL, 0, 0, true);
				InputBox(diqu_, 20, "请重新输入联系人地区", NULL, NULL, 0, 0, true);
				if (strlen(name_) == 0 || strlen(sex_) == 0 || strlen(number_) == 0 || strlen(diqu_) == 0) {
					MessageBox(NULL, "错误的空输入", "False", MB_SYSTEMMODAL);
					return false;
				}

				it->setName(name_);
				it->setSex(sex_);
				it->setNumber(number_);
				it->setDiqu(diqu_);

				MessageBox(NULL, "修改成功", "OK", MB_SYSTEMMODAL);
				return true;
			}
			else {
				++it;
			}
		}
		MessageBox(NULL, "无此联系人", "错误！", MB_SYSTEMMODAL);
		return false;
	}

	void deletedata() {//格式化通讯录数据
		char myprivate[20];
		ifstream du("权限密码.txt", ios::in | ios::binary);//只读
		if (du.is_open()) {//打开成功的话
			du >> myprivate; //读取行字符串，直到读到空就停止
			du.close();
		}
		else {//打开失败的话
			MessageBox(NULL, "当前未设置权限密码，请输入权限密码", "Tip", MB_SYSTEMMODAL);
			ofstream xie("权限密码.txt", ios::out | ios::binary);//只写
			InputBox(myprivate, 20, "请设置您的通讯录管理权限密码", NULL, "不多于20个字符", 0, 0, true);
			xie << myprivate;
			MessageBox(NULL, "权限密码设置成功", "OK", MB_SYSTEMMODAL);
			xie.close();
			return;
		}
		char in1[20];
		MessageBox(NULL, "格式化之后无法恢复哦！", "警告！", MB_SYSTEMMODAL);
		InputBox(in1, 20, "请输入您的通讯录管理权限密码", NULL, NULL, 0, 0, false);
		if (strcmp(in1, myprivate) == 0) {
			char in2[20];
			InputBox(in2, 20, "请再次输入密码进行最后的确定", NULL, NULL, 0, 0, true); {
				if (strcmp(in2, myprivate) == 0) {
					People.clear();

					MessageBox(NULL, "格式化成功", "提示", MB_SYSTEMMODAL);
					return;
				}
				else {
					MessageBox(NULL, "密码错误！", "False", MB_SYSTEMMODAL);
					return;
				}
			}
		}
		else {
			MessageBox(NULL, "密码错误！", "False", MB_SYSTEMMODAL);
			return;
		}

	}

	friend ostream& operator <<(ostream& cout, Txl_systeam& x);
	friend istream& operator >>(istream& cout, Txl_systeam& x);
};

istream& operator >>(istream& cin, Txl_systeam& x) {
	if (x.People.size() == 30) {
		MessageBox(NULL, "通讯录已经满了！", "False ", MB_SYSTEMMODAL);
		return cin;
	}

	char name_[20], sex_[20], number_[11], diqu_[20];
	for(int i = 0;i <1 ; i++)
	InputBox(name_, 20, "请输入联系人姓名", NULL, NULL, 0, 0, true);// EaxyX的 InputBox（）函数 弹出一个窗口来用于获取用户的输入
	for (int i = 0;i < 1; i++)
	InputBox(sex_, 20, "请输入联系人性别", NULL, NULL, 0, 0, true);//InputBox(字符串，最大字符长度，标题，窗口标题，编辑框提示串，弹窗的宽度，高度，确定的形式【true,false】)
	InputBox(number_, 11, "请输入联系人号码", NULL, NULL, 0, 0, true);

	for (vector<person>::iterator it = x.People.begin(); it != x.People.end(); )//判断是否通讯录中已经有重复的号码
	{
		if (number_ == it->getNumber()) {
			MessageBox(NULL, "通讯录中已经有该号码！！", "False Input", MB_SYSTEMMODAL);
			return cin;
		}
		else {
			++it;
		}
	}

	InputBox(diqu_, 20, "请输入联系人地区", NULL, NULL, 0, 0, true);
	if (strlen(name_) == 0 || strlen(sex_) == 0 || strlen(number_) == 0 || strlen(diqu_) == 0) {//提高程序的健壮性——1.输入空串
		MessageBox(NULL, "错误的空输入", "False", MB_SYSTEMMODAL);//EasyX 的MessageBox()函数 弹出一个窗口用于提醒用户
		return cin;                                           // MessageBox(窗口的变量，正文字符串，标题字符串，弹出的形式【 MB_APPLMODA，MB_SYSTEMMODAL， MB_TASKMODAL】)
	}

	person temp_(name_, sex_, number_, diqu_);
	x.People.push_back(temp_);
	MessageBox(NULL, "添加成功", "OK", MB_SYSTEMMODAL);
	MessageBox(NULL, "右击任意区域可保存通讯录", "TIP", MB_SYSTEMMODAL);

	return cin;
}

ostream& operator <<(ostream& cout, Txl_systeam& x) {//重载<<运算符
	mytextwin();
	settextcolor(BLACK);
	while (1) {
		int flag = 0;//记录输出多少个联系人
		int i = 20, j = 110;
		//第一页联系人
		for (vector<person>::iterator it = x.People.begin(); it != x.People.end(); it++)
		{
			flag++;
			if (flag <= 15) {
				cout << it->getName() << "  " << it->getSex() << "     " << it->getNumber() << "    " << it->getDiqu() << endl;
				outtextxy(i, j, (char*)(it->getName()).data());
				outtextxy(i + 100, j, (char*)(it->getSex()).data());
				outtextxy(i + 150, j, (char*)(it->getNumber()).data());
				outtextxy(i + 300, j, (char*)(it->getDiqu()).data());
				j = j + 30;
			}
		}
		while (1) {//输出完第一页之后就进入此循环
			MOUSEMSG mm = GetMouseMsg();

			//下一页的 触发——
			if (mm.uMsg == WM_LBUTTONDOWN && mm.y > 560 && mm.y < 580 && mm.x>300 && mm.x < 360) {
				mytextwin();
				settextcolor(BLACK);
				flag = 0;
				int i = 20, j = 110;
				for (vector<person>::iterator it = x.People.begin(); it != x.People.end(); it++)//第二页联系人
				{
					flag++;
					if (flag > 15) {
						//cout << (*it).name << "  " << (*it).sex << "     " << (*it).number << "    " << (*it).diqu << endl;
						cout << it->getName() << "  " << it->getSex() << "     " << it->getNumber() << "    " << it->getDiqu() << endl;
						outtextxy(i, j, (char*)(it->getName()).data());
						outtextxy(i + 100, j, (char*)(it->getSex()).data());
						outtextxy(i + 150, j, (char*)(it->getNumber()).data());
						outtextxy(i + 300, j, (char*)(it->getDiqu()).data());
						j = j + 30;

					}
				}
			}

			//上一页的触发
			if (mm.uMsg == WM_LBUTTONDOWN && mm.y > 560 && mm.y < 580 && mm.x>20 && mm.x < 80) {
				mytextwin();
				settextcolor(BLACK);
				break;
			}
			//返回主界面的 ‘按钮’
			if (mm.uMsg == WM_LBUTTONDOWN && mm.y > 570 && mm.y < 600 && mm.x>130 && mm.x < 270) {
				return cout;
			}
		}
	}
}

int main() {
	initgraph(400, 650);//画一个宽400，高650的窗口
	mymainmeau();

	Txl_systeam user;
	//BeginBatchDraw();
	while (1) {//进入无限循环，不然这个界面点击一次就失效了

		MOUSEMSG m = GetMouseMsg();//定义鼠标变量
		switch (m.uMsg) {//分配鼠标的消息————比如  鼠标移动，左击，右击，左双击，右双击等等
		case WM_LBUTTONDOWN: {//左击鼠标操作
			if (m.x > 100 && m.x < 300 && m.y>50 && m.y < 80) {//  SHOW  的坐标位置
				cout << user;
				//closegraph();
				mymainmeau();
				break;
			}
			if (m.x > 130 && m.x < 270 && m.y>150 && m.y < 180) {//  +  的位置
				cin >> user;
				break;
			}
			if (m.x > 130 && m.x < 270 && m.y>260 && m.y < 290) {//  - 的位置
				user.Delete();
				break;
			}
			if (m.x > 130 && m.x < 270 && m.y>368 && m.y < 398) {//  查找 的位置
				user.Find();
				break;
			}
			if (m.x > 130 && m.x < 270 && m.y>480 && m.y < 510) {//  修改  的位置
				char ming[20];
				InputBox(ming, 20, "请输入要修改的联系人姓名", NULL, NULL, 0, 0, false);
				user.Updata(ming);

				break;
			}
			if (m.x > 85 && m.x < 315 && m.y>570 && m.y < 600) {//  格式化  的位置
				user.deletedata();
				break;
			}
		}
		case WM_MOUSEMOVE: {//鼠标移动操作                    制造鼠标停留在按钮上会有提示文字的效果，鼠标移开，文字效果消失
			settextstyle(30, 0, "宋体");
			setbkmode(TRANSPARENT);
			if (m.x > 100 && m.x < 300 && m.y>50 && m.y < 80) {//  SHOW  的位置
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(100, 50, 300, 80);
				outtextxy(100, 50, "显示所有联系人");
			}
			else {//如果 离开 SHOW 的位置
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(100, 50, 300, 80);
				outtextxy(100, 50, "显示所有联系人");
			}
			if (m.x > 130 && m.x < 270 && m.y>150 && m.y < 180) {//  +  的位置
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 150, 270, 180);
				outtextxy(130, 150, "添加联系人");

			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 150, 270, 180);
				outtextxy(130, 150, "添加联系人");
			}
			if (m.x > 130 && m.x < 270 && m.y>260 && m.y < 290) {//  - 的位置
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 260, 270, 290);
				outtextxy(130, 260, "删除联系人");
			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 260, 270, 290);
				outtextxy(130, 260, "删除联系人");
			}
			if (m.x > 130 && m.x < 270 && m.y>368 && m.y < 398) {//  chazhao 的位置
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 368, 270, 400);
				outtextxy(130, 368, "查找联系人");
			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 368, 270, 400);
				outtextxy(130, 368, "查找联系人");
			}
			if (m.x > 130 && m.x < 270 && m.y>480 && m.y < 510) {//  xiugai  的位置
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 480, 270, 510);
				outtextxy(130, 480, "修改联系人");
			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 480, 270, 510);
				outtextxy(130, 480, "修改联系人");
			}
			if (m.x > 85 && m.x < 315 && m.y>570 && m.y < 600) {//  格式化  的位置
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(85, 570, 315, 600);
				outtextxy(85, 570, "格式化通讯录数据");
			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(85, 570, 315, 600);
				outtextxy(85, 570, "格式化通讯录数据");
			}
			break;
		}
		case WM_RBUTTONUP: {//右击鼠标保存
			if (m.x > 0 && m.x < 400 && m.y>0 && m.y < 650) {
				user.SaveTxl_systeam();
			}
		}
		}
		//FlushBatchDraw();

	}
	//EndBatchDraw();
	system("pause");
	return 0;
}