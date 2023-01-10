#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "suite_sprintf_flags.h"

START_TEST(string_flags) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *str[] = {
      NULL,
      "",
      "a",
      "ab",
      "abc",
      "abcd",
      "abcde",
      "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(char *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int s = 0; s < len; ++s) {
        sprintf(format, "_%%%ss_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, str[s]);
        ret21 = s21_sprintf(buf21, format, str[s]);
        //        if (ret != ret21 || memcmp(buf, buf21, 1024)) {
        //          printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
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

START_TEST(string_flags_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "10", "32", NULL};
  char *str[] = {
      NULL,
      "",
      "a",
      "ab",
      "abc",
      "abcd",
      "abcde",
      "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(char *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j]; ++j) {
        for (int s = 0; s < len; ++s) {
          sprintf(format, "_%%%s%ss_\n", sprintf_flags[i], width[j]);
          ret = sprintf(buf, format, str[s]);
          ret21 = s21_sprintf(buf21, format, str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
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

START_TEST(string_flags_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "32", NULL};
  char *str[] = {
      NULL,
      "",
      "a",
      "ab",
      "abc",
      "abcd",
      "abcde",
      "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(char *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (int s = 0; s < len; ++s) {
          sprintf(format, "_%%%s.%ss_\n", sprintf_flags[i], precision[j]);
          ret = sprintf(buf, format, str[s]);
          ret21 = s21_sprintf(buf21, format, str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
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

START_TEST(string_flags_width_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "32", "64", NULL};
  char *precision[] = {"", "0", "1", "2", "32", "64", NULL};
  char *str[] = {
      NULL,
      "",
      "a",
      "ab",
      "abc",
      "abcd",
      "abcde",
      "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(char *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j]; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (int s = 0; s < len; ++s) {
            sprintf(format, "_%%%s%s.%ss_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret = sprintf(buf, format, str[s]);
            ret21 = s21_sprintf(buf21, format, str[s]);
            //            if (ret != ret21 || memcmp(buf, buf21, 1024)) {
            //              printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
            //              buf21);
            //            }
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

START_TEST(string_flags_star_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  char *str[] = {
      NULL,
      "",
      "a",
      "ab",
      "abc",
      "abcd",
      "abcde",
      "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(char *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int s = 0; s < len; ++s) {
          sprintf(format, "_%%%s*s_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], str[s]);
          ret21 = s21_sprintf(buf21, format, width[j], str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
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

START_TEST(string_flags_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  char *str[] = {
      NULL,
      "",
      "a",
      "ab",
      "abc",
      "abcd",
      "abcde",
      "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(char *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (int s = 0; s < len; ++s) {
          sprintf(format, "_%%%s.*s_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, precision[j], str[s]);
          ret21 = s21_sprintf(buf21, format, precision[j], str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
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

START_TEST(string_flags_star_width_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32, 64};
  int precision[] = {0, 1, 2, 32, 64};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = sizeof(precision) / sizeof(int);
  char *str[] = {
      NULL,
      "",
      "a",
      "ab",
      "abc",
      "abcd",
      "abcde",
      "asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"
      "asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(char *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (int s = 0; s < len; ++s) {
            sprintf(format, "_%%%s*.*s_\n", sprintf_flags[i]);
            ret = sprintf(buf, format, width[j], precision[k], str[s]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], str[s]);
            //            if (ret != ret21 || memcmp(buf, buf21, 1024)) {
            //              printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
            //              buf21);
            //            }
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

START_TEST(string_flags_l_ascii) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  wchar_t *str[] = {
      NULL,
      L"",
      L"a",
      L"ab",
      L"abc",
      L"abcd",
      L"abcde",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
        if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
        sprintf(format, "_%%%ss_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, str[s]);
        ret21 = s21_sprintf(buf21, format, str[s]);
        //        if (ret != ret21 || memcmp(buf, buf21, 1024)) {
        //          printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
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

START_TEST(string_flags_width_l_ascii) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "10", "32", NULL};
  wchar_t *str[] = {
      NULL,
      L"",
      L"a",
      L"ab",
      L"abc",
      L"abcd",
      L"abcde",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j]; ++j) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%s%ss_\n", sprintf_flags[i], width[j]);
          ret = sprintf(buf, format, str[s]);
          ret21 = s21_sprintf(buf21, format, str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
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

START_TEST(string_flags_precision_l_ascii) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "32", NULL};
  wchar_t *str[] = {
      NULL,
      L"",
      L"a",
      L"ab",
      L"abc",
      L"abcd",
      L"abcde",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%s.%ss_\n", sprintf_flags[i], precision[j]);
          ret = sprintf(buf, format, str[s]);
          ret21 = s21_sprintf(buf21, format, str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
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

START_TEST(string_flags_width_precision_l_ascii) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "32", "64", NULL};
  char *precision[] = {"", "0", "1", "2", "32", "64", NULL};
  wchar_t *str[] = {
      NULL,
      L"",
      L"a",
      L"ab",
      L"abc",
      L"abcd",
      L"abcde",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j]; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s%s.%ss_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret = sprintf(buf, format, str[s]);
            ret21 = s21_sprintf(buf21, format, str[s]);
            //            if (ret != ret21 || memcmp(buf, buf21, 1024)) {
            //              printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
            //              buf21);
            //            }
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

START_TEST(string_flags_star_width_l_ascii) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  wchar_t *str[] = {
      NULL,
      L"",
      L"a",
      L"ab",
      L"abc",
      L"abcd",
      L"abcde",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%s*s_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], str[s]);
          ret21 = s21_sprintf(buf21, format, width[j], str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
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

START_TEST(string_flags_star_precision_l_ascii) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  wchar_t *str[] = {
      NULL,
      L"",
      L"a",
      L"ab",
      L"abc",
      L"abcd",
      L"abcde",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%s.*s_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, precision[j], str[s]);
          ret21 = s21_sprintf(buf21, format, precision[j], str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
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

START_TEST(string_flags_star_width_star_precision_l_ascii) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32, 64};
  int precision[] = {0, 1, 2, 32, 64};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = sizeof(precision) / sizeof(int);
  wchar_t *str[] = {
      NULL,
      L"",
      L"a",
      L"ab",
      L"abc",
      L"abcd",
      L"abcde",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskaksak",
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"
      L"asask askskas kasakskas askskakas asksakask askskka askskaskak"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s*.*s_\n", sprintf_flags[i]);
            ret = sprintf(buf, format, width[j], precision[k], str[s]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], str[s]);
            //            if (ret != ret21 || memcmp(buf, buf21, 1024)) {
            //              printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
            //              buf21);
            //            }
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

START_TEST(string_flags_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  wchar_t *str[] = {NULL,
                    L"",
                    L"a",
                    L"ab",
                    L"abc",
                    L"abcd",
                    L"abcde",
                    L"φωϊϣϺ᮵φω",
                    L"φωϊ",
                    L"φ",
                    L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                    L"asask askskas kasakskas askskakas asksakask askskk",
                    L"asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  setlocale(LC_ALL, "");

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
        if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
        sprintf(format, "_%%%sls_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, str[s]);
        ret21 = s21_sprintf(buf21, format, str[s]);
        //        if (ret != ret21 || memcmp(buf, buf21, 1024)) {
        //          printf("%s%d:%s%d:%s\n", format, ret, buf, ret21, buf21);
        //        }
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
  setlocale(LC_CTYPE, "C");
}
END_TEST

START_TEST(string_flags_width_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "10", "32", NULL};
  wchar_t *str[] = {NULL,
                    L"",
                    L"a",
                    L"ab",
                    L"abc",
                    L"abcd",
                    L"abcde",
                    L"φωϊϣϺ᮵φω",
                    L"φωϊ",
                    L"φ",
                    L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                    L"asask askskas kasakskas askskakas asksakask askskk",
                    L"asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  setlocale(LC_ALL, "");

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j]; ++j) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%s%sls_\n", sprintf_flags[i], width[j]);
          ret = sprintf(buf, format, str[s]);
          ret21 = s21_sprintf(buf21, format, str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
          //          }
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        }
      }
    }
  }

  free(buf);
  free(buf21);
  setlocale(LC_CTYPE, "C");
}
END_TEST

START_TEST(string_flags_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "32", NULL};
  wchar_t *str[] = {NULL,
                    L"",
                    L"a",
                    L"ab",
                    L"abc",
                    L"abcd",
                    L"abcde",
                    L"φωϊϣϺ᮵φω",
                    L"φωϊ",
                    L"φ",
                    L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                    L"asask askskas kasakskas askskakas asksakask askskk",
                    L"asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  setlocale(LC_ALL, "");

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));
  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%s.%sls_\n", sprintf_flags[i], precision[j]);
          ret = sprintf(buf, format, str[s]);
          ret21 = s21_sprintf(buf21, format, str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
          //          }
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        }
      }
    }
  }

  free(buf);
  free(buf21);
  setlocale(LC_CTYPE, "C");
}
END_TEST

START_TEST(string_flags_width_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "32", "64", NULL};
  char *precision[] = {"", "0", "1", "2", "32", "64", NULL};
  wchar_t *str[] = {NULL,
                    L"",
                    L"a",
                    L"ab",
                    L"abc",
                    L"abcd",
                    L"abcde",
                    L"φωϊϣϺ᮵φω",
                    L"φωϊ",
                    L"φ",
                    L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                    L"asask askskas kasakskas askskakas asksakask askskk",
                    L"asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  setlocale(LC_ALL, "");

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j]; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s%s.%sls_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret = sprintf(buf, format, str[s]);
            ret21 = s21_sprintf(buf21, format, str[s]);
            //            if (ret != ret21 || memcmp(buf, buf21, 1024)) {
            //              printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
            //              buf21);
            //            }
            ck_assert_int_eq(ret, ret21);
            ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
          }
        }
      }
    }
  }

  free(buf);
  free(buf21);
  setlocale(LC_CTYPE, "C");
}
END_TEST

START_TEST(string_flags_star_width_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  wchar_t *str[] = {NULL,
                    L"",
                    L"a",
                    L"ab",
                    L"abc",
                    L"abcd",
                    L"abcde",
                    L"φωϊϣϺ᮵φω",
                    L"φωϊ",
                    L"φ",
                    L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                    L"asask askskas kasakskas askskakas asksakask askskk",
                    L"asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  setlocale(LC_ALL, "");

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%s*ls_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], str[s]);
          ret21 = s21_sprintf(buf21, format, width[j], str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
          //          }
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        }
      }
    }
  }
  free(buf);
  free(buf21);
  setlocale(LC_CTYPE, "C");
}
END_TEST

