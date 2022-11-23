#include "s21_string.h"

void *s21_memrchr(const void *s, int c, size_t n)
{
	const unsigned char *ptr = (const unsigned char *) s + n - 1;

	c = (unsigned char) c;
	while (n && *ptr != c) {
		--n;
		--ptr;
	}

	return (n ? (void *) ptr : NULL);
}
