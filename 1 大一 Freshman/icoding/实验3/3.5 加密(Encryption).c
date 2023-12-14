/*题目：

已知的最古⽼的⼀种加密技术是凯撒加密（得名于 Julius
caesar）。该⽅法把⼀条消息中的每个字⺟⽤字⺟表中固定距离之后的那个字⺟来替代。（如果越过了字⺟Z，会绕回到字⺟表的起始位置。例如，如果每个字⺟都⽤字⺟表中两个位置之后的字⺟代替，那么Y就被替换为A，Z就被替换为B。）

编写程序⽤凯撒加密⽅法对消息进⾏加密。⽤户输⼊待加密的消息和移位计数（字⺟移动的位置数⽬）：
Enter message to be encrypted: Go ahead, make my day.
Enter shift amount (1-25): 3
Encrypted message: Jr dkhdg, pdnh pb gdb.

注意,当⽤户输⼊26与移位计数的差值时,程序可以对消息进⾏解密:

Enter message to be encrypted: Jr dkhdg, pdnh pb gdb.
Enter shift amount (1-25): 23
Encrypted message: Go ahead, make my day

不是字⺟的那些字符不要改动。此外，加密时不要改变字⺟的⼤⼩写。

输出范例：

Enter message to be encrypted: Hello, world!
Enter shift amount (1-25): 3
Encrypted message: Khoor, zruog!

Enter message to be encrypted: Khoor, zruog!
Enter shift amount (1-25): 23
Encrypted message: Hello, world!*/
#include <stdio.h>
#include <string.h>

int main() {
  char c[1000]; // 定义一个字符数组存储输入的字符串
  int wy, l;    // wy表示要移动的距离，l表示字符串的长度

  gets(c); // 读取输入的字符串
  l = strlen(c) -
      1; // 计算字符串的长度，减1是因为字符串的最后一个字符是换行符，不算在长度中
  scanf("%d", &wy); // 读取要移动的距离

  for (int i = 0; i <= l; i++) // 遍历字符串中的每个字符
  {
    if (c[i] >= 'a' && c[i] <= 'z') // 如果字符是小写字母
    {
      if (c[i] + wy <= 'z')      // 如果移动后的字符在'z'范围内
        printf("%c", c[i] + wy); // 输出移动后的字符
      else // 如果移动后的字符超出了'z'的范围
        printf("%c", c[i] + wy - 26); // 输出对应的大写字母

      continue; // 跳过本次循环，进入下一个字符的移动
    }

    if (c[i] >= 'A' && c[i] <= 'Z') // 如果字符是大写字母
    {
      if (c[i] + wy <= 'Z')      // 如果移动后的字符在'Z'范围内
        printf("%c", c[i] + wy); // 输出移动后的字符
      else // 如果移动后的字符超出了'Z'的范围
        printf("%c", c[i] + wy - 26); // 输出对应的小写字母

      continue; // 跳过本次循环，进入下一个字符的移动
    }

    printf("%c", c[i]); // 如果字符不是字母，直接输出
  }

  return 0; // 程序结束
}