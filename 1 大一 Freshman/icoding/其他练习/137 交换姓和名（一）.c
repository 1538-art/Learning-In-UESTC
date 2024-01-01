/*
在name指向的字符串中，存放着用户输入的英文“名姓”，
修改字符串：姓在前，然后跟一个逗号，接着是名的首字母，最后加一个点。
原始字符串可能包含无用的多个空格，函数要能处理。
函数原型如下：
void reverse_name(char *name);
*/
#include <stdio.h>

void reverse_name(char *name) {
  char temp[100], first[50], last[50];
  int i = 0, j = 0; // 定义两个整数变量i和j，分别用于循环计数

  while (name[i] == ' ')
    i++;                              // 跳过空格
  while (name[i]) {                   // 当name[i]不为空时，进入循环
    while (name[i] && name[i] != ' ') // 当name[i]不为空格时，继续读取字符
      temp[j++] = name[i++]; // 将name[i]添加到temp数组的j位置，并使i加1
    while (name[i] == ' ')
      i++; // 跳过空格
    if (name[i])
      temp[j++] = ' ';
    // 隔开两个单词，便于下面分割，最后面不加空格，以免被当做姓的一部分
  }
  temp[j] = '\0'; // 将temp数组的最后一个位置设置为空字符，表示字符串结束

  sscanf(temp, "%s %s", first, last);
  // 从temp中读取名字的各个部分（用空格分割），将结果存储在first和last中
  sprintf(name, "%s, %c.", last, first[0]); // 向name中写入处理后的字符串
}
