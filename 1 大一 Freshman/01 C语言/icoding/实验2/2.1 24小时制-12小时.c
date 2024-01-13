/*
24小时制-12小时制转换(24-hour to 12-hour)

编写一个程序，要求用户输入 24 小时制的时间，将其转换为 12 小时制的格式。

Enter a 24-hour time: 21:11
Equivalent 12-hour time: 9:11 PM

Enter a 24-hour time: 0:01
Equivalent 12-hour time: 12:01 AM

注意，不要把12:00显示为0:00。
*/
#include <stdio.h>
int main() {
  int a, b, c;
  scanf("%d:%d", &a, &b);
  c = a - 12;
  if (a > 12) // 判断a是否大于12，大于12则表示是下午，否则表示是上午
    printf("Equivalent 12-hour time: %d:%.2d PM\n", c, b);
  else if (a < 12) {
    if (a == 0)
      printf("Equivalent 12-hour time: %d:%.2d AM\n", a + 12, b);
    else
      printf("Equivalent 12-hour time: %d:%.2d AM\n", a, b);
  } else if (a == 12)
    printf("Equivalent 12-hour time: %d:%.2d PM\n", a, b);
  return 0;
}
