/*
日期格式转化（Date Format Convention）

编写一个程序，以月/日/年（即
mm/dd/yy）的格式接受用户录入的日期信息，并以年月日（即yyyymmdd）的格式将其显示出来。

Enter a date (mm/dd/yyyy): 2/17/2011
You entered the date 20110217
*/
#include <stdio.h>
int main() {
  int mm, dd, yyyy;
  scanf("%d/%d/%d", &mm, &dd, &yyyy);
  printf("You entered the date %.4d%.2d%.2d", yyyy, mm, dd);

  return 0;
}