#include "s21_string.h"

size_t	s21_strspn(const char *s, const char *accept)
{
	const char *ptr = s;

	while (*ptr && s21_strchr(accept, *ptr) != NULL) {
		++ptr;
	}

	return (ptr - s);
}
