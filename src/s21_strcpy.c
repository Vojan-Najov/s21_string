#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src)
{
	char *ptr = dest;

	while (*src) {
		*ptr++ = *src++;
	}
	*ptr = '\0';

	return (dest);
}
