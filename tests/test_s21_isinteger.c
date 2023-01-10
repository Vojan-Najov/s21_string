#include <check.h>

#include "s21_string.h"

START_TEST(test_true) {
  ck_assert_int_eq(s21_isinteger("2147483647"), 1);
  ck_assert_int_eq(s21_isinteger("-2147483648"), 1);
  ck_assert_int_eq(s21_isinteger("+0000002147483647"), 1);
  ck_assert_int_eq(s21_isinteger("+000123asc"), 1);
  ck_assert_int_eq(s21_isinteger("asdads"), 1);
}
END_TEST

START_TEST(test_false) {
  ck_assert_int_eq(s21_isinteger("21474836470"), 0);
  ck_assert_int_eq(s21_isinteger("-2147483649"), 0);
  ck_assert_int_eq(s21_isinteger("1000000000000000"), 0);
}
END_TEST

Suite *suite_s21_isinteger(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_isinteger");
  tc = tcase_create("Tcase_s21_isinteger");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_true);
    tcase_add_test(tc, test_false);
    suite_add_tcase(s, tc);
  }

  return (s);
}
