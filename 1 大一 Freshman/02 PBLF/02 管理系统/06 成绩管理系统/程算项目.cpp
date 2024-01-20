#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
struct temp{
	char username[10010];
	long long password,identity;
};
struct grade{
	char name[10010];
	double calcu,linal,engl,ave;
	struct grade *next;
};
int num1,po;
long long Iden;
char Password[10010];
temp User[1010];
grade stu;
char now_user[10010],now_pass[10010];
bool flag;
const long long mod=1e9+7;
long long Pow(long long a,long long b)
{
	long long ans=1,base=a;
	while(b)
	{
		if(b&1)
		{
			ans=(ans*base)%mod;
		}
		base=(base*base)%mod;
		b>>=1;
	}
	return ans;
}

void SWAP(grade *a,grade *b)
{
	swap(a->ave,b->ave);
	swap(a->calcu,b->calcu);
	swap(a->linal,b->linal);
	swap(a->engl,b->engl);
	char CC[10010];
	strcpy(CC,a->name);
	strcpy(a->name,b->name);
	strcpy(b->name,CC);
}
grade *Start()
{
    grade *fa=(grade*)malloc(sizeof(grade));
    fa->name[0]='w';
    fa->next=NULL;
    fa->calcu=1e9;
    fa->linal=1e9;
    fa->ave=1e9;
    fa->engl=1e9;
    return fa;
}
void Print(grade *fa)
{
    if(fa==NULL) return;
    fa=fa->next;
    cout<<setw(10)<<"����"<<setw(10)<<"΢����"<<setw(10)<<"���Դ���"<<setw(10)<<"Ӣ��"<<setw(10)<<"ƽ����"<<endl;
    while(fa!=NULL)
    {
    	cout<<setw(10)<<fa->name<<setw(10)<<fa->calcu<<setw(10)<<fa->linal<<setw(10)<<fa->engl<<setw(10)<<fa->ave<<endl;
        fa=fa->next;
    }
}
void Insert_Point(grade *fa,grade STU)
{
	while(fa->next!=NULL) fa=fa->next;
	grade *son=(grade*)malloc(sizeof(grade));
	son->next=fa->next;
	fa->next=son;
	strcpy(son->name,STU.name);
	son->ave=STU.ave;
	son->calcu=STU.calcu;
	son->linal=STU.linal;
	son->engl=STU.engl;
}
void Delete_Point(grade *fa,grade STU)
{
	bool FT=0;
	grade *son=fa->next;
	while(son!=NULL)
	{
		if(!strcmp(son->name,STU.name))
		{
			fa->next=son->next;
			FT=1;
			cout<<"�ѳɹ�ɾ�� "<<STU.name<<" �ĳɼ�"<<endl;
			Sleep(1000);
			break;
		}
		fa=fa->next;
		son=son->next;
	}
	if(!FT)
	{
		cout<<"δ�ҵ�����Ϊ��"<<STU.name<<" ��ѧ��"<<endl;
		Sleep(1000);
	}
	return;
}
void Modify_Point(grade *fa,grade STU)
{
	bool FT=0;
	grade *son=fa->next;
	while(son!=NULL)
	{
		if(!strcmp(son->name,STU.name))
		{
			son->ave=STU.ave;
			son->calcu=STU.calcu;
			son->linal=STU.linal;
			son->engl=STU.engl;
			FT=1;
			cout<<"�ѳɹ��޸� "<<STU.name<<" �ĳɼ�"<<endl;
			Sleep(1000);
			break;
		}
		fa=fa->next;
		son=son->next;
	}
	if(!FT)
	{
		cout<<"δ�ҵ�����Ϊ��"<<STU.name<<" ��ѧ��"<<endl;
		Sleep(1000);
	}
	return;
}
void Sort(grade *fa,int com)
{
	grade *son=fa->next;
	while(son!=NULL)
	{
		grade *gson=son->next;
		grade *maxpoint=son;
		bool FL=0;
		while(gson!=NULL)
		{
			switch(com)
			{
				case 1:
					if(maxpoint->ave<gson->ave)
					{
						maxpoint=gson;
						FL=1;
					}
					break;
				case 2:
					if(maxpoint->calcu<gson->calcu)
					{
						maxpoint=gson;
						FL=1;
					}
					break;
				case 3:
					if(maxpoint->linal<gson->linal)
					{
						maxpoint=gson;
						FL=1;
					}
					break;
				case 4:
					if(maxpoint->engl<gson->engl)
					{
						maxpoint=gson;
						FL=1;
					}
					break;
			}
			gson=gson->next;
		}
		if(FL) SWAP(son,maxpoint);
		son=son->next;
	}
}

void ViewController(bool F)
{
	if(!F)
	{
		cout<<"��ӭ����ϵͳ"<<endl;
		cout<<"1.Login"<<endl;
		cout<<"2.Register"<<endl;
		cout<<"3.Exit"<<endl;
		return;
	}
	cout<<"��ӭ����ϵͳ"<<endl;
	cout<<"1.Logout"<<endl;
	cout<<"2.��ѯ�ɼ�"<<endl; 
	cout<<"3.Exit"<<endl;
	if(Iden)
	{
		cout<<"4.����ѧ���ɼ�"<<endl;
		cout<<"5.ɾ��ѧ���ɼ�"<<endl;
		cout<<"6.����ѧ���ɼ�"<<endl;
	}
	return;
}

