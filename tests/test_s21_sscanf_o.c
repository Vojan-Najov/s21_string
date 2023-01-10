#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

static char *(str_fmt[])[7] = {
    {"", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"abc", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"123     +0000000123456", "123 %hho", "123 %ho", "123 %o", "123 %lo",
     "123 %llo", NULL},
    {"-127", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"127", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"255", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"0-177", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"0177", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"0377", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"-32767", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"32767", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"65535", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"-077777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"077777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"071635", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"0177777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"-2147483647", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"2147483647", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"4294967295", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"-017777777777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"017777777777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"011543413562", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"037777777777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"-9223372036854775807", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"9223372036854775807", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"18446744073709551615", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"-0777777777777777777777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"0777777777777777777777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"0125364534132415363453", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"01777777777777777777777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"-9223372036854775807", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"9223372036854775807", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"18446744073709551615", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"-0777777777777777777777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"0777777777777777777777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {"01777777777777777777777", "%hho", "%ho", "%o", "%lo", "%llo", NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

START_TEST(octal) {
  unsigned long long int d, d21;

  for (int i = 0; str_fmt[i][0] != NULL; ++i) {
    d = 123, d21 = 123;
    char *str = str_fmt[i][0];
    char *fmt;
    for (int j = 0; (fmt = str_fmt[i][j]) != NULL; ++j) {
      int ret = sscanf(str, fmt, &d);
      int ret21 = s21_sscanf(str, fmt, &d21);
      if (ret != ret21 || d != d21) {
        printf(
            "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
            "original:%lld\ns21:%lld\n",
            str, fmt, ret, ret21, d, d21);
      }
      ck_assert_int_eq(ret, ret21);
      ck_assert(d == d21);
    }
  }
}
END_TEST

static char *(str_fmt2[])[2] = {
    {"01234567 123", "%o %o"},
    {"01234567 123", "%*o %o"},
    {"01234567 123", "%*o %*o"},
    {"01234567 123", "%5o567 %1o23"},
    {"01234567 123", "%o34%o"},
    {"-1023 -07654", "%o %o"},
    {NULL, NULL},
};

START_TEST(two_octal) {
  for (int i = 0; str_fmt2[i][0] != NULL && str_fmt2[i][1] != NULL; ++i) {
    int d = -123, d21 = -123;
    int dd = -123, dd21 = -123;
    char *str = str_fmt2[i][0];
    char *format = str_fmt2[i][1];
    int ret = sscanf(str, format, &d, &dd);
    int ret21 = s21_sscanf(str, format, &d21, &dd21);
    if (ret != ret21 || d != d21 || dd != dd21) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%d | %d\ns21:%d | %d\n",
          str, format, ret, ret21, d, dd, d21, dd21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(dd, dd21);
  }
}
END_TEST

static char *(str_fmt3[])[2] = {
    {"01234567 123", "%ho %ho"},
    {"01234567 123", "%*ho %ho"},
    {"01234567 123", "%*ho %*ho"},
    {"01234567 123", "%5ho567 %1ho23"},
    {"01234567 123", "%ho34%ho"},
    {"-1023 -07654", "%ho %ho"},
    {NULL, NULL},
};

START_TEST(two_short_octal) {
  for (int i = 0; str_fmt3[i][0] != NULL && str_fmt3[i][1] != NULL; ++i) {
    short int d = -123, d21 = -123;
    short int dd = -123, dd21 = -123;
    char *str = str_fmt3[i][0];
    char *format = str_fmt3[i][1];
    int ret = sscanf(str, format, &d, &dd);
    int ret21 = s21_sscanf(str, format, &d21, &dd21);
    if (ret != ret21 || d != d21 || dd != dd21) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%hd | %hd\ns21:%hd | %hd\n",
          str, format, ret, ret21, d, dd, d21, dd21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(dd, dd21);
  }
}
END_TEST

static char *(str_fmt4[])[2] = {
    {"01234567 123", "%lo %lo"},
    {"01234567 123", "%*lo %lo"},
    {"01234567 123", "%*lo %*lo"},
    {"01234567 123", "%5lo567 %1lo23"},
    {"01234567 123", "%lo34%lo"},
    {"-1023 -07654", "%lo %lo"},
    {NULL, NULL},
};

START_TEST(two_long_octal) {
  for (int i = 0; str_fmt4[i][0] != NULL && str_fmt4[i][1] != NULL; ++i) {
    long int d = -123, d21 = -123;
    long int dd = -123, dd21 = -123;
    char *str = str_fmt4[i][0];
    char *format = str_fmt4[i][1];
    int ret = sscanf(str, format, &d, &dd);
    int ret21 = s21_sscanf(str, format, &d21, &dd21);
    if (ret != ret21 || d != d21 || dd != dd21) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%ld | %ld\ns21:%ld | %ld\n",
          str, format, ret, ret21, d, dd, d21, dd21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(dd, dd21);
  }
}
END_TEST

static char *(str_fmt5[])[2] = {
    {"01234567 123", "%llo %llo"},
    {"01234567 123", "%*llo %llo"},
    {"01234567 123", "%*llo %*llo"},
    {"01234567 123", "%5llo567 %1llo23"},
    {"01234567 123", "%llo34%llo"},
    {"-1023 -07654", "%llo %llo"},
    {NULL, NULL},
};

START_TEST(two_long_long_octal) {
  for (int i = 0; str_fmt5[i][0] != NULL && str_fmt5[i][1] != NULL; ++i) {
    long long int d = -123, d21 = -123;
    long long int dd = -123, dd21 = -123;
    char *str = str_fmt5[i][0];
    char *format = str_fmt5[i][1];
    int ret = sscanf(str, format, &d, &dd);
    int ret21 = s21_sscanf(str, format, &d21, &dd21);
    if (ret != ret21 || d != d21 || dd != dd21) {
      printf(
          "str _%s_\nformat _%s_\nret = %d, ret21 = %d\n"
          "original:%lld | %lld\ns21:%lld | %lld\n",
          str, format, ret, ret21, d, dd, d21, dd21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(dd, dd21);
  }
}
END_TEST

Suite *suite_s21_sscanf_o(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sscanf o");
  tc = tcase_create("s21_sscanf o tcase");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, octal);
    tcase_add_test(tc, two_octal);
    tcase_add_test(tc, two_short_octal);
    tcase_add_test(tc, two_long_octal);
    tcase_add_test(tc, two_long_long_octal);
    suite_add_tcase(s, tc);
  }

  return (s);
}
