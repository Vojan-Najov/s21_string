#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(multitest) {
  int ret;
  int ret21;
  char buf[1024] = {0};
  char buf21[1024] = {0};
  int count = -2;
  int count21 = -2;

  ret = sprintf(buf, "_%%_%c_%s_%d_%*i_%.*o_%10x_%.5X_%p_%n_%f_%e_%LE_123\n",
                'a', "12345", 196, 10, -75, 10, 89, 2882, 182, (void *)&count,
                &count, -8.123, 0.009, -99.98L);
  ret21 = s21_sprintf(buf21,
                      "_%%_%c_%s_%d_%*i_%.*o_%10x_%.5X_%p_%n_%f_%e_%LE_123\n",
                      'a', "12345", 196, 10, -75, 10, 89, 2882, 182,
                      (void *)&count, &count21, -8.123, 0.009, -99.98L);
  ck_assert(ret == ret21 && count == count21 && strcmp(buf, buf21) == 0);
}
END_TEST

Suite *suite_s21_sprintf_multi(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf multitest");
  tc = tcase_create("s21_sprintf multitest tcase");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, multitest);
    suite_add_tcase(s, tc);
  }

  return (s);
}
