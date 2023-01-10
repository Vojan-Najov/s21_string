#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "suite_sprintf_flags.h"

START_TEST(percent_flags) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      sprintf(format, "_%%%s%%_\n", sprintf_flags[i]);
      ret = sprintf(buf, format);
      ret21 = s21_sprintf(buf21, format);
      if (ret != ret21 || memcmp(buf, buf21, 1024)) {
        printf("%s%d:%s%d:%s", format, ret, buf, ret21, buf21);
      }
      ck_assert_int_eq(ret, ret21);
      ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
    }
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(percent_flags_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "10", "32", "64", NULL};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        sprintf(format, "_%%%s%s%%_\n", sprintf_flags[i], width[j]);
        ret = sprintf(buf, format);
        ret21 = s21_sprintf(buf21, format);
        if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          printf("%s%d:%s%d:%s", format, ret, buf, ret21, buf21);
        }
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(percent_flags_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "10", "32", "64", NULL};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j] != NULL; ++j) {
        sprintf(format, "_%%%s.%s%%_\n", sprintf_flags[i], precision[j]);
        ret = sprintf(buf, format);
        ret21 = s21_sprintf(buf21, format);
        if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          printf("%s%d:%s%d:%s", format, ret, buf, ret21, buf21);
        }
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(percent_flags_width_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "32", "64", NULL};
  char *precision[] = {"", "0", "1", "10", "32", "64", NULL};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k] != NULL; ++k) {
          sprintf(format, "_%%%s%s.%s%%_\n", sprintf_flags[i], width[j],
                  precision[k]);
          ret = sprintf(buf, format);
          ret21 = s21_sprintf(buf21, format);
          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
            printf("%s%d:%s%d:%s", format, ret, buf, ret21, buf21);
          }
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        }
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(percent_flags_star_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        sprintf(format, "_%%%s*%%_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, width[j]);
        ret21 = s21_sprintf(buf21, format, width[j]);
        if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          printf("%s%d:%s%d:%s", format, ret, buf, ret21, buf21);
        }
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(percent_flags_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        sprintf(format, "_%%%s.*%%_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, precision[j]);
        ret21 = s21_sprintf(buf21, format, precision[j]);
        if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          printf("%s%d:%s%d:%s", format, ret, buf, ret21, buf21);
        }
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
    free(buf);
    free(buf21);
  }
}
END_TEST

START_TEST(percent_flags_star_width_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32, 64};
  int precision[] = {0, 1, 32, 64};
  int wlen = sizeof(width) / sizeof(int);
  int plen = sizeof(precision) / sizeof(int);

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          sprintf(format, "_%%%s*.*%%_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], precision[k]);
          ret21 = s21_sprintf(buf21, format, width[j], precision[k]);
          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
            printf("%s%d:%s%d:%s", format, ret, buf, ret21, buf21);
          }
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        }
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

Suite *suite_s21_sprintf_percent(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf %");
  tc = tcase_create("TCase_s21_sprintf_percent");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, percent_flags);
    tcase_add_test(tc, percent_flags_width);
    tcase_add_test(tc, percent_flags_precision);
    tcase_add_test(tc, percent_flags_width_precision);
    tcase_add_test(tc, percent_flags_star_width);
    tcase_add_test(tc, percent_flags_star_precision);
    tcase_add_test(tc, percent_flags_star_width_star_precision);

    suite_add_tcase(s, tc);
  }

  return (s);
}
