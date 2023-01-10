#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(empty_strings) {
  const char *s = "";
  const char *reject = "";

  ck_assert(strcspn(s, reject) == s21_strcspn(s, reject));
}
END_TEST

START_TEST(empty_str) {
  const char *s = "";
  const char *reject = "sad ajsjqp 129291- 29s";

  ck_assert(strcspn(s, reject) == s21_strcspn(s, reject));
}
END_TEST

START_TEST(empty_reject) {
  const char *s = "asd quwi saj1 29219 \n";
  const char *reject = "";

  ck_assert(strcspn(s, reject) == s21_strcspn(s, reject));
}
END_TEST

START_TEST(zero_result) {
  const char *s = "1234asdda";
  const char *reject = "4321";

  ck_assert(strcspn(s, reject) == 0);
  ck_assert(strcspn(s, reject) == s21_strcspn(s, reject));
}
END_TEST

START_TEST(nonzero_result) {
  const char *s = "asdkaskak123456789 asdda";
  const char *reject = "987654321";

  ck_assert(strcspn(s, reject) != 0);
  ck_assert(strcspn(s, reject) == s21_strcspn(s, reject));
}
END_TEST

Suite *suite_s21_strcspn(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_strcspn");
  tc = tcase_create("tcase_s21_strcspn");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_strings);
    tcase_add_test(tc, empty_str);
    tcase_add_test(tc, empty_reject);
    tcase_add_test(tc, zero_result);
    tcase_add_test(tc, nonzero_result);
    suite_add_tcase(s, tc);
  }

  return (s);
}
