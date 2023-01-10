#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(empty_strings) {
  const char *s = "";
  const char *accept = "";

  ck_assert(strspn(s, accept) == s21_strspn(s, accept));
}
END_TEST

START_TEST(empty_str) {
  const char *s = "";
  const char *accept = "sad ajsjqp 129291- 29s";

  ck_assert(strspn(s, accept) == s21_strspn(s, accept));
}
END_TEST

START_TEST(empty_accept) {
  const char *s = "asd quwi saj1 29219 \n";
  const char *accept = "";

  ck_assert(strspn(s, accept) == s21_strspn(s, accept));
}
END_TEST

START_TEST(zero_result) {
  const char *s = "a1234asdda";
  const char *accept = "4321";

  ck_assert(strspn(s, accept) == 0);
  ck_assert(strspn(s, accept) == s21_strspn(s, accept));
}
END_TEST

START_TEST(nonzero_result) {
  const char *s = "123456789 asdda";
  const char *accept = "987654321";

  ck_assert(strspn(s, accept) != 0);
  ck_assert(strspn(s, accept) == s21_strspn(s, accept));
}
END_TEST

Suite *suite_s21_strspn(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_strspn");
  tc = tcase_create("tcase_s21_strspn");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_strings);
    tcase_add_test(tc, empty_str);
    tcase_add_test(tc, empty_accept);
    tcase_add_test(tc, zero_result);
    tcase_add_test(tc, nonzero_result);
    suite_add_tcase(s, tc);
  }

  return (s);
}
