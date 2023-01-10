#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

#define DASH_FLAG 0x0001
#define PLUS_FLAG 0x0002
#define SPACE_FLAG 0x0004
#define OKTO_FLAG 0x0008
#define ZERO_FLAG 0x0010
#define STAR_FLAG 0x0020
#define DOT_FLAG 0x0040
#define HH_FLAG 0x0080
#define H_FLAG 0x0100
#define L_FLAG 0x0200
#define LL_FLAG 0x0400
#define LLL_FLAG 0x0800
#define SPTFERROR 0x1000
#define SPTFERANGE 0x2000

static const char *parse_format(va_list ap, const char *format, int *flags,
                                int *width, int *precision);
static int push_percent(char *buf, int flags, int width);
static int push_char(char *buf, va_list ap, int flags, int width);
static int push_wchar(char *buf, va_list ap, int flags, int width);
static int push_decimal(char *buf, va_list ap, int flags, int width,
                        int precision);
static int push_float(char *buf, va_list ap, int flags, int width,
                      int precision);
static int push_float_exponential(char *buf, va_list ap, int flags, int width,
                                  int precision, char expchar);
static int push_string(char *buf, va_list ap, int flags, int width,
                       int precision);
static int push_wstring(char *buf, va_list ap, int flags, int width,
                        int precision);
static int push_unsigned(char *buf, va_list ap, char specifier, int flags,
                         int width, int precision);
static int push_pointer(char *buf, va_list ap, int flags, int width,
                        int precision);
static void pop_current_count(va_list ap, int flags, int count);

int s21_sprintf(char *str, const char *format, ...) {
  char *buf = str;
  int count = 0;
  int offset = 0;
  int flags = 0;
  int width = 0;
  int precision = 0;
  va_list ap;

  va_start(ap, format);
  while (*format && offset >= 0) {
    if (*format == '%') {
      ++format;
      format = parse_format(ap, format, &flags, &width, &precision);
      if (flags & SPTFERROR) {
#if !defined(__APPLE__)
        count = -1;
#else
        if (flags & SPTFERANGE) {
          count = -1;
        }
#endif
        offset = -1;
      } else {
        switch (*format++) {
          case '%':
            offset = push_percent(buf, flags, width);
            break;
          case 'c':
            if (flags & L_FLAG) {
              offset = push_wchar(buf, ap, flags, width);
            } else {
              offset = push_char(buf, ap, flags, width);
            }
            break;
          case 's':
            if (flags & L_FLAG) {
              offset = push_wstring(buf, ap, flags, width, precision);
            } else {
              offset = push_string(buf, ap, flags, width, precision);
            }
            break;
          case 'i':
          case 'd':
            offset = push_decimal(buf, ap, flags, width, precision);
            break;
          case 'u':
            offset = push_unsigned(buf, ap, 'u', flags, width, precision);
            break;
          case 'o':
            offset = push_unsigned(buf, ap, 'o', flags, width, precision);
            break;
          case 'x':
            offset = push_unsigned(buf, ap, 'x', flags, width, precision);
            break;
          case 'X':
            offset = push_unsigned(buf, ap, 'X', flags, width, precision);
            break;
          case 'p':
            offset = push_pointer(buf, ap, flags, width, precision);
            break;
          case 'f':
            offset = push_float(buf, ap, flags, width, precision);
            break;
          case 'e':
            offset =
                push_float_exponential(buf, ap, flags, width, precision, 'e');
            break;
          case 'E':
            offset =
                push_float_exponential(buf, ap, flags, width, precision, 'E');
            break;
          case 'n':
            offset = 0;
            pop_current_count(ap, flags, count);
            break;
        }
        count = offset < 0 ? 0 : count;
        buf += offset > 0 ? offset : 0;
        count += offset;
      }
    } else {
      *buf++ = *format++;
      ++count;
    }
  }
#if defined(__APPLE__) || defined(__MUSL__)
  if (count < 0) {
    buf = str;
  }
#endif
  *buf = '\0';
  va_end(ap);

  return (count);
}

