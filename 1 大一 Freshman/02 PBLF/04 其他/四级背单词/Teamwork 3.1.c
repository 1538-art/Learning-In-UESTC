#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>

int wordSizeText;//�ļ�����ȷ���ʵĳ���
int wordSizeInput;//���뵥�ʵĳ���
//ȫ�ֱ�������ÿ������������ʹ�õı���

void input(char write[])//�������뵥��
{
	char ch; 
	printf("input word:");
	wordSizeInput = 0;
	//ch = getchar();
	//�����ַ������ж�ȡ��һ���ַ�Ȼ�����whileѭ��
	while (isspace(ch = getchar()))
		;
		while (ch != '\n')
		{
			write[wordSizeInput++] = ch;//�ַ������ȡ
			//wordSizeInput��ʱ��Ϊ�ַ����ĳ��ȣ���ʱ�Ѿ����浽��ȫ�ֱ�������
			ch = getchar();//��ȡ��һ���ַ�
		}
}

int judge(char word[16], char write[16]) //�Ƚ�����ĵ��ʺ���ȷ�ĵ��ʣ��ó����,return: 1����������ȷ  0�����������
{
	int i;
	if(wordSizeText != wordSizeInput)
		return 0;
	for (i = 0; i<wordSizeText; i++)
	{
		if (word[i] != write[i])
			return 0;
	}	

	return 1;
}

