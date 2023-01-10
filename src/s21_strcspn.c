#include "s21_string.h"

s21_size_t s21_strcspn(const char *s, const char *reject) {
  const char *ptr = s;

  while (*ptr && s21_strchr(reject, *ptr) == S21_NULL) {
    ++ptr;
  }

  return (ptr - s);
}
