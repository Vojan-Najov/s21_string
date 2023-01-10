#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(empty_strings) {
  const char *s1 = "";
  const char *s2 = "";
  size_t n = 0;

  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  n = 100;
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
}
END_TEST

START_TEST(empty_string) {
  const char *s1 = "";
  const char *s2 = "dasjdaddaksjsaddakdasdjsasadka";
  size_t n = 0;

  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  n = 10;
  ck_assert_int_lt(strncmp(s1, s2, n), 0);
  ck_assert_int_lt(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_gt(strncmp(s2, s1, n), 0);
  ck_assert_int_gt(s21_strncmp(s2, s1, n), 0);
}
END_TEST

START_TEST(cmp_0) {
  const char s1[] = "sadlksadlaskdslassasdalkasddklaasdsal";
  const char s2[] = "sadlksadlaskdslassasdalkasddklaasdsal";
  size_t n;

  n = 0;
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_eq(strncmp(s2, s1, n), 0);
  ck_assert_int_eq(s21_strncmp(s2, s1, n), 0);
  n = sizeof(s1) - 1;
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_eq(strncmp(s2, s1, n), 0);
  ck_assert_int_eq(s21_strncmp(s2, s1, n), 0);
  n = sizeof(s1);
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_eq(strncmp(s2, s1, n), 0);
  ck_assert_int_eq(s21_strncmp(s2, s1, n), 0);
}
END_TEST

START_TEST(cmp_1) {
  char s1[] = "sadlksadlaskdslassasdalkasddklaasdsal";
  char s2[] = "s_dlksadlaskdslassasdalkasddklaasdsal";
  size_t n;

  n = 0;
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_eq(strncmp(s2, s1, n), 0);
  ck_assert_int_eq(s21_strncmp(s2, s1, n), 0);
  n = 1;
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_eq(strncmp(s2, s1, n), 0);
  ck_assert_int_eq(s21_strncmp(s2, s1, n), 0);
  n = 2;
  ck_assert_int_gt(strncmp(s1, s2, n), 0);
  ck_assert_int_gt(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_lt(strncmp(s2, s1, n), 0);
  ck_assert_int_lt(s21_strncmp(s2, s1, n), 0);
  n = sizeof(s1);
  ck_assert_int_gt(strncmp(s1, s2, n), 0);
  ck_assert_int_gt(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_lt(strncmp(s2, s1, n), 0);
  ck_assert_int_lt(s21_strncmp(s2, s1, n), 0);
}
END_TEST

START_TEST(cmp_2) {
  char s1[] = "sadlksadlask";
  char s2[] = "sadlksadlaskdslassasdalkasddklaasdsal";
  size_t n;

  n = 0;
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_eq(strncmp(s2, s1, n), 0);
  ck_assert_int_eq(s21_strncmp(s2, s1, n), 0);
  n = sizeof(s1) - 1;
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_eq(strncmp(s2, s1, n), 0);
  ck_assert_int_eq(s21_strncmp(s2, s1, n), 0);
  n = sizeof(s1);
  ck_assert_int_lt(strncmp(s1, s2, n), 0);
  ck_assert_int_lt(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_gt(strncmp(s2, s1, n), 0);
  ck_assert_int_gt(s21_strncmp(s2, s1, n), 0);
  n = sizeof(s2);
  ck_assert_int_lt(strncmp(s1, s2, n), 0);
  ck_assert_int_lt(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_gt(strncmp(s2, s1, n), 0);
  ck_assert_int_gt(s21_strncmp(s2, s1, n), 0);
}
END_TEST

START_TEST(cmp_3) {
  char s1[] = "sadlksadlaskdslassasdalkasddklaasds_";
  char s2[] = "sadlksadlaskdslassasdalkasddklaasdsa";
  size_t n;

  n = 0;
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_eq(strncmp(s2, s1, n), 0);
  ck_assert_int_eq(s21_strncmp(s2, s1, n), 0);
  n = sizeof(s1) - 2;
  ck_assert_int_eq(strncmp(s1, s2, n), 0);
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_eq(strncmp(s2, s1, n), 0);
  ck_assert_int_eq(s21_strncmp(s2, s1, n), 0);
  n = sizeof(s1);
  ck_assert_int_lt(strncmp(s1, s2, n), 0);
  ck_assert_int_lt(s21_strncmp(s1, s2, n), 0);
  ck_assert_int_gt(strncmp(s2, s1, n), 0);
  ck_assert_int_gt(s21_strncmp(s2, s1, n), 0);
}
END_TEST

Suite *suite_s21_strncmp(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_strncmp");
  tc = tcase_create("tcase_s21_strncmp");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_strings);
    tcase_add_test(tc, empty_string);
    tcase_add_test(tc, cmp_0);
    tcase_add_test(tc, cmp_1);
    tcase_add_test(tc, cmp_2);
    tcase_add_test(tc, cmp_3);
    suite_add_tcase(s, tc);
  }

  return (s);
}
