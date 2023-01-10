#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  if (s > d) {
    return s21_memcpy(dest, src, n);
  } else if (s < d) {
    s += n;
    d += n;
    while (n) {
      *(--d) = *(--s);
      --n;
    }
  }

  return (dest);
}
