#include "s21_string.h"

void s21_itoa(int num, char *buf)
{
	int n = num;
	size_t offset = 0;
	int rem;

	while (n) {
		++offset;
		n /= 10;
	}
	if (num < 0) {
		++offset;
		buf[0] = '-';
	}
	buf[offset] = '\0';
	while (num) {
		rem = num % 10;
		num /= 10;
		rem = rem > 0 ? rem : -rem;
		buf[--offset] = rem + '0';
	}
}