static const char *parse_format(va_list ap, const char *format, int *flags,
                                int *width, int *precision) {
  int flg = 0;
  int wdth = 0;
  int prec = 0;
  const char *flags_str = "-+ #0";
  const char *length_str = "hlL";
  const char *specifiers = "cdieEfgGosuxXpn%";
  const char *digits = "0123456789";

  while (!(flg & SPTFERROR) && s21_strchr(flags_str, *format) != NULL) {
    switch (*format++) {
      case '-':
        flg |= DASH_FLAG;
        break;
      case '+':
        flg |= PLUS_FLAG;
        break;
      case ' ':
        flg |= SPACE_FLAG;
        break;
      case '#':
        flg |= OKTO_FLAG;
        break;
      case '0':
        flg |= ZERO_FLAG;
        break;
      case '\0':
        --format;
        flg = SPTFERROR;
        break;
    }
  }
  if (!(flg & SPTFERROR) && *format == '*') {
    flg |= STAR_FLAG;
    wdth = va_arg(ap, int);
    ++format;
  } else if (!(flg & SPTFERROR)) {
    if (s21_isinteger(format)) {
      wdth = s21_atoi(format);
    } else {
      flg |= SPTFERROR | SPTFERANGE;
    }
    format += s21_strspn(format, digits);
  }
  if (!*format) {
    flg = SPTFERROR;
  }
  if (!(flg & SPTFERROR) && *format == '.') {
    flg |= DOT_FLAG;
    ++format;
    if (*format == '*') {
      flg |= STAR_FLAG;
      prec = va_arg(ap, int);
      ++format;
    } else {
      if (s21_isinteger(format)) {
        prec = s21_atoi(format);
      } else {
        flg |= SPTFERROR | SPTFERANGE;
      }
      format += s21_strspn(format, digits);
    }
  }
  if (!*format) {
    flg = SPTFERROR;
  }
  while (!(flg & SPTFERROR) && s21_strchr(length_str, *format) != NULL) {
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
        --format;
        flg |= SPTFERROR;
        break;
    }
  }
  if (!(flg & SPTFERROR) && s21_strchr(specifiers, *format) != NULL) {
    *flags = flg;
    *width = wdth;
    *precision = prec;
  } else {
    *flags = flg | SPTFERROR;
  }

  return (format);
}

static int push_percent(char *buf, int flags, int width) {
  int count = 0;
  char space = ' ';

#ifdef __APPLE__
  count = width > 0 ? width : 1;
  if (flags & DASH_FLAG) {
    *buf++ = '%';
  } else if (flags & ZERO_FLAG) {
    space = '0';
  }
  while (--width > 0) {
    *buf++ = space;
  }
  if (!(flags & DASH_FLAG)) {
    *buf++ = '%';
  }
#elif defined(__GLIBC__)
  (void)flags;
  (void)width;
  (void)space;
  count = 1;
  *buf = '%';
#else
  (void)width;
  (void)space;
  if (flags || width) {
    count = -1;
  } else {
    count = 1;
    *buf = '%';
  }
#endif

  return (count);
}

static int push_char(char *buf, va_list ap, int flags, int width) {
  char c;
  char space = ' ';
  char *ptr = buf;

  c = (unsigned char)va_arg(ap, int);
  if (flags & DASH_FLAG) {
    *buf++ = c;
  } else if (flags & ZERO_FLAG) {
#ifdef __APPLE__
    space = '0';
#else
    (void)space;
#endif
  }
  while (--width > 0) {
    *buf++ = space;
  }
  if (!(flags & DASH_FLAG)) {
    *buf++ = c;
  }

  return ((int)(buf - ptr));
}

static int push_wchar(char *buf, va_list ap, int flags, int width) {
  wchar_t wc;
  char space = ' ';
  char *ptr = buf;
  int wclen = 0;
  char wcbuf[4];

  wc = (wchar_t)va_arg(ap, int);
  wclen = s21_wctomb(wcbuf, wc);
  if (wclen > 0) {
    width -= wclen;
    if (flags & DASH_FLAG) {
      s21_memcpy(buf, wcbuf, wclen);
      buf += wclen;
    } else if (flags & ZERO_FLAG) {
#ifdef __APPLE__
      space = '0';
#else
      (void)space;
#endif
    }
    while (width-- > 0) {
      *buf++ = space;
    }
    if (!(flags & DASH_FLAG)) {
      s21_memcpy(buf, wcbuf, wclen);
      buf += wclen;
    }
  }

  return (wclen >= 0 ? (int)(buf - ptr) : -1);
}

