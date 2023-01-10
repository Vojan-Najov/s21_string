#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(test) {
  long int n, n21;
  char *end, *end21;
  char *str;

  str = "    \t0";
  n = strtol(str, &end, 10);
  n21 = s21_strtol(str, &end21, 10);
  ck_assert(n == n21);
  ck_assert_ptr_eq(end, end21);

  str = "     -382847ashd";
  n = strtol(str, &end, 0);
  n21 = s21_strtol(str, &end21, 10);
  ck_assert(n == n21);
  ck_assert_ptr_eq(end, end21);
}
END_TEST

Suite *suite_s21_strtol(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_strtol");
  tc = tcase_create("s21_strtol tcase");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test);
    suite_add_tcase(s, tc);
  }

  return (s);
}
