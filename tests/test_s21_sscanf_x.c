#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

static char *(str_fmt[])[7] = {
    {"", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"abc", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"123     +0000000123456", "123 %hhx", "123 %hx", "123 %x", "123 %lx",
     "123 %llx", NULL},
    {"104     +0000000123456", " %123hhx", "123 %hx", "123 %x", "123 %lx",
     "123 %llx", NULL},
    {"-127", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"127", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"255", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0x7f", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0x7f", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0xff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0X7F", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0X7F", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0XFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-32767", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"32767", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"65535", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0x7fff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0x7fff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0x7f1a", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0xffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0X7FFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0X7FFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0X710", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0XFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-2147483647", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"2147483647", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"4294967295", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0x7fffffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0x7fffffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0x78a1285b", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0xffffffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0X7FFFFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0X7FFFFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0XFFFFFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-9223372036854775807", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"9223372036854775807", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"18446744073709551615", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0x7fffffffffffffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0x7fffffffffffffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0xffffffffffffffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0X7FFFFFFFFFFFFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0X7FFFFFFFFFFFFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0XFFFFFFFFFFFFFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-9223372036854775807", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"9223372036854775807", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"18446744073709551615", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0x7fffffffffffffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0x7fffffffffffffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0xffffffffffffffff", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"-0X7FFFFFFFFFFFFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0X7FFFFFFFFFFFFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
    {"0XFFFFFFFFFFFFFFFF", "%hhx", "%hx", "%x", "%lx", "%llx", NULL},
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
    {"0x7fff 1x67ffff", "%x %x"},        {"0x7fff 1x67ffff", "%*x %x"},
    {"0x7fff 1x67ffff", "0%xf %xff"},    {"0x7fff 1x67ffff", "%*x %*x"},
    {"0x7fff 1x67ffff", "%5xf %4xffff"}, {"-0x7fff 1x67ffff", "%x %x"},
    {"0x7f-ff 1x67ff-ff", "%x %x"},      {NULL, NULL},
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
    {"0x7fff 1x67ffff", "%hx %hx"},        {"0x7fff 1x67ffff", "%*hx %hx"},
    {"0x7fff 1x67ffff", "0%hxf %hxff"},    {"0x7fff 1x67ffff", "%*hx %*hx"},
    {"0x7fff 1x67ffff", "%5hxf %4hxffff"}, {"-0x7fff 1x67ffff", "%hx %hx"},
    {"0x7f-ff 1x67ff-ff", "%hx %hx"},      {NULL, NULL},
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
    {"0x7fff 1x67ffff", "%lx %lx"},        {"0x7fff 1x67ffff", "%*lx %lx"},
    {"0x7fff 1x67ffff", "0%lxf %lxff"},    {"0x7fff 1x67ffff", "%*lx %*lx"},
    {"0x7fff 1x67ffff", "%5lxf %4lxffff"}, {"-0x7fff 1x67ffff", "%lx %lx"},
    {"0x7f-ff 1x67ff-ff", "%lx %lx"},      {NULL, NULL},
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
    {"0x7fff 1x67ffff", "%llx %llx"},        {"0x7fff 1x67ffff", "%*llx %llx"},
    {"0x7fff 1x67ffff", "0%llxf %llxff"},    {"0x7fff 1x67ffff", "%*llx %*llx"},
    {"0x7fff 1x67ffff", "%5llxf %4llxffff"}, {"-0x7fff 1x67ffff", "%llx %llx"},
    {"0x7f-ff 1x67ff-ff", "%llx %llx"},      {NULL, NULL},
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

Suite *suite_s21_sscanf_x(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sscanf x");
  tc = tcase_create("s21_sscanf x tcase");

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
