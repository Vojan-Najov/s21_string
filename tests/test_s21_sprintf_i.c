#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "suite_sprintf_flags.h"

START_TEST(decimal_flags_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(char); ++j) {
        sprintf(format, "_%%%shhi_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                      0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(short int); ++j) {
        sprintf(format, "_%%%shi_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                -1,       0,        1,      19,       CHAR_MAX, 1078,
                SHRT_MAX, 10937,    279303, INT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(int); ++j) {
        sprintf(format, "_%%%si_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                     1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(long int); ++j) {
        sprintf(format, "_%%%sli_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                          -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                          INT_MAX,   LONG_MAX, LLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (size_t j = 0; j < sizeof(ints) / sizeof(long long int); ++j) {
        sprintf(format, "_%%%slli_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_width_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(char); ++k) {
          sprintf(format, "_%%%s%shhi_\n", sprintf_flags[i], width[j]);
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

START_TEST(decimal_flags_width_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                      0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(short int); ++k) {
          sprintf(format, "_%%%s%shi_\n", sprintf_flags[i], width[j]);
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

START_TEST(decimal_flags_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                -1,       0,        1,      19,       CHAR_MAX, 1078,
                SHRT_MAX, 10937,    279303, INT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(int); ++k) {
          sprintf(format, "_%%%s%si_\n", sprintf_flags[i], width[j]);
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

START_TEST(decimal_flags_width_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                     1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(long int); ++k) {
          sprintf(format, "_%%%s%sli_\n", sprintf_flags[i], width[j]);
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

START_TEST(decimal_flags_width_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *width[] = {"1", "2", "3", "5", "10", "32", NULL};
  long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                          -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                          INT_MAX,   LONG_MAX, LLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(long long int); ++k) {
          sprintf(format, "_%%%s%slli_\n", sprintf_flags[i], width[j]);
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

START_TEST(decimal_flags_precision_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(char); ++k) {
          sprintf(format, "_%%%s.%shhi_\n", sprintf_flags[i], precision[j]);
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

START_TEST(decimal_flags_precision_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                      0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(short int); ++k) {
          sprintf(format, "_%%%s.%shi_\n", sprintf_flags[i], precision[j]);
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

START_TEST(decimal_flags_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                -1,       0,        1,      19,       CHAR_MAX, 1078,
                SHRT_MAX, 10937,    279303, INT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(int); ++k) {
          sprintf(format, "_%%%s.%si_\n", sprintf_flags[i], precision[j]);
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

START_TEST(decimal_flags_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                     1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(long int); ++k) {
          sprintf(format, "_%%%s.%sli_\n", sprintf_flags[i], precision[j]);
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

START_TEST(decimal_flags_precision_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  char *precision[] = {"", "0", "1", "2", "3", "5", "32", NULL};
  long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                          -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                          INT_MAX,   LONG_MAX, LLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; precision[j]; ++j) {
        for (size_t k = 0; k < sizeof(ints) / sizeof(long long int); ++k) {
          sprintf(format, "_%%%s.%slli_\n", sprintf_flags[i], precision[j]);
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

START_TEST(decimal_flags_width_precision_hh) {
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
  char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
            sprintf(format, "_%%%s%s.%shhi_\n", sprintf_flags[i], width[j],
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

START_TEST(decimal_flags_width_precision_h) {
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
  short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                      0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
            sprintf(format, "_%%%s%s.%shi_\n", sprintf_flags[i], width[j],
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

START_TEST(decimal_flags_width_precision) {
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
  int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                -1,       0,        1,      19,       CHAR_MAX, 1078,
                SHRT_MAX, 10937,    279303, INT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
            sprintf(format, "_%%%s%s.%si_\n", sprintf_flags[i], width[j],
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

START_TEST(decimal_flags_width_precision_l) {
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
  long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                     1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
            sprintf(format, "_%%%s%s.%sli_\n", sprintf_flags[i], width[j],
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

START_TEST(decimal_flags_width_precision_ll) {
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
  long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                          -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                          INT_MAX,   LONG_MAX, LLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; width[j] != NULL; ++j) {
        for (int k = 0; precision[k]; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long long int); ++m) {
            sprintf(format, "_%%%s%s.%slli_\n", sprintf_flags[i], width[j],
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

START_TEST(decimal_flags_star_width_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
          sprintf(format, "_%%%s*hhi_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_width_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                      0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
          sprintf(format, "_%%%s*hi_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_width) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                -1,       0,        1,      19,       CHAR_MAX, 1078,
                SHRT_MAX, 10937,    279303, INT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
          sprintf(format, "_%%%s*i_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_width_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                     1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
          sprintf(format, "_%%%s*li_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_width_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 2, 3, 5, 10, 32};
  int wlen = sizeof(width) / sizeof(int);
  long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                          -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                          INT_MAX,   LONG_MAX, LLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(long long int); ++m) {
          sprintf(format, "_%%%s*lli_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_precision_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
          sprintf(format, "_%%%s.*hhi_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_precision_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                      0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
          sprintf(format, "_%%%s.*hi_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                -1,       0,        1,      19,       CHAR_MAX, 1078,
                SHRT_MAX, 10937,    279303, INT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
          sprintf(format, "_%%%s.*i_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                     1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
          sprintf(format, "_%%%s.*li_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_precision_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int precision[] = {0, 1, 2, 3, 5, 10, 32};
  int plen = (int)(sizeof(precision) / sizeof(int));
  long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                          -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                          INT_MAX,   LONG_MAX, LLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < plen; ++j) {
        for (size_t m = 0; m < sizeof(ints) / sizeof(long long int); ++m) {
          sprintf(format, "_%%%s.*lli_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_width_star_precision_hh) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  char ints[] = {CHAR_MIN, -112, -86 - 1, 0, 1, 87, 113, CHAR_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(char); ++m) {
            sprintf(format, "_%%%s*.*hhi_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_width_star_precision_h) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  short int ints[] = {SHRT_MIN, -1983, CHAR_MIN, -65,      -2,   -1,
                      0,        1,     62,       CHAR_MAX, 1354, SHRT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(short int); ++m) {
            sprintf(format, "_%%%s*.*hi_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_width_star_precision) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  int ints[] = {INT_MIN,  -3941481, -10282, SHRT_MIN, CHAR_MIN, -28,
                -1,       0,        1,      19,       CHAR_MAX, 1078,
                SHRT_MAX, 10937,    279303, INT_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(int); ++m) {
            sprintf(format, "_%%%s*.*i_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_width_star_precision_l) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  long int ints[] = {LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN, -1,      0,
                     1,        CHAR_MAX, SHRT_MAX, INT_MAX,  LONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long int); ++m) {
            sprintf(format, "_%%%s*.*li_\n", sprintf_flags[i]);
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

START_TEST(decimal_flags_star_width_star_precision_ll) {
  int ret;
  int ret21;
  char *buf;
  char *buf21;
  char format[128];
  int width[] = {0, 1, 32};
  int precision[] = {0, 1, 32};
  int wlen = (int)(sizeof(width) / sizeof(int));
  int plen = (int)(sizeof(precision) / sizeof(int));
  long long int ints[] = {LLONG_MIN, LONG_MIN, INT_MIN,  SHRT_MIN, CHAR_MIN,
                          -1,        0,        1,        CHAR_MAX, SHRT_MAX,
                          INT_MAX,   LONG_MAX, LLONG_MAX};

  buf = calloc(1024, sizeof(char));
  buf21 = calloc(1024, sizeof(char));

  if (buf != NULL && buf21 != NULL) {
    for (int i = 0; sprintf_flags[i] != NULL; ++i) {
      for (int j = 0; j < wlen; ++j) {
        for (int k = 0; k < plen; ++k) {
          for (size_t m = 0; m < sizeof(ints) / sizeof(long long); ++m) {
            sprintf(format, "_%%%s*.*lli_\n", sprintf_flags[i]);
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

Suite *suite_s21_sprintf_i(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf i");
  tc = tcase_create("TCase_s21_sprintf_i");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, decimal_flags_hh);
    tcase_add_test(tc, decimal_flags_h);
    tcase_add_test(tc, decimal_flags);
    tcase_add_test(tc, decimal_flags_l);
    tcase_add_test(tc, decimal_flags_ll);
    tcase_add_test(tc, decimal_flags_width_hh);
    tcase_add_test(tc, decimal_flags_width_h);
    tcase_add_test(tc, decimal_flags_width);
    tcase_add_test(tc, decimal_flags_width_l);
    tcase_add_test(tc, decimal_flags_width_ll);
    tcase_add_test(tc, decimal_flags_precision_hh);
    tcase_add_test(tc, decimal_flags_precision_h);
    tcase_add_test(tc, decimal_flags_precision);
    tcase_add_test(tc, decimal_flags_precision_l);
    tcase_add_test(tc, decimal_flags_precision_ll);
    tcase_add_test(tc, decimal_flags_width_precision_hh);
    tcase_add_test(tc, decimal_flags_width_precision_h);
    tcase_add_test(tc, decimal_flags_width_precision);
    tcase_add_test(tc, decimal_flags_width_precision_l);
    tcase_add_test(tc, decimal_flags_width_precision_ll);
    tcase_add_test(tc, decimal_flags_star_width_hh);
    tcase_add_test(tc, decimal_flags_star_width_h);
    tcase_add_test(tc, decimal_flags_star_width);
    tcase_add_test(tc, decimal_flags_star_width_l);
    tcase_add_test(tc, decimal_flags_star_width_ll);
    tcase_add_test(tc, decimal_flags_star_precision_hh);
    tcase_add_test(tc, decimal_flags_star_precision_h);
    tcase_add_test(tc, decimal_flags_star_precision);
    tcase_add_test(tc, decimal_flags_star_precision_l);
    tcase_add_test(tc, decimal_flags_star_precision_ll);
    tcase_add_test(tc, decimal_flags_star_width_star_precision_hh);
    tcase_add_test(tc, decimal_flags_star_width_star_precision_h);
    tcase_add_test(tc, decimal_flags_star_width_star_precision);
    tcase_add_test(tc, decimal_flags_star_width_star_precision_l);
    tcase_add_test(tc, decimal_flags_star_width_star_precision_ll);
    suite_add_tcase(s, tc);
  }

  return (s);
}
