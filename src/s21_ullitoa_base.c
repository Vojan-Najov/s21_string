#include "s21_string.h"

size_t s21_ullitoa_base(unsigned long long int n, unsigned int base,
                        const char *digits, char *buf) {
  size_t len = 0;
  unsigned long long num = n;

  if (base) {
    if (num == 0) {
      *buf++ = digits[0];
      *buf = '\0';
      ++len;
    } else {
      while (n) {
        ++len;
        n /= base;
      }
      size_t offset = len;
      buf[offset] = '\0';
      while (num) {
        int rem = num % base;
        num /= base;
        buf[--offset] = digits[rem];
      }
    }
  }

  return (len);
}
