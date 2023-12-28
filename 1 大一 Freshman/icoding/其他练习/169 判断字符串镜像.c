/*
有两个不包含空格的字符串 s1 和 s2，如果 s2 是 s1 的逆序，那么 s1 和 s2
互为镜像。

例如："abcde"和"edcba"互为镜像，而"abcde"和"edcb"不是，"abcde"和"edcbA"也不是。

根据上述描述，编写程序，要求如下：
编写一个函数判断两个字符串是否互为镜像。函数原型为： int is_mirror(char *s1,
char *s2);
如果s1和s2互为镜像，函数返回1；否则返回0。要求仅使用指针，并且不调用任何字符串处理库函数。
*/
#include <stdio.h>
#include <stdlib.h>
int is_mirror(char *s1, char *s2) {
  int len1 = 0, len2 = 0;
  while (s1[len1] != '\0') {
    len1++;
  }
  while (s2[len2] != '\0') {
    len2++;
  }
  if (len1 != len2)
    return 0;
  for (int i = 0; i < len1; i++) {
    if (s1[i] != s2[len1 - i - 1])
      return 0;
  }
  return 1;
}