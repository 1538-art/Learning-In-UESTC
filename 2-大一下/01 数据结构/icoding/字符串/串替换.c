/*
串替换

不调用库函数，自己实现字符串替换操作，函数原型为：

int str_replace(const char *in, char *out, int outlen, const char *oldstr, const char *newstr);
参数说明:

in， 原始字符串，保持不变
out, 存放替换结果的字符串
outlen，out空间的大小
oldstr，要替换的旧字符串
newstr，替换成的新字符串
函数返回成功替换的次数，即有多少个子串被成功替换
在替换过程中，任何情况下所得字符串（及结束符）不应该超过 outlen，
 如果某次替换所得字符串的长度超过 outlen，则不进行这次替换操作，整个替换操作结束。如：
原始串为 "aaabbbccc"，outlen 为14, oldstr 为 "c"，newstr 为 "333" 时，
 两次替换后得 "aaabbb333333c"，此时字符串占用空间为14字节。
如果再进行替换，则会超出 out 所占用的空间，所以停止替换操作。
 此时函数应该返回 2, out指向的串为 "aaabbb333333c"
再如：原始串为 "aaabbbccc"，outlen 为10, oldstr 为 "b"，newstr 为 "123456"，
 进行替换后所得的串长度为14，与结束符一共占 15 个字节，超过outlen的10字节，此时不进行替换，函数应该返回 0。
 */

#include <stdio.h>
#include <stdlib.h>
#include "dsstring.h"

// 计算从pos开始，字符串长度
int str_len(const char *str, int pos) {
  int count = 0;
  for (int i = pos; str[i] != '\0'; i++) count++;
  return count;
}


int str_replace(const char *in, char *out, int outlen, const char *oldstr, const char *newstr) {
  int count = 0; // 记录替换次数
  int out_i = 0; // 输出字符串的下标
  int newstrLen = str_len(newstr, 0); // 新字符串的长度
  
  // 初始化输出字符串为全零
  for (int i = 0; i < outlen; i++) {
    out[i] = '\0';
  }
  
  for (int i = 0; i < outlen;) {
    int j = 0;
    // 匹配 oldstr
    while (oldstr[j] != '\0') {
      if (oldstr[j] != in[i]) {
        i = i - j + 1;
        break;
      }
      j++;
      i++;
    }
    
    if (oldstr[j] != '\0') {
      // 不匹配，输出当前字符
      out[out_i] = in[i - 1];
      out_i++;
    } else {
      if (str_len(out, 0) + str_len(in, i) + newstrLen < outlen) {
        // 匹配，替换为 newstr
        for (int k = 0; newstr[k] != '\0';) {
          out[out_i] = newstr[k];
          out_i++;
          k++;
        }
        
        count++;
      } else {
        // 输出剩余字符
        while (j != 0) {
          out[out_i] = in[i - j];
          out_i++;
          j--;
        }
        
      }
    }
    // 输入字符串已经到末尾，结束循环
    if (in[i] == '\0') {
      out_i++;
      break;
    }
    
  }
  return count;
}