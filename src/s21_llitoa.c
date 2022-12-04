#include "s21_string.h"

size_t s21_lltoa(long long int num, char *buf)
{
	size_t len;
	size_t offset;
	int rem;
	long long int n = num;

	while (n) {
		++len;
		n /= 10;
	}
	if (num < 0) {
		++len;
		buf[0] = '-';
	}
	offset = len;
	buf[offset] = '\0';
	while (num) {
		rem = num % 10;
		num /= 10;
		rem = rem > 0 ? rem : -rem;
		buf[--offset] = rem + '0';
	}

	return (len);
}
