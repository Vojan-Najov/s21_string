#include "s21_string.h"

char *s21_strpbrk(const char *s, const char *accept)
{
	s += s21_strcspn(s, accept);

	return (*s ? (char *) s : NULL);
}
