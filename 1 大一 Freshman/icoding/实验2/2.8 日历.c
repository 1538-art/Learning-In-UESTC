/*
日历（Calendar Month）

编写程序显示单月的日历。用户指定这个月的天数和该月起始日是星期几。

输出范例：

Enter number of days in month: 31

Enter starting day of the week(1=Sun, 7=Sat): 3

日	一	 二	 三	 四	 五	 六
         1	 2	 3	 4	 5
 6	 7	 8	 9  10	11	12
13	14	15	16	17	18	19
20	21	22	23	24	25	26
27	28	29	30	31
*/
#include <stdio.h>       // 引入标准输入输出库
int main() {             // 主函数
  int days, start, week; // 定义三个整型变量days, start, week
  scanf("%d%d", &days, &start); // 从标准输入读取两个整数，分别赋值给days和start
  week = start; // 将start的值赋给week，表示当前是第几周
  printf("日 一 二 三 四 五 六\n"); // 输出日历的表头
  for (int i = 1; i < start; i++) { // 输出前start-1天
    printf("   ");                  // 输出3个空格
  }
  for (int i = 1; i <= days; i++) { // 循环输出从第1天到第days天
    if (week > 7) {                 // 如果当前是第8天或更多天
      printf("\n");                 // 换行
      week = 1;                     // 将周数重置为1
    }
    if (i < 10)          // 如果当前是第1天到第9天
      printf(" %d ", i); // 输出一个空格和一个数字
    else                 // 如果当前是第10天或更多天
      printf("%d ", i);  // 输出一个数字
    week++;              // 将周数加1
  }
  return 0; // 函数返回0，表示程序正常结束
}