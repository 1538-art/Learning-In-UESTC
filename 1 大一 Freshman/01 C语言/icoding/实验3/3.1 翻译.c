/*
翻译（Translation）

编写程序可以把字母格式的电话号码翻译成数值格式：

Enter phone number: CALLATT

2255288

如果没有电话在身边,参考这里给出的字母在键盘上的对应关系：（2=ABC，3=DEF，4=GHI，5=JKL，6=MNO，7=PQRS，8=TUV，9=WXYZ）原始电话号码中的非字母字符（例如数字或标点符号）保持不变：

Enter phone number: 1-800-COL-LECT1-800-265-5328

可以假设任何用户输入的字母都是大写字母。

输出范例：

Enter phone number: 1-DCKS-A2D-OLED

1-3257-223-6533
*/
#include <stdio.h>
int main() {
  char a;
  while (a != '\n') {
    a = getchar(); // 循环获取输入的字符
    switch (a) {
    case 'A':
    case 'B':
    case 'C':
      a = 2;
      printf("2");
      break;
    case 'D':
    case 'E':
    case 'F':
      a = 3;
      printf("3");
      break;
    case 'G':
    case 'H':
    case 'I':
      a = 4;
      printf("4");
      break;
    case 'J':
    case 'K':
    case 'L':
      a = 5;
      printf("5");
      break;
    case 'M':
    case 'N':
    case 'O':
      a = 6;
      printf("6");
      break;
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
      a = 7;
      printf("7");
      break;
    case 'T':
    case 'U':
    case 'V':
      a = 8;
      printf("8");
      break;
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
      a = 9;
      printf("9");
      break;
    default:
      printf("%c", a);
    }
  }
  return 0;
}