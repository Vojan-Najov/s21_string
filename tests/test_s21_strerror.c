#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(strerror_cmp) {
  for (int i = -1024; i < 1024; ++i) {
    if (strcmp(strerror(i), s21_strerror(i)))
      printf("%s\n%s\n", strerror(i), s21_strerror(i));
    ck_assert_int_eq(strcmp(strerror(i), s21_strerror(i)), 0);
  }
}
END_TEST

START_TEST(limits_int) {
  ck_assert_int_eq(strcmp(strerror(INT_MAX), s21_strerror(INT_MAX)), 0);
  ck_assert_int_eq(strcmp(strerror(INT_MIN), s21_strerror(INT_MIN)), 0);
}
END_TEST

Suite *suite_s21_strerror(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_strerror");
  tc = tcase_create("tcase_s21_strerror");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, strerror_cmp);
    tcase_add_test(tc, limits_int);
    suite_add_tcase(s, tc);
  }

  return (s);
}
