#include "s21_string.h"

char *s21_strtok(char *src, const char *delim) {
  static char *ptr;
  char *str;

  if (src != S21_NULL) {
    ptr = src;
  }
  str = ptr;
  if (str != S21_NULL) {
    str += s21_strspn(str, delim);
    if (*str) {
      ptr = str + s21_strcspn(str, delim);
      if (*ptr) {
        *ptr++ = '\0';
      }
    } else {
      str = ptr = S21_NULL;
    }
  }

  return (str);
}
