/*
键值对数组排序
一. 已知条件
键值对的数据结构 键值对(key-value pair)可以用C语言的结构来描述：
typedef struct {
    char key[30];  //用字符串表示的键
    int value;     //基于简化的目的，数值的类型是int
} pair;
在此基础上，用键值对数组来存储更多的数据。
pair kv[128];  //kv是键值对类型的数组。元素的键无重复。
字符串比较函数 两个字符串进行值比较的标准库函数原型如下：
int strcmp(const char *s, const char *t);
这个函数的功能是：比较两个字符串的字典序大小。如果s>t，函数返回正值；如果s<t，返回负值；如果相等，返回0。
二. 任务
请补全排序函数sort_kv的编码。该函数的原型如下：
void sort_kv(pair kv[], int n);
此函数的功能是：
利用冒泡排序法，按照键值（注：是个字符串）的大小对长度为n的数组kv进行升序排序。
三. 测试用例
测试程序 测试程序已经写好，并保证输入的有效性。你不必自行编写。
测试程序的功能是：
先读入键值对数组长度，然后依次读入键值对。
调用你补全的函数sort_kv，然后如下格式输出排序结果：
(键1=>值1)(键2=>值2)...(键n=>值n)
测试用例举例
用例 输入
5
pear 30
apple 100
pineapple 20
orange 80
durian 10
输出
(apple=>100)(durian=>10)(orange=>80)(pear=>30)(pineapple=>20)
四. 要求
请在框架文件中完成任务。
请将你的代码写在//TODO和//END OF TODO这对标记之间。
请勿修改框架中的任何已有内容。
/*
1.
本题需要的数据较多。因此，为了避免你在本地调试时反复输入，已将测试用例写在了一个数据文件q6.in中，其内容如下：
5
pear 30
apple 100
pineapple 20
orange 80
durian 10
上述数据产生的输出是：
(apple=>100)(durian=>10)(orange=>80)(pear=>30)(pineapple=>20)
2. 如果这个文件不存在，那么你就要从键盘手动输入。
3. 如果你的程序编译后是a.out，那在命令行里，你可以这样运行程序 a.out < q6.in
，避免重复从键盘输入
*/
#include <stdio.h>
#include <string.h>
typedef struct {
  char key[30]; // 用字符串表示的键
  int value;    // 基于简化的目的，数值的类型是int
} pair;
/*
 * 用冒泡排序法对键值对数组按键进行排序（升序）
 *
 * 参数说明：
 *      - kv：int[]，键值对数组
 *      - n：int，数组长度
 * 返回值说明：
 *      - 无
 */
void sort_kv(pair kv[], int n) {
  // TODO
  // END OF TODO
}
pair kv[128]; // kv是键值对类型的数组
static void print_kv(pair kv[], int n) {
  for (int i = 0; i < n; ++i)
    printf("(%s=>%d)", kv[i].key, kv[i].value);
  putchar('\n');
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%s%d", kv[i].key, &kv[i].value);
  sort_kv(kv, n);
  print_kv(kv, n);
  return 0;
}
* /
#include <stdio.h>
#include <string.h>
    typedef struct {
  char key[30]; // 用字符串表示的键
  int value;    // 基于简化的目的，数值的类型是int
} pair;
void sort_kv(pair kv[], int n) {
  // TODO
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (strcmp(kv[j].key, kv[j + 1].key) > 0) {
        pair temp = kv[j];
        kv[j] = kv[j + 1];
        kv[j + 1] = temp;
      }
    }
  }
  // END OF TODO
}
pair kv[128]; // kv是键值对类型的数组
static void print_kv(pair kv[], int n) {
  for (int i = 0; i < n; ++i)
    printf("(%s=>%d)", kv[i].key, kv[i].value);
  putchar('\n');
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%s%d", kv[i].key, &kv[i].value);
  sort_kv(kv, n);
  print_kv(kv, n);
  return 0;
}
