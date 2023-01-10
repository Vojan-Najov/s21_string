#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *ptr = NULL;
  if (src != NULL && str != NULL && start_index <= s21_strlen(src)) {
    ptr =
        (char *)malloc(sizeof(char) * (s21_strlen(src) + s21_strlen(str) + 1));
    if (ptr != NULL) {
      s21_strncpy(ptr, src, start_index);
      *(ptr + start_index) = '\0';
      s21_strcat(ptr, str);
      s21_strcat(ptr, src + start_index);
    }
  }
  return (void *)ptr;
}
