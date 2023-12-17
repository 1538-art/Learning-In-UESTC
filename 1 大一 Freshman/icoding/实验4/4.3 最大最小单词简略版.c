/*最大最小单词简略版（The Biggest and Smallest Words）

编写程序找出一组单词中“最小”单词和“最大”单词。

用户输入单词后，程序根据字典顺序决定排在最前面和最后面的单词。

当用户输入4个字母的单词时，程序停止读入。假设所有单词都不超过20个字母。

输出范例1：
Enter word: dog
Enter word: zebra
Enter word: rabbit
Enter word: catfish
Enter word: walrus
Enter word: cat
Enter word: fish


Smallest word: cat
Largest word zebra


输出范例2：


Enter word: computer
Enter word: ink
Enter word: light
Enter word: bookrack
Enter word: book


Smallest word: book
Largest word: light*/
#include <stdio.h>
#include <string.h>

int main() {

  char current[21]; // 存储当前单词，最后一个用于储存结束符'\0'
  char max[21], min[21]; // 存储最大单词和最小单词

  scanf("%s", current); // 读入第一个单词
  strcpy(max, current); // 将第一个单词赋值给最大单词和最小单词
  strcpy(min, current);

  for (;;) {
    scanf("%s", current); // 读入下一个单词

    if (strlen(current) != 4) { // 如果单词长度不是4，继续

      if (strcmp(current, max) >=
          0) { // 如果当前单词排序大于等于最大单词，更新最大单词
        strcpy(max, current);
      }
      if (strcmp(current, min) <=
          0) { // 如果当前单词排序小于等于最小单词，更新最小单词
        strcpy(min, current);
      }
    }

    else { // 比较完之后退出
      if (strcmp(current, max) >=
          0) { // 如果当前单词排序大于等于最大单词，更新最大单词
        strcpy(max, current);
      }
      if (strcmp(current, min) <=
          0) { // 如果当前单词排序小于等于最小单词，更新最小单词
        strcpy(min, current);
      }

      break; // 读取到单词后退出循环
    }
  }

  printf("Smallest word: %s\n", min); // 输出最小单词
  printf("Largest word: %s\n", max);  // 输出最大单词
  return 0;
}
