#include "s21_string.h"

void *s21_memset(void *s, int c, size_t n)
{
	unsigned char *ptr = (unsigned char *) s;

	c = (unsigned char) c;
	while (n) {
		*ptr++ = c;
		--n;
	}

	return (s);
}
