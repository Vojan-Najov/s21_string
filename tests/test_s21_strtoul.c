#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(test) {
  unsigned long int n, n21;
  char *end, *end21;
  char *str;

  str = "    \t0";
  n = strtoul(str, &end, 10);
  n21 = s21_strtoul(str, &end21, 10);
  if (n != n21 || end != end21) {
    printf("%lu\n%lu\n", n, n21);
  }
  ck_assert(n == n21);
  ck_assert_ptr_eq(end, end21);

  str = "     -123shd";
  n = strtoul(str, &end, 0);
  n21 = s21_strtoul(str, &end21, 10);
  if (n != n21 || end != end21) {
    printf("%lu\n%lu\n", n, n21);
  }
  ck_assert(n == n21);
  ck_assert_ptr_eq(end, end21);
}
END_TEST

Suite *suite_s21_strtoul(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_strtoul");
  tc = tcase_create("s21_strtoul tcase");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test);
    suite_add_tcase(s, tc);
  }

  return (s);
}
