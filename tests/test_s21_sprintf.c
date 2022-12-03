#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <locale.h>
#include "s21_string.h"
#include "suite_sprintf_flags.h"

FILE *logfile;

START_TEST(empty_format)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	const char *format = "";
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		ret = sprintf(buf, format);
		ret21 = s21_sprintf(buf21, format);
		ck_assert_int_eq(ret, ret21);
		ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(simple_string)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[4096];
	
	buf = calloc(4096, sizeof(char));
	buf21 = calloc(4096, sizeof(char));
	for (int i = 0, c = 'a'; i < 4095; ++i, ++c) {
		c = c > 'z' ? 'a' : c;
		format[i] = c;
	}
	format[4095] = '\0';
	if (buf != NULL && buf21 != NULL) {
		ret = sprintf(buf, format);
		ret21 = s21_sprintf(buf21, format);
		ck_assert_int_eq(ret, ret21);
		ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(wrong_format)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	const char *format = "%-1234q";
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		ret = sprintf(buf, format);
		ret21 = s21_sprintf(buf21, format);
		ck_assert_int_eq(ret, ret21);
		ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		format = "asdsda%+h";
		ret = sprintf(buf, format);
		ret21 = s21_sprintf(buf21, format);
		ck_assert_int_eq(ret, ret21);
		ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(percent_flags)
{
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
			fprintf(logfile, "format:%s%6d:%s%6d:%s", format, \
					ret, buf, ret21, buf21); 
			ck_assert_int_eq(ret, ret21);
			ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(percent_flags_width)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	int width[] = {1, 32};
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; j < 2; ++j ) {
				sprintf(format, "_%%%s%d%%_\n", sprintf_flags[i], width[j]);
				ret = sprintf(buf, format);
				ret21 = s21_sprintf(buf21, format);
				fprintf(logfile, "format:%s%6d:%s%6d:%s",
						format, ret, buf, ret21, buf21); 
				ck_assert_int_eq(ret, ret21);
				ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(percent_flags_precesion)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	char *precesion[] = {"", "0", "1", "32", NULL};
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; precesion[j]; ++j ) {
				sprintf(format, "_%%%s.%s%%_\n", sprintf_flags[i], precesion[j]);
				ret = sprintf(buf, format);
				ret21 = s21_sprintf(buf21, format);
				fprintf(logfile, "format:%s%6d:%s%6d:%s",
						format, ret, buf, ret21, buf21); 
				ck_assert_int_eq(ret, ret21);
				ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(percent_flags_width_precesion)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	char *width[] = {"", "1", "32", "64", NULL};
	char *precesion[] = {"", "0", "1", "32", "64", NULL};
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; width[j]; ++j ) {
				for (int k = 0; precesion[k]; ++k ) {
					sprintf(format, "_%%%s%s.%s%%_\n", \
						sprintf_flags[i], width[j], precesion[k]);
					ret = sprintf(buf, format);
					ret21 = s21_sprintf(buf21, format);
					fprintf(logfile, "format:%s%6d:%s%6d:%s",
							format, ret, buf, ret21, buf21); 
					ck_assert_int_eq(ret, ret21);
					ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
				}
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(percent_flags_star_width)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	int width[] = {0, 1, 32};
	int wlen = sizeof(width) / sizeof(int);
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; j < wlen; ++j ) {
				sprintf(format, "_%%%s*%%_\n", sprintf_flags[i]);
				ret = sprintf(buf, format, width[j]);
				ret21 = s21_sprintf(buf21, format, width[j]);
				fprintf(logfile, "format:%s%6d:%s%6d:%s",
						format, ret, buf, ret21, buf21); 
				ck_assert_int_eq(ret, ret21);
				ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(percent_flags_star_precesion)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	int precesion[] = {0, 1, 32};
	int wlen = sizeof(precesion) / sizeof(int);
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; j < wlen; ++j ) {
				sprintf(format, "_%%%s.*%%_\n", sprintf_flags[i]);
				ret = sprintf(buf, format, precesion[j]);
				ret21 = s21_sprintf(buf21, format, precesion[j]);
				fprintf(logfile, "format:%s%6d:%s%6d:%s",
						format, ret, buf, ret21, buf21); 
				ck_assert_int_eq(ret, ret21);
				ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(percent_flags_star_width_star_precesion)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	int width[] = {0, 1, 32};
	int precesion[] = {0, 1, 32};
	int wlen = sizeof(width) / sizeof(int);
	int plen = sizeof(precesion) / sizeof(int);
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; j < wlen; ++j ) {
				for (int k = 0; k < plen; ++k ) {
					sprintf(format, "_%%%s*.*%%_\n", sprintf_flags[i]);
					ret = sprintf(buf, format, width[j], precesion[k]);
					ret21 = s21_sprintf(buf21, format, width[j], precesion[k]);
					fprintf(logfile, "format:%s%6d:%s%6d:%s",
							format, ret, buf, ret21, buf21); 
					ck_assert_int_eq(ret, ret21);
					ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
				}
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST


START_TEST(char_flags)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			sprintf(format, "_%%%sc_\n", sprintf_flags[i]);
			ret = sprintf(buf, format, 'a');
			ret21 = s21_sprintf(buf21, format, 'a');
			fprintf(logfile, "format:%s%6d:%s%6d:%s",
					format, ret, buf, ret21, buf21); 
			ck_assert_int_eq(ret, ret21);
			ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(char_flags_width)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	int width[] = {1, 32};
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; j < 2; ++j ) {
				sprintf(format, "_%%%s%dc_\n", sprintf_flags[i], width[j]);
				ret = sprintf(buf, format, 'a');
				ret21 = s21_sprintf(buf21, format, 'a');
				fprintf(logfile, "format:%s%6d:%s%6d:%s",
						format, ret, buf, ret21, buf21); 
				ck_assert_int_eq(ret, ret21);
				ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(char_flags_precesion)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	char *precesion[] = {"", "0", "1", "32", NULL};
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; precesion[j]; ++j ) {
				sprintf(format, "_%%%s.%sc_\n", sprintf_flags[i], precesion[j]);
				ret = sprintf(buf, format, 'a');
				ret21 = s21_sprintf(buf21, format, 'a');
				fprintf(logfile, "format:%s%6d:%s%6d:%s",
						format, ret, buf, ret21, buf21); 
				ck_assert_int_eq(ret, ret21);
				ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(char_flags_width_precesion)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	char *width[] = {"", "1", "32", "64", NULL};
	char *precesion[] = {"", "0", "1", "32", "64", NULL};
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; width[j]; ++j ) {
				for (int k = 0; precesion[k]; ++k ) {
					sprintf(format, "_%%%s%s.%s%%_\n", \
						sprintf_flags[i], width[j], precesion[k]);
					ret = sprintf(buf, format);
					ret21 = s21_sprintf(buf21, format);
					fprintf(logfile, "format:%s%6d:%s%6d:%s",
							format, ret, buf, ret21, buf21); 
					ck_assert_int_eq(ret, ret21);
					ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
				}
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(char_flags_star_width)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	int width[] = {0, 1, 32};
	int wlen = sizeof(width) / sizeof(int);
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; j < wlen; ++j ) {
				sprintf(format, "_%%%s*c_\n", sprintf_flags[i]);
				ret = sprintf(buf, format, width[j], 'a');
				ret21 = s21_sprintf(buf21, format, width[j], 'a');
				fprintf(logfile, "format:%s%6d:%s%6d:%s",
						format, ret, buf, ret21, buf21); 
				ck_assert_int_eq(ret, ret21);
				ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(char_flags_star_precesion)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	int precesion[] = {0, 1, 32};
	int wlen = sizeof(precesion) / sizeof(int);
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; j < wlen; ++j ) {
				sprintf(format, "_%%%s.*c_\n", sprintf_flags[i]);
				ret = sprintf(buf, format, precesion[j], 'a');
				ret21 = s21_sprintf(buf21, format, precesion[j], 'a');
				fprintf(logfile, "format:%s%6d:%s%6d:%s",
						format, ret, buf, ret21, buf21); 
				ck_assert_int_eq(ret, ret21);
				ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(char_flags_star_width_star_precesion)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	int width[] = {0, 1, 32};
	int precesion[] = {0, 1, 32};
	int wlen = sizeof(width) / sizeof(int);
	int plen = sizeof(precesion) / sizeof(int);
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; j < wlen; ++j ) {
				for (int k = 0; k < plen; ++k ) {
					sprintf(format, "_%%%s*.*c_\n", sprintf_flags[i]);
					ret = sprintf(buf, format, width[j], precesion[k], 'a');
					ret21 = s21_sprintf(buf21, format, width[j], precesion[k], 'a');
					fprintf(logfile, "format:%s%6d:%s%6d:%s",
							format, ret, buf, ret21, buf21); 
					ck_assert_int_eq(ret, ret21);
					ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
				}
			}
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(two_char)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; two_char_format[i] != NULL; ++i) {
			ret = sprintf(buf, two_char_format[i], 'a', 'z');
			ret21 = s21_sprintf(buf21, two_char_format[i], 'a', 'z');
			fprintf(logfile, "format:%s%6d:%s%6d%s", two_char_format[i], ret, buf, \
					ret21, buf21); 
			ck_assert_int_eq(ret, ret21);
			ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(wchar)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char format[128];
	int width[] = {0, 1, 32};
	int precesion[] = {0, 1, 32};
	int wlen = sizeof(width) / sizeof(int);
	int plen = sizeof(precesion) / sizeof(int);
	wchar_t wc = 0;
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; sprintf_flags[i] != NULL; ++i) {
			for (int j = 0; j < wlen; ++j ) {
				for (int k = 0; k < plen; ++k ) {
					sprintf(format, "_%%%s*.*lc_\n", sprintf_flags[i]);
					ret = sprintf(buf, format, width[j], precesion[k], wc);
					ret21 = s21_sprintf(buf21, format, width[j], precesion[k], wc);
					fprintf(logfile, "format:%s%6d:%s%6d:%s",
							format, ret, buf, ret21, buf21); 
					ck_assert_int_eq(ret, ret21);
					if (ret == ret21 && ret > 0)
						ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
				++wc;
				}
			}
		}
		free(buf);
		free(buf21);
	}
}

