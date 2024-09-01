#include "Calculator.h"

#define DEBUG 1 // 调试模式 1:开启 0:关闭
#define TEMP_SIZE 20

待添加：
1.三角函数、绝对值函数，sin->s, cos->c, tan->t,
    abs->a 2.读文件，多个表达式 * /

        int main() {
  char lastInput = '(',            // 上一个输入的字符
      input = '0',                 // 储存输入的字符
      numTemp[TEMP_SIZE],          // 数字字符暂存区
      signTemp[TEMP_SIZE];         // 运算符暂存区
  ClearArray(numTemp, TEMP_SIZE);  // 清空暂存区
  int numIndex = 0, signIndex = 0; // 暂存区字符序数
  Bool isLastSign = TRUE;          // 储存上一个字符是否为运算符
  int unmatchedParentheses = 0;    // 未配对的左括号数
  double number; // 将暂存区数字转化为double类型数字
  // 创建栈并判断是否成功
  Stack *pNumStack = StackConstruct(sizeof(double));
  Stack *pSignStack = StackConstruct(sizeof(char));
  if (pNumStack == NULL || pSignStack == NULL) {
    printf("Stack construction failed!");
    return -1;
  }

  while (1) {
    char endChar = '0';
    // 循环检测输入字符(一行)
    while (2) {
      input = getchar();
      if (input == '\n') {
        // 判断左右括号是否匹配
        if (unmatchedParentheses > 0) {
          printf("There's unmatched parenthesis!");
          return -1;
        } else if (unmatchedParentheses < 0) {
          printf("There's some thing wrong with parentheses!");
          return -1;
        }
        if (!isLastSign) {
          number = atof(numTemp);
          numIndex = 0;
          StackPush(pNumStack, &number);
#if DEBUG
          printf("Input:%lf\nInput end.\n", number);
#endif
        }
        // 计算最终结果
#if DEBUG
        int a = StackGetLength(pNumStack);
        int b = StackGetLength(pSignStack);
        printf("NumStack's length is %d\n", a);
        printf("SignStack's length is %d\n", b);
#endif
        while (StackGetLength(pSignStack) > 0) {
          double formerNum, latterNum;
          StackPop(pNumStack, &latterNum);
          StackPop(pNumStack, &formerNum);
          double temp = formerNum; // debug
          char sign;
          StackPop(pSignStack, &sign);
          CalculateTwoNum(&formerNum, &latterNum, sign);
          StackPush(pNumStack, &formerNum);
#if DEBUG
          printf("%lf%c%lf=%lf\n", temp, sign, latterNum, formerNum);
#endif
        }
        double result;
        StackPop(pNumStack, &result);
        printf("The result is %lf\n", result);
        lastInput = '(';
        break;
      }
      if (input == '$') {
        endChar = '$';
        break;
      }
      // 判断是否为合法字符
      if (!IsIncluded(input)) {
        printf("The input is incorrect\n");
        return -1;
      }
      if (input == '(')
        unmatchedParentheses++;
      else if (input == ')') {
        if (unmatchedParentheses > 0)
          unmatchedParentheses--;
        else {
          printf("Incorrect input:\")\"");
          return -1;
        }
      }
      // 判断是否为符号
      if (isLastSign) {
        Bool isThisSign = IsSign(input);
        isLastSign = isThisSign;
        if (!isThisSign) { // sign->number
          if (lastInput == ')' &&
              (input == '+' ||
               input == '-')) { // 解决右括号之后加减号被当作正负号
            if (StackGetLength(pSignStack) > 0 &&
                StackGetLength(pNumStack) > 1) {
              char formerSign; // 改进：与上面重复，可以考虑写成函数
              StackGetTop(pSignStack, &formerSign);
              if (!IsLatterPriorToFormer(formerSign, input)) {
                double formerNum, latterNum;
                StackPop(pNumStack, &latterNum);
                StackPop(pNumStack, &formerNum);
                double temp = formerNum; // debug
                char sign;
                StackPop(pSignStack, &sign);
                CalculateTwoNum(&formerNum, &latterNum, sign);
                StackPush(pNumStack, &formerNum);
                printf("%lf%c%lf=%lf\n", temp, sign, latterNum, formerNum);
              }
            }
            StackPush(pSignStack, &input);
#if DEBUG
            printf("SignStack:%c\n", input);
#endif
          } else {
            numTemp[numIndex++] = input;
          }
        } else { // sign->sign
          // 输入错误判断
          if (lastInput == ')' && input == '(') { // 两个括号之间缺少运算符
            printf("Sign missing between two parentheses!");
            return -1;
          }
          if (input == ')') {
            if (lastInput != ')') { // 右括号之前的符号(紧挨着)只能是右括号
              printf("A number was missing!");
              return -1;
            }
            char sign;
            StackPop(pSignStack, &sign);
            while (sign != '(') {
              double formerNum, latterNum;
              StackPop(pNumStack, &latterNum);
              StackPop(pNumStack, &formerNum);
              double temp = formerNum; // debug
              CalculateTwoNum(&formerNum, &latterNum, sign);
              StackPush(pNumStack, &formerNum);
#if DEBUG
              printf("%lf%c%lf=%lf\n", temp, sign, latterNum, formerNum);
#endif
              StackPop(pSignStack, &sign);
            }
          } else {                 // input不是右括号
            while (input != '(' && // 若input不是左括号且栈中元素足以做运算
                   StackGetLength(pSignStack) > 0 &&
                   StackGetLength(pNumStack) > 1) {
              // 保证多字符运算符完整和单字符运算符独立
              /*if (((lastInput == '*' || lastInput == '/' || lastInput == '+'
                 || lastInput == '-' || lastInput == '^' || lastInput == '(') &&
                   (input == 's' || input == 'i' || input == 'n' ||
                    input == 'c' || input == 'o' || input == 't' || input == 'a'
                 || input == 'n' || input == 'b'))
                  ||
                  ((input == '*' || input == '/' || input == '+' || input == '-'
                 || input == '^')
                   && (lastInput == 's' || lastInput == 'i' || lastInput == 'n'
                 || lastInput == 'c' || lastInput == 'o' || lastInput == 't' ||
                 lastInput == 'a' || lastInput == 'n' || lastInput == 'b')))
                 {}*/
              char formerSign; // 改进：与上面重复，可以考虑写成函数
              StackGetTop(pSignStack, &formerSign);
              if (!IsLatterPriorToFormer(formerSign, input)) {
                double formerNum, latterNum;
                StackPop(pNumStack, &latterNum);
                StackPop(pNumStack, &formerNum);
                double temp = formerNum; // debug
                char sign;
                StackPop(pSignStack, &sign);
                CalculateTwoNum(&formerNum, &latterNum, sign);
                StackPush(pNumStack, &formerNum);
#if DEBUG
                printf("%lf%c%lf=%lf\n", temp, sign, latterNum, formerNum);
#endif
              } else {
                break;
              }
            }
            // 若左括号后跟加减号，在其间加个“0”
            if ((input == '+' || input == '-') && lastInput == '(') {
              double a = 0;
              StackPush(pNumStack, &a);
            }
            StackPush(pSignStack, &input);
#if DEBUG
            printf("SignStack:%c\n", input);
#endif
          }
        }
      } else {
        Bool isThisSign = IsSign(input);
        isLastSign = isThisSign;
        if (!isThisSign) { // number->number
          numTemp[numIndex++] = input;
        } else { // number->sign
          // 先将暂存区数字转化并压入数字栈
          number = atof(numTemp);
          ClearArray(numTemp, TEMP_SIZE);
          numIndex = 0;
          StackPush(pNumStack, &number);
#if DEBUG
          printf("Input:%lf\n", number);
#endif
          // 再处理符号
          if (input == ')') {
            char sign;
            StackPop(pSignStack, &sign);
            while (sign != '(') {
              double formerNum, latterNum;
              StackPop(pNumStack, &latterNum);
              StackPop(pNumStack, &formerNum);
              double temp = formerNum; // debug
              CalculateTwoNum(&formerNum, &latterNum, sign);
              StackPush(pNumStack, &formerNum);
#if DEBUG
              printf("%lf%c%lf=%lf\n", temp, sign, latterNum, formerNum);
#endif
              StackPop(pSignStack, &sign);
            }
          } else {
            while (StackGetLength(pSignStack) > 0 &&
                   StackGetLength(pNumStack) > 1) {
              char formerSign; // 改进：与上面重复，可以考虑写成函数
              StackGetTop(pSignStack, &formerSign);
              if (!IsLatterPriorToFormer(formerSign, input)) {
                double formerNum, latterNum;
                StackPop(pNumStack, &latterNum);
                StackPop(pNumStack, &formerNum);
                double temp = formerNum; // debug
                char sign;
                StackPop(pSignStack, &sign);
                CalculateTwoNum(&formerNum, &latterNum, sign);
                StackPush(pNumStack, &formerNum);
#if DEBUG
                printf("%lf%c%lf=%lf\n", temp, sign, latterNum, formerNum);
#endif
              } else {
                break;
              }
            }
            StackPush(pSignStack, &input);
#if DEBUG
            printf("SignStack:%c\n", input);
#endif
          }
        }
      }
      lastInput = input;
    }
    // 清空栈，以免对下一个表达式造成干扰
    StackClear(pNumStack);
    StackClear(pSignStack);
    if (endChar == '$') {
      StackDestruct(pNumStack);
      StackDestruct(pSignStack);
      printf("The end!\n");
      return 0;
    }
  }
  /*//检测部分功能是否正常
  void *pNumStack;
  pNumStack = StackConstruct(sizeof(double));
  if (pNumStack == NULL)printf("Construction fails!\n");
  else printf("Construction done!\n");

  double a = 2.3, b = 1.5, c, d,e;
  StackPush(pNumStack, &a);
  StackPush(pNumStack, &b);
  StackPush(pNumStack, &b);
  printf("Length:%d\n", StackGetLength(pNumStack));
  StackGetTop(pNumStack, &c);
  printf("Top:%lf\n", c);
  if (!StackPop(pNumStack, &d))printf("Pop ERROR");
  else printf("Pop:%lf\n", d);
  if (!StackPop(pNumStack, &d))printf("Pop ERROR");
  else printf("Pop:%lf\n", d);
  if (!StackPop(pNumStack, &e))printf("Pop ERROR");
  else printf("Pop:%lf\n", e);
  if (StackIsEmpty(pNumStack)) {
      printf("Empty!\n");
      StackDestruct(pNumStack);
  }

  StackPush(pNumStack, &a);
  StackPush(pNumStack, &b);
  StackPush(pNumStack, &b);
  StackClear(pNumStack);
  if (StackIsEmpty(pNumStack)) {
      printf("Empty!\n");
      StackDestruct(pNumStack);
  }*/
  /*char a = '^', b = '*';
  double c = 2, d = 3;
  printf("%lf,%lf\n", c, d);
  if (!IsLatterPriorToFormer(a, b)) {
      CalculateTwoNum(&c, &d, a);
      printf("%lf\n", c);
  }*/
  return 0;
}
