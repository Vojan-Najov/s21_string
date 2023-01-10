#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"
#include "suite_sprintf_flags.h"

static void test_s21_memchr(void);
static void test_s21_memcmp(void);
static void test_s21_memcpy(void);
static void test_s21_memmove(void);
static void test_s21_memset(void);
static void test_s21_strcat(void);
static void test_s21_strncat(void);
static void test_s21_strchr(void);
static void test_s21_strcmp(void);
static void test_s21_strncmp(void);
static void test_s21_strcpy(void);
static void test_s21_strncpy(void);
static void test_s21_strcspn(void);
static void test_s21_strerror(void);
static void test_s21_strlen(void);
static void test_s21_strpbrk(void);
static void test_s21_strrchr(void);
static void test_s21_strspn(void);
static void test_s21_strstr(void);
static void test_s21_strtok(void);
static void test_s21_sprintf_basic(void);
static void test_s21_sprintf_c(void);
static void test_s21_sprintf_s(void);
static void test_s21_sprintf_d(void);
static void test_s21_sprintf_f(void);

int main() {
  test_s21_memchr();
  test_s21_memcmp();
  test_s21_memcpy();
  test_s21_memmove();
  test_s21_memset();
  test_s21_strcat();
  test_s21_strncat();
  test_s21_strchr();
  test_s21_strcmp();
  test_s21_strncmp();
  test_s21_strcpy();
  test_s21_strncpy();
  test_s21_strcspn();
  test_s21_strerror();
  test_s21_strlen();
  test_s21_strpbrk();
  test_s21_strrchr();
  test_s21_strspn();
  test_s21_strstr();
  test_s21_strtok();
  test_s21_sprintf_basic();
  test_s21_sprintf_c();
  test_s21_sprintf_s();
  test_s21_sprintf_d();
  test_s21_sprintf_f();
  return (0);
}

static void test_s21_memchr(void) {
  {
    void *buf = NULL;
    size_t n = 0;
    int c = 0x44;
    s21_memchr(buf, c, n);
  }
  {
    char buf[] = "";
    size_t n = 0;
    int c = '\0';
    s21_memchr(buf, c, n);
  }
  {
    char buf[] = "abcd";
    size_t n = 0;
    int c = 'a';
    s21_memchr(buf, c, n);
  }
  {
    char buf[] = "abvdefg";
    size_t n = sizeof(buf) / sizeof(char) - 3;
    int c = '\0';
    s21_memchr(buf, c, n);
  }
  {
    char buf[] = "abvdefg";
    size_t n = sizeof(buf) / sizeof(char) - 2;
    int c = 'g';
    s21_memchr(buf, c, n);
  }
  {
    char buf[] = "abvdefga";
    size_t n = sizeof(buf) / sizeof(char);
    int c = 'a';
    s21_memchr(buf, c, n);
  }
  {
    char buf[] = "abvdevfgv";
    size_t n = sizeof(buf) / sizeof(char);
    int c = 'v';
    s21_memchr(buf, c, n);
  }
  {
    char buf[] = "abvdefg";
    size_t n = sizeof(buf) / sizeof(char);
    int c = '\0';
    s21_memchr(buf, c, n);
  }
  {
    char buf[] = "abvdefg";
    size_t n = sizeof(buf) / sizeof(char);
    int c = 'b' | 0x11100;
    s21_memchr(buf, c, n);
  }
}