Suite *suite_s21_sprintf(void)
{
	Suite *s;
	TCase *tc;

	printf("%zu\n", MB_CUR_MAX);
	setlocale(LC_ALL, "");
	printf("%zu\n", MB_CUR_MAX);
	logfile = fopen("sprintf.log", "w");
	if (logfile == NULL) {
		perror("sprintf.log");
		return NULL;
	}
	s = suite_create("Suite_s21_sprintf");
	tc = tcase_create("TCase_s21_sprintf");
	if (s != NULL && tc != NULL) {
		tcase_add_test(tc, empty_format);
		tcase_add_test(tc, simple_string);
		tcase_add_test(tc, wrong_format);

		tcase_add_test(tc, percent_flags);
		tcase_add_test(tc, percent_flags_width);
		tcase_add_test(tc, percent_flags_precesion);
		tcase_add_test(tc, percent_flags_width_precesion);
		tcase_add_test(tc, percent_flags_star_width);
		tcase_add_test(tc, percent_flags_star_precesion);
		tcase_add_test(tc, percent_flags_star_width_star_precesion);

		tcase_add_test(tc, char_flags);
		tcase_add_test(tc, char_flags_width);
		tcase_add_test(tc, char_flags_precesion);
		tcase_add_test(tc, char_flags_width_precesion);
		tcase_add_test(tc, char_flags_star_width);
		tcase_add_test(tc, char_flags_star_precesion);
		tcase_add_test(tc, char_flags_star_width_star_precesion);
		tcase_add_test(tc, two_char);
		tcase_add_test(tc, wchar);

		suite_add_tcase(s, tc);
	}

	return (s);
}
