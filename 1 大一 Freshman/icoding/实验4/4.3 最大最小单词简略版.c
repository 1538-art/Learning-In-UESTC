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

#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

int main() {

  char current[21];
  char max[21], min[21];

  scanf("%s", current);
  strcpy(max, current);
  strcpy(min, current);
  for (;;) {
    scanf("%s", current);
    if (strlen(current) != 4) {

      if (strcmp(current, max) >= 0) {

        strcpy(max, current);
      }
      if (strcmp(current, min) <= 0) {
        strcpy(min, current);
      }
    }

    else {
      if (strcmp(current, max) >= 0) {

        strcpy(max, current);
      }
      if (strcmp(current, min) <= 0) {
        strcpy(min, current);
      }

      break;
    }
  }
  printf("Smallest word: %s\n", min);
  printf("Largest word: %s\n", max);
  return 0;
}