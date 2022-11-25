#include "s21_string.h"

int	s21_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n && *str1 == *str2 && *str1) {
		++str1;
		++str2;
		n--;
	}

	return (n ? (unsigned char) *str1 - (unsigned char) *str2 : 0);
}
