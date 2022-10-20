#include "s21_string.h"

void	*s21_memchr(const void *s, int c, size_t n)
{
	const unsigned char *ptr = (const unsigned char *) s;
	
	c = (unsigned char) c;
	while (n && *ptr != c)
	{
		--n;
		++ptr;
	}
	return n ? (void *) ptr : NULL;
}
