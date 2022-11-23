#include "s21_string.h"

void *s21_rawmemchr(const void *s, int c)
{
	const unsigned char *ptr = (const unsigned char *) s;

	c = (unsigned char) c;
	while (*ptr != c) {
		++ptr;
	}
	return ((void *) ptr);
}
