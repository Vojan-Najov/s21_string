#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(zero_size_1) {
  char buf1[] = "asc";
  char buf2[] = "";
  size_t n = 0;

  ck_assert_int_eq(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_eq(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(zero_size_2) {
  void *buf1 = NULL;
  void *buf2 = NULL;
  size_t n = 0;

  ck_assert_int_eq(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_eq(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(eq_1) {
  char buf1[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
  char buf2[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
  size_t n = sizeof(buf1) / sizeof(char);

  ck_assert_int_eq(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_eq(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(eq_2) {
  char *buf = NULL;
  size_t n = 1024;

  buf = (char *)calloc(sizeof(char), sizeof(*buf) * 1024);
  if (buf != NULL) {
    ck_assert_int_eq(s21_memcmp(buf, buf, n), 0);
    ck_assert_int_eq(memcmp(buf, buf, n), 0);
  }
  free(buf);
}
END_TEST

START_TEST(eq_3) {
  char *buf = NULL;
  size_t n = 1024;

  buf = (char *)calloc(sizeof(char), sizeof(*buf) * 1024);
  if (buf) {
    for (int i = 0; i < 1024; ++i) buf[i] = i % 256;
    ck_assert_int_eq(s21_memcmp(buf, buf, n), 0);
    ck_assert_int_eq(memcmp(buf, buf, n), 0);
  }
  free(buf);
}
END_TEST

START_TEST(eq_4) {
  char buf1[] = "asccdada";
  char buf2[] = "asccdadb";
  size_t n = sizeof(buf1) / sizeof(char) - 2;

  ck_assert_int_eq(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_eq(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(less_1) {
  char buf1[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
  char buf2[] = "bsccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
  size_t n = sizeof(buf1) / sizeof(char);

  ck_assert_int_lt(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_lt(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(less_2) {
  char buf1[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
  char buf2[] = "asccdadasdasdasadsdasdzsdasdasdasdasdasdasasd";
  size_t n = sizeof(buf1) / sizeof(char);

  ck_assert_int_lt(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_lt(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(less_3) {
  char buf1[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasas";
  char buf2[] = "asccdadasdasdasadsdasdasdasdasdasdasdasdasasd";
  size_t n = sizeof(buf1) / sizeof(char);

  ck_assert_int_lt(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_lt(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(greater_1) {
  char buf1[] = "9212383363719300-1-333744740284848428818181882828218";
  char buf2[] = "1212383363719300-1-333744740284848428818181882828218";
  size_t n = sizeof(buf1) / sizeof(char);

  ck_assert_int_gt(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_gt(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(greater_2) {
  char buf1[] = "1212383363719300-1-933744740284848428818181882828218";
  char buf2[] = "1212383363719300-1-333744740284848428818181882828218";
  size_t n = sizeof(buf1) / sizeof(char);

  ck_assert_int_gt(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_gt(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(greater_3) {
  char buf1[] = "1212383363719300-1-333744740284848428818181882828218";
  char buf2[] = "1212383363719300-1-33374474028484842881818188282821";
  size_t n = sizeof(buf2);

  ck_assert_int_gt(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_gt(memcmp(buf1, buf2, n), 0);
}
END_TEST

START_TEST(not_char_1) {
  long buf[] = {19, 29, 73, 85, 89, 1000000, 111111, 8282282828, -129922};
  size_t n = sizeof(buf);
  ck_assert_int_eq(s21_memcmp(buf, buf, n), 0);
  ck_assert_int_eq(memcmp(buf, buf, n), 0);
}
END_TEST

START_TEST(not_char_2) {
  long buf1[] = {19, 29, 73, 85, 89, 1000000, 111111, 8282282828, -129922};
  long buf2[] = {19, 29, 73, 85, 89, 1000000, 11121112, 8282282828, -129922};
  size_t n = sizeof(buf1);

  ck_assert_int_lt(s21_memcmp(buf1, buf2, n), 0);
  ck_assert_int_lt(memcmp(buf1, buf2, n), 0);
}
END_TEST

Suite *suite_s21_memcmp(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_memcmp");
  tc = tcase_create("tcase_s21_memcmp");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, zero_size_1);
    tcase_add_test(tc, zero_size_2);
    tcase_add_test(tc, eq_1);
    tcase_add_test(tc, eq_2);
    tcase_add_test(tc, eq_3);
    tcase_add_test(tc, eq_4);
    tcase_add_test(tc, less_1);
    tcase_add_test(tc, less_2);
    tcase_add_test(tc, less_3);
    tcase_add_test(tc, greater_1);
    tcase_add_test(tc, greater_2);
    tcase_add_test(tc, greater_3);
    tcase_add_test(tc, not_char_1);
    tcase_add_test(tc, not_char_2);
    suite_add_tcase(s, tc);
  }

  return (s);
}
