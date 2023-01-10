#include "s21_string.h"

size_t s21_llitoa(long long int num, char *buf) {
  size_t len = 0;
  long long int n = num;

  if (num == 0) {
    *buf++ = '0';
    *buf = '\0';
    ++len;
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
