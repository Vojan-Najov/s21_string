#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = (unsigned char *) dest;
	const unsigned char *s = (const unsigned char *) src;

	while (n) {
		*d++ = *s++;
		--n;
	}

	return (dest);
}