int main()//��������ʼ
{

	//int res = 1;
	int mode ;
	int i,number = 1;
	char ch;
	long location;
	long getLocation;
	char word[16];
	char write[16];

	FILE* fp;
	FILE* record;
	
	system("color f4");
	printf("By team 4     UESTC     \n");
	printf("���ļ�����ģʽ������ 1 \n");
	printf("���������ģʽ������ 2 \n");
	printf("����������ģʽ������ 3 \n");
	printf("��ѡ��ģʽ(�˳��밴q): ");
	if (scanf("%d",&mode) == 1)
	{
		if (mode == 1)
		{
			for (i = 0; i <= 20; i++)
				printf("***");		

			printf("\nplease according to the Chinese word,write the English word\n\n");

			/*****************************�ؼ�����********************************/
			record = fopen("word\\record.txt","a+");

			if(record == NULL)		
				printf("fail to open record.txt!");
			
			fscanf(record, "%ld", &getLocation);//��ȡ��һ�εĽ��Ȳ���ӡ
			//printf("\n getLocation:%d \n",getLocation);
			fclose(record);
			
			fp = fopen("word\\word.txt","rb");//���ļ������·�������ļ�ָ��
			if(fp == NULL)
			printf("fail to open word.txt!");
			fseek(fp, getLocation, SEEK_SET);    //ʹ�ļ���λ����һ�ε�λ��
			//�浵
			/*fseek(�ļ�ָ�룬ƫ������set�ļ���ͷ/end�ļ���β/cur�ļ���ǰλ��)*/	
			
			
			while (1)//����ѭ������������break�������һֱѭ����ȥ������1����ʡ�Բ�д
			{
				printf("%d. ", number);//ָ�ӵ�һ�����ʿ�ʼ
				wordSizeText = 0;
				ch = fgetc(fp);//��ȡָ��fpָ����ļ����ַ������ļ�ָ��Ų����һ���ַ������Ҹ�ֵ�och
				while (ch != ' ')//ÿ�У���ȡ�ո�֮ǰ�����ݣ�����������Ҫ�ĵ���
				{
					word[wordSizeText++] = ch;//ΪwordSizeText���м��������ҵ�ѭ�����������¼���
					ch = fgetc(fp);
				}
				//������wordSizeInputһ��

				while (ch != '\n')//ÿ�У��ո�֮����֮ǰ�ĵ��ʾ��Ƕ�Ӧ���ʵ���������
				{
					putchar(ch);
					ch = fgetc(fp);
				}	
				printf("\n");

				while(1)
				{
					input(write);//����һ������
					
					if(!judge(word, write))//����ĵ��ʺ��ļ�����ȷ�ĵ��ʽ��жԱ�
						{									
							printf(" wrong\n");
							printf("*1.����  *q.�˳�\n*");					
							int choose;
							if (scanf("%d",&choose) != 1)						
								break;						
						}
					
					else
						{
							printf("true,very good!\n");
							break;
						}
				}

				printf("\n*1.����  *q.�˳�\n*");					
				int b;
				if (scanf("%d",&b) != 1)				
					break;
				
				number++;//����һ������

				/*    ���ȼ�¼    */
				location = ftell(fp);    //ftell���ص�ǰ�ļ���ȡ���ĸ�λ����

				record = fopen("word\\record.txt", "w+");
				if(record == NULL)
					printf("failed to open record.txt!");
			
				fprintf(record,"%ld", location);
				fclose(record);
			}
		}
		else if (mode == 2)
		{
			for (i = 0; i <= 20; i++)
				printf("***");		

			printf("\nplease according to the Chinese word,write the English word\n\n");

			/*****************************�ؼ�����********************************/
			record = fopen("word\\word\\record.txt","a+");

			if(record == NULL)		
				printf("fail to open record.txt!");
			
			fscanf(record, "%ld", &getLocation);//��ȡ��һ�εĽ��Ȳ���ӡ
			//printf("\n getLocation:%d \n",getLocation);
			fclose(record);
			
			fp = fopen("word\\word\\word_random.txt","rb");//���ļ������·�������ļ�ָ��
			if(fp == NULL)
			printf("fail to open word.txt!");
			fseek(fp, getLocation, SEEK_SET);    //ʹ�ļ���λ����һ�ε�λ��
			//�浵
			/*fseek(�ļ�ָ�룬ƫ������set�ļ���ͷ/end�ļ���β/cur�ļ���ǰλ��)*/	
			
			
			while (1)//����ѭ������������break�������һֱѭ����ȥ������1����ʡ�Բ�д
			{
				printf("%d. ", number);//ָ�ӵ�һ�����ʿ�ʼ
				wordSizeText = 0;
				ch = fgetc(fp);//��ȡָ��fpָ����ļ����ַ������ļ�ָ��Ų����һ���ַ������Ҹ�ֵ�och
				while (ch != ' ')//ÿ�У���ȡ�ո�֮ǰ�����ݣ�����������Ҫ�ĵ���
				{
					word[wordSizeText++] = ch;//ΪwordSizeText���м��������ҵ�ѭ�����������¼���
					ch = fgetc(fp);
				}
				//������wordSizeInputһ��

				while (ch != '\n')//ÿ�У��ո�֮����֮ǰ�ĵ��ʾ��Ƕ�Ӧ���ʵ���������
				{
					putchar(ch);
					ch = fgetc(fp);
				}	
				printf("\n");

				while(1)
				{
					input(write);//����һ������
					
					if(!judge(word, write))//����ĵ��ʺ��ļ�����ȷ�ĵ��ʽ��жԱ�
						{									
							printf(" wrong\n");
							printf("*1.����  *q.�˳�\n*");					
							int choose;
							if (scanf("%d",&choose) != 1)						
								break;						
						}
					
					else
						{
							printf("true,very good!\n");
							break;
						}
				}

				printf("\n*1.����  *q.�˳�\n*");					
				int b;
				if (scanf("%d",&b) != 1)				
					break;
				
				number++;//����һ������

				/*    ���ȼ�¼    */
				location = ftell(fp);    //ftell���ص�ǰ�ļ���ȡ���ĸ�λ����

				record = fopen("word\\word\\record.txt", "w+");
				if(record == NULL)
					printf("failed to open record.txt!");
			
				fprintf(record,"%ld", location);
				fclose(record);
			}
		}
		else if (mode == 3)
		{
			for (i = 0; i <= 20; i++)
				printf("***");		

			printf("\nplease according to the Chinese word,write the English word\n\n");

			/*****************************�ؼ�����********************************/
			record = fopen("word\\word\\word\\record.txt","a+");

			if(record == NULL)		
				printf("fail to open record.txt!");
			
			fscanf(record, "%ld", &getLocation);//��ȡ��һ�εĽ��Ȳ���ӡ
			//printf("\n getLocation:%d \n",getLocation);
			fclose(record);
			
			fp = fopen("word\\word\\word\\wordsix.txt","rb");//���ļ������·�������ļ�ָ��
			if(fp == NULL)
			printf("fail to open word.txt!");
			fseek(fp, getLocation, SEEK_SET);    //ʹ�ļ���λ����һ�ε�λ��
			//�浵
			/*fseek(�ļ�ָ�룬ƫ������set�ļ���ͷ/end�ļ���β/cur�ļ���ǰλ��)*/	
			
			
			while (1)//����ѭ������������break�������һֱѭ����ȥ������1����ʡ�Բ�д
			{
				printf("%d. ", number);//ָ�ӵ�һ�����ʿ�ʼ
				wordSizeText = 0;
				ch = fgetc(fp);//��ȡָ��fpָ����ļ����ַ������ļ�ָ��Ų����һ���ַ������Ҹ�ֵ�och
				while (ch != ' ')//ÿ�У���ȡ�ո�֮ǰ�����ݣ�����������Ҫ�ĵ���
				{
					word[wordSizeText++] = ch;//ΪwordSizeText���м��������ҵ�ѭ�����������¼���
					ch = fgetc(fp);
				}
				//������wordSizeInputһ��

				while (ch != '\n')//ÿ�У��ո�֮����֮ǰ�ĵ��ʾ��Ƕ�Ӧ���ʵ���������
				{
					putchar(ch);
					ch = fgetc(fp);
				}	
				printf("\n");

				while(1)
				{
					input(write);//����һ������
					
					if(!judge(word, write))//����ĵ��ʺ��ļ�����ȷ�ĵ��ʽ��жԱ�
						{									
							printf(" wrong\n");
							printf("*1.����  *q.�˳�\n*");					
							int choose;
							if (scanf("%d",&choose) != 1)						
								break;						
						}
					
					else
						{
							printf("true,very good!\n");
							break;
						}
				}

				printf("\n*1.����  *q.�˳�\n*");					
				int b;
				if (scanf("%d",&b) != 1)				
					break;
				
				number++;//����һ������

				/*    ���ȼ�¼    */
				location = ftell(fp);    //ftell���ص�ǰ�ļ���ȡ���ĸ�λ����

				record = fopen("word\\word\\word\\record.txt", "w+");
				if(record == NULL)
					printf("failed to open record.txt!");
			
				fprintf(record,"%ld", location);
				fclose(record);
			}
		}
		
	}
}
