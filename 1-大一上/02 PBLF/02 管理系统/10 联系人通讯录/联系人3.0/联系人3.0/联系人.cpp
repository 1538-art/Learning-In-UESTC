#include"main.h"

//���˵�����
void mymainmeau() {

	//closegraph();

	IMAGE photo;//����ͼƬ����
	loadimage(&photo, "ͼƬ/��ϵ��2.png");//����ͼƬ
	putimage(0, 0, &photo);//��ͼƬ������
	//IMAGE photo1;//����ͼƬ����
	//loadimage(&photo1, "ͼƬ/LOGO.jpg");//����ͼƬ
	//putimage(20, 80, &photo1);//��ͼƬ������
}

//������Ľ��� �Լ����ָ�ʽ
void mytextwin() {
	//initgraph(400, 650);
	IMAGE photo;
	loadimage(&photo, "ͼƬ/��ϵ��2.jpg");
	putimage(0, 0, &photo);
	//cleardevice()��

	settextstyle(20, 0, "����"); settextcolor(BLACK); setbkmode(TRANSPARENT); //�������ֵĴ�С����ʽ����ɫ��͸��

	outtextxy(20, 70, "|����| |�Ա�| |�绰����|      |����|   ");//������ֵ�����   outtextxy�����꣬�ַ�����
	settextstyle(30, 0, "����");
	setfillcolor(RGB(172, 172, 172));
	fillrectangle(130, 570, 280, 600);
	outtextxy(130, 570, "����������");
	

	settextstyle(20, 0, "����");
	fillrectangle(20, 560, 80, 580);
	outtextxy(20, 560, "��һҳ");
	fillrectangle(300, 560, 360, 580);
	outtextxy(300,560,"��һҳ");
}



//��ϵ�˵ĵĻ�����Ϣ����
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

//ͨѶ¼ϵͳ
class Txl_systeam {
private:
	vector<person> People;//��vector�������洢����

public:
	Txl_systeam() {
		MessageBox(NULL, "���һ�����������ɱ���ͨѶ¼", "TIP", MB_SYSTEMMODAL);
		//��ȡ�ļ�����
		ifstream du("ͨѶ¼����.txt", ios::in);//ֻ��
		if (du.is_open()) {// �򿪳ɹ��Ļ�
			string name_;
			string sex_;
			string number_;
			string diqu_;

			while (du >> name_ >> sex_ >> number_ >> diqu_) { //���ζ�ȡÿһ�е��ĸ��ַ�����ֱ�������վ�ֹͣ
				person temp_(name_, sex_, number_, diqu_);

				People.push_back(temp_); //�������� People

			}
			du.close();
			int n = People.size();
			for (int i = 0; i < n - 1; i++) {
				bool flag = false; // ��Ǳ����Ƿ��н���
				for (int j = 0; j < n - i - 1; j++) {
					if (People[j].getName() > People[j + 1].getName()) {
						swap(People[j], People[j + 1]);
						flag = true;
					}
				}
				if (!flag) break; // �������û�н�����˵���Ѿ�����ֱ���˳�ѭ��
			}
		}
		

		else {
			MessageBox(NULL, "��ǰͨѶ¼����Ϊ�գ��������ϵ��", "Tip", MB_SYSTEMMODAL);
		}
	}

	void SaveTxl_systeam() {//��������
		ofstream xie("ͨѶ¼����.txt", ios::out);//ֻд

		vector<person>::iterator it = People.begin();
		for (; it != People.end(); it++) //vector �ı����������õ�����
		{
			xie << it->getName() << "  " << it->getSex() << "     " << it->getNumber() << "    " << it->getDiqu() << endl;
		}
		xie.close();
		MessageBox(NULL, "����ɹ���", "TIP", MB_SYSTEMMODAL);

	}

	bool Delete() { //ɾ��ָ����ϵ��
		char z[20];
		InputBox(z, 20, "������Ҫɾ������ϵ������", NULL, NULL, 0, 0, false);

		for (vector<person>::iterator it = People.begin(); it != People.end(); )
		{
			// if ( mystrcmp(z, (*it).name) == 1 ) {
			if (z == it->getName()) {
				if (MessageBox(NULL, "�ٴ�ȷ���Ƿ�ɾ������ϵ����Ϣ", "ƥ��ɹ�", MB_YESNO) == IDYES) {
					it = People.erase(it);
					MessageBox(NULL, "ɾ���ɹ�", "OK", MB_TASKMODAL);
					MessageBox(NULL, "�һ���������ɱ���ͨѶ¼", "TIP", MB_SYSTEMMODAL);
					return true;
				}
				else return true;
			}
			else {
				++it;
			}
		}
		MessageBox(NULL, "�޴���ϵ��", "����", MB_SYSTEMMODAL);
		return false;
	}

