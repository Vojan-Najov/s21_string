#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(empty_format) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  const char *format = "";

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  if (buf != NULL && buf21 != NULL) {
    ret = sprintf(buf, format);
    ret21 = s21_sprintf(buf21, format);
    //   if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    free(buf);
    free(buf21);
  }
}
END_TEST

START_TEST(simple_string) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[4096];

  buf = calloc(4096, sizeof(char));
  buf21 = calloc(4096, sizeof(char));
  for (int i = 0, c = 'a'; i < 4095; ++i, ++c) {
    c = c > 'z' ? 'a' : c;
    format[i] = c;
  }
  format[4095] = '\0';
  if (buf != NULL && buf21 != NULL) {
    ret = sprintf(buf, format);
    ret21 = s21_sprintf(buf21, format);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    free(buf);
    free(buf21);
  }
}
END_TEST

START_TEST(wrong_format) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  const char *format;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  if (buf != NULL && buf21 != NULL) {
    format = "%";
    ret = sprintf(buf, format);
    ret21 = s21_sprintf(buf21, format);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "%*";
    ret = sprintf(buf, format, 1);
    ret21 = s21_sprintf(buf21, format, 1);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "%123";
    ret = sprintf(buf, format);
    ret21 = s21_sprintf(buf21, format);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "%123.";
    ret = sprintf(buf, format);
    ret21 = s21_sprintf(buf21, format);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "%123.*";
    ret = sprintf(buf, format, 1);
    ret21 = s21_sprintf(buf21, format, 1);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "%123.123";
    ret = sprintf(buf, format);
    ret21 = s21_sprintf(buf21, format);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "%-1234q";
    ret = sprintf(buf, format, 1);
    ret21 = s21_sprintf(buf21, format, 1);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "%l";
    ret = sprintf(buf, format, 1);
    ret21 = s21_sprintf(buf21, format, 1);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "asdsda%+h";
    ret = sprintf(buf, format, 1);
    ret21 = s21_sprintf(buf21, format, 1);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "aa%+-";
    ret = sprintf(buf, format);
    ret21 = s21_sprintf(buf21, format);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "aa%+-100";
    ret = sprintf(buf, format);
    ret21 = s21_sprintf(buf21, format);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    format = "a%+-";
    ret = sprintf(buf, format);
    ret21 = s21_sprintf(buf21, format);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", format, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

    char *digits = "11111111111111111111111111111";
    char fmt[128];
    sprintf(fmt, "a%%%sd\n", digits);
    ret = sprintf(buf, fmt, 100);
    ret21 = s21_sprintf(buf21, fmt, 100);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", fmt, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);

#ifndef __APPLE__
    sprintf(fmt, "%%.%sd", digits);
    ret21 = s21_sprintf(buf21, fmt, 100);
    ret = sprintf(buf, fmt, 100);
    //    if (ret != ret21) {
    //      printf("format: %s\n ret = %d ret21 = %d\n", fmt, ret, ret21);
    //    }
    ck_assert_int_eq(ret, ret21);
#endif
  }
  free(buf);
  free(buf21);
}
END_TEST

Suite *suite_s21_sprintf_basic(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf basic");
  tc = tcase_create("TCase_s21_sprintf_basic");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_format);
    tcase_add_test(tc, simple_string);
    tcase_add_test(tc, wrong_format);
    suite_add_tcase(s, tc);
  }

  return (s);
}
