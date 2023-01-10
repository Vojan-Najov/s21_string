/**************************************************************************/
/* S21_STRING.H */
/**************************************************************************/

#ifndef S21_STRING_H
#define S21_STRING_H

#ifdef __linux__
#include <features.h>
#endif

#if defined(__linux__) && !defined(__GLIBC__)
#define __MUSL__
#endif

typedef int wchar_t;
typedef long unsigned int size_t;
typedef long unsigned int s21_size_t;

#ifndef NULL
#define NULL ((void *)0)
#endif
#define S21_NULL ((void *)0)
#define s21_NULL ((void *)0)

/* string.h */
void *s21_memchr(const void *s, int c, s21_size_t n);
int s21_memcmp(const void *s1, const void *s2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *s, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *s, const char *reject);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *s, const char *accept);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *s, const char *accept);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *src, const char *delim);

/* sscanf */
int s21_sscanf(const char *str, const char *format, ...);

/* sprintf */
int s21_sprintf(char *str, const char *format, ...);

/* special string processing functions */
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

/* auxiliary functions */
int s21_wctomb(char *str, wchar_t wc);
int s21_atoi(const char *str);
size_t s21_itoa(int num, char *buf);
size_t s21_llitoa(long long int num, char *buf);
size_t s21_ullitoa_base(unsigned long long int num, unsigned int base,
                        const char *digits, char *buf);
int s21_isinteger(const char *str);
int s21_ldtoa(long double num, int precision, char **intpart, char **fractpart);
int s21_ldtoa_exponential(long double num, int precision, char **intpart,
                          char **fractpart, char expchar);
long int s21_strtol(const char *nptr, char **endptr, int base);
unsigned long int s21_strtoul(const char *nptr, char **endptr, int base);
long long int s21_strtoll(const char *nptr, char **endptr, int base);
unsigned long long int s21_strtoull(const char *nptr, char **endptr, int base);
long long int s21_str_to_integer(const char *nptr, long int width,
                                 char **endptr, int base);
unsigned long long int s21_str_to_unsigned(const char *nptr, long int width,
                                           char **endptr, int base);

#endif
