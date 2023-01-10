#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(zero_count_hh) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  char count = -1, count21 = -1;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%hhn";
    ret = sprintf(buf, fmt, &count);
    ret21 = s21_sprintf(buf21, fmt, &count21);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
    fmt = "%hhn%s";
    ret = sprintf(buf, fmt, &count, s);
    ret21 = s21_sprintf(buf21, fmt, &count21, s);
    //    if (count != count21 || ret != ret21 || memcmp(buf, buf21, 1024)) {
    //      printf("%s\n%d:%s\n%d:%s\n", fmt, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(zero_count_h) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  short count = -1, count21 = -1;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%hn";
    ret = sprintf(buf, fmt, &count);
    ret21 = s21_sprintf(buf21, fmt, &count21);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
    fmt = "%hn%s";
    ret = sprintf(buf, fmt, &count, s);
    ret21 = s21_sprintf(buf21, fmt, &count21, s);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(zero_count) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  int count = -1, count21 = -1;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%n";
    ret = sprintf(buf, fmt, &count);
    ret21 = s21_sprintf(buf21, fmt, &count21);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
    fmt = "%n%s";
    ret = sprintf(buf, fmt, &count, s);
    ret21 = s21_sprintf(buf21, fmt, &count21, s);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(zero_count_l) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  long count = -1, count21 = -1;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%ln";
    ret = sprintf(buf, fmt, &count);
    ret21 = s21_sprintf(buf21, fmt, &count21);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
    fmt = "%ln%s";
    ret = sprintf(buf, fmt, &count, s);
    ret21 = s21_sprintf(buf21, fmt, &count21, s);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(zero_count_ll) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  long long count = -1, count21 = -1;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%lln";
    ret = sprintf(buf, fmt, &count);
    ret21 = s21_sprintf(buf21, fmt, &count21);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
    fmt = "%lln%s";
    ret = sprintf(buf, fmt, &count, s);
    ret21 = s21_sprintf(buf21, fmt, &count21, s);
    //    if (count != count21 || ret != ret21 || memcmp(buf, buf21, 1024)) {
    //      printf("%s\n%d:%s\n%d:%s\n", fmt, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(count_hh) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  char count = -1, count21 = -1;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%s%hhn something";
    ret = sprintf(buf, fmt, s, &count);
    ret21 = s21_sprintf(buf21, fmt, s, &count21);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
    fmt = "%300s%hhn something";
    ret = sprintf(buf, fmt, s, &count);
    ret21 = s21_sprintf(buf21, fmt, s, &count21);
    //    if (count != count21 || ret != ret21 || memcmp(buf, buf21, 1024)) {
    //      printf("%s\n%d:%s\n%d:%s\n", fmt, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(count_h) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  short int count = -1, count21 = -1;

  buf = calloc(SHRT_MAX + 100, sizeof(char));
  buf21 = calloc(SHRT_MAX + 100, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%s%hn something";
    ret = sprintf(buf, fmt, s, &count);
    ret21 = s21_sprintf(buf21, fmt, s, &count21);
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
    fmt = "%*s%hn something";
    ret = sprintf(buf, fmt, SHRT_MAX + 10, s, &count);
    ret21 = s21_sprintf(buf21, fmt, SHRT_MAX + 10, s, &count21);
    //    if (count != count21 || ret != ret21 || memcmp(buf, buf21, 1024)) {
    //      printf("%s\n%d:%s\n%d:%s\n", fmt, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(count) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  int count = -1, count21 = -1;

  buf = calloc(SHRT_MAX + 100, sizeof(char));
  buf21 = calloc(SHRT_MAX + 100, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%*s%n something";
    ret = sprintf(buf, fmt, SHRT_MAX + 10, s, &count);
    ret21 = s21_sprintf(buf21, fmt, SHRT_MAX + 10, s, &count21);
    if (count != count21 || ret != ret21 || memcmp(buf, buf21, 1024)) {
      printf("%scount=%d\ncount21=%d\n\n%d:%s\n%d:%s\n", fmt, count, count21,
             ret, buf, ret21, buf21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(count_l) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  long int count = -1, count21 = -1;

  buf = calloc(SHRT_MAX + 100, sizeof(char));
  buf21 = calloc(SHRT_MAX + 100, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%*s%ln something";
    ret = sprintf(buf, fmt, SHRT_MAX + 10, s, &count);
    ret21 = s21_sprintf(buf21, fmt, SHRT_MAX + 10, s, &count21);
    //    if (count != count21 || ret != ret21 || memcmp(buf, buf21, 1024)) {
    //      printf("%scount=%ld\ncount21=%ld\n\n%d:%s\n%d:%s\n", fmt, count,
    //      count21,
    //             ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(count_ll) {
  char *fmt;
  char *s = "hello";
  char *buf, *buf21;
  int ret, ret21;
  long long int count = -1, count21 = -1;

  buf = calloc(SHRT_MAX + 100, sizeof(char));
  buf21 = calloc(SHRT_MAX + 100, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%*s%lln something";
    ret = sprintf(buf, fmt, 100, s, &count);
    ret21 = s21_sprintf(buf21, fmt, 100, s, &count21);
    //    if (count != count21 || ret != ret21 || memcmp(buf, buf21, 1024)) {
    //      printf("%scount=%lld\ncount21=%lld\n\n%d:%s\n%d:%s\n", fmt, count,
    //             count21, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(multi_count) {
  char *fmt;
  char *s = "hello";
  int ret, ret21;
  char *buf, *buf21;
  int count = -1, count21 = -1, count1 = -1, count121 = -1;
  int count2 = -1, count221 = -1, count3 = -1, count321 = -1;
  int count4 = -1, count421 = -1, count5 = -1, count521 = -1;

  buf = calloc(SHRT_MAX + 100, sizeof(char));
  buf21 = calloc(SHRT_MAX + 100, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    fmt = "%n%100s%n%n_%n%100d%n%20c%n";
    ret = sprintf(buf, fmt, &count, s, &count1, &count2, &count3, 100, &count4,
                  'a', &count5);
    ret21 = s21_sprintf(buf21, fmt, &count21, s, &count121, &count221,
                        &count321, 100, &count421, 'a', &count521);
    //    if (count != count21 || ret != ret21 || memcmp(buf, buf21, 1024)) {
    //      printf("%s\n%d:%s\n%d:%s\n", fmt, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    ck_assert(count == count21);
    ck_assert(count1 == count121);
    ck_assert(count2 == count221);
    ck_assert(count3 == count321);
    ck_assert(count4 == count421);
    ck_assert(count5 == count521);
  }
  free(buf);
  free(buf21);
}
END_TEST

Suite *suite_s21_sprintf_n(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf n");
  tc = tcase_create("TCase_s21_sprintf_n");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, zero_count_hh);
    tcase_add_test(tc, zero_count_h);
    tcase_add_test(tc, zero_count);
    tcase_add_test(tc, zero_count_l);
    tcase_add_test(tc, zero_count_ll);
    tcase_add_test(tc, count_hh);
    tcase_add_test(tc, count_h);
    tcase_add_test(tc, count);
    tcase_add_test(tc, count_l);
    tcase_add_test(tc, count_ll);
    tcase_add_test(tc, multi_count);
    suite_add_tcase(s, tc);
  }

  return (s);
}
