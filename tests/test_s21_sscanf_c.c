#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

static char *(str_fmt[])[2] = {{"", "%c"},    {"1", "%c"},   {"12", "%c2"},
                               {"12", "%ca"}, {"12", "a%c"},  //
                               {"1", "%*c"},  {"\n", "%c"},  {NULL, NULL}};

START_TEST(one_char) {
  char *str;
  int ret, ret21;
  char *format;
  char c[1024] = {0};
  char c21[1024] = {0};

  for (int i = 0; str_fmt[i][0] != NULL && str_fmt[i][1] != NULL; ++i) {
    str = str_fmt[i][0];
    format = str_fmt[i][1];
    ret = sscanf(str, format, c);
    ret21 = s21_sscanf(str, format, c21);
    if (ret != ret21 || memcmp(c, c21, 1024)) {
      printf("str _%s_\nformat _%s_\nret = %d, ret21 = %d\n", str, format, ret,
             ret21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(c, c21, 1024), 0);
  }
}
END_TEST

static char *(str_fmt2[])[2] = {{"", "%c%c"},
                                {"1", "%c%c"},
                                {"12", "%c2%c"},
                                {"12", "1%c%c"},
                                {"12", "a%c%c"},
                                {"12", "%c%c"},
                                {"1abc2", "%cabc%c"},
                                {"1abc2", "%cab2%c"},
                                {"0123456789a123456789", "%10ca%20c"},  //
                                {"1 2", "%c %c"},
                                {"12", "% c%c"},
                                {"12", "%*c%c"},
                                {"12", "%*c %*c"},
                                {"12", "%c %c"},
                                {"\n\\", "%c%c"},
                                {"' /", "%c%c"},
                                {"*1", "%c%c"},
                                {" 1", "%*c%c"},
                                {"1 ", "%*c%c"},
                                {"  ", "%c%*c"},
                                {"12", "%1c%0c"},
                                {NULL, NULL}};

START_TEST(two_chars) {
  char *str;
  int ret, ret21;
  char *format;
  char c[1024] = {0};
  char c21[1024] = {0};

  for (int i = 0; str_fmt2[i][0] != NULL && str_fmt[i][1] != NULL; ++i) {
    str = str_fmt2[i][0];
    format = str_fmt2[i][1];
    ret = sscanf(str, format, c, c + 512);
    ret21 = s21_sscanf(str, format, c21, c21 + 512);
    if (ret != ret21 || memcmp(c, c21, 1024)) {
      printf("str _%s_\nformat _%s_\nret = %d, ret21 = %d\n", str, format, ret,
             ret21);
    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(memcmp(c, c21, 1024), 0);
  }
}
END_TEST

Suite *suite_s21_sscanf_c(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sscanf c");
  tc = tcase_create("s21_sscanf c tcase");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, one_char);
    tcase_add_test(tc, two_chars);
    suite_add_tcase(s, tc);
  }

  return (s);
}
