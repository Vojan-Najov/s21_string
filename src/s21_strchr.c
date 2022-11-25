#include "s21_string.h"

char *s21_strchr(const char *str, int c)
{
	unsigned char *s = (unsigned char *) str;

	c = (unsigned char) c;
	while (*s && *s != c) {
		++s;
	}

	return (*s == c ? (char *) s : NULL);
}
