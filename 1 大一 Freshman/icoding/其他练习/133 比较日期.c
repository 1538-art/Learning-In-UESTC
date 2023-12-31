/*
编写程序，提升用户输入两个日期，然后显示哪一个日期更早
示例如下
输入：
Enter first date（mm/dd/yy）：12/6/22
Enter second date（mm/dd/yy）：1/9/22
----------------------------------------------------
输出：
1/9/22 is earlier than 12/6/22
*/
#include <stdio.h>

int main() {
  int m1, d1, y1;
  int m2, d2, y2;

  printf("Enter first date (mm/dd/yy): ");
  scanf("%d/%d/%d", &m1, &d1, &y1);
  printf("Enter second date (mm/dd/yy): ");
  scanf("%d/%d/%d", &m2, &d2, &y2);

  if (y1 < y2 || (y1 == y2 && m1 < m2) || (y1 == y2 && m1 == m2 && d1 < d2)) {
    printf("%d/%d/%d is earlier than %d/%d/%d\n", m1, d1, y1, m2, d2, y2);
  } else {
    printf("%d/%d/%d is earlier than %d/%d/%d\n", m2, d2, y2, m1, d1, y1);
  }
  return 0;
}
