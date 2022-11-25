#include "s21_string.h"

char *s21_strchrnul(const char *str, int c)
{
	c = (unsigned char) c;
	while (*str && *str != c) {
		++str;
	}

	return ((char *) str);
}
