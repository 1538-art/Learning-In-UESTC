/*
有两个不包含空格的字符串 s1 和 s2，如果 s2 是 s1 的逆序，那么 s1 和 s2
互为镜像。
例如："abcde"和"edcba"互为镜像，而"abcde"和"edcb"不是，"abcde"和"edcbA"也不是。
已定义好函数 is_mirror，该函数判断两个字符串是否互为镜像。函数原型为： int
is_mirror(char *s1, char *s2); 如果 s1 和 s2 互为镜像，函数返回 1；否则返回
0。
请根据上述描述，编写程序，要求如下。
编写main()函数，其功能是：从键盘输入两个字符串（使用scanf），调用 is_mirror
判断输入的串是否为镜像。如果是，输出yes；否则输出 no。
提示：注意不要使用野指针！。
*/                                                                             \
#include<stdio.h>
#include <stdlib.h>
// is_mirror函数已实现，只需完成main函数即可
int is_mirror(char *s1, char *s2); // 请不要删除，否则编译不通过
int main() {
  char s1[101], s2[101];
  scanf("%s", s1); // scanf不读取'\n'，gets要
  scanf("%s", s2);
  if (is_mirror(s1, s2)) {
    printf("yes\n");
  } else {
    printf("no\n");
  }
  return 0;
}