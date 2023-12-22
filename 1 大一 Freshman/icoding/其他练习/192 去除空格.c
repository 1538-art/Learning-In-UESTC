/*
去除字符串首尾的所有空格
题目编号：192
一. 已知条件
首尾空格去除 一个字符串的首尾可能存在多个无用的空格。例如：
"   this is    a   test.    "
现在需要将这个字符串首尾所有的空格去除，但字符串中间的空格要原样保留。结果是这样的：
"this is    a   test."
这个结果将保存到另一个字符串中。
思路 对于原始字符串s和结果字符串t：
指针p从s开头向后，找到第一个非空格字符；
指针q从s尾部向前，找到第一个非空格字符；
将指针p、q之间的字符复制到t中；
字符串t封尾。
提示：如何找到字符串的尾部？
二. 任务
请补全函数trim的编码。该函数的原型如下：
void trim(char *s, char *t);
此函数的功能是：
去除字符串s首尾所有空格，但s中间的空格原样保留。
结果保存到字符串t中。
三. 测试用例
测试程序 测试程序已经写好，并保证输入的有效性。你不必自行编写。
测试程序的功能是：
从键盘输入首尾、中间可能带有空格的字符串，去掉行尾的'\n'，用'\0'封尾。测试程序保证没有全是空格的输入。
调用你补全的函数trim，得到结果，并按如下格式输出： (去掉首尾空格的字符串)
加上()的作用是为了让结果一目了然。
测试用例举例
用例 输入 this is a test. 输出 this is a test.
注：输入输出背景加深是为了能看清两端空格的存在。
四. 要求
请在框架文件中完成任务。
请将你的代码写在//TODO和//END OF TODO这对标记之间。
请勿修改框架中的任何已有内容。
#include <stdio.h>
#include <string.h>
 对于原始字符串s和结果字符串t：
    - 指针p从s开头向后，找到第一个非空格字符；
    - 指针q从s尾部向前，找到第一个非空格字符；
    - 将指针p、q之间的字符复制到t中；
    - 字符串t封尾。
 * 去除字符串两端空格的函数trim
 * 将字符串开头和末尾的所有空格字符去除
 *
 * 参数说明：
 *      - s：char*，原始字符串
 *      - t：char*，去掉所有首尾空格后的字符串
 * 返回值说明：
 *      - 无
void trim(char *s, char *t) {
  // TODO
  // END OF TODO
}
#define MAXN 512
extern void trim(char *s, char *t);
int main() {
  char s[MAXN + 1], t[MAXN + 1];
  fgets(s, MAXN, stdin);
  char *p = strchr(s, '\n');
  if (p)
    *p = '\0';
  trim(s, t);
  printf("(%s)\n", t);
  return 0;
}
*/
#include <stdio.h>
#include <string.h>
void trim(char *s, char *t) {
  char *p = s;
  char *q = s + strlen(s) - 1; // 使q指针指向最后一个字符（strlen不包含\0符号）
  while (*p == ' ')
    ++p; // 找到第一个不是空格的字符

  while (*q == ' ')
    --q; // 找到最后一个不是空格的字符

  while (p <= q) { // 将两个指针之间的字符复制到数组t中
    *t = *p;
    ++t;
    ++p;
  }
  *t = '\0'; // 字符串以\0结尾
}
#define MAXN 512
extern void trim(char *s, char *t);
int main() {
  char s[MAXN + 1], t[MAXN + 1];
  fgets(s, MAXN, stdin);
  char *p = strchr(s, '\n'); // 获取第一个换行符
  if (p)
    *p = '\0'; // 将其换为字符串结束符
  trim(s, t);
  printf("(%s)\n", t);
  return 0;
}
