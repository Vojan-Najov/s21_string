#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "s21_test.h"

static int run_test_suite(Suite *test_suite) {
  int number_failed = 0;
  SRunner *sr = NULL;

  sr = srunner_create(test_suite);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}

int main(void) {
  int number_failed = 0;
  Suite *suite_array[] = {suite_s21_memchr(),
                          suite_s21_memcmp(),
                          suite_s21_memcpy(),
                          suite_s21_memmove(),
                          suite_s21_memset(),
                          suite_s21_strcat(),
                          suite_s21_strncat(),
                          suite_s21_strchr(),
                          suite_s21_strcmp(),
                          suite_s21_strncmp(),
                          suite_s21_strcpy(),
                          suite_s21_strncpy(),
                          suite_s21_strcspn(),
                          suite_s21_strerror(),
                          suite_s21_strlen(),
                          suite_s21_strpbrk(),
                          suite_s21_strrchr(),
                          suite_s21_strspn(),
                          suite_s21_strstr(),
                          suite_s21_strtok(),
                          suite_s21_sprintf_basic(),
                          suite_s21_sprintf_percent(),
                          suite_s21_sprintf_c(),
                          suite_s21_sprintf_s(),
                          suite_s21_sprintf_d(),
                          suite_s21_sprintf_i(),
                          suite_s21_sprintf_u(),
                          suite_s21_sprintf_o(),
                          suite_s21_sprintf_x(),
                          suite_s21_sprintf_xx(),
                          suite_s21_sprintf_p(),
                          suite_s21_sprintf_n(),
                          suite_s21_sprintf_f(),
                          suite_s21_sprintf_lf(),
                          suite_s21_sprintf_e(),
                          suite_s21_sprintf_le(),
                          suite_s21_sprintf_ee(),
                          suite_s21_sprintf_lee(),
                          suite_s21_sprintf_multi(),
                          suite_s21_sscanf_basic(),
                          suite_s21_sscanf_c(),
                          suite_s21_sscanf_d(),
                          suite_s21_sscanf_i(),
                          suite_s21_sscanf_o(),
                          suite_s21_sscanf_x(),
                          suite_s21_sscanf_xx(),
                          suite_s21_sscanf_p(),
                          suite_s21_sscanf_n(),
                          suite_s21_to_lower(),
                          suite_s21_to_upper(),
                          suite_s21_trim(),
                          suite_s21_insert(),
                          NULL};

  Suite *suite_additions[] = {suite_s21_atoi(), suite_s21_isinteger(),
                              suite_s21_strtol(), suite_s21_strtoul(), NULL};

  for (size_t i = 0; suite_array[i]; ++i) {
    number_failed += run_test_suite(suite_array[i]);
  }
  printf("\ntest auxiliary functions\n");
  for (size_t i = 0; suite_additions[i]; ++i) {
    number_failed += run_test_suite(suite_additions[i]);
  }

  return (number_failed ? EXIT_FAILURE : EXIT_SUCCESS);
}
