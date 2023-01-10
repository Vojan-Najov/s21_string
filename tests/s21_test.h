#ifndef S21_TEST_H
#define S21_TEST_H

Suite *suite_s21_memchr(void);
Suite *suite_s21_memcmp(void);
Suite *suite_s21_memcpy(void);
Suite *suite_s21_memmove(void);
Suite *suite_s21_memset(void);
Suite *suite_s21_strcat(void);
Suite *suite_s21_strncat(void);
Suite *suite_s21_strcmp(void);
Suite *suite_s21_strncmp(void);
Suite *suite_s21_strchr(void);
Suite *suite_s21_strrchr(void);
Suite *suite_s21_strcpy(void);
Suite *suite_s21_strncpy(void);
Suite *suite_s21_strspn(void);
Suite *suite_s21_strcspn(void);
Suite *suite_s21_strlen(void);
Suite *suite_s21_strpbrk(void);
Suite *suite_s21_strstr(void);
Suite *suite_s21_strtok(void);
Suite *suite_s21_strerror(void);
Suite *suite_s21_sprintf_basic(void);
Suite *suite_s21_sprintf_percent(void);
Suite *suite_s21_sprintf_c(void);
Suite *suite_s21_sprintf_d(void);
Suite *suite_s21_sprintf_i(void);
Suite *suite_s21_sprintf_s(void);
Suite *suite_s21_sprintf_u(void);
Suite *suite_s21_sprintf_o(void);
Suite *suite_s21_sprintf_x(void);
Suite *suite_s21_sprintf_xx(void);
Suite *suite_s21_sprintf_p(void);
Suite *suite_s21_sprintf_n(void);
Suite *suite_s21_sprintf_f(void);
Suite *suite_s21_sprintf_lf(void);
Suite *suite_s21_sprintf_e(void);
Suite *suite_s21_sprintf_le(void);
Suite *suite_s21_sprintf_ee(void);
Suite *suite_s21_sprintf_lee(void);
Suite *suite_s21_sprintf_multi(void);
Suite *suite_s21_sscanf_basic(void);
Suite *suite_s21_sscanf_c(void);
Suite *suite_s21_sscanf_d(void);
Suite *suite_s21_sscanf_i(void);
Suite *suite_s21_sscanf_o(void);
Suite *suite_s21_sscanf_x(void);
Suite *suite_s21_sscanf_xx(void);
Suite *suite_s21_sscanf_p(void);
Suite *suite_s21_sscanf_n(void);

Suite *suite_s21_sprintf(void);

Suite *suite_s21_to_upper(void);
Suite *suite_s21_to_lower(void);
Suite *suite_s21_trim(void);
Suite *suite_s21_insert(void);
/* auxiliary */
Suite *suite_s21_atoi(void);
Suite *suite_s21_isinteger(void);
Suite *suite_s21_strtol(void);
Suite *suite_s21_strtoul(void);

#endif
