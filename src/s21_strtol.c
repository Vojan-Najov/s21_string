#include <ctype.h>
#include <errno.h>
#include <limits.h>

#include "s21_string.h"

static const unsigned char digit_table[] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   255, 255,
    255, 255, 255, 255, 255, 10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
    20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,
    35,  255, 255, 255, 255, 255, 255, 10,  11,  12,  13,  14,  15,  16,  17,
    18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,
    33,  34,  35,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255};

long long int s21_str_to_integer(const char *nptr, long int width,
                                 char **endptr, int base) {
  int sign = 0;
  const unsigned char *str = (unsigned char *)nptr;
  const unsigned char *digits = (unsigned char *)digit_table;
  long long int n = 0;

  if (base < 0 || base > 36 || base == 1) {
    errno = EINVAL;
  } else {
    while (isspace(*str)) {
      ++str;
    }
    if (width > 0 && (*str == '+' || *str == '-')) {
      sign = (*str++ == '-');
      --width;
    }
    if (width > 0 && (base == 0 || base == 16) && (*str == '0')) {
      ++str;
      --width;
      if (width > 0 && (*str == 'x' || *str == 'X')) {
        ++str;
        --width;
        base = 16;
#if defined(__MUSL__)
        if (digits[*str] >= base) {
          errno = EINVAL;
        }
#endif
      } else if (base == 0) {
        base = 8;
      }
    } else if (width > 0) {
      if (base == 0) {
        base = 10;
      }
      if (digits[*str] >= base) {
        errno = EINVAL;
      }
    }
    if (sign) {
      while (width > 0 && digits[*str] < base && n >= LLONG_MIN / base &&
             base * n >= LLONG_MIN + digits[*str]) {
        n = n * base - digits[*str];
        ++str;
        --width;
      }
    } else {
      while (width > 0 && digits[*str] < base && n <= LLONG_MAX / base &&
             base * n <= LLONG_MAX - digits[*str]) {
        n = n * base + digits[*str];
        ++str;
        --width;
      }
    }
    if (width > 0 && digits[*str] < base) {
      while (digits[*str] < base) {
        ++str;
      }
      errno = ERANGE;
      if (sign) {
        n = LLONG_MIN;
      } else {
        n = LLONG_MAX;
      }
    }
  }
  if (endptr != NULL) {
    *endptr = (char *)str;
  }

  return (n);
}

long long int s21_strtoll(const char *nptr, char **endptr, int base) {
  long long num;

  num = s21_str_to_integer(nptr, INT_MAX, endptr, base);

  return (num);
}

long int s21_strtol(const char *nptr, char **endptr, int base) {
  long long int num;

  num = s21_str_to_integer(nptr, INT_MAX, endptr, base);
  if (num > (long long int)LONG_MAX) {
    num = (long long int)LONG_MAX;
  } else if (num < (long long int)LONG_MIN) {
    num = (long long int)LONG_MIN;
  }

  return ((long int)num);
}

unsigned long long int s21_str_to_unsigned(const char *nptr, long int width,
                                           char **endptr, int base) {
  unsigned long long int sign = 0;
  const unsigned char *str = (unsigned char *)nptr;
  const unsigned char *digits = (unsigned char *)digit_table;
  unsigned long long n = 0;

  if (base < 0 || base > 36 || base == 1) {
    errno = EINVAL;
  } else {
    while (isspace(*str)) {
      ++str;
    }
    if (width > 0 && (*str == '+' || *str == '-')) {
      sign = -(*str++ == '-');
      --width;
    }
    if (width > 0 && (base == 0 || base == 16) && (*str == '0')) {
      ++str;
      --width;
      if (width > 0 && (*str == 'x' || *str == 'X')) {
        ++str;
        --width;
        base = 16;
#if defined(__MUSL__)
        if (digits[*str] >= base) {
          errno = EINVAL;
        }
#endif
      } else if (base == 0) {
        base = 8;
      }
    } else if (width > 0) {
      if (base == 0) {
        base = 10;
      }
      if (digits[*str] >= base) {
        errno = EINVAL;
      }
    }
    while (width > 0 && digits[*str] < base && n <= ULLONG_MAX / base &&
           base * n <= ULLONG_MAX - digits[*str]) {
      n = n * base + digits[*str];
      ++str;
      --width;
    }
    if (width > 0 && digits[*str] < base) {
      while (digits[*str] < base) {
        ++str;
      }
      errno = ERANGE;
      n = ULLONG_MAX;
      sign = 0;
    }
  }
  if (endptr != NULL) {
    *endptr = (char *)str;
  }

  return (sign ? ~n + 1 : n);
}

unsigned long long int s21_strtoull(const char *nptr, char **endptr, int base) {
  unsigned long long int num;

  num = s21_str_to_unsigned(nptr, INT_MAX, endptr, base);

  return (num);
}

unsigned long int s21_strtoul(const char *nptr, char **endptr, int base) {
  unsigned long long int num;

  num = s21_str_to_unsigned(nptr, INT_MAX, endptr, base);
  if (num > (unsigned long long int)ULONG_MAX) {
    num = (unsigned long long int)ULONG_MAX;
  }

  return ((unsigned long int)num);
}
