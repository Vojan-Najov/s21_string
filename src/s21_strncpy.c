#include "s21_string.h"

char	*s21_strncpy(char *dest, const char *src, size_t n)
{
	char *ptr = dest;

	while (n && *src)
	{
		*ptr++ = *src++;
		n--;
	}
	while (n) {
		*ptr++ = '\0';
		n--;
	}

	return (dest);
}
