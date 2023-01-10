#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(simple_cases) {
  unsigned long long int d, d21;
  unsigned long long int n = 109, n21 = 109;
  char c[10] = {0};
  char c21[10] = {0};
  char *str, *fmt;
  int ret, ret21;

  str = "";
  fmt = "%n";
  ret = sscanf(str, fmt, &n);
  ret21 = s21_sscanf(str, fmt, &n21);
  if (ret != ret21 || n != n21) {
    printf(
        "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
        "original:%lld\ns21:%lld\n",
        str, fmt, ret, ret21, n, n21);
  }
  ck_assert_int_eq(ret, ret21);
  ck_assert(n == n21);

  str = "123";
  fmt = "123%n";
  ret = sscanf(str, fmt, &n);
  ret21 = s21_sscanf(str, fmt, &n21);
  if (ret != ret21 || n != n21) {
    printf(
        "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
        "original:%lld\ns21:%lld\n",
        str, fmt, ret, ret21, n, n21);
  }
  ck_assert_int_eq(ret, ret21);
  ck_assert(n == n21);

  str = "12abc";
  fmt = "%2cabc%n";
  ret = sscanf(str, fmt, c, &n);
  ret21 = s21_sscanf(str, fmt, c21, &n21);
  if (ret != ret21 || n != n21) {
    printf(
        "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
        "original:%lld\ns21:%lld\n",
        str, fmt, ret, ret21, n, n21);
  }
  ck_assert_int_eq(ret, ret21);
  ck_assert(n == n21);

  str = "12abc1234543123";
  fmt = "%2cabc%d%n";
  ret = sscanf(str, fmt, c, &d, &n);
  ret21 = s21_sscanf(str, fmt, c21, &d21, &n21);
  if (ret != ret21 || n != n21) {
    printf(
        "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
        "original:%lld\ns21:%lld\n",
        str, fmt, ret, ret21, n, n21);
  }
  ck_assert_int_eq(ret, ret21);
  ck_assert(n == n21);
}
END_TEST

Suite *suite_s21_sscanf_n(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sscanf n");
  tc = tcase_create("s21_sscanf n tcase");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, simple_cases);
    suite_add_tcase(s, tc);
  }

  return (s);
}
