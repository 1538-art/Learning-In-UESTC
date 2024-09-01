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
#include <stdio.h> // 引入标准输入输出库

int main() {
  int days, week; // 定义两个整数变量days（天数）和week（起始日是星期几）
  scanf("%d%d", &days, &week); // 从用户输入中读取days和week的值

  for (int i = 1; i < week; i++) {
    printf("   "); // 打印三个空格，表示一个星期的间隔
  }

  for (int i = 1; i <= days; i++) {
    if (week > 7) {
      // 如果当前星期的数字已经超过了7，说明已经到了下一个星期的第一个日期
      printf("\n"); // 换行，开始下一星期的打印
      week = 1; // 将星期的数字重置为1，表示当前星期的第一个日期
    }

    if (i < 10) { // 如果当前的日期小于10，需要在日期前加上2个空格
      printf("  %d", i);
    } else { // 如果当前的日期大于等于10，先打印一个空格
      printf(" %d", i);
    }
    week++; // 当前星期的数字加1
  }

  return 0; // 函数返回0，表示程序正常结束
}
