#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *str = NULL;
  const char *begin;
  const char *end;

  if (src != NULL && trim_chars != NULL) {
    begin = src;
    while (*begin && s21_strchr(trim_chars, *begin) != NULL) ++begin;
    if (!*begin) {
      str = (char *)calloc(1, sizeof(char));
    } else {
      end = src + s21_strlen(src) - 1;
      while (end != begin && s21_strchr(trim_chars, *end) != NULL) {
        --end;
      }
      size_t len = end - begin + 1;
      str = (char *)malloc(sizeof(char) * (len + 1));
      if (str != NULL) {
        s21_memcpy(str, begin, len);
        str[len] = '\0';
      }
    }
  }

  return ((void *)str);
}
