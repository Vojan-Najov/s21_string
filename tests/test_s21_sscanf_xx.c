#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

static char *(str_fmt[])[7] = {
    {"", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"abc", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"123     +0000000123456", "123 %hhX", "123 %hX", "123 %X", "123 %lX",
     "123 %llX", NULL},
    {"-127", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"127", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"255", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0-177", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0177", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0377", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0x7f", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0x7f", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0xff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0X-7F", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0X7F", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0XFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-32767", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"32767", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"65535", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-077777", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"071635", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0x7fff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0x7fff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0x7f1a", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0xffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0X7FFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0X7FFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0X710", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0XFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-2147483647", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"2147483647", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"4294967295", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0x7fffffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0x7fffffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0x78a1285b", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0xffffffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0X7FFFFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0X7FFFFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0XFFFFFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-9223372036854775807", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"9223372036854775807", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"18446744073709551615", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0x7fffffffffffffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0x7fffffffffffffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0xffffffffffffffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0X7FFFFFFFFFFFFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0X7FFFFFFFFFFFFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0XFFFFFFFFFFFFFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-9223372036854775807", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"9223372036854775807", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"18446744073709551615", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0x7fffffffffffffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0x7fffffffffffffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0xffffffffffffffff", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"-0X7FFFFFFFFFFFFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0X7FFFFFFFFFFFFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {"0XFFFFFFFFFFFFFFFF", "%hhX", "%hX", "%X", "%lX", "%llX", NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

START_TEST(hexadecimal) {
  unsigned long long int d, d21;

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
    {"0x7fff 1x67ffff", "%X %X"},        {"0x7fff 1x67ffff", "%*X %X"},
    {"0x7fff 1x67ffff", "0%X %Xff"},     {"0x7fff 1x67ffff", "%*X %*X"},
    {"0x7fff 1x67ffff", "%5Xf %4Xffff"}, {"-0x7fff 1x67ffff", "%X %X"},
    {"0x7f-ff 1x67ff-ff", "%X %X"},      {NULL, NULL},
};

START_TEST(two_hexadecimal) {
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
    {"0X7FFF 1X7FFFF", "%hX %hX"},         {"0X7FFF 1X67FFFF", "%*hX %hX"},
    {"0X7FFF 1X67FFFF", "0%hXF %hXFF"},    {"0X7FFF 1X67FFFF", "%*hX %*hX"},
    {"0X7FFF 1X67FFFF", "%5hXF %4hXFFFF"}, {"-0X7FFF 1X67FFFF", "%hX %hX"},
    {"0X7F-FF 1X67FF-FF", "%hX %hX"},      {NULL, NULL},
};

START_TEST(two_short_hexadecimal) {
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
    {"0X7FFF 1X7FFFF", "%lX %lX"},         {"0X7FFF 1X67FFFF", "%*lX %lX"},
    {"0X7FFF 1X67FFFF", "0%lXF %lXFF"},    {"0X7FFF 1X67FFFF", "%*lX %*lX"},
    {"0X7FFF 1X67FFFF", "%5lXF %4lXFFFF"}, {"-0X7FFF 1X67FFFF", "%lX %lX"},
    {"0X7F-FF 1X67FF-FF", "%lX %lX"},      {NULL, NULL},
};

START_TEST(two_long_hexadecimal) {
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
    {"0X7FFF 1X7FFFF", "%llX %llX"},         {"0X7FFF 1X67FFFF", "%*llX %llX"},
    {"0X7FFF 1X67FFFF", "0%llXF %llXFF"},    {"0X7FFF 1X67FFFF", "%*llX %*llX"},
    {"0X7FFF 1X67FFFF", "%5llXF %4llXFFFF"}, {"-0X7FFF 1X67FFFF", "%llX %llX"},
    {"0X7F-FF 1X67FF-FF", "%llX %llX"},      {NULL, NULL},
};

START_TEST(two_long_long_hexadecimal) {
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

Suite *suite_s21_sscanf_xx(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sscanf X");
  tc = tcase_create("s21_sscanf X tcase");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, hexadecimal);
    tcase_add_test(tc, two_hexadecimal);
    tcase_add_test(tc, two_short_hexadecimal);
    tcase_add_test(tc, two_long_hexadecimal);
    tcase_add_test(tc, two_long_long_hexadecimal);
    suite_add_tcase(s, tc);
  }

  return (s);
}
