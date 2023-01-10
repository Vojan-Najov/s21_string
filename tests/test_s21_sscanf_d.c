#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

static char *(str_fmt[])[7] = {
    {"", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"abc", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"     +0000000123456", " %hhd", " %hd", " %d", " %ld", " %lld", NULL},
    {"123     -000000099123456", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"123     -00000009912345699999999999999",
     "123%d"
     "123%hhd",
     "123%hd", "123%d", "123%ld", "123%lld", NULL},
    {"0", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-0", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"1", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-1", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-129", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-128", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"127", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"128", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"255", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"256", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-32769", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-32768", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"32767", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"32768", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"65535", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"65536", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-2147483649", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-2147483648", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"2147483647", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"2147483648", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"4294967295", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"4294967296", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-9223372036854775808", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-9223372036854775809", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"9223372036854775807", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"9223372036854775808", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"18446744073709551615", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"18446744073709551616", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-9223372036854775809", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"-9223372036854775808", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"9223372036854775807", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"9223372036854775808", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"18446744073709551615", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},
    {"18446744073709551616", "%hhd", "%hd", "%d", "%ld", "%lld", NULL},  //
    {"1", "%hhd", "%hd", "%*d", "%ld", "%lld", NULL},
    {"2147483647", "%1hhd", "%2hd", "%3d", "%4ld", "%5lld", NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

START_TEST(decimal) {
  long long int d, d21;

  for (int i = 0; str_fmt[i][0] != NULL; ++i) {
    d = 123, d21 = 123;
    char *str = str_fmt[i][0];
    char *fmt;
    for (int j = 0; (fmt = str_fmt[i][j]) != NULL; ++j) {
      int ret = sscanf(str, fmt, &d);
      int ret21 = s21_sscanf(str, fmt, &d21);
      if (ret != ret21 || d != d21) {
        printf(
            "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
            "original:%lld\ns21:%lld\n",
            str, fmt, ret, ret21, d, d21);
      }
      ck_assert_int_eq(ret, ret21);
      ck_assert(d == d21);
    }
  }
}
END_TEST

static char *(str_fmt2[])[2] = {
    {"123     -0000000991234569abc    +000000983764", "123%dabc%d"},  //
    {"123 111223 ab777", "%d %*d ab%d"},
    {"123     -0000000991234569abc    +000000983764", "123%3dabc%5d"},
    {"1234", "1%1d%1d4"},
    {"1234", "1%15d%1d4"},
    {"++1 ------21", "%d %d"},
    {"123 1234", "%*d %*d"},
    {"123 21", "1%*1d3 %d"},
    {NULL, NULL}};

START_TEST(two_decimal) {
  for (int i = 0; str_fmt2[i][0] != NULL && str_fmt2[i][1] != NULL; ++i) {
    int d = -123, d21 = -123;
    int dd = -123, dd21 = -123;
    char *str = str_fmt2[i][0];
    char *format = str_fmt2[i][1];
    int ret = sscanf(str, format, &d, &dd);
    int ret21 = s21_sscanf(str, format, &d21, &dd21);
    if (ret != ret21 || d != d21 || dd != dd21) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%d | %d\ns21:%d | %d\n",
          str, format, ret, ret21, d, dd, d21, dd21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(dd, dd21);
  }
}
END_TEST

static char *(str_fmt3[])[2] = {
    {"123     -0000000991234569abc    +000000983764", "123%hdabc%hd"},  //
    {"123 111223 ab777", "%hd %*hd ab%hd"},
    {"123     -0000000991234569abc    +000000983764", "123%3hdabc%5hd"},
    {"1234", "1%1hd%1hd4"},
    {"1234", "1%15hd%1hd4"},
    {"++1 ------21", "%hd %hd"},
    {"123 1234", "%*hd %*hd"},
    {"123 21", "1%*1hd3 %hd"},
    {NULL, NULL}};

START_TEST(two_short_decimal) {
  for (int i = 0; str_fmt3[i][0] != NULL && str_fmt3[i][1] != NULL; ++i) {
    short int d = -123, d21 = -123;
    short int dd = -123, dd21 = -123;
    char *str = str_fmt3[i][0];
    char *format = str_fmt3[i][1];
    int ret = sscanf(str, format, &d, &dd);
    int ret21 = s21_sscanf(str, format, &d21, &dd21);
    if (ret != ret21 || d != d21 || dd != dd21) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%hd | %hd\ns21:%hd | %hd\n",
          str, format, ret, ret21, d, dd, d21, dd21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(dd, dd21);
  }
}
END_TEST

static char *(str_fmt4[])[2] = {
    {"123     -0000000991234569abc    +000000983764", "123%ldabc%ld"},  //
    {"123 111223 ab777", "%ld %*ld ab%ld"},
    {"123     -0000000991234569abc    +000000983764", "123%3ldabc%5ld"},
    {"1234", "1%1ld%1ld4"},
    {"1234", "1%15ld%1ld4"},
    {"++1 ------21", "%ld %ld"},
    {"123 1234", "%*ld %*ld"},
    {"123 21", "1%*1ld3 %ld"},
    {NULL, NULL}};

START_TEST(two_long_decimal) {
  for (int i = 0; str_fmt4[i][0] != NULL && str_fmt4[i][1] != NULL; ++i) {
    long int d = -123, d21 = -123;
    long int dd = -123, dd21 = -123;
    char *str = str_fmt4[i][0];
    char *format = str_fmt4[i][1];
    int ret = sscanf(str, format, &d, &dd);
    int ret21 = s21_sscanf(str, format, &d21, &dd21);
    if (ret != ret21 || d != d21 || dd != dd21) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%ld | %ld\ns21:%ld | %ld\n",
          str, format, ret, ret21, d, dd, d21, dd21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(dd, dd21);
  }
}
END_TEST

static char *(str_fmt5[])[2] = {
    {"123     -0000000991234569abc    +000000983764", "123%lldabc%lld"},  //
    {"123 111223 ab777", "%lld %*lld ab%lld"},
    {"123     -0000000991234569abc    +000000983764", "123%3lldabc%5lld"},
    {"1234", "1%1lld%1lld4"},
    {"1234", "1%15lld%1lld4"},
    {"++1 ------21", "%lld %lld"},
    {"123 1234", "%*lld %*lld"},
    {"123 21", "1%*1lld3 %lld"},
    {"123-21", "%lld%lld"},
    {NULL, NULL}};

START_TEST(two_long_long_decimal) {
  for (int i = 0; str_fmt5[i][0] != NULL && str_fmt5[i][1] != NULL; ++i) {
    long long int d = -123, d21 = -123;
    long long int dd = -123, dd21 = -123;
    char *str = str_fmt5[i][0];
    char *format = str_fmt5[i][1];
    int ret = sscanf(str, format, &d, &dd);
    int ret21 = s21_sscanf(str, format, &d21, &dd21);
    if (ret != ret21 || d != d21 || dd != dd21) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%lld | %lld\ns21:%lld | %lld\n",
          str, format, ret, ret21, d, dd, d21, dd21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(dd, dd21);
  }
}
END_TEST

Suite *suite_s21_sscanf_d(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sscanf d");
  tc = tcase_create("s21_sscanf d tcase");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, decimal);
    tcase_add_test(tc, two_decimal);
    tcase_add_test(tc, two_short_decimal);
    tcase_add_test(tc, two_long_decimal);
    tcase_add_test(tc, two_long_long_decimal);
    suite_add_tcase(s, tc);
  }

  return (s);
}
