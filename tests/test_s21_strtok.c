#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(empty_strings) {
  char s1[] = "";
  char s2[] = "";
  char delim[] = "";
  char *ret1, *ret2;

  ret1 = strtok(s1, delim);
  ret2 = s21_strtok(s2, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
  ret1 = strtok(NULL, delim);
  ret2 = s21_strtok(NULL, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
  ret1 = strtok(NULL, delim);
  ret2 = s21_strtok(NULL, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
}
END_TEST

START_TEST(empty_delim) {
  char s1[] = "hello";
  char s2[] = "hello";
  char *delim = "";
  char *ret1, *ret2;

  ret1 = strtok(s1, delim);
  ret2 = s21_strtok(s2, delim);
  ck_assert_int_eq(strcmp(ret1, ret2), 0);
  ret1 = strtok(NULL, delim);
  ret2 = s21_strtok(NULL, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
  ret1 = strtok(NULL, delim);
  ret2 = s21_strtok(NULL, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
}
END_TEST

START_TEST(no_delim) {
  char s1[] = "hello";
  char s2[] = "hello";
  char *delim = " ;,.";
  char *ret1, *ret2;

  ret1 = strtok(s1, delim);
  ret2 = s21_strtok(s2, delim);
  ck_assert_int_eq(strcmp(ret1, ret2), 0);
  ret1 = strtok(NULL, delim);
  ret2 = s21_strtok(NULL, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
  ret1 = strtok(NULL, delim);
  ret2 = s21_strtok(NULL, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
}
END_TEST

START_TEST(one_delim) {
  char buf1[] = "hello man how are you";
  char buf2[] = "hello man how are you";
  char *s1 = buf1;
  char *s2 = buf2;
  char *delim = " ";
  char *ret1, *ret2;

  while ((ret1 = strtok(s1, delim)) != NULL) {
    ret2 = s21_strtok(s2, delim);
    s1 = s2 = NULL;
    ck_assert_int_eq(strcmp(ret1, ret2), 0);
  }
  ret2 = s21_strtok(s2, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
}
END_TEST

START_TEST(any_delim) {
  char buf1[] = "hello man! how,are ,you.";
  char buf2[] = "hello man! how,are ,you.";
  char *s1 = buf1;
  char *s2 = buf2;
  char *delim = " !;,.";
  char *ret1, *ret2;

  while ((ret1 = strtok(s1, delim)) != NULL) {
    ret2 = s21_strtok(s2, delim);
    s1 = s2 = NULL;
    ck_assert_int_eq(strcmp(ret1, ret2), 0);
    ck_assert_int_eq(memcmp(buf1, buf2, sizeof(buf1)), 0);
  }
  ret2 = s21_strtok(s2, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
}
END_TEST

START_TEST(other_delim) {
  char buf1[] = "hello man! how,are ,you.";
  char buf2[] = "hello man! how,are ,you.";
  char *s1 = buf1;
  char *s2 = buf2;
  char *delim[] = {" !", ".,", " ,"};
  char *ret1, *ret2;
  int i = 0;

  while ((ret1 = strtok(s1, delim[i])) != NULL) {
    ret2 = s21_strtok(s2, delim[i]);
    s1 = s2 = NULL;
    ck_assert_int_eq(strcmp(ret1, ret2), 0);
    ck_assert_int_eq(memcmp(buf1, buf2, sizeof(buf1)), 0);
    ++i;
    i %= 3;
  }
  ret2 = s21_strtok(s2, delim[i]);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
}
END_TEST

START_TEST(other_strings_1) {
  char buf1[] = "hello man! how,are ,you.";
  char buf2[] = "hello man! how,are ,you.";
  char buf10[] = "HELLO MAN! HOW,ARE ,YOU.";
  char buf20[] = "HELLO MAN! HOW,ARE ,YOU.";
  char *s1 = buf1;
  char *s2 = buf2;
  char *delim = " !;,.";
  char *ret1, *ret2;
  int i = 0;

  while (i < 3) {
    ret1 = strtok(s1, delim);
    ret2 = s21_strtok(s2, delim);
    s1 = s2 = NULL;
    ck_assert_int_eq(strcmp(ret1, ret2), 0);
    ck_assert_int_eq(memcmp(buf1, buf2, sizeof(buf1)), 0);
    ++i;
  }
  ck_assert_ptr_ne(ret1, NULL);
  ck_assert_ptr_ne(ret2, NULL);
  s1 = buf10;
  s2 = buf20;
  while ((ret1 = strtok(s1, delim)) != NULL) {
    ret2 = s21_strtok(s2, delim);
    s1 = s2 = NULL;
    ck_assert_int_eq(strcmp(ret1, ret2), 0);
    ck_assert_int_eq(memcmp(buf10, buf20, sizeof(buf10)), 0);
  }
  ret2 = s21_strtok(s2, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);

  ret2 = s21_strtok(s2, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
}
END_TEST

START_TEST(other_strings_2) {
  char buf1[] = "hello man! how,are ,you.";
  char buf2[] = "hello man! how,are ,you.";
  char buf10[] = "HELLO MAN! HOW,ARE ,YOU.";
  char buf20[] = "HELLO MAN! HOW,ARE ,YOU.";
  char *s1 = buf1;
  char *s2 = buf2;
  char *delim = " !;,.";
  char *ret1, *ret2;

  while ((ret1 = strtok(s1, delim)) != NULL) {
    ret2 = s21_strtok(s2, delim);
    s1 = s2 = NULL;
    ck_assert_int_eq(strcmp(ret1, ret2), 0);
    ck_assert_int_eq(memcmp(buf1, buf2, sizeof(buf1)), 0);
  }
  ret2 = s21_strtok(s2, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
  s1 = buf10;
  s2 = buf20;
  while ((ret1 = strtok(s1, delim)) != NULL) {
    ret2 = s21_strtok(s2, delim);
    s1 = s2 = NULL;
    ck_assert_int_eq(strcmp(ret1, ret2), 0);
    ck_assert_int_eq(memcmp(buf10, buf20, sizeof(buf10)), 0);
  }
  ret2 = s21_strtok(s2, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);

  ret2 = s21_strtok(s2, delim);
  ck_assert_ptr_eq(ret1, NULL);
  ck_assert_ptr_eq(ret2, NULL);
}
END_TEST

Suite *suite_s21_strtok(void) {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("s21_strtok");
  tc = tcase_create("tcase_s21_strtok");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, empty_strings);
    tcase_add_test(tc, empty_delim);
    tcase_add_test(tc, no_delim);
    tcase_add_test(tc, one_delim);
    tcase_add_test(tc, any_delim);
    tcase_add_test(tc, other_delim);
    tcase_add_test(tc, other_strings_1);
    tcase_add_test(tc, other_strings_2);
    suite_add_tcase(s, tc);
  }

  return (s);
}
