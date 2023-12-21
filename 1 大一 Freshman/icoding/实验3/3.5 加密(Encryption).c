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
Encrypted message: Hello, world!
*/
#include <stdio.h>
#include <string.h>

int main() {
  char str[100];
  int shift = 0, len = 0;

  fgets(str, sizeof(str), stdin); // 使用fgets获取字符串
  len = strlen(str);              // 获取字符串长度

  scanf("%d", &shift);
  shift = shift % 26; // 确保移位在1-25之间
  for (int i = 0; i < len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') { // 加密小写字母
      str[i] = (str[i] - 'a' + shift) % 26 + 'a';
      // 加密，若小写字母超过'z'，则从'a'算起
    } else if (str[i] >= 'A' && str[i] <= 'Z') { // 加密大写字母
      str[i] = (str[i] - 'A' + shift) % 26 + 'A';
    }
    // 对于非字母字符，不做处理，直接输出
  }

  printf("Encrypted message: %s", str); // 输出加密后的字符串
  return 0;                             // 程序结束
}