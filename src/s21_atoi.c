/********
int _atoi(const char *str, int *num)
{
	int n = 0;
	int negative = 0;
	int digit;
	int status = 0;
	const char *ptr;

	if (*str == '-' || *str == '+') {
		sign = *str == '-' ? 1 : 0;
		++str;
	}
	ptr = str;
	while ('0' <= *str && *str <= '9') {
		digit = *str - '0';
		if (n > INT_MAX / 10) {
			status = 1;
			break;
		}
		else if (n < INT_MAX / 10) {
			n *= 10;
			n += digit;
		}
		else {
			if ((sign && -digit < INT_MIN % 10) ||
			    (!sign && digit > INT_MAX % 10)) {
				status = 1;
				break;
			}
			else {
				n *= 10;
				n += digit;
			}
		} 
		++str;
	}
	if (str == ptr) {
		status = 1;
	}
	if (sign) {
		n = -n;
	}
	*num = n;

	return (status);
}
*/

#include <ctype.h>

int s21_atoi(const char *str)
{
	int num =0;
	int negative = 0;

	while (isspace(*str)) {
		++str;
	}
	switch (*str) {
		case '-':
			negative = 1;
			++str;
			break;
		case '+':
			++str;
			break;
	}
	while (isdigit(*str)) {
		num = 10 * num - (*str++ - '0');
	}

	return (negative ? num : -num);
}
