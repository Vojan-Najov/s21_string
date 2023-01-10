#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(zero_size_1) {
  void *s = NULL;
  int c = '\0';
  size_t n = 0;

  ck_assert_ptr_eq(s21_memset(s, c, n), memset(s, c, n));
}
END_TEST

START_TEST(zero_size_2) {
  char s[] = "hello";
  int c = '\0';
  size_t n = 0;

  s21_memset(s, c, n);
  ck_assert(memcpy(s, "hello", sizeof("hello") / sizeof(char)));
  ck_assert_ptr_eq(s21_memset(s, c, n), memset(s, c, n));
}
END_TEST

START_TEST(set_1) {
  char s[100];
  char s21[100];
  int c = 'a';

  ck_assert_ptr_eq(s21_memset(s21, c, 20), s21);
  memset(s, c, 20);
  ++c;
  ck_assert_ptr_eq(s21_memset(s21 + 20, c, 20), s21 + 20);
  memset(s + 20, c, 20);
  ++c;
  ck_assert_ptr_eq(s21_memset(s21 + 40, c, 20), s21 + 40);
  memset(s + 40, c, 20);
  ++c;
  ck_assert_ptr_eq(s21_memset(s21 + 60, c, 20), s21 + 60);
  memset(s + 60, c, 20);
  ++c;
  ck_assert_ptr_eq(s21_memset(s21 + 80, c, 20), s21 + 80);
  memset(s + 80, c, 20);
  ck_assert(memcmp(s, s21, 100) == 0);
}
END_TEST

START_TEST(set_2) {
  long s[1024];
  long s21[1024];
  int c = 0x18f;
  size_t n = 1024 * sizeof(long);

  ck_assert_ptr_eq(s21_memset(s21, c, n), s21);
  memset(s, c, n);
  ck_assert(memcmp(s21, s, n) == 0);
  c &= 0xff;
  unsigned char *ptr21 = (unsigned char *)s21;
  unsigned char *ptr = (unsigned char *)s;
  for (size_t i = 0; i < n; ++i) {
    ck_assert(ptr21[i] == c && ptr[i] == c);
  }
}

Suite *suite_s21_memset(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_memset");
  tc = tcase_create("tcase_s21_memset");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, zero_size_1);
    tcase_add_test(tc, zero_size_2);
    tcase_add_test(tc, set_1);
    tcase_add_test(tc, set_2);
    suite_add_tcase(s, tc);
  }

  return (s);
}