	bool Find() { //����ָ����ϵ����Ϣ
		char z[200];
		//string z;
		InputBox(z, 200, "������Ҫ���ҵ���ϵ������", NULL, NULL, 0, 0, false);
		vector<person>::iterator it = People.begin();
		for (; it != People.end(); )
		{
			// if ( mystrcmp(z, (*it).name) == 1 ) {
			if (z == it->getName()) {
				string data;//�����ĸ� char[] ��һ�� char[]��
				data += "������";
				data += it->getName();
				data += "\n";
				data += "�Ա�";
				data += it->getSex();
				data += "\n";
				data += "���룺";
				data += it->getNumber();
				data += "\n";
				data += "������";
				data += it->getDiqu();

				MessageBox(NULL, (char*)data.data(), "��ϸ��ϢΪ", MB_SYSTEMMODAL);
				if (MessageBox(NULL, (char*)data.data(), "�Ƿ��޸Ĵ���ϵ����Ϣ", MB_YESNO) == IDYES) {
					Updata(z);
				}

				return true;
			}
			else {
				++it;
			}
		}
		MessageBox(NULL, "�޴���ϵ��", "����", MB_SYSTEMMODAL);
		return false;
	}

	bool Updata(char ming[]) {//����ָ����ϵ����Ϣ

		for (vector<person>::iterator it = People.begin(); it != People.end(); )
		{
			if (ming == it->getName()) {
				char name_[20], sex_[5], number_[20], diqu_[10];
				InputBox(name_, 20, "������������ϵ������", NULL, NULL, 0, 0, true);
				InputBox(sex_, 20, "������������ϵ���Ա�", NULL, NULL, 0, 0, true);
				InputBox(number_, 20, "������������ϵ�˺���", NULL, NULL, 0, 0, true);
				InputBox(diqu_, 20, "������������ϵ�˵���", NULL, NULL, 0, 0, true);
				if (strlen(name_) == 0 || strlen(sex_) == 0 || strlen(number_) == 0 || strlen(diqu_) == 0) {
					MessageBox(NULL, "����Ŀ�����", "False", MB_SYSTEMMODAL);
					return false;
				}

				it->setName(name_);
				it->setSex(sex_);
				it->setNumber(number_);
				it->setDiqu(diqu_);

				MessageBox(NULL, "�޸ĳɹ�", "OK", MB_SYSTEMMODAL);
				return true;
			}
			else {
				++it;
			}
		}
		MessageBox(NULL, "�޴���ϵ��", "����", MB_SYSTEMMODAL);
		return false;
	}

	void deletedata() {//��ʽ��ͨѶ¼����
		char myprivate[20];
		ifstream du("Ȩ������.txt", ios::in | ios::binary);//ֻ��
		if (du.is_open()) {//�򿪳ɹ��Ļ�
			du >> myprivate; //��ȡ���ַ�����ֱ�������վ�ֹͣ
			du.close();
		}
		else {//��ʧ�ܵĻ�
			MessageBox(NULL, "��ǰδ����Ȩ�����룬������Ȩ������", "Tip", MB_SYSTEMMODAL);
			ofstream xie("Ȩ������.txt", ios::out | ios::binary);//ֻд
			InputBox(myprivate, 20, "����������ͨѶ¼����Ȩ������", NULL, "������20���ַ�", 0, 0, true);
			xie << myprivate;
			MessageBox(NULL, "Ȩ���������óɹ�", "OK", MB_SYSTEMMODAL);
			xie.close();
			return;
		}
		char in1[20];
		MessageBox(NULL, "��ʽ��֮���޷��ָ�Ŷ��", "���棡", MB_SYSTEMMODAL);
		InputBox(in1, 20, "����������ͨѶ¼����Ȩ������", NULL, NULL, 0, 0, false);
		if (strcmp(in1, myprivate) == 0) {
			char in2[20];
			InputBox(in2, 20, "���ٴ����������������ȷ��", NULL, NULL, 0, 0, true); {
				if (strcmp(in2, myprivate) == 0) {
					People.clear();

					MessageBox(NULL, "��ʽ���ɹ�", "��ʾ", MB_SYSTEMMODAL);
					return;
				}
				else {
					MessageBox(NULL, "�������", "False", MB_SYSTEMMODAL);
					return;
				}
			}
		}
		else {
			MessageBox(NULL, "�������", "False", MB_SYSTEMMODAL);
			return;
		}

	}

