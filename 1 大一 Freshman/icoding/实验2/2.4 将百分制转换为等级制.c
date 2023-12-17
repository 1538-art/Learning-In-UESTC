/*
将百分制转换为等级制（Centesimal-grade to Letter-grade）

利用switch语句编写一个程序，把用数字表示的成绩转化为字母表示的等级。

使用下面的等级评定规则：A为90~100，B为80~89，C为70~79，D为60~69，F为0~59。如果成绩大于100或小于0显示出错信息。

输出范例：
Enter numerical grade: 84
Letter grade: B

Enter numerical grade: -1
Error, grade must be between 0 and 100.

提示：把成绩拆分成 2 个数字，然后使用 switch 语句判定十位上的数字。
*/
#include <stdio.h>
int main() {
  int a, b;
  scanf("%d", &a); // 从标准输入读取一个整数，赋值给变量a

  // 判断a的值是否在0到100之间
  if (a < 0 || a > 100) {
    printf(
        "Error, grade must be between 0 and 100.\n"); // 如果a不在0到100之间，输出错误信息
    return 0; // 函数返回0，表示程序正常结束
  }
  b = a / 10; // 因为题目说判定十位上的数字，所以不用考虑小于10的数

  // 根据b的值判断a的等级
  switch (b) {
  case 9:
  case 10: // 如果b等于9或10，表示等级为A
    printf("Letter grade: A\n");
    break;
  case 8:
    printf("Letter grade: B\n"); // 如果b等于8，表示等级为B
    break;
  case 7:
    printf("Letter grade: C\n"); // 如果b等于7，表示等级为C
    break;
  case 6:
    printf("Letter grade: D\n"); // 如果b等于6，表示等级为D
    break;
  case 5:
  case 4:
  case 3:
  case 2:
  case 1:
  case 0: // 如果b等于0到4，表示等级为F
    printf("Letter grade: F\n");
    break;
  default:
    printf(
        "Error, grade must be between 0 and 100.\n"); // 如果b不在0到100之间，输出错误信息
  }

  return 0; // 函数返回0，表示程序正常结束
}