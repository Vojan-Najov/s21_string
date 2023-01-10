#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

static char *(str_fmt[])[7] = {
    {"", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"abc", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"123     +0000000123456", "123 %hhi", "123 %hi", "123 %i", "123 %li",
     "123 %lli", NULL},
    {"104     +0000000123456", " %123hhi", "123 %hi", "123 %i", "123 %li",
     "123 %lli", NULL},
    {"-127", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"127", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"255", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0-177", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0177", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0377", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0x-7f", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0x7f", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0xff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0X-7F", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0X7F", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0XFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-32767", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"32767", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"65535", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-077777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"077777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"071635", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0177777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0x7fff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0x7fff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0x7f1a", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0xffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0X7FFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0X7FFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0X710", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0XFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-2147483647", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"2147483647", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"4294967295", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-017777777777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"017777777777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"011543413562", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"037777777777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0x7fffffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0x7fffffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0x78a1285b", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0xffffffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0X7FFFFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0X7FFFFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0XFFFFFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-9223372036854775807", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"9223372036854775807", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"18446744073709551615", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0777777777777777777777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0777777777777777777777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0125364534132415363453", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"01777777777777777777777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0x7fffffffffffffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0x7fffffffffffffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0xffffffffffffffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0X7FFFFFFFFFFFFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0X7FFFFFFFFFFFFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0XFFFFFFFFFFFFFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-9223372036854775807", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"9223372036854775807", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"18446744073709551615", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0777777777777777777777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0777777777777777777777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"01777777777777777777777", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0x7fffffffffffffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0x7fffffffffffffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0xffffffffffffffff", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"-0X7FFFFFFFFFFFFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0X7FFFFFFFFFFFFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {"0XFFFFFFFFFFFFFFFF", "%hhi", "%hi", "%i", "%li", "%lli", NULL},  //
    {"0X710", "%*hhi", "%*hi", "%*i", "%*li", "%*lli", NULL},
    {"01000101", "%hhi", "%hi", "%i", "%li", "%lli", NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

START_TEST(decimal) {
  long long int d, d21;

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
    {"123     -0000000991234569abc    +000000983764", "123%iabc%i"},
    {"123 111223 ab777", "%i %*i ab%i"},
    {"123     -0000000991234569abc    +000000983764", "123%3iabc%5i"},
    {"1234", "1%1i%1i4"},
    {"1234", "1%15i%1i4"},
    {"++1 ------21", "%i %i"},
    {"123 1234", "%*i %*i"},
    {NULL, NULL}};

START_TEST(two_decimal) {
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
    {"01234567 123", "%i %i"},
    {"01234567 123", "%*i %i"},
    {"01234567 123", "%*i %*i"},
    {"01234567 123", "%5i567 %1i23"},
    {"01234567 123", "%i34%i"},
    {"-1023 -07654", "%i %i"},
    {NULL, NULL},
};

START_TEST(two_octal) {
  for (int i = 0; str_fmt3[i][0] != NULL && str_fmt3[i][1] != NULL; ++i) {
    int d = -123, d21 = -123;
    int dd = -123, dd21 = -123;
    char *str = str_fmt3[i][0];
    char *format = str_fmt3[i][1];
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

static char *(str_fmt4[])[2] = {
    {"0x7fff 1x67ffff", "%i %i"},        {"0x7fff 1x67ffff", "%*i %i"},
    {"0x7fff 1x67ffff", "0%if %iff"},    {"0x7fff 1x67ffff", "%*i %*i"},
    {"0x7fff 1x67ffff", "%5if %4iffff"}, {"-0x7fff 1x67ffff", "%i %i"},
    {"0x7f-ff 1x67ff-ff", "%i %i"},      {NULL, NULL},
};

START_TEST(two_hexadecimal) {
  for (int i = 0; str_fmt4[i][0] != NULL && str_fmt4[i][1] != NULL; ++i) {
    int d = -123, d21 = -123;
    int dd = -123, dd21 = -123;
    char *str = str_fmt4[i][0];
    char *format = str_fmt4[i][1];
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

static char *(str_fmt5[])[2] = {
    {"123     -0000000991234569abc    +000000983764", "123%hiabc%hi"},
    {"123 111223 ab777", "%hi %*hi ab%hi"},
    {"123     -0000000991234569abc    +000000983764", "123%3hiabc%5hi"},
    {"1234", "1%1hi%1hi4"},
    {"1234", "1%15hi%1hi4"},
    {"++1 ------21", "%hi %hi"},
    {"123 1234", "%*hi %*hi"},
    {NULL, NULL}};

START_TEST(two_short_decimal) {
  for (int i = 0; str_fmt5[i][0] != NULL && str_fmt5[i][1] != NULL; ++i) {
    short int d = -123, d21 = -123;
    short int dd = -123, dd21 = -123;
    char *str = str_fmt5[i][0];
    char *format = str_fmt5[i][1];
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

static char *(str_fmt6[])[2] = {
    {"123     -0000000991234569abc    +000000983764", "123%liabc%li"},
    {"123 111223 ab777", "%li %*li ab%li"},
    {"123     -0000000991234569abc    +000000983764", "123%3liabc%5li"},
    {"1234", "1%1li%1li4"},
    {"1234", "1%15li%1li4"},
    {"++1 ------21", "%li %li"},
    {"123 1234", "%*li %*li"},
    {NULL, NULL}};

START_TEST(two_long_decimal) {
  for (int i = 0; str_fmt6[i][0] != NULL && str_fmt6[i][1] != NULL; ++i) {
    long int d = -123, d21 = -123;
    long int dd = -123, dd21 = -123;
    char *str = str_fmt6[i][0];
    char *format = str_fmt6[i][1];
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

static char *(str_fmt7[])[2] = {
    {"01234567 123", "%li %i"},
    {"01234567 123", "%*li %li"},
    {"01234567 123", "%*li %*li"},
    {"01234567 123", "%5li567 %1li23"},
    {"01234567 123", "%li34%li"},
    {"-1023 -07654", "%li %li"},
    {NULL, NULL},
};

START_TEST(two_long_octal) {
  for (int i = 0; str_fmt7[i][0] != NULL && str_fmt7[i][1] != NULL; ++i) {
    long int d = -123, d21 = -123;
    long int dd = -123, dd21 = -123;
    char *str = str_fmt7[i][0];
    char *format = str_fmt7[i][1];
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

static char *(str_fmt8[])[2] = {
    {"01234567 123", "%hi %hi"},
    {"01234567 123", "%*hi %hi"},
    {"01234567 123", "%*hi %*hi"},
    {"01234567 123", "%5hi567 %1hi23"},
    {"01234567 123", "%hi34%hi"},
    {"-1023 -07654", "%hi %hi"},
    {NULL, NULL},
};

START_TEST(two_short_octal) {
  for (int i = 0; str_fmt8[i][0] != NULL && str_fmt8[i][1] != NULL; ++i) {
    short int d = -123, d21 = -123;
    short int dd = -123, dd21 = -123;
    char *str = str_fmt8[i][0];
    char *format = str_fmt8[i][1];
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

Suite *suite_s21_sscanf_i(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sscanf i");
  tc = tcase_create("s21_sscanf i tcase");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, decimal);
    tcase_add_test(tc, two_decimal);
    tcase_add_test(tc, two_octal);
    tcase_add_test(tc, two_hexadecimal);
    tcase_add_test(tc, two_short_decimal);
    tcase_add_test(tc, two_long_decimal);
    tcase_add_test(tc, two_long_octal);
    tcase_add_test(tc, two_short_octal);
    suite_add_tcase(s, tc);
  }

  return (s);
}