	friend ostream& operator <<(ostream& cout, Txl_systeam& x);
	friend istream& operator >>(istream& cout, Txl_systeam& x);
};

istream& operator >>(istream& cin, Txl_systeam& x) {
	if (x.People.size() == 30) {
		MessageBox(NULL, "ͨѶ¼�Ѿ����ˣ�", "False ", MB_SYSTEMMODAL);
		return cin;
	}

	char name_[20], sex_[20], number_[11], diqu_[20];
	for(int i = 0;i <1 ; i++)
	InputBox(name_, 20, "��������ϵ������", NULL, NULL, 0, 0, true);// EaxyX�� InputBox�������� ����һ�����������ڻ�ȡ�û�������
	for (int i = 0;i < 1; i++)
	InputBox(sex_, 20, "��������ϵ���Ա�", NULL, NULL, 0, 0, true);//InputBox(�ַ���������ַ����ȣ����⣬���ڱ��⣬�༭����ʾ���������Ŀ�ȣ��߶ȣ�ȷ������ʽ��true,false��)
	InputBox(number_, 11, "��������ϵ�˺���", NULL, NULL, 0, 0, true);

	for (vector<person>::iterator it = x.People.begin(); it != x.People.end(); )//�ж��Ƿ�ͨѶ¼���Ѿ����ظ��ĺ���
	{
		if (number_ == it->getNumber()) {
			MessageBox(NULL, "ͨѶ¼���Ѿ��иú��룡��", "False Input", MB_SYSTEMMODAL);
			return cin;
		}
		else {
			++it;
		}
	}

	InputBox(diqu_, 20, "��������ϵ�˵���", NULL, NULL, 0, 0, true);
	if (strlen(name_) == 0 || strlen(sex_) == 0 || strlen(number_) == 0 || strlen(diqu_) == 0) {//��߳���Ľ�׳�ԡ���1.����մ�
		MessageBox(NULL, "����Ŀ�����", "False", MB_SYSTEMMODAL);//EasyX ��MessageBox()���� ����һ���������������û�
		return cin;                                           // MessageBox(���ڵı����������ַ����������ַ�������������ʽ�� MB_APPLMODA��MB_SYSTEMMODAL�� MB_TASKMODAL��)
	}

	person temp_(name_, sex_, number_, diqu_);
	x.People.push_back(temp_);
	MessageBox(NULL, "��ӳɹ�", "OK", MB_SYSTEMMODAL);
	MessageBox(NULL, "�һ���������ɱ���ͨѶ¼", "TIP", MB_SYSTEMMODAL);

	return cin;
}

