#include <stdlib.h>

int s21_wctomb(char *str, wchar_t wc) {
  int wclen = 0;

  if ((unsigned int)wc < 0x80) {
    *str = wc;
    wclen = 1;
  } else if (MB_CUR_MAX == 1) {
    if ((unsigned int)wc < 0x100) {
      *str = wc;
      wclen = 1;
    } else {
      wclen = -1;
    }
  } else if ((unsigned int)wc < 0x800) {
    *str++ = 0xC0 | (wc >> 6);
    *str = 0x80 | (wc & 0x3F);
    wclen = 2;
  } else if ((unsigned int)wc < 0x10000) {
    *str++ = 0xE0 | (wc >> 12);
    *str++ = 0x80 | ((wc >> 6) & 0x3F);
    *str = 0x80 | (wc & 0x3F);
    wclen = 3;
  } else if ((unsigned int)wc < 0x110000) {
    *str++ = 0xF0 | (wc >> 18);
    *str++ = 0x80 | ((wc >> 12) & 0x3F);
    *str++ = 0x80 | ((wc >> 6) & 0x3F);
    *str = 0x80 | (wc & 0x3F);
    wclen = 4;
  } else {
    wclen = -1;
  }

  return (wclen);
}