static int push_decimal(char *buf, va_list ap, int flags, int width,
                        int precision) {
  long long int n;
  char *ptr = buf;
  char nbuf[64] = "";
  char *nbuf_ptr = nbuf;
  int nlen;
  char sign = 0;
  int zero_pending = 0;
  int space_pending = 0;

  if (flags & LL_FLAG) {
    n = (long long int)va_arg(ap, long long int);
  } else if (flags & L_FLAG) {
    n = (long int)va_arg(ap, long int);
  } else if (flags & H_FLAG) {
    n = (short int)va_arg(ap, int);
  } else if (flags & HH_FLAG) {
    n = (char)va_arg(ap, int);
  } else {
    n = (int)va_arg(ap, int);
  }
  nlen = (int)s21_llitoa(n, nbuf);

  if (n < 0) {
    sign = '-';
    ++nbuf_ptr;
    --nlen;
  } else if (flags & PLUS_FLAG) {
    sign = '+';
  } else if (flags & SPACE_FLAG) {
    sign = ' ';
  }
  if (flags & DOT_FLAG) {
    zero_pending = precision - nlen;
    if (n == 0) {
      ++zero_pending;
      ++nbuf_ptr;
      nlen = 0;
    }
    zero_pending = zero_pending > 0 ? zero_pending : 0;
  }
  space_pending = width - nlen - zero_pending - (sign ? 1 : 0);
  space_pending = space_pending > 0 ? space_pending : 0;
  if (!(flags & DASH_FLAG) && (flags & ZERO_FLAG) && !(flags & DOT_FLAG)) {
    zero_pending = space_pending;
    space_pending = 0;
  }
  if ((flags & DASH_FLAG) || ((flags & ZERO_FLAG) && !(flags & DOT_FLAG))) {
    if (sign) {
      *buf++ = sign;
    }
    s21_memset(buf, '0', zero_pending);
    buf += zero_pending;
    s21_strcpy(buf, nbuf_ptr);
    buf += nlen;
    s21_memset(buf, ' ', space_pending);
    buf += space_pending;
  } else {
    s21_memset(buf, ' ', space_pending);
    buf += space_pending;
    if (sign) {
      *buf++ = sign;
    }
    s21_memset(buf, '0', zero_pending);
    buf += zero_pending;
    s21_strcpy(buf, nbuf_ptr);
    buf += nlen;
  }

  return (buf - ptr);
}

static int push_string(char *buf, va_list ap, int flags, int width,
                       int precision) {
  char *ptr = buf;
  char *str;
  int len;
  char space = ' ';
#if defined(__GLIBC__)
  int isnull = 0;
#endif

  str = (char *)va_arg(ap, char *);
  if (str == NULL) {
    str = "(null)";
#if defined(__GLIBC__)
    isnull = 1;
#endif
  }
  len = (int)s21_strlen(str);
  if ((flags & DOT_FLAG) && (precision < len)) {
#if defined(__GLIBC__)
    len = isnull ? 0 : precision;
#else
    len = precision;
#endif
  }
  width -= len;
  width = width > 0 ? width : 0;
  if (!(flags & DASH_FLAG)) {
#ifdef __APPLE__
    if (flags & ZERO_FLAG) {
      space = '0';
    }
#endif
    s21_memset(buf, space, width);
    buf += width;
  }
  s21_memcpy(buf, str, len);
  buf += len;
  if (flags & DASH_FLAG) {
    s21_memset(buf, space, width);
    buf += width;
  }

  return (buf - ptr);
}

static int push_wstring(char *buf, va_list ap, int flags, int width,
                        int precision) {
  wchar_t *ws;
  int isnull = 0;
  char space = ' ';
  char mbbuf[4];
  int mbsize;
  int mblen = 0;
  int count = 0;

  ws = (wchar_t *)va_arg(ap, wchar_t *);
  if (ws == NULL) {
    ws = L"(null)";
#if defined(__APPLE__)
    isnull = 0;
#else
    isnull = 1;
#endif
  }
  for (wchar_t *tmp = ws; *tmp; ++tmp) {
    int mblen_tmp = 0;
    if (*tmp < 0x7F) {
      mblen_tmp += 1;
    } else if (MB_CUR_MAX == 1) {
      if (*tmp < 0x100) {
        mblen += 1;
      } else {
        mblen = -1;
        break;
      }
    } else if (*tmp < 0x7FF) {
      mblen_tmp += 2;
    } else if (*tmp < 0xFFFF) {
      mblen_tmp += 3;
    } else if (*tmp < 0x10FFFF) {
      mblen_tmp += 4;
    }
    if (flags & DOT_FLAG) {
      precision -= mblen_tmp;
      if (precision >= 0) {
        mblen += mblen_tmp;
      } else {
        break;
      }
    } else {
      mblen += mblen_tmp;
    }
  }
  mblen = mblen < 0 ? 0 : mblen;
  if (isnull && mblen < (int)(sizeof("(null)") - 1)) {
    mblen = 0;
  }
  width -= mblen;
  width = width > 0 ? width : 0;
  if (!(flags & DASH_FLAG)) {
#ifdef __APPLE__
    if (flags & ZERO_FLAG) {
      space = '0';
    }
#endif
    s21_memset(buf, space, width);
    count += width;
    buf += width;
  }
  while (mblen > 0) {
    mbsize = s21_wctomb(mbbuf, *ws++);
    if (mblen >= mbsize) {
      s21_memcpy(buf, mbbuf, mbsize);
      count += mbsize;
      buf += mbsize;
    }
    mblen -= mbsize;
  }
  if (flags & DASH_FLAG) {
    s21_memset(buf, space, width);
    count += width;
  }

  return (count);
}