ostream& operator <<(ostream& cout, Txl_systeam& x) {//����<<�����
	mytextwin();
	settextcolor(BLACK);
	while (1) {
		int flag = 0;//��¼������ٸ���ϵ��
		int i = 20, j = 110;
		//��һҳ��ϵ��
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
		while (1) {//������һҳ֮��ͽ����ѭ��
			MOUSEMSG mm = GetMouseMsg();

			//��һҳ�� ��������
			if (mm.uMsg == WM_LBUTTONDOWN && mm.y > 560 && mm.y < 580 && mm.x>300 && mm.x < 360) {
				mytextwin();
				settextcolor(BLACK);
				flag = 0;
				int i = 20, j = 110;
				for (vector<person>::iterator it = x.People.begin(); it != x.People.end(); it++)//�ڶ�ҳ��ϵ��
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

			//��һҳ�Ĵ���
			if (mm.uMsg == WM_LBUTTONDOWN && mm.y > 560 && mm.y < 580 && mm.x>20 && mm.x < 80) {
				mytextwin();
				settextcolor(BLACK);
				break;
			}
			//����������� ����ť��
			if (mm.uMsg == WM_LBUTTONDOWN && mm.y > 570 && mm.y < 600 && mm.x>130 && mm.x < 270) {
				return cout;
			}
		}
	}
}

int main() {
	initgraph(400, 650);//��һ����400����650�Ĵ���
	mymainmeau();

	Txl_systeam user;
	//BeginBatchDraw();
	while (1) {//��������ѭ������Ȼ���������һ�ξ�ʧЧ��

		MOUSEMSG m = GetMouseMsg();//����������
		switch (m.uMsg) {//����������Ϣ������������  ����ƶ���������һ�����˫������˫���ȵ�
		case WM_LBUTTONDOWN: {//���������
			if (m.x > 100 && m.x < 300 && m.y>50 && m.y < 80) {//  SHOW  ������λ��
				cout << user;
				//closegraph();
				mymainmeau();
				break;
			}
			if (m.x > 130 && m.x < 270 && m.y>150 && m.y < 180) {//  +  ��λ��
				cin >> user;
				break;
			}
			if (m.x > 130 && m.x < 270 && m.y>260 && m.y < 290) {//  - ��λ��
				user.Delete();
				break;
			}
			if (m.x > 130 && m.x < 270 && m.y>368 && m.y < 398) {//  ���� ��λ��
				user.Find();
				break;
			}
			if (m.x > 130 && m.x < 270 && m.y>480 && m.y < 510) {//  �޸�  ��λ��
				char ming[20];
				InputBox(ming, 20, "������Ҫ�޸ĵ���ϵ������", NULL, NULL, 0, 0, false);
				user.Updata(ming);

				break;
			}
			if (m.x > 85 && m.x < 315 && m.y>570 && m.y < 600) {//  ��ʽ��  ��λ��
				user.deletedata();
				break;
			}
		}
		case WM_MOUSEMOVE: {//����ƶ�����                    �������ͣ���ڰ�ť�ϻ�����ʾ���ֵ�Ч��������ƿ�������Ч����ʧ
			settextstyle(30, 0, "����");
			setbkmode(TRANSPARENT);
			if (m.x > 100 && m.x < 300 && m.y>50 && m.y < 80) {//  SHOW  ��λ��
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(100, 50, 300, 80);
				outtextxy(100, 50, "��ʾ������ϵ��");
			}
			else {//��� �뿪 SHOW ��λ��
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(100, 50, 300, 80);
				outtextxy(100, 50, "��ʾ������ϵ��");
			}
			if (m.x > 130 && m.x < 270 && m.y>150 && m.y < 180) {//  +  ��λ��
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 150, 270, 180);
				outtextxy(130, 150, "�����ϵ��");

			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 150, 270, 180);
				outtextxy(130, 150, "�����ϵ��");
			}
			if (m.x > 130 && m.x < 270 && m.y>260 && m.y < 290) {//  - ��λ��
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 260, 270, 290);
				outtextxy(130, 260, "ɾ����ϵ��");
			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 260, 270, 290);
				outtextxy(130, 260, "ɾ����ϵ��");
			}
			if (m.x > 130 && m.x < 270 && m.y>368 && m.y < 398) {//  chazhao ��λ��
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 368, 270, 400);
				outtextxy(130, 368, "������ϵ��");
			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 368, 270, 400);
				outtextxy(130, 368, "������ϵ��");
			}
			if (m.x > 130 && m.x < 270 && m.y>480 && m.y < 510) {//  xiugai  ��λ��
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 480, 270, 510);
				outtextxy(130, 480, "�޸���ϵ��");
			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(130, 480, 270, 510);
				outtextxy(130, 480, "�޸���ϵ��");
			}
			if (m.x > 85 && m.x < 315 && m.y>570 && m.y < 600) {//  ��ʽ��  ��λ��
				settextcolor(RED);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(85, 570, 315, 600);
				outtextxy(85, 570, "��ʽ��ͨѶ¼����");
			}
			else {
				settextcolor(WHITE);
				setfillcolor(RGB(172, 172, 172));
				fillrectangle(85, 570, 315, 600);
				outtextxy(85, 570, "��ʽ��ͨѶ¼����");
			}
			break;
		}
		case WM_RBUTTONUP: {//�һ���걣��
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