START_TEST(string_flags_star_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  wchar_t *str[] = {NULL,
                    L"",
                    L"a",
                    L"ab",
                    L"abc",
                    L"abcd",
                    L"abcde",
                    L"φωϊϣϺ᮵φω",
                    L"φωϊ",
                    L"φ",
                    L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                    L"asask askskas kasakskas askskakas asksakask askskk",
                    L"asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  setlocale(LC_ALL, "");

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
          if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
          sprintf(format, "_%%%s.*ls_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, precision[j], str[s]);
          ret21 = s21_sprintf(buf21, format, precision[j], str[s]);
          //          if (ret != ret21 || memcmp(buf, buf21, 1024)) {
          //            printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
          //            buf21);
          //          }
          ck_assert_int_eq(ret, ret21);
          ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
        }
      }
    }
  }
  free(buf);
  free(buf21);
  setlocale(LC_CTYPE, "C");
}
END_TEST

START_TEST(string_flags_star_width_star_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 32, 64};
  int precision[] = {0, 1, 2, 32, 64};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = sizeof(precision) / sizeof(int);
  wchar_t *str[] = {NULL,
                    L"",
                    L"a",
                    L"ab",
                    L"abc",
                    L"abcd",
                    L"abcde",
                    L"φωϊϣϺ᮵φω",
                    L"φωϊ",
                    L"φ",
                    L"φωϊϣ Ϻ᮵φω φωϊϣϺ᮵ φ ωφω ϊϣϺ᮵φω",
                    L"asask askskas kasakskas askskakas asksakask askskk",
                    L"asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"
                    "asask askskas kasakskas askskakas asksakask askskkk"};
  int len = (int)(sizeof(str) / (sizeof(wchar_t *)));

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  setlocale(LC_ALL, "");

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (int s = 0; s < len; ++s) {
#ifdef __MUSL__
            if (str[s] == NULL || strrchr(format, '0')) continue;
#endif
            sprintf(format, "_%%%s*.*ls_\n", sprintf_flags[i]);
            ret = sprintf(buf, format, width[j], precision[k], str[s]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], str[s]);
            //            if (ret != ret21 || memcmp(buf, buf21, 1024)) {
            //              printf("%s%d:%s%d:%s\n", format, ret, buf, ret21,
            //              buf21);
            //            }
            ck_assert_int_eq(ret, ret21);
            ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
          }
        }
      }
    }
  }
  free(buf);
  free(buf21);
  setlocale(LC_CTYPE, "C");
}
END_TEST

