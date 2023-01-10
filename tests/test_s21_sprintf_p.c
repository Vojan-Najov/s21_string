#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "suite_sprintf_flags.h"

START_TEST(pointer_flags) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  void *ptrs[5];
  ptrs[0] = NULL;
  ptrs[1] = (void *)&ret;
  ptrs[2] = (void *)&ret21;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  ptrs[3] = (void *)buf;
  ptrs[4] = (void *)buf21;

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ptrs) / sizeof(void *); ++j) {
        sprintf(format, "_%%%sp_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, ptrs[j]);
        ret21 = s21_sprintf(buf21, format, ptrs[j]);
        //        if (ret != ret21 || memcmp(buf, buf21, 1024)) {
        //          printf("%s%p\n%d:%s%d:%s\n", format, ptrs[j], ret, buf,
        //          ret21, buf21);
        //        }
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(pointer_flags_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "32", "64", NULL};
  void *ptrs[5];
  ptrs[0] = NULL;
  ptrs[1] = (void *)&ret;
  ptrs[2] = (void *)&ret21;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  ptrs[3] = (void *)buf;
  ptrs[4] = (void *)buf21;

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ptrs) / sizeof(void *); ++k) {
          sprintf(format, "_%%%s%sp_\n", sprintf_flags[i], width[j]);
          ret = sprintf(buf, format, ptrs[k]);
          ret21 = s21_sprintf(buf21, format, ptrs[k]);
          //          if (ret != ret21 || (memcmp(buf, buf21, 1024) != 0)) {
          //            printf("%s%p\n%d:%s%d:%s\n", format, ptrs[j], ret, buf,
          //            ret21,
          //                   buf21);
          //          }
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

START_TEST(pointer_flags_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  void *ptrs[5];
  ptrs[0] = NULL;
  ptrs[1] = (void *)&ret;
  ptrs[2] = (void *)&ret21;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  ptrs[3] = (void *)buf;
  ptrs[4] = (void *)buf21;

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ptrs) / sizeof(void *); ++k) {
          sprintf(format, "_%%%s.%sp_\n", sprintf_flags[i], precision[j]);
          ret = sprintf(buf, format, ptrs[k]);
          ret21 = s21_sprintf(buf21, format, ptrs[k]);
          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
            printf("%s%p\n%d:%s%d:%s\n", format, ptrs[j], ret, buf, ret21,
                   buf21);
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

START_TEST(pointer_flags_width_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "32", "64", NULL};
  char *precision[] = {"",
                       "0",
                       "1",
                       "2",
                       "3",
                       "5"
                       "32",
                       "64",
                       NULL};
  void *ptrs[5];
  ptrs[0] = NULL;
  ptrs[1] = (void *)&ret;
  ptrs[2] = (void *)&ret21;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  ptrs[3] = (void *)buf;
  ptrs[4] = (void *)buf21;

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ptrs) / sizeof(void *); ++m) {
            sprintf(format, "_%%%s%s.%sp_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret = sprintf(buf, format, ptrs[m]);
            ret21 = s21_sprintf(buf21, format, ptrs[m]);
            ck_assert_int_eq(ret, ret21);
            ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
          }
        }
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(pointer_flags_star_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  void *ptrs[5];
  ptrs[0] = NULL;
  ptrs[1] = (void *)&ret;
  ptrs[2] = (void *)&ret21;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  ptrs[3] = (void *)buf;
  ptrs[4] = (void *)buf21;

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ptrs) / sizeof(void *); ++m) {
          sprintf(format, "_%%%s*p_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], ptrs[m]);
          ret21 = s21_sprintf(buf21, format, width[j], ptrs[m]);
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

START_TEST(pointer_flags_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  void *ptrs[5];
  ptrs[0] = NULL;
  ptrs[1] = (void *)&ret;
  ptrs[2] = (void *)&ret21;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  ptrs[3] = (void *)buf;
  ptrs[4] = (void *)buf21;

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ptrs) / sizeof(void *); ++m) {
          sprintf(format, "_%%%s.*p_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, precision[j], ptrs[m]);
          ret21 = s21_sprintf(buf21, format, precision[j], ptrs[m]);
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

START_TEST(pointer_flags_star_width_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 5, 10, 16, 32};
  int precision[] = {0, 1, 2, 3, 5, 10, 16, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  void *ptrs[5];
  ptrs[0] = NULL;
  ptrs[1] = (void *)&ret;
  ptrs[2] = (void *)&ret21;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  ptrs[3] = (void *)buf;
  ptrs[4] = (void *)buf21;

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ptrs) / sizeof(void *); ++m) {
            sprintf(format, "_%%%s*.*p_\n", sprintf_flags[i]);
            ret = sprintf(buf, format, width[j], precision[k], ptrs[m]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], ptrs[m]);
            ck_assert_int_eq(ret, ret21);
            ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
          }
        }
      }
    }
  }
  free(buf);
  free(buf21);
}
END_TEST

Suite *suite_s21_sprintf_p(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf p");
  tc = tcase_create("TCase_s21_sprintf_p");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, pointer_flags);
    tcase_add_test(tc, pointer_flags_width);
    tcase_add_test(tc, pointer_flags_precision);
    tcase_add_test(tc, pointer_flags_width_precision);
    tcase_add_test(tc, pointer_flags_star_width);
    tcase_add_test(tc, pointer_flags_star_precision);
    tcase_add_test(tc, pointer_flags_star_width_star_precision);

    suite_add_tcase(s, tc);
  }

  return (s);
}
