#include "s21_string.h"

s21_size_t s21_strspn(const char *s, const char *accept) {
  const char *ptr = s;

  while (*ptr && s21_strchr(accept, *ptr) != S21_NULL) {
    ++ptr;
  }

  return (ptr - s);
}
