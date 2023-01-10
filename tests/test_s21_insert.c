#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(two_words) {
  char str1[5] = "heli";
  char str2[7] = "copter";
  char *str3 = (char *)s21_insert(str1, str2, 4);
  ck_assert_str_eq(str3, "helicopter");
  free(str3);
}
END_TEST

START_TEST(check_for_error_null) {
  char str1[1] = "";
  char str2[5] = "null";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

START_TEST(split_word) {
  char str1[11] = "helicopter";
  char str2[2] = " ";
  char *str3 = (char *)s21_insert(str1, str2, 4);
  ck_assert_str_eq(str3, "heli copter");
  free(str3);
}
END_TEST

START_TEST(add_to_null) {
  char str1[11] = "helicopter";
  char *str2 = S21_NULL;
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

START_TEST(add_to_start) {
  char str1[7] = "copter";
  char str2[5] = "heli";
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_str_eq(str3, "helicopter");
  free(str3);
}
END_TEST

START_TEST(wrong_location) {
  char str1[5] = "heli";
  char str2[7] = "copter";
  char *str3 = (char *)s21_insert(str1, str2, -1);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

START_TEST(insert_to_null) {
  char *str1 = S21_NULL;
  char str2[7] = "copter";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

START_TEST(string_size_check) {
  char str1[2] = " ";
  char str2[5] = "heli";
  char *str3 = (char *)s21_insert(str1, str2, 3);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

START_TEST(null_to_null) {
  char *str1 = S21_NULL;
  char *str2 = S21_NULL;
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

START_TEST(empty_addition) {
  char str1[1] = "";
  char str2[1] = "";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

Suite *suite_s21_insert(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_insert");
  tc = tcase_create("tcase_s21_insert");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, two_words);
    tcase_add_test(tc, check_for_error_null);
    tcase_add_test(tc, split_word);
    tcase_add_test(tc, add_to_null);
    tcase_add_test(tc, add_to_start);
    tcase_add_test(tc, wrong_location);
    tcase_add_test(tc, insert_to_null);
    tcase_add_test(tc, string_size_check);
    tcase_add_test(tc, null_to_null);
    tcase_add_test(tc, empty_addition);
    suite_add_tcase(s, tc);
  }

  return (s);
}
