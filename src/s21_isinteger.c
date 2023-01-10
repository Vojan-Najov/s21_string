#include <ctype.h>
#include <limits.h>

int s21_isinteger(const char *str) {
  int status = 1;
  int n = 0;
  int negative = 0;

  while (isspace(*str)) {
    ++str;
  }
  switch (*str) {
    case '-':
      negative = 1;
      ++str;
      break;
    case '+':
      ++str;
      break;
  }
  while (isdigit(*str)) {
    int digit = *str - '0';
    if (n > INT_MAX / 10) {
      status = 0;
      break;
    } else if (n < INT_MAX / 10) {
      n *= 10;
      n += digit;
    } else {
      if (isdigit(*(str + 1))) {
        status = 0;
        break;
      } else if ((negative && -digit < INT_MIN % 10) ||
                 (!negative && digit > INT_MAX % 10)) {
        status = 0;
        break;
      }
    }
    ++str;
  }

  return (status);
}
