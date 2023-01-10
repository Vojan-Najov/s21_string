#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(empty_string) {
  const char str[] = "";
  int c;

  c = 'a';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
  c = '\0';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(not_found) {
  const char str[] = "abvdefg";
  int c;

  c = 'A';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
  c = '\0';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(found_1) {
  const char str[] = "abvdefg";
  int c = 'a';

  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
  c = '\0';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(found_2) {
  const char str[] = "abvdevfgv";
  int c = 'v';

  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(found_unsigned_char) {
  const char str[] = "abvdefg";
  int c = 'b' | 0x11100;

  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

Suite *suite_s21_strchr(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_strchr");
  tc = tcase_create("tcase_s21_strchr");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_string);
    tcase_add_test(tc, not_found);
    tcase_add_test(tc, found_1);
    tcase_add_test(tc, found_2);
    tcase_add_test(tc, found_unsigned_char);
    suite_add_tcase(s, tc);
  }

  return (s);
}
