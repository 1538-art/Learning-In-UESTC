/*逆序（Reversal）

编写程序读一条消息，然后逆序打印出这条消息。

输出范例：


Enter a message: Don't get mad, get even.
Reversal is: .neve teg ,dam teg t'noD


Enter a message: Hello, world!
Reversal is: !dlrow ,olleH


提示：一次读取消息中的一个字符（用getchar函数），并且把这些字符存储在数组中，当数组写满或者读到字符
'\n' 时停止读入。*/

#include <stdio.h>

int main() {
  int i = 0;     // 定义一个变量i用于循环读取字符
  char a[20000]; // 定义一个字符数组a来存储读取的字符

  while (1) {
    a[i] = getchar(); // 读取一个字符并存储到a[i]
    if (a[i] == '\n') { // 如果读取到换行符，说明已经读取完毕，跳出循环
      break;
    }
    i++;
  }
  i--;
  printf("Reversal is: ");
  while (i >= 0) {
    printf("%c", a[i]);
    i--;
  }
  return 0; // 程序结束
}