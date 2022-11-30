#include <stdarg.h>
#include <limits.h>
#include <stdio.h>
#include "s21_string.h"

#define DASH_FLAG  0x0001
#define PLUS_FLAG  0x0002
#define SPACE_FLAG 0x0004
#define OKTO_FLAG  0x0008
#define ZERO_FLAG  0x0010
#define DOT_FLAG   0x0020
#define H_FLAG     0x0040
#define L_FLAG     0x0080
#define LL_FLAG    0x0100
#define SPTFERROR  0x1000

static int
parse_format(va_list ap, const char **format, int *width, int *precision);
static int
push_char(char *buf, va_list ap, int flags, int width, int precesion);
static int
push_decimal(va_list ap, int flags, int width, int precesion);

int s21_sprintf(char *str, const char *format, ...)
{
	int count = 0;
	int offset;
	int flags = 0;
	int width = 0;
	int precesion = 0;
	va_list ap;

	va_start(ap, format);
	while (*format && !(count < 0)) {
		if (*format == '%') {
			++format;
			flags = parse_format(ap, &format, &width, &precesion);
			if (flags & SPTFERROR) {
				count = -1;
			}
			else {
				switch (*format++) {
					case '%':
						*str = '%';
						offset = 1;
						break;
					case 'c':
						offset = push_char(str, ap, flags, width, precesion);
						break;
					case 'i':
					case 'd':
						push_decimal(ap, flags, width, precesion);
						break;
				}				
				str += offset;
				count += offset;
			}
		}
		else {
			*str++ = *format++;
			++count;
		}
	}
	*str = '\0';
	va_end(ap);

	return (count);
}

static int parse_format(va_list ap, const char **format, int *width, int *precesion)
{
	int flags = 0;
	int wdth = 0;
	int prec = 0;
	const char *fmt = *format;
	const char *flags_str = "-+ #0";
	const char *length_str = "hlL";
	const char *specifiers = "cdieEfgGosuxXpn%";

	while (s21_strchr(flags_str, *fmt) != NULL) {
		switch (*fmt++) {
			case '-':
				flags |= DASH_FLAG;
				break;
			case '+':
				flags |= PLUS_FLAG;
				break;
			case ' ':
				flags |= SPACE_FLAG;
				break;
			case '#':
				flags |= OKTO_FLAG;
				break;
			case '0':
				flags |= ZERO_FLAG;
				break;
			case '\0':
				flags = SPTFERROR;
				break;
		}
	}
	if (*fmt == '*') {
		wdth = va_arg(ap, int);
		++fmt;
	}
	else {
		if (s21_isinteger(fmt)) {
			wdth = s21_atoi(fmt);
			fmt += s21_strspn(fmt, "0123456789");
		}
		else {
			flags = SPTFERROR;
		}
	}
	if (*fmt == '.') {
		flags |= DOT_FLAG;
		++fmt;
	}
	if (*fmt == '*') {
		prec = va_arg(ap, int);
		++fmt;
	}
	else {
		if (s21_isinteger(fmt)) {
			prec = s21_atoi(fmt);
			fmt += s21_strspn(fmt, "0123456789");
		}
		else {
			flags = SPTFERROR;
		}
	}
	if (s21_strchr(length_str, *fmt) != NULL) {
		switch (*fmt++) {
			case 'h':
				flags |= H_FLAG;
				break;
			case 'l':
				flags |= L_FLAG;
				break;
			case 'L':
				flags = LL_FLAG;
				break;
			case '\0':
				flags = SPTFERROR;
				break;
		}
	}
	if (*fmt && s21_strchr(specifiers, *fmt) != NULL) {
		*format = fmt;
		*width = wdth;
		*precesion = prec;
	}
	else {
		flags = SPTFERROR;
	}

	return (flags);

}

/*
static int push_percentage(char *buf, int flags, int width)
{
	char space = ' ';
	int count = width ? width : 1;

	if ((flags & ZERO_FLAG) && !(flags &DASH_FLAG) ) {
		space = '0';
	}
	if (flags & DASH_FLAG) {
		*buf++ = '%';
	}
	while (--width > 0) {
		*buf++ = space;
	}
	printf("%d\n", !(flags & DASH_FLAG));
	if (!(flags & DASH_FLAG)) {
		*buf++ = '%';
	}

	return (count);
}
*/

static int push_char(char *buf, va_list ap, int flags, int width, int precesion)
{
	char c;
	int count = width ? width : 1;

	(void) precesion;
	c = (unsigned char) va_arg(ap, int);
	if (flags & DASH_FLAG) {
		*buf++ = c;
	}
	while (--width > 0) {
		*buf++ = ' ';
	}
	if (!(flags & DASH_FLAG)) {
		*buf++ = c;
	}

	return (count);
}

static int push_decimal(va_list ap, int flags, int width, int precesion)
{
	(void) ap;
	(void) flags;
	(void) width;
	(void) precesion;
	return 0;
}