static int push_unsigned(char *buf, va_list ap, char specifier, int flags,
                         int width, int precision) {
  char *ptr = buf;
  unsigned long long int n;
  unsigned int base;
  const char *digits;
  const char *prefix;
  int plen = 0;
  char nbuf[64];
  int nlen;
  int zero_pending = 0;
  int space_pending = 0;

  if (flags & LL_FLAG) {
    n = (unsigned long long int)va_arg(ap, unsigned long long int);
  } else if (flags & L_FLAG) {
    n = (unsigned long int)va_arg(ap, unsigned long int);
  } else if (flags & H_FLAG) {
    n = (unsigned short int)va_arg(ap, unsigned int);
  } else if (flags & HH_FLAG) {
    n = (unsigned char)va_arg(ap, unsigned int);
  } else {
    n = (unsigned int)va_arg(ap, unsigned int);
  }
  switch (specifier) {
    case 'o':
      base = 8;
      digits = "01234567";
      prefix = "0";
      plen = 1;
      break;
    case 'p':
    case 'x':
      base = 16;
      digits = "0123456789abcdef";
      prefix = "0x";
      plen = 2;
      break;
    case 'X':
      base = 16;
      digits = "0123456789ABCDEF";
      prefix = "0X";
      plen = 2;
      break;
    default:
      base = 10;
      digits = "0123456789";
      prefix = "";
      plen = 0;
      break;
  }
  nlen = (int)s21_ullitoa_base(n, base, digits, nbuf);

  if (flags & DOT_FLAG) {
    zero_pending = precision - nlen;
    if (n == 0) {
      ++zero_pending;
      nlen = 0;
    }
    if ((flags & OKTO_FLAG) && specifier == 'o') {
      if (!n && !precision) {
        ++zero_pending;
      } else if (n) {
        --zero_pending;
      }
    }
    zero_pending = zero_pending > 0 ? zero_pending : 0;
  }
  space_pending = width - nlen - zero_pending;
  if ((flags & OKTO_FLAG) && n) {
    space_pending -= plen;
  }
  space_pending = space_pending > 0 ? space_pending : 0;
  if (!(flags & DASH_FLAG) && (flags & ZERO_FLAG) && !(flags & DOT_FLAG)) {
    zero_pending = space_pending;
    space_pending = 0;
  }
  if ((flags & DASH_FLAG) || ((flags & ZERO_FLAG) && !(flags & DOT_FLAG))) {
    if ((flags & OKTO_FLAG) && n) {
      s21_strcpy(buf, prefix);
      buf += plen;
    }
    s21_memset(buf, '0', zero_pending);
    buf += zero_pending;
    s21_strcpy(buf, nbuf);
    buf += nlen;
    s21_memset(buf, ' ', space_pending);
    buf += space_pending;
  } else {
    s21_memset(buf, ' ', space_pending);
    buf += space_pending;
    if ((flags & OKTO_FLAG) && n) {
      s21_strcpy(buf, prefix);
      buf += plen;
    }
    s21_memset(buf, '0', zero_pending);
    buf += zero_pending;
    s21_strcpy(buf, nbuf);
    buf += nlen;
  }

  return (buf - ptr);
}

