/*
出现次数（Number Occurrences）

修改如下程序，使其打印⼀份列表，显示出每个数字在数中出现的次数。

输出范例：

Enter a number: 41271092

Digit:	      0	1	2	3	4	5	6	7 8	9
Occurrences:	1	2	2	0	1	0	0 1 0	1
*/
#include <stdio.h> // 引入标准输入输出库
int main() {       // 主函数
  int a[10] = {0}; // 定义一个长度为10的整数数组a，初始值都为0
  char c;          // 定义一个字符变量c
  while (1) {      // 无限循环
    c = getchar(); // 从标准输入读取一个字符
    if (c == '\n') // 如果读取到换行符
      break;       // 跳出循环
    a[c - '0']++;
    // 将字符转换为数字(ASCII)，并将其存储在数组a中对应的位置，同时该位置的值加1
  }
  printf("Digit:0 1 2 3 4 5 6 7 8 9\n"); // 打印数组a的数字和出现次数
  printf("Occurrences:");                // 打印字符串"Occurrences："
  for (int i; i < 10; i++)               // 循环遍历数组a的每个元素
    printf("%d ", a[i]);                 // 打印元素及其出现次数
  return 0;                              // 返回0，表示程序执行成功
}