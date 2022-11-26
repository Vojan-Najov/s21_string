#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle)
{
	const char *hptr = haystack;
	const char *nptr = needle;

	while (*haystack)
	{
		hptr = haystack;
		nptr = needle;
		while (*nptr && *nptr == *hptr)
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