Suite *suite_s21_sprintf_s(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf s");
  tc = tcase_create("TCase_s21_sprintf_s");
  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, string_flags);
    tcase_add_test(tc, string_flags_width);
    tcase_add_test(tc, string_flags_precision);
    tcase_add_test(tc, string_flags_width_precision);
    tcase_add_test(tc, string_flags_star_width);
    tcase_add_test(tc, string_flags_star_precision);
    tcase_add_test(tc, string_flags_star_width_star_precision);
    tcase_add_test(tc, string_flags_l_ascii);
    tcase_add_test(tc, string_flags_width_l_ascii);
    tcase_add_test(tc, string_flags_precision_l_ascii);
    tcase_add_test(tc, string_flags_width_precision_l_ascii);
    tcase_add_test(tc, string_flags_star_width_l_ascii);
    tcase_add_test(tc, string_flags_star_precision_l_ascii);
    tcase_add_test(tc, string_flags_star_width_star_precision_l_ascii);
    tcase_add_test(tc, string_flags_l);
    tcase_add_test(tc, string_flags_l);
    tcase_add_test(tc, string_flags_width_l);
    tcase_add_test(tc, string_flags_precision_l);
    tcase_add_test(tc, string_flags_width_precision_l);
    tcase_add_test(tc, string_flags_star_width_l);
    tcase_add_test(tc, string_flags_star_precision_l);
    tcase_add_test(tc, string_flags_star_width_star_precision_l);
    suite_add_tcase(s, tc);
  }

  return (s);
}
