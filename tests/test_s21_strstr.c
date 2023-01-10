#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(empty_strings) {
  const char *h = "";
  const char *n = "";

  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST

START_TEST(empty_needle) {
  const char *h = "abssak aksdk lala 123";
  const char *n = "";

  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST

START_TEST(empty_haystack) {
  const char *h = "";
  const char *n = "abcd";

  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST

START_TEST(not_found) {
  const char *h = "planet Earth";
  const char *n = "planeta";

  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  n = "plaet";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  n = " e";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  n = "th0";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  h = "hol\0a";
  n = "hola";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST

START_TEST(found) {
  const char *h = "planet Earth";
  const char *n = "planet";

  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  n = "et ";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  n = " Ea";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  n = "a";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  n = "t";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  n = "th";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  h = "planet Earth plan";
  n = "plan";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
  h = "plazet Earth plan";
  n = "plan";
  ck_assert_ptr_eq(strstr(h, n), s21_strstr(h, n));
}
END_TEST

Suite *suite_s21_strstr(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_strstr");
  tc = tcase_create("tcase_s21_strstr");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_strings);
    tcase_add_test(tc, empty_needle);
    tcase_add_test(tc, empty_haystack);
    tcase_add_test(tc, not_found);
    tcase_add_test(tc, found);
    suite_add_tcase(s, tc);
  }

  return (s);
}
