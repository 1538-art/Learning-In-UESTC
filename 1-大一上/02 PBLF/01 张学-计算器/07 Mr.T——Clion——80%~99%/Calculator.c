//
// Created by Thomas on 2023/11/28.
//

#include "Calculator.h"

void ClearArray(char a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = '\0';
    }
}

Bool IsSign(char a) {   //不需要再根据上一个字符判断正负号了
    switch (a) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '(':
        case ')':
        case 's':
        case 'i':
        case 'n':
        case 'c':
        case 'o':
        case 'a':
        case 'b':
        case 't':
        case '\n':
            return TRUE;
        default:
            return FALSE;
    }
}

Bool IsIncluded(char a) {
    switch (a) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        case '.':
        case '-':
        case '+':
        case '*':
        case '/':
        case '(':
        case ')':
        case '^':
        case 's':   //sin
        case 'c':   //cos
        case 't':   //tan
        case 'a':   //abs
            return TRUE;
        default:
            return FALSE;
    }
}

Bool IsLatterPriorToFormer(char former, char latter) {  // ( + - * / ^
    switch (latter) {
        case '^':
            if (former == '^')return FALSE;
            else return TRUE;
        case '*':
        case '/':
            if (former == '*' || former == '/' || former == '^') return FALSE;
            else return TRUE;
        case '+':
        case '-':
            if (former == '(') return TRUE;
            else return FALSE;
        default:
            return FALSE;
    }
}

void CalculateTwoNum(double *former, double *latter, char sign) {
    switch (sign) {
        case '-':
            *former -= *latter;
            break;
        case '*':
            *former *= *latter;
            break;
        case '/': {
            if (*latter == 0) {
                printf("0 can't be divisor!");
                exit(-1);
            }
            *former /= *latter;
        }
            break;
        case '^': {
            if (*former == 0 && *latter < 1) {
                printf("0的非正数次幂无意义！");
                exit(-1);
            }
            *former = pow(*former, *latter);
        }
            break;
        default:    //加法
            *former += *latter;
    }
}