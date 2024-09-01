/*
还贷计算（Loan Balance）

编程计算第一、第二、第三个月还贷后剩余的贷款金额。

Enter amout of loan: 20000.00
Enter interest rate: 6.0
Enter monthly payment: 386.66

Balance remaining after first payment: $19713.34
Balance remaining after second payment: $19425.25
Balance remaining after third payment: $19135.71

提示：每个月的贷款余额减去还款金额后，还需要加上贷款余额与月利率的乘积。
月利率的计算方法是把用户输入的利率转换成百分数再除以12。
*/
#include <stdio.h>
int main(void) {
  float loan, rate, payment, a1, a2, a3, interest;

  scanf("%f", &loan);
  scanf("%f", &rate);
  scanf("%f", &payment);
  interest = rate / 100 / 12;
  a1 = loan * interest +
       (loan - payment); // 原本贷款的利息加上还款之后的剩余贷款
  a2 = a1 * interest + (a1 - payment);
  a3 = a2 * interest + (a2 - payment);
  printf("Balance remaining after first payment:%.2f\n", a1);
  printf("Balance remaining after second payment:%.2f\n", a2);
  printf("Balance remaining after third payment:%.2f\n", a3);

  return 0;
}