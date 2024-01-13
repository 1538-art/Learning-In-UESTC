/*
风速等级与描述（Wind Speed）

下面是用于测量风力等级的简化版，编写一个程序，要求用户输入风速（海里/小时），然后显示相应的描述。

速率（海里/⼩时）	描述
小于 1	Calm（无风）
1~3	    Light air（轻风）
4~27	Breeze（微风）
28~47	Gale（⼤风）
48~63	Storm（暴风）
⼤于63	Hurricane（飓风）
输出范例：Enter a wind speed: 1

Light air

Enter a wind speed: 27

Breeze
*/
#include <stdio.h>
int main() {
  int a;
  scanf("%d", &a);
  if (a < 1)
    printf("Calm");
  else if (a < 4)
    printf("Light air");
  else if (a < 28)
    printf("Breeze");
  else if (a < 48)
    printf("Gale");
  else if (a < 64)
    printf("Storm");
  else
    printf("Hurricane");
  return 0;
}