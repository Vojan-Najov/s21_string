#include "s21_string.h"

size_t	s21_strcspn(const char *s, const char *reject)
{
	const char *ptr = s;

	while (*ptr && s21_strchr(reject, *ptr) == NULL) {
		++ptr;
	}

	return (ptr - s);
}
