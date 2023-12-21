/*
三角形面积
题目编号：188
一. 已知条件
秦九韶公式
给定三个边长a、b、c。如果这三条边能构成一个三角形，那么该三角形的面积可以由秦九韶公式求出：
s = (a + b + c) / 2.0
area = sqrt(s * (s - a) * (s - b) * (s - c))
三角形任意两边之和大于第三边。
求平方根函数sqrt 该函数的原型如下：
double sqrt(double x);
其功能是：求数x的平方根。你可以在程序中直接调用它。
二. 任务
请补全函数area。该函数的原型如下：
double area(double a, double b, double c);
此函数的功能是：判断给定的边长a、b、c是否能构成三角形。
如果能，计算并返回三角形的面积。
如果不能，返回任意负值。
三. 测试用例
测试程序 测试程序已经写好，并保证输入的有效性。你不必自行编写。
测试程序的功能是：
从键盘输入三条边长。各输入项间用空格隔开。
调用你补全的函数area，得到结果。
如果结果是正值，则按%.2lf格式输出面积；否则输出invalid。
测试用例举例
用例1 输入 3 4 5 输出 6.00
用例2 输入 1 2 3 输出 invalid
四. 要求
请在框架文件中完成任务。
请将你的代码写在//TODO和//END OF TODO这对标记之间。
请勿修改框架中的任何已有内容。
#include <math.h>
#include <stdio.h>
*
 * 求三角形面积函数area
 * 参数说明：
 *      - a、b、c都是三角形的边长。
 * 返回值说明：
 *      - 如果a、b、c能构成三角形，则返回面积。
 *      - 否则，返回任意负值。
 *
double area(double a, double b, double c) {
  // TODO
  // END OF TODO
}
int main() {
  float a, b, c;
  scanf("%f %f %f", &a, &b, &c);
  double res = area(a, b, c);
  if (res < 0)
    printf("invalid");
  else
    printf("%.2lf", res);
}
*/
#include <math.h>
#include <stdio.h>
double area(double a, double b, double c) {
  // 判断是否能构成三角形
  if (a + b <= c || a + c <= b || b + c <= a) {
    return -1;
  }
  // 计算半周长
  double s = (a + b + c) / 2.0;
  // 使用秦九韶公式计算面积
  return sqrt(s * (s - a) * (s - b) * (s - c));
}
int main() {
  float a, b, c;
  scanf("%f %f %f", &a, &b, &c);
  double res = area(a, b, c);
  if (res < 0)
    printf("invalid");
  else
    printf("%.2lf", res);
}
