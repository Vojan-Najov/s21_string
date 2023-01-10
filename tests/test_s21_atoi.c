#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(check_ints) {
  char buf[1024];

  for (int i = INT_MIN + 1; i < INT_MAX - 10000; i += 100000) {
    sprintf(buf, "   \t  %d", i);
    ck_assert_int_eq(atoi(buf), s21_atoi(buf));
  }
}
END_TEST

START_TEST(check_limits) {
  char buf[1024];

  sprintf(buf, "   \t  %d", INT_MIN);
  ck_assert_int_eq(atoi(buf), s21_atoi(buf));
  sprintf(buf, "   \t  %d", INT_MAX);
  ck_assert_int_eq(atoi(buf), s21_atoi(buf));
}
END_TEST

START_TEST(check_wrong_strs) {
  char buf[1024];

  sprintf(buf, "  - \t  %d", INT_MAX);
  ck_assert_int_eq(atoi(buf), s21_atoi(buf));
  sprintf(buf, "   \t -+%d", INT_MAX);
  ck_assert_int_eq(atoi(buf), s21_atoi(buf));
  sprintf(buf, "   \t -+%dabc", INT_MAX);
  ck_assert_int_eq(atoi(buf), s21_atoi(buf));
  sprintf(buf, "   \t -0000000000000000%dabc", INT_MAX);
  ck_assert_int_eq(atoi(buf), s21_atoi(buf));
}
END_TEST

Suite *suite_s21_atoi(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_atoi");
  tc = tcase_create("Tcase_s21_atoi");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, check_ints);
    tcase_add_test(tc, check_limits);
    tcase_add_test(tc, check_wrong_strs);
    suite_add_tcase(s, tc);
  }

  return (s);
}
