#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(empty_strings) {
  char dest[] = "";
  char dest21[] = "";
  const char *src = "";

  ck_assert_ptr_eq(strcpy(dest, src), dest);
  ck_assert_ptr_eq(s21_strcpy(dest21, src), dest21);
  ck_assert_int_eq(strcmp(dest, dest21), 0);
}
END_TEST

START_TEST(empty_src) {
  char dest[] = "abv123";
  char dest21[] = "abv123";
  const char *src = "";

  ck_assert_ptr_eq(strcpy(dest, src), dest);
  ck_assert_ptr_eq(s21_strcpy(dest21, src), dest21);
  ck_assert_int_eq(strcmp(dest, dest21), 0);
}
END_TEST

START_TEST(empty_dest) {
  char dest[100] = "";
  char dest21[100] = "";
  const char *src = "asdjsakd sakjddsada asdkjas";

  ck_assert_ptr_eq(strcpy(dest, src), dest);
  ck_assert_ptr_eq(s21_strcpy(dest21, src), dest21);
  ck_assert_int_eq(strcmp(dest, dest21), 0);
}
END_TEST

START_TEST(copy) {
  char dest[100] = "dasdasasd dsaa adsd\0sasd";
  char dest21[100] = "dasdasasd dsaa adsd\0sasd";
  const char *src = "asdjsakd sakjddsada a\0sdkjas";

  ck_assert_ptr_eq(strcpy(dest, src), dest);
  ck_assert_ptr_eq(s21_strcpy(dest21, src), dest21);
  ck_assert_int_eq(strcmp(dest, dest21), 0);
}
END_TEST

Suite *suite_s21_strcpy(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_strcpy");
  tc = tcase_create("tcase_s21_strcpy");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_strings);
    tcase_add_test(tc, empty_src);
    tcase_add_test(tc, empty_dest);
    tcase_add_test(tc, copy);
    suite_add_tcase(s, tc);
  }

  return (s);
}
