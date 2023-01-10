#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(nil) {
  char *str1 = NULL;
  char *str2 = s21_to_lower(str1);
  ck_assert_ptr_eq(str1, str2);
  free(str2);
}
END_TEST

START_TEST(just_word) {
  char str1[11] = "HELICOPTER";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "helicopter");
  free(str2);
}
END_TEST

START_TEST(just_word_2) {
  char str1[] = "!HELICOPTER!";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "!helicopter!");
  free(str2);
}
END_TEST

START_TEST(few_words) {
  char str1[22] = "SOME MORE HELICOPTERS";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "some more helicopters");
  free(str2);
}
END_TEST

START_TEST(empty_string) {
  char str1[1] = "";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(no_change) {
  char str1[16] = "not helicopter";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "not helicopter");
  free(str2);
}
END_TEST

START_TEST(word_with_number) {
  char str1[14] = "HELICOPTER123";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "helicopter123");
  free(str2);
}
END_TEST

START_TEST(end_symbol) {
  char str1[15] = "NEW\0HELICOPTER";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "new");
  free(str2);
}
END_TEST

Suite *suite_s21_to_lower(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_to_lower");
  tc = tcase_create("tcase_s21_to_lower");

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
