/**************************************************************************/
/* S21_STRING.H */
/**************************************************************************/

#ifndef S21_STRING_H
#define S21_STRING_H

typedef long unsigned int size_t;

#ifndef NULL
#define NULL ((void*)0)
#endif

void	*s21_memchr(const void *s, int c, size_t n);

int		s21_memcmp(const void *s1, const void *s2, size_t n);

void	*s21_memcpy(void *dest, const void *src, size_t n);

void	*s21_memmove(void *dest, const void *src, size_t n);

void	*s21_memset(void *s, int c, size_t n);

char	*s21_strcat(char *dest, const char *src);

char	*s21_strncat(char *dest, const char *src, size_t n);

char	*s21_strchr(const char *str, int c);

int		s21_strcmp(const char *str1, const char *str2);

int		s21_strncmp(const char *str1, const char *str2, size_t n);

char	*s21_strcpy(char *dest, const char *src);

char	*s21_strncpy(char *dest, const char *src, size_t n);

size_t	s21_strcspn(const char str1, const char str2);

size_t	s21_strlen(const char *str);

char	*s21_strpbrk(const char *s, const char *accept);

char	*s21_strrchr(const char *s, int c);

size_t	s21_strspn(const char *s, const char *accept);

char	*s21_strstr(const char *haystack, const char *needle);

char	*s21_strtok(char *src, const char *delim);

#endif
