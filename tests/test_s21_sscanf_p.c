#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

static char *(str_fmt[])[7] = {
    {"", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"abc", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"123     +0000000123456", "123 %hhp", "123 %hp", "123 %p", "123 %lp",
     "123 %llp", NULL},
    {"104     +0000000123456", " %123hhp", "123 %hp", "123 %p", "123 %lp",
     "123 %llp", NULL},
    {"-127", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"127", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"255", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0x7f", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0x7f", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0xff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0X7F", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0X7F", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0XFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-32767", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"32767", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"65535", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0x7fff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0x7fff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0x7f1a", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0xffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0X7FFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0X7FFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0X710", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0XFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-2147483647", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"2147483647", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"4294967295", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0x7fffffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0x7fffffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0x78a1285b", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0xffffffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0X7FFFFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0X7FFFFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0XFFFFFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-9223372036854775807", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"9223372036854775807", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"18446744073709551615", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0x7fffffffffffffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0x7fffffffffffffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0xffffffffffffffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0X7FFFFFFFFFFFFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0X7FFFFFFFFFFFFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0XFFFFFFFFFFFFFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-9223372036854775807", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"9223372036854775807", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"18446744073709551615", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0x7fffffffffffffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0x7fffffffffffffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0xffffffffffffffff", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"-0X7FFFFFFFFFFFFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0X7FFFFFFFFFFFFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {"0XFFFFFFFFFFFFFFFF", "%hhp", "%hp", "%p", "%lp", "%llp", NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

START_TEST(decimal) {
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
    {"123     -0000000991234569abc    +000000983764", "123%pabc%p"},
    {"123 111223 ab777", "%p %*p ab%p"},
    {"123     -0000000991234569abc    +000000983764", "123%3pabc%5p"},
    {"1234", "1%1p%1p4"},
    {"1234", "1%15p%1p4"},
    {"++1 ------21", "%p %p"},
    {"123 1234", "%*p %*p"},
    {NULL, NULL}};

START_TEST(two_decimal) {
  for (int i = 0; str_fmt2[i][0] != NULL && str_fmt2[i][1] != NULL; ++i) {
    char c1, c2;
    void *p1 = &c1, *p2 = &c2;
    void *ptr1 = &c1, *ptr2 = &c2;
    char *str = str_fmt2[i][0];
    char *format = str_fmt2[i][1];
    int ret = sscanf(str, format, &p1, &p2);
    int ret21 = s21_sscanf(str, format, &ptr1, &ptr2);
    if (ret != ret21 || p1 != ptr1 || p2 != ptr2) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%p | %p\ns21:%p | %p\n",
          str, format, ret, ret21, p1, p2, ptr1, ptr2);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_ptr_eq(p1, ptr1);
    ck_assert_ptr_eq(p2, ptr2);
  }
}
END_TEST

static char *(str_fmt3[])[2] = {
    {"01234567 123", "%p %p"},
    {"01234567 123", "%*p %p"},
    {"01234567 123", "%*p %*p"},
    {"01234567 123", "%5p567 %1p23"},
    {"01234567 123", "%p34%p"},
    {"-1023 -07654", "%p %p"},
    {NULL, NULL},
};

START_TEST(two_octal) {
  for (int i = 0; str_fmt3[i][0] != NULL && str_fmt3[i][1] != NULL; ++i) {
    char c1, c2;
    void *p1 = &c1, *p2 = &c2;
    void *ptr1 = &c1, *ptr2 = &c2;
    char *str = str_fmt3[i][0];
    char *format = str_fmt3[i][1];
    int ret = sscanf(str, format, &p1, &p2);
    int ret21 = s21_sscanf(str, format, &ptr1, &ptr2);
    if (ret != ret21 || p1 != ptr1 || p2 != ptr2) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%p | %p\ns21:%p | %p\n",
          str, format, ret, ret21, p1, p2, ptr1, ptr2);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_ptr_eq(p1, ptr1);
    ck_assert_ptr_eq(p2, ptr2);
  }
}
END_TEST

static char *(str_fmt4[])[2] = {
    {"0x7fff 1x67ffff", "%p %p"},        {"0x7fff 1x67ffff", "%*p %p"},
    {"0x7fff 1x67ffff", "0%pf %pff"},    {"0x7fff 1x67ffff", "%*p %*p"},
    {"0x7fff 1x67ffff", "%5pf %4pffff"}, {"-0x7fff 1x67ffff", "%p %p"},
    {"0x7f-ff 1x67ff-ff", "%p %p"},      {NULL, NULL},
};

START_TEST(two_hexadecimal) {
  for (int i = 0; str_fmt4[i][0] != NULL && str_fmt4[i][1] != NULL; ++i) {
    char c1, c2;
    void *p1 = &c1, *p2 = &c2;
    void *ptr1 = &c1, *ptr2 = &c2;
    char *str = str_fmt4[i][0];
    char *format = str_fmt4[i][1];
    int ret = sscanf(str, format, &p1, &p2);
    int ret21 = s21_sscanf(str, format, &ptr1, &ptr2);
    if (ret != ret21 || p1 != ptr1 || p2 != ptr2) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%p | %p\ns21:%p | %p\n",
          str, format, ret, ret21, p1, p2, ptr1, ptr2);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_ptr_eq(p1, ptr1);
    ck_assert_ptr_eq(p2, ptr2);
  }
}
END_TEST

Suite *suite_s21_sscanf_p(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sscanf p");
  tc = tcase_create("s21_sscanf p tcase");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, decimal);
    tcase_add_test(tc, two_decimal);
    tcase_add_test(tc, two_octal);
    tcase_add_test(tc, two_hexadecimal);
    suite_add_tcase(s, tc);
  }

  return (s);
}
