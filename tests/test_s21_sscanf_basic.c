#include <check.h>
#include <stdio.h>

#include "s21_string.h"

static char *str_fmt[][2] = {{"", ""},         {"1", ""},       {"", "a"},
                             {"a", "%q"},
#ifndef __MUSL__
                             {"a", "%h"},
#endif
                             {"123", "234"},   {"123", "1234"}, {"1234", "123"},
                             {"1234", "123a"}, {NULL, NULL}};

START_TEST(basic) {
  char *str;
  int ret, ret21;
  char *format;

  for (int i = 0; str_fmt[i][0] != NULL; ++i) {
    ret = ret21 = -10;
    str = str_fmt[i][0];
    format = str_fmt[i][1];
    ret = sscanf(str, format);
    ret21 = s21_sscanf(str, format);
    if (ret != ret21) {
      printf("str _%s_\nformat _%s_\nret = %d, ret21 = %d\n", str, format, ret,
             ret21);
    }
    ck_assert_int_eq(ret, ret21);
  }
}

START_TEST(percent) {
  char *str;
  int ret, ret21;
  char *format;

  format = "%%";
  str = "a";
  ret = sscanf(str, format);
  ret21 = s21_sscanf(str, format);
  if (ret != ret21) {
    printf("str _%s_\nformat _%s_\nret = %d, ret21 = %d\n", str, format, ret,
           ret21);
  }
  ck_assert_int_eq(ret, ret21);

  format = "%%";
  str = "%";
  ret = sscanf(str, format);
  ret21 = s21_sscanf(str, format);
  if (ret != ret21) {
    printf("str _%s_\nformat _%s_\nret = %d, ret21 = %d\n", str, format, ret,
           ret21);
  }
  ck_assert_int_eq(ret, ret21);

  format = "123%%";
  str = "123%";
  ret = sscanf(str, format);
  ret21 = s21_sscanf(str, format);
  if (ret != ret21) {
    printf("str _%s_\nformat _%s_\nret = %d, ret21 = %d\n", str, format, ret,
           ret21);
  }
  ck_assert_int_eq(ret, ret21);

  format = "123%%";
  str = "23%";
  ret = sscanf(str, format);
  ret21 = s21_sscanf(str, format);
  if (ret != ret21) {
    printf("str _%s_\nformat _%s_\nret = %d, ret21 = %d\n", str, format, ret,
           ret21);
  }
  ck_assert_int_eq(ret, ret21);

  format = "123%%123";
  str = "123%123";
  ret = sscanf(str, format);
  ret21 = s21_sscanf(str, format);
  if (ret != ret21) {
    printf("str _%s_\nformat _%s_\nret = %d, ret21 = %d\n", str, format, ret,
           ret21);
  }
  ck_assert_int_eq(ret, ret21);
}
END_TEST

Suite *suite_s21_sscanf_basic(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sscanf basic");
  tc = tcase_create("s21_sscanf basic tcase");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, basic);
    tcase_add_test(tc, percent);
    suite_add_tcase(s, tc);
  }

  return (s);
}
