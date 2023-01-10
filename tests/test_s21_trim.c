#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(one_char) {
  char *str1 = "    a     ";
  char *str2 = " ";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_str_eq(str3, "a");
  free(str3);
}
END_TEST

START_TEST(remove_char) {
  char *str1 = "New Helicopter";
  char *str2 = "N";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_str_eq(str3, "ew Helicopter");
  free(str3);
}
END_TEST

START_TEST(remove_chars) {
  char *str1 = "New Helicoptner";
  char *str2 = "Ner";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_str_eq(str3, "w Helicoptn");
  free(str3);
}
END_TEST

START_TEST(empty_string) {
  char *str1 = "";
  char *str2 = "";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(remove_all) {
  char *str = "empty";
  char *str2 = "empty";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(test_null) {
  char *str = S21_NULL;
  char *str2 = S21_NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

START_TEST(remove_null) {
  char *str = "";
  char *str2 = S21_NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

START_TEST(remove_from_null) {
  char *str = S21_NULL;
  char *str2 = "          ";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_ptr_eq(str3, S21_NULL);
  free(str3);
}
END_TEST

START_TEST(dont_remove_extra) {
  char *str = "helicopter";
  char *str2 = "t";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_ne(str3, "helicop");
  free(str3);
}
END_TEST

Suite *suite_s21_trim(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_trim");
  tc = tcase_create("tcase_s21_trim");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, one_char);
    tcase_add_test(tc, remove_char);
    tcase_add_test(tc, remove_chars);
    tcase_add_test(tc, empty_string);
    tcase_add_test(tc, remove_all);
    tcase_add_test(tc, test_null);
    tcase_add_test(tc, remove_null);
    tcase_add_test(tc, remove_from_null);
    tcase_add_test(tc, dont_remove_extra);
    suite_add_tcase(s, tc);
  }

  return (s);
}