static int push_pointer(char *buf, va_list ap, int flags, int width,
                        int precision) {
#ifndef __MUSL__
  char *ptr = buf;
  unsigned long int n;
  char ptrbuf[64];
  int buflen;
  int isnil = 0;
  char sign = 0;
  int zero_pending = 0;
  int space_pending = 0;

#ifdef __APPLE__
  flags &= ~PLUS_FLAG;
  flags &= ~SPACE_FLAG;
#endif
  n = (unsigned long int)va_arg(ap, void *);
  if (!n) {
#ifdef __APPLE__
    isnil = 0;
    buflen = 1;
    if ((flags & DOT_FLAG) && (!precision)) {
      s21_strcpy(ptrbuf, "");
      buflen = 0;
    } else {
      s21_strcpy(ptrbuf, "0");
    }
#else
    isnil = 1;
    s21_strcpy(ptrbuf, "(nil)");
    buflen = (int)(sizeof("(nil)") - 1);
    flags &= ~DOT_FLAG;
#endif
  } else {
    buflen = (int)s21_ullitoa_base(n, 16, "0123456789abcdef", ptrbuf);
  }
  if (flags & PLUS_FLAG) {
    sign = isnil ? 0 : '+';
  } else if (flags & SPACE_FLAG) {
    sign = isnil ? 0 : ' ';
  }
  if (flags & DOT_FLAG) {
    zero_pending = precision - buflen;
    zero_pending = zero_pending > 0 ? zero_pending : 0;
  }
  space_pending =
      width - zero_pending - buflen - (isnil ? 0 : 2) - (sign ? 1 : 0);
  space_pending = space_pending > 0 ? space_pending : 0;
  if (!(flags & DASH_FLAG) && (flags & ZERO_FLAG) && !(flags & DOT_FLAG) &&
      !isnil) {
    zero_pending = space_pending;
    space_pending = 0;
  }
  if ((flags & DASH_FLAG) ||
      (!isnil && (flags & ZERO_FLAG) && !(flags & DOT_FLAG))) {
    if (!isnil && sign) {
      *buf++ = sign;
    }
    if (!isnil) {
      s21_strcpy(buf, "0x");
      buf += 2;
    }
    s21_memset(buf, '0', zero_pending);
    buf += zero_pending;
    s21_strcpy(buf, ptrbuf);
    buf += buflen;
    s21_memset(buf, ' ', space_pending);
    buf += space_pending;
  } else {
    s21_memset(buf, ' ', space_pending);
    buf += space_pending;
    if (!isnil && sign) {
      *buf++ = sign;
    }
    if (!isnil) {
      s21_strcpy(buf, "0x");
      buf += 2;
    }
    s21_memset(buf, '0', zero_pending);
    buf += zero_pending;
    s21_strcpy(buf, ptrbuf);
    buf += buflen;
  }

  return (buf - ptr);
#else
  if (flags & DOT_FLAG) {
    precision = precision > 16 ? precision : 16;
  }
  flags |= L_FLAG;
  flags |= OKTO_FLAG;
  return (push_unsigned(buf, ap, 'x', flags, width, precision));
#endif
}

static void pop_current_count(va_list ap, int flags, int count) {
  if (flags & LL_FLAG) {
    *((long long int *)va_arg(ap, long long int *)) = (long long int)count;
  } else if (flags & L_FLAG) {
    *((long int *)va_arg(ap, long int *)) = (long int)count;
  } else if (flags & H_FLAG) {
    *((short int *)va_arg(ap, short int *)) = (short int)count;
  } else if (flags & HH_FLAG) {
    *((char *)va_arg(ap, char *)) = (char)count;
  } else {
    *((int *)va_arg(ap, int *)) = count;
  }
}

