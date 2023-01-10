#include "s21_string.h"

size_t s21_itoa(int num, char *buf) {
  int n = num;
  size_t len = 0;

  if (n == 0) {
    *buf++ = '0';
    *buf = '\0';
    len = 1;
  } else {
    while (n) {
      ++len;
      n /= 10;
    }
    if (num < 0) {
      ++len;
      buf[0] = '-';
    }
    size_t offset = len;
    buf[offset] = '\0';
    while (num) {
      int rem = num % 10;
      num /= 10;
      rem = rem > 0 ? rem : -rem;
      buf[--offset] = rem + '0';
    }
  }

  return (len);
}