int main()
{
	grade *fa=Start();
	FILE* pf1=fopen("123.dat","r");
	if(pf1==NULL)
	{
		perror("fopen");
		exit(-1);
	}
	FILE* pf2=fopen("123.dat","a+");
	if(pf2==NULL)
	{
		perror("fopen");
		exit(-1);
	}
	while((fgets(User[++num1].username,10010,pf1))!=NULL)
	{
		fscanf(pf1,"%lld%lld",&(User[num1].password),&(User[num1].identity));
	}
	num1--;
	FILE* pf3=fopen("456.dat","r");
	if(pf3==NULL)
	{
		perror("fopen");
		exit(-1);
	}
	while((fgets(stu.name,10010,pf3))!=NULL)
	{
		fscanf(pf3,"%lf%lf%lf",&(stu.calcu),&(stu.linal),&(stu.engl));
		stu.name[strlen(stu.name)-1]=0;
		stu.ave=(stu.calcu+stu.linal+stu.engl)/3.0;
		Insert_Point(fa,stu);
		fgets(stu.name,10010,pf3);
	}
	FILE* pf4=fopen("456.dat","w");
	if(pf4==NULL)
	{
		perror("fopen");
		exit(-1);
	}
	while(1)
	{
		ViewController(flag);
		cin>>po;
		system("cls");
		if(po==2)
		{
			if(!flag)
			{
				cin>>User[++num1].username;
				cin>>Password;
				User[num1].password=Password[0]-0;
				for(int i=1;i<strlen(Password);i++)
				{
					User[num1].password=Pow(User[num1].password,Password[i]-0);
				}
				User[num1].username[strlen(User[num1].username)]='\n';
				User[num1].identity=0;
				fprintf(pf2,"%s%lld\n%lld\n",User[num1].username,User[num1].password,User[num1].identity);
				system("cls");
				continue;
			}
			else
			{
				bool FL=0;
				while(1)
				{
					Print(fa);
					cout<<"1.Exit"<<endl;
					cout<<"2.��ƽ��������������"<<endl;
					cout<<"3.��΢���ַ�����������"<<endl;
					cout<<"4.���ߴ�������������"<<endl;
					cout<<"5.��Ӣ�������������"<<endl;
					int kl;
					cin>>kl;
					if(kl==1)
					{
						system("cls");
						break;
					}
					switch(kl)
					{
						case 2:
							Sort(fa,1);
							break;
						case 3:
							Sort(fa,2);
							break;
						case 4:
							Sort(fa,3);
							break;
						case 5:
							Sort(fa,4);
							break;
					}
					system("cls");
				}
			}
		}
		else if(po==1)
		{
			if(flag)
			{
				Iden=0;
				flag=0;
				continue;
			}
			memset(now_user,0,sizeof(now_user));
			memset(now_pass,0,sizeof(now_pass));
			cin>>now_user;
			cin>>now_pass;
			long long nowpass=now_pass[0]-0ll;
			now_user[strlen(now_user)]='\n';
			for(int i=1;i<strlen(now_pass);i++)
			{
				cout<<i<<" "<<now_pass[i]<<" "<<(now_pass[i]-0)<<" "<<nowpass<<endl;
				nowpass=Pow(nowpass,now_pass[i]-0);
			}
			system("cls");
			for(int i=1;i<=num1;i++)
			{
				if((!strcmp(now_user,User[i].username))&&(nowpass==User[i].password))
				{
					cout<<"Success"<<endl;
					Iden=User[i].identity; 
					flag=1;
					cout<<"�û�: ";
					for(int i=0;i<=strlen(now_user);i++) cout<<now_user[i];
					cout<<"���: ";
					if(Iden) cout<<"��ʦ";
					else cout<<"ѧ��"; 
					Sleep(2000);
					break;
				}
			}
			if(!flag)
			{
				cout<<"Wrong Username or Password"<<endl;
				Sleep(1000);
			}
		}
		else if(po==3) break;
		else if(po>3&&!Iden)
		{
			cout<<"�����ָ�����������"<<endl;
			Sleep(1000);
		}
		else if(po==4)
		{
			cout<<"������ѧ�������� ";
			cin>>stu.name;
			cout<<"������ѧ��΢���ַ����� ";
			cin>>stu.calcu;
			cout<<"������ѧ�����Դ��������� ";
			cin>>stu.linal;
			cout<<"������ѧ��Ӣ������� ";
			cin>>stu.engl;
			stu.ave=(stu.calcu+stu.linal+stu.engl)/3.0;
			Insert_Point(fa,stu);
		}
		else if(po==5)
		{
			cout<<"������ѧ�������� ";
			cin>>stu.name;
			Delete_Point(fa,stu);
		}
		else if(po==6)
		{
			cout<<"������ѧ�������� ";
			cin>>stu.name;
			cout<<"������ѧ��΢���ַ����� ";
			cin>>stu.calcu;
			cout<<"������ѧ�����Դ��������� ";
			cin>>stu.linal;
			cout<<"������ѧ��Ӣ������� ";
			cin>>stu.engl;
			stu.ave=(stu.calcu+stu.linal+stu.engl)/3.0;
			Modify_Point(fa,stu);
		}
		system("cls");
	}
	fa=fa->next;
	while(fa!=NULL)
	{
		fprintf(pf4,"%s\n",fa->name);
		fprintf(pf4,"%.2lf %.2lf %.2lf\n",fa->calcu,fa->linal,fa->engl);
		fa=fa->next;
	}
	fclose(pf1);
	fclose(pf2);
	fclose(pf3);
	fclose(pf4);
	return 0;
}
