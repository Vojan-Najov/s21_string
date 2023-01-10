#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(nil) {
  char *str1 = NULL;
  char *str2 = s21_to_upper(str1);
  ck_assert_ptr_eq(str1, str2);
  free(str2);
}
END_TEST

START_TEST(just_word) {
  char str1[11] = "helicopter";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "HELICOPTER");
  free(str2);
}
END_TEST

START_TEST(just_word_2) {
  char str1[] = "{helicopter}";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "{HELICOPTER}");
  free(str2);
}
END_TEST

START_TEST(few_words) {
  char str1[22] = "some more helicopters";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "SOME MORE HELICOPTERS");
  free(str2);
}
END_TEST

START_TEST(empty_string) {
  char str1[1] = "";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(no_change) {
  char str1[15] = "NOT HELICOPTER";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "NOT HELICOPTER");
  free(str2);
}
END_TEST

START_TEST(word_with_number) {
  char str1[14] = "helicopter123";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "HELICOPTER123");
  free(str2);
}
END_TEST

START_TEST(end_symbol) {
  char str1[15] = "new\0helicopter";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "NEW");
  free(str2);
}
END_TEST

Suite *suite_s21_to_upper(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_to_upper");
  tc = tcase_create("tcase_s21_to_upper");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, nil);
    tcase_add_test(tc, just_word);
    tcase_add_test(tc, just_word_2);
    tcase_add_test(tc, few_words);
    tcase_add_test(tc, empty_string);
    tcase_add_test(tc, no_change);
    tcase_add_test(tc, word_with_number);
    tcase_add_test(tc, end_symbol);
    suite_add_tcase(s, tc);
  }

  return (s);
}
