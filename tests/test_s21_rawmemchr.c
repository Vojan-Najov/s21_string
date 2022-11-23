#define _GNU_SOURCE
#include <check.h>
#include <string.h>
#include "s21_string.h"

START_TEST (found_1)
{
	void *buf = "123456789";
	int c = '7';

	ck_assert_ptr_eq(s21_rawmemchr(buf, c), rawmemchr(buf, c));
}
END_TEST

START_TEST (found_2)
{
	void *buf = "123456789";
	int c = '\0';

	ck_assert_ptr_eq(s21_rawmemchr(buf, c), rawmemchr(buf, c));
}
END_TEST

START_TEST (unsigned_char)
{
	void *buf = "123456789";
	int c = '7' & 0x1ff;

	ck_assert_ptr_eq(s21_rawmemchr(buf, c), rawmemchr(buf, c));
}
END_TEST

Suite *suite_s21_rawmemchr(void)
{
	Suite *s = NULL;
	TCase *tc = NULL;

	s = suite_create("suite_s21_rawmemchr");
	tc = tcase_create("tcase_s21_rawmemchr");
	if (s != NULL && tc != NULL) {
		tcase_add_test(tc, found_1);
		tcase_add_test(tc, found_2);
		tcase_add_test(tc, unsigned_char);
		suite_add_tcase(s, tc);
	}

	return (s);
}
