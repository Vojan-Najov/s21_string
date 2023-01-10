#include <ctype.h>

int s21_atoi(const char *str) {
  int num = 0;
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
    num = 10 * num - (*str++ - '0');
  }

  return (negative ? num : -num);
}
