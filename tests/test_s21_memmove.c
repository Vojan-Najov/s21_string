#include <check.h>
#include <limits.h>
#include <string.h>

#include "s21_string.h"

START_TEST(zero_size_1) {
  void *dest = NULL;
  void *src = NULL;
  size_t n = 0;

  ck_assert_ptr_eq(s21_memmove(dest, src, n), s21_memmove(dest, src, n));
}
END_TEST

START_TEST(zero_size_2) {
  char dest[10] = "";
  char src[] = "hello";
  size_t n = 0;

  ck_assert_ptr_eq(s21_memmove(dest, src, n), s21_memmove(dest, src, n));
  dest[0] = 'a';
  dest[1] = '\0';
  s21_memmove(dest, src, n);
  ck_assert(memcmp(dest, "a", 2) == 0);
}
END_TEST

START_TEST(zero_size_3) {
  char buf[] = "verylongstring";
  char *dest = buf + 5;
  char *src = buf + 1;
  size_t n = 0;

  ck_assert_ptr_eq(s21_memmove(dest, src, n), s21_memmove(dest, src, n));
  s21_memmove(dest, src, n);
  ck_assert(memcmp(dest, "ongstring", sizeof("ongstring") / sizeof(char)) == 0);
}
END_TEST

START_TEST(copy) {
  long src[1024];
  long dest21[1024];
  long dest[1024];
  size_t n = 1024;

  for (int i = 0, k = INT_MAX; i < 1024; ++i, --k) {
    src[i] = k;
  }
  ck_assert_ptr_eq(s21_memmove(dest21, src, n * sizeof(long)), dest21);
  memmove(dest, src, n * sizeof(long));
  ck_assert(memcmp(dest21, dest, n * sizeof(long)) == 0);
}
END_TEST

START_TEST(copy_from_right_to_left) {
  long buf21[1024];
  long buf[1024];
  size_t n1 = 256;
  size_t n2 = 1024 - 256;

  for (int i = 0, k = INT_MAX; i < 1024; ++i, --k) {
    buf[i] = k;
    buf21[i] = k;
  }
  ck_assert_ptr_eq(s21_memmove(buf21, buf21 + n1, n2 * sizeof(long)), buf21);
  memmove(buf, buf + n1, n2 * sizeof(long));
  ck_assert(memcmp(buf21, buf, 1024 * sizeof(long)) == 0);
}
END_TEST

START_TEST(copy_from_left_to_right) {
  long buf21[1024];
  long buf[1024];
  size_t n1 = 256;
  size_t n2 = 1024 - 256;

  for (int i = 0, k = INT_MAX; i < 1024; ++i, --k) {
    buf[i] = k;
    buf21[i] = k;
  }
  ck_assert_ptr_eq(s21_memmove(buf21 + n1, buf21, n2 * sizeof(long)),
                   buf21 + n1);
  memmove(buf + n1, buf, n2 * sizeof(long));
  ck_assert(memcmp(buf21, buf, 1024 * sizeof(long)) == 0);
}
END_TEST

START_TEST(copy_from_begin_to_begin) {
  long buf21[1024];
  long buf[1024];
  size_t n = 1024;

  for (int i = 0, k = INT_MAX; i < 1024; ++i, --k) {
    buf[i] = k;
    buf21[i] = k;
  }
  ck_assert_ptr_eq(s21_memmove(buf21, buf21, n * sizeof(long)), buf21);
  memmove(buf, buf, n * sizeof(long));
  ck_assert(memcmp(buf21, buf, n * sizeof(long)) == 0);
}
END_TEST

Suite *suite_s21_memmove(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_memmove");
  tc = tcase_create("tcase_s21_memmove");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, zero_size_1);
    tcase_add_test(tc, zero_size_2);
    tcase_add_test(tc, zero_size_3);
    tcase_add_test(tc, copy);
    tcase_add_test(tc, copy_from_right_to_left);
    tcase_add_test(tc, copy_from_left_to_right);
    tcase_add_test(tc, copy_from_begin_to_begin);
    suite_add_tcase(s, tc);
  }

  return (s);
}
