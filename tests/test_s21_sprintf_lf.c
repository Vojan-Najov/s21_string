#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"
#include "suite_sprintf_flags.h"

static long double num[] = {0.0,  //-NAN
                            0.0,  // NAN,
                            -INFINITY,
                            -DBL_MAX,
                            -1228338383838381883.2828282828828282,
                            -1234.292987697867897867697687122122192191939339,
                            -1.122212221,
                            -0.2121921121393939113,
                            -FLT_MIN,
                            -0.0,
                            0.0,
                            FLT_MIN,
                            0.21219219121393939113,
                            1.122212221,
                            1234.292217687978677686978622192191939339,
                            1228338383838381883.2828282828828282,
                            DBL_MAX,
                            INFINITY};
static int nlen = sizeof(num) / sizeof(long double);

static char *width[] = {"1", "10", "64", "100", "1000", NULL};

static char *precision[] = {"",
                            "0",
                            "1",
                            "2"
                            "5",
                            "6",
                            "10",
                            "32",
                            "100",
                            "1000",
                            NULL};

static char *(wp[])[2] = {
    {"100", ""},    {"100", "0"},   {"100", "1"},   {"100", "10"},
    {"100", "6"},   {"100", "32"},  {"100", "100"}, {"100", "120"},
    {"100", "150"}, {"300", "150"},
};
static int wplen = sizeof(wp) / sizeof(wp[0]);

START_TEST(flags) {
  char *buf;
  char *buf21;
  int ret, ret21;
  char format[128];

  buf = calloc(16 * 1024, sizeof(char));
  buf21 = calloc(16 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      sprintf(format, "_%%%sLf_\n", sprintf_flags[i]);
      for (int j = 0; j < nlen; ++j) {
        ret = sprintf(buf, format, num[j]);
        ret21 = s21_sprintf(buf21, format, num[j]);
        //        if (ret != ret21) || strcmp(buf, buf21)) {
        //          printf("_%Lf_\n", num[j]);
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
  char *buf;
  char *buf21;
  int ret, ret21;
  char format[128];

  buf = calloc(16 * 1024, sizeof(char));
  buf21 = calloc(16 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int w = 0; width[w] != NULL; ++w) {
        sprintf(format, "_%%%s%sLf_\n", sprintf_flags[i], width[w]);
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
  char *buf;
  char *buf21;
  int ret, ret21;
  char format[128];

  buf = calloc(16 * 1024, sizeof(char));
  buf21 = calloc(16 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL && sprintf_flags[i + 1] != NULL;
         i += 2) {
      for (int p = 0; precision[p] != NULL; ++p) {
        sprintf(format, "_%%%s.%sLf_\n", sprintf_flags[i], precision[p]);
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
  char *buf;
  char *buf21;
  int ret, ret21;
  char format[128];

  buf = calloc(16 * 1024, sizeof(char));
  buf21 = calloc(16 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int w = 0; w < wplen; ++w) {
        sprintf(format, "_%%%s%s.%sLf_\n", sprintf_flags[i], wp[w][0],
                wp[w][1]);
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
  char *buf;
  char *buf21;
  int ret, ret21;
  char format[128];
  long double n;

  buf = calloc(16 * 1024, sizeof(char));
  buf21 = calloc(16 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    n = 0.0;
    sprintf(format, "_%%.0Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.0;
    sprintf(format, "_%%.10Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.35;
    sprintf(format, "_%%.1Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.45;
    sprintf(format, "_%%.1Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.12331231;
    sprintf(format, "_%%Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.123847;
    sprintf(format, "_%%.3Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.123895;
    sprintf(format, "_%%.3Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.879999;
    sprintf(format, "_%%.3Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 0.99978;
    sprintf(format, "_%%.3Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = -0.99978;
    sprintf(format, "_%%.3Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = 2599.99978;
    sprintf(format, "_%%.3Lf_\n");
    ret = sprintf(buf, format, n);
    ret21 = s21_sprintf(buf21, format, n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = -1899.99978;
    sprintf(format, "_%%.3Lf_\n");
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

START_TEST(ldbl_max) {
  char *buf;
  char *buf21;
  int ret, ret21;
  long double n;

  buf = calloc(16 * 1024, sizeof(char));
  buf21 = calloc(16 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    n = LDBL_MAX;
    ret = sprintf(buf, "%.100Lf\n", n);
    ret21 = s21_sprintf(buf21, "%.100Lf\n", n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%d:%s%d:%s\n", ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = -LDBL_MAX;
    ret = sprintf(buf, "%.100Lf\n", n);
    ret21 = s21_sprintf(buf21, "%.100Lf\n", n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%d:%s%d:%s\n", ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(dbl_min) {
  char *buf;
  char *buf21;
  int ret, ret21;
  long double n;

  buf = calloc(16 * 1024, sizeof(char));
  buf21 = calloc(16 * 1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    n = DBL_MIN;
    ret = sprintf(buf, "%.100Lf\n", n);
    ret21 = s21_sprintf(buf21, "%.100Lf\n", n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%d:%s%d:%s\n", ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);

    n = -DBL_MIN;
    ret = sprintf(buf, "%.100Lf\n", n);
    ret21 = s21_sprintf(buf21, "%.100Lf\n", n);
    //    if (ret != ret21 || strcmp(buf, buf21)) {
    //      printf("%d:%s%d:%s\n", ret, buf, ret21, buf21);
    //    }
    ck_assert_int_eq(ret, ret21);
    ck_assert_int_eq(strcmp(buf, buf21), 0);
  }

  free(buf);
  free(buf21);
}
END_TEST

Suite *suite_s21_sprintf_lf(void) {
  Suite *s;
  TCase *tc;

  num[0] = nan("");
  num[1] = -nan("");

  s = suite_create("s21_sprintf Lf");
  tc = tcase_create("Tcase_s21_sprintf_Lf");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, flags);
    tcase_add_test(tc, flags_width);
    tcase_add_test(tc, flags_precision);
    tcase_add_test(tc, flags_width_precision);
    tcase_add_test(tc, precision_and_rounding);
    tcase_add_test(tc, ldbl_max);
    tcase_add_test(tc, dbl_min);
    suite_add_tcase(s, tc);
  }

  return (s);
}
