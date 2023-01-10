#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"
#include "suite_sprintf_flags.h"

static double num[] = {0.0,  //-NAN
                       0.0,  // NAN,
                       -INFINITY,
                       -DBL_MAX,
                       -FLT_MAX,
                       -1228338383838381883.2828282828828282,
                       -1234.292987697867897867697687122122192191939339,
                       -1.122212221,
                       -0.2121921121393939113,
                       -0.0000000123892121921121393939113,
                       -FLT_MIN,
                       -0.0,
                       0.0,
                       FLT_MIN,
                       0.21219219121393939113,
                       0.000000989889,
                       1.122212221,
                       1234.292217687978677686978622192191939339,
                       1228338383838381883.2828282828828282,
                       FLT_MAX,
                       DBL_MAX,
                       INFINITY};
static int nlen = sizeof(num) / sizeof(double);

static char *width[] = {"1", "10", "64", "100", "1000", NULL};

static char *precision[] = {"",
                            "0",
                            "1",
                            "2"
                            "5",
                            "6",
                            "10",
                            "16",
                            "32",
                            "50",
                            "100",
                            "150",
                            NULL};

static char *(wp[])[2] = {
    {"100", ""},    {"100", "0"},   {"100", "1"},  {"100", "10"},
    {"100", "6"},   {"100", "32"},  {"100", "50"}, {"100", "100"},
    {"100", "150"}, {"300", "150"},
};
static int wplen = sizeof(wp) / sizeof(wp[0]);

START_TEST(flags) {
  int ret, ret21;
  char format[128];
  char *buf, *buf21;

  buf = calloc(8 * 1024, sizeof(char));
  buf21 = calloc(8 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      sprintf(format, "_%%%se_\n", sprintf_flags[i]);
      for (int j = 0; j < nlen; ++j) {
        ret = sprintf(buf, format, num[j]);
        ret21 = s21_sprintf(buf21, format, num[j]);
        //        if (ret != ret21 || strcmp(buf, buf21)) {
        //          printf("_%e_\n", num[j]);
        //          printf("%soriginal:\n%d:%ss21:\n%d:%s\n", format, ret, buf,
        //          ret21,
        //                 buf21);
        //        }
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(strcmp(buf, buf21), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(flags_width) {
  int ret, ret21;
  char format[128];
  char *buf, *buf21;

  buf = calloc(8 * 1024, sizeof(char));
  buf21 = calloc(8 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int w = 0; width[w] != NULL; ++w) {
        sprintf(format, "_%%%s%se_\n", sprintf_flags[i], width[w]);
        for (int j = 0; j < nlen; ++j) {
          ret = sprintf(buf, format, num[j]);
          ret21 = s21_sprintf(buf21, format, num[j]);
          //          if (ret != ret21 || strcmp(buf, buf21)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
          //          }
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(strcmp(buf, buf21), 0);
        }
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(flags_precision) {
  int ret, ret21;
  char format[128];
  char *buf, *buf21;

  buf = calloc(8 * 1024, sizeof(char));
  buf21 = calloc(8 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL && sprintf_flags[i + 1] != NULL;
         i += 2) {
      for (int p = 0; precision[p] != NULL; ++p) {
        sprintf(format, "_%%%s.%se_\n", sprintf_flags[i], precision[p]);
        for (int j = 0; j < nlen; ++j) {
          ret = sprintf(buf, format, num[j]);
          ret21 = s21_sprintf(buf21, format, num[j]);
          //          if (ret != ret21 || strcmp(buf, buf21)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
          //          }
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(strcmp(buf, buf21), 0);
        }
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(flags_width_precision) {
  int ret, ret21;
  char format[128];
  char *buf, *buf21;

  buf = calloc(8 * 1024, sizeof(char));
  buf21 = calloc(8 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int w = 0; w < wplen; ++w) {
        sprintf(format, "_%%%s%s.%se_\n", sprintf_flags[i], wp[w][0], wp[w][1]);
        for (int j = 13; j < nlen; ++j) {
          ret = sprintf(buf, format, num[j]);
          ret21 = s21_sprintf(buf21, format, num[j]);
          //          if (ret != ret21 || strcmp(buf, buf21)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
          //          }
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(strcmp(buf, buf21), 0);
        }
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(precision_and_rounding) {
  int ret, ret21;
  char format[128];
  double n;
  char *buf, *buf21;

  buf = calloc(8 * 1024, sizeof(char));
  buf21 = calloc(8 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    n = 0.0;
    sprintf(format, "_%%.0e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.0;
    sprintf(format, "_%%.10e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.12331231;
    sprintf(format, "_%%e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.123847;
    sprintf(format, "_%%.3e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.123895;
    sprintf(format, "_%%.3e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //   }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.879999;
    sprintf(format, "_%%.3e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.99978;
    sprintf(format, "_%%.3e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("hello\n");
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = -0.99978;
    sprintf(format, "_%%.3e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 2599.99978;
    sprintf(format, "_%%.3e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("hello\n");
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = -1899.99978;
    sprintf(format, "_%%.3e_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);
  }

  free(buf);
  free(buf21);
}
END_TEST

Suite *suite_s21_sprintf_e(void) {
  Suite *s;
  TCase *tc;

  num[0] = nan("");
  num[1] = -nan("");

  s = suite_create("s21_sprintf e");
  tc = tcase_create("Tcase_s21_sprintf_e");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, flags);
    tcase_add_test(tc, flags_width);
    tcase_add_test(tc, flags_precision);
    tcase_add_test(tc, flags_width_precision);
    tcase_add_test(tc, precision_and_rounding);
    suite_add_tcase(s, tc);
  }

  return (s);
}
