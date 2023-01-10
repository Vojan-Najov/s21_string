#include "s21_error.h"
#include "s21_string.h"

char *s21_strerror(int errnum) {
  char *strerr;
  int errarr_size = (int)(sizeof(err_array) / sizeof(char *));

  if (0 <= errnum && errnum <= (errarr_size - 1)) {
    strerr = err_array[errnum];
  } else {
#if defined(__linux__) && defined(__GLIBC__) || defined(__APPLE__)
    int offset = sizeof("Unknown error");
#ifdef __APPLE__
    ++offset;
#endif
    s21_itoa(errnum, unknown_buf + offset);
#endif
    strerr = unknown_buf;
  }

  return (strerr);
}
