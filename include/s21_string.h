/**************************************************************************/
/* S21_STRING.H */
/**************************************************************************/

#ifndef S21_STRING_H
#define S21_STRING_H

typedef long unsigned int size_t;
typedef int wchar_t;

#ifndef NULL
#define NULL ((void*)0)
#endif

/* string.h */
void *s21_memchr(const void *s, int c, size_t n);

void *s21_memrchr(const void *s, int c, size_t n); /* gnu_source */

void *s21_rawmemchr(const void *s, int c); /* gnu_source */

int s21_memcmp(const void *s1, const void *s2, size_t n);

void *s21_memcpy(void *dest, const void *src, size_t n);

void *s21_memmove(void *dest, const void *src, size_t n);

void *s21_memset(void *s, int c, size_t n);

char *s21_strcat(char *dest, const char *src);

char *s21_strncat(char *dest, const char *src, size_t n);

char *s21_strchr(const char *str, int c);

char *s21_strrchr(const char *str, int c);

char *s21_strchrnul(const char *str, int); /* gnu_source */

int s21_strcmp(const char *str1, const char *str2);

int s21_strncmp(const char *str1, const char *str2, size_t n);

char *s21_strcpy(char *dest, const char *src);

char *s21_strncpy(char *dest, const char *src, size_t n);

size_t s21_strspn(const char *s, const char *accept);

size_t s21_strcspn(const char *s, const char *reject);

size_t s21_strlen(const char *str);

char *s21_strpbrk(const char *s, const char *accept);

char *s21_strstr(const char *haystack, const char *needle);

char *s21_strcasestr(const char *haystack, const char *needle); /* gnu_source */

char *s21_strtok(char *src, const char *delim);

char *s21_strerror(int errnum);

/* sprintf */
int s21_sprintf(char *str, const char *format, ...);

/* scanf */

/* special string processing functions */ 

/* additions */
int s21_wctomb(char *str, wchar_t wc);

int s21_atoi(const char *str);

void s21_itoa(int num, char *buf);

int s21_isinteger(const char *str);

#endif
