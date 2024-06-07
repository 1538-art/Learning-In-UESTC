#include "dsstring.h" //请不要删除，否则检查不通过

int str_compare(const char *ptr1, const char *ptr2) {
  while (*ptr1 == *ptr2 || *ptr1 + 32 == *ptr2 || *ptr2 + 32 == *ptr1) {
    if (*ptr1 == '\0') return 0;
    (ptr1)++;
    (ptr2)++;
  }
  return (*ptr1 - *ptr2);
  
}