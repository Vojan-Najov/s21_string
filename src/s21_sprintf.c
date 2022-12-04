#include <stdarg.h>
#include "s21_string.h"

#define DASH_FLAG  0x0001
#define PLUS_FLAG  0x0002
#define SPACE_FLAG 0x0004
#define OKTO_FLAG  0x0008
#define ZERO_FLAG  0x0010
#define DOT_FLAG   0x0020
#define HH_FLAG    0x0040
#define H_FLAG     0x0080
#define L_FLAG     0x0100
#define LL_FLAG    0x0200
#define LLL_FLAG   0x0400
#define SPTFERROR  0x1000

static int
parse_format(va_list ap, const char **format, int *width, int *precision);
static int
push_percent(char *buf, int flags, int width);
static int
push_char(char *buf, va_list ap, int flags, int width);
static int
push_wchar(char *buf, va_list ap, int flags, int width);
static int
push_decimal(char *buf, va_list ap, int flags, int width, int precision);

int s21_sprintf(char *str, const char *format, ...)
{
	int count = 0;
	int offset = 0;
	int flags = 0;
	int width = 0;
	int precision = 0;
	va_list ap;

	va_start(ap, format);
	while (*format && offset >= 0) {
		if (*format == '%') {
			++format;
			flags = parse_format(ap, &format, &width, &precision);
			if (flags & SPTFERROR) {
				count = -1;
				offset = -1;
			}
			else {
				switch (*format++) {
					case '%':
						offset = push_percent(str, flags, width);
						break;
					case 'c':
						if (flags & L_FLAG) {
							offset = push_wchar(str, ap, flags, width);
							count = offset < 0 ? 0 : count;
						} else {
							offset = push_char(str, ap, flags, width);
						}
						break;
					case 'i':
					case 'd':
						push_decimal(str, ap, flags, width, precision);
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
	if (count > 0) {
		*str = '\0';
	}
	va_end(ap);

	return (count);
}

static int parse_format(va_list ap, const char **format, int *width, int *precision)
{
	int flags = 0;
	int wdth = 0;
	int prec = 0;
	const char *fmt = *format;
	const char *flags_str = "-+ #0";
	const char *length_str = "hlL";
	const char *specifiers = "cdieEfgGosuxXpn%";
	const char *digits = "0123456789";

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
			fmt += s21_strspn(fmt, digits);
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
			fmt += s21_strspn(fmt, digits);
		}
		else {
			flags = SPTFERROR;
		}
	}
	if (s21_strchr(length_str, *fmt) != NULL) {
		switch (*fmt++) {
			case 'h':
				if (*fmt == 'h') {
					flags |= HH_FLAG;
					++fmt;
				} else {
					flags |= H_FLAG;
				}
				break;
			case 'l':
				if (*fmt == 'l') {
					flags |= LL_FLAG;
				} else {
					flags |= L_FLAG;
				}
				break;
			case 'L':
				flags = LLL_FLAG;
				break;
			default:
				flags = SPTFERROR;
				break;
		}
	}
	if (*fmt && s21_strchr(specifiers, *fmt) != NULL) {
		*format = fmt;
		*width = wdth;
		*precision = prec;
	}
	else {
		flags = SPTFERROR;
	}

	return (flags);
}

static int push_percent(char *buf, int flags, int width)
{
	int count;
	char space = ' ';

#ifdef __APPLE__
	count = width ? width : 1;
	if (flags & DASH_FLAG) {
		*buf++ = '%';
	} else if (flags & ZERO_FLAG) {
		space = '0';
	}
	while (--width > 0) {
		*buf++ = space;
	}
	if (!(flags & DASH_FLAG)) {
		*buf++ = '%';
	}
#else 
	(void) flags;
	(void) width;
	(void) space;
	count = 1;
	*buf = '%';
#endif

	return (count);
}

static int push_char(char *buf, va_list ap, int flags, int width)
{
	char c;
	char space = ' ';
	char *ptr = buf;

	c = (unsigned char) va_arg(ap, int);
	if (flags & DASH_FLAG) {
		*buf++ = c;
	} else if (flags & ZERO_FLAG) {
#ifdef __APPLE__
		space = '0';
#else
		space = ' ';
#endif
	}
	while (--width > 0) {
		*buf++ = space;
	}
	if (!(flags & DASH_FLAG)) {
		*buf++ = c;
	}

	return ((int)(buf - ptr));
}

static int push_wchar(char *buf, va_list ap, int flags, int width)
{
	wchar_t wc;
	char space = ' ';
	char *ptr = buf;
	int wclen;
	char wcbuf[4];

	wc = (wchar_t) va_arg(ap, int);
	wclen = s21_wctomb(wcbuf, wc);
	if (wclen > 0) {
		width -= wclen;
		if (flags & DASH_FLAG) {
			s21_memcpy(buf, wcbuf, wclen);
			buf += wclen;
		} else if (flags & ZERO_FLAG) {
#ifdef __APPLE__
			space = '0';
#else
			space = ' ';
#endif
		}
		while (width-- > 0) {
			*buf++ = space;
		}
		if (!(flags & DASH_FLAG)) {
			s21_memcpy(buf, wcbuf, wclen);
			buf += wclen;
		}
	}

	return (wclen > 0 ? (int)(buf - ptr) : -1);
}


static int push_decimal(char *buf, va_list ap, int flags, int width, int precision)
{
	long long int n;
	char *ptr = buf;
	char space = ' ';
	char nbuf[64];
	size_t nlen;
	
	if (flags & HH_FLAG) {
		n = (char) va_arg(ap, int);
	} else if (flags & H_FLAG) {
		n = (short int) va_arg(ap, int);
	} else if (flags & L_FLAG) {
		n = (long int) va_arg(ap, long int);
	} else if (flags & LL_FLAG) {
		n = (long long int) va_arg(ap, long long int);
	} else {
		n = (int) va_arg(ap, int);
	}

	nlen = s21_lltoa(n, nbuf);
	
	return 0;
}
