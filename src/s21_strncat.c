#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;

  if (n) {
    ptr += s21_strlen(dest);
    while (n && *src) {
      *ptr++ = *src++;
      --n;
    }
    *ptr = '\0';
  }

  return (dest);
}
