#include <check.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(empty_string) {
  const char *s = "";

  ck_assert(strlen(s) == s21_strlen(s));
  s = "\0asdasas";
  ck_assert(strlen(s) == s21_strlen(s));
}
END_TEST

START_TEST(len) {
  const char *s = "sadjkksajdsakj kasjkdakdsa sakdjas";

  ck_assert(strlen(s) == s21_strlen(s));
  s = "0000000000000\0asdasas";
  ck_assert(strlen(s) == s21_strlen(s));
}
END_TEST

START_TEST(long_string) {
  char *s = NULL;
  char c = 'a';
  size_t size = 1024;

  s = (char *)malloc(sizeof(char) * size);
  if (s != NULL) {
    s[size - 1] = '\0';
    for (unsigned int i = 0; i < size - 1; ++i) {
      s[i] = c;
    }
    ck_assert(strlen(s) == s21_strlen(s));
  }
  free(s);
}
END_TEST

START_TEST(easy_test) {
  const char *s = "123";

  ck_assert(strlen(s) == s21_strlen(s));
  s = "\0asdasas";
  ck_assert(strlen(s) == s21_strlen(s));
}
END_TEST

Suite *suite_s21_strlen(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_strlen");
  tc = tcase_create("tcase_s21_strlen");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_string);
    tcase_add_test(tc, len);
    tcase_add_test(tc, long_string);
    tcase_add_test(tc, easy_test);
    suite_add_tcase(s, tc);
  }

  return (s);
}
