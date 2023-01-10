#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>

#include "s21_string.h"

#define STAR_FLAG 0x0001
#define H_FLAG 0x0002
#define HH_FLAG 0x0004
#define L_FLAG 0x0008
#define LL_FLAG 0x0010
#define LLL_FLAG 0x0020
#define PTR_FLAG 0x0040
#define SSCNFERROR 0x1000
#define INPUT_FAIL 0
#define MATCH_SUCCESS 1
#define MATCH_FAIL 2
#define FORMAT_FAIL 3

#define SCAN_NOT_SUPPRESSED(flags) (!((flags)&STAR_FLAG))

static const char *parse_format(const char *format, int *flags,
                                long int *width);
static int pop_char(va_list ap, const char **str, int flags, long int width);
static int pop_integer(va_list ap, const char **str, int flags, long int width,
                       int base);
static int pop_unsigned(va_list ap, const char **str, int flags, long int width,
                        int base);
static void pop_count(va_list ap, int flags, long long int count);

int s21_sscanf(const char *str, const char *format, ...) {
  const char *start = str;
  int count = 0;
  va_list ap;
  long int width = 0;
  int flags = 0;
  int status = MATCH_SUCCESS;

  va_start(ap, format);
  while (isspace(*format)) ++format;

  while (status == MATCH_SUCCESS && *format) {
    if (*format == '%') {
      format = parse_format(format, &flags, &width);
      if (flags & SSCNFERROR) {
        status = FORMAT_FAIL;
      } else {
        switch (*format++) {
          case '%':
            if (*str++ == '%') {
              continue;
            } else {
              status = MATCH_FAIL;
            }
            break;
          case 'c':
            status = pop_char(ap, &str, flags, width);
            break;
          case 'd':
            status = pop_integer(ap, &str, flags, width, 10);
            break;
          case 'i':
            status = pop_integer(ap, &str, flags, width, 0);
            break;
          case 'o':
            status = pop_unsigned(ap, &str, flags, width, 8);
            break;
          case 'x':
          case 'X':
            status = pop_unsigned(ap, &str, flags, width, 16);
            break;
          case 'p':
            flags |= PTR_FLAG;
            status = pop_unsigned(ap, &str, flags, width, 16);
            break;
          case 'n':
            pop_count(ap, flags, (long long int)(str - start));
            continue;
            break;
        }
        if (status == MATCH_SUCCESS && SCAN_NOT_SUPPRESSED(flags)) {
          ++count;
        }
      }
    } else {
      if (!*str) {
        status = INPUT_FAIL;
      } else if (*format == *str) {
        ++format;
        ++str;
      } else if (isspace(*format)) {
        while (isspace(*format)) ++format;
      } else {
        status = MATCH_FAIL;
      }
    }
  }
  va_end(ap);
#ifdef __GLIBC__
  if (status == INPUT_FAIL && !count) {
#else
  if ((status == INPUT_FAIL || status == FORMAT_FAIL) && !count) {
#endif
    count = -1;
  }
  return (count);
}

static const char *parse_format(const char *format, int *flags,
                                long int *width) {
  int flg = 0;
  long int wdth = 0;
  char *endptr;

  const char *length_str = "hlL";
  const char *specifiers = "cdieEfgGosuxXpn%";

  ++format;
  if (*format == '*') {
    flg |= STAR_FLAG;
    ++format;
  }
  errno = 0;
  wdth = s21_strtol(format, &endptr, 10);
  format = (const char *)endptr;
  if (wdth < 0) {
    flg = SSCNFERROR;
  }
  while (!(flg & SSCNFERROR) && s21_strchr(length_str, *format) != NULL) {
    switch (*format++) {
      case 'h':
        if (*format == 'h') {
          flg |= HH_FLAG;
          ++format;
        } else {
          flg |= H_FLAG;
        }
        break;
      case 'l':
        if (*format == 'l') {
          flg |= LL_FLAG;
          ++format;
        } else {
          flg |= L_FLAG;
        }
        break;
      case 'L':
        flg |= LLL_FLAG;
        break;
      case '\0':
        flg = SSCNFERROR;
        break;
    }
  }
  if (!(flg & SSCNFERROR) && s21_strchr(specifiers, *format) != NULL) {
    *flags = flg;
    *width = wdth;
  } else {
    *flags = SSCNFERROR;
  }

  return (format);
}

static int pop_char(va_list ap, const char **str, int flags, long int width) {
  char *ptr;
  const char *s = *str;
  int status = MATCH_SUCCESS;

  if (width < 1) {
    width = 1;
  }
  if (SCAN_NOT_SUPPRESSED(flags)) {
    ptr = (char *)va_arg(ap, char *);
  }
  if (*s) {
    while (*s && width-- > 0) {
      if (SCAN_NOT_SUPPRESSED(flags)) {
        *ptr++ = *s++;
      } else {
        ++s;
      }
    }
    *str = s;
  } else {
    status = INPUT_FAIL;
  }

  return (status);
}

static int pop_integer(va_list ap, const char **str, int flags, long int width,
                       int base) {
  void *ptr;
  const char *s = *str;
#ifndef __MUSL__
  long long int num;
#else
  unsigned long long int num;
#endif
  char *endptr = NULL;
  int status = MATCH_SUCCESS;

  if (width == 0) {
    width = LONG_MAX;
  }
  if (SCAN_NOT_SUPPRESSED(flags)) {
    ptr = (void *)va_arg(ap, void *);
  }
  if (*s) {
    errno = 0;
#ifndef __MUSL__
    num = s21_str_to_integer(s, width, &endptr, base);
#else
    num = s21_str_to_unsigned(s, width, &endptr, base);
#endif
    if (errno == EINVAL) {
      status = MATCH_FAIL;
    } else if (SCAN_NOT_SUPPRESSED(flags) && ptr != NULL) {
      if (flags & LL_FLAG) {
        *(long long int *)ptr = num;
      } else if (flags & L_FLAG) {
        *(long int *)ptr = (long int)num;
      } else if (flags & H_FLAG) {
        *(short int *)ptr = (short int)num;
      } else if (flags & HH_FLAG) {
        *(signed char *)ptr = (signed char)num;
      } else {
        *(int *)ptr = (int)num;
      }
    }
    *str = endptr;
  } else {
    status = INPUT_FAIL;
  }

  return (status);
}

static int pop_unsigned(va_list ap, const char **str, int flags, long int width,
                        int base) {
  void *ptr;
  const char *s = *str;
  unsigned long long int num;
  char *endptr = NULL;
  int status = MATCH_SUCCESS;

  if (width == 0) {
    width = LONG_MAX;
  }
  if (SCAN_NOT_SUPPRESSED(flags)) {
    ptr = (void *)va_arg(ap, void *);
  }
  if (*s) {
    errno = 0;
    num = s21_str_to_unsigned(s, width, &endptr, base);
    if (errno == EINVAL) {
      status = MATCH_FAIL;
    } else if (SCAN_NOT_SUPPRESSED(flags) && ptr != NULL) {
      if (flags & PTR_FLAG) {
        *(void **)ptr = (void *)(uintptr_t)num;
      } else if (flags & LL_FLAG) {
        *(unsigned long long int *)ptr = num;
      } else if (flags & L_FLAG) {
        *(unsigned long int *)ptr = (unsigned long int)num;
      } else if (flags & H_FLAG) {
        *(unsigned short int *)ptr = (unsigned short int)num;
      } else if (flags & HH_FLAG) {
        *(unsigned char *)ptr = (unsigned char)num;
      } else {
        *(unsigned int *)ptr = (unsigned int)num;
      }
    }
    *str = endptr;
  } else {
    status = INPUT_FAIL;
  }

  return (status);
}

static void pop_count(va_list ap, int flags, long long int count) {
  void *ptr;

  if (SCAN_NOT_SUPPRESSED(flags)) {
    ptr = (void *)va_arg(ap, void *);
    if (ptr != NULL) {
      if (flags & LL_FLAG) {
        *(long long int *)ptr = count;
      } else if (flags & L_FLAG) {
        *(long int *)ptr = (long int)count;
      } else if (flags & H_FLAG) {
        *(short int *)ptr = (short int)count;
      } else if (flags & HH_FLAG) {
        *(char *)ptr = (char)count;
      } else {
        *(int *)ptr = (int)count;
      }
    }
  }
}
