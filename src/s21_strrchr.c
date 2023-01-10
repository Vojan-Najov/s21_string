#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *ptr = S21_NULL;

  c = (unsigned char)c;
  while (*str) {
    if (*str == c) {
      ptr = (char *)str;
    }
    ++str;
  }
  if (c == '\0') {
    ptr = (char *)str;
  }

  return (ptr);
}
