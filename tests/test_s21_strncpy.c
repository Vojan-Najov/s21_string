#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(empty_strings) {
  char dest[10] = "";
  char dest21[10] = "";
  const char *src = "";
  size_t n;

  n = 0;
  ck_assert_ptr_eq(strncpy(dest, src, n), dest);
  ck_assert_ptr_eq(s21_strncpy(dest21, src, n), dest21);
  ck_assert_int_eq(strcmp(dest, dest21), 0);
  n = 10;
  ck_assert_ptr_eq(strncpy(dest, src, n), dest);
  ck_assert_ptr_eq(s21_strncpy(dest21, src, n), dest21);
  ck_assert_int_eq(memcmp(dest, dest21, n), 0);
}
END_TEST

START_TEST(empty_src) {
  char dest[20] = "adsadsadasdaasa";
  char dest21[20] = "adsadsadasdaasa";
  const char *src = "";
  size_t n;

  n = 0;
  ck_assert_ptr_eq(strncpy(dest, src, n), dest);
  ck_assert_ptr_eq(s21_strncpy(dest21, src, n), dest21);
  ck_assert_int_eq(strcmp(dest, dest21), 0);
  n = 1;
  ck_assert_ptr_eq(strncpy(dest, src, n), dest);
  ck_assert_ptr_eq(s21_strncpy(dest21, src, n), dest21);
  ck_assert_int_eq(strcmp(dest, dest21), 0);
  n = 20;
  ck_assert_ptr_eq(strncpy(dest, src, n), dest);
  ck_assert_ptr_eq(s21_strncpy(dest21, src, n), dest21);
  ck_assert_int_eq(memcmp(dest, dest21, n), 0);
}
END_TEST

START_TEST(zero_n) {
  char dest[20] = "adsadsadasdaasa";
  char dest21[20] = "adsadsadasdaasa";
  const char *src = "asd sada";
  size_t n = 0;

  ck_assert_ptr_eq(strncpy(dest, src, n), dest);
  ck_assert_ptr_eq(s21_strncpy(dest21, src, n), dest21);
  ck_assert_int_eq(strcmp(dest, dest21), 0);
}
END_TEST

START_TEST(n_eq_srclen) {
  char dest[] = "adsadsadasdaasa";
  char dest21[] = "adsadsadasdaasa";
  const char *src = "asd sada";
  size_t n = sizeof(src) - 1;

  ck_assert_ptr_eq(strncpy(dest, src, n), dest);
  ck_assert_ptr_eq(s21_strncpy(dest21, src, n), dest21);
  ck_assert_int_eq(memcmp(dest, dest21, sizeof(dest)), 0);
}
END_TEST

START_TEST(n_gt_srclen) {
  char dest[] = "adsadsadasdaasa               ";
  char dest21[] = "adsadsadasdaasa               ";
  const char *src = "asd sada";
  size_t n = sizeof(src) + 7;

  ck_assert_ptr_eq(strncpy(dest, src, n), dest);
  ck_assert_ptr_eq(s21_strncpy(dest21, src, n), dest21);
  ck_assert_int_eq(memcmp(dest, dest21, sizeof(dest)), 0);
}
END_TEST

START_TEST(n_lt_srclen) {
  char dest[] = "adsadsadasdaasa               ";
  char dest21[] = "adsadsadasdaasa               ";
  const char *src = "asd sada";
  size_t n = sizeof(src) - 3;

  ck_assert_ptr_eq(strncpy(dest, src, n), dest);
  ck_assert_ptr_eq(s21_strncpy(dest21, src, n), dest21);
  ck_assert_int_eq(memcmp(dest, dest21, sizeof(dest)), 0);
}
END_TEST

Suite *suite_s21_strncpy(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_strncpy");
  tc = tcase_create("tcase_s21_strncpy");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_strings);
    tcase_add_test(tc, empty_src);
    tcase_add_test(tc, zero_n);
    tcase_add_test(tc, n_eq_srclen);
    tcase_add_test(tc, n_gt_srclen);
    tcase_add_test(tc, n_lt_srclen);
    suite_add_tcase(s, tc);
  }

  return (s);
}