static int push_float(char *buf, va_list ap, int flags, int width,
                      int precision) {
  long double num;
  char *ptr = buf;
  char *intpart = NULL;
  char *fractpart = NULL;
  int sign = 0;
  int space = ' ';
  int fractlen;
  int intlen;

  if ((flags & LL_FLAG) || (flags & LLL_FLAG)) {
    num = (long double)va_arg(ap, long double);
  } else {
    num = (long double)va_arg(ap, double);
  }
  if (!(flags & DOT_FLAG)) {
    precision = 6;
  }

  sign = s21_ldtoa(num, precision, &intpart, &fractpart);
  if (fractpart == NULL) {
    precision = 0;
#if defined(__APPLE__)
    if (intpart[0] == 'n' && intpart[1] == 'a' && intpart[2] == 'n') {
      flags &= ~SPACE_FLAG;
      flags &= ~PLUS_FLAG;
      sign = 0;
    }
#endif
  }
  if (sign) {
    sign = '-';
  } else if (flags & PLUS_FLAG) {
    sign = '+';
  } else if (flags & SPACE_FLAG) {
    sign = ' ';
  }
  if (!(flags & DASH_FLAG) && (flags & ZERO_FLAG) && fractpart) {
    space = '0';
  }
  intlen = (int)s21_strlen(intpart);
  fractlen = fractpart ? (int)s21_strlen(fractpart) : 0;
  width -= intlen;
  width -= fractlen > precision ? fractlen : precision;
  width -= sign ? 1 : 0;
  if (fractpart && (precision || (flags & OKTO_FLAG))) {
    --width;
  }
  width = width > 0 ? width : 0;
  precision -= fractlen;
  precision = precision > 0 ? precision : 0;

  if (!(flags & DASH_FLAG) && (space == ' ')) {
    s21_memset(buf, space, width);
    buf += width;
  }
  if (sign) {
    *buf++ = sign;
  }
  if (!(flags & DASH_FLAG) && (space == '0')) {
    s21_memset(buf, space, width);
    buf += width;
  }
  s21_strcpy(buf, intpart);
  buf += intlen;
  if (fractpart) {
    if (*fractpart || (flags & OKTO_FLAG) || precision) {
      *buf++ = '.';
    }
    s21_strcpy(buf, fractpart);
    buf += fractlen;
    s21_memset(buf, '0', precision);
    buf += precision;
  }
  if (flags & DASH_FLAG) {
    s21_memset(buf, space, width);
    buf += width;
  }

  return (buf - ptr);
}

static int push_float_exponential(char *buf, va_list ap, int flags, int width,
                                  int precision, char expchar) {
  long double num;
  char *ptr = buf;
  char *numstr = NULL;
  char *expstr = NULL;
  int sign = 0;
  int space = ' ';

  if ((flags & LL_FLAG) || (flags & LLL_FLAG)) {
    num = (long double)va_arg(ap, long double);
  } else {
    num = (long double)va_arg(ap, double);
  }
  if (!(flags & DOT_FLAG)) {
    precision = 6;
  }

  sign = s21_ldtoa_exponential(num, precision, &numstr, &expstr, expchar);
  if (expstr == NULL) {
    precision = 0;
#if defined(__APPLE__)
    if ((numstr[0] | 0x20) == 'n' && (numstr[1] | 0x20) == 'a' &&
        (numstr[2] | 0x20) == 'n') {
      flags &= ~SPACE_FLAG;
      flags &= ~PLUS_FLAG;
      sign = 0;
    }
#endif
  }
  if (sign) {
    sign = '-';
  } else if (flags & PLUS_FLAG) {
    sign = '+';
  } else if (flags & SPACE_FLAG) {
    sign = ' ';
  }
  if (!(flags & DASH_FLAG) && (flags & ZERO_FLAG) && expstr) {
    space = '0';
  }
  char *intpart = numstr;
  char *fractpart = NULL;
  if (expstr) {
    numstr[1] = '\0';
    fractpart = numstr + 2;
  }
  int intlen = (int)s21_strlen(intpart);
  int fractlen = fractpart ? (int)s21_strlen(fractpart) : 0;
  width -= intlen;
  width -= fractlen > precision ? fractlen : precision;
  width -= sign ? 1 : 0;
  if (fractpart && (precision || (flags & OKTO_FLAG))) {
    --width;
  }
  width -= expstr ? s21_strlen(expstr) : 0;
  width = width > 0 ? width : 0;
  precision -= fractlen;
  precision = precision > 0 ? precision : 0;
  if (!(flags & DASH_FLAG) && (space == ' ')) {
    s21_memset(buf, space, width);
    buf += width;
  }
  if (sign) {
    *buf++ = sign;
  }
  if (!(flags & DASH_FLAG) && (space == '0')) {
    s21_memset(buf, space, width);
    buf += width;
  }
  s21_strcpy(buf, intpart);
  buf += intlen;
  if (fractpart) {
    if (*fractpart || (flags & OKTO_FLAG) || precision) {
      *buf++ = '.';
    }
    s21_strcpy(buf, fractpart);
    buf += fractlen;
    s21_memset(buf, '0', precision);
    buf += precision;
  }
  if (expstr) {
    s21_strcpy(buf, expstr);
    buf += s21_strlen(expstr);
  }
  if (flags & DASH_FLAG) {
    s21_memset(buf, space, width);
    buf += width;
  }

  return (buf - ptr);
}
