#include "s21_string.h"

int		s21_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *ptr1 = (const unsigned char *) s1;
	const unsigned char *ptr2 = (const unsigned char *) s2;

	while (n && *ptr1 == *ptr2)
	{
		--n;
		++ptr1;
		++ptr2;
	}

	return n ? *ptr1 - *ptr2 : 0;
}
