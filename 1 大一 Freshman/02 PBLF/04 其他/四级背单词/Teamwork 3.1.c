#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>

int wordSizeText;//文件中正确单词的长度
int wordSizeInput;//输入单词的长度
//全局变量，即每个函数都可以使用的变量

void input(char write[])//键盘输入单词
{
	char ch; 
	printf("input word:");
	wordSizeInput = 0;
	//ch = getchar();
	//输入字符串进行读取第一个字符然后进入while循环
	while (isspace(ch = getchar()))
		;
		while (ch != '\n')
		{
			write[wordSizeInput++] = ch;//字符逐个读取
			//wordSizeInput此时即为字符串的长度，此时已经保存到了全局变量当中
			ch = getchar();//读取下一个字符
		}
}

int judge(char word[16], char write[16]) //比较输入的单词和正确的单词，得出结果,return: 1代表输入正确  0代表输入错误
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

int main()//主函数开始
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
	printf("背四级单词模式请输入 1 \n");
	printf("背随机单词模式请输入 2 \n");
	printf("背六级单词模式请输入 3 \n");
	printf("请选择模式(退出请按q): ");
	if (scanf("%d",&mode) == 1)
	{
		if (mode == 1)
		{
			for (i = 0; i <= 20; i++)
				printf("***");		

			printf("\nplease according to the Chinese word,write the English word\n\n");

			/*****************************关键部分********************************/
			record = fopen("word\\record.txt","a+");

			if(record == NULL)		
				printf("fail to open record.txt!");
			
			fscanf(record, "%ld", &getLocation);//读取上一次的进度并打印
			//printf("\n getLocation:%d \n",getLocation);
			fclose(record);
			
			fp = fopen("word\\word.txt","rb");//打开文件（相对路径），文件指针
			if(fp == NULL)
			printf("fail to open word.txt!");
			fseek(fp, getLocation, SEEK_SET);    //使文件定位到上一次的位置
			//存档
			/*fseek(文件指针，偏移量，set文件开头/end文件结尾/cur文件当前位置)*/	
			
			
			while (1)//无限循环，除非遇到break，否则就一直循环下去，其中1可以省略不写
			{
				printf("%d. ", number);//指从第一个单词开始
				wordSizeText = 0;
				ch = fgetc(fp);//读取指针fp指向的文件的字符并将文件指针挪向下一个字符，并且赋值給ch
				while (ch != ' ')//每行，获取空格之前的内容，就是我们所要的单词
				{
					word[wordSizeText++] = ch;//为wordSizeText进行计数，并且当循环结束后重新计数
					ch = fgetc(fp);
				}
				//与上文wordSizeInput一样

				while (ch != '\n')//每行，空格之后换行之前的单词就是对应单词的中文释义
				{
					putchar(ch);
					ch = fgetc(fp);
				}	
				printf("\n");

				while(1)
				{
					input(write);//输入一个单词
					
					if(!judge(word, write))//输入的单词和文件中正确的单词进行对比
						{									
							printf(" wrong\n");
							printf("*1.继续  *q.退出\n*");					
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

				printf("\n*1.继续  *q.退出\n*");					
				int b;
				if (scanf("%d",&b) != 1)				
					break;
				
				number++;//到下一个单词

				/*    进度记录    */
				location = ftell(fp);    //ftell返回当前文件读取到哪个位置了

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

			/*****************************关键部分********************************/
			record = fopen("word\\word\\record.txt","a+");

			if(record == NULL)		
				printf("fail to open record.txt!");
			
			fscanf(record, "%ld", &getLocation);//读取上一次的进度并打印
			//printf("\n getLocation:%d \n",getLocation);
			fclose(record);
			
			fp = fopen("word\\word\\word_random.txt","rb");//打开文件（相对路径），文件指针
			if(fp == NULL)
			printf("fail to open word.txt!");
			fseek(fp, getLocation, SEEK_SET);    //使文件定位到上一次的位置
			//存档
			/*fseek(文件指针，偏移量，set文件开头/end文件结尾/cur文件当前位置)*/	
			
			
			while (1)//无限循环，除非遇到break，否则就一直循环下去，其中1可以省略不写
			{
				printf("%d. ", number);//指从第一个单词开始
				wordSizeText = 0;
				ch = fgetc(fp);//读取指针fp指向的文件的字符并将文件指针挪向下一个字符，并且赋值給ch
				while (ch != ' ')//每行，获取空格之前的内容，就是我们所要的单词
				{
					word[wordSizeText++] = ch;//为wordSizeText进行计数，并且当循环结束后重新计数
					ch = fgetc(fp);
				}
				//与上文wordSizeInput一样

				while (ch != '\n')//每行，空格之后换行之前的单词就是对应单词的中文释义
				{
					putchar(ch);
					ch = fgetc(fp);
				}	
				printf("\n");

				while(1)
				{
					input(write);//输入一个单词
					
					if(!judge(word, write))//输入的单词和文件中正确的单词进行对比
						{									
							printf(" wrong\n");
							printf("*1.继续  *q.退出\n*");					
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

				printf("\n*1.继续  *q.退出\n*");					
				int b;
				if (scanf("%d",&b) != 1)				
					break;
				
				number++;//到下一个单词

				/*    进度记录    */
				location = ftell(fp);    //ftell返回当前文件读取到哪个位置了

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

			/*****************************关键部分********************************/
			record = fopen("word\\word\\word\\record.txt","a+");

			if(record == NULL)		
				printf("fail to open record.txt!");
			
			fscanf(record, "%ld", &getLocation);//读取上一次的进度并打印
			//printf("\n getLocation:%d \n",getLocation);
			fclose(record);
			
			fp = fopen("word\\word\\word\\wordsix.txt","rb");//打开文件（相对路径），文件指针
			if(fp == NULL)
			printf("fail to open word.txt!");
			fseek(fp, getLocation, SEEK_SET);    //使文件定位到上一次的位置
			//存档
			/*fseek(文件指针，偏移量，set文件开头/end文件结尾/cur文件当前位置)*/	
			
			
			while (1)//无限循环，除非遇到break，否则就一直循环下去，其中1可以省略不写
			{
				printf("%d. ", number);//指从第一个单词开始
				wordSizeText = 0;
				ch = fgetc(fp);//读取指针fp指向的文件的字符并将文件指针挪向下一个字符，并且赋值給ch
				while (ch != ' ')//每行，获取空格之前的内容，就是我们所要的单词
				{
					word[wordSizeText++] = ch;//为wordSizeText进行计数，并且当循环结束后重新计数
					ch = fgetc(fp);
				}
				//与上文wordSizeInput一样

				while (ch != '\n')//每行，空格之后换行之前的单词就是对应单词的中文释义
				{
					putchar(ch);
					ch = fgetc(fp);
				}	
				printf("\n");

				while(1)
				{
					input(write);//输入一个单词
					
					if(!judge(word, write))//输入的单词和文件中正确的单词进行对比
						{									
							printf(" wrong\n");
							printf("*1.继续  *q.退出\n*");					
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

				printf("\n*1.继续  *q.退出\n*");					
				int b;
				if (scanf("%d",&b) != 1)				
					break;
				
				number++;//到下一个单词

				/*    进度记录    */
				location = ftell(fp);    //ftell返回当前文件读取到哪个位置了

				record = fopen("word\\word\\word\\record.txt", "w+");
				if(record == NULL)
					printf("failed to open record.txt!");
			
				fprintf(record,"%ld", location);
				fclose(record);
			}
		}
		
	}
}
