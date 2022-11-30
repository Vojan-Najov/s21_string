#include <stdio.h>
#include <check.h>
#include "s21_string.h"
#include <stdlib.h>

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
	char format[1024];
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	for (int i = 0, c = 'a'; i < 1023; ++i, ++c) {
		c = c > 'z' ? 'a' : c;
		format[i] = c;
	}
	format[1023] = '\0';
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

START_TEST(percentage)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	char *format[] = {
		"_%%_\n",
		"_%100%_\n",
		"_%-32%_\n",
		"_%+32%_\n",
		"_% 32%_\n",
		"_%#32%_\n",
		"_%032%_\n",
		"_%-032%_\n",
		"_%-+#032%_\n",
		"_%.32%_\n",
		"_%%%%%%_\n",
		NULL
	};
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; format[i] != NULL; ++i) {
			ret = sprintf(buf, format[i]);
			ret21 = s21_sprintf(buf21, format[i]);
			ck_assert_int_eq(ret, ret21);
			ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

#include "one_char_format_suite.h"
START_TEST(format_one_char)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		for (int i = 0; one_char_format[i] != NULL; ++i) {
			ret = sprintf(buf, one_char_format[i], 'a');
			ret21 = s21_sprintf(buf21, one_char_format[i], 'a');
			ck_assert_int_eq(ret, ret21);
			ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

#include "two_char_format_suite.h"
START_TEST(format_two_char)
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
			ck_assert_int_eq(ret, ret21);
			ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);
		}
		free(buf);
		free(buf21);
	}
}
END_TEST

START_TEST(format_char_with_star)
{
	int ret;
	int ret21;
	char *buf;
	char *buf21;
	const char *format = "_%*.10c_\n_%64.*c_\n_%*.*c_\n";
	
	buf = calloc(1024, sizeof(char));
	buf21 = calloc(1024, sizeof(char));
	if (buf != NULL && buf21 != NULL) {
		ret = sprintf(buf, format, 24, 'a', 64, 'z', 10, 10, 'e');
		ret21 = s21_sprintf(buf21, format, 24, 'a', 64, 'z', 10, 10, 'e');
		ck_assert_int_eq(ret, ret21);
		ck_assert_int_eq(memcmp(buf, buf21, 1024), 0);

		free(buf);
		free(buf21);
	}
}
END_TEST



Suite *suite_s21_sprintf(void)
{
	Suite *s;
	TCase *tc;

	s = suite_create("Suite_s21_sprintf");
	tc = tcase_create("TCase_s21_sprintf");
	if (s != NULL && tc != NULL) {
		tcase_add_test(tc, empty_format);
		tcase_add_test(tc, simple_string);
		tcase_add_test(tc, wrong_format);
		tcase_add_test(tc, percentage);
		tcase_add_test(tc, format_one_char);
		tcase_add_test(tc, format_two_char);
		tcase_add_test(tc, format_char_with_star);
		suite_add_tcase(s, tc);
	}

	return (s);
}
