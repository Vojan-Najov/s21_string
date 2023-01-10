#include <stdlib.h>

#include "s21_string.h"

void *s21_to_lower(const char *str) {
  int offset = 'A' - 'a';
  char *ptr = NULL;

  if (str != NULL) {
    ptr = (char *)malloc(sizeof(char) * (s21_strlen(str) + 1));
    if (ptr != NULL) {
      s21_strcpy(ptr, str);
      for (size_t i = 0; ptr[i]; ++i) {
        if (ptr[i] >= 'A' && ptr[i] <= 'Z') {
          ptr[i] -= offset;
        }
      }
    }
  }

  return ((void *)ptr);
}
