#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "suite_sprintf_flags.h"

START_TEST(char_flags) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  unsigned char c = 'a';

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      sprintf(format, "_%%%sc_\n", sprintf_flags[i]);
      ret = sprintf(buf, format, c);
      ret21 = s21_sprintf(buf21, format, c);
      ck_assert_int_eq(ret, ret21);
      ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      ++c;
      c = c > 'z' ? 'a' : c;
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(char_flags_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "10", "32", NULL};
  unsigned char c = 'a';

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j]; ++j) {
        sprintf(format, "_%%%s%sc_\n", sprintf_flags[i], width[j]);
        ret = sprintf(buf, format, c);
        ret21 = s21_sprintf(buf21, format, c);
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        ++c;
        c = c > 'z' ? 'a' : c;
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(char_flags_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "32", NULL};
  unsigned char c = '!';

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        sprintf(format, "_%%%s.%sc_\n", sprintf_flags[i], precision[j]);
        ret = sprintf(buf, format, c);
        ret21 = s21_sprintf(buf21, format, c);
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        ++c;
        c = c > 'z' ? '!' : c;
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(char_flags_width_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "32", "64", NULL};
  char *precision[] = {"", "0", "1", "2", "32", "64", NULL};
  unsigned char c = '!';

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j]; ++j) {
        for (int k = 0; precision[k]; ++k) {
          sprintf(format, "_%%%s%s.%sc_\n", sprintf_flags[i], width[j],
                  precision[k]);
          ret = sprintf(buf, format, c);
          ret21 = s21_sprintf(buf21, format, c);
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
          ++c;
          c = c > 'z' ? '!' : c;
        }
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(char_flags_star_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  unsigned char c = 0;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        sprintf(format, "_%%%s*c_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, width[j], c);
        ret21 = s21_sprintf(buf21, format, width[j], c);
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        ++c;
        c = c > 'z' ? 0 : c;
      }
    }
    free(buf);
    free(buf21);
  }
}
END_TEST

START_TEST(char_flags_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned char c = '!';

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        sprintf(format, "_%%%s.*c_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, precision[j], c);
        ret21 = s21_sprintf(buf21, format, precision[j], c);
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        ++c;
        c = c > 'z' ? '!' : c;
      }
    }
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(char_flags_star_width_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32, 64};
  int precision[] = {0, 1, 2, 32, 64};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = sizeof(precision) / sizeof(int);
  unsigned char c = '!';

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          sprintf(format, "_%%%s*.*c_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], precision[k], c);
          ret21 = s21_sprintf(buf21, format, width[j], precision[k], c);
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
          ++c;
          c = c > 'z' ? '!' : c;
        }
      }
    }
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(wchar_ascii) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32, 64};
  int precision[] = {0, 1, 2, 32, 64};
  int wlen = sizeof(width) / sizeof(int);
  int plen = sizeof(precision) / sizeof(int);
  wchar_t wc = '!';

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          sprintf(format, "_%%%s*.*lc_\n", sprintf_flags[i]);
#ifdef __MUSL__
          if (strchr(format, '0') || strchr(format, '#')) continue;
#endif
          ret = sprintf(buf, format, width[j], precision[k], wc);
          ret21 = s21_sprintf(buf21, format, width[j], precision[k], wc);
          //          if (ret != ret21) {
          //            printf("wc = %x\n", wc);
          //          }
          ck_assert_int_eq(ret, ret21);
          if (ret == ret21 && ret > 0)
            ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
          ++wc;
          wc = wc > '}' ? '!' : wc;
        }
      }
    }
  }
  free(buf);
  free(buf21);
}
END_TEST

START_TEST(wchar) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32, 64};
  int precision[] = {0, 1, 2, 32, 64};
  int wlen = sizeof(width) / sizeof(int);
  int plen = sizeof(precision) / sizeof(int);
  wchar_t wc = 0;

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  setlocale(LC_ALL, "");
  wc = 0x100000;
  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          sprintf(format, "_%%%s*.*lc_\n", sprintf_flags[i]);
#ifdef __MUSL__
          if (strchr(format, '0') || strchr(format, '#')) continue;
#endif
          ret = sprintf(buf, format, width[j], precision[k], wc);
          ret21 = s21_sprintf(buf21, format, width[j], precision[k], wc);
          ck_assert_int_eq(ret, ret21);
          if (ret > 0) ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
          ++wc;
        }
      }
    }
  }
  setlocale(LC_CTYPE, "C");

  free(buf);
  free(buf21);
}
END_TEST

Suite *suite_s21_sprintf_c(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf c");
  tc = tcase_create("TCase_s21_sprintf_c");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, char_flags);
    tcase_add_test(tc, char_flags_width);
    tcase_add_test(tc, char_flags_precision);
    tcase_add_test(tc, char_flags_width_precision);
    tcase_add_test(tc, char_flags_star_width);
    tcase_add_test(tc, char_flags_star_precision);
    tcase_add_test(tc, char_flags_star_width_star_precision);
    tcase_add_test(tc, wchar_ascii);
    tcase_add_test(tc, wchar);
    suite_add_tcase(s, tc);
  }

  return (s);
}
