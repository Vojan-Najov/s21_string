#include "s21_string.h"

static int _tolower(int c)
{
	if (c >= 'A' && c <= 'Z') {
		c += 'a' - 'A';
	}

	return (c);
}

char *s21_strstr(const char *haystack, const char *needle)
{
	const char *hptr = haystack;
	const char *nptr = needle;

	while (*haystack)
	{
		hptr = haystack;
		nptr = needle;
		while (*nptr && _tolower(*nptr) == _tolower(*hptr))
		{
			++hptr;
			++nptr;
		}
		if (!*nptr) {
			break;
		}
		++haystack;
	}

	return (*haystack || !*needle ? (char *) haystack : NULL);
}