static void test_s21_memcmp(void) {
  {
    char buf1[] = "asc";
    char buf2[] = "";
    size_t n = 0;
    s21_memcmp(buf1, buf2, n);
  }
  {
    void *buf1 = NULL;
    void *buf2 = NULL;
    size_t n = 0;
    s21_memcmp(buf1, buf2, n);
  }
  {
    char buf1[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
    char buf2[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
    size_t n = sizeof(buf1) / sizeof(char);
    s21_memcmp(buf1, buf2, n);
  }
  {
    char *buf = NULL;
    size_t n = 1024;

    buf = (char *)calloc(sizeof(char), sizeof(*buf) * 1024);
    if (buf != NULL) {
      s21_memcmp(buf, buf, n);
    }
    free(buf);
  }
  {
    char *buf = NULL;
    size_t n = 1024;
    buf = (char *)calloc(sizeof(char), sizeof(*buf) * 1024);
    if (buf) {
      for (int i = 0; i < 1024; ++i) buf[i] = i % 256;
      s21_memcmp(buf, buf, n);
    }
    free(buf);
  }
  {
    char buf1[] = "asccdada";
    char buf2[] = "asccdadb";
    size_t n = sizeof(buf1) / sizeof(char) - 2;
    s21_memcmp(buf1, buf2, n);
  }
  {
    char buf1[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
    char buf2[] = "bsccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
    size_t n = sizeof(buf1) / sizeof(char);
    s21_memcmp(buf1, buf2, n);
  }
  {
    char buf1[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
    char buf2[] = "asccdadasdasdasadsdasdzsdasdasdasdasdasdasasd";
    size_t n = sizeof(buf1) / sizeof(char);
    s21_memcmp(buf1, buf2, n);
  }
  {
    char buf1[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasas";
    char buf2[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
    size_t n = sizeof(buf1) / sizeof(char);
    s21_memcmp(buf1, buf2, n);
  }
  {
    char buf1[] = "9212383363719300-1-333744740284848428818181882828218";
    char buf2[] = "1212383363719300-1-333744740284848428818181882828218";
    size_t n = sizeof(buf1) / sizeof(char);
    s21_memcmp(buf1, buf2, n);
  }
  {
    char buf1[] = "1212383363719300-1-933744740284848428818181882828218";
    char buf2[] = "1212383363719300-1-333744740284848428818181882828218";
    size_t n = sizeof(buf1) / sizeof(char);
    s21_memcmp(buf1, buf2, n);
  }
  {
    char buf1[] = "1212383363719300-1-333744740284848428818181882828218";
    char buf2[] = "1212383363719300-1-33374474028484842881818188282821";
    size_t n = sizeof(buf2);
    s21_memcmp(buf1, buf2, n);
  }
  {
    long buf[] = {19, 29, 73, 85, 89, 1000000, 111111, 8282282828, -129922};
    size_t n = sizeof(buf);
    s21_memcmp(buf, buf, n);
  }
  {
    long buf1[] = {19, 29, 73, 85, 89, 1000000, 111111, 8282282828, -129922};
    long buf2[] = {19, 29, 73, 85, 89, 1000000, 11121112, 8282282828, -129922};
    size_t n = sizeof(buf1);
    s21_memcmp(buf1, buf2, n);
  }
}

static void test_s21_memcpy(void) {
  {
    void *src = NULL;
    void *dest = NULL;
    size_t n = 0;
    s21_memcpy(dest, src, n);
  }
  {
    char src[] = "hello";
    char dest[10] = {'\0'};
    size_t n = 0;
    s21_memcpy(dest, src, n);
  }
  {
    char src[] = "hello";
    char dest[10] = "bye";
    size_t n = sizeof(src) / sizeof(char);
    s21_memcpy(dest, src, n);
  }
  {
    int src[4096];
    int dest[1024];
    size_t n = 1024 * sizeof(int);
    for (int k = INT_MAX, i = 0; i < 4096; ++i, --k) {
      src[i] = k;
    }
    s21_memcpy(dest, src, n);
  }
}

static void test_s21_memmove(void) {
  {
    void *dest = NULL;
    void *src = NULL;
    size_t n = 0;
    s21_memmove(dest, src, n);
  }
  {
    char dest[10] = "";
    char src[] = "hello";
    size_t n = 0;
    s21_memmove(dest, src, n);
  }
  {
    char buf[] = "verylongstring";
    char *dest = buf + 5;
    char *src = buf + 1;
    size_t n = 0;
    s21_memmove(dest, src, n);
  }
  {
    long src[1024];
    long dest21[1024];
    size_t n = 1024;
    for (int i = 0, k = INT_MAX; i < 1024; ++i, --k) {
      src[i] = k;
    }
    s21_memmove(dest21, src, n * sizeof(long));
  }
  {
    long buf21[1024];
    size_t n1 = 256;
    size_t n2 = 1024 - 256;
    for (int i = 0, k = INT_MAX; i < 1024; ++i, --k) {
      buf21[i] = k;
    }
    s21_memmove(buf21, buf21 + n1, n2 * sizeof(long));
  }
  {
    long buf21[1024];
    size_t n1 = 256;
    size_t n2 = 1024 - 256;
    for (int i = 0, k = INT_MAX; i < 1024; ++i, --k) {
      buf21[i] = k;
    }
    s21_memmove(buf21 + n1, buf21, n2 * sizeof(long));
  }
  {
    long buf21[1024];
    size_t n = 1024;
    for (int i = 0, k = INT_MAX; i < 1024; ++i, --k) {
      buf21[i] = k;
    }
    s21_memmove(buf21, buf21, n * sizeof(long));
  }
}

static void test_s21_memset(void) {
  {
    void *s = NULL;
    int c = '\0';
    size_t n = 0;
    s21_memset(s, c, n);
  }
  {
    char s[] = "hello";
    int c = '\0';
    size_t n = 0;
    s21_memset(s, c, n);
  }
  {
    char s[100];
    int c = 'a';
    s21_memset(s, c, 20);
    ++c;
    s21_memset(s + 20, c, 20);
    ++c;
    s21_memset(s + 40, c, 20);
    ++c;
    s21_memset(s + 60, c, 20);
    ++c;
    s21_memset(s + 80, c, 20);
  }
  {
    long s21[1024];
    int c = 0x18f;
    size_t n = 1024 * sizeof(long);
    s21_memset(s21, c, n);
  }
}

static void test_s21_strcat(void) {
  {
    char src[] = "";
    char dest[] = "abc";
    s21_strcat(dest, src);
  }
  {
    char src[] = "\0abc";
    char dest[10] = "abc";
    s21_strcat(dest, src);
  }
  {
    char src[1024];
    char dest[2048];
    for (int c = 'a', i = 0; i < 1023; ++i, ++c) {
      dest[i] = src[i] = (char)c;
      c = (c > 'z' ? 'a' : c);
    }
    dest[1023] = src[1023] = '\0';
    s21_strcat(dest, src);
  }
  {
    char src[] = "dsalaskl332023020221340";
    char dest[2048] = "\0\0\0\0";
    s21_strcat(dest, src);
  }
}

static void test_s21_strncat(void) {
  {
    char dest21[5] = "";
    char *src21 = NULL;
    size_t n = 0;
    s21_strncat(dest21, src21, n);
  }
  {
    char dest[1024];
    char src[512];
    size_t n = 700;
    for (int c = 'a', i = 0; i < 511; ++c, ++i) {
      src[i] = (char)c;
      c = c > 'z' ? 'a' : c;
    }
    src[511] = '\0';
    for (int c = 'a', i = 0; i < 255; ++c, ++i) {
      dest[i] = (char)c;
      c = c > 'z' ? 'a' : c;
    }
    dest[255] = '\0';
    s21_strncat(dest, src, n);
  }
  {
    char dest[1024];
    char src[512];
    size_t n = 256;
    for (int c = 'a', i = 0; i < 511; ++c, ++i) {
      src[i] = (char)c;
      c = c > 'z' ? 'a' : c;
    }
    src[511] = '\0';
    for (int c = 'a', i = 0; i < 1024; ++c, ++i) {
      dest[i] = (char)c;
      c = c > 'z' ? 'a' : c;
    }
    dest[255] = '\0';
    s21_strncat(dest, src, n);
  }
  {
    char dest[1024];
    char src[512];
    size_t n = 511;
    for (int c = 'a', i = 0; i < 511; ++c, ++i) {
      src[i] = (char)c;
      c = c > 'z' ? 'a' : c;
    }
    src[511] = '\0';
    for (int c = 'a', i = 0; i < 1024; ++c, ++i) {
      dest[i] = (char)c;
      c = c > 'z' ? 'a' : c;
    }
    dest[255] = '\0';
    s21_strncat(dest, src, n);
  }
}

static void test_s21_strchr(void) {
  {
    const char str[] = "";
    int c;
    c = 'a';
    s21_strchr(str, c);
    c = '\0';
    s21_strchr(str, c);
  }
  {
    const char str[] = "abvdefg";
    int c;
    c = 'A';
    s21_strchr(str, c);
    c = '\0';
    s21_strchr(str, c);
  }
  {
    const char str[] = "abvdefg";
    int c = 'a';
    s21_strchr(str, c);
    c = '\0';
    s21_strchr(str, c);
  }
  {
    const char str[] = "abvdevfgv";
    int c = 'v';
    s21_strchr(str, c);
  }
  {
    const char str[] = "abvdefg";
    int c = 'b' | 0x11100;
    s21_strchr(str, c);
  }
}

static void test_s21_strcmp(void) {
  {
    const char *s1 = "";
    const char *s2 = "";
    s21_strcmp(s1, s2);
  }
  {
    const char *s1 = "";
    const char *s2 = "dasjdaddaksjsaddakdasdjsasadka";
    s21_strcmp(s1, s2);
  }
  {
    const char *s1 = "dasjdaddaksjsaddakdasdjsasadka";
    const char *s2 = "";
    s21_strcmp(s1, s2);
  }
  {
    char s1[] = "\0\0";
    char s2[] = "\0\0";
    s1[0] = -127;
    s2[0] = 80;
    s21_strcmp(s1, s2);
  }
  {
    char s1[] = "\0\0";
    char s2[] = "\0\0";
    s1[0] = -127;
    s1[1] = -126;
    s2[0] = -127;
    s2[1] = -126;
    s21_strcmp(s1, s2);
    s21_strcmp(s2, s1);
  }
  {
    char s1[] = "sadlksadlaskdslassasdalkasddklaasdsal";
    char s2[] = "sadlksadlaskdslassasdalkasddklaasdsal";
    s21_strcmp(s1, s2);
    s21_strcmp(s2, s1);
  }
  {
    char s1[] = "sadlksadlaskdslassasdalkasddklaasdsal";
    char s2[] = "s_dlksadlaskdslassasdalkasddklaasdsal";
    s21_strcmp(s1, s2);
    s21_strcmp(s2, s1);
  }
  {
    char s1[] = "sadlksadlaskdslass_sdalkasd_laasdsal";
    char s2[] = "sadlksadlaskdslassasdalkasddklaasdsal";
    s21_strcmp(s1, s2);
    s21_strcmp(s2, s1);
  }
  {
    char s1[] = "sadlksadlaskdslassasdalkasddklaasds_";
    char s2[] = "sadlksadlaskdslassasdalkasddklaasdsa";
    s21_strcmp(s1, s2);
    s21_strcmp(s2, s1);
  }
  {
    char s1[] = "sadlksadlaskdslass";
    char s2[] = "sadlksadlaskdslassasdalkasddklaasdsal";
    s21_strcmp(s1, s2);
    s21_strcmp(s2, s1);
  }
}

static void test_s21_strncmp(void) {
  {
    const char *s1 = "";
    const char *s2 = "";
    size_t n = 0;
    s21_strncmp(s1, s2, n);
    n = 100;
    s21_strncmp(s1, s2, n);
  }
  {
    const char *s1 = "";
    const char *s2 = "dasjdaddaksjsaddakdasdjsasadka";
    size_t n = 0;
    s21_strncmp(s1, s2, n);
    n = 10;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
  }
  {
    const char s1[] = "sadlksadlaskdslassasdalkasddklaasdsal";
    const char s2[] = "sadlksadlaskdslassasdalkasddklaasdsal";
    size_t n;
    n = 0;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = sizeof(s1) - 1;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = sizeof(s1);
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
  }
  {
    char s1[] = "sadlksadlaskdslassasdalkasddklaasdsal";
    char s2[] = "s_dlksadlaskdslassasdalkasddklaasdsal";
    size_t n;
    n = 0;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = 1;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = 2;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = sizeof(s1);
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
  }
  {
    char s1[] = "sadlksadlask";
    char s2[] = "sadlksadlaskdslassasdalkasddklaasdsal";
    size_t n;
    n = 0;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = sizeof(s1) - 1;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = sizeof(s1);
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = sizeof(s2);
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
  }
  {
    char s1[] = "sadlksadlaskdslassasdalkasddklaasds_";
    char s2[] = "sadlksadlaskdslassasdalkasddklaasdsa";
    size_t n;
    n = 0;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = sizeof(s1) - 2;
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
    n = sizeof(s1);
    s21_strncmp(s1, s2, n);
    s21_strncmp(s2, s1, n);
  }
}

static void test_s21_strcpy(void) {
  {
    char dest21[] = "";
    const char *src = "";
    s21_strcpy(dest21, src);
  }
  {
    char dest21[] = "abv123";
    const char *src = "";
    s21_strcpy(dest21, src);
  }
  {
    char dest21[100] = "";
    const char *src = "asdjsakd sakjddsada asdkjas";
    s21_strcpy(dest21, src);
  }
  {
    char dest21[100] = "dasdasasd dsaa adsd\0sasd";
    const char *src = "asdjsakd sakjddsada a\0sdkjas";
    s21_strcpy(dest21, src);
  }
}

static void test_s21_strncpy(void) {
  {
    char dest21[10] = "";
    const char *src = "";
    size_t n;
    n = 0;
    s21_strncpy(dest21, src, n);
    n = 10;
    s21_strncpy(dest21, src, n);
  }
  {
    char dest21[20] = "adsadsadasdaasa";
    const char *src = "";
    size_t n;
    n = 0;
    s21_strncpy(dest21, src, n);
    n = 1;
    s21_strncpy(dest21, src, n);
    n = 20;
    s21_strncpy(dest21, src, n);
  }
  {
    char dest21[20] = "adsadsadasdaasa";
    const char *src = "asd sada";
    size_t n = 0;
    s21_strncpy(dest21, src, n);
  }
  {
    char dest21[] = "adsadsadasdaasa";
    const char *src = "asd sada";
    size_t n = sizeof(src) - 1;
    s21_strncpy(dest21, src, n);
  }
  {
    char dest21[] = "adsadsadasdaasa               ";
    const char *src = "asd sada";
    size_t n = sizeof(src) + 7;

    s21_strncpy(dest21, src, n);
  }
  {
    char dest21[] = "adsadsadasdaasa               ";
    const char *src = "asd sada";
    size_t n = sizeof(src) - 3;
    s21_strncpy(dest21, src, n);
  }
}

static void test_s21_strcspn(void) {
  {
    const char *s = "";
    const char *reject = "";
    s21_strcspn(s, reject);
  }
  {
    const char *s = "";
    const char *reject = "sad ajsjqp 129291- 29s";
    s21_strcspn(s, reject);
  }
  {
    const char *s = "asd quwi saj1 29219 \n";
    const char *reject = "";
    s21_strcspn(s, reject);
  }
  {
    const char *s = "1234asdda";
    const char *reject = "4321";
    s21_strcspn(s, reject);
  }
  {
    const char *s = "asdkaskak123456789 asdda";
    const char *reject = "987654321";
    s21_strcspn(s, reject);
  }
}

static void test_s21_strerror(void) {
  {
    for (int i = -1024; i < 1024; ++i) {
      s21_strerror(i);
    }
  }
  {
    s21_strerror(INT_MAX);
    s21_strerror(INT_MIN);
  }
}

static void test_s21_strlen(void) {
  {
    const char *s = "";
    s21_strlen(s);
    s = "\0asdasas";
    s21_strlen(s);
  }
  {
    const char *s = "sadjkksajdsakj kasjkdakdsa sakdjas";
    s21_strlen(s);
    s = "0000000000000\0asdasas";
    s21_strlen(s);
  }
  {
    char *s = NULL;
    char c = 'a';
    size_t size = 1024;
    s = (char *)malloc(sizeof(char) * size);
    if (s != NULL) {
      s[size - 1] = '\0';
      for (unsigned int i = 0; i < size - 1; ++i) {
        s[i] = c;
      }
      s21_strlen(s);
    }
    free(s);
  }
  {
    const char *s = "123";
    s21_strlen(s);
    s = "\0asdasas";
    s21_strlen(s);
  }
}

static void test_s21_strpbrk(void) {
  {
    const char *s = "";
    const char *a = "";
    s21_strpbrk(s, a);
  }
  {
    const char *s = "ashs 12231 sjasj";
    const char *a = "";
    s21_strpbrk(s, a);
  }
  {
    const char *s = "";
    const char *a = "abcdefg";
    s21_strpbrk(s, a);
  }
  {
    const char *s = "abhdha asjdj asjsj asj aodpdc";
    const char *a = "13839102";
    s21_strpbrk(s, a);
  }
  {
    const char *s = "abhdha asjdj 9  1 asjsj asj 1234 aodpdc";
    const char *a = "13839102";
    s21_strpbrk(s, a);
  }
}

static void test_s21_strrchr(void) {
  {
    const char str[] = "";
    int c;
    c = 'a';
    s21_strrchr(str, c);
    c = '\0';
    s21_strrchr(str, c);
  }
  {
    const char str[] = "abvdefg";
    int c;
    c = 'A';
    s21_strrchr(str, c);
  }
  {
    const char str[] = "abvdefg";
    int c = 'a';
    s21_strrchr(str, c);
    c = '\0';
    s21_strrchr(str, c);
  }
  {
    const char str[] = "abvdevfgv";
    int c = 'v';
    s21_strrchr(str, c);
    c = '\0';
    s21_strrchr(str, c);
  }
  {
    const char str[] = "abvdefg";
    int c = 'b' | 0x11100;
    s21_strrchr(str, c);
  }
}

static void test_s21_strspn(void) {
  {
    const char *s = "";
    const char *accept = "";
    s21_strspn(s, accept);
  }
  {
    const char *s = "";
    const char *accept = "sad ajsjqp 129291- 29s";
    s21_strspn(s, accept);
  }
  {
    const char *s = "asd quwi saj1 29219 \n";
    const char *accept = "";
    s21_strspn(s, accept);
  }
  {
    const char *s = "a1234asdda";
    const char *accept = "4321";
    s21_strspn(s, accept);
  }
  {
    const char *s = "123456789 asdda";
    const char *accept = "987654321";
    s21_strspn(s, accept);
  }
}

static void test_s21_strstr(void) {
  {
    const char *h = "";
    const char *n = "";
    s21_strstr(h, n);
  }
  {
    const char *h = "abssak aksdk lala 123";
    const char *n = "";
    s21_strstr(h, n);
  }
  {
    const char *h = "";
    const char *n = "abcd";
    s21_strstr(h, n);
  }
  {
    const char *h = "planet Earth";
    const char *n = "planeta";
    s21_strstr(h, n);
    n = "plaet";
    s21_strstr(h, n);
    n = " e";
    s21_strstr(h, n);
    n = "th0";
    s21_strstr(h, n);
    h = "hol\0a";
    n = "hola";
    s21_strstr(h, n);
  }
  {
    const char *h = "planet Earth";
    const char *n = "planet";
    s21_strstr(h, n);
    n = "et ";
    s21_strstr(h, n);
    n = " Ea";
    s21_strstr(h, n);
    n = "a";
    s21_strstr(h, n);
    n = "t";
    s21_strstr(h, n);
    n = "th";
    s21_strstr(h, n);
    h = "planet Earth plan";
    n = "plan";
    s21_strstr(h, n);
    h = "plazet Earth plan";
    n = "plan";
    s21_strstr(h, n);
  }
}

static void test_s21_strtok(void) {
  {
    char s2[] = "";
    char delim[] = "";
    char *ret2;
    ret2 = s21_strtok(s2, delim);
    ret2 = s21_strtok(NULL, delim);
    ret2 = s21_strtok(NULL, delim);
    (void)ret2;
  }
  {
    char s2[] = "hello";
    char *delim = "";
    char *ret2;

    ret2 = s21_strtok(s2, delim);
    ret2 = s21_strtok(NULL, delim);
    ret2 = s21_strtok(NULL, delim);
    (void)ret2;
  }
  {
    char s2[] = "hello";
    char *delim = " ;,.";
    char *ret2;

    ret2 = s21_strtok(s2, delim);
    ret2 = s21_strtok(NULL, delim);
    ret2 = s21_strtok(NULL, delim);
    (void)ret2;
  }
  {
    char buf1[] = "hello man how are you";
    char *s1 = buf1;
    char *delim = " ";
    char *ret1;

    while ((ret1 = s21_strtok(s1, delim)) != NULL) {
      s1 = NULL;
    }
    (void)ret1;
  }
  {
    char buf1[] = "hello man! how,are ,you.";
    char *s1 = buf1;
    char *delim = " !;,.";
    char *ret1;

    while ((ret1 = s21_strtok(s1, delim)) != NULL) {
      s1 = NULL;
    }
    (void)ret1;
  }
  {
    char buf1[] = "hello man! how,are ,you.";
    char *s1 = buf1;
    char *delim[] = {" !", ".,", " ,"};
    char *ret1;
    int i = 0;
    while ((ret1 = s21_strtok(s1, delim[i])) != NULL) {
      s1 = NULL;
      ++i;
      i %= 3;
    }
    (void)ret1;
  }
  {
    char buf1[] = "hello man! how,are ,you.";
    char buf10[] = "HELLO MAN! HOW,ARE ,YOU.";
    char *s1 = buf1;
    char *delim = " !;,.";
    char *ret1;
    int i = 0;

    while (i < 3) {
      ret1 = s21_strtok(s1, delim);
      s1 = NULL;
      ++i;
    }
    s1 = buf10;
    while ((ret1 = s21_strtok(s1, delim)) != NULL) {
      s1 = NULL;
    }
    (void)ret1;
  }
  {
    char buf1[] = "hello man! how,are ,you.";
    char buf10[] = "HELLO MAN! HOW,ARE ,YOU.";
    char *s1 = buf1;
    char *delim = " !;,.";
    char *ret1;

    while ((ret1 = s21_strtok(s1, delim)) != NULL) {
      s1 = NULL;
    }
    s1 = buf10;
    while ((ret1 = s21_strtok(s1, delim)) != NULL) {
      s1 = NULL;
    }
    (void)ret1;
  }
}

static void test_s21_sprintf_basic(void) {
  {
    int ret21;
    char *buf21;
    const char *format = "";
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      ret21 = s21_sprintf(buf21, format);
      free(buf21);
      (void)ret21;
    }
  }
  {
    int ret21;
    char *buf21;
    char format[4096];
    buf21 = calloc(4096, sizeof(char));
    for (int i = 0, c = 'a'; i < 4095; ++i, ++c) {
      c = c > 'z' ? 'a' : c;
      format[i] = c;
    }
    format[4095] = '\0';
    if (buf21 != NULL) {
      ret21 = s21_sprintf(buf21, format);
      free(buf21);
      (void)ret21;
    }
  }
  {
    int ret21;
    char *buf21;
    const char *format;
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      format = "%";
      ret21 = s21_sprintf(buf21, format);
      format = "%*";
      ret21 = s21_sprintf(buf21, format);
      format = "%123";
      ret21 = s21_sprintf(buf21, format);
      format = "%123.";
      ret21 = s21_sprintf(buf21, format);
      ret21 = s21_sprintf(buf21, format);
      format = "%123.123";
      ret21 = s21_sprintf(buf21, format);
      format = "%-1234q";
      ret21 = s21_sprintf(buf21, format);
      format = "%l";
      ret21 = s21_sprintf(buf21, format);
      format = "asdsda%+h";
      ret21 = s21_sprintf(buf21, format);
      format = "aa%+-";
      ret21 = s21_sprintf(buf21, format);
      format = "aa%+-100";
      ret21 = s21_sprintf(buf21, format);
      format = "a%+-";
      ret21 = s21_sprintf(buf21, format);
      char *digits = "11111111111111111111111111111";
      char fmt[128];
      sprintf(fmt, "a%%%sd\n", digits);
      ret21 = s21_sprintf(buf21, fmt, 100);
#ifndef __APPLE__
      sprintf(fmt, "%%.%sd", digits);
      ret21 = s21_sprintf(buf21, fmt, 100);
#endif
      (void)ret21;
    }
    free(buf21);
  }
}

static void test_s21_sprintf_c(void) {
  {
    int ret21;
    char *buf21;
    char format[128];
    unsigned char c = 'a';
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        sprintf(format, "_%%%sc_\n", sprintf_flags[i]);
        ret21 = s21_sprintf(buf21, format, c);
        ++c;
        c = c > 'z' ? 'a' : c;
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "10", "32", NULL};
    unsigned char c = 'a';
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j]; ++j) {
          sprintf(format, "_%%%s%sc_\n", sprintf_flags[i], width[j]);
          ret21 = s21_sprintf(buf21, format, c);
          ++c;
          c = c > 'z' ? 'a' : c;
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *precision[] = {"", "0", "1", "2", "32", NULL};
    unsigned char c = '!';

    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; precision[j]; ++j) {
          sprintf(format, "_%%%s.%sc_\n", sprintf_flags[i], precision[j]);
          ret21 = s21_sprintf(buf21, format, c);
          ++c;
          c = c > 'z' ? '!' : c;
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "32", "64", NULL};
    char *precision[] = {"", "0", "1", "2", "32", "64", NULL};
    unsigned char c = '!';

    buf21 = calloc(1024, sizeof(char));

    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j]; ++j) {
          for (int k = 0; precision[k]; ++k) {
            sprintf(format, "_%%%s%s.%sc_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret21 = s21_sprintf(buf21, format, c);
            ++c;
            c = c > 'z' ? '!' : c;
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32};
    int wlen = (int)(sizeof(width) / sizeof(int));
    unsigned char c = 0;
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          sprintf(format, "_%%%s*c_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, width[j], c);
          ++c;
          c = c > 'z' ? 0 : c;
        }
      }
      free(buf21);
      (void)ret21;
    }
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int precision[] = {0, 1, 2, 32};
    int plen = (int)(sizeof(precision) / sizeof(int));
    unsigned char c = '!';
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < plen; ++j) {
          sprintf(format, "_%%%s.*c_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, precision[j], c);
          ++c;
          c = c > 'z' ? '!' : c;
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32, 64};
    int precision[] = {0, 1, 2, 32, 64};
    int wlen = (int)(sizeof(width) / sizeof(int));
    int plen = sizeof(precision) / sizeof(int);
    unsigned char c = '!';
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int k = 0; k < plen; ++k) {
            sprintf(format, "_%%%s*.*c_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], c);
            ++c;
            c = c > 'z' ? '!' : c;
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32, 64};
    int precision[] = {0, 1, 2, 32, 64};
    int wlen = sizeof(width) / sizeof(int);
    int plen = sizeof(precision) / sizeof(int);
    wchar_t wc = '!';
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int k = 0; k < plen; ++k) {
            sprintf(format, "_%%%s*.*lc_\n", sprintf_flags[i]);
#ifdef __MUSL__
            if (strchr(format, '0') || strchr(format, '#')) continue;
#endif
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], wc);
            ++wc;
            wc = wc > '}' ? '!' : wc;
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32, 64};
    int precision[] = {0, 1, 2, 32, 64};
    int wlen = sizeof(width) / sizeof(int);
    int plen = sizeof(precision) / sizeof(int);
    wchar_t wc = 0;
    buf21 = calloc(1024, sizeof(char));
    setlocale(LC_ALL, "");
    wc = 0x100000;
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int k = 0; k < plen; ++k) {
            sprintf(format, "_%%%s*.*lc_\n", sprintf_flags[i]);
#ifdef __MUSL__
            if (strchr(format, '0') || strchr(format, '#')) continue;
#endif
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], wc);
            ++wc;
          }
        }
      }
    }
    setlocale(LC_CTYPE, "C");
    free(buf21);
    (void)ret21;
  }
}

