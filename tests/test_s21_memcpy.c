#include <check.h>
#include <limits.h>
#include <string.h>

#include "s21_string.h"

START_TEST(zero_size_1) {
  void *src = NULL;
  void *dest = NULL;
  size_t n = 0;

  ck_assert_ptr_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(zero_size_2) {
  char src[] = "hello";
  char dest[10] = {'\0'};
  size_t n = 0;

  ck_assert_ptr_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
  dest[0] = '\0';
  s21_memcpy(dest, src, n);
  ck_assert(dest[0] == '\0');
}
END_TEST

START_TEST(copy_1) {
  char src[] = "hello";
  char dest[10] = "bye";
  size_t n = sizeof(src) / sizeof(char);

  ck_assert_ptr_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
  dest[0] = '\0';
  s21_memcpy(dest, src, n);
  ck_assert(memcmp(dest, src, n) == 0);
}
END_TEST

START_TEST(copy_2) {
  int src[4096];
  int dest[1024];
  size_t n = 1024 * sizeof(int);

  for (int k = INT_MAX, i = 0; i < 4096; ++i, --k) {
    src[i] = k;
  }
  s21_memcpy(dest, src, n);
  ck_assert(memcmp(dest, src, n) == 0);
}
END_TEST

Suite *suite_s21_memcpy(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_memcpy");
  tc = tcase_create("tcase_s21_memcpy");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, zero_size_1);
    tcase_add_test(tc, zero_size_2);
    tcase_add_test(tc, copy_1);
    tcase_add_test(tc, copy_2);
    suite_add_tcase(s, tc);
  }

  return (s);
}
