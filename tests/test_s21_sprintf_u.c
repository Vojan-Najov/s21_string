#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "suite_sprintf_flags.h"

START_TEST(unsigned_flags_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  unsigned char ints[] = {0, 1, 87, 113, CHAR_MAX, 179, UCHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(char); ++j) {
        sprintf(format, "_%%%shhu_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, ints[j]);
        ret21 = s21_sprintf(buf21, format, ints[j]);
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(unsigned_flags_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  unsigned short int ints[] = {0,        1,         62,  CHAR_MAX, 1354,
                               SHRT_MAX, UCHAR_MAX, 589, USHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(short int); ++j) {
        sprintf(format, "_%%%shu_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, ints[j]);
        ret21 = s21_sprintf(buf21, format, ints[j]);
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(unsigned_flags) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  unsigned int ints[] = {0,       1,         19,        CHAR_MAX,
                         1078,    SHRT_MAX,  10937,     279303,
                         INT_MAX, UCHAR_MAX, USHRT_MAX, UINT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(int); ++j) {
        sprintf(format, "_%%%su_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, ints[j]);
        ret21 = s21_sprintf(buf21, format, ints[j]);
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(unsigned_flags_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  unsigned long int ints[] = {0,        1,        CHAR_MAX,  SHRT_MAX,
                              INT_MAX,  LONG_MAX, UCHAR_MAX, USHRT_MAX,
                              UINT_MAX, ULONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(long int); ++j) {
        sprintf(format, "_%%%slu_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, ints[j]);
        ret21 = s21_sprintf(buf21, format, ints[j]);
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(unsigned_flags_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  unsigned long long int ints[] = {0,         1,        CHAR_MAX,  SHRT_MAX,
                                   INT_MAX,   LONG_MAX, LLONG_MAX, UCHAR_MAX,
                                   USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(long long int); ++j) {
        sprintf(format, "_%%%sllu_\n", sprintf_flags[i]);
        ret = sprintf(buf, format, ints[j]);
        ret21 = s21_sprintf(buf21, format, ints[j]);
        ck_assert_int_eq(ret, ret21);
        ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
      }
    }
  }

  free(buf);
  free(buf21);
}
END_TEST

START_TEST(unsigned_flags_width_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  unsigned char ints[] = {0, 1, 87, 113, CHAR_MAX, 179, UCHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(char); ++k) {
          sprintf(format, "_%%%s%shhu_\n", sprintf_flags[i], width[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_width_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  unsigned short int ints[] = {0,        1,         62,  CHAR_MAX, 1354,
                               SHRT_MAX, UCHAR_MAX, 589, USHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(short int); ++k) {
          sprintf(format, "_%%%s%shu_\n", sprintf_flags[i], width[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  unsigned int ints[] = {0,       1,         19,        CHAR_MAX,
                         1078,    SHRT_MAX,  10937,     279303,
                         INT_MAX, UCHAR_MAX, USHRT_MAX, UINT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(int); ++k) {
          sprintf(format, "_%%%s%su_\n", sprintf_flags[i], width[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_width_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  unsigned long int ints[] = {0,        1,        CHAR_MAX,  SHRT_MAX,
                              INT_MAX,  LONG_MAX, UCHAR_MAX, USHRT_MAX,
                              UINT_MAX, ULONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(long int); ++k) {
          sprintf(format, "_%%%s%slu_\n", sprintf_flags[i], width[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_width_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  unsigned long long int ints[] = {0,         1,        CHAR_MAX,  SHRT_MAX,
                                   INT_MAX,   LONG_MAX, LLONG_MAX, UCHAR_MAX,
                                   USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(long long int); ++k) {
          sprintf(format, "_%%%s%sllu_\n", sprintf_flags[i], width[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_precision_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  unsigned char ints[] = {0, 1, 87, 113, CHAR_MAX, 179, UCHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(char); ++k) {
          sprintf(format, "_%%%s.%shhu_\n", sprintf_flags[i], precision[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_precision_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  unsigned short int ints[] = {0,        1,         62,  CHAR_MAX, 1354,
                               SHRT_MAX, UCHAR_MAX, 589, USHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(short int); ++k) {
          sprintf(format, "_%%%s.%shu_\n", sprintf_flags[i], precision[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  unsigned int ints[] = {0,       1,         19,        CHAR_MAX,
                         1078,    SHRT_MAX,  10937,     279303,
                         INT_MAX, UCHAR_MAX, USHRT_MAX, UINT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(int); ++k) {
          sprintf(format, "_%%%s.%su_\n", sprintf_flags[i], precision[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  unsigned long int ints[] = {0,        1,        CHAR_MAX,  SHRT_MAX,
                              INT_MAX,  LONG_MAX, UCHAR_MAX, USHRT_MAX,
                              UINT_MAX, ULONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(long int); ++k) {
          sprintf(format, "_%%%s.%slu_\n", sprintf_flags[i], precision[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_precision_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  unsigned long long int ints[] = {0,         1,        CHAR_MAX,  SHRT_MAX,
                                   INT_MAX,   LONG_MAX, LLONG_MAX, UCHAR_MAX,
                                   USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(long long int); ++k) {
          sprintf(format, "_%%%s.%sllu_\n", sprintf_flags[i], precision[j]);
          ret = sprintf(buf, format, ints[k]);
          ret21 = s21_sprintf(buf21, format, ints[k]);
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

START_TEST(unsigned_flags_width_precision_hh) {
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
  unsigned char ints[] = {0, 1, 87, 113, CHAR_MAX, 179, UCHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
            sprintf(format, "_%%%s%s.%shhu_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret = sprintf(buf, format, ints[m]);
            ret21 = s21_sprintf(buf21, format, ints[m]);
            if (ret != ret21 || memcmp(buf, buf21, 1024)) {
              printf("%s%d\n%d:%s%d:%s", format, ints[k], ret, buf, ret21,
                     buf21);
            }
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

START_TEST(unsigned_flags_width_precision_h) {
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
  unsigned short int ints[] = {0,        1,         62,  CHAR_MAX, 1354,
                               SHRT_MAX, UCHAR_MAX, 589, USHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
            sprintf(format, "_%%%s%s.%shu_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret = sprintf(buf, format, ints[m]);
            ret21 = s21_sprintf(buf21, format, ints[m]);
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

START_TEST(unsigned_flags_width_precision) {
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
  unsigned int ints[] = {0,       1,         19,        CHAR_MAX,
                         1078,    SHRT_MAX,  10937,     279303,
                         INT_MAX, UCHAR_MAX, USHRT_MAX, UINT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
            sprintf(format, "_%%%s%s.%su_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret = sprintf(buf, format, ints[m]);
            ret21 = s21_sprintf(buf21, format, ints[m]);
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

START_TEST(unsigned_flags_width_precision_l) {
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
  unsigned long int ints[] = {0,        1,        CHAR_MAX,  SHRT_MAX,
                              INT_MAX,  LONG_MAX, UCHAR_MAX, USHRT_MAX,
                              UINT_MAX, ULONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
            sprintf(format, "_%%%s%s.%slu_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret = sprintf(buf, format, ints[m]);
            ret21 = s21_sprintf(buf21, format, ints[m]);
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

START_TEST(unsigned_flags_width_precision_ll) {
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
  unsigned long long int ints[] = {0,         1,        CHAR_MAX,  SHRT_MAX,
                                   INT_MAX,   LONG_MAX, LLONG_MAX, UCHAR_MAX,
                                   USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long long int); ++m) {
            sprintf(format, "_%%%s%s.%sllu_\n", sprintf_flags[i], width[j],
                    precision[k]);
            ret = sprintf(buf, format, ints[m]);
            ret21 = s21_sprintf(buf21, format, ints[m]);
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

START_TEST(unsigned_flags_star_width_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  unsigned char ints[] = {0, 1, 87, 113, CHAR_MAX, 179, UCHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
          sprintf(format, "_%%%s*hhu_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
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

START_TEST(unsigned_flags_star_width_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  unsigned short int ints[] = {0,        1,         62,  CHAR_MAX, 1354,
                               SHRT_MAX, UCHAR_MAX, 589, USHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
          sprintf(format, "_%%%s*hu_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
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

START_TEST(unsigned_flags_star_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  unsigned int ints[] = {0,       1,         19,        CHAR_MAX,
                         1078,    SHRT_MAX,  10937,     279303,
                         INT_MAX, UCHAR_MAX, USHRT_MAX, UINT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
          sprintf(format, "_%%%s*u_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
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

START_TEST(unsigned_flags_star_width_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  unsigned long int ints[] = {0,        1,        CHAR_MAX,  SHRT_MAX,
                              INT_MAX,  LONG_MAX, UCHAR_MAX, USHRT_MAX,
                              UINT_MAX, ULONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
          sprintf(format, "_%%%s*lu_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
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

START_TEST(unsigned_flags_star_width_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  unsigned long long int ints[] = {0,         1,        CHAR_MAX,  SHRT_MAX,
                                   INT_MAX,   LONG_MAX, LLONG_MAX, UCHAR_MAX,
                                   USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(long long int); ++m) {
          sprintf(format, "_%%%s*llu_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, width[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, width[j], ints[m]);
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

START_TEST(unsigned_flags_star_precision_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned char ints[] = {0, 1, 87, 113, CHAR_MAX, 179, UCHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
          sprintf(format, "_%%%s.*hhu_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, precision[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, precision[j], ints[m]);
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

START_TEST(unsigned_flags_star_precision_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned short int ints[] = {0,        1,         62,  CHAR_MAX, 1354,
                               SHRT_MAX, UCHAR_MAX, 589, USHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
          sprintf(format, "_%%%s.*hu_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, precision[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, precision[j], ints[m]);
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

START_TEST(unsigned_flags_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned int ints[] = {0,       1,         19,        CHAR_MAX,
                         1078,    SHRT_MAX,  10937,     279303,
                         INT_MAX, UCHAR_MAX, USHRT_MAX, UINT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
          sprintf(format, "_%%%s.*u_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, precision[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, precision[j], ints[m]);
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

START_TEST(unsigned_flags_star_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned long int ints[] = {0,        1,        CHAR_MAX,  SHRT_MAX,
                              INT_MAX,  LONG_MAX, UCHAR_MAX, USHRT_MAX,
                              UINT_MAX, ULONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
          sprintf(format, "_%%%s.*lu_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, precision[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, precision[j], ints[m]);
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

START_TEST(unsigned_flags_star_precision_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned long long int ints[] = {0,         1,        CHAR_MAX,  SHRT_MAX,
                                   INT_MAX,   LONG_MAX, LLONG_MAX, UCHAR_MAX,
                                   USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(long long int); ++m) {
          sprintf(format, "_%%%s.*llu_\n", sprintf_flags[i]);
          ret = sprintf(buf, format, precision[j], ints[m]);
          ret21 = s21_sprintf(buf21, format, precision[j], ints[m]);
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

START_TEST(unsigned_flags_star_width_star_precision_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned char ints[] = {0, 1, 87, 113, CHAR_MAX, 179, UCHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
            sprintf(format, "_%%%s*.*hhu_\n", sprintf_flags[i]);
            ret = sprintf(buf, format, width[j], precision[k], ints[m]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], ints[m]);
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

START_TEST(unsigned_flags_star_width_star_precision_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned short int ints[] = {0,        1,         62,  CHAR_MAX, 1354,
                               SHRT_MAX, UCHAR_MAX, 589, USHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
            sprintf(format, "_%%%s*.*hu_\n", sprintf_flags[i]);
            ret = sprintf(buf, format, width[j], precision[k], ints[m]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], ints[m]);
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

START_TEST(unsigned_flags_star_width_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned int ints[] = {0,       1,         19,        CHAR_MAX,
                         1078,    SHRT_MAX,  10937,     279303,
                         INT_MAX, UCHAR_MAX, USHRT_MAX, UINT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
            sprintf(format, "_%%%s*.*u_\n", sprintf_flags[i]);
            ret = sprintf(buf, format, width[j], precision[k], ints[m]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], ints[m]);
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

START_TEST(unsigned_flags_star_width_star_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned long int ints[] = {0,        1,        CHAR_MAX,  SHRT_MAX,
                              INT_MAX,  LONG_MAX, UCHAR_MAX, USHRT_MAX,
                              UINT_MAX, ULONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
            sprintf(format, "_%%%s*.*lu_\n", sprintf_flags[i]);
            ret = sprintf(buf, format, width[j], precision[k], ints[m]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], ints[m]);
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

START_TEST(unsigned_flags_star_width_star_precision_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  unsigned long long int ints[] = {0,         1,        CHAR_MAX,  SHRT_MAX,
                                   INT_MAX,   LONG_MAX, LLONG_MAX, UCHAR_MAX,
                                   USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long long); ++m) {
            sprintf(format, "_%%%s*.*llu_\n", sprintf_flags[i]);
            ret = sprintf(buf, format, width[j], precision[k], ints[m]);
            ret21 = s21_sprintf(buf21, format, width[j], precision[k], ints[m]);
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

Suite *suite_s21_sprintf_u(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf u");
  tc = tcase_create("TCase_s21_sprintf_u");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, unsigned_flags_hh);
    tcase_add_test(tc, unsigned_flags_h);
    tcase_add_test(tc, unsigned_flags);
    tcase_add_test(tc, unsigned_flags_l);
    tcase_add_test(tc, unsigned_flags_ll);
    tcase_add_test(tc, unsigned_flags_width_hh);
    tcase_add_test(tc, unsigned_flags_width_h);
    tcase_add_test(tc, unsigned_flags_width);
    tcase_add_test(tc, unsigned_flags_width_l);
    tcase_add_test(tc, unsigned_flags_width_ll);
    tcase_add_test(tc, unsigned_flags_precision_hh);
    tcase_add_test(tc, unsigned_flags_precision_h);
    tcase_add_test(tc, unsigned_flags_precision);
    tcase_add_test(tc, unsigned_flags_precision_l);
    tcase_add_test(tc, unsigned_flags_precision_ll);
    tcase_add_test(tc, unsigned_flags_width_precision_hh);
    tcase_add_test(tc, unsigned_flags_width_precision_h);
    tcase_add_test(tc, unsigned_flags_width_precision);
    tcase_add_test(tc, unsigned_flags_width_precision_l);
    tcase_add_test(tc, unsigned_flags_width_precision_ll);
    tcase_add_test(tc, unsigned_flags_star_width_hh);
    tcase_add_test(tc, unsigned_flags_star_width_h);
    tcase_add_test(tc, unsigned_flags_star_width);
    tcase_add_test(tc, unsigned_flags_star_width_l);
    tcase_add_test(tc, unsigned_flags_star_width_ll);
    tcase_add_test(tc, unsigned_flags_star_precision_hh);
    tcase_add_test(tc, unsigned_flags_star_precision_h);
    tcase_add_test(tc, unsigned_flags_star_precision);
    tcase_add_test(tc, unsigned_flags_star_precision_l);
    tcase_add_test(tc, unsigned_flags_star_precision_ll);
    tcase_add_test(tc, unsigned_flags_star_width_star_precision_hh);
    tcase_add_test(tc, unsigned_flags_star_width_star_precision_h);
    tcase_add_test(tc, unsigned_flags_star_width_star_precision);
    tcase_add_test(tc, unsigned_flags_star_width_star_precision_l);
    tcase_add_test(tc, unsigned_flags_star_width_star_precision_ll);
    suite_add_tcase(s, tc);
  }

  return (s);
}