static void test_s21_sprintf_s(void) {
  {
    int ret21;
    char *buf21;
    char format[128];
    char *str[] = {
        NULL,
        "",
        "a",
        "ab",
        "abc",
        "abcd",
        "abcde",
        "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(char *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int s = 0; s < len; ++s) {
          sprintf(format, "_%%%ss_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, str[s]);
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "10", "32", NULL};
    char *str[] = {
        NULL,
        "",
        "a",
        "ab",
        "abc",
        "abcd",
        "abcde",
        "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(char *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j]; ++j) {
          for (int s = 0; s < len; ++s) {
            sprintf(format, "_%%%s%ss_\n", sprintf_flags[i], width[j]);
            ret21 = s21_sprintf(buf21, format, str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *precision[] = {"", "0", "1", "2", "32", NULL};
    char *str[] = {
        NULL,
        "",
        "a",
        "ab",
        "abc",
        "abcd",
        "abcde",
        "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(char *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; precision[j]; ++j) {
          for (int s = 0; s < len; ++s) {
            sprintf(format, "_%%%s.%ss_\n", sprintf_flags[i], precision[j]);
            ret21 = s21_sprintf(buf21, format, str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "32", "64", NULL};
    char *precision[] = {"", "0", "1", "2", "32", "64", NULL};
    char *str[] = {
        NULL,
        "",
        "a",
        "ab",
        "abc",
        "abcd",
        "abcde",
        "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(char *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j]; ++j) {
          for (int k = 0; precision[k]; ++k) {
            for (int s = 0; s < len; ++s) {
              sprintf(format, "_%%%s%s.%ss_\n", sprintf_flags[i], width[j],
                      precision[k]);
              ret21 = s21_sprintf(buf21, format, str[s]);
            }
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32};
    int wlen = (int)(sizeof(width) / sizeof(int));
    char *str[] = {
        NULL,
        "",
        "a",
        "ab",
        "abc",
        "abcd",
        "abcde",
        "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(char *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int s = 0; s < len; ++s) {
            sprintf(format, "_%%%s*s_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, width[j], str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int precision[] = {0, 1, 2, 32};
    int plen = (int)(sizeof(precision) / sizeof(int));
    char *str[] = {
        NULL,
        "",
        "a",
        "ab",
        "abc",
        "abcd",
        "abcde",
        "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(char *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < plen; ++j) {
          for (int s = 0; s < len; ++s) {
            sprintf(format, "_%%%s.*s_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, precision[j], str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32, 64};
    int precision[] = {0, 1, 2, 32, 64};
    int wlen = (int)(sizeof(width) / sizeof(int));
    int plen = sizeof(precision) / sizeof(int);
    char *str[] = {
        NULL,
        "",
        "a",
        "ab",
        "abc",
        "abcd",
        "abcde",
        "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"
        "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(char *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int k = 0; k < plen; ++k) {
            for (int s = 0; s < len; ++s) {
              sprintf(format, "_%%%s*.*s_\n", sprintf_flags[i]);
              ret21 =
                  s21_sprintf(buf21, format, width[j], precision[k], str[s]);
            }
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    wchar_t *str[] = {
        NULL,
        L"",
        L"a",
        L"ab",
        L"abc",
        L"abcd",
        L"abcde",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%ss_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, str[s]);
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "10", "32", NULL};
    wchar_t *str[] = {
        NULL,
        L"",
        L"a",
        L"ab",
        L"abc",
        L"abcd",
        L"abcde",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j]; ++j) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s%ss_\n", sprintf_flags[i], width[j]);
            ret21 = s21_sprintf(buf21, format, str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *precision[] = {"", "0", "1", "2", "32", NULL};
    wchar_t *str[] = {
        NULL,
        L"",
        L"a",
        L"ab",
        L"abc",
        L"abcd",
        L"abcde",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; precision[j]; ++j) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s.%ss_\n", sprintf_flags[i], precision[j]);
            ret21 = s21_sprintf(buf21, format, str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "32", "64", NULL};
    char *precision[] = {"", "0", "1", "2", "32", "64", NULL};
    wchar_t *str[] = {
        NULL,
        L"",
        L"a",
        L"ab",
        L"abc",
        L"abcd",
        L"abcde",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j]; ++j) {
          for (int k = 0; precision[k]; ++k) {
            for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
              if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
              sprintf(format, "_%%%s%s.%ss_\n", sprintf_flags[i], width[j],
                      precision[k]);
              ret21 = s21_sprintf(buf21, format, str[s]);
            }
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32};
    int wlen = (int)(sizeof(width) / sizeof(int));
    wchar_t *str[] = {
        NULL,
        L"",
        L"a",
        L"ab",
        L"abc",
        L"abcd",
        L"abcde",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s*s_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, width[j], str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int precision[] = {0, 1, 2, 32};
    int plen = (int)(sizeof(precision) / sizeof(int));
    wchar_t *str[] = {
        NULL,
        L"",
        L"a",
        L"ab",
        L"abc",
        L"abcd",
        L"abcde",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < plen; ++j) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s.*s_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, precision[j], str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32, 64};
    int precision[] = {0, 1, 2, 32, 64};
    int wlen = (int)(sizeof(width) / sizeof(int));
    int plen = sizeof(precision) / sizeof(int);
    wchar_t *str[] = {
        NULL,
        L"",
        L"a",
        L"ab",
        L"abc",
        L"abcd",
        L"abcde",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
        L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int k = 0; k < plen; ++k) {
            for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
              if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
              sprintf(format, "_%%%s*.*s_\n", sprintf_flags[i]);
              ret21 =
                  s21_sprintf(buf21, format, width[j], precision[k], str[s]);
            }
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    wchar_t *str[] = {NULL,
                      L"",
                      L"a",
                      L"ab",
                      L"abc",
                      L"abcd",
                      L"abcde",
                      L"φωϊϣϺ᮵φω",
                      L"φωϊ",
                      L"φ",
                      L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                      L"asask askskas kasakskas askskakas asksakask askskk",
                      L"asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    setlocale(LC_ALL, "");
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%sls_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, str[s]);
        }
      }
    }
    (void)ret21;
    free(buf21);
    setlocale(LC_CTYPE, "C");
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "10", "32", NULL};
    wchar_t *str[] = {NULL,
                      L"",
                      L"a",
                      L"ab",
                      L"abc",
                      L"abcd",
                      L"abcde",
                      L"φωϊϣϺ᮵φω",
                      L"φωϊ",
                      L"φ",
                      L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                      L"asask askskas kasakskas askskakas asksakask askskk",
                      L"asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    setlocale(LC_ALL, "");
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j]; ++j) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s%sls_\n", sprintf_flags[i], width[j]);
            ret21 = s21_sprintf(buf21, format, str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
    setlocale(LC_CTYPE, "C");
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *precision[] = {"", "0", "1", "2", "32", NULL};
    wchar_t *str[] = {NULL,
                      L"",
                      L"a",
                      L"ab",
                      L"abc",
                      L"abcd",
                      L"abcde",
                      L"φωϊϣϺ᮵φω",
                      L"φωϊ",
                      L"φ",
                      L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                      L"asask askskas kasakskas askskakas asksakask askskk",
                      L"asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    setlocale(LC_ALL, "");
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; precision[j]; ++j) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s.%sls_\n", sprintf_flags[i], precision[j]);
            ret21 = s21_sprintf(buf21, format, str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
    setlocale(LC_CTYPE, "C");
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "32", "64", NULL};
    char *precision[] = {"", "0", "1", "2", "32", "64", NULL};
    wchar_t *str[] = {NULL,
                      L"",
                      L"a",
                      L"ab",
                      L"abc",
                      L"abcd",
                      L"abcde",
                      L"φωϊϣϺ᮵φω",
                      L"φωϊ",
                      L"φ",
                      L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                      L"asask askskas kasakskas askskakas asksakask askskk",
                      L"asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    setlocale(LC_ALL, "");
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j]; ++j) {
          for (int k = 0; precision[k]; ++k) {
            for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
              if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
              sprintf(format, "_%%%s%s.%sls_\n", sprintf_flags[i], width[j],
                      precision[k]);
              ret21 = s21_sprintf(buf21, format, str[s]);
            }
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
    setlocale(LC_CTYPE, "C");
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32};
    int wlen = (int)(sizeof(width) / sizeof(int));
    wchar_t *str[] = {NULL,
                      L"",
                      L"a",
                      L"ab",
                      L"abc",
                      L"abcd",
                      L"abcde",
                      L"φωϊϣϺ᮵φω",
                      L"φωϊ",
                      L"φ",
                      L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                      L"asask askskas kasakskas askskakas asksakask askskk",
                      L"asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    setlocale(LC_ALL, "");
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s*ls_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, width[j], str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
    setlocale(LC_CTYPE, "C");
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int precision[] = {0, 1, 2, 32};
    int plen = (int)(sizeof(precision) / sizeof(int));
    wchar_t *str[] = {NULL,
                      L"",
                      L"a",
                      L"ab",
                      L"abc",
                      L"abcd",
                      L"abcde",
                      L"φωϊϣϺ᮵φω",
                      L"φωϊ",
                      L"φ",
                      L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                      L"asask askskas kasakskas askskakas asksakask askskk",
                      L"asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    setlocale(LC_ALL, "");
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < plen; ++j) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s.*ls_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, precision[j], str[s]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
    setlocale(LC_CTYPE, "C");
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 32, 64};
    int precision[] = {0, 1, 2, 32, 64};
    int wlen = (int)(sizeof(width) / sizeof(int));
    int plen = sizeof(precision) / sizeof(int);
    wchar_t *str[] = {NULL,
                      L"",
                      L"a",
                      L"ab",
                      L"abc",
                      L"abcd",
                      L"abcde",
                      L"φωϊϣϺ᮵φω",
                      L"φωϊ",
                      L"φ",
                      L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                      L"asask askskas kasakskas askskakas asksakask askskk",
                      L"asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"
                      "asask askskas kasakskas askskakas asksakask askskkk"};
    int len = (int)(sizeof(str) / (sizeof(wchar_t *)));
    buf21 = calloc(1024, sizeof(char));
    setlocale(LC_ALL, "");
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int k = 0; k < plen; ++k) {
            for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
              if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
              sprintf(format, "_%%%s*.*ls_\n", sprintf_flags[i]);
              ret21 =
                  s21_sprintf(buf21, format, width[j], precision[k], str[s]);
            }
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
    setlocale(LC_CTYPE, "C");
  }
}

static void test_s21_sprintf_d(void) {
  {
    int ret21;
    char *buf21;
    char format[128];
    char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (size_t j = 0; j < sizeof(ints) / sizeof(char); ++j) {
          sprintf(format, "_%%%shhd_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, ints[j]);
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                        0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (size_t j = 0; j < sizeof(ints) / sizeof(short int); ++j) {
          sprintf(format, "_%%%shd_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, ints[j]);
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                  -1,       0,        1,      19,       CHAR_MAX, 1078,
                  SHRT_MAX, 10937,    279303, INT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (size_t j = 0; j < sizeof(ints) / sizeof(int); ++j) {
          sprintf(format, "_%%%sd_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, ints[j]);
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                       1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (size_t j = 0; j < sizeof(ints) / sizeof(long int); ++j) {
          sprintf(format, "_%%%sld_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, ints[j]);
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                            -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                            INT_MAX,   LONG_MAX, LLONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (size_t j = 0; j < sizeof(ints) / sizeof(long long int); ++j) {
          sprintf(format, "_%%%slld_\n", sprintf_flags[i]);
          ret21 = s21_sprintf(buf21, format, ints[j]);
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
    char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(char); ++k) {
            sprintf(format, "_%%%s%shhd_\n", sprintf_flags[i], width[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
    short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                        0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(short int); ++k) {
            sprintf(format, "_%%%s%shd_\n", sprintf_flags[i], width[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
    int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                  -1,       0,        1,      19,       CHAR_MAX, 1078,
                  SHRT_MAX, 10937,    279303, INT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(int); ++k) {
            sprintf(format, "_%%%s%sd_\n", sprintf_flags[i], width[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
    long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                       1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(long int); ++k) {
            sprintf(format, "_%%%s%sld_\n", sprintf_flags[i], width[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
    long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                            -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                            INT_MAX,   LONG_MAX, LLONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(long long int); ++k) {
            sprintf(format, "_%%%s%slld_\n", sprintf_flags[i], width[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
    char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; precision[j]; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(char); ++k) {
            sprintf(format, "_%%%s.%shhd_\n", sprintf_flags[i], precision[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
    short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                        0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; precision[j]; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(short int); ++k) {
            sprintf(format, "_%%%s.%shd_\n", sprintf_flags[i], precision[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    (void)ret21;
    free(buf21);
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
    int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                  -1,       0,        1,      19,       CHAR_MAX, 1078,
                  SHRT_MAX, 10937,    279303, INT_MAX};

    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; precision[j]; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(int); ++k) {
            sprintf(format, "_%%%s.%sd_\n", sprintf_flags[i], precision[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
    long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                       1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; precision[j]; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(long int); ++k) {
            sprintf(format, "_%%%s.%sld_\n", sprintf_flags[i], precision[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
    long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                            -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                            INT_MAX,   LONG_MAX, LLONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; precision[j]; ++j) {
          for (size_t k = 0; k < sizeof(ints) / sizeof(long long int); ++k) {
            sprintf(format, "_%%%s.%slld_\n", sprintf_flags[i], precision[j]);
            ret21 = s21_sprintf(buf21, format, ints[k]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "32", "64", NULL};
    char *precision[] = {"",
                         "0",
                         "1",
                         "2",
                         "3",
                         "5"
                         "32",
                         "64",
                         NULL};
    char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (int k = 0; precision[k]; ++k) {
            for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
              sprintf(format, "_%%%s%s.%shhd_\n", sprintf_flags[i], width[j],
                      precision[k]);
              ret21 = s21_sprintf(buf21, format, ints[m]);
            }
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "32", "64", NULL};
    char *precision[] = {"",
                         "0",
                         "1",
                         "2",
                         "3",
                         "5"
                         "32",
                         "64",
                         NULL};
    short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                        0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (int k = 0; precision[k]; ++k) {
            for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
              sprintf(format, "_%%%s%s.%shd_\n", sprintf_flags[i], width[j],
                      precision[k]);
              ret21 = s21_sprintf(buf21, format, ints[m]);
            }
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "32", "64", NULL};
    char *precision[] = {"",
                         "0",
                         "1",
                         "2",
                         "3",
                         "5"
                         "32",
                         "64",
                         NULL};
    int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                  -1,       0,        1,      19,       CHAR_MAX, 1078,
                  SHRT_MAX, 10937,    279303, INT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (int k = 0; precision[k]; ++k) {
            for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
              sprintf(format, "_%%%s%s.%sd_\n", sprintf_flags[i], width[j],
                      precision[k]);
              ret21 = s21_sprintf(buf21, format, ints[m]);
            }
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "32", "64", NULL};
    char *precision[] = {"",
                         "0",
                         "1",
                         "2",
                         "3",
                         "5"
                         "32",
                         "64",
                         NULL};
    long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                       1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (int k = 0; precision[k]; ++k) {
            for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
              sprintf(format, "_%%%s%s.%sld_\n", sprintf_flags[i], width[j],
                      precision[k]);
              ret21 = s21_sprintf(buf21, format, ints[m]);
            }
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    char *width[] = {"1", "2", "3", "5", "32", "64", NULL};
    char *precision[] = {"",
                         "0",
                         "1",
                         "2",
                         "3",
                         "5"
                         "32",
                         "64",
                         NULL};
    long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                            -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                            INT_MAX,   LONG_MAX, LLONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; width[j] != NULL; ++j) {
          for (int k = 0; precision[k]; ++k) {
            for (size_t m = 0; m < sizeof(ints) / sizeof(long long int); ++m) {
              sprintf(format, "_%%%s%s.%slld_\n", sprintf_flags[i], width[j],
                      precision[k]);
              ret21 = s21_sprintf(buf21, format, ints[m]);
            }
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 3, 5, 10, 32};
    int wlen = sizeof(width) / sizeof(int);
    char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
            sprintf(format, "_%%%s*hhd_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 3, 5, 10, 32};
    int wlen = sizeof(width) / sizeof(int);
    short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                        0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
            sprintf(format, "_%%%s*hd_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 3, 5, 10, 32};
    int wlen = sizeof(width) / sizeof(int);
    int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                  -1,       0,        1,      19,       CHAR_MAX, 1078,
                  SHRT_MAX, 10937,    279303, INT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
            sprintf(format, "_%%%s*d_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 3, 5, 10, 32};
    int wlen = sizeof(width) / sizeof(int);
    long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                       1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
            sprintf(format, "_%%%s*ld_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 2, 3, 5, 10, 32};
    int wlen = sizeof(width) / sizeof(int);
    long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                            -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                            INT_MAX,   LONG_MAX, LLONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long long int); ++m) {
            sprintf(format, "_%%%s*lld_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int precision[] = {0, 1, 2, 3, 5, 10, 32};
    int plen = (int)(sizeof(precision) / sizeof(int));
    char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};
    buf21 = calloc(1024, sizeof(char));

    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < plen; ++j) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
            sprintf(format, "_%%%s.*hhd_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, precision[j], ints[m]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int precision[] = {0, 1, 2, 3, 5, 10, 32};
    int plen = (int)(sizeof(precision) / sizeof(int));
    long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                            -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                            INT_MAX,   LONG_MAX, LLONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < plen; ++j) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long long int); ++m) {
            sprintf(format, "_%%%s.*lld_\n", sprintf_flags[i]);
            ret21 = s21_sprintf(buf21, format, precision[j], ints[m]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 32};
    int precision[] = {0, 1, 32};
    int wlen = (int)(sizeof(width) / sizeof(int));
    int plen = (int)(sizeof(precision) / sizeof(int));
    int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                  -1,       0,        1,      19,       CHAR_MAX, 1078,
                  SHRT_MAX, 10937,    279303, INT_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int k = 0; k < plen; ++k) {
            for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
              sprintf(format, "_%%%s*.*d_\n", sprintf_flags[i]);
              ret21 =
                  s21_sprintf(buf21, format, width[j], precision[k], ints[m]);
            }
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char *buf21;
    char format[128];
    int width[] = {0, 1, 32};
    int precision[] = {0, 1, 32};
    int wlen = (int)(sizeof(width) / sizeof(int));
    int plen = (int)(sizeof(precision) / sizeof(int));
    long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                       1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};
    buf21 = calloc(1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int j = 0; j < wlen; ++j) {
          for (int k = 0; k < plen; ++k) {
            for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
              sprintf(format, "_%%%s*.*ld_\n", sprintf_flags[i]);
              ret21 =
                  s21_sprintf(buf21, format, width[j], precision[k], ints[m]);
            }
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
}

static double num[] = {0.0,  //-NAN
                       0.0,  // NAN,
                       -INFINITY,
                       -DBL_MAX,
                       -FLT_MAX,
                       -1228338383838381883.2828282828828282,
                       -1234.292987697867897867697687122122192191939339,
                       -1.122212221,
                       -0.2121921121393939113,
                       -FLT_MIN,
                       -0.0,
                       0.0,
                       FLT_MIN,
                       0.21219219121393939113,
                       1.122212221,
                       1234.292217687978677686978622192191939339,
                       1228338383838381883.2828282828828282,
                       FLT_MAX,
                       DBL_MAX,
                       INFINITY};
static int nlen = sizeof(num) / sizeof(double);

static char *width[] = {"1", "10", "64", "100", "1000", NULL};

static char *precision[] = {"",
                            "0",
                            "1",
                            "2"
                            "5",
                            "6",
                            "10",
                            "32",
                            "100",
                            "1000",
                            NULL};

static char *(wp[])[2] = {
    {"100", ""},    {"100", "0"},   {"100", "1"},   {"100", "10"},
    {"100", "6"},   {"100", "32"},  {"100", "100"}, {"100", "120"},
    {"100", "150"}, {"300", "150"},
};
static int wplen = sizeof(wp) / sizeof(wp[0]);

static void test_s21_sprintf_f(void) {
  num[0] = nan("");
  num[1] = -nan("");
  {
    int ret21;
    char format[128];
    char *buf21;
    buf21 = calloc(8 * 1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        sprintf(format, "_%%%sf_\n", sprintf_flags[i]);
        for (int j = 0; j < nlen; ++j) {
          ret21 = s21_sprintf(buf21, format, num[j]);
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char format[128];
    char *buf21;
    buf21 = calloc(8 * 1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int w = 0; width[w] != NULL; ++w) {
          sprintf(format, "_%%%s%sf_\n", sprintf_flags[i], width[w]);
          for (int j = 0; j < nlen; ++j) {
            ret21 = s21_sprintf(buf21, format, num[j]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char format[128];
    char *buf21;
    buf21 = calloc(8 * 1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL && sprintf_flags[i + 1] != NULL;
           i += 2) {
        for (int p = 0; precision[p] != NULL; ++p) {
          sprintf(format, "_%%%s.%sf_\n", sprintf_flags[i], precision[p]);
          for (int j = 0; j < nlen; ++j) {
            ret21 = s21_sprintf(buf21, format, num[j]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char format[128];
    char *buf21;
    buf21 = calloc(8 * 1024, sizeof(char));
    if (buf21 != NULL) {
      for (int i = 0; sprintf_flags[i] != NULL; ++i) {
        for (int w = 0; w < wplen; ++w) {
          sprintf(format, "_%%%s%s.%sf_\n", sprintf_flags[i], wp[w][0],
                  wp[w][1]);
          for (int j = 13; j < nlen; ++j) {
            ret21 = s21_sprintf(buf21, format, num[j]);
          }
        }
      }
    }
    free(buf21);
    (void)ret21;
  }
  {
    int ret21;
    char format[128];
    double n;
    char *buf21;
    buf21 = calloc(8 * 1024, sizeof(char));
    if (buf21 != NULL) {
      n = 0.0;
      sprintf(format, "_%%.0f_\n");
      ret21 = s21_sprintf(buf21, format, n);
      n = 0.0;
      sprintf(format, "_%%.10f_\n");
      ret21 = s21_sprintf(buf21, format, n);
      n = 0.12331231;
      sprintf(format, "_%%f_\n");
      ret21 = s21_sprintf(buf21, format, n);
      n = 0.123847;
      sprintf(format, "_%%.3f_\n");
      ret21 = s21_sprintf(buf21, format, n);
      n = 0.123895;
      sprintf(format, "_%%.3f_\n");
      ret21 = s21_sprintf(buf21, format, n);
      n = 0.879999;
      sprintf(format, "_%%.3f_\n");
      ret21 = s21_sprintf(buf21, format, n);
      n = 0.99978;
      sprintf(format, "_%%.3f_\n");
      ret21 = s21_sprintf(buf21, format, n);
      n = -0.99978;
      sprintf(format, "_%%.3f_\n");
      ret21 = s21_sprintf(buf21, format, n);
      n = 2599.99978;
      sprintf(format, "_%%.3f_\n");
      ret21 = s21_sprintf(buf21, format, n);
      n = -1899.99978;
      sprintf(format, "_%%.3f_\n");
      ret21 = s21_sprintf(buf21, format, n);
    }
    free(buf21);
    (void)ret21;
  }
}
